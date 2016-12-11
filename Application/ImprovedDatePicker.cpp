#include "stdafx.h"
#include "ImprovedDatePicker.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <string>
#include <fstream>

enum CachedPen
{
	PenRed = 0,
	PenText,
	PenLast
};

enum CachedBrush
{
	BrushTitle = 0,
	BrushMonth,
	BrushBackground,
	BrushLast
};

/* single calendar data */
typedef struct _CALENDAR_INFO
{
	RECT title;      /* rect for the header above the calendar */
	RECT titlemonth; /* the 'month name' text in the header */
	RECT titleyear;  /* the 'year number' text in the header */
	RECT wdays;      /* week days at top */
	RECT days;       /* calendar area */
	RECT weeknums;   /* week numbers at left side */

	SYSTEMTIME month;/* contains calendar main month/year */
} CALENDAR_INFO;
/*
typedef struct
{
	int	buffer[2555];
	HWND    hwndSelf;
	DWORD   dwStyle; /* cached GWL_STYLE 

	COLORREF    colors[MCSC_TRAILINGTEXT + 1];
	HBRUSH      brushes[BrushLast];
	HPEN        pens[1];
	WCHAR       text[32];

	HFONT   hFont;
	HFONT   hBoldFont;
	int     textHeight;
	int     height_increment;
	int     width_increment;
	INT     delta;  /* scroll rate; # of months that the
                    /* control moves when user clicks a scroll button 
	int     firstDay;   /* Start month calendar with firstDay's day,
							stored in SYSTEMTIME format
	BOOL    firstDaySet;    /* first week day differs from locale defined 

	BOOL    isUnicode;      /* value set with MCM_SETUNICODE format

	MONTHDAYSTATE *monthdayState;
	SYSTEMTIME  todaysDate;
	BOOL    todaySet;       /* Today was forced with MCM_SETTODAY 
	int     status;     /* See MC_SEL flags
	SYSTEMTIME  firstSel;   /* first selected day
	INT     maxSelCount;
	SYSTEMTIME  minSel;         /* contains single selection when used without MCS_MULTISELECT
	SYSTEMTIME  maxSel;
	SYSTEMTIME  focusedSel;     /* date currently focused with mouse movement
	DWORD   rangeValid;
	SYSTEMTIME  minDate;
	SYSTEMTIME  maxDate;

	RECT titlebtnnext;  ///* the `next month' button in the header
	RECT titlebtnprev;  ///* the `prev month' button in the header 
	RECT todayrect; ///* `today: xx/xx/xx' text rect
	HWND hwndNotify;   / /* Window to receive the notifications 
	HWND hWndYearEdit;  /* Window Handle of edit box to handle years 
	HWND hWndYearUpDown;/* Window Handle of updown box to handle years 
	WNDPROC EditWndProc;  /* original Edit window procedure

	CALENDAR_INFO *calendars;
	SIZE dim;           /* [cx,cy] - dimensions of calendars matrix, row/column count 
} MONTHCAL_INFO, *LPMONTHCAL_INFO;
*/
typedef struct
{
	CRect buffer[2555];
	BYTE bytes[3];
	HWND hwndSelf;
	HWND hMonthCal;
	HWND hwndNotify;
	HWND hUpdown;
	DWORD dwStyle;
	SYSTEMTIME date;
	BOOL dateValid;
	HWND hwndCheckbut;
	RECT rcClient; /* rect around the edge of the window */
	RECT rcDraw; /* rect inside of the border */
	RECT checkbox;  /* checkbox allowing the control to be enabled/disabled */
	RECT calbutton; /* button that toggles the dropdown of the monthcal control */
	BOOL bCalDepressed; /* TRUE = cal button is depressed */
	BOOL bDropdownEnabled;
	int  select;
	WCHAR charsEntered[4];
	int nCharsEntered;
	HFONT hFont;
	int nrFieldsAllocated;
	int nrFields;
	int haveFocus;
	int *fieldspec;
	RECT *fieldRect;
	int  *buflen;
	WCHAR textbuf[256];
	POINT monthcal_pos;
	int pendingUpdown;
} DATETIME_INFO, *LPDATETIME_INFO;

ImprovedDatePicker::ImprovedDatePicker()
{
}


ImprovedDatePicker::~ImprovedDatePicker()
{
}

BEGIN_MESSAGE_MAP(ImprovedDatePicker, CDateTimeCtrl)
	ON_NOTIFY_REFLECT(DTN_DROPDOWN, &ImprovedDatePicker::OnDtnDropdown)
	ON_WM_PAINT(&ImprovedDatePicker::OnPaint)
	ON_NOTIFY_REFLECT(DTN_DATETIMECHANGE, &ImprovedDatePicker::OnDtnDatetimechange)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/*
BEGIN_MESSAGE_MAP(CMyDatePicker, CDateTimeCtrl)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT(OnPaint)
	ON_DTN_DROPDOWN, &CMyDatePicker::OnDtnDropdown)
END_MESSAGE_MAP()
*/

