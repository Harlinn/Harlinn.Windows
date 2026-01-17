#pragma once
#ifndef __HCCOBJBASE_H__
#define __HCCOBJBASE_H__
/*
   Copyright 2024-2026 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <HCCCOM.h>
#include <HCCException.h>
#include <HCCVariant.h>
#include <HCCIO.h>


namespace Harlinn::Common::Core
{
    enum class MarshalContext : DWORD
    {
        Local = 0,
        NoSharedMem = 1,
        DifferentMachine = 2,
        InProc = 3,
        CrossCtx = 4
    };

    enum class MarshalFlags : DWORD
    {
        Normal = 0,
        TableStrong = 1,
        TableWeak = 2,
        NoPing = 4
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( MarshalFlags, DWORD );


    class Marshal : public Unknown
    {
    public:
        typedef Unknown Base;

        HCC_COM_STANDARD_METHODS_IMPL( Marshal, Unknown, IMarshal, IUnknown )

        CLSID GetUnmarshalClass( REFIID riid, void* pv, MarshalContext destContext, MarshalFlags flags ) const
        {
            auto pInterface = GetInterface( );
            CLSID result;
            auto hr = pInterface->GetUnmarshalClass( riid, pv, DWORD( destContext ), nullptr, DWORD( flags ), &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        DWORD GetMarshalSizeMax( REFIID riid, void* pv, MarshalContext destContext, MarshalFlags flags ) const
        {
            auto pInterface = GetInterface( );
            DWORD result;
            auto hr = pInterface->GetMarshalSizeMax( riid, pv, DWORD( destContext ), nullptr, DWORD( flags ), &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        void MarshalInterface( IStream* pStm, REFIID riid, void* pv, MarshalContext destContext, MarshalFlags flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->MarshalInterface( pStm, riid, pv, DWORD( destContext ), nullptr, DWORD( flags ) );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void UnmarshalInterface( IStream* pStm, REFIID riid, void** ppv ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->UnmarshalInterface( pStm, riid, ppv );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
        void ReleaseMarshalData( IStream* pStm ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ReleaseMarshalData( pStm );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void DisconnectObject( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DisconnectObject( 0 );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
    };


    class Malloc : public Unknown
    {
    public:
        typedef Unknown Base;

        HCC_COM_STANDARD_METHODS_IMPL( Malloc, Unknown, IMalloc, IUnknown )

        static Malloc GetMalloc( ) 
        {
            IMalloc* ptr = nullptr;
            auto hr = CoGetMalloc( 1, &ptr );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return Malloc( ptr );
        }

        void* Alloc( SIZE_T numberOfBytesToAllocate ) const
        {
            auto pInterface = GetInterface( );
            auto result = pInterface->Alloc( numberOfBytesToAllocate );
            if ( !result && numberOfBytesToAllocate )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
            return result;
        }
        void* Realloc( void* pv, SIZE_T newMemoryBufferSize ) const
        {
            auto pInterface = GetInterface( );
            auto result = pInterface->Realloc( pv, newMemoryBufferSize );
            if ( !result && newMemoryBufferSize )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
            return result;
        }
        void Free( void* pv ) const
        {
            auto pInterface = GetInterface( );
            pInterface->Free( pv );
        }
        SIZE_T GetSize( void* pv ) const
        {
            auto pInterface = GetInterface( );
            auto result = pInterface->GetSize( pv );
            return result;
        }
        int DidAlloc( void* pv ) const
        {
            auto pInterface = GetInterface( );
            auto result = pInterface->DidAlloc( pv );
            return result;
        }
        void HeapMinimize( void ) const
        {
            auto pInterface = GetInterface( );
            pInterface->HeapMinimize( );
        }
    };


    class EnumUnknown : Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( EnumUnknown, Unknown, IEnumUnknown, IUnknown )

        bool Next( Unknown& result ) const
        {
            auto pInterface = GetInterface( );
            IUnknown* pElement = nullptr;
            ULONG actual = 0;
            auto hr = pInterface->Next( 1, &pElement, &actual );
            if ( actual )
            {
                result.ResetPtr( pElement );
                return true;
            }
            return false;
        }
        bool Next( ULONG requestedNumberOfElements, std::vector<Unknown>& result ) const
        {
            auto pInterface = GetInterface( );
            IUnknown** pElements = (IUnknown**)_malloca( requestedNumberOfElements * sizeof( IUnknown* ) );
            std::unique_ptr<IUnknown*, FreeADeleter<IUnknown*>> elementsPtr( pElements );
            memset( pElements, 0, requestedNumberOfElements * sizeof( IUnknown* ) );
            ULONG actual = 0;

            auto hr = pInterface->Next( requestedNumberOfElements, pElements, &actual );
            if ( actual )
            {
                result.clear( );
                for ( ULONG i = 0; i < actual; i++ )
                {
                    result.push_back( Unknown( pElements[i] ) );
                }
                return true;
            }
            return false;
        }
        void Skip( ULONG numberOfElements ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Skip( numberOfElements );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void Reset( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Reset( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        EnumUnknown Clone( ) const
        {
            auto pInterface = GetInterface( );
            IEnumUnknown* pClone = nullptr;
            auto hr = pInterface->Clone( &pClone );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return EnumUnknown( pClone );
        }
    };


    class EnumVARIANT : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( EnumVARIANT, Unknown, IEnumVARIANT, IUnknown )

        bool Next( VARIANT& result ) const
        {
            auto pInterface = GetInterface( );
            ULONG actual = 0;
            auto hr = pInterface->Next( 1, &result, &actual );
            if ( actual )
            {
                return true;
            }
            return false;
        }

        bool Next( ULONG requestedNumberOfElements, std::vector<Variant>& result ) const
        {
            auto pInterface = GetInterface( );
            result.clear( );
            result.resize( requestedNumberOfElements );
            ULONG actual = 0;

            auto hr = pInterface->Next( 1, reinterpret_cast<VARIANT*>(result.data( )), &actual );
            if ( actual )
            {
                if ( result.size( ) != actual )
                {
                    result.resize( actual );
                }
                return true;
            }
            return false;
        }

        void Skip( ULONG numberOfElements ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Skip( numberOfElements );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void Reset( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Reset( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        EnumVARIANT Clone( ) const
        {
            auto pInterface = GetInterface( );
            IEnumVARIANT* pClone = nullptr;
            auto hr = pInterface->Clone( &pClone );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return EnumVARIANT( pClone );
        }

    };


    class SequentialStream : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( SequentialStream, Unknown, ISequentialStream, IUnknown )

        ULONG Read( void* pv, ULONG numberOfBytesToRead ) const
        {
            auto pInterface = GetInterface( );
            ULONG result = 0;
            auto hr = pInterface->Read( pv, numberOfBytesToRead, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        ULONG Write( const void* pv, ULONG numberOfBytesToWrite ) const
        {
            auto pInterface = GetInterface( );
            ULONG result = 0;
            auto hr = pInterface->Write( pv, numberOfBytesToWrite, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
    };

    class Stream : public SequentialStream
    {
    public:
        typedef SequentialStream Base;
        HCC_COM_STANDARD_METHODS_IMPL( Stream, SequentialStream, IStream, ISequentialStream )
    public:

        unsigned long long Seek( long long numberOfBytesToMove, IO::SeekOrigin seekOrigin ) const
        {
            auto pInterface = GetInterface( );
            ULARGE_INTEGER result;
            result.QuadPart = 0;
            LARGE_INTEGER btm;
            btm.QuadPart = numberOfBytesToMove;
            auto hr = pInterface->Seek( btm, DWORD( seekOrigin ), &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result.QuadPart;
        }

        void SetSize( unsigned long long newSize ) const
        {
            auto pInterface = GetInterface( );
            ULARGE_INTEGER nz;
            nz.QuadPart = newSize;
            auto hr = pInterface->SetSize( nz );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void CopyTo( IStream* pstm, unsigned long long numberOfBytesToCopy, unsigned long long* actualNumberOfBytesRead, unsigned long long* actualNumberOfBytesWritten ) const
        {
            auto pInterface = GetInterface( );
            ULARGE_INTEGER nobtc, anobr, anobw;
            nobtc.QuadPart = numberOfBytesToCopy;
            anobr.QuadPart = 0;
            anobw.QuadPart = 0;
            auto hr = pInterface->CopyTo( pstm, nobtc, &anobr, &anobw );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            if ( actualNumberOfBytesRead )
            {
                *actualNumberOfBytesRead = anobr.QuadPart;
            }
            if ( actualNumberOfBytesWritten )
            {
                *actualNumberOfBytesWritten = anobw.QuadPart;
            }
        }
        void CopyTo( IStream* pstm, unsigned long long numberOfBytesToCopy, unsigned long long& actualNumberOfBytesRead, unsigned long long& actualNumberOfBytesWritten ) const
        {
            auto pInterface = GetInterface( );
            ULARGE_INTEGER nobtc, anobr, anobw;
            nobtc.QuadPart = numberOfBytesToCopy;
            anobr.QuadPart = 0;
            anobw.QuadPart = 0;
            auto hr = pInterface->CopyTo( pstm, nobtc, &anobr, &anobw );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            actualNumberOfBytesRead = anobr.QuadPart;
            actualNumberOfBytesWritten = anobw.QuadPart;

        }
        void Commit( DWORD commitFlags = STGC_DEFAULT ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Commit( commitFlags );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void Revert( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Revert( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }


        void LockRegion( unsigned long long offset, unsigned long long sizeOfRegion, DWORD lockType ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->LockRegion( *(ULARGE_INTEGER*)&offset, *(ULARGE_INTEGER*)&sizeOfRegion, lockType );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void UnlockRegion( unsigned long long offset, unsigned long long sizeOfRegion, DWORD lockType ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->UnlockRegion( *(ULARGE_INTEGER*)&offset, *(ULARGE_INTEGER*)&sizeOfRegion, lockType );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void Stat( STATSTG* pstatstg, DWORD grfStatFlag ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Stat( pstatstg, grfStatFlag );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        Stream Clone( ) const
        {
            IStream* result = nullptr;
            auto pInterface = GetInterface( );
            auto hr = pInterface->Clone( &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return Stream( result );
        }

        void WriteClassId( REFCLSID rclsid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = WriteClassStm( pInterface, rclsid );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        CLSID ReadClassId( ) const
        {
            auto pInterface = GetInterface( );
            CLSID result = { 0, };
            auto hr = ReadClassStm( pInterface, &result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            result;
        }
    };
}


#endif

