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

#ifndef MINCUTINFERENCE_H_
#define MINCUTINFERENCE_H_

#include "DynamicInference.h"

class MinCutInference: public DynamicInference {

	gum::Size __m, __s;

	std::string __staticName(std::string name);
	void __extract(gum::UndiGraph& g);

	/**
	 * This min-cut algorithm is based on this paper :
	 * article{263872,
	 * author = {Stoer, Mechthild and Wagner, Frank},
	 * title = {A simple min-cut algorithm},
	 * journal = {J. ACM},
	 * volume = {44},
	 * number = {4},
	 * year = {1997},
	 * issn = {0004-5411},
	 * pages = {585--591},
	 * doi = {http://doi.acm.org/10.1145/263867.263872},
	 * publisher = {ACM},
	 * address = {New York, NY, USA},
	 *}
	 *
	 *
	 */
	void __minVertexCut(const gum::UndiGraph& g, gum::NodeId p, gum::NodeId e, gum::Set<gum::NodeId>& interface);

protected :

	void _fillMarginal(DynNodeId id, Epoch e, gum::Potential<FIXED_PRECISION>& marginal);

public:
	MinCutInference(const DynamicBayesNet& dbn);
	virtual ~MinCutInference();

	void setScenario(const Scenario& scenario);
	void execute();
	void clear();

	/**
	 * Set the number of slices the interface will span across.
	 * By default, m=1 wich is the same as applying the interface algorithm.
	 *
	 * @param m The new value of the parameter
	 *
	 */
	void setSpan(gum::Size m);

	/**
	 * Set the slice skip parameter,ie how many slices to skip between each boundary.
	 * By default, this is set to 1.
	 *
	 * @param s The new value of the skip parameter
	 */
	void setSkip(gum::Size s);
};

#endif /* MINCUTINFERENCE_H_ */
