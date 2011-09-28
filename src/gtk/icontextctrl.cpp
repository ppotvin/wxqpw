/////////////////////////////////////////////////////////////////////////////
// Name:        gtk/icontextctrl.cpp
// Purpose:     wxIconTextCtrl GTK Implementation
// Author:      Pascal Potvin
// Created:     21.09.11
// Copyright:   (c) Pascal Potvin
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#if wxUSE_TEXTCTRL

#include "wx/icontextctrl.h"

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib-object.h>

extern "C"
{
static void gtk_icon_release_callback(GtkEntry *entry,
		GtkEntryIconPosition icon_pos, GdkEventButton *event,
		wxIconTextCtrl * textCtrl)
{
	gint x = event->x;
	gint y = event->y;

	gint width = gdk_window_get_width(event->window);
	gint height = gdk_window_get_height(event->window);

	// "icon-release" event should be converted into a full click if the mouse stayed on the icon.
	if ((x >= 0 && x <= width) && (y >= 0 && y <= height))
	{
		wxCommandEvent commandEvent(
				(icon_pos == GTK_ENTRY_ICON_PRIMARY ?
						wxEVT_PRIMARY_ICON : wxEVT_SECONDARY_ICON), textCtrl->GetId());
				commandEvent.SetEventObject(textCtrl);
				textCtrl->HandleWindowEvent(commandEvent);
			}
		}

		static void gtk_icontextctrl_popup_unmap( GtkMenu *WXUNUSED(menu),wxIconTextCtrl* win) {
	win->GTKEnableFocusOutEvent();
}

static void gtk_icontextctrl_populate_popup( GtkEntry *WXUNUSED(entry), GtkMenu *menu, wxIconTextCtrl *win ) {
	win->GTKDisableFocusOutEvent();

	g_signal_connect (menu, "unmap", G_CALLBACK (gtk_icontextctrl_popup_unmap), win );
}

static void gtk_text_changed_callback( GtkWidget *WXUNUSED(widget), wxIconTextCtrl *win ) {

	if (!win->m_hasVMT) {
		return;
	}

	win->SendTextUpdatedEvent();
}
}

//-----------------------------------------------------------------------------
//  clipboard events: "copy-clipboard", "cut-clipboard", "paste-clipboard"
//-----------------------------------------------------------------------------

// common part of the event handlers below
static void handle_text_clipboard_callback(GtkWidget *widget,
		wxIconTextCtrl *win, wxEventType eventType, const gchar * signal_name)
{
	wxClipboardTextEvent event(eventType, win->GetId());
	event.SetEventObject(win);
	if (win->HandleWindowEvent(event))
	{
		// don't let the default processing to take place if we did something
		// ourselves in the event handler
		g_signal_stop_emission_by_name(widget, signal_name);
	}
}

extern "C"
{
static void gtk_copy_clipboard_callback(GtkWidget *widget, wxIconTextCtrl *win)
{
	handle_text_clipboard_callback(widget, win, wxEVT_COMMAND_TEXT_COPY,
			"copy-clipboard");
}

static void gtk_cut_clipboard_callback(GtkWidget *widget, wxIconTextCtrl *win)
{
	handle_text_clipboard_callback(widget, win, wxEVT_COMMAND_TEXT_CUT,
			"cut-clipboard");
}

static void gtk_paste_clipboard_callback(GtkWidget *widget, wxIconTextCtrl *win)
{
	handle_text_clipboard_callback(widget, win, wxEVT_COMMAND_TEXT_PASTE,
			"paste-clipboard");
}
}

wxIconTextCtrl::wxIconTextCtrl(wxWindow *parent,
							   wxWindowID id,
							   const wxString &value,
							   const wxBitmap & primaryIcon,
							   const wxBitmap & secondaryIcon,
							   const wxPoint &pos,
							   const wxSize &size,
							   long style,
							   const wxValidator& validator,
							   const wxString &name)
{
	Init();

	Create(parent, id, value, primaryIcon, secondaryIcon, pos, size, style,
			validator, name);
}

