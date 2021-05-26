/*
 * OptionsDialog.h
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

#ifndef OPTIONSDIALOG_H_
#define OPTIONSDIALOG_H_

#include "OffloadUI.h"
#include "Options.h"

class OptionsDialog : public OptionsDialogUI {
public:
	Options *options;
	OptionsDialog(Options *parent_options);
	~OptionsDialog();
	void save_options(wxFileDirPickerEvent& event);
};


#endif /* OPTIONSDIALOG_H_ */
