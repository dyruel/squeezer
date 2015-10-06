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

#ifndef ANSWERWRITER_H_
#define ANSWERWRITER_H_

#include <iostream>
#include <fstream>
#include "../Answer.h"
//#include <string>

/**
 * @class AnswerWriter
 * @brief Pure virtual class for writting an Answer to a file.
 *
 * Every class used to write the content of an Answer in a stream, or
 * a file must be a subclass of AnswerWriter.
 */
class AnswerWriter {
public:

    /**
     * Default constructor.
     */
	AnswerWriter();

    /**
     * Default destructor.
     */
	virtual ~AnswerWriter();

    /**
     * Writes an Answer in the ouput stream.
     *
     * @param output The output stream.
     * @param answer The answer writen in output.
     * @throws IOError Raised if an I/O error occurs.
     */
    virtual void write( std::ostream &output, const Answer& answer ) = 0;

};

#endif /* ANSWERWRITER_H_ */
