/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_richtextctrl.h
// Purpose:     XRC resource for wxRichTextCtrl
// Author:      Pascal Potvin
// Created:     25.05.11
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_RICHTEXTCTRL_HPP_
#define _WX_XH_RICHTEXTCTRL_HPP_

#include "wx/xrc/xmlres.h"

#if wxUSE_XRC

class WXDLLIMPEXP_FWD_CORE wxRichTextCtrl;

class WXDLLIMPEXP_XRC wxRichTextCtrlXmlHandler: public wxXmlResourceHandler {
	DECLARE_DYNAMIC_CLASS(wxRichTextCtrlXmlHandler)
public:
	wxRichTextCtrlXmlHandler();
	virtual wxObject *DoCreateResource();
	virtual bool CanHandle(wxXmlNode *node);
};

#endif /* wxUSE_XRC */

#endif /* _WX_XH_RICHTEXTCTRL_HPP_ */
