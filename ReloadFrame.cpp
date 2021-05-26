/*
 * ReloadFrame.cpp
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

#include "ReloadFrame.h"

#include <wx/log.h> // wxLog
#include <wx/dir.h> // wxDir::GetTotalSize
#include "wxCopyDir.h"

ReloadFrame::ReloadFrame(Options *parent_options, OffloadedList *parent_offloadedlist, size_t selected_arg) : ReloadFrameUI(0) {
	options = parent_options;
	offloadedlist = parent_offloadedlist;
	selected = selected_arg;
	wxString selected_text = offloadedlist->GetLine(selected);
	source = selected_text.SubString(0, selected_text.find(" > ")-1);
	dest = selected_text.SubString(selected_text.find(" > ")+3, selected_text.Len());
	wxLogDebug("source = \""+source+"\"");
	wxLogInfo("dest = \""+dest+"\"");
	this->m_selected_text->SetValue(selected_text);

	// Update Free Space
	wxGetDiskSpace(options->source.GetPath(), NULL, &source_space);
	wxLongLong ss = source_space / (1024 * 1024); // use to convert source_space to MB
	this->m_source_space->SetLabel(ss.ToString()+" MB");
	wxGetDiskSpace(options->dest.GetPath(), NULL, &dest_space);
	wxLongLong ds = dest_space / (1024 * 1024); // use to convert dest_space to MB
	this->m_dest_space->SetLabel(ds.ToString()+" MB");

	wxFileName source_filename = wxFileName::DirName(source);
	wxString dest_sub = dest + wxFileName::DirName(source).GetDirs().Last();
	long long int llirs; // use to convert wxULongLong to wxLongLong
	wxDir::GetTotalSize(dest_sub).ToString().ToLongLong(&llirs);
	wxLongLong required_space = llirs;
	if (required_space < source_space) {
		this->m_stop_button->Enable();
	} else {
		this->m_stop_button->Disable();
	}

	wxLongLong rs = required_space / (1024 * 1024); // use to convert required_space to MB
	this->m_required_space->SetLabel(rs.ToString()+" MB");
}

ReloadFrame::~ReloadFrame() {
	this->Hide();
}

void ReloadFrame::stop_click(wxCommandEvent& event) {
	wxString dest_sub = dest + wxFileName::DirName(source).GetDirs().Last();
	wxLogDebug("Reload "+dest_sub+" > "+source);

	// Delete Junction from Source
	//wxSystem("rmdir "+source);
	wxLogDebug("rmdir "+source);
	wxFileName::Rmdir(source);

	// Copy Offload to source
	//wxSystem("mkdir "+source);
	wxLogDebug("mkdir "+source);
	wxFileName::Mkdir(source);
	//wxSystem("xcopy /E /H /C "+dest_sub+" "+source);
	wxLogDebug("xcopy /E /H /C "+dest_sub+" "+source);
	wxCopyDir(dest_sub, source);

	// Delete from Offload
	//wxSystem("rmdir /S /Q "+dest_sub);
	wxLogDebug("rmdir /S /Q "+dest_sub);
	wxFileName::Rmdir(dest_sub, wxPATH_RMDIR_RECURSIVE);

	// Remove from OffloadList
	offloadedlist->RemoveLine(selected);
	offloadedlist->Write();
	offloadedlist->update_ui();
	this->Destroy();
}



