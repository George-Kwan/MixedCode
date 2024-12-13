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

#include "OlsApiInitDef.h"

//-----------------------------------------------------------------------------
//
// Externs
//
//-----------------------------------------------------------------------------

// DLL
extern _GetDllStatus GetDllStatus;
extern _GetDllVersion GetDllVersion;
extern _GetDriverVersion GetDriverVersion;
extern _GetDriverType GetDriverType;

extern _InitializeOls InitializeOls;
extern _DeinitializeOls DeinitializeOls;

// CPU
extern _IsCpuid IsCpuid;
extern _IsMsr IsMsr;
extern _IsTsc IsTsc;

extern _Rdmsr Rdmsr;
extern _Cpuid Cpuid;
extern _Rdtsc Rdtsc;

extern _RdmsrTx RdmsrTx;
extern _CpuidTx CpuidTx;
extern _RdtscTx RdtscTx;

extern _RdmsrPx RdmsrPx;
extern _CpuidPx CpuidPx;
extern _RdtscPx RdtscPx;