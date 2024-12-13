//-----------------------------------------------------------------------------
//     Author : hiyohiyo
//       Mail : hiyohiyo@crystalmark.info
//        Web : http://openlibsys.org/
//    License : The modified BSD license
//
//                          Copyright 2009 OpenLibSys.org. All rights reserved.
//-----------------------------------------------------------------------------

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CVirtualCheckerApp:
// See VirtualChecker.cpp for the implementation of this class
//

class CVirtualCheckerApp : public CWinApp
{
public:
	CVirtualCheckerApp();

// Overrides
	public:
	virtual BOOL InitInstance();

	OSVERSIONINFO m_OsVer;
	BOOL m_IsNT;

#ifdef RUN_TIME_DYNAMIC_LINKING
	HMODULE m_hOpenLibSys;
#endif

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CVirtualCheckerApp theApp;