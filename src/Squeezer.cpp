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

#include <iostream>
#include <stdio.h>
#include <sys/time.h>

#include "Squeezer.h"
#include "io/DbnBifReader.h"
#include "engines/GroundInference.h"
#include "io/ScenarioXmlReader.h"
#include "io/AnswerXmlWriter.h"
#include "io/AnswerCsvWriter.h"
#include "ToolBox.h"
#include "Config.h"
#include <agrum/BN/inference/lazyPropagation.h>
#include <agrum/BN/inference/Gibbs.h>
#include <agrum/BN/inference/ShaferShenoyInference.h>
#include <agrum/BN/io/BIFIO.h>

//
extern char* optarg;
extern int optind, opterr;

Squeezer::Squeezer():
	__argc(-1), __argv(NULL), __path(""){

}

Squeezer::Squeezer(int argc, char ** argv):
	__argc(argc), __argv(argv), __path("") {

	unsigned int i;

	for(i=0; i < NUM_OPTIONS; ++i) {
		__options[i] = false;
	}

	for(i=0; i < NUM_OPTIONS_ARG; ++i) {
		__optionsArg[i] = NULL;
	}
}

Squeezer::~Squeezer() {

}


void Squeezer::__usage(char* prog) {
	std::cout << "Squeezer 0.4 (powered by aGrUM 0.6)" << std::endl << std::endl;
	std::cout << "usage: " << prog << " [OPTIONS...]" << std::endl;
//	std::cout << "-w	No warnings" << std::endl;
//	std::cout << "-t	Display a benchmark" << std::endl;
	std::cout << "-b biffile	Create a XML description of a BIF" << std::endl;
	std::cout << "-x xmlfile	Read and launch an inference using a XML file" << std::endl;
	std::cout << "-o xml|csv	Output format" << std::endl;
	exit(1);
}


void Squeezer::__init() {
	char* progname = __argv[0];
	int c;
	bool errflag = false;


	while((c = getopt(__argc, __argv, "b:x:f:o:twh")) != -1) {
		switch(c) {
		case 'w':
			__options[DISPLAY_WARNINGS] = true;
			break;
		case 'x':
			__optionsArg[XML_FILE] = optarg;
			break;
		case 'o':
			__optionsArg[OUTPUT_TYPE] = optarg;
			break;
		case 'f':
			__optionsArg[OUTPUT_FILE] = optarg;
			break;
		case 't':
			__options[DISPLAY_BENCH] = true;
			break;
		case 'b':
			__optionsArg[BIF_FILE] = optarg;
			break;
		case 'h':
			__usage(progname);
			break;
		case '?':
			errflag = true;
			break;
		}
	}

	if(errflag) {
		__usage(progname);
	}
}

void Squeezer::__parseScenario(const TiXmlNode& scenario) {
	ScenarioXmlReader reader;
	std::stringstream out;
	out << scenario;
	Scenario* s = reader.read(out);
	__scenarios.push_back(s);
}


void Squeezer::__parseConfig(const TiXmlNode& config) {
	const TiXmlNode* pParent = NULL, * pChild = NULL;

	pParent = config.FirstChild();
	while ( pParent ) {
		pChild = NULL;

		if ( pParent->Type() == TiXmlNode::ELEMENT ) {
			if ( pParent->ValueStr() == "biffile" ) {
				std::string name = pParent->ToElement()->Attribute( "name" );
				__config.setBif(__path.append(name));
			}
			else if( pParent->ValueStr() == "inference" ) {
				Config::InferenceType infType;
				std::string type = pParent->ToElement()->Attribute( "type" );

				if(type == "lazy") {
					infType = Config::LAZY;
				}
				else if(type == "gibbs") {
					infType = Config::GIBBS;
				}
				else if(type == "shafer") {
					infType = Config::SHAFER;
				}
				else if(type == "mincut") {
					infType = Config::MINCUT;
				}
				else{
					std::cout << "No inference engine specified or the engine does not exist. Squeezer will use Lazy." << std::endl;
					infType = Config::LAZY;
				}
				__config.setInferenceType(infType);
			}
		}

		pParent = pParent->NextSibling();
	}

}


