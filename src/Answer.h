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

#ifndef ANSWER_H_
#define ANSWER_H_

#include "engines/DynamicInference.h"
#include "Config.h"

//#ifndef FIXED_PRECISION
//#define FIXED_PRECISION float
//#endif

/**
 * @class Answer
 * @brief Class
 *
 *
 */
class Answer {

	Scenario __scenario;
	Config __config;
	gum::HashTable<std::string, gum::HashTable<Epoch, gum::Potential<FIXED_PRECISION>* > > __marginals;
	DynamicBayesNet* __dbn;
	DynamicInference* __inf;

public:

	Answer(const Scenario& scenario, const Config& config);
	virtual ~Answer();

	const gum::Potential<FIXED_PRECISION>& marginal(std::string name, Epoch e) const;
	const Scenario& scenario() const;
	const Config& config() const;
};

#endif /* ANSWER_H_ */
