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

BEGIN_MESSAGE_MAP(CMultipleMonthCalCtrl, CMonthCalCtrl)
END_MESSAGE_MAP()


