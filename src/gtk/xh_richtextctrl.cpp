/**
 * @file xh_richtextctrl.cpp
 * TODO 2011-09-03 Ajouter une description
 * 
 * @date 2011-09-03
 * @author Pascal Potvin
 */

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_XRC

#include "wx/xrc/xh_richtextctrl.h"
#include "wx/richtext/richtextctrl.h"

IMPLEMENT_DYNAMIC_CLASS(wxRichTextCtrlXmlHandler, wxXmlResourceHandler)

wxRichTextCtrlXmlHandler::wxRichTextCtrlXmlHandler() :
		wxXmlResourceHandler()
{
	AddWindowStyles();

	XRC_ADD_STYLE(wxRE_CENTRE_CARET);
	XRC_ADD_STYLE(wxRE_MULTILINE);
	XRC_ADD_STYLE(wxRE_READONLY);

}

wxObject *wxRichTextCtrlXmlHandler::DoCreateResource() {
	XRC_MAKE_INSTANCE(rtc, wxRichTextCtrl)

	rtc->Create(m_parentAsWindow, GetID(), GetText(wxT("value")), GetPosition(),
			GetSize(), GetStyle(), wxDefaultValidator, GetName());

	return rtc;
}

bool wxRichTextCtrlXmlHandler::CanHandle(wxXmlNode *node) {
	return IsOfClass(node, wxT("RichTextCtrl"));
}

#endif /* wxUSE_XRC */
