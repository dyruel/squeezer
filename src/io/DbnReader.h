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

#ifndef DBNREADER_H_
#define DBNREADER_H_

#include "../DynamicBayesNet.h"
#include <agrum/core/hashTable.h>

/**
 * @class DbnReader
 * @brief Pure virtual class for reading a DBN from a file
 *
 * Every class used to read the content of a Dynamic Bayesian Network from a stream,
 * or a file must be a subclass of DbnReader.
 *
 */
class DbnReader {


public:
	// ############################################################################
	/// @name Constructors / Destructors
	// ############################################################################
	/// @{
	/**
	 * Default constructor.
	 */
	DbnReader();

	/**
	 * Default destructor.
	 */
	virtual ~DbnReader();
	/// @}

	// ############################################################################
	/// @name Manipulation Methods
	// ############################################################################
	/// @{

	/**
	 * Reads a Dynamic Bayesian Network from the file referenced by filePath.
	 * @return Returns the Dynamic Bayesian Network.
	 */
	virtual DynamicBayesNet* read(std::string& filePath) = 0;
	/// @}
};

#endif /* DBNREADER_H_ */
