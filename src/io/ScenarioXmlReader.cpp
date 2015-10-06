/*****************************************************************************
 *   Squeezer (powered by aGrUM <http://agrum.lip6.fr/>)                     *
 *   Copyright (C) 2008  Chopin Morgan                                       *
 *   dyruel_at_gmail.com                                                     *
 *                                                                           *
 *   This program is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation, either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>    *
 *****************************************************************************/

#include "ScenarioXmlReader.h"
#include "../tinyXML/tinyxml.h"
#include "../ToolBox.h"

ScenarioXmlReader::ScenarioXmlReader() {

}

ScenarioXmlReader::~ScenarioXmlReader() {

}

Scenario* ScenarioXmlReader::read(std::istream& input) {
	Scenario* scenario = new Scenario();
	TiXmlDocument xmlFile;
	input >> xmlFile;
	TiXmlNode* pParent = NULL, * pChild = NULL, * pSubChild = NULL, * pSubSubChild = NULL;
	std::string nodeName, path;

	bool hasEvidences = false;
	bool hasVarsFollow = false;

//	if ( !xmlFile.LoadFile() ) {
//		throw gum::Exception("In ScenarioXmlReader::read -> Failed to load XML file", "Squeezer error");
//	}

//	std::string str(filePath);
//	std::string::size_type pos = str.find_last_of("/");
//	path = "";
//	if(pos != std::string::npos) {
//		path = str.substr(0, pos) + "/";
//	}

	pParent = xmlFile.FirstChild();

//	while ( pParent!=NULL && pParent->ValueStr() != "InfSetupFile" ) {
//		pParent = pParent->NextSibling();
//	}
//
	pParent = pParent->FirstChild();

	while ( pParent ) {

		pChild = NULL;
		pSubChild = NULL;

		if ( pParent->Type() == TiXmlNode::ELEMENT ) {
			nodeName = pParent->ValueStr();
//			std::cout << nodeName << std::endl;
			if ( nodeName == "epochs" ) {
				int epoch;
				pParent->ToElement()->Attribute( "upto", &epoch );
//				std::cout << epoch << std::endl;
				if(epoch < 0) {
					throw gum::Exception("In ScenarioXmlReader::read -> Expected declaration of a positive number of epochs.", "Squeezer error");
				}

				scenario->setEpoch((Epoch) epoch);

			} else if ( nodeName == "follow" ) {
				pChild = pParent->FirstChild();

				while ( pChild != NULL ) {

					if ( pChild->ValueStr() == "variable" ) {
						scenario->addGoal(pChild->ToElement()->Attribute( "name" ));
						hasVarsFollow = true;
//						std::cout << pChild->ToElement()->Attribute( "name" ) << std::endl;
					}

					pChild = pChild->NextSibling();
				}
			} else if ( nodeName == "context" ) {

				pChild = pParent->FirstChild();

				while ( pChild != NULL ) {

					if ( pChild->ValueStr() == "instance" ) {
						Scenario::ContextInstance c(
								pParent->ToElement()->Attribute( "name" ),
								pChild->ToElement()->Attribute( "value" ),
								ToolBox::strToTyp<Epoch>(pChild->ToElement()->Attribute( "start" )),
								ToolBox::strToTyp<Epoch>(pChild->ToElement()->Attribute( "end" ))
						);

//						std::cout << pParent->ToElement()->Attribute( "name" ) << " " << pChild->ToElement()->Attribute( "value" ) << std::endl;
						std::cout << "Context instance are not yet implemented. Squeezer will ignore it." << std::endl;
						scenario->addContextInstance(c);
					}

					pChild = pChild->NextSibling();
				}

			}
			else if ( nodeName == "evidences" ) {

				pChild = pParent->FirstChild();

				while ( pChild != NULL ) {

					if ( pChild->ValueStr() == "epoch" ) {

						int epoch;

						pChild->ToElement()->Attribute( "t", &epoch );

						if(epoch < 0) {
							throw gum::Exception("In ScenarioXmlReader::read -> Expected declaration of a positive number of epochs.", "Squeezer error");
						}

						pSubChild = pChild->FirstChild();

						while ( pSubChild != NULL ) {

							// Insertion hardEvidence
							if ( pSubChild->ValueStr() == "hardevidence" ) {
								Scenario::TemporalEvidence e((Epoch) epoch, pSubChild->ToElement()->Attribute( "variable" ));
								e.setValue(pSubChild->ToElement()->Attribute( "modality" ), 1.0f);
								scenario->addEvidence(e);
//								std::cout << e.name() << "=" << pSubChild->ToElement()->Attribute( "modality" ) << std::endl;
								hasEvidences = true;
							}
							// Insertion softEvidence
							else if ( pSubChild->ValueStr() == "softevidence" ) {
								Scenario::TemporalEvidence e((Epoch) epoch, pSubChild->ToElement()->Attribute( "variable" ));
								pSubSubChild = pSubChild->FirstChild();

								while ( pSubSubChild != NULL ) {

									if ( pSubSubChild->ValueStr() == "modality" ) {
										e.setValue(
												pSubSubChild->ToElement()->Attribute( "name" ),
												ToolBox::strToTyp<FIXED_PRECISION>(pSubSubChild->ToElement()->Attribute( "value" ))
										);

										hasEvidences = true;
									}

									pSubSubChild = pSubSubChild->NextSibling();
								}
//								std::cout << e.name() << "= *" << std::endl;
								scenario->addEvidence(e);
							}
							else if (pSubChild->ValueStr() == "intervention") {
								Scenario::TemporalEvidence e((Epoch) epoch, pSubChild->ToElement()->Attribute( "variable" ));
								e.setValue(pSubChild->ToElement()->Attribute( "modality" ), 1.0f);
								scenario->addIntervention(e);
//								std::cout << e.name() << "=" << pSubChild->ToElement()->Attribute( "modality" ) << std::endl;
								hasEvidences = true;
							}

							pSubChild = pSubChild->NextSibling();
						}
					}

					pChild = pChild->NextSibling();
				}
			}
		}

		pParent = pParent->NextSibling();
	}
	/*
	  if(!evidencesMatrix.isEmpty()) {
	    hasEvidences = true;
	  }
	 */
	if(!hasVarsFollow) {
		//throw SqueezerException("You have to follow at least one variable.");
		gum::Exception("In ScenarioXmlReader::read -> You have to follow at least one variable.", "Squeezer error");
	}

	return scenario;
}
