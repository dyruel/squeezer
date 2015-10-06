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

#include "AnswerCsvWriter.h"
#include "../ToolBox.h"

AnswerCsvWriter::AnswerCsvWriter() {


}

AnswerCsvWriter::~AnswerCsvWriter() {

}

void AnswerCsvWriter::write( std::ostream& output, const Answer& answer ) {
	Epoch e;
	const Scenario& scenario = answer.scenario();
	std::stringstream csvHeadStream, csvDataStream;
	bool done = false;

	csvHeadStream << "epoch";

	for(e = 0; e <= scenario.epoch(); ++e) {
		csvDataStream << ToolBox::typToStr(e);

		for(Scenario::GoalIterator iter = scenario.beginGoal(); iter != scenario.endGoal(); ++iter) {
			const gum::Potential<FIXED_PRECISION>& p = answer.marginal(*iter, e);
			const gum::DiscreteVariable& v = p.variable(0);
			gum::Instantiation i(p);

			for ( i.setFirst(); !i.end(); ++i ) {
				std::string value = ToolBox::typToStr( p[i] );
				std::string label = v.label(i.val( (gum::Idx) 0 )); // TODO peut on mieux faire ??

				if(!done) {
					csvHeadStream << ";" + ( *iter ) + "=" + label;
				}

				csvDataStream << ";" + value;
			}

		}

		done = true;
		csvDataStream << std::endl;
	}

	output << csvHeadStream.str() << std::endl << csvDataStream.str();

}
