/**
 * @file xh_richtextctrl.hpp
 * TODO 2011-09-03 Ajouter une description
 * 
 * @date 2011-09-03
 * @author Pascal Potvin
 */

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
