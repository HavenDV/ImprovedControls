////////////////////////////////////////////////////////////////////////////
// File:	DateTimeEditCtrl.h
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

#if !defined(AFX_DATETIMEEDITCTRL_H__737F6EBA_CC75_11D6_8634_0000B48746CF__INCLUDED_)
#define AFX_DATETIMEEDITCTRL_H__737F6EBA_CC75_11D6_8634_0000B48746CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxdtctl.h" // only needed for date/time controls

#define DTCEM_DESTROY_CALENDAR	(WM_USER+1)
#define DTCEM_RECREATE		(WM_USER+2)

#ifndef _UXTHEME_H_
// to avoid reliance on uxtheme.h, and uxtheme.lib, we'll load 
// the theme functions, but only once
typedef HANDLE HTHEME;
#endif // _UXTHEME_H_

typedef HTHEME(_stdcall *PFNOPENTHEMEDATA)(HWND, LPWSTR);
typedef HRESULT(_stdcall *PFNCLOSETHEMEDATA)(HTHEME);
typedef HRESULT(__stdcall *PFNDRAWTHEMEBACKGROUND)(HTHEME hTheme, HDC hdc, 
	int iPartId, int iStateId, const RECT *pRect,  const RECT *pClipRect);
typedef BOOL(__stdcall *PFNISAPPTHEMED)(void);
typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDCONTENTRECT)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pBoundingRect, RECT *pContentRect);

#include <shlwapi.h>  // for DllGetVersion definitions

/////////////////////////////////////////////////////////////////////////////
// CDateTimeEditCtrl window

class CDateTimeEditCtrl : public CDateTimeCtrl
{
  DECLARE_DYNAMIC(CDateTimeEditCtrl)

