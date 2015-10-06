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

#include "MinCutInference.h"
#include "../GroundNet.h"

MinCutInference::MinCutInference(const DynamicBayesNet& dbn):
	DynamicInference(dbn), __m(1), __s(1) {


}

MinCutInference::~MinCutInference() {

}

std::string MinCutInference::__staticName(std::string name) {
	std::string str = name.substr(0, name.find("_"));
	return str;
}

//void MinCutInference::__extract(gum::UndiGraph& g) {
//	GroundNet gn(_dbn);
//	gn.unroll(__m);
//	g = gn.groundNet().moralGraph();
//
//	for(gum::NodeSetIterator iter = g.beginNodes(); iter != g.endNodes(); ++iter) {
//		std::string name = _dbn.ttbn().variable(*iter).name();
//
//		if(name[name.find("_")+1] == '0') {
//			g.eraseNode(*iter);
//		}
//	}
//
//}

// Actually, this is a simple min between the forward interface and the backward interface
void MinCutInference::__minVertexCut(const gum::UndiGraph& g, gum::NodeId p, gum::NodeId e, gum::Set<gum::NodeId>& interface) {
	interface.clear();
	gum::Set<gum::NodeId> backward, forward;

	for(gum::EdgeSetIterator iter = g.beginEdges(); iter != g.endEdges(); ++iter) {

		if((*iter).first() == e) {
			forward.insert((*iter).second());
		}
		else if((*iter).second() == e) {
			forward.insert((*iter).first());
		}
		else if((*iter).first() == p) {
			backward.insert((*iter).second());
		}
		else if((*iter).second() == p) {
			backward.insert((*iter).first());
		}
	}

	if(forward.size() <= backward.size()) {
		interface = forward;
	}
	else {
		interface = backward;
	}
}

void MinCutInference::_fillMarginal(DynNodeId id, Epoch e, gum::Potential<FIXED_PRECISION>& marginal) {

}

void MinCutInference::setSpan(gum::Size m) {
	if(m<1) return;
	__m = m;
}


void MinCutInference::setSkip(gum::Size s) {
	if(s<1) return;
	__s = s;
}

void MinCutInference::setScenario(const Scenario& scenario) {

}

void MinCutInference::execute() {
	const gum::BayesNet<FIXED_PRECISION>& ttbn = _dbn.ttbn();
	gum::NodeId p, e;
	gum::UndiGraph g;
	gum::Set<gum::NodeId> interface;
	GroundNet gn(_dbn);

	/*
	 * Step 1 : Find the optimal interface
	 */

	gn.unroll(__m);
	gum::BayesNet<FIXED_PRECISION> bn(gn.groundNet()), prologue, chunk, epilogue;

	for(gum::NodeSetIterator iter = bn.beginNodes(); iter != bn.endNodes(); ++iter) {
		std::string name = _dbn.ttbn().variable(*iter).name();

		if(name[name.find("_")+1] == '0') {
			bn.erase(*iter);
		}
	}

	g = bn.moralGraph();

	p = g.insertNode();
	e = g.insertNode();

	for(gum::ArcSetIterator iter = ttbn.dag().beginArcs(); iter != ttbn.dag().endArcs(); ++iter) {
		std::string headName = _dbn.ttbn().variable((*iter).head()).name();
		std::string tailName = _dbn.ttbn().variable((*iter).tail()).name();

		if(tailName[tailName.find("_")+1] == '0' && headName[headName.find("_")+1] == '1') {
			DynNodeId tail = _dbn.index(__staticName(tailName)), head = _dbn.index(__staticName(headName));

			gum::NodeId v = gn.groundNet().nodeId(gn.variable(head, 1));
			gum::NodeId u = gn.groundNet().nodeId(gn.variable(tail, __m));

			g.insertEdge(p,v);
			g.insertEdge(u,e);
		}
	}

	__minVertexCut(g, p, e, interface);

//	std::cout << interface.toString() << std::endl;

	/*
	 * Step 2 : Build the prologue, chunk and epilogue networks using the interface found in the previous step
	 */


}

void MinCutInference::clear() {

}

