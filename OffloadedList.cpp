/*
 * OffloadedList.cpp
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

#include "OffloadedList.h"

#include <wx/log.h> // wxLog
#include <wx/stdpaths.h> // wxStandardPaths

OffloadedList::OffloadedList(wxListBox *parent_ui) : wxTextFile() {
	listfilename = wxStandardPaths::Get().GetExecutablePath()+".list";
	this->Open(listfilename);
	if (!this->Exists()) {
		this->Create();
		wxLogInfo("OffloadedList file created");
	}
	ui = parent_ui;
}

OffloadedList::~OffloadedList() {
	this->Close();
}

void OffloadedList::update_ui() {
	// Update m_offloaded_listbox from OffloadedList
	ui->Clear();
	for (size_t i=0; i<this->GetLineCount(); i++) {
		ui->Insert(this->GetLine(i),i);
	}
}


