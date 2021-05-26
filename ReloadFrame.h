/*
 * ReloadFrame.h
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

#ifndef RELOADFRAME_H_
#define RELOADFRAME_H_

#include "OffloadUI.h"
#include "Options.h"
#include "OffloadedList.h"

class ReloadFrame : public ReloadFrameUI {
public:
	Options *options;
	OffloadedList *offloadedlist;
	size_t selected;
	wxLongLong source_space;
	wxLongLong dest_space;
	ReloadFrame(Options *parent_options, OffloadedList *parent_offloadedlist, size_t selected_arg);
	~ReloadFrame();
	void stop_click(wxCommandEvent& event);
protected:
	wxString source;
	wxString dest;
};


#endif /* RELOADFRAME_H_ */
