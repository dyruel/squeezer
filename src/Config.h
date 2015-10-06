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

#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>

class Config {

public :

	/**
	 * An enumeration of inferences types
	 *
	 */
	typedef enum {
		LAZY = 0, /** Lazy propagation */
		SHAFER, /** Shafer-shenoy inference*/
		GIBBS, /** Gibbs sampling */
		MINCUT, /** Inference using a min-cut */
		NUM_INFERENCES
	} InferenceType;


	Config();
	virtual ~Config();

	void setBif(std::string filename);
	std::string bif() const;

	void setInferenceType(InferenceType inf);
	InferenceType inferenceType() const;

private:

	std::string __bif;
	InferenceType __inf;

};

#endif /* CONFIG_H_ */
