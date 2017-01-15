#pragma once
#include <SDKDDKVer.h>
#include <afxdtctl.h>
#include <vector>

class CMultipleMonthCalCtrl : public CMonthCalCtrl
{
	DECLARE_DYNAMIC(CMultipleMonthCalCtrl)

public:
	CMultipleMonthCalCtrl();
	virtual ~CMultipleMonthCalCtrl();

	static void   RegisterControl();
	static void   UnregisterControl();

	void    SetOriginalColors();

	void    EnableMultiselect(int maxSelectCount = 0);
	void    DisableMultiselect();

	std::vector<SYSTEMTIME>	
	        GetSelection() const;

	/* This method set last date as first month in calendar.
	 * Use SetRange() after for select need range.
	 */
	void	SelectDate(const SYSTEMTIME & date);
	void	SelectDates(const std::vector<SYSTEMTIME> & dates);
	void	UnselectAll();

	BOOL	SetDayState(int count, MONTHDAYSTATE * states);

protected:

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
};


/*
* Utilities for T3000
*/

std::vector<SYSTEMTIME> ToSystemTimeVector(int monthCount, MONTHDAYSTATE * states, const SYSTEMTIME & start);
MONTHDAYSTATE*    ToDayStates(const std::vector<SYSTEMTIME> & days, int & mCount, SYSTEMTIME & start);

//Default - sunday
//0 - sunday, 6 - monday
std::vector<SYSTEMTIME>   GetAllYearDaysForDayOfWeek(int year, int dayOfWeek = 0);