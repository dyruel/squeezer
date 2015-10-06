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

#ifndef SCENARIOREADER_H_
#define SCENARIOREADER_H_

#include "../Scenario.h"

/**
 * @class ScenarioReader
 * @brief Pure virtual class for reading a Scenario from a file
 *
 * Every class used to read the content of a Scenario from a stream,
 * or a file must be a subclass of ScenarioReader.
 *
 */
class ScenarioReader {

public:
	// ############################################################################
	/// @name Constructors / Destructors
	// ############################################################################
	/// @{
	/**
	 * Default constructor.
	 */
	ScenarioReader();

	/**
	 * Default destructor.
	 */
	virtual ~ScenarioReader();
	/// @}

	// ############################################################################
	/// @name Manipulation Methods
	// ############################################################################
	/// @{

	/**
	 * Reads a scenario from the file referenced by filePath.
	 * @return Returns the scenario.
	 */
	virtual Scenario* read(std::istream& input) = 0;
	/// @}

};

#endif /* SCENARIOREADER_H_ */
