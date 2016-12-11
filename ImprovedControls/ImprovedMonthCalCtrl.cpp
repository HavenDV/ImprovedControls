// ImprovedMonthCalCtrl.cpp : implementation file
//
#include "ImprovedMonthCalCtrl.h"
#include <fstream>
#include <string>


// CImprovedMonthCalCtrl

IMPLEMENT_DYNAMIC(CImprovedMonthCalCtrl, CMonthCalCtrl)

CImprovedMonthCalCtrl::CImprovedMonthCalCtrl()
{
}

CImprovedMonthCalCtrl::~CImprovedMonthCalCtrl()
{
}


BEGIN_MESSAGE_MAP(CImprovedMonthCalCtrl, CMonthCalCtrl)
	ON_NOTIFY_REFLECT(MCN_SELCHANGE, &CImprovedMonthCalCtrl::OnMcnSelchange)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CImprovedMonthCalCtrl message handlers



static const WCHAR themeClass[] = { 'S','c','r','o','l','l','b','a','r',0 };

void CImprovedMonthCalCtrl::OnMcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);

	//::SetWindowTheme(m_hWnd, themeClass, L" ");
	//AfxMessageBox(_T("OnMcnSelchange"));

	*pResult = 0;
}


BOOL CImprovedMonthCalCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	// get clipping rectangle
	//CRect rcClip;
	//CBrush brushRed(RGB(255,0,0));
	//pDC->GetClipBox(rcClip);
	// fill rectangle using a given brush
	//pDC->FillRect(rcClip, &brushRed);
	//return TRUE; // returns non-zero to prevent further erasing

	return CMonthCalCtrl::OnEraseBkgnd(pDC);
}


HBRUSH CImprovedMonthCalCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMonthCalCtrl::OnCtlColor(pDC, pWnd, nCtlColor);

	CBrush brushRed(RGB(255, 0, 0));
	//HBRUSH hbr = (HBRUSH)brushRed;
	return hbr;
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
		// just return a not NULL brush handle
		hbr = (HBRUSH)brushRed;
		break;
	case CTLCOLOR_STATIC:
	{
		// set text color, transparent back node then 
		//pDC->SetTextColor(m_crStaticText);
		pDC->SetBkMode(TRANSPARENT);
		// return a not NULL brush handle
		hbr = (HBRUSH)brushRed;
	}
	break;
	default:
		// do the default processing
		//hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		break;
	}
	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

//int unused[373];
//CRect selectionRect;

typedef struct
{
	int year;
	int month;
	int day;
	int hz;
	int hour;
	int minute;
	int second;
	int unused[3];
} TIME_INFO, *LPTIME_INFO;

typedef struct
{
	int unused[187];
	CRect        rects[16];
	int unused3[5];
	TIME_INFO    times[10]; //256 to 356
	int unused2[17];
	CRect selectionRect;
	int buffer[12555];
} MONTHCAL_INFO, *LPMONTHCAL_INFO;

void CImprovedMonthCalCtrl::OnPaint()
{
	CRect rcClip;
	this->GetUpdateRect(rcClip);
	//Default();  // we want all the default drawing
	CMonthCalCtrl::OnPaint();

	MONTHCAL_INFO *infoPtr;
	infoPtr = (MONTHCAL_INFO *)::GetWindowLongPtr(m_hWnd, 0);
	VERIFY(infoPtr);

	auto func = &::DrawThemeBackground;

	//280-300 left button and title
	//260-280 systemtime 1 and right button
	//buffer[299] title string?
	//for (auto i = 296; i<296; ++i)
	//infoPtr->buffer[i] = 0;
	//CCalendar * cal = (CCalendar*)this;
	//CPaintDC
	CClientDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CMonthCalCtrl::OnPaint() for painting messages
	
	//dc.GetClipBox(rcClip);
	// fill rectangle using a given brush
	//for (auto i = rcClip.left; i < rcClip.right; ++i)
	//	for (auto j = rcClip.top; j < rcClip.bottom; ++j)	
	//auto need = RGB(255, 232, 205);

	COLORREF monthTitleColor = RGB(219, 238, 244);
	COLORREF selectBgColor = RGB(148, 196, 206);
	COLORREF selectTextColor = RGB(10, 65, 122);
	CBrush brushSelectBg(selectTextColor);
	COLORREF crBkgnd = dc.GetBkColor();
	
	SYSTEMTIME time;
	CMonthCalCtrl::GetCurSel(&time);
	//wchar_t dayString[3];
	//swprintf_s(dayString, L"%d", time.wDay);

	//dc.TextOut(rcClip.left, rcClip.top, dayString);
	
	//	dc.FillRect(infoPtr->buffer[59], &brushSelectBg);
	//dc.FillRect(infoPtr->selectionRect, &brushSelectBg);
	//
	//	dc.SetPixel(i, j, RGB(255, 0, 0));
	//dc.TextOut(0, 0, L"TextOut Samples");
	//CDC dcMem;
	// create memory DC
	//dcMem.CreateCompatibleDC(&dc);
	// select the source bitmao into the memory DC
	//CBitmap* pOldBitmap = (CBitmap*)dcMem.SelectObject(&m_bmpEarth);
	// get the bitmap data
	//BITMAP bmp = { 0 };
	//m_bmpEarth.GetBitmap(&bmp);
	// transfer the bitmap into paint DC using a transparent color  
	//dc.TransparentBlt(
	//	10, 10, bmp.bmWidth, bmp.bmHeight, // destination coordinates and sizes
	//	&dcMem,                            // source DC
	///	0, 0, bmp.bmWidth, bmp.bmHeight,   // source coordinates and sizes
	//	RGB(255, 0, 0));                   // transparent color
										   // restore DC / free GDI objects 
	//dcMem.SelectObject(pOldBitmap);
}

//13 14
void CImprovedMonthCalCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default


	CMonthCalCtrl::OnLButtonDown(nFlags, point);

	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);

	wchar_t x[7];
	swprintf_s(x, L"%d", pt.y);
	//AfxMessageBox(x);
}


int CImprovedMonthCalCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMonthCalCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}
