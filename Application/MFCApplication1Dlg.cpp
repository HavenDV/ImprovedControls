
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "../ImprovedControls/MultipleMonthCalCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_monthCalCtrl);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SYSTEMTIME systime;
	::GetSystemTime(&systime);
	SYSTEMTIME sysFromtime;
	SYSTEMTIME sysEndtime;
	sysFromtime = systime;
	sysEndtime = systime;
	sysFromtime.wDay = 1;
	sysFromtime.wMonth = 1;
	sysEndtime.wDay = 31;
	sysEndtime.wMonth = 12;
	m_monthCalCtrl.SetRange(&sysFromtime, &sysEndtime);
	m_monthCalCtrl.SetOriginalColors();
	//m_monthCalCtrl.EnableMultiselect(15);
	std::vector<SYSTEMTIME> dates;
	dates.push_back(sysEndtime);
	dates.push_back(sysFromtime);
	//m_monthCalCtrl.SetCurSel(&sysEndtime);
	//m_monthCalCtrl.SetCurSel(&sysFromtime);
	//m_monthCalCtrl.UnselectAll();
	//int nCount = m_monthCalCtrl.GetMonthRange(&sysFromtime, &sysEndtime, GMR_DAYSTATE);

	int count = 12;
	MONTHDAYSTATE * states = ToDayStates(GetAllYearDaysForDayOfWeek(2016, 0), count, sysFromtime);
	dates = ToSystemTimeVector(count, states, sysFromtime);
	m_monthCalCtrl.SelectDates(dates);
	MONTHDAYSTATE * pstates = ToDayStates(dates, count, sysFromtime);
	m_monthCalCtrl.SetRange(&sysFromtime, &sysEndtime);
	m_monthCalCtrl.SetDayState(count, pstates);

	CMultipleMonthCalCtrl button;
	button.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON | DT_CENTER, CRect(5, 5, 55, 19), this, 111);

	button.SetRange(&sysFromtime, &sysEndtime);
	button.SetOriginalColors();
	button.EnableMultiselect(15);
	button.SetCurSel(&sysEndtime);
	button.SetCurSel(&sysFromtime);

	CMultipleMonthCalCtrl * newCtrl = new CMultipleMonthCalCtrl();
	newCtrl->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON | DT_CENTER, CRect(5, 5, 55, 19), this, 111);
	newCtrl->SetRange(&sysFromtime, &sysEndtime);
	newCtrl->SetOriginalColors();
	newCtrl->EnableMultiselect(15);
	newCtrl->SetCurSel(&sysEndtime);
	newCtrl->SetCurSel(&sysFromtime);
	delete newCtrl;


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

