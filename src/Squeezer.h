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

#ifndef SQUEEZER_H_
#define SQUEEZER_H_

#ifndef FIXED_PRECISION
#define FIXED_PRECISION double
#endif

#include "tinyXML/tinyxml.h"
#include "DynamicBayesNet.h"
#include "engines/DynamicInference.h"
#include "Config.h"

/*! \mainpage Squeezer
    \b Squeezer is an open source software aimed at making inferences in Dynamic Bayesian Networks (DBN).
    It is written in C++ and relies on the aGrUM library. Squeezer is used for the INCALIN research project (supported by the French ANR-PNRA fund).

    \page install_and_use Installing and using Squeezer
    \section Installation

    To compile and run Squeezer :
    @code
    svn co http://webia.lip6.fr/svn/phw/projects/squeezer/tags/v0.4
    make
    ./build/squeezer
    @endcode


    \section using_squeezer Quick start

	You can use Squeezer in different manners, but the most simple method is :

    @code
	squeezer -x config.xml
    @endcode

	This will read the config.xml file (wich is described in the section below) and write the result in a XML format in the standard output. If you prefer
	to have the result in the CSV format, then type the following command :

    @code
	squeezer -x config.xml -o csv
    @endcode

	If you want to know more about available options, execute this command :

    @code
	squeezer -h
    @endcode

 */

// TODO BUG Les hard evidence de config_squeezer.xml pas pris en compte lorsque inference=shafer
// TODO GENERAL Gerer la balise <comment ....
// TODO GENERAL Mettre des const là où il faut
// TODO GENERAL Finir de mettre en place les tests unitaires
// TODO GENERAL L'option -o finalement pas top -> <outputfile name="filename" type="xml|csv"/>

/**
 * An enumeration of available options
 *
 */
enum {
	DISPLAY_WARNINGS = 0, /** Displays warnings */
	DISPLAY_BENCH, /** Displays a benchmark */
	NUM_OPTIONS /** the number of options */
};

/**
 * An enumeration of options with an argument
 *
 */
enum {
	XML_FILE = 0, /** XML configuration file */
	OUTPUT_TYPE, /** Type of the output */
	OUTPUT_FILE, /** Name of the output file */
	BIF_FILE, /** Creates the config file from the BIF */
	NUM_OPTIONS_ARG
};

/**
 * @class Squeezer
 * @brief The main class of the program : it initializes squeezer, and run it.
 */
class Squeezer {

	void __usage(char* prog);
	void __init();
	TiXmlDocument* __createConfig(std::string biffile);
	void __parseScenario(const TiXmlNode& scenario);
	void __parseConfig(const TiXmlNode& config);
	void __parse(const TiXmlDocument& xml);
	int __argc;
	char ** __argv;

	bool __options[NUM_OPTIONS];
	char* __optionsArg[NUM_OPTIONS_ARG];
	std::string __path;

	std::vector<const Scenario*> __scenarios;
	Config __config;

public:
    // ############################################################################
    /// @name Constructors / Destructors
    // ############################################################################
    /// @{

    /**
     * Default constructor.
     */
	Squeezer();

    /**
     * Constructor
     */
	Squeezer(int argc, char ** argv);

    /**
     * Destructor.
     */
	virtual ~Squeezer();
    /// @}


    // ############################################################################
    /// @name Manipulation Methods
    // ############################################################################
    /// @{

    /**
	 * Runs squeezer
	 *
     * @return Excution status
     *
     */
	int run();

	/// @}
};

#endif /* SQUEEZER_H_ */
