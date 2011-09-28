/////////////////////////////////////////////////////////////////////////////
// Name:        xrc/xh_treelistctrl.cpp
// Purpose:     XRC resource for wxTreeListCtrl
// Author:      Pascal Potvin
// Created:     25.05.11
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_XRC

#include "wx/xrc/xh_treelistctrl.h"

#include "wx/treelistctrl.h"

IMPLEMENT_DYNAMIC_CLASS(wxTreeListCtrlXmlHandler, wxXmlResourceHandler)

wxTreeListCtrlXmlHandler::wxTreeListCtrlXmlHandler() : wxXmlResourceHandler() {
	XRC_ADD_STYLE(wxTR_NO_BUTTONS);
	XRC_ADD_STYLE(wxTR_HAS_BUTTONS);
	XRC_ADD_STYLE(wxTR_NO_LINES);
	XRC_ADD_STYLE(wxTR_LINES_AT_ROOT);
	XRC_ADD_STYLE(wxTR_TWIST_BUTTONS);

	XRC_ADD_STYLE(wxTR_SINGLE);
	XRC_ADD_STYLE(wxTR_MULTIPLE);

#if WXWIN_COMPATIBILITY_2_8
    XRC_ADD_STYLE(wxTR_EXTENDED);
#endif // WXWIN_COMPATIBILITY_2_8

    XRC_ADD_STYLE(wxTR_HAS_VARIABLE_ROW_HEIGHT);

    XRC_ADD_STYLE(wxTR_EDIT_LABELS);
    XRC_ADD_STYLE(wxTR_ROW_LINES);
    XRC_ADD_STYLE(wxTR_HIDE_ROOT);

    XRC_ADD_STYLE(wxTR_FULL_ROW_HIGHLIGHT);

    XRC_ADD_STYLE(wxTR_DEFAULT_STYLE);
    XRC_ADD_STYLE(wxTR_COLUMN_LINES);
    XRC_ADD_STYLE(wxTR_VIRTUAL);

	AddWindowStyles();
}

wxObject *wxTreeListCtrlXmlHandler::DoCreateResource() {
	//wxAssert(m_class == wxT("wxTreeListCtrl"));

	XRC_MAKE_INSTANCE(tlc, wxTreeListCtrl)

	tlc->Create(m_parentAsWindow, GetID(), GetPosition(), GetSize(), GetStyle(wxT("style")), wxDefaultValidator, GetName());

	return tlc;
}

bool wxTreeListCtrlXmlHandler::CanHandle(wxXmlNode * node) {
	return IsOfClass(node, wxT("TreeListCtrl"));
}

#endif
