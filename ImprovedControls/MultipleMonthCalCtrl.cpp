// ImprovedMonthCalCtrl.cpp : implementation file
//
#include "MultipleMonthCalCtrl.h"

//Prototype of function in improvedmonthcal.cpp
void MONTHCAL_Register(void);

IMPLEMENT_DYNAMIC(CMultipleMonthCalCtrl, CMonthCalCtrl)

CMultipleMonthCalCtrl::CMultipleMonthCalCtrl()
{
}

CMultipleMonthCalCtrl::~CMultipleMonthCalCtrl()
{
}

void   CMultipleMonthCalCtrl::RegisterControl()
{
	MONTHCAL_Register();
}

void   CMultipleMonthCalCtrl::SetDefaultColors()
{
	//SetWindowTheme(pCtrl->m_hWnd, L" ", L" ");
	//m_datetime.SetMonthCalColor(MCSC_TITLEBK, RGB(0, 0, 128));
	//m_datetime.SetMonthCalStyle(MCS_NOSELCHANGEONNAV);
	//m_datetime.SetMonthCalColor(MCSC_MONTHBK, RGB(70, 170, 255));
	//m_datetime.SetMonthCalColor(MCSC_TEXT, RGB(250, 240, 50));
	//m_datetime.SetMonthCalColor(MCSC_TITLETEXT, RGB(255, 255, 0));
	//m_datetime.SetMonthCalColor(MCSC_BACKGROUND, RGB(255, 0, 0));
	//m_datetime.SetMonthCalColor(MCSC_TRAILINGTEXT, RGB(150, 200, 255));

	COLORREF monthTitleColor = RGB(219, 238, 244);
	COLORREF selectBgColor = RGB(148, 196, 206);
	COLORREF selectTextColor = RGB(10, 65, 122);
	/*
	m_datepicker.SetMonthCalColor(MCSC_BACKGROUND, RGB(255, 255, 255));
	m_datepicker.SetMonthCalColor(MCSC_TITLEBK, selectTextColor);
	m_datepicker.SetMonthCalColor(MCSC_MONTHBK, RGB(255, 255, 255));
	m_datepicker.SetMonthCalColor(MCSC_TEXT, RGB(0, 0, 0));
	m_datepicker.SetMonthCalColor(MCSC_TITLETEXT, monthTitleColor);
	m_datepicker.SetMonthCalColor(MCSC_TRAILINGTEXT, RGB(255, 255, 255));
	*/
}

void   CMultipleMonthCalCtrl::SetDefaultFont()
{
	/*
	HTHEME theme = ::GetWindowTheme(m_monthCalCtrl.m_hWnd);
	VERIFY(theme);

	LOGFONTW lf;
	HRESULT hr = GetThemeFont(theme, NULL,
		HP_HEADERITEM, HIS_NORMAL, TMT_CAPTIONFONT, &lf);
	if (FAILED(hr))
		hr = GetThemeSysFont(theme, TMT_CAPTIONFONT, &lf);
	*/

	LOGFONT lf = { 0 };
	memset(&lf, 0, sizeof(lf));
	lf.lfHeight = 16;
	lf.lfWidth = 6;
	lf.lfWeight = FW_EXTRALIGHT;
	//lf.lfPitchAndFamily = FIXED_PITCH | FF_DECORATIVE;
	//lf.lfQuality |= ANTIALIASED_QUALITY;

	_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("Segoe UI"));
	if (m_font.CreateFontIndirect(&lf))
	{
		// if successful, set the month calendar font
		SetFont(&m_font);
	}
}

void   CMultipleMonthCalCtrl::EnableMultiselect(int maxSelectCount)
{
	//SetMonthCalStyle(MCS_MULTISELECT);
	//ModifyStyleEx(NULL, MCS_MULTISELECT);
	SetMaxSelCount(maxSelectCount);
	::SetWindowLongW(m_hWnd, GWL_STYLE, 
		::GetWindowLongW(m_hWnd, GWL_STYLE) | MCS_MULTISELECT);
}

void   CMultipleMonthCalCtrl::DisableMultiselect()
{
	EnableMultiselect(1);
	::SetWindowLongW(m_hWnd, GWL_STYLE, 
		::GetWindowLongW(m_hWnd, GWL_STYLE) & ~MCS_MULTISELECT);
}

BEGIN_MESSAGE_MAP(CMultipleMonthCalCtrl, CMonthCalCtrl)
END_MESSAGE_MAP()
