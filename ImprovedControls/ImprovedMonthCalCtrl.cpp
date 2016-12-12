// ImprovedMonthCalCtrl.cpp : implementation file
//
#include "ImprovedMonthCalCtrl.h"

//Prototype of function in improvedmonthcal.cpp
void MONTHCAL_Register(void);

IMPLEMENT_DYNAMIC(CImprovedMonthCalCtrl, CMonthCalCtrl)

CImprovedMonthCalCtrl::CImprovedMonthCalCtrl()
{
}

CImprovedMonthCalCtrl::~CImprovedMonthCalCtrl()
{
}

void   CImprovedMonthCalCtrl::RegisterControl()
{
	MONTHCAL_Register();
}

BEGIN_MESSAGE_MAP(CImprovedMonthCalCtrl, CMonthCalCtrl)
END_MESSAGE_MAP()


