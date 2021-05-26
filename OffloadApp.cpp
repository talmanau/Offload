/*
 * OffloadApp.cpp
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

#include "OffloadApp.h"

#include <wx/log.h>  // wxLog
#include <wx/stdpaths.h> // wxStandardPaths

IMPLEMENT_APP(OffloadApp)

void OffloadApp::OnInitCmdLine(wxCmdLineParser& parser) {
}

bool OffloadApp::OnCmdLineParsed(wxCmdLineParser& parser) {
	return true;
}

bool OffloadApp::OnInit() {
	wxString logfilename = wxStandardPaths::Get().GetExecutablePath()+".log";
	logfile = wxFopen(logfilename, wxT("a"));
	if (logfile == NULL) {
		wxLogFatalError("Unable to open log filename=%s", logfilename);
		return false;
	}
	delete wxLog::SetActiveTarget(new wxLogStderr(logfile));
	wxLog::SetVerbose();
	wxLog::SetTimestamp("%Y-%m-%d_%H:%M:%S");
	wxLog::SetLogLevel(wxLOG_Debug);

    if (!wxApp::OnInit()) {
    	wxLogFatalError("Unable to wxApp::OnInit()");
    	return false;
    }

    if (m_one.IsAnotherRunning()) {
    	wxLogWarning("Process already running");
    	return false;
    }

    wxLogInfo("Start OffloadApp process");

    // Create MainWindow class
    mainwindow = new MainWindow();
    mainwindow->Show();

    return true;
}

int OffloadApp::OnExit() {
	wxLogInfo("Exit OffloadApp process");
	delete wxLog::SetActiveTarget(NULL);
	fclose(logfile);
    return wxApp::OnExit();
}


// MainWindow
