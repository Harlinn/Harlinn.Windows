#pragma once
/******************************************************************************
 * $Id$
 *
 * Project:  OpenGIS Simple Features Reference Implementation
 * Purpose:  Client of geocoding service.
 * Author:   Even Rouault, <even dot rouault at spatialys.com>
 *
 ******************************************************************************
 * Copyright (c) 2012, Even Rouault <even dot rouault at spatialys.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#ifndef OGR_GEOCODING_H_INCLUDED
#define OGR_GEOCODING_H_INCLUDED

#include <port/cpl_port.h>
#include <ogr/ogr_api.h>

/**
 * \file ogr_geocoding.h
 *
 * C API for geocoding client.
 */

CPL_C_START

/** Opaque type for a geocoding session */
typedef struct _OGRGeocodingSessionHS *OGRGeocodingSessionH;

HGDAL_EXPORT OGRGeocodingSessionH OGRGeocodeCreateSession(char** papszOptions);

HGDAL_EXPORT void OGRGeocodeDestroySession(OGRGeocodingSessionH hSession);

HGDAL_EXPORT OGRLayerH OGRGeocode(OGRGeocodingSessionH hSession,
                             const char* pszQuery,
                             char** papszStructuredQuery,
                             char** papszOptions);

HGDAL_EXPORT OGRLayerH OGRGeocodeReverse(OGRGeocodingSessionH hSession,
                                    double dfLon, double dfLat,
                                    char** papszOptions);

HGDAL_EXPORT void OGRGeocodeFreeResult(OGRLayerH hLayer);

CPL_C_END

#endif // OGR_GEOCODING_H_INCLUDED