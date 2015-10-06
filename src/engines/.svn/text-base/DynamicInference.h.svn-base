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

#ifndef DYNAMICINFERENCE_H_
#define DYNAMICINFERENCE_H_

#include "../DynamicBayesNet.h"
//#include "../Answer.h"
#include "../Scenario.h"

/**
 * @class DynamicInference
 * @brief Abstract class for making inference in dynamic bayesian networks
 *
 *
 *
 */
class DynamicInference {

protected:

	const DynamicBayesNet& _dbn;

	gum::HashTable<DynNodeId, gum::HashTable<Epoch, gum::Potential<FIXED_PRECISION>* > > _marginals;

    /**
     * Returns the marginal of a variable
	 *
     * @param id The variable's id
     * @param e The epoch
     * @param marginal The potential to fill
     *
     */
	virtual void _fillMarginal(DynNodeId id, Epoch e, gum::Potential<FIXED_PRECISION>& marginal) = 0;
	void _invalidateMarginals();

public:
    // ############################################################################
    /// @name Constructors / Destructors
    // ############################################################################
    /// @{

    /**
     * Default constructor.
     */
	DynamicInference(const DynamicBayesNet& dbn);

    /**
     * Destructor.
     */
	virtual ~DynamicInference();
    /// @}

    /**
     * Insert the scenario
	 *
     * @param scenario A scenario
     *
     */
	virtual void setScenario(const Scenario& scenario) = 0;

    /**
     * Makes the inference
	 *
     */
	virtual void execute() = 0;

    /**
     * Returns the probability of the variable.
     * If makeInference wasn't yet called, then only the marginal
     * of the given variable will be computed.
     *
     * @param id The variable's id.
     * @param e The epoch
     * @return The probability of the variable.
     * @throw NotFound Raised if no variable matches id.
     * @throw OperationNotAllowed Raised if the inference has not and can
     * not be done.
     */
	const gum::Potential<FIXED_PRECISION>& marginal(DynNodeId id, Epoch e);

    /**
     * Clear everything
     *
     */
	virtual void clear() = 0;

    /**
     * Getter for the DBN
     *
     * @return A constant reference to the DBN
     */
	const DynamicBayesNet& dbn();
};

#endif /* DYNAMICINFERENCE_H_ */
