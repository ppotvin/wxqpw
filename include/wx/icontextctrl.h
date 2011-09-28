///////////////////////////////////////////////////////////////////////////////
// Name:        wx/icontextctrl.h
// Purpose:     wxIconTextCtrlBase class - the interface of wxIconTextCtrl
// Author:      Pascal Potvin
// Modified by:
// Created:     27.09.11
// RCS-ID:      $Id$
// Copyright:   (c) Pascal Potvin
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////


#ifndef _WX_ICONTEXTCTRL_H_BASE_
#define _WX_ICONTEXTCTRL_H_BASE_

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "wx/defs.h"

#if wxUSE_TEXTCTRL

#include "wx/control.h"         // the base class
#include "wx/textentry.h"       // single-line text entry interface
#include "wx/gdicmn.h"          // wxPoint
#include "wx/bitmap.h"			// wxBitmap

class WXDLLIMPEXP_FWD_CORE wxIconTextCtrl;
class WXDLLIMPEXP_FWD_CORE wxIconTextCtrlBase;

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

extern WXDLLIMPEXP_DATA_CORE(const char) wxIconTextCtrlNameStr[];

// ----------------------------------------------------------------------------
// wxIconTextCtrl style flags
// ----------------------------------------------------------------------------

#define wxTE_READONLY       0x0010
#define wxTE_PROCESS_TAB    0x0040

// alignment flags
#define wxTE_LEFT           0x0000                    // 0x0000
#define wxTE_CENTER         wxALIGN_CENTER_HORIZONTAL // 0x0100
#define wxTE_RIGHT          wxALIGN_RIGHT             // 0x0200
#define wxTE_CENTRE         wxTE_CENTER

#define wxTE_PROCESS_ENTER  0x0400
#define wxTE_PASSWORD       0x0800

// by default, the Windows text control doesn't show the selection when it
// doesn't have focus - use this style to force it to always show it
#define wxTE_NOHIDESEL      0x2000

wxDECLARE_EVENT(wxEVT_PRIMARY_ICON, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_SECONDARY_ICON, wxCommandEvent);

// ----------------------------------------------------------------------------
// wxIconTextCtrl events
// ----------------------------------------------------------------------------

#define EVT_PRIMARY_ICON(winid, func) wx__DECLARE_EVT1(wxEVT_PRIMARY_ICON, winid, wxCommandEventHandler(func))
#define EVT_SECONDARY_ICON(winid, func) wx__DECLARE_EVT1(wxEVT_SECONDARY_ICON, winid, wxCommandEventHandler(func))

// ----------------------------------------------------------------------------
// wxIconTextCtrl events
// ----------------------------------------------------------------------------

enum wxTextCtrlIconPosition
{
	wxTC_ICON_PRIMARY,
	wxTC_ICON_SECONDARY,
};

// ----------------------------------------------------------------------------
// wxIconTextCtrlBase: a single line text zone with icons where user can edit text.
// ----------------------------------------------------------------------------

class wxIconTextCtrlBase: public wxControl,
							public wxTextEntry
{
public:
	// creation
	// --------
	wxIconTextCtrlBase() { }
	virtual ~wxIconTextCtrlBase() {	}

	virtual void SetIcon(wxTextCtrlIconPosition iconPosition, const wxBitmap & bitmap) =0;
	virtual void EnableIcon(wxTextCtrlIconPosition iconPosition, bool enabled = true) =0;
	void DisableIcon(wxTextCtrlIconPosition iconPosition)
	{
		EnableIcon(iconPosition, false);
	}

	virtual void ShowIcon(wxTextCtrlIconPosition iconPosition, bool visible = true) =0;
	void HideIcon(wxTextCtrlIconPosition iconPosition)
	{
		ShowIcon(iconPosition, false);
	}

	virtual void SetIconTooltip(wxTextCtrlIconPosition iconPosition, const wxString & tooltip) =0;

protected:
	virtual wxWindow *GetEditableWindow() {	return this; }

	const wxBitmap & GetIconBitmap(wxTextCtrlIconPosition iconPosition) const;
	void SetIconBitmap(wxTextCtrlIconPosition iconPosition, const wxBitmap & bitmap);

wxDECLARE_NO_COPY_CLASS(wxIconTextCtrlBase);
wxDECLARE_ABSTRACT_CLASS(wxIconTextCtrlBase);
private:
	wxBitmap primaryIconBitmap;
	wxBitmap secondaryIconBitmap;
};

#if defined(__WXGTK20__)
	#include "wx/gtk/icontextctrl.h"
#endif

#endif // wxUSE_TEXTCTRL
#endif // _WX_ICONTEXTCTRL_H_BASE_
