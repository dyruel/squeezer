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

#include "DynamicBayesNet.h"
#include <agrum/multidim/labelizedVariable.h>
#include <agrum/core/exceptions.h>


DynamicBayesNet::DynamicBayesNet():
	__nextIndex(0){

}

DynamicBayesNet::DynamicBayesNet(const gum::BayesNet<FIXED_PRECISION>& ttbn):
	__nextIndex(0),__ttbn(ttbn)  {

	for(gum::NodeSetIterator iter = __ttbn.beginNodes(); iter != __ttbn.endNodes(); ++iter) {
		std::string name = __ttbn.variable(*iter).name();
		std::size_t pos = name.find("_");

		if(pos == std::string::npos) {
			throw gum::Exception("In DynamicBayesNet::DynamicBayesNet -> Invalid 2TBN Format (0)", "Squeezer error");
		}

		char type = name[pos+1];
		std::string realName = name.substr(0, pos);

//		std::cout << __variableMap << std::endl;
//		std::cout << __idMapFirst << std::endl;
//		std::cout << __idMapSecond << std::endl;

		switch(type) {

		case 'c':
//			std::cout << "insert __variableMap 1 : " << realName << " -> " << __nextIndex << std::endl;
//			std::cout << "insert __idMapContext 2 : " << __nextIndex << " -> " << *iter << std::endl;
			__idMapContext.insert(__nextIndex, *iter);
			__variableMap.insert(realName, __nextIndex);
			__nextIndex++;
			break;

		case '0':

			if(__variableMap.exists(realName)) {
//				std::cout << "insert __idMapFirst 3 : " << __variableMap[realName] << " -> " << *iter << std::endl;
				__idMapFirst.insert(__variableMap[realName], *iter);
			}
			else {
//				std::cout << "insert __idMapFirst 4 : " << __nextIndex << " -> " << *iter << std::endl;
//				std::cout << "insert __variableMap 5 : " << realName << " -> " << __nextIndex << std::endl;
				__idMapFirst.insert(__nextIndex, *iter);
				__variableMap.insert(realName, __nextIndex);
				__nextIndex++;
			}

			break;

		case '1':

			if(__variableMap.exists(realName)) {
//				std::cout << "insert __idMapSecond 6 : " << __variableMap[realName] << " -> " << *iter << std::endl;
				__idMapSecond.insert(__variableMap[realName], *iter);
			}
			else {
//				std::cout << "insert __idMapSecond 7 : " << __nextIndex << " -> " << *iter << std::endl;
//				std::cout << "insert __variableMap 8 : " << realName << " -> " << __nextIndex << std::endl;
				__idMapSecond.insert(__nextIndex, *iter);
				__variableMap.insert(realName, __nextIndex);
				__nextIndex++;
			}

			break;

		default:
			throw gum::Exception("In DynamicBayesNet::DynamicBayesNet -> Invalid 2TBN Format (1)", "Squeezer error");

		}
	}

}

DynamicBayesNet::~DynamicBayesNet() {

}

const gum::BayesNet<FIXED_PRECISION>& DynamicBayesNet::ttbn() const {
	return __ttbn;
}

const gum::Potential<FIXED_PRECISION>& DynamicBayesNet::cpt(DynNodeId id, SliceId sid) {

	gum::NodeId idBN;

	try {
		if(sid == FIRST) {
			idBN = __idMapFirst[id];
		}
		else if(sid == SECOND) {
			idBN = __idMapSecond[id];
		}
		else {
			throw gum::Exception("In DynamicBayesNet::cpt -> Operation not allowed", "Squeezer error");
		}
	}
	catch(gum::NotFound e){
		throw gum::Exception("In DynamicBayesNet::cpt -> "+e.getContent(), "Squeezer error");
	}

	return __ttbn.cpt(idBN);
}


const gum::Potential<FIXED_PRECISION>& DynamicBayesNet::cptContext(gum::NodeId id) {

	gum::NodeId idBN;

	try {
		idBN = __idMapContext[id];
	}
	catch(gum::NotFound e) {
		throw gum::Exception("In DynamicBayesNet::cptContext -> "+e.getContent(), "Squeezer error");
	}

	return __ttbn.cpt(idBN);
}


