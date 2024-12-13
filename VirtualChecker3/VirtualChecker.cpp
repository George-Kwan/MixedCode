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

#include "IsCurrentUserLocalAdministrator.h"

#include "OlsDef.h"
#ifdef RUN_TIME_DYNAMIC_LINKING 
#include "OlsApiInit.h"
#else // for Load-Time Dynamic Linking
#include "OlsApi.h"
#ifdef _M_X64
#pragma comment(lib, "WinRing0X64.lib")
#else
#pragma comment(lib, "WinRing0.lib")
#endif
#endif


//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------
static BOOL RunAsRestart();

// CVirtualCheckerApp

BEGIN_MESSAGE_MAP(CVirtualCheckerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CVirtualCheckerApp construction

CVirtualCheckerApp::CVirtualCheckerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CVirtualCheckerApp object

CVirtualCheckerApp theApp;


// CVirtualCheckerApp initialization

BOOL CVirtualCheckerApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();
	AfxEnableControlContainer();

	ZeroMemory(&m_OsVer, sizeof(OSVERSIONINFO));
	m_OsVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&m_OsVer);

// for Windows NT family
	if(m_OsVer.dwPlatformId == VER_PLATFORM_WIN32_NT && ! IsCurrentUserLocalAdministrator())
	{
		if(m_OsVer.dwMajorVersion < 6)
		{
			AfxMessageBox(_T("CrystalDiskInfo is required Administrator Privileges."));
		}
		RunAsRestart();
		return FALSE;
	}

#ifdef RUN_TIME_DYNAMIC_LINKING
	m_hOpenLibSys = NULL;
	if(InitOpenLibSys(&m_hOpenLibSys) != TRUE)
	{
		AfxMessageBox(_T("DLL Load Error!!"));
		return FALSE;
	}
#else
	if(! InitializeOls())
	{
		AfxMessageBox(_T("InitializeOls() Error!!"));
		return FALSE;
	}
#endif

	switch(GetDllStatus())
	{
	case OLS_DLL_NO_ERROR:
		break;
	case OLS_DLL_UNSUPPORTED_PLATFORM:
		AfxMessageBox(_T("DLL Status Error!! UNSUPPORTED_PLATFORM"));
		return FALSE;
		break;
	case OLS_DLL_DRIVER_NOT_LOADED:
		AfxMessageBox(_T("DLL Status Error!! DRIVER_NOT_LOADED"));
		return FALSE;
		break;
	case OLS_DLL_DRIVER_NOT_FOUND:
		AfxMessageBox(_T("DLL Status Error!! DRIVER_NOT_FOUND"));
		return FALSE;
		break;
	case OLS_DLL_DRIVER_UNLOADED:
		AfxMessageBox(_T("DLL Status Error!! DRIVER_UNLOADED"));
		return FALSE;
		break;
	case OLS_DLL_DRIVER_NOT_LOADED_ON_NETWORK:
		AfxMessageBox(_T("DLL Status Error!! DRIVER_NOT_LOADED_ON_NETWORK"));
		return FALSE;
		break;
	case OLS_DLL_UNKNOWN_ERROR:
	default:
		AfxMessageBox(_T("DLL Status Error!! UNKNOWN_ERROR"));
		return FALSE;
		break;
	}

	CVirtualCheckerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

#ifdef RUN_TIME_DYNAMIC_LINKING
	DeinitOpenLibSys(&m_hOpenLibSys);
#else
	DeinitializeOls();
#endif

	return FALSE;
}


BOOL RunAsRestart()
{
	int count;
#ifdef _UNICODE
	TCHAR** cmd = ::CommandLineToArgvW(::GetCommandLine(), &count);
#else
	TCHAR** cmd = ::__argv;
	count = ::__argc;
#endif

	if(count < 2 || _tcscmp(cmd[1], _T("runas")) != 0)
	{
		TCHAR path[MAX_PATH];
		::GetModuleFileName(NULL, path, MAX_PATH);
		if(::ShellExecute(NULL, _T("runas"), path, _T("runas"), NULL, SW_SHOWNORMAL)
			> (HINSTANCE)32)
		{
			return TRUE;
		}
	}
	return FALSE;
}
