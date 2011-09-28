/**
 * @file xh_icontextctrl.hpp
 * TODO 2011-09-24 Ajouter une description
 * 
 * @date 2011-09-24
 * @author pp
 */

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
