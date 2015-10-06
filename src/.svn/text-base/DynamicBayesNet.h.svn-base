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

#ifndef DYNAMICBAYESNET_H_
#define DYNAMICBAYESNET_H_


//#ifndef FIXED_PRECISION
//#define FIXED_PRECISION float
//#endif

#include <agrum/BN/BayesNet.h>

class GroundNet;
typedef gum::NodeId DynNodeId;
typedef unsigned int Epoch;

/**
 * @class DynamicBayesNet
 * @brief Class representing a Dynamic Bayesian Network
 *
 *
 *
 */
class DynamicBayesNet {

	friend class GroundNet;

	DynNodeId __nextIndex;
	gum::HashTable<DynNodeId, gum::NodeId> __idMapFirst, __idMapSecond;
	gum::HashTable<gum::NodeId, gum::NodeId> __idMapContext;
	gum::BayesNet<FIXED_PRECISION> __ttbn;
	gum::HashTable<std::string, DynNodeId> __variableMap;

public:

	typedef std::vector<DynNodeId>::iterator iterator;

    // ############################################################################
    /// @name Constructors / Destructors
    // ############################################################################
    /// @{
    /**
     * Default constructor.
     */
	DynamicBayesNet();

    /**
     * Default constructor.
     */
	DynamicBayesNet(const gum::BayesNet<FIXED_PRECISION>& ttbn);

    /**
     * Destructor.
     */
	virtual ~DynamicBayesNet();
    /// @}

    // ############################################################################
    /// @name Extra Structures
    // ############################################################################
    /// @{

	/**
	 * An enumeration of existing slices
	 *
	 */
	enum SliceId {
		FIRST = 0, /** the slice's id at t */
		SECOND, /** the slice's id at t+1 */
		BOTH, /** designates both slices */
		NUM_SLICES /** */
	};

    /// @}

    // ############################################################################
    /// @name Network Manipulation Methods
    // ############################################################################
    /// @{
    /**
     * Returns the CPT of a variable in a specific slice
     *
     * @warning the value BOTH is not allowed here.
	 *
     * @param id The variable id
     * @param sid The slice id
     * @return Returns a constant reference on the CPT
     */
	const gum::Potential<FIXED_PRECISION>& cpt(DynNodeId id, SliceId sid);

	/**
	 * Returns the bayesian network representation of the 2TBN
	 *
	 * @return Returns a constant reference on the BN
	 *
	 */
	const gum::BayesNet<FIXED_PRECISION>& ttbn() const;

    /**
     * Returns the CPT of a context variable
	 *
     * @param id The variable id
     * @return Returns a constant reference on the CPT
     */
	const gum::Potential<FIXED_PRECISION>& cptContext(gum::NodeId id);

    /**
     * Add a variable
	 *
     * @param var The variable added by copy
     * @return The id of the added variable
     */
	DynNodeId addVariable(const gum::DiscreteVariable& var);

    /**
     * Add a context variable
	 *
     * @param var The context variable added by copy
     * @return The id of the added variable
     */
	gum::NodeId addContext(const gum::DiscreteVariable& var);

    /**
     * Setting a context dependance between a context variable and a variable
     *
	 *
     * @param c The context variable id
     * @param id The variable id
     * @param sid The slice id
     *
     */
	void setContext(gum::NodeId c, DynNodeId id, SliceId sid = BOTH);

    /**
     * Add an arc in a specific slice
     *
	 *
     * @param tail and
     * @param head as NodeId
     * @param sid The slice id
     *
     */
	void addSynchronousArc(DynNodeId tail, DynNodeId head, SliceId sid = BOTH);

    /**
     * Add an arc between a variable at t and a variable at t+1. This makes a temporal dependance.
	 *
     * @param id1 and
     * @param id2 as NodeId
     *
     */
	void addAsynchronousArc(DynNodeId id1, DynNodeId id2);

    /**
	 * Removes a variable
	 *
	 * @warning Not yet implemented !
	 *
     * @param id The variable id
     *
     */
	void eraseVariable(DynNodeId id);

    /**
	 * Getter for the variables
	 *
	 * @warning the value BOTH is not allowed here.
	 *
     * @param id The variable id
     * @param sid The slice id
     *
     */
	const gum::DiscreteVariable& variable(DynNodeId id, SliceId sid);

    /**
	 * Getter for the context variables
	 *
     * @param id The context variable id
     *
     */
	const gum::DiscreteVariable& context(gum::NodeId id);

	/**
	 * Returns variable id from its name.
	 *
	 * @return A NodeId
	 */
	DynNodeId index(std::string name) const;

    /**
	 * Clear everything.
     *
     */
	void clear();

    /**
	 *
     *
     */
	std::string toString() const;

    /**
	 *
	 *
	 * @param name The graph name in the dot syntax. Default is G.
	 * @return Returns a string describing the graph in the dot syntax
     *
     */
	std::string toDot(std::string name ="G") const;

    /// @}

};

#endif /* DYNAMICBAYESNET_H_ */
