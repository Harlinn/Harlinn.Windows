#pragma once
/**********************************************************************
 * Project:  CPL - Common Portability Library
 * Purpose:  Microsoft Azure Storage Blob routines
 * Author:   Even Rouault <even.rouault at spatialys.com>
 *
 **********************************************************************
 * Copyright (c) 2017, Even Rouault <even.rouault at spatialys.com>
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

#ifndef CPL_AZURE_INCLUDED_H
#define CPL_AZURE_INCLUDED_H

#include "..\hgdaldef.h"

#ifndef DOXYGEN_SKIP

#ifdef HAVE_CURL

#include <curl/curl.h>
#include <port/cpl_http.h>
#include "cpl_aws.h"
#include <map>

class VSIAzureBlobHandleHelper final: public IVSIS3LikeHandleHelper
{
        CPLString m_osURL;
        CPLString m_osEndpoint;
        CPLString m_osBucket;
        CPLString m_osObjectKey;
        CPLString m_osStorageAccount;
        CPLString m_osStorageKey;
        CPLString m_osSAS;
        bool      m_bUseHTTPS;
        bool      m_bFromManagedIdendities;

        enum class Service
        {
            BLOB,
            ADLS,
        };

        HGDAL_EXPORT static bool     GetConfiguration(CSLConstList papszOptions,
                                         Service eService,
                                         bool& bUseHTTPS,
                                         CPLString& osEndpoint,
                                         CPLString& osStorageAccount,
                                         CPLString& osStorageKey,
                                         CPLString& osSAS,
                                         bool& bFromManagedIdentities);

        HGDAL_EXPORT static bool     GetConfigurationFromManagedIdentities(
                                                    CPLString& osAccessToken);

        HGDAL_EXPORT static CPLString BuildURL(const CPLString& osEndpoint,
                                  const CPLString& osStorageAccount,
                                  const CPLString& osBucket,
                                  const CPLString& osObjectKey,
                                  const CPLString& osSAS,
                                  bool bUseHTTPS);

        HGDAL_EXPORT void RebuildURL() override;

    public:
        HGDAL_EXPORT VSIAzureBlobHandleHelper(const CPLString& osEndpoint,
                                 const CPLString& osBucket,
                                 const CPLString& osObjectKey,
                                 const CPLString& osStorageAccount,
                                 const CPLString& osStorageKey,
                                 const CPLString& osSAS,
                                 bool bUseHTTPS,
                                 bool bFromManagedIdentities);
        HGDAL_EXPORT ~VSIAzureBlobHandleHelper();

        HGDAL_EXPORT static VSIAzureBlobHandleHelper* BuildFromURI(const char* pszURI,
                                                      const char* pszFSPrefix,
                                                      CSLConstList papszOptions = nullptr);

        HGDAL_EXPORT struct curl_slist* GetCurlHeaders(const CPLString& osVerbosVerb,
                                          const struct curl_slist* psExistingHeaders,
                                          const void *pabyDataContent = nullptr,
                                          size_t nBytesContent = 0) const override;

        const CPLString& GetURL() const override { return m_osURL; }

        HGDAL_EXPORT CPLString GetSignedURL(CSLConstList papszOptions);

        HGDAL_EXPORT static void ClearCache();

        HGDAL_EXPORT std::string GetSASQueryString() const;
};

namespace cpl
{
    HGDAL_EXPORT int GetAzureBufferSize();
}

#endif /* HAVE_CURL */

#endif /* #ifndef DOXYGEN_SKIP */

#endif /* CPL_AZURE_INCLUDED_H */