bool wxIconTextCtrl::Create(wxWindow *parent,
							wxWindowID id,
							const wxString &value,
							const wxBitmap & primaryIcon,
							const wxBitmap & secondaryIcon,
							const wxPoint &pos,
							const wxSize &size,
							long style,
							const wxValidator& validator,
							const wxString &name)
{
	if (!PreCreation(parent, pos, size)
			|| !CreateBase(parent, id, pos, size, style, validator, name))
	{
		wxFAIL_MSG( wxT("wxIconTextCtrl creation failed"));
		return false;
	}

	m_widget = gtk_entry_new();
	m_text = GTK_ENTRY(m_widget);

	// work around probable bug in GTK+ 2.18 when calling WriteText on a
	// new, empty control, see http://trac.wxwidgets.org/ticket/11409
	gtk_entry_get_text(m_text);

	if (style & wxNO_BORDER)
	{
		g_object_set(m_text, "has-frame", FALSE, NULL);
	}

	g_object_ref(m_widget);

	m_parent->DoAddChild(this);

	m_focusWidget = m_widget;

	PostCreation(size);

	g_signal_connect(m_text, "changed", G_CALLBACK(gtk_text_changed_callback),
			this);

	g_signal_connect(m_text, "populate_popup",
			G_CALLBACK(gtk_icontextctrl_populate_popup), this);

	if (!value.empty())
	{
		SetValue(value);
	}

	if (style & wxTE_PASSWORD)
	{
		GTKSetVisibility();
	}

	if (style & wxTE_READONLY)
	{
		GTKSetEditable();
	}

	if (style & (wxTE_RIGHT | wxTE_CENTRE))
	{
		GTKSetJustification();
	}

	GTKSetActivatesDefault();

	g_signal_connect(m_text, "copy-clipboard",
			G_CALLBACK (gtk_copy_clipboard_callback), this);
	g_signal_connect(m_text, "cut-clipboard",
			G_CALLBACK (gtk_cut_clipboard_callback), this);
	g_signal_connect(m_text, "paste-clipboard",
			G_CALLBACK (gtk_paste_clipboard_callback), this);

	g_signal_connect(m_text, "icon-release",
			G_CALLBACK (gtk_icon_release_callback), this);

	if (primaryIcon.IsOk())
	{
		SetIcon(wxTC_ICON_PRIMARY, primaryIcon);
	}

	if (secondaryIcon.IsOk())
	{
		SetIcon(wxTC_ICON_SECONDARY, secondaryIcon);
	}

	//m_cursor = wxCursor(wxCURSOR_IBEAM);

	return true;
}

GtkEditable *wxIconTextCtrl::GetEditable() const
{
	return GTK_EDITABLE(m_text);
}


GtkEntry *wxIconTextCtrl::GetEntry() const
{
	return GTK_ENTRY(m_text);
}


// ----------------------------------------------------------------------------
// flags handling
// ----------------------------------------------------------------------------

void wxIconTextCtrl::GTKSetEditable()
{
	gboolean editable = !HasFlag(wxTE_READONLY);
	gtk_editable_set_editable(GTK_EDITABLE(m_text), editable);
}


void wxIconTextCtrl::GTKSetVisibility()
{
	gtk_entry_set_visibility(GTK_ENTRY(m_text), !HasFlag(wxTE_PASSWORD));
}


void wxIconTextCtrl::GTKSetActivatesDefault()
{
	gtk_entry_set_activates_default(GTK_ENTRY(m_text),
			!HasFlag(wxTE_PROCESS_ENTER));
}


void wxIconTextCtrl::GTKSetJustification()
{
	gfloat align;
	if (HasFlag(wxTE_RIGHT))
		align = 1.0;
	else if (HasFlag(wxTE_CENTRE))
		align = 0.5;
	else
		// single line
		align = 0.0;

	gtk_entry_set_alignment(GTK_ENTRY(m_text), align);
}


