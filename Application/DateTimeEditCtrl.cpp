////////////////////////////////////////////////////////////////////////////
// File:	DateTimeEditCtrl.cpp
// Version:	3.7
// Created:	21-Jan-2008
//
// Author:	Paul S. Vickery
// E-mail:	paul@vickeryhome.freeserve.co.uk
//
// Class to provide an editable Date picker control. Based on CDateTimeCtrl.
//
// You are free to use or modify this code, with no restrictions, other than
// you continue to acknowledge me as the original author in this source code,
// or any code derived from it.
//
// If you use this code, or use it as a base for your own code, it would be 
// nice to hear from you simply so I know it's not been a waste of time!
//
// Copyright (c) 2003-2008 Paul S. Vickery
//
////////////////////////////////////////////////////////////////////////////
// Version History:
//
// Version 3.7 - 21-Jan-2008
// =========================
//
// - updated to work correctly on Vista
//
// Version 3.6.1 - 20-Apr-2007
// ===========================
//
// - fixed missing and incorrect NM_KILLFOCUS notifications
// - changed to compile correctly in VC7 (VS2003) and VC8 (VS2005)
// - added fix to control being shown if hidden in initialising of parent
//
// Version 3.6 - 22-Dec-2005
// =========================
//
// - added 'read-only' state, to allow a semi-disabled state
// - updated to recognise XP theme changes, and re-draw accordingly
// - fixed bug where calendar could be shown in non-editable mode on F4, and 
//   date could be changed by using up/down keys
// - added support for a 'disabled' image to be used when the control is 
//   disabled or read-only
// - fixed bug where creating control with ES_READONLY style failed
// - nested button/edit/calendar/xp-style classes so they don't appear in 
//   the top level of the ClassView
//
// Version 3.5 - 04-Apr-2005
// =========================
// - updated to support XP-styling
// - changed to grey-out edit if disabled (suggested by Hans-Georg Ulrich)
// - added fix to enable compilation with VS.NET (thanks to Mark Harmon)
//
// Version 3.4 - 09-Jul-2004
// =========================
// - Fixed bug where dismissing the month menu in the calendar control by 
//   clicking outside of the calendar area then prevents the calendar being 
//   dismissed without first clicking back on the calendar control.
//   (Reported by winkle.)
// - Fixed assertion failures on re-creation of the control when two or more 
//   instances of the control are on a dialog. (Reported by pimOOsse and Rick 
//   Austin.)
//
// Version 3.3 - 09-Jul-2003
// =========================
// Updated to support Unicode.
//
// Version 3.2 - 15-Apr-2003
// =========================
// - Extended control to accept the DTM_SETRANGE and DTM_GETRANGE messages.
// - Fixed incorrect implementation of DTS_RIGHTALIGN.
// - Added facility to use a bitmap for the button instead of a down arrow
// - WM_NOTIFY notifications now passed to parent window from date control's 
//   children
// - Fixed bug where clicking on current (circled) day when edit control is 
//   empty closed the calendar did not put the selected day in the edit control
//
// Version 3.1 - 20-Jan-2003
// =========================
// - Fixed bug where, if new date text is set in the DTN_DATETIMECHANGE handler 
//   (for instance to constrain the date within some boundary), and the user 
//   selects a date which is 'out-of-bounds', and the calendar closes, the 
//   selected date is copied to the edit control, overwriting the 'fixed' date.
// 
// Version 3 - 17-Jan-2003
// =======================
// - Fixed bug where a call to Get/SetWindowText, SetFont, or any function 
//   which resulted in a sending of a DTM_XXX message caused an assertion the 
//   first time round, if called from the OnInitDialog of a parent dialog, or 
//   equivalent.
// 
// Version 2 - 07-Jan-2003
// =======================
// - Edit control notifications (eg EN_CHANGE) now get sent to date control's 
//   parent window
// - Added features as suggested by Marc Clifton on CodeProject:
//   - Added function to validate a date string (IsValidDate)
//   - Added function to only allow valid chars to be typed into the edit control.
//     Also a function to set the valid characters. The default valid characters 
//     are 0-9 and the current user's locale's date separator. If the user changes 
//     the locale settings then the control will automatically pick this up and 
//     use the new separator.
//   - Added ability to use up/down keys to edit portions of the date text
// 
// Version 1 - 03-Jan-2003
// =======================
// Initial version
// 
////////////////////////////////////////////////////////////////////////////
// PLEASE LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DateTimeEditCtrl.h"

#pragma warning (push, 3)
#include <string>
#pragma warning (pop)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const UINT ID_EDIT = 1;
static const UINT ID_BUTTON = 2;
static const UINT ID_CALENDAR = 3;
static const UINT ID_DROPWND = 4;

#define CALENDAR_AS_POPUP 1

// the arrow button is 16 pixels wide
static const UINT CX_BTN = 16;

static CDateTimeEditCtrl::CDateTimeEditXPStyle s_xpstyle;

// recreate the edit control by copying styles etc, and text 
// and applying them to a newly created control
static BOOL RecreateEditCtrl(CEdit* pEdit, LPVOID lpParam = NULL)
{
  if (pEdit == NULL)
    return FALSE;
  if (pEdit->GetSafeHwnd() == NULL)
    return FALSE;

  CWnd* pParent = pEdit->GetParent();
  if (pParent == NULL)
    return FALSE;

  // get current attributes
  DWORD dwStyle = pEdit->GetStyle();
  DWORD dwStyleEx = pEdit->GetExStyle();
  CRect rc;
  pEdit->GetWindowRect(&rc);
  pParent->ScreenToClient(&rc);	// map to client co-ords
  UINT nID = pEdit->GetDlgCtrlID();
  CFont* pFont = pEdit->GetFont();
  CWnd* pWndAfter = pEdit->GetNextWindow(GW_HWNDPREV);
  CString sText;
  pEdit->GetWindowText(sText);

  pEdit->DestroyWindow();
  if (! pEdit->CreateEx(dwStyleEx, _T("EDIT"), sText, dwStyle, rc, pParent, nID, lpParam))
    return FALSE;
  pEdit->SetFont(pFont);

  // position correctly in z-order
  pEdit->SetWindowPos(pWndAfter == NULL ? &CWnd::wndBottom : pWndAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

  return TRUE;
}

// returns whether we're running on Vista (Windows 6) or later
static BOOL IsVistaOrLater()
{
  static BOOL bGot = FALSE;
  static BOOL bVista = FALSE;
  if (bGot)
    return bVista;
  OSVERSIONINFO osvi = { 0 };
  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  //if (GetVersionEx(&osvi))
    bGot = TRUE;
  return (bGot && (bVista = (osvi.dwMajorVersion >= 6)));
}

/////////////////////////////////////////////////////////////////////////////
// CDateTimeEditCtrlButton

BEGIN_MESSAGE_MAP(CDateTimeEditCtrlButton, CButton)
	//{{AFX_MSG_MAP(CDateTimeEditCtrlButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateTimeEditCtrlButton message handlers

void CDateTimeEditCtrlButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
  CButton::OnLButtonUp(nFlags, point);
  // set the focus back to the parent, and stop it looking like the default button
  if ((GetStyle() & 0xf) != BS_OWNERDRAW)
    ModifyStyle(0xf, 0);
  if (! m_bNonEditable && m_bRestoreFocus && m_pWndLastFocus != NULL && ::IsWindow(m_pWndLastFocus->m_hWnd))
    m_pWndLastFocus->SetFocus();
  else
    GetParent()->SetFocus();
}

void CDateTimeEditCtrlButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
  if (! m_bNonEditable && m_bRestoreFocus)
    m_pWndLastFocus = CWnd::GetFocus();
  else
    m_pWndLastFocus = NULL;
  CButton::OnLButtonDown(nFlags, point);
  // stop it looking like the default button
  if ((GetStyle() & 0xf) != BS_OWNERDRAW)
    ModifyStyle(0xf, 0);
}

void CDateTimeEditCtrlButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  CButton::OnKeyDown(nChar, nRepCnt, nFlags);

  if (nChar == VK_F4)
    // hide or show cal ctrl, by simulating a button click
    GetParent()->PostMessage(WM_COMMAND, MAKEWPARAM(ID_BUTTON, BN_CLICKED), (LPARAM)GetNextWindow()->GetSafeHwnd());
}