DynNodeId DynamicBayesNet::addVariable(const gum::DiscreteVariable& v) {

	gum::NodeId ids[2];
	gum::DiscreteVariable* v_cpy = v.copyFactory(); // TODO bof ou alors à stocker pour une utilisation ultérieure ?

	v_cpy->setName(v.name()+"_0");
	ids[0] = __ttbn.addVariable(*v_cpy);

	v_cpy->setName(v.name()+"_1");
	ids[1] = __ttbn.addVariable(*v_cpy);

	__idMapFirst.insert(__nextIndex, ids[0]);
	__idMapSecond.insert(__nextIndex, ids[1]);
	__variableMap.insert(v.name(), __nextIndex);
	__nextIndex++;

	delete v_cpy;

	return (__nextIndex-1);
}

gum::NodeId DynamicBayesNet::addContext(const gum::DiscreteVariable& v) {

	gum::NodeId id;
	gum::DiscreteVariable* v_cpy = v.copyFactory(); // TODO bof ou alors à stocker pour une utilisation ultérieure ?

	v_cpy->setName(v.name()+"_1");
	id = __ttbn.addVariable(v);

	__idMapContext.insert(__nextIndex, id);
	__variableMap.insert(v.name(), __nextIndex);
	__nextIndex++;

	delete v_cpy;

	return (__nextIndex-1);

}

void DynamicBayesNet::setContext(gum::NodeId c, DynNodeId id, SliceId sid) {
	gum::NodeId idTail, idsHead[2];

	try {
		idTail = __idMapContext[c];
		idsHead[0] = __idMapFirst[id];
		idsHead[1] = __idMapSecond[id];
	}
	catch(gum::NotFound e) {
		throw gum::Exception("In DynamicBayesNet::setContext -> "+e.getContent(), "Squeezer error");
	}

	if(sid == FIRST || sid == BOTH) {
//		std::cout << __ttbn.variable(idsTail[0]).name() << " " << __ttbn.variable(idsHead[0]).name() << std::endl;
		__ttbn.insertArc(idTail, idsHead[0]);
	}

	if(sid == SECOND || sid == BOTH) {
//		std::cout << __ttbn.variable(idsTail[1]).name() << " " << __ttbn.variable(idsHead[1]).name() << std::endl;
		__ttbn.insertArc(idTail, idsHead[1]);
	}
}

void DynamicBayesNet::addSynchronousArc(DynNodeId tail, DynNodeId head, SliceId sid) {

	gum::NodeId idsTail[2], idsHead[2];

	try {
		idsTail[0] = __idMapFirst[tail];
		idsTail[1] = __idMapSecond[tail];
		idsHead[0] = __idMapFirst[head];
		idsHead[1] = __idMapSecond[head];
	}
	catch(gum::NotFound e) {
		throw gum::Exception("In DynamicBayesNet::insertArc -> "+e.getContent(), "Squeezer error");
	}

	if(sid == FIRST || sid == BOTH) {
//		std::cout << __ttbn.variable(idsTail[0]).name() << " " << __ttbn.variable(idsHead[0]).name() << std::endl;
		__ttbn.insertArc(idsTail[0], idsHead[0]);
	}

	if(sid == SECOND || sid == BOTH) {
//		std::cout << __ttbn.variable(idsTail[1]).name() << " " << __ttbn.variable(idsHead[1]).name() << std::endl;
		__ttbn.insertArc(idsTail[1], idsHead[1]);
	}

}


