#pragma once
#include "afxdtctl.h"

class ImprovedDatePicker : public CDateTimeCtrl
{
public:
	ImprovedDatePicker();
	~ImprovedDatePicker(); 
	

private:
//	CImprovedMonthCalCtrl m_monthCalCtrl;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnDtnDropdown(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void DoDataExchange(CDataExchange* pDX);
};