BOOL CDateTimeEditCtrlButton::PreTranslateMessage(MSG* pMsg) 
{
  if (pMsg->message == WM_KEYDOWN && 
	(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
  {
    // destroy calendar
    if (GetParent()->SendMessage(DTCEM_DESTROY_CALENDAR, (pMsg->wParam == VK_ESCAPE)))
      return TRUE;
  }
  return CButton::PreTranslateMessage(pMsg);
}

BOOL CDateTimeEditCtrlButton::OnEraseBkgnd(CDC* pDC) 
{
  if (s_xpstyle.IsAppXPStyled())
  {
    // we want to let the default button show through
    //pDC->SelectStockObject(NULL_BRUSH);
    //return TRUE;
  }
  return CButton::OnEraseBkgnd(pDC);
}

#ifndef CP_DROPDOWNBUTTON
#define CP_DROPDOWNBUTTON 1
#define CBXS_NORMAL 1
#define CBXS_HOT 2
#define CBXS_PRESSED 3
#define CBXS_DISABLED 4
#endif // ! CP_DROPDOWNBUTTON

void CDateTimeEditCtrlButton::DrawItem(LPDRAWITEMSTRUCT lpdis) 
{
  // if we're using XP styles, then draw the button as a combobox 
  // drop-down button, using the appropriate theme
  // then, if we are using a bitmap for the button, draw this on top
  _ASSERTE(s_xpstyle.IsAppXPStyled());
  _ASSERTE(! IsVistaOrLater());
  HTHEME hTheme = s_xpstyle.OpenThemeData(m_hWnd, L"COMBOBOX");
  ASSERT(hTheme);
  VERIFY(s_xpstyle.DrawThemeBackground(hTheme, lpdis->hDC, CP_DROPDOWNBUTTON, 
    ((GetState() & 0x0004) == BST_PUSHED) ? CBXS_PRESSED : 
    IsWindowEnabled() ? CBXS_NORMAL : GetStyle() & WS_DISABLED ? CBXS_DISABLED : CBXS_NORMAL, &lpdis->rcItem, NULL) == S_OK);
  s_xpstyle.CloseThemeData(hTheme);

  if (GetBitmap() != NULL)
  {
    // draw the bitmap in the centre of the button area
    CDC* pDC = CDC::FromHandle(lpdis->hDC);
    _ASSERTE(pDC != NULL);
    CDC dc;
    dc.CreateCompatibleDC(pDC);
    CBitmap* pBmp = CBitmap::FromHandle(GetBitmap());
    _ASSERTE(pBmp != NULL);
    dc.SelectObject(pBmp);
    BITMAP bmp;
    pBmp->GetBitmap(&bmp);
    CRect rcClient;
    GetClientRect(rcClient);
    rcClient.left = rcClient.right - CX_BTN;
    CPoint ptOrg = rcClient.CenterPoint();
    ptOrg.Offset(-bmp.bmWidth / 2, -bmp.bmHeight / 2);
    pDC->BitBlt(ptOrg.x, ptOrg.y, 16, 16, &dc, 0, 0, SRCCOPY);
  }
}

/////////////////////////////////////////////////////////////////////////////
// CDateTimeEditCtrlEditCtrl

BEGIN_MESSAGE_MAP(CDateTimeEditCtrlEditCtrl, CEdit)
	//{{AFX_MSG_MAP(CDateTimeEditCtrlEditCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_SETCURSOR()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_SETTINGCHANGE()
	ON_WM_NCCALCSIZE()
	ON_WM_STYLECHANGED()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateTimeEditCtrlEditCtrl message handlers

static TCHAR s_chDateSep = _T('/');
static TCHAR s_szDateFormat[81] = { _T('\0') };

CDateTimeEditCtrlEditCtrl::CDateTimeEditCtrlEditCtrl()
{
  m_bNonEditable = FALSE;
  m_bValidCharsOnly = FALSE;
  m_bAllowUpDownKeys = TRUE;

  int nLen = ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDATE, &s_chDateSep, 0);
  if (nLen != 0)
    ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDATE, &s_chDateSep, nLen);
  nLen = ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SSHORTDATE, s_szDateFormat, 0);
  if (nLen != 0)
    ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SSHORTDATE, s_szDateFormat, nLen);
}

UINT CDateTimeEditCtrlEditCtrl::OnGetDlgCode() 
{
  if (m_bNonEditable)
    return DLGC_STATIC;
  return CEdit::OnGetDlgCode();
}

BOOL CDateTimeEditCtrlEditCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
  // if we are non-editable, we want the cursor to look like an arrow
  // not like an I-bar
  if (m_bNonEditable && nHitTest == HTCLIENT)
  {
    AfxGetApp()->LoadStandardCursor(IDC_ARROW);
    return TRUE;
  }
  return CEdit::OnSetCursor(pWnd, nHitTest, message);
}

HBRUSH CDateTimeEditCtrlEditCtrl::CtlColor(CDC* pDC, UINT nCtlColor) 
{
  // if we are non-editable, we want the edit to be readonly, but look
  // like editable (ie with white (standard 'window') background)
  if (m_bNonEditable && IsWindowEnabled())
  {
    pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
    return GetSysColorBrush(COLOR_WINDOW);
  }
  return NULL;
}

BOOL CDateTimeEditCtrlEditCtrl::PreTranslateMessage(MSG* pMsg) 
{
  if (pMsg->message == WM_KEYDOWN && 
	(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
  {
    if (s_xpstyle.IsAppXPStyled() && IsVistaOrLater())
    {
      // pass to parent
      CDateTimeCtrl* pCtrl = DYNAMIC_DOWNCAST(CDateTimeCtrl, GetParent());
      if (pCtrl != NULL && pCtrl->GetMonthCalCtrl() != NULL)
      {
	pCtrl->SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
	return TRUE;
      }
    }
    else
    {
      // destroy calendar
      if (GetParent()->SendMessage(DTCEM_DESTROY_CALENDAR, (pMsg->wParam == VK_ESCAPE)))
	return TRUE;
    }
  }
  return CEdit::PreTranslateMessage(pMsg);
}

#ifdef _UNICODE
typedef std::wstring _tstring;
#else
typedef std::string _tstring;
#endif

int ReverseFindOneOf(const CString& sString, LPCTSTR lpszCharSet)
{
  _tstring s = sString;
  return (int)s.find_last_of(lpszCharSet);
}

int FindOneOf(const CString& sString, LPCTSTR lpszCharSet, int nStart)
{
  _tstring s = sString;
  return (int)s.find_first_of(lpszCharSet, nStart);
}

void CDateTimeEditCtrlEditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  if (m_bAllowUpDownKeys && (nChar == VK_UP || nChar == VK_DOWN) && (! (GetStyle() & ES_READONLY) || m_bNonEditable))
  {
    BOOL bInc = (nChar == VK_UP);
    // increment part of date in which cursor is positioned
    int nStart, nEnd;
    GetSel(nStart, nEnd);
    CString sText;
    GetWindowText(sText);
    CString sSeps(s_chDateSep);

    // find portion of text we're in, and select
    // between two separators
    if (! m_sValidChars.IsEmpty())
    {
      sSeps = m_sValidChars;
      for (TCHAR chRemove = _T('0'); chRemove <= _T('9'); chRemove++)
	sSeps.Remove(chRemove);
      // sSeps just contains the separators now
    }

    int nSep2 = FindOneOf(sText, sSeps, nEnd);
    CString sStart(sText);
    if (nSep2 >= 0)
      sStart = sText.Left(nSep2);
    int nPos = ReverseFindOneOf(sStart, sSeps);

    BOOL bLeftPos = TRUE;
    BOOL bMidPos = FALSE;
    int nSep1 = 0;
    if (nPos >= 0)
    {
      // mid position
      if (nSep2 >= 0)
      {
	bLeftPos = FALSE;
	bMidPos = TRUE;
      }
      nSep1 = nPos + 1;
    }
    if (nSep2 < 0)
    {
      // right-most portion
      nSep2 = sText.GetLength();
      bLeftPos = FALSE;
    }

    CString sDateFormat(s_szDateFormat);
    CString sPortion;

    int nFirstSep = sDateFormat.FindOneOf(sSeps);
    // find out which part of the format we are in
    if (bLeftPos)
    {
      // get bit before first sep
      if (nFirstSep > 0)
	sPortion = sDateFormat.Left(nFirstSep);
    }
    else if (bMidPos)
    {
      // get bit after first sep, and before last
      if (nFirstSep > 0)
      {
	nFirstSep++;
	int nPos = FindOneOf(sDateFormat, sSeps, nFirstSep);
	if (nPos >= nFirstSep)
	  sPortion = sDateFormat.Mid(nFirstSep, nPos - nFirstSep);
      }
    }
    else
    {
      // get bit after last sep
      int nPos = ReverseFindOneOf(sDateFormat, sSeps);
      if (nPos >= 0)
	sPortion = sDateFormat.Right(sDateFormat.GetLength() - (nPos+1));
    }

    // select new portion
    SetSel(nSep1, nSep2);
    CString sVal(sStart.GetLength() > nSep1 ? sStart.Mid(nSep1) : sStart);

    LPTSTR lpszFormat = _T("%02d");
    int nVal = _ttoi(sVal);
    int nMin = 1;
    int nMax = 12;

    // make sure the number is within bounds depending on portion
    if (! sPortion.IsEmpty())
    {
      int nLen = sPortion.GetLength();
      if (nLen != 2)
	lpszFormat = _T("%0d");
      switch (sPortion.GetAt(0))
      {
      case _T('d'):	// day
      case _T('D'):	// day
	nMax = 31;
	break;

      case _T('M'):	// month
      case _T('m'):	// month
	nMax = 12;
	break;

      case _T('y'):	// year
      case _T('Y'):	// year
	{
	  nMin = 0;
	  if (nLen == 1)
	    nMax = 9;
	  else if (nLen == 2)
	    nMax = 99;
	  else if (nLen == 4)
	  {
	    lpszFormat = _T("%04d");
	    nMax = 9999;
	  }
	}
	break;
      };
    }

    if (bInc)
      nVal++;
    else
      nVal--;

    // wrap values
    if (nVal < nMin)
      nVal = nMax;
    else if (nVal > nMax)
      nVal = nMin;

    sVal.Format(lpszFormat, nVal);

    // replace and re-select new portion
    ReplaceSel(sVal);

    BOOL bInvalid = FALSE;

    // if this takes the value out of range, correct it
    CDateTimeEditCtrl* pCtrl = DYNAMIC_DOWNCAST(CDateTimeEditCtrl, GetParent());
    if (pCtrl != NULL)
    {
      CString sTextNew;
      GetWindowText(sTextNew);
      COleDateTime dateMin, dateMax;
      DWORD dwFlags = pCtrl->GetRange(&dateMin, &dateMax);
      COleDateTime date;
      date.ParseDateTime(sTextNew);
      if (dwFlags & GDTR_MIN && date < dateMin)
      {
	bInvalid = TRUE;
	date = dateMin;
      }
      else if (dwFlags & GDTR_MAX && date > dateMax)
      {
	bInvalid = TRUE;
	date = dateMax;
      }
      sText = date.Format(VAR_DATEVALUEONLY/*s_szDateFormat*/);
    }

    if (bInvalid)
    {
      SetWindowText(sText);
      SetSel(nStart, nEnd);
    }
    else
    {
      nSep2 = nSep1 + sVal.GetLength();
      SetSel(nSep1, nSep2);
    }

    SendDateTimeChange();

    return;
  }

  CEdit::OnKeyDown(nChar, nRepCnt, nFlags);

  if (nChar == VK_F4 && (! (GetStyle() & ES_READONLY) || m_bNonEditable))
  {
    if (! s_xpstyle.IsAppXPStyled() || ! IsVistaOrLater())
      // hide or show cal ctrl, by simulating a button click
      GetParent()->PostMessage(WM_COMMAND, MAKEWPARAM(ID_BUTTON, BN_CLICKED), (LPARAM)GetNextWindow()->GetSafeHwnd());
    else
    {
      // just pass to date time ctrl
      CDateTimeEditCtrl* pCtrl = DYNAMIC_DOWNCAST(CDateTimeEditCtrl, GetParent());
      const MSG* pMsg = GetCurrentMessage();
      if (pCtrl != NULL && pMsg != NULL)
	pCtrl->PostMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
    }
  }
}

void CDateTimeEditCtrlEditCtrl::SendDateTimeChange()
{
  CDateTimeEditCtrl* pCtrl = DYNAMIC_DOWNCAST(CDateTimeEditCtrl, GetParent());
  if (pCtrl != NULL)
  {
    CWnd* pParent = pCtrl->GetParent();
    if (pParent != NULL)
    {
      COleDateTime date;
      CString sText;
      GetWindowText(sText);
      date.ParseDateTime(sText);
      SYSTEMTIME st = { '\0' };
      date.GetAsSystemTime(st);
      // tell parent about it (DTN_DATETIMECHANGE)
      NMDATETIMECHANGE nmdtc;
      nmdtc.nmhdr.code = DTN_DATETIMECHANGE;
      nmdtc.nmhdr.hwndFrom = pCtrl->GetSafeHwnd();
      nmdtc.nmhdr.idFrom = pCtrl->GetDlgCtrlID();
      nmdtc.dwFlags = GDT_VALID;
      nmdtc.st = st;
      pParent->SendMessage(WM_NOTIFY, (WPARAM)nmdtc.nmhdr.idFrom, (LPARAM)&nmdtc);
    }
  }
}

// set whether the user can only enter chars that are valid
void CDateTimeEditCtrlEditCtrl::SetValidCharsOnly(BOOL bValidCharsOnly/*=TRUE*/)
{
  m_bValidCharsOnly = bValidCharsOnly;
}

// returns whether the user can only enter valid chars into the edit control
BOOL CDateTimeEditCtrlEditCtrl::GetValidCharsOnly()
{
  return m_bValidCharsOnly;
}

// sets the chars that are valid for the user to type into the edit control
// if NULL is specified, then the default chars are used (0-9 and current 
// user's locale's date separator). If the user changes the locale settings 
// then the control will automatically pick this up and use the new separator.
void CDateTimeEditCtrlEditCtrl::SetValidChars(LPCTSTR lpszValidChars/*=NULL*/)
{
  m_sValidChars = lpszValidChars;
}

// returns the chars that are valid for the user to type into the edit control
CString CDateTimeEditCtrlEditCtrl::GetValidChars()
{
  return m_sValidChars;
}

void CDateTimeEditCtrlEditCtrl::SetAllowUpDownKeys(BOOL bAllow/*=TRUE*/)
{
  m_bAllowUpDownKeys = bAllow;
}

BOOL CDateTimeEditCtrlEditCtrl::GetAllowUpDownKeys()
{
  return m_bAllowUpDownKeys;
}

void CDateTimeEditCtrlEditCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  if (m_bValidCharsOnly && nChar >= 0x20)
  {
    BOOL bValid = TRUE;
    if (m_sValidChars.IsEmpty())
    {
      // only allow numeric or date separator
      if (nChar >= 0x20 && (nChar < _T('0') || nChar > _T('9')) && nChar != (UINT)s_chDateSep)
	bValid = FALSE;
    }
    else
    {
      // see if the char is in the valid chars list
      if (m_sValidChars.Find((TCHAR)nChar) == -1)
	bValid = FALSE;
    }
    if (! bValid)
    {
      // don't allow it
      MessageBeep(MB_ICONEXCLAMATION);
      return;
    }
  }
  CEdit::OnChar(nChar, nRepCnt, nFlags);

  // tell the parent dialog of the change
  SendDateTimeChange();
}

