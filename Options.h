/*
 * Options.h
 *
 *  Created on: 23 May 2021
 *  Author: Leslie Liew <talman.au@gmail.com>
 *
 *  Copyright (C) 2021  Leslie Liew
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <wx/textfile.h> // wxTextFile
#include <wx/filename.h> // wxFileName

class Options {
public:
	wxString conffilename;
	wxTextFile conftextfile;
	wxFileName source;
	wxFileName dest;
	Options();
	~Options();
	void Write();
};

#endif /* OPTIONS_H_ */
