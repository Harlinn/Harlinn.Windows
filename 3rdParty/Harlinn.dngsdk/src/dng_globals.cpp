/*****************************************************************************/
// Copyright 2006-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

#include "dng_globals.h"
#include "dng_simd_type.h"

/*****************************************************************************/

#if qDNGValidate

DNG_EXPORT bool gVerbose = false;

DNG_EXPORT uint32 gDumpLineLimit = 100;

#endif

/******************************************************************************/

DNG_EXPORT bool gDNGUseFakeTimeZonesInXMP = false;

/*****************************************************************************/

DNG_EXPORT bool gDNGShowTimers = true;

/*****************************************************************************/

DNG_EXPORT uint32 gDNGStreamBlockSize = 4096;

DNG_EXPORT uint32 gDNGMaxStreamBufferSize = 1024 * 1024;

/*****************************************************************************/

DNG_EXPORT bool gImagecore = false;

DNG_EXPORT bool gPrintTimings = false;

DNG_EXPORT bool gPrintAsserts = true;

DNG_EXPORT bool gBreakOnAsserts = true;

/*****************************************************************************/

// This is declared in dng_simd_type.h

DNG_EXPORT SIMDType gDNGMaxSIMD = Scalar;

/*****************************************************************************/
