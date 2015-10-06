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

#include "DbnBifReader.h"
#include <agrum/BN/io/BIFIO.h>

DbnBifReader::DbnBifReader() {
}

DbnBifReader::~DbnBifReader() {

}

DynamicBayesNet* DbnBifReader::read(std::string& filePath) {
	gum::BIFReader reader;
	gum::BayesNet<FIXED_PRECISION> ttbn;

	if(!reader.read(filePath, &ttbn)) {
		throw gum::Exception("In DbnBifReader::read -> bif reader error", "Squeezer error");
	}

	DynamicBayesNet* dbn = new DynamicBayesNet(ttbn);

	return dbn;
}

#endif  // DOXYGEN_SHOULD_SKIP_THIS