void Squeezer::__parse(const TiXmlDocument& xml) {
	const TiXmlNode* pParent = NULL;

	pParent = xml.FirstChild();

	while ( pParent!=NULL && pParent->ValueStr() != "InfSetupFile" ) {
		pParent = pParent->NextSibling();
	}

	if(pParent == NULL || pParent->ValueStr() != "InfSetupFile") {
		throw gum::Exception("In Squeezer::run -> Invalid XML format", "Squeezer error");
	}

	pParent = pParent->FirstChild();

	while(pParent) {
		if(pParent->Type() == TiXmlNode::ELEMENT) {
			std::string nodeName = pParent->ValueStr();

			if(nodeName == "config") {
				__parseConfig(*pParent);
			}
			else if(nodeName == "scenario") {
				__parseScenario(*pParent);
			}
			else {

			}
		}
		pParent = pParent->NextSibling();
	}

}

TiXmlDocument* Squeezer::__createConfig(std::string biffile) {
	TiXmlDocument* doc = new TiXmlDocument();
	TiXmlDeclaration * decl = NULL;
	TiXmlElement * root = NULL;
	gum::BIFReader reader;
	gum::BayesNet<FIXED_PRECISION> bn;
	gum::Idx k;
	std::string name;

	if(!reader.read(biffile, &bn)) {
		throw gum::Exception("In Squeezer::__createConfig -> bif reader error", "Squeezer error");
	}

	decl = new TiXmlDeclaration( "1.0", "", "" );
	root = new TiXmlElement( "config" );
	root->SetAttribute("name", ToolBox::file(biffile));
	doc->LinkEndChild( decl );
	TiXmlElement * variables = new TiXmlElement( "variables" );
	TiXmlElement * engines = new TiXmlElement( "engines" );

	// Variables
	for(gum::NodeSetIterator iter = bn.beginNodes(); iter != bn.endNodes(); ++iter) {
		TiXmlElement * variable = new TiXmlElement( "variable" );
		name =  bn.variable(*iter).name();
		variable->SetAttribute("name",name.substr(0, name.find("_")));

		if(name[name.find("_")+1] != '0')
			continue;

		for(k=0; k < bn.variable(*iter).domainSize(); k++) {
			TiXmlElement * modality = new TiXmlElement( "modality" );
			modality->SetAttribute("name",bn.variable(*iter).label(k));
			variable->LinkEndChild(modality);
		}

		variables->LinkEndChild(variable);
	}

	// Available Engines
	TiXmlElement * engine = new TiXmlElement( "engine" );
	engine->SetAttribute("name", "lazy");
	engines->LinkEndChild(engine);
	engine = new TiXmlElement( "engine" );
	engine->SetAttribute("name", "shafer");
	engines->LinkEndChild(engine);
	engine = new TiXmlElement( "engine" );
	engine->SetAttribute("name", "gibbs");
	engines->LinkEndChild(engine);

	root->LinkEndChild( variables );
	root->LinkEndChild( engines );
	doc->LinkEndChild( root );

	return doc;
}

int Squeezer::run() {
	AnswerWriter* writer = NULL;
	TiXmlDocument xml;

	// Read input
	__init();


	//
	if(__optionsArg[BIF_FILE]) {
		std::string biffile = __optionsArg[BIF_FILE];
		std::cout << *__createConfig(biffile) << std::endl;
		return 0;
	}


	if(__optionsArg[XML_FILE]) {
		xml.LoadFile(__optionsArg[XML_FILE]);
		__path = ToolBox::path(__optionsArg[XML_FILE]);
	}
	else {
		std::cin >> xml;
	}

	// Initialization
	try {
		__parse(xml);
	}
	catch(gum::Exception& e) {
		std::cout << e.getContent() << std::endl;
	}

	// Select the output type
	if(__optionsArg[OUTPUT_TYPE]) {
		std::string outputType(__optionsArg[OUTPUT_TYPE]);

		if(outputType == "xml") {
			writer = new AnswerXmlWriter();
		}
		else if(outputType == "csv") {
			writer = new AnswerCsvWriter();
		}
	}
	else {
		writer = new AnswerXmlWriter();
	}

	// Run the inference
	for(std::vector<const Scenario*>::iterator iter = __scenarios.begin(); iter != __scenarios.end(); ++iter) {
		Answer answer(*(*iter), __config);
		writer->write(std::cout, answer); // TODO ? -> [ Changer la destination (fichier ou stdout) en fonction des options ]
		std::cout << std::endl;
	}
	std::cout << "c" << std::endl;
	if(writer)
		delete writer;

	return 0;
}

#endif  // DOXYGEN_SHOULD_SKIP_THIS

