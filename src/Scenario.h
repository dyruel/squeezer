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

#ifndef SCENARIO_H_
#define SCENARIO_H_

#include "DynamicBayesNet.h"
#include <agrum/core/hashTable.h>

/**
 * @class Scenario
 * @brief Class representing a scenario for a Dynamic Bayesian Network
 *
 */
class Scenario {

public:

    // ############################################################################
    /// @name Extra structures
    // ############################################################################
    /// @{

	/**
	 * @class TemporalEvidence
	 * @brief Class representing an Evidence in a Scenario for a Dynamic Bayesian Network
	 *
	 */
	class TemporalEvidence {
		Epoch __at;
		std::string __varName;
		gum::HashTable<std::string, FIXED_PRECISION> __values;

	public:

		typedef gum::HashTable<std::string, FIXED_PRECISION>::iterator iterator;

	    // ############################################################################
	    /// @name Constructors / Destructors
	    // ############################################################################
	    /// @{
	    /**
	     * Default constructor.
	     *
	     * @param at
	     * @param varName Name of the variable
	     *
	     *
	     */
		TemporalEvidence(Epoch at, std::string varName):
			__at(at), __varName(varName){
			__values.clear();
		}

	    /**
	     * Destructor.
	     */
		virtual ~TemporalEvidence(){
		}
		/// @}

	    // ############################################################################
	    /// @name Manipulation Methods
	    // ############################################################################
	    /// @{

	    /**
	     * Setting the value of a modality
	     *
	     * @param modality The name of the modality
	     * @param value The value
	     *
	     *
	     */
		void setValue(std::string modality, FIXED_PRECISION value) {
			if(__values.exists(modality)) {
				__values[modality] = value;
			}
			else {
				__values.insert(modality, value);
			}
		}

	    /**
	     * Getting the epoch of the evidence
	     *
	     * @return The epoch
	     *
	     */
		Epoch at() const {
			return __at;
		}

	    /**
	     * Getting the name of the variable
	     *
	     * @return The name of the variable
	     *
	     */
		std::string name() const {
			return __varName;
		}

	    /**
	     * Checks if the evidence is hard or not.
	     *
	     */
		bool isHard() const {
			FIXED_PRECISION v = (FIXED_PRECISION) 0, one = (FIXED_PRECISION) 1;

			if(__values.size()!=1) {
				return false;
			}

			for(gum::HashTable<std::string, FIXED_PRECISION>::iterator iter = __values.begin(); iter != __values.end(); ++iter) {
				v = *iter;
			}

			return v == one;
		}

	    /**
	     * Getting the value of a modality
	     *
	     * @param modality The name of the modality
	     * @return The modality value
	     *
	     */
		FIXED_PRECISION value(std::string modality) const {
			if(__values.exists(modality)) {
				return __values[modality];
			}
			else {
				return (FIXED_PRECISION) 0;
			}
		}
		/// @}

		//TODO faire un begin() end()
		iterator begin() const {
			return __values.begin();
		}

		iterator end() const {
			return __values.end();
		}

	};


	typedef TemporalEvidence Intervention;

	/**
	 * @class ContextInstance
	 * @brief Class representing an Context instance in a Scenario for a Dynamic Bayesian Network
	 *
	 */
	class ContextInstance {
		std::string __varName, __value;
		Epoch __begin, __end;

	public:

	    // ############################################################################
	    /// @name Constructors / Destructors
	    // ############################################################################
	    /// @{

	    /**
	     * Default constructor.
	     *
	     * @param varName Name of the variable
	     * @param value The value taken by the variable
	     * @param begin from begin
	     * @param end to end
	     *
	     *
	     */
		ContextInstance(std::string varName, std::string value, Epoch begin, Epoch end):
			__varName(varName), __value(value), __begin(begin), __end(end) {
		}

	    /**
	     * Destructor.
	     */
		virtual ~ContextInstance(){
		}
		/// @}

	    // ############################################################################
	    /// @name Manipulation Methods
	    // ############################################################################
	    /// @{

	    /**
	     * Getting the name of the context variable
	     *
	     * @return The name of the context variable
	     *
	     */
		std::string name() const {
			return __varName;
		}

	    /**
	     * Getting the value of the context instance
	     *
	     * @return The value
	     *
	     */
		std::string value() const {
			return __value;
		}

		// TODO changer nom begin et end : confusion possible avec iterator
		Epoch begin() const {
			return __begin;
		}

		Epoch end() const {
			return __end;
		}
		/// @}
	};

	typedef std::vector<TemporalEvidence>::const_iterator EvidenceIterator;
	typedef std::vector<Intervention>::const_iterator InterventionIterator;
	typedef std::vector<ContextInstance>::const_iterator ContextInstanceIterator;
	typedef std::vector<std::string>::const_iterator GoalIterator;

	/// }@

    // ############################################################################
    /// @name Constructors / Destructors
    // ############################################################################
    /// @{
    /**
     * Default constructor.
     */
	Scenario();

    /**
     * Destructor.
     */
	virtual ~Scenario();
	/// @}

    // ############################################################################
    /// @name Manipulation Methods
    // ############################################################################
    /// @{

    /**
	 * Insert an evidence in the dynamic bayesian network
	 *
     * @param e A temporal evidence
     *
     */
	void addEvidence(const TemporalEvidence& e);

    /**
	 * Insert an intervention in the dynamic bayesian network
	 *
     * @param e An intervention
     *
     */
	void addIntervention(const Intervention& e);

    /**
	 * Insert an instantiation of a context node in the dynamic bayesian network
	 *
     * @param e A temporal evidence
     *
     */
	void addContextInstance(const ContextInstance& e);

    /**
	 * Add a name of a variable to follow
	 *
     * @param name A variable name
     *
     */
	void addGoal(std::string name);

    /**
	 * Setting the horizon of the dynamic bayesian network
	 *
     * @param epoch The horizon
     *
     */
	void setEpoch(Epoch epoch);

    /**
	 * Getting the horizon value
	 *
     * @return The horizon value
     *
     */
	Epoch epoch() const;

	/// @}

    // ############################################################################
    /// @name Iteration Methods
    // ############################################################################
    /// @{

    /**
	 * Iterates on the evidences
     *
     */
	EvidenceIterator beginEvidence() const;
	EvidenceIterator endEvidence() const;

    /**
	 * Iterates on the intervention
     *
     */
	InterventionIterator beginIntervention() const;
	InterventionIterator endIntervention() const;

    /**
	 * Iterates on the context instances
     *
     */
	ContextInstanceIterator beginContextInstance() const;
	ContextInstanceIterator endContextInstance() const;

    /**
	 * Iterates on the variable names to follow
     *
     */
	GoalIterator beginGoal() const;
	GoalIterator endGoal() const;

	/// @}

private:

	std::vector<std::string> __goals;
	std::vector<TemporalEvidence> __temporalEvidences;
	std::vector<Intervention> __interventions;
	std::vector<ContextInstance> __contextInstances;
	Epoch __epoch;


};

#endif /* SCENARIO_H_ */