  class CDateTimeEditXPStyle
  {
    // comctl32.dll, and some other DLLs, export a DllGetVersion method 
    // so we use that to see which version of comctl32.dll is currently loaded
    static DWORD GetComCtl32Version()
    {
      HINSTANCE hInstDll = LoadLibrary(_T("COMCTL32.DLL"));
      if (hInstDll == NULL)
	return 0;
      DLLGETVERSIONPROC pfnDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hInstDll, "DllGetVersion");
      if (pfnDllGetVersion == NULL)
	return 0;
      DLLVERSIONINFO dvi = { sizeof(dvi) };
      pfnDllGetVersion(&dvi);
      DWORD dwMajor = dvi.dwMajorVersion;
      FreeLibrary(hInstDll);
      return dwMajor;
    }
  public:
    CDateTimeEditXPStyle()
    {
      m_nIsAppXPStyled = -1;
      m_hThemeDLL = LoadLibrary(_T("uxtheme.dll"));
      if (m_hThemeDLL != NULL)
      {
	m_pfnOpenThemeData = (PFNOPENTHEMEDATA)GetProcAddress(m_hThemeDLL, "OpenThemeData");
	m_pfnCloseThemeData = (PFNCLOSETHEMEDATA)GetProcAddress(m_hThemeDLL, "CloseThemeData");
	m_pfnDrawThemeBackground = (PFNDRAWTHEMEBACKGROUND)GetProcAddress(m_hThemeDLL, "DrawThemeBackground");
	m_pfnIsAppThemed = (PFNISAPPTHEMED)GetProcAddress(m_hThemeDLL, "IsAppThemed");
	m_pfnGetThemeBackgroundContentRect = (PFNGETTHEMEBACKGROUNDCONTENTRECT)GetProcAddress(m_hThemeDLL, "GetThemeBackgroundContentRect");
      }
    }
    ~CDateTimeEditXPStyle()
      { if (m_hThemeDLL != NULL) FreeLibrary(m_hThemeDLL); }
    HTHEME OpenThemeData(HWND hwnd, LPWSTR pszClassList)
      { return (m_pfnOpenThemeData != NULL) ? m_pfnOpenThemeData(hwnd, pszClassList) : NULL; }
    HRESULT CloseThemeData(HTHEME hTheme)
      { return (m_pfnCloseThemeData != NULL) ? m_pfnCloseThemeData(hTheme) : E_FAIL; }
    HRESULT DrawThemeBackground(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, const RECT *pClipRect = NULL)
      { return (m_pfnDrawThemeBackground != NULL) ? m_pfnDrawThemeBackground(hTheme, hdc, iPartId, iStateId, pRect, pClipRect) : E_FAIL; }
    HRESULT GetThemeBackgroundContentRect(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pBoundingRect, RECT *pContentRect)
      { return (m_pfnGetThemeBackgroundContentRect != NULL) ? m_pfnGetThemeBackgroundContentRect(hTheme, hdc, iPartId, iStateId, pBoundingRect, pContentRect) : E_FAIL; }
    BOOL IsAppThemed(void)
      { return (m_pfnIsAppThemed != NULL) ? m_pfnIsAppThemed() : FALSE; }
    BOOL IsAppXPStyled()
    {
      if (m_nIsAppXPStyled == -1)
	// IsAppThemed returns TRUE even if the app has no manifest file 
	// The only way to really check is to test the major version of comctl32.dll
	m_nIsAppXPStyled = (IsAppThemed() && GetComCtl32Version() >= 6) ? 1 : 0;
      return (m_nIsAppXPStyled > 0);
    }
    void Reset() { m_nIsAppXPStyled = -1; }
  protected:
    HINSTANCE m_hThemeDLL;  // DLL handle for XP styling library
    PFNOPENTHEMEDATA m_pfnOpenThemeData;
    PFNCLOSETHEMEDATA m_pfnCloseThemeData;
    PFNDRAWTHEMEBACKGROUND m_pfnDrawThemeBackground;
    PFNISAPPTHEMED m_pfnIsAppThemed;
    PFNGETTHEMEBACKGROUNDCONTENTRECT m_pfnGetThemeBackgroundContentRect;
    int m_nIsAppXPStyled;
  };

  /////////////////////////////////////////////////////////////////////////////
  // CDateTimeEditCtrlButton window
  class CDateTimeEditCtrlButton : public CButton
  {
  public:
    CDateTimeEditCtrlButton() { m_bRestoreFocus = FALSE; m_pWndLastFocus = NULL; m_bNonEditable = FALSE; }
    void RestoreFocus(BOOL bRestore = TRUE) { m_bRestoreFocus = bRestore; }
    void SetNonEditable(BOOL bNonEditable = TRUE) { m_bNonEditable = bNonEditable; }
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDateTimeEditCtrlButton)
	  public:
	  virtual BOOL PreTranslateMessage(MSG* pMsg);
	  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	  //}}AFX_VIRTUAL

    // Generated message map functions
  protected:
    CWnd* m_pWndLastFocus;
    BOOL m_bRestoreFocus;
    BOOL m_bNonEditable;

    //{{AFX_MSG(CDateTimeEditCtrlButton)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	  //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

  /////////////////////////////////////////////////////////////////////////////
  // CDateTimeEditCtrlEditCtrl window
  class CDateTimeEditCtrlEditCtrl : public CEdit
  {
  public:
    BOOL GetAllowUpDownKeys();
    void SetAllowUpDownKeys(BOOL bAllow = TRUE);
    CString GetValidChars();
    void SetValidChars(LPCTSTR lpszValidChars = NULL);
    BOOL GetValidCharsOnly();
    void SetValidCharsOnly(BOOL bValidCharsOnly = TRUE);
    CDateTimeEditCtrlEditCtrl();
    void SetNonEditable(BOOL bNonEditable = TRUE) { m_bNonEditable = bNonEditable; }
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDateTimeEditCtrlEditCtrl)
	  public:
	  virtual BOOL PreTranslateMessage(MSG* pMsg);
	  //}}AFX_VIRTUAL

    // Generated message map functions
  protected:
	  void SendDateTimeChange();
    BOOL m_bNonEditable;
    BOOL m_bValidCharsOnly;
    CString m_sValidChars;
    BOOL m_bAllowUpDownKeys;

	  //{{AFX_MSG(CDateTimeEditCtrlEditCtrl)
	  afx_msg UINT OnGetDlgCode();
	  afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	  afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	  afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	  afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	  afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	  afx_msg void OnKillFocus(CWnd* pNewWnd);
	  //}}AFX_MSG
	  afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
    DECLARE_MESSAGE_MAP()
  };

  /////////////////////////////////////////////////////////////////////////////
  // CDateTimeEditCtrlMonthCalCtrl window

  class CDateTimeEditCtrlMonthCalCtrl : public CMonthCalCtrl
  {
  // Construction
  public:
	  CDateTimeEditCtrlMonthCalCtrl();

  // Attributes
  public:

  // Operations
  public:

  // Overrides
	  // ClassWizard generated virtual function overrides
	  //{{AFX_VIRTUAL(CDateTimeEditCtrlMonthCalCtrl)
	  protected:
	  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	  //}}AFX_VIRTUAL

  // Implementation
  public:
	  virtual ~CDateTimeEditCtrlMonthCalCtrl();

	  // Generated message map functions
  protected:
	  DWORD m_nIgnoreNextMessage;

	  //{{AFX_MSG(CDateTimeEditCtrlMonthCalCtrl)
	  //}}AFX_MSG
	  DECLARE_MESSAGE_MAP()
  };

  /////////////////////////////////////////////////////////////////////////////
  // CDateTimeEditCtrlCalendarWnd window

  class CDateTimeEditCtrlCalendarWnd : public CWnd
  {
  // Construction
  public:
    CDateTimeEditCtrlCalendarWnd(CWnd* pComboParent, DWORD dwMCStyle = 0);

  // Attributes
  public:
    CDateTimeEditCtrlMonthCalCtrl* GetMonthCalCtrl() { return m_pCalendar; }

  // Operations
  public:

  // Overrides
	  // ClassWizard generated virtual function overrides
	  //{{AFX_VIRTUAL(CDateTimeEditCtrlCalendarWnd)
	  public:
	  virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	  virtual BOOL DestroyWindow();
	  protected:
	  virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	  //}}AFX_VIRTUAL

  // Implementation
  public:
	  virtual ~CDateTimeEditCtrlCalendarWnd();

	  // Generated message map functions
  protected:
	  //{{AFX_MSG(CDateTimeEditCtrlCalendarWnd)
	  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	  //}}AFX_MSG
  #if _MFC_VER >= 0x0700
	  afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);
  #else
	  afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
  #endif
	  DECLARE_MESSAGE_MAP()

  private:
	  CDateTimeEditCtrlMonthCalCtrl* m_pCalendar;

	  CWnd* m_pComboParent;

	  DWORD m_dwMCStyle;
  };

