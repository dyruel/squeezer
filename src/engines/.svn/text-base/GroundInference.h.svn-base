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

#ifndef GROUNDINFERENCE_H_
#define GROUNDINFERENCE_H_

#include <agrum/BN/BayesNet.h>
#include "DynamicInference.h"
#include "../GroundNet.h"

//#ifndef FIXED_PRECISION
//#define FIXED_PRECISION float
//#endif

template <class StaticInference>
class GroundInference : public DynamicInference {

	GroundNet __groundNet;
	StaticInference* __inf;

protected :

	void _fillMarginal(DynNodeId id, Epoch e, gum::Potential<FIXED_PRECISION>& marginal);

public:
	GroundInference(const DynamicBayesNet& dbn);
	virtual ~GroundInference();

	void setScenario(const Scenario& scenario);
	void execute();
	void clear();

};

#include "GroundInference.tcc"

#endif /* GROUNDINFERENCE_H_ */
