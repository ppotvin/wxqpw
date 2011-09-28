/////////////////////////////////////////////////////////////////////////////
// Name:        xrc/xh_icontextctrl.cpp
// Purpose:     wxIconTextCtrlXmlHandler Implementation
// Author:      Pascal Potvin
// Created:     24.09.11
// Copyright:   (c) Pascal Potvin
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_XRC && wxUSE_TEXTCTRL

#include "wx/xrc/xh_text.h"
#include "wx/xrc/xh_icontextctrl.h"

#include "wx/icontextctrl.h"

wxIMPLEMENT_DYNAMIC_CLASS(wxIconTextCtrlXmlHandler, wxXmlResourceHandler);

wxIconTextCtrlXmlHandler::wxIconTextCtrlXmlHandler() :
	wxXmlResourceHandler()
{
	AddWindowStyles();

	XRC_ADD_STYLE(wxTE_READONLY);
	XRC_ADD_STYLE(wxTE_PROCESS_TAB);
	XRC_ADD_STYLE(wxTE_LEFT);
	XRC_ADD_STYLE(wxTE_CENTER);
	XRC_ADD_STYLE(wxTE_RIGHT);
	XRC_ADD_STYLE(wxTE_CENTRE);
	XRC_ADD_STYLE(wxTE_PROCESS_ENTER);
	XRC_ADD_STYLE(wxTE_PASSWORD);

}


wxObject *wxIconTextCtrlXmlHandler::DoCreateResource() {
	XRC_MAKE_INSTANCE(itc, wxIconTextCtrl)

	wxBitmap pIcon = GetBitmap("primary-icon", wxART_LIST, wxSize(16, 16));
	wxBitmap sIcon = GetBitmap("secondary-icon", wxART_LIST, wxSize(16, 16));

	itc->Create(m_parentAsWindow, GetID(), GetText(wxT("value")), pIcon, sIcon, GetPosition(),
			GetSize(), GetStyle(), wxDefaultValidator, GetName());

	return itc;
}

bool wxIconTextCtrlXmlHandler::CanHandle(wxXmlNode *node) {
	return IsOfClass(node, wxT("IconTextCtrl"));
}

#endif /* wxUSE_XRC */
