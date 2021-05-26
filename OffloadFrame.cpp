/*
 * OffloadFrame.cpp
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

#include "OffloadFrame.h"

#include <wx/log.h> // wxLog
#include <wx/dir.h> // wxDir::GetTotalSize
#include "wxCopyDir.h"

OffloadFrame::OffloadFrame(Options *parent_options, OffloadedList *parent_offloadedlist) : OffloadFrameUI(0) {
	options = parent_options;
	offloadedlist = parent_offloadedlist;

	// Update Free Space
	wxGetDiskSpace(options->source.GetPath(), NULL, &source_space);
	wxLongLong ss = source_space / (1024 * 1024); // use to convert source_space to MB
	this->m_source_space->SetLabel(ss.ToString()+" MB");
	wxGetDiskSpace(options->dest.GetPath(), NULL, &dest_space);
	wxLongLong ds = dest_space / (1024 * 1024); // use to convert dest_space to MB
	this->m_dest_space->SetLabel(ds.ToString()+" MB");
}

OffloadFrame::~OffloadFrame() {
	this->Hide();
}

void OffloadFrame::offload_changed(wxFileDirPickerEvent& event) {
	long long int llirs; // use to convert wxULongLong to wxLongLong
	wxDir::GetTotalSize(this->m_dirpicker->GetDirName().GetPath()).ToString().ToLongLong(&llirs);
	wxLongLong required_space = llirs;

	if (required_space < dest_space) {
		this->m_start_button->Enable();
	} else {
		this->m_start_button->Disable();
	}

	wxLongLong rs = required_space / (1024 * 1024); // use to convert required_space to MB
	this->m_required_space->SetLabel(rs.ToString()+" MB");
}

void OffloadFrame::start_click(wxCommandEvent& event) {
	wxString source = this->m_dirpicker->GetDirName().GetPath(wxPATH_GET_VOLUME | wxPATH_NO_SEPARATOR);
	wxString dest = options->dest.GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR);
	wxString dest_sub = dest+this->m_dirpicker->GetDirName().GetDirs().Last();
	wxLogDebug("Offload "+source+" > "+dest);

	if (!wxDir::Exists(dest_sub)) {
		// Copy to Offload Dir
		//wxSystem("mkdir "+dest_sub);
		wxLogDebug("mkdir "+dest_sub);
		wxFileName::Mkdir(dest_sub);
		//wxSystem("xcopy /E /H /C "+source+" "+dest_sub);
		wxLogDebug("xcopy /E /H /C "+source+" "+dest_sub);
		wxCopyDir(source, dest_sub);

		// Delete from Source
		//wxSystem("rmdir /S /Q "+source);
		wxLogDebug("rmdir /S /Q "+source);
		wxFileName::Rmdir(source, wxPATH_RMDIR_RECURSIVE);

		// Make Junction at Source
		wxLogInfo("mklink /J \""+source+"\" \""+dest_sub+"\"");
		//wxSystem("mklink /J \""+source+"\" \""+dest_sub+"\"");
		wxArrayString output; // Catching Output suppresses cmd window
		wxExecute("cmd /cmklink /J \""+source+"\" \""+dest_sub+"\"", output);

		// Add to OffloadedList
		offloadedlist->AddLine(source+" > "+dest);
		offloadedlist->Write();
		offloadedlist->update_ui();
		this->Destroy();
	} else {
		this->m_start_button->Disable();
		wxLogError("Offload "+source+" > "+dest+" exists "+dest_sub);
	}
}
