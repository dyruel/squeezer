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

#ifndef GROUNDNET_H_
#define GROUNDNET_H_

#include "DynamicBayesNet.h"

/**
 * @class GroundNet
 * @brief Class representing an unrolled Dynamic Bayesian Network
 *
 *
 */
class GroundNet {

	const DynamicBayesNet& __dbn;
	gum::BayesNet<FIXED_PRECISION> __groundNet;
	gum::HashTable<DynNodeId, gum::HashTable<Epoch,gum::NodeId> > __variables;
	gum::HashTable<gum::NodeId, gum::NodeId > __contexts;

	std::string __staticName(std::string name);
	// TODO -> remplacer __cptCopy par une fullCopy (peut pas implémenter une fullCopy car les potentiels sont passés en const !)
	void __cptCopy(const gum::Potential<FIXED_PRECISION>& cpt_src, const gum::Potential<FIXED_PRECISION>& cpt_dst, const gum::HashTable<gum::NodeId, gum::NodeId>& map);

public:


    // ############################################################################
    /// @name Constructors / Destructors
    // ############################################################################
    /// @{

    /**
     * Default constructor.
     */
	GroundNet(const DynamicBayesNet& dbn);


    /**
     * Destructor.
     */
	virtual ~GroundNet();
    /// @}


    // ############################################################################
    /// @name Manipulation Methods
    // ############################################################################
    /// @{

    /**
	 * Unroll the DBN up to a specific epoch
	 *
	 * @param t An epoch
	 *
     */
	void unroll(Epoch t);


    /**
	 * Getter for the ground network
	 *
     * @return Returns a reference on the bayes net
     */
	const gum::BayesNet<FIXED_PRECISION>& groundNet();

    /**
	 * Getter for the variables
	 *
     * @param id The variable id
     * @param e The epoch
     *
     */
	const gum::DiscreteVariable& variable(DynNodeId id, Epoch e);

    /**
	 * Removes an arc in the Ground BN, and update head's CPT.
	 * If (tail, head) doesn't exist, nothing happens.
	 *
     * @param tail The id of the node (variable) at the tail of the arc.
     * @param head The id of the node (variable) at the head of the arc.
     *
     */
	void eraseArc(gum::NodeId tail, gum::NodeId head);

    /**
	 * Clear everything.
     *
     */
	void clear();

	/// @}

    // ############################################################################
    /// @name Output Methods
    // ############################################################################
    /// @{
    /**
	 *
     *
     */
	std::string toString();

    /**
	 *
	 *
	 * @param name The graph name in the dot syntax. Default is G.
	 * @return Returns a string describing the graph in the dot syntax
     *
     */
	std::string toDot(std::string name ="G");
	/// @}
};

#endif /* GROUNDNET_H_ */