void    ImprovedDatePicker::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDateTimeCtrl::OnPaint() for painting messages
	
	CDateTimeCtrl::OnPaint();
	/*
	CDC* pdc = GetDC();
	//COLORREF temp = pdc->SetTextColor(RGB(255, 0, 0));
	COleDateTime time;
	CDateTimeCtrl::GetTime(time);
	CString str = time.Format(_T("%m, %d, %Y"));
	//CString str = time.Format(_T("%A, %B %d, %Y"));

	pdc->SetTextColor(RGB(255, 0, 0));
	pdc->TextOutW(4, 2, str);
	//CDateTimeCtrl::OnKillFocus(this);
	//UpdateWindow();
	*/
}

BOOL CALLBACK MyEnumProc(HWND hWnd, LPARAM lParam)
{
	// Do your work here.
	TRACE("Enumerated Child Window : %x\n", hWnd);
	//::SetWindowTheme(hWnd, L" ", L" ");
	::MessageBox((HWND)lParam, _T("hello"), _T("Error"), MB_ICONERROR | MB_OK);
	return TRUE;
}

void    ImprovedDatePicker::OnDtnDropdown(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPDATETIME_INFO dateInfoPtr;
	dateInfoPtr = (LPDATETIME_INFO)::GetWindowLongPtr(m_hWnd, 0);
	VERIFY(dateInfoPtr); 
	//DATETIMEPICKERINFO dtpi = { 0 };
	//dtpi.cbSize = sizeof(DATETIMEPICKERINFO);
	//BOOL rc = GetDateTimePickerInfo(&dtpi);
	//dtpi.hwndDropDown = CreateWindowExW (0, MONTHCAL_CLASSW, 0, WS_BORDER | WS_POPUP | WS_CLIPSIBLINGS,
	//				  0, 0, 0, 0, m_hWnd, 0, 0, 0);
	//if (rc == TRUE)
	//	AfxMessageBox(_T("Information retrieved"),
	//		MB_ICONEXCLAMATION);
	//else
	//	AfxMessageBox(_T("Information was not retrieved"));
	//for (int i = 0; i < 2555; ++i)[i]
	{
		//dateInfoPtr->hwndDropDown = 0;
	}

	CMonthCalCtrl* myCalCtrl = new CImprovedMonthCalCtrl();
	CRect rect(300, 100, 470, 200);
	VERIFY(myCalCtrl->Create(WS_TABSTOP | WS_CHILD | WS_VISIBLE |
		WS_BORDER | MCS_MULTISELECT, rect, this, 166));
	//dateInfoPtr->buffer[54] = myCalCtrl->m_hWnd;
	SetWindowLongPtrW(m_hWnd, 0, (DWORD_PTR)dateInfoPtr);
	dateInfoPtr = (LPDATETIME_INFO)::GetWindowLongPtr(m_hWnd, 0);
	//offset 2 54

	CMonthCalCtrl* calCtrl = this->GetMonthCalCtrl();
	//calCtrl->m_hWnd = 
	VERIFY(calCtrl);
	//myCalCtrl->Create(0,CR)
	//VERIFY(myCalCtrl);
	//memcpy(calCtrl, myCalCtrl, sizeof(CImprovedMonthCalCtrl));
	//memset(calCtrl, ((int*)myCalCtrl)[0], 1);

	*pResult = 0;
	
	auto need = RGB(255, 232, 205);
	auto need2 = RGB(205, 232, 255);
	::SetWindowTheme(calCtrl->m_hWnd, L" ", L" ");
	return;
	//infoPtr->colors[MCSC_BACKGROUND] = RGB(255, 0, 0);
	//infoPtr->colors[MCSC_TEXT] = RGB(255, 0, 0);
	//infoPtr->colors[MCSC_TITLEBK] = RGB(255, 0, 0);
	//infoPtr->colors[MCSC_TITLETEXT] = RGB(255, 0, 0);
	//infoPtr->colors[MCSC_MONTHBK] = RGB(255, 0, 0);
	//infoPtr->colors[MCSC_TRAILINGTEXT] = RGB(255, 0, 0);
	std::ofstream log("logfile.txt", std::ios_base::app | std::ios_base::out);
	std::ofstream log2("text.txt", std::ios_base::app | std::ios_base::out);
	log2 << BYTE(255) << BYTE(232) << BYTE(205);
	for (int i = 0; i<25555;++i)
	{
		if (GetSysColor(i)== RGB(255, 232, 205))
			MessageBox(_T("hello"), _T("hello"), MB_ICONERROR | MB_OK);
		//log << infoPtr->buffer[i];
		//wchar_t wcstring[32];
		//size_t convertedChars = 0;

		//mbstowcs_s(&convertedChars, wcstring, 32, std::to_string(infoPtr->buffer[i]).c_str(), _TRUNCATE);

		//if (i>0 && infoPtr->buffer[i-1] == (BYTE)204 && infoPtr->buffer[i]== (BYTE)232)
		//MessageBox(wcstring, _T("hello"), MB_ICONERROR | MB_OK);
		
	}
	wchar_t wcstring[32];
	size_t convertedChars = 0;

	//mbstowcs_s(&convertedChars, wcstring, 32, std::to_string(infoPtr->colors[MCSC_TRAILINGTEXT]).c_str(), _TRUNCATE);

	//MessageBox(wcstring, _T("Error"), MB_ICONERROR | MB_OK);
	//infoPtr->brushes[BrushBackground] = CreateSolidBrush(infoPtr->colors[MCSC_BACKGROUND]);
	//infoPtr->brushes[BrushTitle] = CreateSolidBrush(infoPtr->colors[MCSC_TITLEBK]);
	//infoPtr->brushes[BrushMonth] = CreateSolidBrush(infoPtr->colors[MCSC_MONTHBK]);

	//infoPtr->pens[PenRed] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	//infoPtr->pens[PenText] = CreatePen(PS_SOLID, 1, infoPtr->colors[MCSC_TEXT]);

	//mbstowcs_s(&convertedChars, infoPtr->text, 32, "hello world", _TRUNCATE);

	//memset(&infoPtr + 1, 0, 1);
	//SetWindowLongPtrW(calCtrl->m_hWnd, 0, (DWORD_PTR)infoPtr);


	EnumChildWindows(calCtrl->m_hWnd,
		MyEnumProc,
		(LPARAM)this); // 3rd parameters 
			   // non-NULL only if you want to 
			   //pass something to the callback
			   // function
	//calCtrl->
	HTHEME theme = ::GetWindowTheme(m_hWnd);
	VERIFY(theme);
	//for (auto i=0;i < 10;++i)
	{
		auto pdc = calCtrl->GetWindowDC();
		
		CString str = (_T("%m, %d, %Y"));
		//CString str = time.Format(_T("%A, %B %d, %Y"));

		pdc->SetTextColor(RGB(255, 0, 0));
		pdc->TextOutW(4, 2, str);
		//TCHAR cName[MAX_PATH];
		//if (container && GetWindowModuleFileName(container->GetSafeHwnd(), cName, 4000) > 0)
		//{
			//MessageBox(cName, _T("Error"), MB_ICONERROR | MB_OK);
		//	::SetWindowTheme(container->m_hWnd, L" ", L" ");
		//}
		//auto container = calCtrl->ChildWindowFromPoint(CPoint(10,10)); 
		//if(container)
		//MessageBox(_T("Error"), _T("Error"), MB_ICONERROR | MB_OK);
		//VERIFY(container);
	}
	TCHAR stringThemeName[MAX_PATH];
	TCHAR stringColorName[MAX_PATH];
	TCHAR stringSizeName[MAX_PATH];
	::GetCurrentThemeName(stringThemeName, MAX_PATH, stringColorName, MAX_PATH, stringSizeName, MAX_PATH);
	//MessageBox(stringThemeName, _T("Error"), MB_ICONERROR | MB_OK);
	//MessageBox(stringColorName, _T("Error"), MB_ICONERROR | MB_OK);
	//MessageBox(stringSizeName, _T("Error"), MB_ICONERROR | MB_OK);
	
	LOGFONTW lf;
	HRESULT hr = ::GetThemeFont(theme, NULL,
		HP_HEADERITEM, HIS_NORMAL, TMT_CAPTIONFONT, &lf);
	if (FAILED(hr))
		hr = ::GetThemeSysFont(theme, TMT_CAPTIONFONT, &lf);

	//MessageBox(lf.lfFaceName, _T("Error"), MB_ICONERROR | MB_OK);
	//LOGFONT font;
	//VERIFY(GetThemeFont(theme, TMT_CAPTIONFONT, &font));
	//std::cout << font.lfFaceName;

	//::SetWindowTheme(calCtrl->m_hWnd, L" ", L" ");

	CloseThemeData(theme);
	*pResult = 0;
}

