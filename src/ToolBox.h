/*****************************************************************************
 *   Squeezer (powered by aGrUM <http://agrum.lip6.fr/>)                     *
 *   Copyright (C) 2008  Chopin Morgan					     *
 *   dyruel_at_gmail.com						     *
 *									     *
 *   This program is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation, either version 3 of the License, or	     *
 *   (at your option) any later version.				     *
 *									     *
 *   This program is distributed in the hope that it will be useful,	     *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of	     *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	     *
 *   GNU General Public License for more details.			     *
 *									     *
 *   You should have received a copy of the GNU General Public License	     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>    *
 *****************************************************************************/

#ifndef TOOLBOX_H
#define TOOLBOX_H

/**
 * @class ToolBox
 * @brief This class contains usefull methods.
 *
 */
class ToolBox {

	public:

		/**
		 * Converts a number from string to type T
		 *
		 * @param str The variable id
		 * @return Returns the number of type T
		 */
		template<typename T>
		static T strToTyp(const std::string& str)
		{
        	T dest;
        	std::istringstream iss( str );
       		iss >> dest;
        	return dest;
		}

		/**
		 * Converts a number of type T to a string
		 *
		 * @param value The variable id
		 * @return Returns the number of type T
		 */
		template<typename T>
		static std::string typToStr(const T& value)
		{
       		std::ostringstream oss;
        	oss << value;
        	return oss.str();
		}

		/**
		 * Get the directory of a file path
		 *
		 * ex : /path/to/file/file.ext -> /path/to/file/
		 *
		 * @param str a file path
		 * @return The directory
		 */
		static std::string path(const std::string& str) {

			std::string::size_type pos = str.find_last_of("/");
			std::string r = "";

			if(pos != std::string::npos) {
				r = str.substr(0, pos) + "/";
			}

			return r;
		}

		static std::string path(const char* str) {
			std::string r(str);

			return path(r);
		}

		/**
		 * Get the file of a file path
		 *
		 * ex : /path/to/file/file.ext -> file.ext
		 *
		 * @param str a file path
		 * @return The file name
		 */
		static std::string file(const std::string& str) {
			std::string::size_type pos = str.find_last_of("/");
			std::string r = "";

			if(pos != std::string::npos) {
				r = str.substr(pos+1, str.length());
			}

			return r;
		}


};

#endif // TOOLBOX_H