void wxIconTextCtrl::SetWindowStyleFlag(long style)
{
	long styleOld = GetWindowStyleFlag();

	wxWindow::SetWindowStyleFlag(style);

	if ((style & wxTE_READONLY) != (styleOld & wxTE_READONLY))
		GTKSetEditable();

	if ((style & wxTE_PASSWORD) != (styleOld & wxTE_PASSWORD))
		GTKSetVisibility();

	if ((style & wxTE_PROCESS_ENTER) != (styleOld & wxTE_PROCESS_ENTER))
		GTKSetActivatesDefault();

	static const long flagsAlign = wxTE_LEFT | wxTE_CENTRE | wxTE_RIGHT;
	if ((style & flagsAlign) != (styleOld & flagsAlign))
		GTKSetJustification();
}

// ----------------------------------------------------------------------------
// control value
// ----------------------------------------------------------------------------

void wxIconTextCtrl::DoSetValue(const wxString &value, int flags)
{
	wxCHECK_RET( m_text != NULL, wxT("invalid text ctrl"));

	wxTextEntry::DoSetValue(value, flags);
}


bool wxIconTextCtrl::Enable(bool enable)
{
	bool returnValue = wxWindowBase::Enable(enable);

	if (returnValue)
	{
		gtk_widget_set_sensitive(GTK_WIDGET(m_text), enable);
		//SetCursor(enable? wxCursor(wxCURSOR_IBEAM) : wxCursor());
	}

	return returnValue;
}

// wxGTK-specific: called recursively by Enable,
// to give widgets an opportunity to correct their colours after they
// have been changed by Enable
void wxIconTextCtrl::OnEnabled(bool WXUNUSED(enable))
{
	// If we have a custom background colour, we use this colour in both
	// disabled and enabled mode, or we end up with a different colour under the
	// text.
	wxColour oldColour = GetBackgroundColour();
	if (oldColour.IsOk())
	{
		// Need to set twice or it'll optimize the useful stuff out
		if (oldColour == *wxWHITE)
			SetBackgroundColour(*wxBLACK);
		else
			SetBackgroundColour(*wxWHITE);
		SetBackgroundColour(oldColour);
	}
}

void wxIconTextCtrl::SetIcon(wxTextCtrlIconPosition iconPosition,
		const wxBitmap & bitmap)
{
	SetIconBitmap(iconPosition, bitmap);

	ShowIcon(iconPosition);
}


void wxIconTextCtrl::EnableIcon(wxTextCtrlIconPosition iconPosition,
		bool enabled)
{
	GtkEntryIconPosition icon_pos = (
			iconPosition == wxTC_ICON_PRIMARY ?
					GTK_ENTRY_ICON_PRIMARY : GTK_ENTRY_ICON_SECONDARY);

	gtk_entry_set_icon_sensitive(m_text, icon_pos, enabled);
}


void wxIconTextCtrl::ShowIcon(wxTextCtrlIconPosition iconPosition, bool visible)
{
	const wxBitmap & bitmap = GetIconBitmap(iconPosition);
	GtkEntryIconPosition icon_pos = (
			iconPosition == wxTC_ICON_PRIMARY ?
					GTK_ENTRY_ICON_PRIMARY : GTK_ENTRY_ICON_SECONDARY);

	if (visible && bitmap.IsOk())
	{
		gtk_entry_set_icon_from_pixbuf(m_text, icon_pos, bitmap.GetPixbuf());
	}
	else
	{
		gtk_entry_set_icon_from_pixbuf(m_text, icon_pos, NULL);
	}
}

void wxIconTextCtrl::SetIconTooltip(wxTextCtrlIconPosition iconPosition,
		const wxString & tooltip)
{
	GtkEntryIconPosition icon_pos = (
			iconPosition == wxTC_ICON_PRIMARY ?
					GTK_ENTRY_ICON_PRIMARY : GTK_ENTRY_ICON_SECONDARY);
	std::string str = tooltip.ToStdString();

	gtk_entry_set_icon_tooltip_text(m_text, icon_pos, str.c_str());
}

#endif // wxUSE_TEXTCTRL