// Construction
public:
	CDateTimeEditCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateTimeEditCtrl)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
  BOOL SetButtonImageID(UINT nID, UINT nDisabledID = 0);
  UINT GetButtonImageID(UINT* pDisabledID = NULL) const { if (pDisabledID != NULL) *pDisabledID = m_nBtnImageDisabledID; return m_nBtnImageID; }
  void GetButtonImageIDs(UINT& nID, UINT& nDisabledID) const { nID = m_nBtnImageID; nDisabledID = m_nBtnImageDisabledID; }
  BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
  virtual ~CDateTimeEditCtrl();
  CEdit* GetEditControl() const { return m_pEdit; }
  void EnableButton(BOOL bEnable = TRUE);
  void RestoreFocus(BOOL bRestore = TRUE) { if (m_pBtn != NULL) m_pBtn->RestoreFocus(bRestore); }
  void SetNonEditable(BOOL bNonEditable = TRUE);
  BOOL GetNonEditable() { return m_bNonEditable; }
  void SetReadOnly(BOOL bReadOnly = TRUE);
  BOOL GetReadOnly() const { return m_bReadOnly; }
  virtual BOOL IsValidDate(LPCTSTR lpszDate = NULL);
  void SetValidCharsOnly(BOOL bValidCharsOnly = TRUE);
  BOOL GetValidCharsOnly();
  void SetValidChars(LPCTSTR lpszValidChars = NULL);
  CString GetValidChars();
  void SetAllowUpDownKeys(BOOL bAllow = TRUE);
  BOOL GetAllowUpDownKeys();

	// Generated message map functions
protected:
  BOOL DestroyCalendar(BOOL bDiscard = FALSE);
  BOOL CreateCalendar();
  CDateTimeEditCtrlEditCtrl* m_pEdit;
  CDateTimeEditCtrlButton* m_pBtn;
  UINT m_nBtnImageID;
  UINT m_nBtnImageDisabledID;
  BOOL m_bNonEditable;
  BOOL m_bReadOnly;
  BOOL m_bDisabled;
  BOOL m_bRightAlign;

  CSpinButtonCtrl* m_pSpin;

  CDateTimeEditCtrlCalendarWnd* m_pCalWnd;
  CString m_sOrigDate;

  BOOL m_bInCreate;

  COleDateTime* m_pDateMin;
  COleDateTime* m_pDateMax;

  // monthcal properties
  HFONT m_hMCFont;
  COLORREF m_acrMonthCal[6];

	//{{AFX_MSG(CDateTimeEditCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCancelMode();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	public:
	afx_msg void OnPaint();
	//}}AFX_MSG
	protected:
	afx_msg BOOL OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LONG OnDestroyCalendar(WPARAM wParam, LPARAM lParam);
	afx_msg void OnStyleChanging(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg LONG OnRecreate(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

// typedef the nested classes so we can use the plain names
// and so the Class Wizard will still work
typedef CDateTimeEditCtrl::CDateTimeEditCtrlButton CDateTimeEditCtrlButton;
typedef CDateTimeEditCtrl::CDateTimeEditCtrlEditCtrl CDateTimeEditCtrlEditCtrl;
typedef CDateTimeEditCtrl::CDateTimeEditCtrlMonthCalCtrl CDateTimeEditCtrlMonthCalCtrl;
typedef CDateTimeEditCtrl::CDateTimeEditCtrlCalendarWnd CDateTimeEditCtrlCalendarWnd;

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATETIMEEDITCTRL_H__737F6EBA_CC75_11D6_8634_0000B48746CF__INCLUDED_)
