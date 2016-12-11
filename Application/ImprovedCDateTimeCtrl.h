
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "afxdtctl.h"


// CMFCApplication1Dlg dialog
class ImprovedCDateTimeCtrl : public CDateTimeCtrl
{
	// Construction
public:
	ImprovedCDateTimeCtrl();	// standard constructor
	afx_msg BOOL OnEraseBkgnd(
		CDC* pDC
	);
	afx_msg void OnPaint();

protected:
	
	CDateTimeCtrl m_datetime;
};
