/////////////////////////////////////////////////////////////////////////////
// Name:        xh_treelistctrl.hpp
// Purpose:     XRC resource for wxTreeListCtrl
// Author:      Pascal Potvin
// Created:     2011/05/25
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_TREELISTCTRL_HPP_
#define _WX_XH_TREELISTCTRL_HPP_

#include "wx/xrc/xmlres.h"

#if wxUSE_XRC

class WXDLLIMPEXP_FWD_CORE wxTreeListCtrl;

class WXDLLIMPEXP_XRC wxTreeListCtrlXmlHandler : public wxXmlResourceHandler {
	DECLARE_DYNAMIC_CLASS(wxTreeListCtrlXmlHandler)
public:
	wxTreeListCtrlXmlHandler();
	virtual wxObject *DoCreateResource();
	virtual bool CanHandle(wxXmlNode *node);
};

#endif /* wxUSE_XRC */

#endif /* _WX_XH_TREELISTCTRL_HPP_ */
