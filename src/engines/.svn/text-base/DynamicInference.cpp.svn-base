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


#include "DynamicInference.h"


DynamicInference::DynamicInference(const DynamicBayesNet& dbn):
	_dbn(dbn){

}

DynamicInference::~DynamicInference() {
	_invalidateMarginals();
}

const DynamicBayesNet& DynamicInference::dbn() {
	return _dbn;
}

void DynamicInference::_invalidateMarginals() {
  for ( gum::HashTable<DynNodeId, gum::HashTable<Epoch, gum::Potential<FIXED_PRECISION>* > >::iterator i = _marginals.begin(); i != _marginals.end(); ++i ) {
	  for ( gum::HashTable<Epoch, gum::Potential<FIXED_PRECISION>* >::iterator j = (*i).begin(); j != (*i).end(); ++j ) {
		  if(*j) delete *j;
	  }
	  (*i).clear();
  }

  _marginals.clear();
}

const gum::Potential<FIXED_PRECISION>& DynamicInference::marginal(DynNodeId id, Epoch e) {

	if ( ! _marginals.exists( id ) ) {
		gum::HashTable<Epoch, gum::Potential<FIXED_PRECISION>* > hash;
		hash.insert(e, new gum::Potential<FIXED_PRECISION>());
		_marginals.insert(id, hash);
		_fillMarginal(id, e, *_marginals[id][e]);
//		std::cout << "new var" << std::endl;
	}
	else if( ! _marginals[id].exists(e)) {
		_marginals[id].insert(e, new gum::Potential<FIXED_PRECISION>());
		_fillMarginal(id, e, *_marginals[id][e]);
//		std::cout << "new e" << std::endl;
	}
//std::cout << "rty" << std::endl;
	return *_marginals[id][e];

}
