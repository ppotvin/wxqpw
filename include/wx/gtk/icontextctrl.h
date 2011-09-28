///////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/icontextctrl.h
// Purpose:     wxIconTextCtrl class - The wxGTK version
// Author:      Pascal Potvin
// Modified by:
// Created:     21.09.11
// RCS-ID:      $Id$
// Copyright:   (c) Pascal Potvin
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_GTK_ICONTEXTCTRL_H_
#define _WX_GTK_ICONTEXTCTRL_H_

#include "../icontextctrl.h"

class wxIconTextCtrl: public wxIconTextCtrlBase {
public:
	wxIconTextCtrl() { Init(); }

	wxIconTextCtrl(wxWindow *parent,
				   wxWindowID id,
				   const wxString &value = wxEmptyString,
				   const wxBitmap & primaryIcon = wxBitmap(),
				   const wxBitmap & secondaryIcon = wxBitmap(),
				   const wxPoint &pos =	wxDefaultPosition,
				   const wxSize &size = wxDefaultSize,
				   long style = 0,
				   const wxValidator& validator = wxDefaultValidator,
				   const wxString &name = wxIconTextCtrlNameStr);

	virtual ~wxIconTextCtrl() { }

	bool Create(wxWindow *parent,
				wxWindowID id,
				const wxString &value =	wxEmptyString,
				const wxBitmap & primaryIcon = wxBitmap(),
				const wxBitmap & secondaryIcon = wxBitmap(),
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				long style = 0,
				const wxValidator& validator = wxDefaultValidator,
				const wxString &name = wxIconTextCtrlNameStr);

    // implement base class pure virtuals
    // ----------------------------------

	virtual bool Enable(bool enable = true);
	virtual void SetWindowStyleFlag(long style);

	virtual void SetIcon(wxTextCtrlIconPosition iconPosition, const wxBitmap & bitmap);
	virtual void EnableIcon(wxTextCtrlIconPosition iconPosition, bool enabled = true);

	virtual void ShowIcon(wxTextCtrlIconPosition iconPosition, bool visible = true);

	virtual void SetIconTooltip(wxTextCtrlIconPosition iconPosition, const wxString & tooltip);

protected:
	// common part of all ctors
	void Init() { }

    // wrappers hiding the differences between functions doing the same thing
    // for GtkTextView and GtkEntry (all of them use current window style to
    // set the given characteristic)
	void GTKSetEditable();
	void GTKSetVisibility();
	void GTKSetActivatesDefault();
	void GTKSetJustification();

    // wxGTK-specific: called recursively by Enable,
    // to give widgets an oppprtunity to correct their colours after they
    // have been changed by Enable
	virtual void OnEnabled(bool enabled);

	virtual void DoSetValue(const wxString &value, int flags = 0);
private:
	virtual GtkEditable *GetEditable() const;
	virtual GtkEntry *GetEntry() const;

	GtkEntry * m_text;
};

#endif // _WX_GTK_ICONTEXTCTRL_H_
