/**
 * @file icontextctrl.cpp
 * TODO 2011-09-27 Ajouter une description
 * 
 * @date 2011-09-27
 * @author pp
 */

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
