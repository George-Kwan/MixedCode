//-----------------------------------------------------------------------------
//     Author : hiyohiyo
//       Mail : hiyohiyo@crystalmark.info
//        Web : http://openlibsys.org/
//    License : The modified BSD license
//
//                          Copyright 2009 OpenLibSys.org. All rights reserved.
//-----------------------------------------------------------------------------

#pragma once
#include "afxwin.h"



#define MSR_IA32_VMX_PROCBASED_CTLS_0x482   0x482
#define MSR_IA32_VMX_PROCBASED_CTLS2_0x48B  0x48B



// CVirtualCheckerDlg dialog
class CVirtualCheckerDlg : public CDialog
{
// Construction
public:
	CVirtualCheckerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VIRTUALCHECKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CBitmap m_BitmapBackground, m_BitmapVmx, m_BitmapSlat, m_BitmapX64, m_BitmapDep;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void SetClientRect(DWORD sizeX, DWORD sizeY, DWORD menuLine);

	// Intel
	BOOL IsIntelVtSupported();
	BOOL IsIntelVtEnabled();
	BOOL IsIntelEptSupported();
	BOOL IsIntelEptEnabled();

	// AMD
	BOOL IsAmdvSupported();
	BOOL IsAmdvEnabled();
	BOOL IsAmdRviSupported();
	BOOL IsAmdRviEnabled();

	// Intel/AMD
	BOOL IsDepSupported();
	BOOL IsDepEnabled();
	BOOL IsX64Supported();
	BOOL IsX64Enabled();

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CStatic m_Background, m_Vmx, m_Slat, m_X64, m_Dep;
};
