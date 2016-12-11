#pragma once
#include <SDKDDKVer.h>
#include <afx.h>
#include <afxctl.h>
#include <afxdtctl.h>

// CImprovedMonthCalCtrl

class CImprovedMonthCalCtrl : public CMonthCalCtrl
{
	DECLARE_DYNAMIC(CImprovedMonthCalCtrl)

public:
	CImprovedMonthCalCtrl();
	virtual ~CImprovedMonthCalCtrl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnMcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


