/*
 * wxCopyDir.cpp
 *
 *  Created on: 23 May 2021
 *  https://forums.wxwidgets.org/viewtopic.php?t=2080#p137769
 */

#include "wxCopyDir.h"

#include <wx/dir.h> // wxDir
#include <wx/filename.h> // wxFileName

// https://forums.wxwidgets.org/viewtopic.php?t=2080#p137769
bool wxCopyDir(wxString sFrom, wxString sTo) {
    if (sFrom[sFrom.Len() - 1] != '\\' && sFrom[sFrom.Len() - 1] != '/') sFrom += wxFILE_SEP_PATH;
    if (sTo[sTo.Len() - 1] != '\\' && sTo[sTo.Len() - 1] != '/') sTo += wxFILE_SEP_PATH;

    if (!wxDirExists(sFrom)) {
        wxLogError(wxT("%s does not exist!\r\nCan not copy directory"), sFrom.c_str());
        return false;
    }
    if (!wxDirExists(sTo)) {
        if (!wxFileName::Mkdir(sTo, 0777, wxPATH_MKDIR_FULL)) {
            wxLogError(wxT("%s could not be created!"), sTo.c_str());
            return false;
        }
    }

    wxDir fDir(sFrom);
    wxString sNext = wxEmptyString;
    bool bIsFile = fDir.GetFirst(&sNext);
    while (bIsFile) {
        const wxString sFileFrom = sFrom + sNext;
        const wxString sFileTo = sTo + sNext;
        if (wxDirExists(sFileFrom)) {
            wxCopyDir(sFileFrom, sFileTo);
        }
        else {
            if (!wxFileExists(sFileTo)) {
                if (!wxCopyFile(sFileFrom, sFileTo)) {
                    wxLogError(wxT("Could not copy %s to %s !"), sFileFrom.c_str(), sFileTo.c_str());
                    return false;
                }
            }
        }
        bIsFile = fDir.GetNext(&sNext);
    }
    return true;
}