void CDateTimeEditCtrlEditCtrl::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
  if (lpszSection != NULL && lstrcmpi(lpszSection, _T("intl")) == 0)
  {
    int nLen = ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDATE, &s_chDateSep, 0);
    if (nLen != 0)
      ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDATE, &s_chDateSep, nLen);
  }
  CEdit::OnSettingChange(uFlags, lpszSection);
}

void CDateTimeEditCtrlEditCtrl::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
  _ASSERTE(lpStyleStruct != NULL);

  if (nStyleType == GWL_STYLE)
  {
    // see if we've changed the read-only state, in which case 
    // we need to re-create ourself in order for the style to take effect
    if ((lpStyleStruct->styleOld & ES_READONLY && ! (lpStyleStruct->styleNew & ES_READONLY)) || 
	(! (lpStyleStruct->styleOld & ES_READONLY) && lpStyleStruct->styleNew & ES_READONLY))
      RecreateEditCtrl(this);
  }
}

void CDateTimeEditCtrlEditCtrl::OnKillFocus(CWnd* pNewWnd) 
{
  CDateTimeEditCtrl* pDateTimeEditCtrl = DYNAMIC_DOWNCAST(CDateTimeEditCtrl, GetParent());
  if (pDateTimeEditCtrl != NULL && pDateTimeEditCtrl != pNewWnd && pDateTimeEditCtrl->GetMonthCalCtrl() != pNewWnd)
  {
    // send notification to parent of date time ctrl, unless the focus is moving to the date time ctrl or calendar
    CWnd* pParent = pDateTimeEditCtrl->GetParent();
    if (pParent != NULL)
    {
      NMHDR nmhdr;
      nmhdr.hwndFrom = pDateTimeEditCtrl->m_hWnd;
      nmhdr.idFrom = pDateTimeEditCtrl->GetDlgCtrlID();
      nmhdr.code = NM_KILLFOCUS;
      pParent->SendMessage(WM_NOTIFY, (WPARAM)nmhdr.idFrom, (LPARAM)&nmhdr);
    }
  }
  CEdit::OnKillFocus(pNewWnd);
}

/////////////////////////////////////////////////////////////////////////////
// CDateTimeEditCtrlMonthCalCtrl

CDateTimeEditCtrlMonthCalCtrl::CDateTimeEditCtrlMonthCalCtrl()
{
  m_nIgnoreNextMessage = 0;
}

CDateTimeEditCtrlMonthCalCtrl::~CDateTimeEditCtrlMonthCalCtrl()
{
}

BEGIN_MESSAGE_MAP(CDateTimeEditCtrlMonthCalCtrl, CMonthCalCtrl)
	//{{AFX_MSG_MAP(CDateTimeEditCtrlMonthCalCtrl)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateTimeEditCtrlMonthCalCtrl message handlers

LRESULT CDateTimeEditCtrlMonthCalCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
  if (m_nIgnoreNextMessage != message)
  {
    if (message == WM_LBUTTONDOWN || 
	message == WM_MBUTTONDOWN || 
	message == WM_RBUTTONDOWN)
    {
      // Is mouse within control
      CPoint point(lParam);
      CRect rcClient;
      GetClientRect(rcClient);
      if (! rcClient.PtInRect(point))
      {
	ReleaseCapture();
	GetOwner()->PostMessage(DTCEM_DESTROY_CALENDAR);
      }
      else
	SetCapture();
    }
    else if (message == WM_LBUTTONUP || 
	     message == WM_MBUTTONUP || 
	     message == WM_RBUTTONUP)
    {
      CMonthCalCtrl::WindowProc(message, wParam, lParam);
      // we seem to lose capture on Xbuttonup, which stops us catching
      // out-of-rect messages after changing, for instance, the month
      // so we need to re-capture messages. However, if the Xbuttondown
      // was out-of-rect, then we won't exist by this point, so test validity
      if (::IsWindow(m_hWnd))
	SetCapture();
      return 0;
    }
    else if (message == WM_PARENTNOTIFY)
    {
      if (LOWORD(wParam) == WM_DESTROY)
	// just destroyed the 'year' edit/updown, but this makes us lose capture
	SetCapture();
    }
    else if (message == WM_MENUSELECT)
    {
      if (HIWORD(wParam) == 0xffff && lParam == 0)
      {
	// the month menu has been closed, so re-take capture
	SetCapture();
	// if the menu was closed by clicking outside of the client area, 
	// then by retaining the capture the mouse event will close the 
	// calendar, which is not what we want, so we need to ignore the 
	// next click of that mouse button in our code above
	m_nIgnoreNextMessage = 0;
	if (GetAsyncKeyState(MK_LBUTTON) & 0x80000000)
	  m_nIgnoreNextMessage = WM_LBUTTONDOWN;
	else if (GetAsyncKeyState(MK_MBUTTON) & 0x80000000)
	  m_nIgnoreNextMessage = WM_MBUTTONDOWN;
	else if (GetAsyncKeyState(MK_RBUTTON) & 0x80000000)
	  m_nIgnoreNextMessage = WM_RBUTTONDOWN;
      }
    }
  }
  if (message == m_nIgnoreNextMessage)
    m_nIgnoreNextMessage = 0; // don't ignore it again
  return CMonthCalCtrl::WindowProc(message, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CDateTimeEditCtrlCalendarWnd

CDateTimeEditCtrlCalendarWnd::CDateTimeEditCtrlCalendarWnd(CWnd* pComboParent, DWORD dwMCStyle/*=0*/)
{
  m_pComboParent = pComboParent;
  m_dwMCStyle = dwMCStyle;
  m_pCalendar = NULL;
}

CDateTimeEditCtrlCalendarWnd::~CDateTimeEditCtrlCalendarWnd()
{
  delete m_pCalendar;
}

BEGIN_MESSAGE_MAP(CDateTimeEditCtrlCalendarWnd, CWnd)
	//{{AFX_MSG_MAP(CDateTimeEditCtrlCalendarWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ACTIVATEAPP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateTimeEditCtrlCalendarWnd message handlers

BOOL CDateTimeEditCtrlCalendarWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
  return CWnd::Create(0, 0, dwStyle, rect, pParentWnd, nID, pContext);
}

int CDateTimeEditCtrlCalendarWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  // hide the taskbar button
  if (!(lpCreateStruct->style & WS_POPUP))
    ModifyStyleEx(0, WS_EX_TOOLWINDOW);

  // Create calendar control
  m_pCalendar = new CDateTimeEditCtrlMonthCalCtrl;
  DWORD dwStyle = m_dwMCStyle & ~(WS_VISIBLE);
  VERIFY(m_pCalendar->Create(dwStyle | WS_CHILD, CPoint(0, 0), this, ID_CALENDAR));
  m_pCalendar->SizeMinReq();
  m_pCalendar->SetOwner(m_pComboParent);

  // size self to fit calendar
  // and make us top-most, so we're seen
  CRect rcCal;
  m_pCalendar->GetWindowRect(&rcCal);
  CalcWindowRect(&rcCal);
  SetWindowPos(&wndTopMost, 0, 0, rcCal.Width(), rcCal.Height(), SWP_NOMOVE | SWP_NOACTIVATE);

  m_pCalendar->ShowWindow(SW_SHOW);

  // the calendar needs to catch all mouse messages, so it can respond to
  // changes in the visible month etc
  m_pCalendar->SetCapture();

  return 0;
}

BOOL CDateTimeEditCtrlCalendarWnd::DestroyWindow() 
{
  ReleaseCapture();
  m_pCalendar->DestroyWindow();
  return CWnd::DestroyWindow();
}

#if _MFC_VER >= 0x0700
void CDateTimeEditCtrlCalendarWnd::OnActivateApp(BOOL bActive, DWORD dwThreadID) 
#else
void CDateTimeEditCtrlCalendarWnd::OnActivateApp(BOOL bActive, HTASK hTask) 
#endif
{
#if _MFC_VER >= 0x0700
  CWnd::OnActivateApp(bActive, dwThreadID);
#else
  CWnd::OnActivateApp(bActive, hTask);
#endif
  if (! bActive && m_pComboParent != NULL)
    m_pComboParent->PostMessage(DTCEM_DESTROY_CALENDAR, TRUE);
}

BOOL CDateTimeEditCtrlCalendarWnd::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
  LPNMHDR lpnmhdr = (LPNMHDR)lParam;
  if (lpnmhdr != NULL && m_pComboParent != NULL && 
	    (lpnmhdr->code == MCN_SELECT || lpnmhdr->code == MCN_SELCHANGE))
  {
    *pResult = m_pComboParent->SendMessage(WM_NOTIFY, wParam, lParam);
    return TRUE;
  }
  return CWnd::OnNotify(wParam, lParam, pResult);
}

/////////////////////////////////////////////////////////////////////////////
// CDateTimeEditCtrl

#if _AFXDLL
IMPLEMENT_DYNAMIC(CDateTimeCtrl, CWnd)	// missing from MFC sources
#endif

IMPLEMENT_DYNAMIC(CDateTimeEditCtrl, CDateTimeCtrl)

CDateTimeEditCtrl::CDateTimeEditCtrl()
{
  m_pEdit = NULL;
  m_pBtn = NULL;
  m_nBtnImageID = 0;
  m_nBtnImageDisabledID = 0;
  m_bNonEditable = FALSE;
  m_bReadOnly = FALSE;
  m_bDisabled = FALSE;
  m_bRightAlign = FALSE;
  m_pCalWnd = NULL;
  m_bInCreate = FALSE;
  m_hMCFont = NULL;
  // initial values of cal ctrl colours
  m_acrMonthCal[0] = (COLORREF)-1;		// the background color (between months)
  m_acrMonthCal[1] = GetSysColor(COLOR_BTNTEXT);// the dates
  m_acrMonthCal[2] = GetSysColor(COLOR_ACTIVECAPTION);	// background of the title
  m_acrMonthCal[3] = (COLORREF)-1;		// title text
  m_acrMonthCal[4] = (COLORREF)-1;		// background within the month cal
  m_acrMonthCal[5] = GetSysColor(COLOR_3DSHADOW);// the text color of header & trailing days
  m_pDateMin = NULL;
  m_pDateMax = NULL;
}

CDateTimeEditCtrl::~CDateTimeEditCtrl()
{
  delete m_pEdit;
  delete m_pBtn;
  delete m_pCalWnd;
  delete m_pDateMin;
  delete m_pDateMax;
  ReleaseCapture();
}

BEGIN_MESSAGE_MAP(CDateTimeEditCtrl, CDateTimeCtrl)
	//{{AFX_MSG_MAP(CDateTimeEditCtrl)
	ON_WM_CREATE()
	ON_WM_ENABLE()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_CANCELMODE()
	ON_WM_NCCALCSIZE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT_EX(NM_KILLFOCUS, OnKillfocus)
	ON_MESSAGE(DTCEM_DESTROY_CALENDAR, OnDestroyCalendar)
	ON_WM_STYLECHANGING()
	ON_MESSAGE(DTCEM_RECREATE, OnRecreate)
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateTimeEditCtrl message handlers

LONG CDateTimeEditCtrl::OnDestroyCalendar(WPARAM wParam, LPARAM lParam)
{
  // wParam is the key that this is in response to, if applicable
  return DestroyCalendar((BOOL)wParam);
}

BOOL CDateTimeEditCtrl::Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID)
{
  m_bInCreate = TRUE;
  if (! CWnd::Create(DATETIMEPICK_CLASS, NULL, dwStyle, rect, pParentWnd, nID))
    return FALSE;

  return TRUE;
}

int CDateTimeEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  m_bInCreate = TRUE; // we're being created explicitly

  if (m_nBtnImageID != 0 && s_xpstyle.IsAppXPStyled() && ! IsVistaOrLater())
    lpCreateStruct->style |= WS_BORDER;

  DWORD dwStyleDTS = (lpCreateStruct->style & 0xFF);
  lpCreateStruct->style &= ~0xFF;
  // creation of a date time control fails if ES_READONLY included, so remove it
  DWORD dwStyleOrig = lpCreateStruct->style;
  lpCreateStruct->style &= ~ES_READONLY;
  m_bReadOnly = (dwStyleOrig & ES_READONLY);
  if (CDateTimeCtrl::OnCreate(lpCreateStruct) == -1)
    return -1;
  lpCreateStruct->style = dwStyleOrig;

  _ASSERTE(!(dwStyleDTS & DTS_UPDOWN)); // updown not supported
  // 'show none' style not supported, as this control would be used instead
  _ASSERTE(!(dwStyleDTS & DTS_SHOWNONE));
  _ASSERTE(!(dwStyleDTS & DTS_APPCANPARSE));  // app parsing not supported
  _ASSERTE(!(dwStyleDTS & DTS_LONGDATEFORMAT)); // only short dates supported
  _ASSERTE(!(dwStyleDTS & DTS_TIMEFORMAT)); // only short dates supported

  if (dwStyleDTS & DTS_RIGHTALIGN)
    m_bRightAlign = TRUE;
  CRect rc(0, 0, 0, 0);

  m_pEdit = new CDateTimeEditCtrlEditCtrl;
  if (! s_xpstyle.IsAppXPStyled() || ! IsVistaOrLater())
    m_pBtn = new CDateTimeEditCtrlButton;

  // Get the edit control styles and create the edit control
  // we want to isolate the edit styles from the style, and
  // visible and disabled if specified
  // then add in WS_CHILD
  DWORD dwStyleEdit = lpCreateStruct->style & (WS_VISIBLE | WS_DISABLED | 0x3DFFL);
  dwStyleEdit |= WS_CHILD | WS_CLIPSIBLINGS | ES_AUTOHSCROLL;
  dwStyleEdit &= ~WS_BORDER;
  if (! m_pEdit->Create(dwStyleEdit, rc, this, ID_EDIT))
    return -1;

  if (m_pBtn != NULL)
  {
    // Get the button styles and create the button
    // just allow visible and disabled from the specified style
    // and add WS_CHILD and BS_PUSHBUTTON
    DWORD dwStyleBtn = lpCreateStruct->style & (WS_VISIBLE | WS_DISABLED);
    dwStyleBtn |= WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON;
    if (s_xpstyle.IsAppXPStyled())
      dwStyleBtn |= BS_OWNERDRAW;
    if (! m_pBtn->Create(_T("6"), dwStyleBtn, rc, this, ID_BUTTON))
      return -1;
  }

  if (m_bReadOnly)
  {
    m_bReadOnly = FALSE; // force update of controls
    SetReadOnly(TRUE);
  }

  SetButtonImageID(m_nBtnImageID, m_nBtnImageDisabledID);

  // get parent's font, and apply to this control
  CWnd* pParent = GetParent();
  if (pParent != NULL)
  {
    CFont* pFont = pParent->GetFont();
    SetFont(pFont);
  }

  if (m_pBtn != NULL)
  {
    CFont font;
    font.CreatePointFont(100, _T("Marlett"));
    HFONT hFont = (HFONT)font.Detach();
    m_pBtn->SendMessage(WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
  }

  return 0;
}