void DynamicBayesNet::addAsynchronousArc(DynNodeId tail, DynNodeId head) {

	gum::NodeId idsTail[2], idsHead[2];

	try {
		idsTail[0] = __idMapFirst[tail];
		idsTail[1] = __idMapSecond[tail];
		idsHead[0] = __idMapFirst[head];
		idsHead[1] = __idMapSecond[head];
	}
	catch(gum::NotFound e) {
		throw gum::Exception("In DynamicBayesNet::setTemporalDependance -> "+e.getContent(), "Squeezer error");
	}

//	std::cout << __ttbn.variable(idsTail[0]).name() << " -> " << __ttbn.variable(idsHead[1]).name() << std::endl;
	__ttbn.insertArc(idsTail[0], idsHead[1]);

}

void DynamicBayesNet::eraseVariable(DynNodeId id) {
	// TODO erase variable
}

const gum::DiscreteVariable& DynamicBayesNet::variable(DynNodeId id, SliceId sid) {

	gum::NodeId idBN;

	try {
		if(sid == FIRST) {
			idBN = __idMapFirst[id];
		}
		else if(sid == SECOND) {
			idBN = __idMapSecond[id];
		}
		else {
			throw gum::Exception("In DynamicBayesNet::cpt -> Operation not allowed", "Squeezer error");
		}
	}
	catch(gum::NotFound e){
		throw gum::Exception("In DynamicBayesNet::cpt -> "+e.getContent(), "Squeezer error");
	}

	return __ttbn.variable(idBN);

}


const gum::DiscreteVariable& DynamicBayesNet::context(gum::NodeId id) {
	gum::NodeId i;

	try {
		i = __idMapContext[id];
	}
	catch(gum::NotFound e) {
		throw gum::Exception("In DynamicBayesNet::context -> "+e.getContent(), "Squeezer error");
	}

	return __ttbn.variable(i);
}

DynNodeId DynamicBayesNet::index(std::string name) const {
	try {
		return __variableMap[name];
	}
	catch(gum::NotFound e) {
		throw gum::Exception("In DynamicBayesNet::index -> "+e.getContent(), "Squeezer error");
	}
}


void DynamicBayesNet::clear() {
//	__ttbn.clear(); // TODO clear()
	__nextIndex = 0;
	__idMapFirst.clear();
	__idMapSecond.clear();
	__idMapContext.clear();
}

std::string DynamicBayesNet::toString() const {
	return __ttbn.dag().toString();
}

std::string DynamicBayesNet::toDot(std::string name) const {

	std::stringstream strBuff, vars0, vars1;
//	gum::HashTable<gum::NodeId, char> sliceMap;

	strBuff << "digraph G {" << std::endl;

	strBuff << "rankdir=\"LR\"" << std::endl;
	strBuff << "ranksep=.75" << std::endl;

	strBuff << "subgraph cluster_0 {" << std::endl;
	for(gum::HashTable<gum::NodeId, gum::NodeId>::iterator iter = __idMapFirst.begin(); iter != __idMapFirst.end(); ++iter) {
		strBuff << __ttbn.variable(*iter).name() << std::endl;
//		sliceMap.insert(*iter, '0');
	}
	strBuff << "}" << std::endl;

	strBuff << "subgraph cluster_1 {" << std::endl;
	for(gum::HashTable<gum::NodeId, gum::NodeId>::iterator iter = __idMapSecond.begin(); iter != __idMapSecond.end(); ++iter) {
		strBuff << __ttbn.variable(*iter).name() << std::endl;
//		sliceMap.insert(*iter, '1');
	}
	strBuff << "}" << std::endl;

	strBuff << "subgraph cluster_c {" << std::endl;
	for(gum::HashTable<gum::NodeId, gum::NodeId>::iterator iter = __idMapContext.begin(); iter != __idMapContext.end(); ++iter) {
		strBuff << __ttbn.variable(*iter).name() << std::endl;
//		sliceMap.insert((*iter), 'c');
	}
	strBuff << "}" << std::endl;

	for(gum::ArcSetIterator iter = __ttbn.dag().beginArcs(); iter != __ttbn.dag().endArcs(); ++iter) {
		strBuff << __ttbn.variable((*iter).tail()).name() << "->" << __ttbn.variable((*iter).head()).name() << std::endl;
	}

	strBuff << "}" << std::endl;

	return strBuff.str();
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */

