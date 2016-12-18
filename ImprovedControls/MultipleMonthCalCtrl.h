#pragma once
#include <SDKDDKVer.h>
#include <afxdtctl.h>
#include <vector>

#define MCSC_SELECTEDTEXT      6  // selection text color
#define MCSC_SELECTEDBK        7  // selection background color
#define MCSC_ABBREVIATIONSTEXT 8  // abbreviations text color
#define MCSC_ABBREVIATIONSBK   9  // abbreviations background color
#define MCSC_ABBREVIATIONSLINE 10 // abbreviations line color

class CMultipleMonthCalCtrl : public CMonthCalCtrl
{
	DECLARE_DYNAMIC(CMultipleMonthCalCtrl)

public:
	CMultipleMonthCalCtrl();
	virtual ~CMultipleMonthCalCtrl();

	static void RegisterControl();

	void    SetOriginalColors();

	void    EnableMultiselect(int maxSelectCount = 0);
	void    DisableMultiselect();

	std::vector<SYSTEMTIME>	
	        GetSelection() const;

	/* This method set last date as first month in calendar.
	 * Use SetRange() after for select need range.
	 */
	void	SetSelection(const std::vector<SYSTEMTIME> & dates);

protected:

	DECLARE_MESSAGE_MAP()
public:

};


