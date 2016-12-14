#pragma once
#include <SDKDDKVer.h>
#include <afxdtctl.h>

#define MCS_RANGESELECT     MCS_MULTISELECT
#undef  MCS_MULTISELECT
#define MCS_MULTISELECT     0x1000

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

protected:
	DECLARE_MESSAGE_MAP()
};


