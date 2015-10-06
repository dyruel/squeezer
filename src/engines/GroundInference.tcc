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

template <class StaticInference>
GroundInference<StaticInference>::GroundInference(const DynamicBayesNet& dbn):
	DynamicInference(dbn), __groundNet(dbn), __inf(NULL) {

}

template <class StaticInference>
GroundInference<StaticInference>::~GroundInference() {
	if(__inf)
		delete __inf;
}

template <class StaticInference>
void GroundInference<StaticInference>::_fillMarginal(DynNodeId id, Epoch e, gum::Potential<FIXED_PRECISION>& marginal) {
	const gum::DiscreteVariable& v = __groundNet.variable(id, e);
	gum::NodeId idbn = __groundNet.groundNet().nodeId(v);

	if(__inf)
		marginal = __inf->marginal(idbn);
	else
		throw gum::Exception("In GroundInference<StaticInference>::_fillMarginal -> Null pointer", "Squeezer error");
}

template <class StaticInference>
void GroundInference<StaticInference>::setScenario(const Scenario& scenario) {
	gum::Idx k;
	gum::List<const gum::Potential<FIXED_PRECISION>*> evidences;

	clear();

	__groundNet.unroll(scenario.epoch());

	for(Scenario::EvidenceIterator iter = scenario.beginEvidence(); iter != scenario.endEvidence(); ++iter) {

		gum::Potential<FIXED_PRECISION>* e = new gum::Potential<FIXED_PRECISION>( new gum::MultiDimArray<FIXED_PRECISION>() );

		if((*iter).at() > scenario.epoch()) {
			throw gum::Exception("In GroundInference<StaticInference>::setScenario -> Evidence out of time", "Squeezer error");
		}

		const gum::DiscreteVariable& v = __groundNet.variable(_dbn.index((*iter).name()), (*iter).at());

		*e << v;
		e->fill((FIXED_PRECISION) 0);
		gum::Instantiation i(*e);

		for(k=0; k < v.domainSize(); k++) {
			i.chgVal(v, v[v.label(k)]);
			e->set(i, (*iter).value(v.label(k)));
		}

		evidences.insert(e);
	}

	for(Scenario::InterventionIterator iter = scenario.beginIntervention(); iter != scenario.endIntervention(); ++iter) {

		gum::Potential<FIXED_PRECISION>* e = new gum::Potential<FIXED_PRECISION>( new gum::MultiDimArray<FIXED_PRECISION>() );

		if((*iter).at() > scenario.epoch()) {
			throw gum::Exception("In GroundInference<StaticInference>::setScenario -> Intervention out of time", "Squeezer error");
		}

		const gum::DiscreteVariable& v = __groundNet.variable(_dbn.index((*iter).name()), (*iter).at());

		*e << v;
		e->fill((FIXED_PRECISION) 0);
		gum::Instantiation i(*e);

		for(k=0; k < v.domainSize(); k++) {
			i.chgVal(v, v[v.label(k)]);
			e->set(i, (*iter).value(v.label(k)));
		}

		evidences.insert(e);

        // Erase parent arcs
		// TODO Rien à faire sur les CPT ??
		const gum::ArcSet&  parentArcs = __groundNet.groundNet().dag().parents(__groundNet.groundNet().nodeId(v));
		for(gum::ArcSet::iterator iter = parentArcs.begin(); iter != parentArcs.end(); ++iter) {
			const gum::NodeId& parentId = (*iter).tail();
			__groundNet.eraseArc(parentId, __groundNet.groundNet().nodeId(v));
		}
	}

	for(Scenario::ContextInstanceIterator iter = scenario.beginContextInstance(); iter != scenario.endContextInstance(); ++iter) {
//		std::cout << (*iter).name() << std::endl;
	}

//	std::cout << __groundNet.toDot() << std::endl;
//	std::cout << __groundNet.groundNet().cpt( __groundNet.groundNet().nodeId(__groundNet.variable(2, 0)) ) << std::endl;
	__inf = new StaticInference(__groundNet.groundNet());
	__inf->insertEvidence(evidences);
}

template <class StaticInference>
void GroundInference<StaticInference>::execute() {
	if(__inf)
		__inf->makeInference();
	else
		throw gum::Exception("In GroundInference<StaticInference>::execute -> Null pointer", "Squeezer error");
//	std::cout << __inf->marginal(__groundNet.groundNet().nodeId(__groundNet.variable(2, 0))) << std::endl;
}

template <class StaticInference>
void GroundInference<StaticInference>::clear() {
	__groundNet.clear();

	if(__inf)
		delete __inf;
}

#endif  // DOXYGEN_SHOULD_SKIP_THIS