void    ImprovedDatePicker::OnDtnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult)
{
	/*
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	COleDateTime  timeDest;
	GetTime(timeDest);
	
	if (timeDest.GetMonth() == 11)
	{
		SetMonthCalColor(MCSC_TEXT, RGB(255, 0, 0));
	}
	else
		SetMonthCalColor(MCSC_TEXT, RGB(0, 0, 0));
	*/
	*pResult = 0;
}


BOOL   ImprovedDatePicker::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDateTimeCtrl::OnEraseBkgnd(pDC);
}


BOOL ImprovedDatePicker::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	// TODO: Add your specialized code here and/or call the base classif(WM_CTLCOLOREDIT != message)

	//MessageBox(wcstring, _T("Error"), MB_ICONERROR | MB_OK);
	if (WM_CTLCOLORSTATIC != message)
		return CDateTimeCtrl::OnChildNotify(message, wParam, lParam, pLResult);

	HDC hdcChild = (HDC)wParam;
	if (NULL != hdcChild)
	{
		SetBkMode(hdcChild, TRANSPARENT);
		SetTextColor(hdcChild, RGB(255, 255, 0));
		SetBkColor(hdcChild, RGB(255, 0, 0));
		//*pLResult = (LRESULT)(m_Brush.GetSafeHandle());
	}

	MessageBox(_T("Error"), _T("Error"), MB_ICONERROR | MB_OK);
	return TRUE;
}