void CDateTimeEditCtrl::OnStyleChanging(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
  _ASSERTE(lpStyleStruct != NULL);

  if (nStyleType == GWL_STYLE)
  {
    DWORD dwStyleDTSOld = (lpStyleStruct->styleOld & 0xFF);
    DWORD dwStyleDTSNew = (lpStyleStruct->styleNew & 0xFF);
    // isolate bits which have changed (xor old and new)
    DWORD dwStyleDTS = dwStyleDTSOld ^ dwStyleDTSNew;
    _ASSERTE(!(dwStyleDTS & DTS_UPDOWN));
    _ASSERTE(!(dwStyleDTS & DTS_SHOWNONE));
    _ASSERTE(!(dwStyleDTS & DTS_APPCANPARSE));
    _ASSERTE(!(dwStyleDTS & DTS_LONGDATEFORMAT));
    _ASSERTE(!(dwStyleDTS & DTS_TIMEFORMAT));

    if (dwStyleDTS & DTS_RIGHTALIGN)
      m_pEdit->ModifyStyle(dwStyleDTSOld & ES_RIGHT, dwStyleDTSNew & ES_RIGHT);

    // see if we're changing the read-only state
    if (! m_bReadOnly && lpStyleStruct->styleNew & ES_READONLY)
      SetReadOnly(TRUE);
    else if (m_bReadOnly && ! (lpStyleStruct->styleNew & ES_READONLY))
      SetReadOnly(FALSE);
  }
}

void CDateTimeEditCtrl::OnEnable(BOOL bEnable) 
{
  m_bDisabled = ! bEnable;
  // if we're becoming enabled, and we're read-only, 
  // then we actually want to remain disabled, 
  // but just re-enable the edit control
  if (! bEnable || ! m_bReadOnly)
  {
    CDateTimeCtrl::OnEnable(bEnable);
    if (m_pBtn != NULL)
      m_pBtn->EnableWindow(bEnable);
  }
  if (m_pEdit != NULL)
  {
    m_pEdit->EnableWindow(bEnable);
    if (bEnable && ! m_bReadOnly && ! m_bNonEditable)
      m_pEdit->ModifyStyle(ES_READONLY, 0);
  }
  SetButtonImageID(m_nBtnImageID, m_nBtnImageDisabledID);  // cause styles etc to updated
}

void CDateTimeEditCtrl::EnableButton(BOOL bEnable/*=TRUE*/)
{
  if (m_pBtn != NULL)
    m_pBtn->EnableWindow(bEnable);
}

void CDateTimeEditCtrl::OnSetFocus(CWnd* pOldWnd) 
{
  CDateTimeCtrl::OnSetFocus(pOldWnd);

  if (m_bNonEditable && m_pBtn != NULL && ::IsWindow(m_pBtn->m_hWnd))
  {
    // set the focus to the button control
    m_pBtn->SetFocus();
  }
  else if (m_pEdit != NULL && ::IsWindow(m_pEdit->m_hWnd))
  {
    // set the focus to the edit control
    m_pEdit->SetFocus();
    m_pEdit->SetSel(0, -1);
  }
}

// values below found by experimentation; they don't seem to be defined anywhere
#ifndef DP_DATETEXT
// date-picker theme parts
#define DP_DATEBORDER 1
#define DP_DATETEXT 2
#define DP_SHOWCALENDARBUTTONRIGHT 3
#endif // ! DP_DATETEXT

#ifndef DTM_GETDATETIMEPICKERINFO
#define DTM_GETDATETIMEPICKERINFO (DTM_FIRST + 14)  // found by trial and error
typedef struct tagDATETIMEPICKERINFO {
    DWORD cbSize;
    RECT rcCheck;
    DWORD stateCheck;
    RECT rcButton;
    DWORD stateButton;
    HWND hwndEdit;
    HWND hwndUD;
    HWND hwndDropDown;
} DATETIMEPICKERINFO, *LPDATETIMEPICKERINFO;
#endif // DTM_GETDATETIMEPICKERINFO

void CDateTimeEditCtrl::OnSize(UINT nType, int cx, int cy) 
{
  CDateTimeCtrl::OnSize(nType, cx, cy);

  if (cx == 0 || cy == 0)
    return;

  CPoint ptOrg(0, 0);
  CRect rcEdit(ptOrg, CSize(cx, cy));
  CRect rcBtn(CPoint(cx - cy, ptOrg.y), CSize(cy, cy));

  if (s_xpstyle.IsAppXPStyled())
  {
    // if Vista or later, we need to get the button dimensions, etc
    if (IsVistaOrLater())
    {
      // try to get the button rect
      DATETIMEPICKERINFO dtpi = { 0 };
      dtpi.cbSize = sizeof(DATETIMEPICKERINFO);
      SendMessage(DTM_GETDATETIMEPICKERINFO, 0, (LPARAM)&dtpi);

      HTHEME hTheme = s_xpstyle.OpenThemeData(m_hWnd, L"DATEPICKER");
      _ASSERTE(hTheme != NULL);
      if (hTheme != NULL && s_xpstyle.GetThemeBackgroundContentRect(hTheme, GetDC()->m_hDC, DP_DATETEXT, 0, &rcEdit, &rcEdit) == S_OK)
	rcEdit.right -= (dtpi.rcButton.right - dtpi.rcButton.left);
      s_xpstyle.CloseThemeData(hTheme);
    }
    else
    {
      // set the size of the edit and the button
      rcEdit.right -= cy;
      rcEdit.DeflateRect(1, 0, 1, 0);
      rcBtn.left = rcBtn.right - CX_BTN;
      rcEdit.right = cx - rcBtn.Width();
    }
  }
  else
    rcEdit.right -= cy;

  // we can't set the edit control to centre the text verically, so we'll need to figure out the text size, and size the edit to fit
  CDC* pDC = GetDC();
  CSize sizeText = pDC->GetTextExtent(_T("0123456789:/"));
  rcEdit.bottom = rcEdit.top + sizeText.cy;
  rcEdit.OffsetRect(0, (cy - (sizeText.cy + 1)) / 2); // add one to height to make sure odds are rounded up, not down, when halving

  // size the child controls
  if (m_pEdit != NULL && ::IsWindow(m_pEdit->m_hWnd))
    m_pEdit->MoveWindow(&rcEdit);
  if (m_pBtn != NULL && ::IsWindow(m_pBtn->m_hWnd))
    m_pBtn->MoveWindow(&rcBtn);
}

BOOL CDateTimeEditCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
  NMHDR* pnmhdr = (NMHDR*)lParam;
  if (pnmhdr != NULL)
  {
    // if notification from cal ctrl then act on them, and destroy cal ctrl
    CMonthCalCtrl* pCalCtrl = GetMonthCalCtrl();
    if (pCalCtrl != NULL && pnmhdr->hwndFrom == pCalCtrl->m_hWnd)
    {
      if (pnmhdr->code == MCN_SELECT || 
	  pnmhdr->code == MCN_SELCHANGE || 
	  pnmhdr->code == MCN_GETDAYSTATE)
      {
	if (pnmhdr->code == MCN_SELCHANGE || pnmhdr->code == MCN_SELECT)
	{
	  // get date, and put in edit ctrl
	  LPNMSELCHANGE lpnmsc = (LPNMSELCHANGE)pnmhdr;
	  COleDateTime date(lpnmsc->stSelStart);
	  _ASSERTE(date.GetStatus() == COleDateTime::valid);
	  CString sDate(date.Format(VAR_DATEVALUEONLY));
	  m_pEdit->SetWindowText(sDate);

	  if (! s_xpstyle.IsAppXPStyled() || (! IsVistaOrLater() && m_pBtn != NULL))
	  {
	    // tell parent about it (DTN_DATETIMECHANGE)
	    CWnd* pParent = GetParent();
	    if (pParent != NULL)
	    {
	      NMDATETIMECHANGE nmdtc;
	      nmdtc.nmhdr.code = DTN_DATETIMECHANGE;
	      nmdtc.nmhdr.hwndFrom = GetSafeHwnd();
	      nmdtc.nmhdr.idFrom = GetDlgCtrlID();
	      nmdtc.dwFlags = GDT_VALID;
	      nmdtc.st = lpnmsc->stSelStart;
	      pParent->SendMessage(WM_NOTIFY, (WPARAM)nmdtc.nmhdr.idFrom, (LPARAM)&nmdtc);
	    }
	    if (pnmhdr->code == MCN_SELECT)
	    {
	      // we want to close the calendar when the user selects a date
	      DestroyCalendar();
	    }
	  }
	}
	if (! s_xpstyle.IsAppXPStyled() || (! IsVistaOrLater() && m_pBtn != NULL))
	  return TRUE;
      }
    }
    // pass tool-tip notifications or notifications from children on to the parent
    // (there must be a better way of determining which to pass, but this works for now)
    BOOL bPassToParent = FALSE;
    CWnd* pWnd = CWnd::FromHandle(pnmhdr->hwndFrom);
    if (pWnd != NULL && pWnd->GetParent() == this)
      bPassToParent = TRUE;
    if (bPassToParent || (pnmhdr->code == TTN_GETDISPINFOA || pnmhdr->code == TTN_GETDISPINFOW))
    {
      CWnd* pParent = GetParent();
      if (pParent != NULL)
      {
	NMHDR nmhdr = *pnmhdr;
	pnmhdr = &nmhdr;
	pnmhdr->idFrom = GetDlgCtrlID();
	pnmhdr->hwndFrom = GetSafeHwnd();
	*pResult = pParent->SendMessage(WM_NOTIFY, (WPARAM)pnmhdr->idFrom, lParam);
	return TRUE;
      }
    }
  }
  return CDateTimeCtrl::OnNotify(wParam, lParam, pResult);
}

BOOL CDateTimeEditCtrl::OnCommand(WPARAM wParam, LPARAM lParam) 
{
  // if button clicked, show calendar control
  if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == ID_BUTTON)
  {
    if (m_pCalWnd != NULL)
      DestroyCalendar();
    else
      CreateCalendar();
    return TRUE;
  }
  return CDateTimeCtrl::OnCommand(wParam, lParam);
}

