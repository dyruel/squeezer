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

#include "Scenario.h"

Scenario::Scenario():
	__epoch(0){

}

Scenario::~Scenario() {

}

void Scenario::addEvidence(const TemporalEvidence& e) {
	__temporalEvidences.push_back(e);
}


void Scenario::addIntervention(const Intervention& e) {
	if(!e.isHard()) {
		throw gum::Exception("In Scenario::addIntervention -> Not an intervention.", "Squeezer error");
	}
	__interventions.push_back(e);
}


void Scenario::addContextInstance(const ContextInstance& e) {
	__contextInstances.push_back(e);
}

void Scenario::addGoal(std::string name) {
	__goals.push_back(name);
}


void Scenario::setEpoch(Epoch epoch) {
	__epoch = epoch;
}

Epoch Scenario::epoch() const {
	return __epoch;
}

Scenario::EvidenceIterator Scenario::beginEvidence() const {
	return __temporalEvidences.begin();
}

Scenario::EvidenceIterator Scenario::endEvidence() const {
	return __temporalEvidences.end();
}

Scenario::InterventionIterator Scenario::beginIntervention() const {
	return __interventions.begin();
}

Scenario::InterventionIterator Scenario::endIntervention() const {
	return __interventions.end();
}

Scenario::ContextInstanceIterator Scenario::beginContextInstance() const {
	return __contextInstances.begin();
}

Scenario::ContextInstanceIterator Scenario::endContextInstance() const {
	return __contextInstances.end();
}

Scenario::GoalIterator Scenario::beginGoal() const {
	return __goals.begin();
}

Scenario::GoalIterator Scenario::endGoal() const {
	return __goals.end();
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
