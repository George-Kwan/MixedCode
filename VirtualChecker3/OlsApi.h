//-----------------------------------------------------------------------------
//     Author : hiyohiyo
//       Mail : hiyohiyo@crystalmark.info
//        Web : http://openlibsys.org/
//    License : The modified BSD license
//
//                     Copyright 2007-2010 OpenLibSys.org. All rights reserved.
//-----------------------------------------------------------------------------
// for WinRing0 2.0.x

#pragma once

/******************************************************************************
**
** DLL Information
**
******************************************************************************/

//-----------------------------------------------------------------------------
// GetDllStatus
//-----------------------------------------------------------------------------
DWORD // DLL Status, defined OLS_DLL_****
WINAPI GetDllStatus();

//-----------------------------------------------------------------------------
// GetDllVersion
//-----------------------------------------------------------------------------
DWORD // DLL Version, defined OLS_VERSION
WINAPI GetDllVersion(
	PBYTE major,		// major version
	PBYTE minor,		// minor version
	PBYTE revision,		// revision
	PBYTE release		// release/build
);

//-----------------------------------------------------------------------------
// GetDriverVersion
//-----------------------------------------------------------------------------
DWORD // Device Driver Version, defined OLS_DRIVER_VERSION
WINAPI GetDriverVersion(
	PBYTE major,		// major version
	PBYTE minor,		// minor version
	PBYTE revision,		// revision
	PBYTE release		// release/build
);

//-----------------------------------------------------------------------------
// GetDriverType
//-----------------------------------------------------------------------------
DWORD // Device Driver Type, defined OLS_DRIVER_TYPE_****
WINAPI GetDriverType();

//-----------------------------------------------------------------------------
// InitializeOls
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI InitializeOls();

//-----------------------------------------------------------------------------
// DeinitializeOls
//-----------------------------------------------------------------------------
VOID WINAPI DeinitializeOls();

/******************************************************************************
**
** CPU
**
******************************************************************************/

//-----------------------------------------------------------------------------
// IsCpuid
//-----------------------------------------------------------------------------
BOOL // TRUE: support CPUID instruction, FALSE: not support CPUID instruction
WINAPI IsCpuid();

//-----------------------------------------------------------------------------
// IsMsr
//-----------------------------------------------------------------------------
BOOL // TRUE: support MSR(Model-Specific Register), FALSE: not support MSR
WINAPI IsMsr();

//-----------------------------------------------------------------------------
// IsTsc
//-----------------------------------------------------------------------------
BOOL // TRUE: support TSC(Time Stamp Counter), FALSE: not support TSC
WINAPI IsTsc();

//-----------------------------------------------------------------------------
// Rdmsr
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI Rdmsr(
	DWORD index,					// MSR index
	PDWORD eax,						// bit  0-31
	PDWORD edx						// bit 32-63
);

//-----------------------------------------------------------------------------
// RdmsrTx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI RdmsrTx(
	DWORD index,					// MSR index
	PDWORD eax,						// bit  0-31
	PDWORD edx,						// bit 32-63
	DWORD_PTR threadAffinityMask
);

//-----------------------------------------------------------------------------
// RdmsrPx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI RdmsrPx(
	DWORD index,					// MSR index
	PDWORD eax,						// bit  0-31
	PDWORD edx,						// bit 32-63
	DWORD_PTR processAffinityMask
);

//-----------------------------------------------------------------------------
// Cpuid
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI Cpuid(
	DWORD indexEax,
	DWORD indexEcx,
	PDWORD eax,
	PDWORD ebx,
	PDWORD ecx,
	PDWORD edx
);

//-----------------------------------------------------------------------------
// CpuidTx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI CpuidTx(
	DWORD indexEax,
	DWORD indexEcx,
	PDWORD eax,
	PDWORD ebx,
	PDWORD ecx,
	PDWORD edx,
	DWORD_PTR threadAffinityMask
);

//-----------------------------------------------------------------------------
// CpuidPx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI CpuidPx(
	DWORD indexEax,
	DWORD indexEcx,
	PDWORD eax,
	PDWORD ebx,
	PDWORD ecx,
	PDWORD edx,
	DWORD_PTR processAffinityMask
);

//-----------------------------------------------------------------------------
// Rdtsc
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI Rdtsc(
	PDWORD eax,						// bit  0-31
	PDWORD edx						// bit 32-63
);

//-----------------------------------------------------------------------------
// RdmsrTx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI RdtscTx(
	PDWORD eax,						// bit  0-31
	PDWORD edx,						// bit 32-63
	DWORD_PTR threadAffinityMask
);

//-----------------------------------------------------------------------------
// RdmsrPx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI RdtscPx(
	PDWORD eax,						// bit  0-31
	PDWORD edx,						// bit 32-63
	DWORD_PTR processAffinityMask
);