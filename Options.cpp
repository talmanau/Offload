/*
 * Options.cpp
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

#include "Options.h"

#include <wx/log.h> // wxLog
#include <wx/stdpaths.h> // wxStandardPaths
#include <wx/textfile.h> // wxTextFile

Options::Options() {
	conffilename = wxStandardPaths::Get().GetExecutablePath()+".conf";
	conftextfile.Open(conffilename);
	if (!conftextfile.Exists()) {
		conftextfile.Create();
		conftextfile.AddLine(wxT("")); // default source
		conftextfile.AddLine(wxT("")); // default dest
		conftextfile.Write();
		wxLogInfo("Options file created");
	}

	source = conftextfile.GetLine(0);
	dest = conftextfile.GetLine(1);
}

Options::~Options() {
	if (conftextfile.IsOpened()) {
		conftextfile.Close();
	}
}

void Options::Write() {
	if (conftextfile.IsOpened()) {
		conftextfile.Clear();
		conftextfile.AddLine(source.GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR));
		conftextfile.AddLine(dest.GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR));
		conftextfile.Write();
		wxLogInfo("Options file saved");
	}
}



