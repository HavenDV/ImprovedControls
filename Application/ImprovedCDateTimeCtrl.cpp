
#include "stdafx.h"
#include "ImprovedCDateTimeCtrl.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ImprovedCDateTimeCtrl::ImprovedCDateTimeCtrl()
{
}

afx_msg BOOL ImprovedCDateTimeCtrl::OnEraseBkgnd(
	CDC* pDC
) {
	//return CWnd::OnEraseBkgnd(pDC);

	// Draw the icon
	//pDC->DrawText(L"Hello", 5, , DT_CENTER);
	pDC->FillRect(CRect(0,0,1000,1000), CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	return TRUE;
}


afx_msg void ImprovedCDateTimeCtrl::OnPaint()
{
	
}