void CDateTimeEditCtrl::SetNonEditable(BOOL bNonEditable/*=TRUE*/)
{
  if (m_pEdit == NULL)
    return;
  m_bNonEditable = bNonEditable;
  if (m_bReadOnly)
    return;
  if (m_bDisabled)
    return;
  if (m_bNonEditable || m_bReadOnly)
    m_pEdit->ModifyStyle(0, ES_READONLY);
  else if (! m_bReadOnly)
    m_pEdit->ModifyStyle(ES_READONLY, 0);
  m_pEdit->SetNonEditable(m_bNonEditable);
  // tell the button whether we are non-editable, so it can decide
  // whether to try and restore the focus
  if (m_pBtn != NULL)
    m_pBtn->SetNonEditable(m_bNonEditable);
}

void CDateTimeEditCtrl::SetReadOnly(BOOL bReadOnly/*=TRUE*/)
{
  BOOL bReadOnlyOld = m_bReadOnly;
  m_bReadOnly = bReadOnly;
  if (m_bDisabled)
    return;
  if (bReadOnly && ! bReadOnlyOld)
  {
    // making it readonly
    BOOL bNonEditable = m_bNonEditable;
    m_bReadOnly = FALSE;
    SetNonEditable(FALSE);
    m_bReadOnly = TRUE;
    m_bNonEditable = bNonEditable;
    m_pEdit->ModifyStyle(0, ES_READONLY);
    EnableWindow(FALSE);
    EnableWindow(TRUE);
  }
  else if (! bReadOnly && bReadOnlyOld)
  {
    // making it non-readonly
    EnableWindow(FALSE);
    EnableWindow(TRUE);
    if (! m_bNonEditable)
      m_pEdit->ModifyStyle(ES_READONLY, 0);
    BOOL bNonEditable = m_bNonEditable;
    m_bNonEditable = FALSE;
    SetNonEditable(bNonEditable);
  }
  // cause button to be re-drawn correctly
  SetButtonImageID(m_nBtnImageID, m_nBtnImageDisabledID);
}

BOOL CDateTimeEditCtrl::CreateCalendar()
{
  CRect rc;
  _ASSERTE(m_pCalWnd == NULL);
  m_pCalWnd = new CDateTimeEditCtrlCalendarWnd(this);
  GetWindowRect(&rc);
  rc.top = rc.bottom;

  // Get screen size
  CRect rcWorkArea;
  SystemParametersInfo(SPI_GETWORKAREA, 0, (LPRECT)rcWorkArea, 0);
  if (rc.bottom >= rcWorkArea.bottom)
    rc.bottom = rcWorkArea.bottom;

#if CALENDAR_AS_POPUP
  m_pCalWnd->CreateEx(0, NULL, NULL, WS_CHILD | WS_POPUP | WS_BORDER | WS_CLIPSIBLINGS, rc, this, 0);
#else
  m_pCalWnd->Create(WS_CHILD | WS_BORDER, rc, GetDesktopWindow(), ID_DROPWND);
#endif // CALENDAR_AS_POPUP

  // line calendar window up with appropriate edge of control
  CRect rcCal, rcEdit;
  GetClientRect(&rc);
  ClientToScreen(&rc);
  rc.top = rc.bottom;
  m_pCalWnd->GetWindowRect(&rcCal);
  m_pEdit->GetClientRect(&rcEdit);
  m_pEdit->ClientToScreen(&rcEdit);
  rc.bottom = rc.top + rcCal.Height();
  if (m_bRightAlign)
  {
    rc.right = rcEdit.right;
    rc.left = rc.right - rcCal.Width();
  }
  else
  {
    rc.left = rcEdit.left;
    rc.right = rc.left + rcCal.Width();
  }

  // if it goes off the bottom of the screen, then put it above this control
  if (rc.bottom > rcWorkArea.bottom)
  {
    CRect rcWnd;
    GetWindowRect(&rcWnd);
    rc.OffsetRect(0, -(rcCal.Height() + rcWnd.Height()));
  }
  // if it's off the left, then nudge it over
  if (rc.left < rcWorkArea.left)
  {
    rc.OffsetRect(rcWorkArea.left - rc.left, 0);
  }
  m_pCalWnd->SetWindowPos(NULL, rc.left, rc.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

  m_pCalWnd->ShowWindow(SW_SHOWNA);

  CDateTimeEditCtrlMonthCalCtrl* pCal = m_pCalWnd->GetMonthCalCtrl();

  // set the min/max range if they've been set
  if (pCal != NULL)
    pCal->SetRange(m_pDateMin, m_pDateMax);

  // get edit's current date/time, and set ctrl accordingly
  m_pEdit->GetWindowText(m_sOrigDate);
  if (pCal != NULL)
  {
    COleDateTime dateInit(COleDateTime::GetCurrentTime());
    COleDateTime date;
    if (! m_sOrigDate.IsEmpty() && date.ParseDateTime(m_sOrigDate))
      dateInit = date;
    if (m_pDateMin != NULL && dateInit < *m_pDateMin)
      dateInit = *m_pDateMin;
    else if (m_pDateMax != NULL && dateInit > *m_pDateMax)
      dateInit = *m_pDateMax;
    if (dateInit.GetStatus() == GDT_VALID)
      pCal->SetCurSel(dateInit);
  }

  // set font of cal ctrl if font is non-NULL
  // set colours of cal ctrl if colours are not -1
  if (pCal != NULL)
  {
    if (m_hMCFont != NULL)
    {
      CFont* pFont = CFont::FromHandle(m_hMCFont);
      if (pFont != NULL)
	pCal->SetFont(pFont);
    }
    for (int n = 0; n < 6; n++)
    {
      if (m_acrMonthCal[n] != -1)
	pCal->SetColor(n, m_acrMonthCal[n]);
    }
  }

  // tell parent about it (DTN_DROPDOWN)
  CWnd* pParent = GetParent();
  if (pParent != NULL)
  {
    NMHDR nmhdr;
    nmhdr.code = DTN_DROPDOWN;
    nmhdr.hwndFrom = GetSafeHwnd();
    nmhdr.idFrom = GetDlgCtrlID();
    pParent->SendMessage(WM_NOTIFY, (WPARAM)nmhdr.idFrom, (LPARAM)&nmhdr);
  }

  return TRUE;
}

// destroy the cal ctrl if shown
// returns TRUE if destroyed, else FALSE if not shown
BOOL CDateTimeEditCtrl::DestroyCalendar(BOOL bDiscard/*=FALSE*/)
{
  if (m_pCalWnd == NULL)
    return FALSE;
  if (::IsWindow(m_pCalWnd->m_hWnd))
    m_pCalWnd->DestroyWindow();
  delete m_pCalWnd;
  m_pCalWnd = NULL;
  m_pEdit->SetFocus();
  CWnd* pParent = GetParent();
  // if we canceled, set the original time string, and send change
  if (bDiscard)
  {
    m_pEdit->SetWindowText(m_sOrigDate);
    // tell parent about it (DTN_DATETIMECHANGE)
    if (pParent != NULL)
    {
      NMDATETIMECHANGE nmdtc;
      nmdtc.nmhdr.code = DTN_DATETIMECHANGE;
      nmdtc.nmhdr.hwndFrom = GetSafeHwnd();
      nmdtc.nmhdr.idFrom = GetDlgCtrlID();
      COleDateTime date;
      date.ParseDateTime(m_sOrigDate);
      if (date.GetStatus() == COleDateTime::valid)
	nmdtc.dwFlags = GDT_VALID;
      else
	nmdtc.dwFlags = GDT_NONE;
      date.GetAsSystemTime(nmdtc.st);
      pParent->SendMessage(WM_NOTIFY, (WPARAM)nmdtc.nmhdr.idFrom, (LPARAM)&nmdtc);
    }
  }
  // tell parent about it (DTN_CLOSEUP)
  if (pParent != NULL)
  {
    NMHDR nmhdr;
    nmhdr.code = DTN_CLOSEUP;
    nmhdr.hwndFrom = GetSafeHwnd();
    nmhdr.idFrom = GetDlgCtrlID();
    pParent->SendMessage(WM_NOTIFY, (WPARAM)nmhdr.idFrom, (LPARAM)&nmhdr);
  }
  return TRUE;
}

void CDateTimeEditCtrl::OnCancelMode() 
{
  CDateTimeCtrl::OnCancelMode();
  DestroyCalendar();
}

#define MAP_DTM(dtm) case dtm: s = #dtm;

CString FormatDTM(UINT message)
{
  CString s("<unknown>");
  switch (message)
  {
    MAP_DTM(DTM_GETSYSTEMTIME)
    MAP_DTM(DTM_SETSYSTEMTIME)
    MAP_DTM(DTM_GETRANGE)
    MAP_DTM(DTM_SETRANGE)
    MAP_DTM(DTM_SETFORMAT)
    MAP_DTM(DTM_SETMCCOLOR)
    MAP_DTM(DTM_GETMCCOLOR)
    MAP_DTM(DTM_GETMONTHCAL)
    MAP_DTM(DTM_SETMCFONT)
    MAP_DTM(DTM_GETMCFONT)
  };
  return s;
}

#ifndef WM_THEMECHANGED
#define WM_THEMECHANGED 0x031A
#endif // ! WM_THEMECHANGED

LRESULT CDateTimeEditCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
  // if a recreate message is pending, then we won't have created 
  // the edit control etc yet, so deal with it now
  if (m_pEdit == NULL)
  {
    MSG msg;
    if (PeekMessage(&msg, m_hWnd, DTCEM_RECREATE, DTCEM_RECREATE, PM_REMOVE))
    {
      DispatchMessage(&msg);
      if (message == WM_SHOWWINDOW)
	ShowWindow(wParam ? SW_SHOW : SW_HIDE);
      _ASSERTE(m_pEdit != NULL);
      _ASSERTE(m_pBtn != NULL || (s_xpstyle.IsAppXPStyled() && IsVistaOrLater()));
    }
  }
  switch (message)
  {
  case WM_SETTEXT:
  case WM_GETTEXT:
  case WM_GETTEXTLENGTH:
    {
      _ASSERTE(m_pEdit != NULL);
      return m_pEdit->SendMessage(message, wParam, lParam);
    }
    break;

  case WM_SETFONT:
    {
      _ASSERTE(m_pEdit != NULL);
      m_pEdit->SendMessage(WM_SETFONT, wParam, lParam);
      if (m_pBtn != NULL)
      {
	CFont font;
	font.CreatePointFont(100, _T("Marlett"));
	HFONT hFont = (HFONT)font.Detach();
	m_pBtn->SendMessage(WM_SETFONT, (WPARAM)hFont, lParam);
      }
    }
    break;

  case WM_ERASEBKGND:
    if (m_pEdit != NULL && ::IsWindow(m_pEdit->m_hWnd))
      m_pEdit->Invalidate();
    break;

  case WM_COMMAND:
    {
      // send notifications from the edit control to the parent
      if (LOWORD(wParam) == ID_EDIT)
      {
	CWnd* pParent = GetParent();
	if (pParent != NULL)
	  return pParent->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), HIWORD(wParam)), (LPARAM)GetSafeHwnd());
      }
    }
    break;

  case WM_THEMECHANGED:
    s_xpstyle.Reset(); // make it re-evaluate
    SetButtonImageID(m_nBtnImageID, m_nBtnImageDisabledID);  // cause styles etc to updated
    // the button needs to be owner-drawn for XP-styles
    if (m_pBtn != NULL && ::IsWindow(m_pBtn->m_hWnd))
    {
      if (s_xpstyle.IsAppXPStyled())
	m_pBtn->ModifyStyle(0, BS_OWNERDRAW);
      else
	m_pBtn->ModifyStyle(BS_OWNERDRAW, 0);
    }
    break;

  case DTM_GETSYSTEMTIME:
    {
      // get the time from the current edit text
      // and return whether it's valid
      CString sDate;
      _ASSERTE(m_pEdit != NULL);
      m_pEdit->GetWindowText(sDate);
      if (sDate.IsEmpty())
	return GDT_NONE;
      else
      {
	LPSYSTEMTIME lpst = (LPSYSTEMTIME)lParam;
	ASSERT(lpst != NULL);
	COleDateTime date;
	date.ParseDateTime(sDate);
	ASSERT(date.GetStatus() == COleDateTime::valid);
	date.GetAsSystemTime(*lpst);
	return GDT_VALID;
      }
    }
    break;

  case DTM_SETSYSTEMTIME:
    {
      // set the control's time to the time specified
      _ASSERTE(m_pEdit != NULL);
      if (wParam == GDT_NONE)
	m_pEdit->SetWindowText(_T(""));
      else if (wParam == GDT_VALID)
      {
	if (lParam == 0)
	  return FALSE;
	LPSYSTEMTIME lpst = (LPSYSTEMTIME)lParam;
	COleDateTime date(*lpst);
	if (date.GetStatus() != COleDateTime::valid)
	  return FALSE;
	CString sDate(date.Format(VAR_DATEVALUEONLY));
	m_pEdit->SetWindowText(sDate);
      }
      else
	return FALSE;
      return TRUE;
    }
    break;

  case DTM_GETMONTHCAL:
    {
      if (m_pCalWnd != NULL)
      {
	CMonthCalCtrl* pCal = m_pCalWnd->GetMonthCalCtrl();
	if (pCal != NULL)
	  return (LRESULT)pCal->m_hWnd;
	else
	  return (LRESULT)NULL;
      }
    }
    break;

  case DTM_SETMCFONT:
    {
      m_hMCFont = (HFONT)wParam;
      BOOL bRedraw = (BOOL)lParam;
      if (m_pCalWnd != NULL)
      {
	CMonthCalCtrl* pCal = m_pCalWnd->GetMonthCalCtrl();
	if (pCal == NULL)
	  return 0;
	CFont* pFont = CFont::FromHandle(m_hMCFont);
	pCal->SetFont(pFont, bRedraw);
      }
    }
    break;

  case DTM_GETMCFONT:
    {
      if (m_pCalWnd == NULL)
	return (LRESULT)m_hMCFont;
      CMonthCalCtrl* pCal = m_pCalWnd->GetMonthCalCtrl();
      if (pCal == NULL)
	return (LRESULT)m_hMCFont;
      CFont* pFont = pCal->GetFont();
      return (LRESULT)pFont->m_hObject;
    }
    break;

  case DTM_SETMCCOLOR:
    {
      // set the colour accordingly
      int nIndex = (int)wParam;
      _ASSERTE(nIndex >= 0 && nIndex < 6);
      COLORREF crOld = m_acrMonthCal[nIndex];
      m_acrMonthCal[nIndex] = (COLORREF)lParam;
      // if the cal ctrl is present, set its colours
      if (m_pCalWnd != NULL)
      {
	CMonthCalCtrl* pCal = m_pCalWnd->GetMonthCalCtrl();
	if (pCal != NULL)
	  return (LRESULT)pCal->SetColor(nIndex, m_acrMonthCal[nIndex]);
      }
      return (LRESULT)crOld;
    }
    break;

  case DTM_GETMCCOLOR:
    {
      // get the colour accordingly
      int nIndex = (int)wParam;
      _ASSERTE(nIndex >= 0 && nIndex < 6);
      // if the cal ctrl is present, get its colours
      if (m_pCalWnd != NULL)
      {
	CMonthCalCtrl* pCal = m_pCalWnd->GetMonthCalCtrl();
	if (pCal != NULL)
	  return (LRESULT)pCal->GetColor(nIndex);
      }
      return (LRESULT)m_acrMonthCal[nIndex];
    }
    break;

  case DTM_SETRANGE:
    {
      int nFlags = (int)wParam;
      LPSYSTEMTIME ast = (LPSYSTEMTIME)lParam;
      delete m_pDateMin;
      delete m_pDateMax;
      if (ast != NULL)
      {
	if (nFlags & GDTR_MIN)
	  m_pDateMin = new COleDateTime(ast[0]);
	if (nFlags & GDTR_MAX)
	  m_pDateMax = new COleDateTime(ast[1]);
      }
      // if we're showing calendar control, apply to it now
      CMonthCalCtrl* pCal = GetMonthCalCtrl();
      if (pCal != NULL)
	pCal->SendMessage(DTM_SETRANGE, wParam, lParam);
      return 0;
    }
    break;

  case DTM_GETRANGE:
    {
      int nFlags = 0;
      LPSYSTEMTIME ast = (LPSYSTEMTIME)lParam;
      if (ast != NULL)
      {
	if (m_pDateMin != NULL)
	{
	  m_pDateMin->GetAsSystemTime(ast[0]);
	  nFlags |= GDTR_MIN;
	}
	if (m_pDateMax != NULL)
	{
	  m_pDateMax->GetAsSystemTime(ast[1]);
	  nFlags |= GDTR_MAX;
	}
      }
      return nFlags;
    }
    break;

  case DTM_SETFORMAT:
    TRACE(_T("Got DTM: %s\n"), FormatDTM(message));
    ASSERT(FALSE);  // not supported
    AfxThrowNotSupportedException();
    break;

  }
  return CDateTimeCtrl::WindowProc(message, wParam, lParam);
}

