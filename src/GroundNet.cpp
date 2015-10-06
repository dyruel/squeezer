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

#include "GroundNet.h"
#include "ToolBox.h"

GroundNet::GroundNet(const DynamicBayesNet& dbn):
	__dbn(dbn){
//	__groundNet.clear(); // TODO clear()
}

GroundNet::~GroundNet() {

}

std::string GroundNet::__staticName(std::string name) {
	std::string str = name.substr(0, name.find("_"));
	return str;
}

void GroundNet::__cptCopy(const gum::Potential<FIXED_PRECISION>& cpt_src, const gum::Potential<FIXED_PRECISION>& cpt_dst, const gum::HashTable<gum::NodeId, gum::NodeId>& map) {
	gum::Instantiation order, from(cpt_src);
	gum::NodeId id;
//	gum::Potential<FIXED_PRECISION> cpt_tmp;

	const gum::Sequence<const gum::DiscreteVariable*>& seq = cpt_src.variablesSequence();

//	for(gum::Sequence<const gum::DiscreteVariable*>::iterator iter = seq.begin(); iter != seq.end(); ++iter ) {
//		std::cout << *(*iter);
//	}
//	std::cout << std::endl;
//
//	for(gum::Sequence<const gum::DiscreteVariable*>::iterator iter = cpt_dst.variablesSequence().begin(); iter != cpt_dst.variablesSequence().end(); ++iter ) {
//		std::cout << *(*iter);
//	}
//	std::cout << std::endl;

	//
	for(gum::Sequence<const gum::DiscreteVariable*>::iterator iter = seq.begin(); iter != seq.end(); ++iter ) {
		id = __dbn.__ttbn.nodeId(*(*iter));
		order << __groundNet.variable(map[id]);
	}

	cpt_dst.copyFrom(cpt_src, &order);


//    for ( order.setFirst(), from.setFirst();! order.end() ; ++order,++from ) {
//    	cpt_dst.set(order, 0.1);
//    }
	//

//	for(gum::Sequence<const gum::DiscreteVariable*>::iterator iter = cpt_dst.variablesSequence().begin(); iter != cpt_dst.variablesSequence().end(); ++iter ) {
//		std::cout << *(*iter);
//	}
//	std::cout << std::endl;
//
//	std::cout << std::endl;
}