static BOOL
DATETIME_SendSimpleNotify(HWND hWndFrom, HWND hWndTo, UINT code)
{
	NMHDR nmhdr;

	TRACE("%x\n", code);
	nmhdr.hwndFrom = hWndFrom;
	nmhdr.idFrom = GetWindowLongPtrW(hWndFrom, GWLP_ID);
	nmhdr.code = code;

	return (BOOL)SendMessageW(hWndTo, WM_NOTIFY,
		nmhdr.idFrom, (LPARAM)&nmhdr);
}

void ImprovedDatePicker::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDateTimeCtrl::OnLButtonDown(nFlags, point);
	return;
	CRect rect(0, 200, 0, 200);
	VERIFY(m_monthCalCtrl.Create(WS_TABSTOP | WS_CHILD | WS_VISIBLE |
		WS_BORDER | MCS_MULTISELECT, rect, this, IDC_MONTHCALCTRL1));
	
	RECT rcMonthCal;
	POINT pos;
	::SendMessageW(m_monthCalCtrl.m_hWnd, MCM_GETMINREQRECT, 0, (LPARAM)&rcMonthCal);

	/* FIXME: button actually is only depressed during dropdown of the */
	/* calendar control and when the mouse is over the button window */
	//infoPtr->bCalDepressed = TRUE;

	/* recalculate the position of the monthcal popup */
	//if (infoPtr->dwStyle & DTS_RIGHTALIGN)
	//	pos.x = infoPtr->calbutton.left - (rcMonthCal.right - rcMonthCal.left);
	//else
		/* FIXME: this should be after the area reserved for the checkbox */
	//	pos.x = infoPtr->rcDraw.left;
	pos.x = 0;
	pos.y = 0;
	//pos.y = infoPtr->rcClient.bottom;
	OffsetRect(&rcMonthCal, pos.x, pos.y);
	::MapWindowPoints(m_hWnd, 0, (POINT *)&rcMonthCal, 2);
	::SetWindowPos(m_monthCalCtrl.m_hWnd, 0, rcMonthCal.left, rcMonthCal.top,
		rcMonthCal.right - rcMonthCal.left, rcMonthCal.bottom - rcMonthCal.top, 0);
	if (::IsWindowVisible(m_monthCalCtrl.m_hWnd)) {
		::ShowWindow(m_monthCalCtrl.m_hWnd, SW_HIDE);
		//infoPtr->bDropdownEnabled = FALSE;
		DATETIME_SendSimpleNotify(m_hWnd, GetParent()->m_hWnd, DTN_CLOSEUP);
	}
	else {
		//const SYSTEMTIME *lprgSysTimeArray = &infoPtr->date;
		//TRACE("update calendar %04d/%02d/%02d\n",
		//	lprgSysTimeArray->wYear, lprgSysTimeArray->wMonth, lprgSysTimeArray->wDay);
		::SendMessageW(m_monthCalCtrl.m_hWnd, MCM_SETCURSEL, 0, NULL);

		if (TRUE) {
			::ShowWindow(m_monthCalCtrl.m_hWnd, SW_SHOW);
			DATETIME_SendSimpleNotify(m_hWnd, GetParent()->m_hWnd, DTN_DROPDOWN);
		}
		//infoPtr->bDropdownEnabled = TRUE;
	}
	InvalidateRect(NULL, TRUE); 
	//AfxMessageBox(_T("Information retrieved"));
	//CDateTimeCtrl::OnLButtonDown(nFlags, point);
}


void ImprovedDatePicker::DoDataExchange(CDataExchange* pDX)
{
	// TODO: Add your specialized code here and/or call the base class

	CDateTimeCtrl::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MONTHCALCTRL1, m_monthCalCtrl);
}
