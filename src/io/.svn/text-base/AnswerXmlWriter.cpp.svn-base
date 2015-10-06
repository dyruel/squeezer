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

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include "AnswerXmlWriter.h"
#include "../ToolBox.h"
#include "../tinyXML/tinyxml.h"

AnswerXmlWriter::AnswerXmlWriter() {

}

AnswerXmlWriter::~AnswerXmlWriter() {

}

// TODO pleins de new sans delete...
void AnswerXmlWriter::write( std::ostream& output, const Answer& answer ) {

	TiXmlDocument xml;
	TiXmlElement* root = NULL;
	Epoch e;
	const Scenario& scenario = answer.scenario();
	const Config& config = answer.config();

	xml.LinkEndChild(new TiXmlDeclaration( "1.0", "", "" ));

	root = new TiXmlElement( "InfAnswerFile" );
	xml.LinkEndChild(root);

	TiXmlElement * configroot = new TiXmlElement( "config" );
	TiXmlElement * bif = new TiXmlElement( "biffile" );
	bif->SetAttribute("name", ToolBox::file(config.bif()));
	TiXmlElement * inference = new TiXmlElement( "inference" );

	if(config.inferenceType() == Config::LAZY) {
		inference->SetAttribute("type", "lazy");
	}
	else if(config.inferenceType() == Config::GIBBS) {
		inference->SetAttribute("type", "gibbs");
	}
	else if (config.inferenceType() == Config::SHAFER) {
		inference->SetAttribute("type", "shafer");
	}
	else {
		inference->SetAttribute("type", "lazy");
	}

	configroot->LinkEndChild(bif);
	configroot->LinkEndChild(inference);
	root->LinkEndChild(configroot);

	for(e = 0; e <= scenario.epoch(); ++e) {

		TiXmlElement * epoch = new TiXmlElement( "epoch" );
		TiXmlElement * variables = new TiXmlElement( "variables" );
		epoch->SetAttribute( "t", e);

		TiXmlElement * evidences = new TiXmlElement( "evidences" );

		for(Scenario::EvidenceIterator iter = scenario.beginEvidence(); iter != scenario.endEvidence(); ++iter) {
			if( (*iter).at() == e ) {
				TiXmlElement * evidence = NULL;

				if((*iter).isHard()) {
					evidence = new TiXmlElement( "hardevidence" );
				}
				else {
					evidence = new TiXmlElement( "softevidence" );
				}

				evidence->SetAttribute( "variable", (*iter).name() );

				for(Scenario::TemporalEvidence::iterator j = (*iter).begin(); j != (*iter).end(); ++j) {
			           TiXmlElement * modality = new TiXmlElement( "modality" );
			           modality->SetAttribute("name", j.key() );
			           modality->SetDoubleAttribute("value", *j);
			           evidence->LinkEndChild(modality);
				}

				evidences->LinkEndChild(evidence);
			}
		}

		for(Scenario::InterventionIterator iter = scenario.beginIntervention(); iter != scenario.endIntervention(); ++iter) {
			if( (*iter).at() == e ) {
				TiXmlElement * evidence = NULL;

				evidence = new TiXmlElement( "intervention" );

				evidence->SetAttribute( "variable", (*iter).name() );

				for(Scenario::TemporalEvidence::iterator j = (*iter).begin(); j != (*iter).end(); ++j) {
			           TiXmlElement * modality = new TiXmlElement( "modality" );
			           modality->SetAttribute("name", j.key() );
			           modality->SetDoubleAttribute("value", *j);
			           evidence->LinkEndChild(modality);
				}

				evidences->LinkEndChild(evidence);
			}
		}

		epoch->LinkEndChild( evidences );

		for(Scenario::GoalIterator iter = scenario.beginGoal(); iter != scenario.endGoal(); ++iter) {
			TiXmlElement * variable = new TiXmlElement( "variable" );
			const gum::Potential<FIXED_PRECISION>& p = answer.marginal(*iter, e);
			const gum::DiscreteVariable& v = p.variable(0);
			gum::Instantiation i(p);

			variable->SetAttribute( "name", *iter );

			for ( i.setFirst(); !i.end(); ++i ) {
				TiXmlElement * val = new TiXmlElement( "val" );
				std::string value = ToolBox::typToStr( p[i] );
				std::string label = v.label(i.val( (gum::Idx) 0 )); // TODO peut on mieux faire ??

				val->SetAttribute( "label", label );
				val->SetAttribute( "value", value );
				variable->LinkEndChild( val );
			}

			variables->LinkEndChild( variable );
		}

		epoch->LinkEndChild( variables );
		root->LinkEndChild( epoch );
	}

	output << xml;
	xml.SaveFile("test_squeezer.xml");
}

#endif  // DOXYGEN_SHOULD_SKIP_THIS
