#pragma once
#include <SDKDDKVer.h>
#include <afxdtctl.h>

#define MCSC_SELECTEDTEXT 6       // selection text color
#define MCSC_SELECTEDBK 7         // selection background color
#define MCSC_ABBREVIATIONSTEXT 8  // abbreviations text color
#define MCSC_ABBREVIATIONSBK 9    // abbreviations background color

class CMultipleMonthCalCtrl : public CMonthCalCtrl
{
	DECLARE_DYNAMIC(CMultipleMonthCalCtrl)

public:
	CMultipleMonthCalCtrl();
	virtual ~CMultipleMonthCalCtrl();

	static void RegisterControl();

	void    SetDefaultColors();
	void    SetDefaultFont();

	void    EnableMultiselect(int maxSelectCount = 0);
	void    DisableMultiselect();

protected:
	CFont m_font;

	DECLARE_MESSAGE_MAP()
public:

};


