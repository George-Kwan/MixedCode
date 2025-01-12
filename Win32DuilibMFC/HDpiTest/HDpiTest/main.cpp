//#include "stdafx.h"


#include "resource.h"
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h> //包含头文件  
// 导入静态库  
#pragma comment(lib, "Comctl32.lib")  
// 
//#include <uxtheme.h>
//#pragma comment(lib, "UxTheme.lib")


#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

BOOL CenterWindow(HWND hwndWindow)
{
	HWND hwndParent = GetParent(hwndWindow);
	hwndParent = hwndParent ? hwndParent : GetDesktopWindow();
	RECT rectWindow, rectParent;

	// make the window relative to its parent
	//if ((hwndParent = GetParent(hwndWindow)) != NULL)
	{
		GetWindowRect(hwndWindow, &rectWindow);
		GetWindowRect(hwndParent, &rectParent);

		int nWidth = rectWindow.right - rectWindow.left;
		int nHeight = rectWindow.bottom - rectWindow.top;

		int nX = ((rectParent.right - rectParent.left) - nWidth) / 2 + rectParent.left;
		int nY = ((rectParent.bottom - rectParent.top) - nHeight) / 2 + rectParent.top;

		int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		// make sure that the dialog box never moves outside of the screen
		if (nX < 0) nX = 0;
		if (nY < 0) nY = 0;
		if (nX + nWidth > nScreenWidth) nX = nScreenWidth - nWidth;
		if (nY + nHeight > nScreenHeight) nY = nScreenHeight - nHeight;

		MoveWindow(hwndWindow, nX, nY, nWidth, nHeight, FALSE);

		return TRUE;
	}

	return FALSE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id) {

	case IDCANCEL:
		//MessageBox(hwnd, L"IDCANCEL", L"tip", 48);
		DestroyWindow(hwnd);
		return;
	case IDOK:
		//MessageBox(hwnd, L"now test", L"tip", 48);
		return;
	}
}

LRESULT OnInitdialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	//MessageBox(hwnd, L"WM_INITDIALOG", L"tip", 48);
	return 0L;
}

void OnDestroy(HWND hwnd)
{
	//MessageBox(hwnd, L"WM_DESTROY", L"tip", 48);
	PostQuitMessage(0);
}



LRESULT OnDPIChanged(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	MessageBox(hwnd, L"WM_DPICHANGED", L"tip", 48);
	return 0L;
}


HBRUSH OnCtlColorStatic(HWND hwnd, HDC wParam, HWND lParam, UINT /*nCtlColor*/)
{
	SetTextColor((HDC)wParam, RGB(0, 255, 0));
	SetBkColor((HDC)wParam, RGB(10, 10, 10));
	return CreateSolidBrush(RGB(10, 10, 10));
}


BOOL CALLBACK HostDialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	/*switch (msg) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case IDCANCEL:
			MessageBox(h, L"IDCANCEL", L"tip", 48);
			DestroyWindow(h);
			return 1;
		case IDOK:
			MessageBox(hwnd, L"now test", L"tip", 48);
			return 1;
		}
	case WM_INITDIALOG:
		MessageBox(h, L"WM_INITDIALOG", L"tip", 48);
		break;

	case WM_DESTROY:
		MessageBox(h, L"WM_DESTROY", L"tip", 48);
		PostQuitMessage(0);
		break;		
	}*/

	//return HANDLE_WM_DESTROY(hwnd, wParam, lParam, OnDestroy);

	switch (msg) {
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitdialog);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hwnd, WM_CTLCOLORSTATIC, OnCtlColorStatic);
		//HANDLE_MSG(hwnd, WM_DPICHANGED, OnDPIChanged);
		//case 0x02E0:             //#define WM_DPICHANGED                   0x02E0
		//{
		//	OnDPIChanged(hwnd, msg, wParam, lParam);
		//}break;
	}

	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
	//SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	HMODULE hModule = ::LoadLibraryW(L"User32.dll");
	if (hModule) {
		typedef void* (WINAPI* LPSetThreadDpiAwarenessContext)(void*);
		LPSetThreadDpiAwarenessContext SetThreadDpiAwarenessContext = (LPSetThreadDpiAwarenessContext)GetProcAddress(hModule, "SetThreadDpiAwarenessContext");
		if (SetThreadDpiAwarenessContext) {
			SetThreadDpiAwarenessContext((void*)-4);
		}
	}

	//https://learn.microsoft.com/zh-cn/windows/win32/api/commctrl/nf-commctrl-initcommoncontrolsex
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_STANDARD_CLASSES | ICC_COOL_CLASSES | ICC_BAR_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	//SetWindowTheme(hwndList, L"Explorer", NULL);
	//::DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), nullptr, &HostDialogProc);
	HWND hHostDlg = CreateDialogParamW(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), nullptr, HostDialogProc, 0);
	if (!hHostDlg)
	{
		return FALSE;
	}

	//https://learn.microsoft.com/zh-cn/windows/win32/api/uxtheme/nf-uxtheme-setwindowtheme?redirectedfrom=MSDN
	//SetWindowTheme(hHostDlg, L"Explorer", NULL);

	//CenterWindow(hHostDlg);
	SetDlgItemTextW(hHostDlg, IDC_EDIT_OUTPUT, L"Fonts DPI Text");

	ShowWindow(hHostDlg, nCmdShow);

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;





    return 0;
}