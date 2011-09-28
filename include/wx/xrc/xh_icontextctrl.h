/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_icontextctrl.h
// Purpose:     XRC resource for wxIconTextCtrl
// Author:      Pascal Potvin
// Created:     25.05.11
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_ICONTEXTCTRL_H_
#define _WX_XH_ICONTEXTCTRL_H_

#include "wx/xrc/xmlres.h"

#if wxUSE_XRC && wxUSE_TEXTCTRL

class WXDLLIMPEXP_FWD_CORE wxIconTextCtrl;

class WXDLLIMPEXP_XRC wxIconTextCtrlXmlHandler: public wxXmlResourceHandler {
	wxDECLARE_DYNAMIC_CLASS(wxIconTextCtrlXmlHandler);
public:
	wxIconTextCtrlXmlHandler();
	virtual wxObject *DoCreateResource();
	virtual bool CanHandle(wxXmlNode * node);
};

#endif // wxUSE_XRC && wxUSE_TEXTCTRL

#endif // _WX_XH_ICONTEXTCTRL_H_
