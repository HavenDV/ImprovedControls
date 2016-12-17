
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

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
	//DDX_Control(pDX, IDC_DATETIMEPICKER1, m_datepicker);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_monthCalCtrl);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


void RenderWithBkgndColor(HWND hWnd, HDC hDC, COLORREF clrBkgnd)
{
	//Render control with the background color
	//'clrBkgnd' = color for the background (if control is enabled)

	//SOURCE:
	//  http://comp.os.ms-windows.programmer.win32.narkive.com/0H8cHhw1/setting-color-for-sysdatetimepick32-control

	RECT rect;
	::GetWindowRect(hWnd, &rect);
	::MapWindowPoints(NULL, hWnd, (LPPOINT)&rect, 2);
	long nWidth = rect.right - rect.left, nHeight = rect.bottom - rect.top;

	HDC hDCMem = ::CreateCompatibleDC(hDC);
	HBITMAP hBitmap = ::CreateBitmap(nWidth, nHeight, ::GetDeviceCaps(hDC, PLANES), ::GetDeviceCaps(hDC, BITSPIXEL), (const void *)NULL);
	if (hBitmap)
	{
		HBITMAP hBitmapOld = (HBITMAP)::SelectObject(hDCMem, hBitmap);

		//Render control itself
		::SendMessage(hWnd, WM_PRINT, (WPARAM)hDCMem, PRF_CLIENT | PRF_CHILDREN | PRF_NONCLIENT);

		//Only if we have the color
		if (clrBkgnd != NULL)
		{
			//Only if control is enabled
			if ((::GetWindowLongPtr(hWnd, GWL_STYLE) & (WS_VISIBLE | WS_DISABLED)) == (WS_VISIBLE | 0))
			{
#define ALLOWED_DIFF 20

				DWORD dwBkgClr = ::GetSysColor(COLOR_WINDOW);   //0xFFFFFF;

				DWORD br0 = dwBkgClr & 0xFF;
				DWORD br1 = (dwBkgClr & 0xFF00) >> 8;
				DWORD br2 = (dwBkgClr & 0xFF0000) >> (8 * 2);

				for (int y = 0; y < nHeight; y++)
				{
					for (int x = 0; x < nWidth; x++)
					{
						COLORREF clrPxl = ::GetPixel(hDCMem, x, y);

						DWORD r0 = clrPxl & 0xFF;
						DWORD r1 = (clrPxl & 0xFF00) >> 8;
						DWORD r2 = (clrPxl & 0xFF0000) >> (8 * 2);

						int nDiff_r0 = r0 - br0;
						int nDiff_r1 = r1 - br1;
						int nDiff_r2 = r2 - br2;

						if (abs(nDiff_r0) < ALLOWED_DIFF &&
							abs(nDiff_r1) < ALLOWED_DIFF &&
							abs(nDiff_r2) < ALLOWED_DIFF)
						{
							::SetPixel(hDCMem, x, y, clrBkgnd);
						}
					}
				}

			}

		}

		::BitBlt(hDC, rect.left, rect.top, nWidth, nHeight, hDCMem, 0, 0, SRCCOPY);

		::SelectObject(hDCMem, hBitmapOld);
		::DeleteObject(hBitmap);
	}

	::DeleteDC(hDCMem);
}

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
	sysFromtime.wYear += 1;
	sysEndtime.wDay = 31;
	sysEndtime.wMonth = 12;
	sysEndtime.wYear += 1;
	m_monthCalCtrl.SetRange(&sysFromtime, &sysEndtime);
	m_monthCalCtrl.SetDefaultColors();
	m_monthCalCtrl.SetDefaultFont();
	m_monthCalCtrl.EnableMultiselect(3);

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
		//CMonthCalCtrl *  month = m_datepicker.GetMonthCalCtrl();
		//if (month) {
		//	SetWindowTheme(month->m_hWnd, L" ", L" ");
			//month->SetColor(MCSC_TITLEBK, RGB(0, 0, 128));
			//month->SetColor(MCSC_TEXT, RGB(250, 240, 50));
		//}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