void GroundNet::unroll(Epoch t) {
	const gum::BayesNet<FIXED_PRECISION>& ttbn =  __dbn.__ttbn;
	const gum::DAG& dag = ttbn.dag();
	gum::NodeId id;
	Epoch c = 1;
	gum::HashTable<gum::NodeId, gum::NodeId> map, interSlicesMap;
	std::vector<const gum::Arc*> arcs;

	if(!__groundNet.empty()) {
		clear();
	}

	// Contexts
	for(gum::HashTable<gum::NodeId, gum::NodeId>::iterator iter = __dbn.__idMapContext.begin(); iter != __dbn.__idMapContext.end(); ++iter) {
		id = __groundNet.addVariable(__dbn.__ttbn.variable(*iter));
		map.insert(*iter, id);
		__cptCopy(ttbn.cpt(*iter), __groundNet.cpt(id), map);
	}

	// Variables
	for(gum::HashTable<DynNodeId, gum::NodeId>::iterator iter = __dbn.__idMapFirst.begin(); iter != __dbn.__idMapFirst.end(); ++iter) {
		gum::HashTable<Epoch, gum::NodeId> seq;
		gum::DiscreteVariable* v_cpy = __dbn.__ttbn.variable(*iter).copyFactory(); // TODO bof bof
		DynNodeId dynId = iter.key();

		v_cpy->setName(__staticName(v_cpy->name())+"_0");
		id = __groundNet.addVariable(*v_cpy);

		seq.insert(0, id);
		__variables.insert(dynId, seq);

		map.insert(*iter, id);
		interSlicesMap.insert(__dbn.__idMapSecond[dynId], *iter); // Init of interSlicesMap

		delete v_cpy;
	}

	// Arcs
	for(gum::ArcSetIterator iter = dag.beginArcs(); iter != dag.endArcs(); ++iter) {
		gum::NodeId tail = (*iter).tail(), head = (*iter).head();
		std::string tailName = __dbn.__ttbn.variable(tail).name(), headName = __dbn.__ttbn.variable(head).name();
		char tailType = tailName[tailName.find("_")+1], headType = headName[headName.find("_")+1];

		if(tailType == 'c' && headType == '0') {
			__groundNet.insertArc(map[tail], map[head]);
		}
		else if(tailType == 'c' && headType == '1') {
			arcs.push_back(&(*iter));
		}
		else if(tailType == '0' && headType == '0') {
			__groundNet.insertArc(map[tail], map[head]);
		}
		else if(tailType == '1' && headType == '1') {
			arcs.push_back(&(*iter));
		}
		else if(tailType == '0' && headType == '1') {
			arcs.push_back(&(*iter));
		}
		else {
			throw gum::Exception("In GroundNet::unroll -> Invalid 2TBN Format (1)", "Squeezer error");
		}
	}

	// Cpt
	for(gum::HashTable<gum::NodeId, gum::NodeId>::iterator iter = __dbn.__idMapFirst.begin(); iter != __dbn.__idMapFirst.end(); ++iter) {
		__cptCopy(ttbn.cpt(*iter), __groundNet.cpt(map[*iter]), map);
	}


	// Prepare the while loop
	for(gum::HashTable<gum::NodeId, gum::NodeId>::iterator iter = __dbn.__idMapSecond.begin(); iter != __dbn.__idMapSecond.end(); ++iter) {
		map.insert(*iter, 0);
	}

	while(c <= t) {

		// Variables
		for(gum::HashTable<gum::NodeId, gum::NodeId>::iterator iter = __dbn.__idMapSecond.begin(); iter != __dbn.__idMapSecond.end(); ++iter) {
			gum::DiscreteVariable* v_cpy = __dbn.__ttbn.variable(*iter).copyFactory(); // TODO bof bof
			DynNodeId dynId = iter.key();

			v_cpy->setName(__staticName(v_cpy->name())+"_"+ToolBox::typToStr(c));
			id = __groundNet.addVariable(*v_cpy);

			__variables[dynId].insert(c, id);

			map[*iter] = id;

			delete v_cpy;
		}

		for(std::vector<const gum::Arc*>::iterator iter = arcs.begin(); iter != arcs.end(); ++iter) {
			gum::NodeId tail = (*iter)->tail(), head = (*iter)->head();
			__groundNet.insertArc(map[tail], map[head]);
		}

		// Copy
		for(gum::HashTable<gum::NodeId, gum::NodeId>::iterator iter = __dbn.__idMapSecond.begin(); iter != __dbn.__idMapSecond.end(); ++iter) {
			__cptCopy(ttbn.cpt(*iter), __groundNet.cpt(map[*iter]), map);
		}

		for(gum::HashTable<gum::NodeId, gum::NodeId>::iterator iter = __dbn.__idMapSecond.begin(); iter != __dbn.__idMapSecond.end(); ++iter) {
			map[interSlicesMap[*iter]] = map[*iter];
		}

		++c;
	}

}

const gum::BayesNet<FIXED_PRECISION>& GroundNet::groundNet() {
	return __groundNet;
}


const gum::DiscreteVariable& GroundNet::variable(DynNodeId id, Epoch e) {
	return __groundNet.variable(__variables[id][e]);
}

void GroundNet::eraseArc(gum::NodeId tail, gum::NodeId head) {
	__groundNet.eraseArc(tail, head);
}

void GroundNet::clear() {
//	__groundNet.clear(); // TODO clear()
	__variables.clear(); // TODO c propre ce clear direct ?
}

std::string GroundNet::toString() {
	return __groundNet.dag().toString();
}

std::string GroundNet::toDot(std::string name) {
	std::stringstream strBuff, vars0, vars1;
	gum::HashTable<gum::NodeId, char> sliceMap;

	strBuff << "digraph G {" << std::endl;

	for(gum::HashTable<DynNodeId, gum::HashTable<Epoch,gum::NodeId> >::iterator i = __variables.begin(); i != __variables.end(); ++i) {
		for(gum::HashTable<Epoch, gum::NodeId>::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			strBuff << __groundNet.variable(*j).name() << ";" << std::endl;
		}
	}

	for(gum::ArcSetIterator iter = __groundNet.dag().beginArcs(); iter != __groundNet.dag().endArcs(); ++iter) {
		strBuff << __groundNet.variable((*iter).tail()).name() << "->" << __groundNet.variable((*iter).head()).name() << ";" << std::endl;
	}

	strBuff << "}" << std::endl;

	return strBuff.str();
}

#endif  // DOXYGEN_SHOULD_SKIP_THIS



