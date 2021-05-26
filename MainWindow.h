/*
 * MainWindow.h
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

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "OffloadUI.h"
#include "Options.h"
#include "OffloadedList.h"
#include "AboutDialog.h"
#include "OptionsDialog.h"
#include "OffloadFrame.h"
#include "ReloadFrame.h"

class MainWindow : public MainWindowUI {
public:
	Options *options;
	OffloadedList *offloadedlist;
	AboutDialog *uiabout;
	OptionsDialog *uioptions;
	OffloadFrame *uioffload;
	ReloadFrame *uireload;

	MainWindow();
	~MainWindow();
	void update_offloaded_listbox();
	void about_click(wxCommandEvent& event);
	void options_click(wxCommandEvent& event);
	void selected(wxCommandEvent& event);
	void offload_click(wxCommandEvent& event);
	void reload_click(wxCommandEvent& event);
};


#endif /* MAINWINDOW_H_ */
