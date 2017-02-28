// DialogFormsDlg.h : header file
//

#pragma once
#include "afxwin.h"

// CDialogFormsDlg dialog
class CDialogFormsDlg : public CDialog
{
// Construction
public:
	CDialogFormsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DIALOGFORMS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void OnMaskInputRejected(System::Object^, 
		System::Windows::Forms::MaskInputRejectedEventArgs^);
public:
BEGIN_DELEGATE_MAP( CDialogFormsDlg )
	EVENT_DELEGATE_ENTRY( OnMaskInputRejected, System::Object ^, 
		System::Windows::Forms::MaskInputRejectedEventArgs^ )
END_DELEGATE_MAP()

// Implementation
protected:
	HICON m_hIcon;
	//CWinFormsControl<System::Windows::Forms::MaskedTextBox> m_MaskedEdit;
	CWinFormsControl<T3000Controls::SetPointsControl> m_MaskedEdit;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
