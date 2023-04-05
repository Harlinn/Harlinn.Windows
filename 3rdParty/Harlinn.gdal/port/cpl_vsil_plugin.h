#pragma once
/******************************************************************************
 *
 * Project:  CPL - Common Portability Library
 * Purpose:  Declarations for vsi filesystem plugin handlers
 * Author:   Thomas Bonfort <thomas.bonfort@airbus.com>
 *
 ******************************************************************************
 * Copyright (c) 2019, Thomas Bonfort <thomas.bonfort@airbus.com>
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

#ifndef CPL_VSIL_PLUGIN_H_INCLUDED
#define CPL_VSIL_PLUGIN_H_INCLUDED

#include <port/cpl_port.h>
#include <port/cpl_string.h>
#include <port/cpl_vsi.h>
#include <port/cpl_vsi_virtual.h>

//! @cond Doxygen_Suppress

namespace cpl {

/************************************************************************/
/*                     VSIPluginFilesystemHandler                         */
/************************************************************************/

class VSIPluginHandle;

class VSIPluginFilesystemHandler : public VSIFilesystemHandler
{
    CPL_DISALLOW_COPY_ASSIGN(VSIPluginFilesystemHandler)

private:
    const char*         m_Prefix;
    const VSIFilesystemPluginCallbacksStruct* m_cb;

protected:
    friend class VSIPluginHandle;
    HGDAL_EXPORT VSIPluginHandle* CreatePluginHandle(void *cbData);
    HGDAL_EXPORT const char* GetCallbackFilename(const char* pszFilename);
    HGDAL_EXPORT bool IsValidFilename(const char *pszFilename);

    HGDAL_EXPORT vsi_l_offset    Tell( void *pFile );
    HGDAL_EXPORT int             Seek( void *pFile, vsi_l_offset nOffset, int nWhence );
    HGDAL_EXPORT size_t          Read( void *pFile, void *pBuffer, size_t nSize, size_t nCount );
    HGDAL_EXPORT int             ReadMultiRange( void *pFile, int nRanges, void ** ppData, const vsi_l_offset* panOffsets, const size_t* panSizes );
    HGDAL_EXPORT VSIRangeStatus  GetRangeStatus( void *pFile, vsi_l_offset nOffset, vsi_l_offset nLength );
    HGDAL_EXPORT int             Eof( void *pFile );
    HGDAL_EXPORT size_t          Write( void *pFile, const void *pBuffer, size_t nSize,size_t nCount);
    HGDAL_EXPORT int             Flush( void *pFile );
    HGDAL_EXPORT int             Truncate( void *pFile, vsi_l_offset nNewSize );
    HGDAL_EXPORT int             Close( void *pFile );

public:
    HGDAL_EXPORT VSIPluginFilesystemHandler( const char *pszPrefix,
                                const VSIFilesystemPluginCallbacksStruct *cb);
    HGDAL_EXPORT ~VSIPluginFilesystemHandler() override;

    HGDAL_EXPORT VSIVirtualHandle *Open( const char *pszFilename,
                            const char *pszAccess,
                            bool bSetError,
                            CSLConstList /* papszOptions */ ) override;

    HGDAL_EXPORT int Stat        ( const char *pszFilename, VSIStatBufL *pStatBuf, int nFlags ) override;
    HGDAL_EXPORT int Unlink      ( const char * pszFilename ) override;
    HGDAL_EXPORT int Rename      ( const char * oldpath, const char * /*newpath*/ ) override;
    HGDAL_EXPORT int Mkdir       ( const char * pszDirname, long nMode ) override;
    HGDAL_EXPORT int Rmdir       ( const char * pszDirname ) override;
    char **ReadDir  ( const char *pszDirname ) override
                        { return ReadDirEx(pszDirname, 0); }
    HGDAL_EXPORT char **ReadDirEx( const char * pszDirname, int nMaxFiles ) override;
    HGDAL_EXPORT char **SiblingFiles( const char * pszFilename ) override;
    HGDAL_EXPORT int HasOptimizedReadMultiRange(const char* pszPath ) override;
    
};

/************************************************************************/
/*                           VSIPluginHandle                              */
/************************************************************************/

class VSIPluginHandle : public VSIVirtualHandle
{
    CPL_DISALLOW_COPY_ASSIGN(VSIPluginHandle)

  protected:
    VSIPluginFilesystemHandler* poFS;
    void *cbData;

  public:

    HGDAL_EXPORT VSIPluginHandle( VSIPluginFilesystemHandler* poFS, void *cbData);
    HGDAL_EXPORT ~VSIPluginHandle() override;

    HGDAL_EXPORT vsi_l_offset    Tell() override;
    HGDAL_EXPORT int             Seek( vsi_l_offset nOffset, int nWhence ) override;
    HGDAL_EXPORT size_t          Read( void *pBuffer, size_t nSize, size_t nCount ) override;
    HGDAL_EXPORT int             ReadMultiRange( int nRanges, void ** ppData, const vsi_l_offset* panOffsets, const size_t* panSizes ) override;
    HGDAL_EXPORT VSIRangeStatus  GetRangeStatus( vsi_l_offset nOffset, vsi_l_offset nLength ) override;
    HGDAL_EXPORT int             Eof() override;
    HGDAL_EXPORT size_t          Write( const void *pBuffer, size_t nSize,size_t nCount) override;
    HGDAL_EXPORT int             Flush() override;
    HGDAL_EXPORT int             Truncate( vsi_l_offset nNewSize ) override;
    HGDAL_EXPORT int             Close() override;
};

} // namespace cpl

//! @endcond

#endif // CPL_VSIL_PLUGIN_H_INCLUDED
