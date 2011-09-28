/////////////////////////////////////////////////////////////////////////////
// Name:        common/icontextctrl.cpp
// Purpose:     wxIconTextCtrl Implementation
// Author:      Pascal Potvin
// Created:     27.09.11
// Copyright:   (c) Pascal Potvin
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#if wxUSE_TEXTCTRL

#include "wx/icontextctrl.h"

wxDEFINE_EVENT(wxEVT_PRIMARY_ICON, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_SECONDARY_ICON, wxCommandEvent);

wxIMPLEMENT_ABSTRACT_CLASS(wxIconTextCtrlBase, wxControl);

extern WXDLLEXPORT_DATA(const char) wxIconTextCtrlNameStr[] = "icontext";

const wxBitmap & wxIconTextCtrlBase::GetIconBitmap(wxTextCtrlIconPosition iconPosition) const {
	return (wxTC_ICON_PRIMARY == iconPosition ? primaryIconBitmap : secondaryIconBitmap);
}

void wxIconTextCtrlBase::SetIconBitmap(wxTextCtrlIconPosition iconPosition, const wxBitmap & bitmap) {
	if (wxTC_ICON_PRIMARY == iconPosition) {
		primaryIconBitmap = bitmap;
	} else {
		secondaryIconBitmap = bitmap;
	}
}

#endif // wxUSE_TEXTCTRL