void CDateTimeEditCtrl::PreSubclassWindow() 
{
  CDateTimeCtrl::PreSubclassWindow();

  // if we were created explicitly then everything is hunky-dory
  // else we need to destroy the datetimectrl and create our own stuff
  if (m_bInCreate)
    return;

  PostMessage(DTCEM_RECREATE);
}

LONG CDateTimeEditCtrl::OnRecreate(WPARAM wParam, LPARAM lParam)
{
  // we come in here if we've been subclassed, so we can destroy
  // the existing control, and create our own version
  CWnd* pParentWnd = GetParent();
  if (pParentWnd == NULL)
    pParentWnd = GetDesktopWindow();

  CWnd* pWndFocus = CWnd::GetFocus();
  BOOL bFocus = (pWndFocus == this);

  // get current attributes
  DWORD dwStyle = GetStyle();
  DWORD dwStyleEx = GetExStyle();
  CRect rc;
  GetWindowRect(&rc);
  pParentWnd->ScreenToClient(&rc);	// map to client co-ords
  UINT nID = GetDlgCtrlID();
  CFont* pFont = GetFont();
  CWnd* pWndAfter = GetNextWindow(GW_HWNDPREV);

  if (m_nBtnImageID != 0 && s_xpstyle.IsAppXPStyled() && ! IsVistaOrLater())
    dwStyle |= WS_BORDER;

  DestroyWindow();
  m_hWnd = NULL;

  m_bInCreate = TRUE;

  if (! CWnd::CreateEx(dwStyleEx, DATETIMEPICK_CLASS, NULL, dwStyle, rc, pParentWnd, nID))
    return -1;
  // re-apply attributes
  if (pFont == NULL)
    pFont = pParentWnd->GetFont();
  SetFont(pFont);

  // re-set focus
  if (bFocus)
    SetFocus();

  // position correctly in z-order
  SetWindowPos(pWndAfter == NULL ? &CWnd::wndBottom : pWndAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

  return 0;
}

// returns whether the date passed is valid
// if NULL is passed, then the date in the edit control is used
BOOL CDateTimeEditCtrl::IsValidDate(LPCTSTR lpszDate/*=NULL*/)
{
  CString sDate(lpszDate);
  if (sDate.IsEmpty())
    GetWindowText(sDate);
  COleDateTime date;
  return date.ParseDateTime(sDate);
}

// set whether the user can only enter chars that are valid
void CDateTimeEditCtrl::SetValidCharsOnly(BOOL bValidCharsOnly/*=TRUE*/)
{
  if (m_pEdit != NULL)
    m_pEdit->SetValidCharsOnly(bValidCharsOnly);
}

// returns whether the user can only enter valid chars into the edit control
BOOL CDateTimeEditCtrl::GetValidCharsOnly()
{
  if (m_pEdit != NULL)
    return m_pEdit->GetValidCharsOnly();
  return FALSE;
}

// sets the chars that are valid for the user to type into the edit control
// if NULL is specified, then the default chars are used (0-9 and current 
// user's locale's date separator). If the user changes the locale settings 
// then the control will automatically pick this up and use the new separator.
void CDateTimeEditCtrl::SetValidChars(LPCTSTR lpszValidChars/*=NULL*/)
{
  if (m_pEdit != NULL)
    m_pEdit->SetValidChars(lpszValidChars);
}

// returns the chars that are valid for the user to type into the edit control
CString CDateTimeEditCtrl::GetValidChars()
{
  if (m_pEdit != NULL)
    return m_pEdit->GetValidChars();
  return CString("");
}

void CDateTimeEditCtrl::SetAllowUpDownKeys(BOOL bAllow/*=TRUE*/)
{
  if (m_pEdit != NULL)
    m_pEdit->SetAllowUpDownKeys(bAllow);
}

BOOL CDateTimeEditCtrl::GetAllowUpDownKeys()
{
  if (m_pEdit != NULL)
    return m_pEdit->GetAllowUpDownKeys();
  return FALSE;
}

BOOL CDateTimeEditCtrl::SetButtonImageID(UINT nID, UINT nDisabledID/*=0*/)
{
  m_nBtnImageID = nID;
  m_nBtnImageDisabledID = nDisabledID;

  if (m_pBtn != NULL && ::IsWindow(m_pBtn->m_hWnd))
  {
    _ASSERTE(! IsVistaOrLater());
    if (nID == 0)
    {
      m_pBtn->ModifyStyle(BS_BITMAP | BS_CENTER, 0);
      HBITMAP hbmp = m_pBtn->SetBitmap(NULL);
      if (hbmp != NULL)
	DeleteObject(hbmp);
      if (s_xpstyle.IsAppXPStyled())
	ModifyStyle(WS_BORDER, 0, SWP_FRAMECHANGED);
    }
    else
    {
      CBitmap bmp;
      if (! bmp.LoadBitmap(! m_pBtn->IsWindowEnabled() && m_nBtnImageDisabledID != 0 ? m_nBtnImageDisabledID : m_nBtnImageID))
	return FALSE;
      m_pBtn->ModifyStyle(0, BS_BITMAP | BS_CENTER);
      m_pBtn->SetBitmap((HBITMAP)bmp.GetSafeHandle());
      bmp.Detach();
      if (s_xpstyle.IsAppXPStyled())
	ModifyStyle(0, WS_BORDER, SWP_FRAMECHANGED);
    }
  }
  return TRUE;
}

void CDateTimeEditCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
  CDateTimeCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
  // if using XP styles (but not Vista), and showing a bitmap on the button, 
  // make the client rect bigger, as the border is greedy, 
  // else we won't fit the button in
  if (GetButtonImageID() != 0 && s_xpstyle.IsAppXPStyled() && ! IsVistaOrLater())
    InflateRect(&(lpncsp->rgrc[0]), 2, 2);
}

void CDateTimeEditCtrlEditCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
  CEdit::OnNcCalcSize(bCalcValidRects, lpncsp);
  // if using XP styles (but not Vista), and showing a bitmap on the button, 
  // compensate for the fact that we've made the client rect 
  // of the date control bigger to fit the button in
  CDateTimeEditCtrl* pDate = DYNAMIC_DOWNCAST(CDateTimeEditCtrl, GetParent());
  if (pDate != NULL && pDate->GetButtonImageID() != 0 && s_xpstyle.IsAppXPStyled() && ! IsVistaOrLater())
    InflateRect(&(lpncsp->rgrc[0]), -2, -2);
}

BOOL CDateTimeEditCtrl::OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult) 
{
  *pResult = 0;
  // if we are passing focus to the edit control, don't pass the NM_KILLFOCUS to the parent
  if (CWnd::GetFocus() == m_pEdit)
    return TRUE;  // don't let parent get this
  return FALSE;	// pass on to parent
}
/*
/* returns bounding box for day in given position in given calendar 
static inline void MONTHCAL_GetDayRectI(RECT *r,
	INT col, INT row, INT calIdx)
{
	r->left = days_left + col * width_increment;
	r->right = r->left + width_increment;
	r->top = days_top + row * height_increment;
	r->bottom = r->top + textHeight;
}

static void MONTHCAL_DrawDay(HDC hdc, const SYSTEMTIME *st,
	int bold, const PAINTSTRUCT *ps)
{
	static const WCHAR fmtW[] = { '%','d',0 };
	WCHAR buf[10];
	RECT r, r_temp;
	COLORREF oldCol = 0;
	COLORREF oldBk = 0;
	INT old_bkmode, selection;

	/* no need to check styles: when selection is not valid, it is set to zero.
	1 < day < 31, so everything is OK 
	MONTHCAL_GetDayRect(infoPtr, st, &r, -1);
	if (!IntersectRect(&r_temp, &(ps->rcPaint), &r)) return;

	if ((MONTHCAL_CompareDate(st, &infoPtr->minSel) >= 0) &&
		(MONTHCAL_CompareDate(st, &infoPtr->maxSel) <= 0))
	{
		TRACE("%d %d %d\n", st->wDay, infoPtr->minSel.wDay, infoPtr->maxSel.wDay);
		TRACE("%s\n", wine_dbgstr_rect(&r));
		oldCol = SetTextColor(hdc, infoPtr->colors[MCSC_MONTHBK]);
		oldBk = SetBkColor(hdc, infoPtr->colors[MCSC_TRAILINGTEXT]);
		FillRect(hdc, &r, infoPtr->brushes[BrushTitle]);

		selection = 1;
	}
	else
		selection = 0;

	SelectObject(hdc, bold ? infoPtr->hBoldFont : infoPtr->hFont);

	old_bkmode = SetBkMode(hdc, TRANSPARENT);
	wsprintfW(buf, fmtW, st->wDay);
	DrawTextW(hdc, buf, -1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SetBkMode(hdc, old_bkmode);

	if (selection)
	{
		SetTextColor(hdc, oldCol);
		SetBkColor(hdc, oldBk);
	}
}
*/

void CDateTimeEditCtrl::OnPaint()
{
  Default();  // we want all the default drawing

  CClientDC dc(this);

  CRect rc;

  // if a button image id is specified, and we are xp-styled on Vista or later, draw the image over the button
  if (m_nBtnImageID != 0 && m_pBtn == NULL)
  {
    if (IsVistaOrLater())
    {
      // get the button rect
      DATETIMEPICKERINFO dtpi = { 0 };
      dtpi.cbSize = sizeof(DATETIMEPICKERINFO);
      SendMessage(DTM_GETDATETIMEPICKERINFO, 0, (LPARAM)&dtpi);
      rc = dtpi.rcButton;
    }
    else
    {
      CRect rcClient;
      GetClientRect(&rcClient);
      int cx = rcClient.Width();
      int cy = rcClient.Height();
      rc = CRect(CPoint(cx - CX_BTN, 0), CSize(CX_BTN, cy));
    }
    if (s_xpstyle.IsAppXPStyled())
    {
      // the closest we can get to a date-time picker's button, but without its own image, is the combo-box button
      // so we'll draw a combo-box button over the top of the date-time picker's button, and then put the image on that
      HTHEME hTheme = s_xpstyle.OpenThemeData(m_hWnd, L"COMBOBOX");
      _ASSERTE(hTheme != NULL);
      // figure out what state to draw:
      // if the calendar is shown, then it's pressed, else, if enabled, if mouse over button then hot else normal, else disabled
      UINT nState = CBXS_NORMAL;
      if (! IsWindowEnabled())
	nState = CBXS_DISABLED;
      else if (IsVistaOrLater() && GetMonthCalCtrl() != NULL)
	nState = CBXS_PRESSED;
      else
      {
	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	if (rc.PtInRect(pt))
	{
	  nState = CBXS_HOT;
	  if (! IsVistaOrLater() && GetAsyncKeyState(MK_LBUTTON) & 0x80000000)
	    nState = CBXS_PRESSED;
	}
      }
      VERIFY(s_xpstyle.DrawThemeBackground(hTheme, dc.GetSafeHdc(), CP_DROPDOWNBUTTON, nState, &rc, NULL) == S_OK);
      s_xpstyle.CloseThemeData(hTheme);
    }
    else
    {
      // not xp-styled; draw button and bitmap using good old GDI functions
      dc.DrawFrameControl(rc, DFC_BUTTON, DFCS_BUTTONPUSH);
    }
    // now we draw the actual bitmap
    UINT nImageID = ! IsWindowEnabled() && m_nBtnImageDisabledID != 0 ? m_nBtnImageDisabledID : m_nBtnImageID;
    CBitmap bmp;
    bmp.LoadBitmap(nImageID);
    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);
    CPoint pt = rc.TopLeft();
    pt.Offset(rc.CenterPoint() - rc.TopLeft());
    pt.Offset(-bmpInfo.bmWidth / 2, -bmpInfo.bmHeight / 2);
    CDC dcMemory;
    dcMemory.CreateCompatibleDC(&dc);
    dcMemory.SelectObject(&bmp);
    dc.BitBlt(pt.x, pt.y, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory, 0, 0, SRCCOPY);
  }
}
