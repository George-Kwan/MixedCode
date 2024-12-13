//-----------------------------------------------------------------------------
//     Author : hiyohiyo
//       Mail : hiyohiyo@crystalmark.info
//        Web : http://openlibsys.org/
//    License : The modified BSD license
//
//                          Copyright 2009 OpenLibSys.org. All rights reserved.
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "VirtualChecker.h"
#include "VirtualCheckerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "OlsDef.h"
#ifdef RUN_TIME_DYNAMIC_LINKING
#include "OlsApiInitExt.h"
#else // for Load-Time Dynamic Linking
#include "OlsApi.h"
#endif

// CVirtualCheckerDlg dialog

CVirtualCheckerDlg::CVirtualCheckerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVirtualCheckerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVirtualCheckerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BACKGROUND, m_Background);
	DDX_Control(pDX, IDC_VMX, m_Vmx);
	DDX_Control(pDX, IDC_SLAT, m_Slat);
	DDX_Control(pDX, IDC_X64, m_X64);
	DDX_Control(pDX, IDC_DEP, m_Dep);
}

BEGIN_MESSAGE_MAP(CVirtualCheckerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CVirtualCheckerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CVirtualCheckerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CVirtualCheckerDlg message handlers

BOOL CVirtualCheckerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	if(IsIntelVtSupported() || IsAmdvSupported())
	{
		if(IsIntelVtEnabled() || IsAmdvEnabled())
		{
			m_BitmapVmx.LoadBitmap(MAKEINTRESOURCE(IDB_ENABLED));
		}
		else
		{
			m_BitmapVmx.LoadBitmap(MAKEINTRESOURCE(IDB_DISABLED));
		}
	}
	else
	{
		m_BitmapVmx.LoadBitmap(MAKEINTRESOURCE(IDB_UNSUPPORTED));
	}

	if(IsIntelEptSupported())
	{
		if(IsIntelEptEnabled())
		{
			m_BitmapSlat.LoadBitmap(MAKEINTRESOURCE(IDB_ENABLED));
		}
		else
		{
			m_BitmapSlat.LoadBitmap(MAKEINTRESOURCE(IDB_DISABLED_UNSUPPORTED));
		}
	}
	else if(IsAmdRviSupported())
	{
		m_BitmapSlat.LoadBitmap(MAKEINTRESOURCE(IDB_SUPPORTED));
	}
	else
	{
		m_BitmapSlat.LoadBitmap(MAKEINTRESOURCE(IDB_UNSUPPORTED));
	}

	if(IsX64Supported())
	{
		if(IsX64Enabled())
		{
			m_BitmapX64.LoadBitmap(MAKEINTRESOURCE(IDB_ENABLED));
		}
		else
		{
			m_BitmapX64.LoadBitmap(MAKEINTRESOURCE(IDB_DISABLED));
		}
		m_BitmapX64.LoadBitmap(MAKEINTRESOURCE(IDB_SUPPORTED));
	}
	else
	{
		m_BitmapX64.LoadBitmap(MAKEINTRESOURCE(IDB_UNSUPPORTED));
	}

	if(IsDepSupported())
	{
		if(IsDepEnabled())
		{
			m_BitmapDep.LoadBitmap(MAKEINTRESOURCE(IDB_ENABLED));
		}
		else
		{
			m_BitmapDep.LoadBitmap(MAKEINTRESOURCE(IDB_DISABLED));
		}
	}
	else
	{
		m_BitmapDep.LoadBitmap(MAKEINTRESOURCE(IDB_DISABLED_UNSUPPORTED));
	}

	m_BitmapBackground.LoadBitmap(MAKEINTRESOURCE(IDB_BACKGROUND));
	m_Background.MoveWindow(0, 0, 480, 280, 0);
	m_Vmx.MoveWindow(20, 60, 200, 60, 0);
	m_Slat.MoveWindow(260, 60, 200, 60, 0);
	m_X64.MoveWindow(20, 200, 200, 60, 0);
	m_Dep.MoveWindow(260, 200, 200, 60, 0);

	SetClientRect(480, 280, 0);
	CenterWindow();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVirtualCheckerDlg::SetClientRect(DWORD sizeX, DWORD sizeY, DWORD menuLine)
{
	RECT rc;
	RECT clientRc;
	rc.left = 0;
	rc.top = 0;
	rc.right = sizeX;
	rc.bottom = sizeY;

	GetClientRect(&clientRc);
	if(clientRc.bottom - clientRc.top == sizeY && clientRc.right - clientRc.left == sizeX)
	{
		return;
	}

	WINDOWINFO wi = {0};
	wi.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(&wi);

// 0x94CE004C

	AdjustWindowRect(&rc, wi.dwStyle, TRUE);
	SetWindowPos(&CWnd::wndTop, -1, -1,
		rc.right - rc.left,
		rc.bottom - rc.top + GetSystemMetrics(SM_CYMENU) * menuLine,
		SWP_NOMOVE);

	GetClientRect(&clientRc);
	if(clientRc.bottom - clientRc.top != sizeY)
	{
		SetWindowPos(&CWnd::wndTop , -1, -1, 
			rc.right - rc.left,
			rc.bottom - rc.top + GetSystemMetrics(SM_CYMENU) * menuLine + sizeY - (clientRc.bottom - clientRc.top), SWP_NOMOVE);	
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVirtualCheckerDlg::OnPaint()
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
		CDialog::OnPaint();

		m_Background.SetBitmap(m_BitmapBackground);
		m_Vmx.SetBitmap(m_BitmapVmx);
		m_Slat.SetBitmap(m_BitmapSlat);
		m_X64.SetBitmap(m_BitmapX64);
		m_Dep.SetBitmap(m_BitmapDep);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVirtualCheckerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVirtualCheckerDlg::OnBnClickedOk()
{
//	OnOK();
}

void CVirtualCheckerDlg::OnBnClickedCancel()
{
	OnCancel();
}

BOOL CVirtualCheckerDlg::IsIntelVtSupported()
{
	DWORD eax, ebx, ecx, edx;
	if(CpuidPx(0x1, 0, &eax, &ebx, &ecx, &edx, 1) && (ecx & (1 << 5)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CVirtualCheckerDlg::IsIntelVtEnabled()
{
	DWORD eax, edx;
	if(RdmsrPx(0x3A, &eax, &edx, 1) && (eax & (1 << 2)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CVirtualCheckerDlg::IsIntelEptSupported()
{
	DWORD eax, edx;
	if(RdmsrPx(MSR_IA32_VMX_PROCBASED_CTLS_0x482, &eax, &edx, 1) && ((edx & (1 << 31))))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CVirtualCheckerDlg::IsIntelEptEnabled()
{
	DWORD eax, edx;
	if(RdmsrPx(MSR_IA32_VMX_PROCBASED_CTLS2_0x48B, &eax, &edx, 1) && ((edx & (1 << 1)) || (edx & (1 << 5))))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CVirtualCheckerDlg::IsAmdvSupported()
{
	DWORD eax, ebx, ecx, edx;
	CpuidPx(0x80000000, 0, &eax, &ebx, &ecx, &edx, 1);
	if(eax < 0x80000001)
	{
		return FALSE;
	}
	if(CpuidPx(0x80000001, 0, &eax, &ebx, &ecx, &edx, 1) && (ecx & (1 << 2)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CVirtualCheckerDlg::IsAmdvEnabled()
{
	DWORD eax, edx;
	if(RdmsrPx(0xC0010114, &eax, &edx, 1) && (! (eax & (1 << 4))))
//	if(RdmsrPx(0xC0000080, &eax, &edx, 1) && (eax & (1 << 12)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CVirtualCheckerDlg::IsAmdRviSupported()
{
	DWORD eax, ebx, ecx, edx;
	CpuidPx(0x80000000, 0, &eax, &ebx, &ecx, &edx, 1);
	if(eax < 0x8000000A)
	{
		return FALSE;
	}
	if(CpuidPx(0x8000000A, 0, &eax, &ebx, &ecx, &edx, 1) && (edx & (1 << 0)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CVirtualCheckerDlg::IsDepSupported()
{
	DWORD eax, ebx, ecx, edx;
	CpuidPx(0x80000000, 0, &eax, &ebx, &ecx, &edx, 1);
	if(eax < 0x80000001)
	{
		return FALSE;
	}
	if(CpuidPx(0x80000001, 0, &eax, &ebx, &ecx, &edx, 1) && (edx & (1 << 20)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CVirtualCheckerDlg::IsDepEnabled()
{
	DWORD eax, edx;
	if(RdmsrPx(0xC0000080, &eax, &edx, 1) && (eax & (1 << 11)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CVirtualCheckerDlg::IsX64Supported()
{
	DWORD eax, ebx, ecx, edx;
	CpuidPx(0x80000000, 0, &eax, &ebx, &ecx, &edx, 1);
	if(eax < 0x80000001)
	{
		return FALSE;
	}
	if(CpuidPx(0x80000001, 0, &eax, &ebx, &ecx, &edx, 1) && (edx & (1 << 29)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CVirtualCheckerDlg::IsX64Enabled()
{
	DWORD eax, edx;
	if(RdmsrPx(0xC0000080, &eax, &edx, 1) && (eax & (1 << 10)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}