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

#include "Answer.h"
#include "io/DbnBifReader.h"
#include "engines/GroundInference.h"
#include "engines/MinCutInference.h"
#include <agrum/BN/inference/lazyPropagation.h>
#include <agrum/BN/inference/Gibbs.h>
#include <agrum/BN/inference/ShaferShenoyInference.h>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

Answer::Answer(const Scenario& scenario, const Config& config) {
	Epoch e;
	Config::InferenceType infType = config.inferenceType();
	std::string biffile = config.bif();
	DbnBifReader reader;

	__dbn = reader.read(biffile);

	if(infType == Config::LAZY) {
		__inf = new GroundInference<gum::LazyPropagation<FIXED_PRECISION> >(*__dbn);
	}
	else if(infType == Config::GIBBS) {
		__inf = new GroundInference<gum::Gibbs<FIXED_PRECISION> >(*__dbn);
	}
	else if(infType == Config::SHAFER) {
		__inf = new GroundInference<gum::ShaferShenoyInference<FIXED_PRECISION> >(*__dbn);
	}
	else if(infType == Config::MINCUT) {
		__inf = new MinCutInference(*__dbn);
	}
	else{
		std::cout << "No inference engine specified or the engine does not exist. Squeezer will use Lazy." << std::endl;
		__inf = new GroundInference<gum::LazyPropagation<FIXED_PRECISION> >(*__dbn);
	}

	__inf->setScenario(scenario);
	__inf->execute();

	for(Scenario::GoalIterator i = scenario.beginGoal(); i != scenario.endGoal(); ++i) {
		DynNodeId id = __dbn->index(*i);

		for(e = 0; e <= scenario.epoch(); ++e) {

			if ( ! __marginals.exists( *i ) ) {
				gum::HashTable<Epoch, gum::Potential<FIXED_PRECISION>* > hash;
				hash.insert(e, new gum::Potential<FIXED_PRECISION>());
				__marginals.insert(*i, hash);
				*__marginals[*i][e] = __inf->marginal(id, e);
			}
			else if( ! __marginals[*i].exists(e)) {
				__marginals[*i].insert(e, new gum::Potential<FIXED_PRECISION>());
				*__marginals[*i][e] = __inf->marginal(id, e);
			}

		}

	}

	__scenario = scenario;
	__config = config;
}

Answer::~Answer() {
	if(__dbn)
		delete __dbn;
	if(__inf)
		delete __inf;
}

const gum::Potential<FIXED_PRECISION>& Answer::marginal(std::string name, Epoch e) const {
	return *__marginals[name][e];
}

const Scenario& Answer::scenario() const {
	return __scenario;
}

const Config& Answer::config() const {
	return __config;
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
