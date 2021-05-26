/*
 * OffloadApp.h
 *
 *  Created on: 21 May 2021
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

#ifndef OFFLOADAPP_H_
#define OFFLOADAPP_H_

#define VERSION "0.1"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "MainWindow.h"
#include <wx/snglinst.h> // wxSingleInstanceChecker

class OffloadApp : public wxApp {
public:
	MainWindow *mainwindow;
	void OnInitCmdLine(wxCmdLineParser& parser);
	bool OnCmdLineParsed(wxCmdLineParser& parser);
	bool OnInit();
	int OnExit();
protected:
	FILE *logfile;
	wxSingleInstanceChecker m_one;
};


#endif /* OFFLOADAPP_H_ */
