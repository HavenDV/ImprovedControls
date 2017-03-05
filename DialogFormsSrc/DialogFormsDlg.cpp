// DialogFormsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DialogForms.h"
#include "DialogFormsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDialogFormsDlg dialog

CDialogFormsDlg::CDialogFormsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFormsDlg::IDD, pParent)
{}

void CDialogFormsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_ManagedControl(pDX, IDC_SET_POINTS, m_setPointsControl);
	DDX_ManagedControl(pDX, IDC_SLIDERCONTROL1, m_sliderControl);
}

BEGIN_MESSAGE_MAP(CDialogFormsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

// CDialogFormsDlg message handlers

BOOL CDialogFormsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	//m_MaskedEdit->MaskInputRejected +=
	//	MAKE_DELEGATE( System::Windows::Forms::MaskInputRejectedEventHandler, OnMaskInputRejected) ;
	return TRUE;  
}

void CDialogFormsDlg::OnPaint()
{
	CDialog::OnPaint();
}

void CDialogFormsDlg::OnMaskInputRejected(System::Object^, 
		System::Windows::Forms::MaskInputRejectedEventArgs^ args)
{}