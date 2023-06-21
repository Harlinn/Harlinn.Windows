#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{

    void BFILELocator::FileClose( ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto handle = (OCILobLocator*)Handle( );
        OCI::LobFileClose( serviceContext, error, handle );
    }

    bool BFILELocator::FileExists( ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto handle = (OCILobLocator*)Handle( );

        bool result = false;
        OCI::LobFileExists( serviceContext, error, handle, &result );
        return result;
    }

    bool BFILELocator::FileIsOpen( ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto handle = (OCILobLocator*)Handle( );

        bool result = false;
        OCI::LobFileIsOpen( serviceContext, error, handle, &result );
        return result;
    }

    void BFILELocator::FileOpen( ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto handle = (OCILobLocator*)Handle( );

        OCI::LobFileOpen( serviceContext, error, handle, OCI_FILE_READONLY );
        
    }

    WideString BFILELocator::FileGetName( WideString& directoryAlias ) const
    {
        auto& environment = Environment( );
        auto& error = Error( );
        auto handle = (OCILobLocator*)Handle( );

        wchar_t dirAliasBuffer[31];
        UInt16 dirAliasSize = sizeof( dirAliasBuffer );

        wchar_t filenameBuffer[256];
        UInt16 filenameSize = sizeof( filenameBuffer );


        OCI::LobFileGetName( environment, error, handle, dirAliasBuffer, &dirAliasSize, filenameBuffer, &filenameSize );


        WideString result( (wchar_t*)filenameBuffer, size_t( filenameSize ) / sizeof( wchar_t ) );
        WideString da( (wchar_t*)dirAliasBuffer, size_t( dirAliasSize ) / sizeof( wchar_t ) );
        directoryAlias = da;
        return result;
    }

    void BFILELocator::FileSetName( const WideString& directoryAlias, const WideString& filename )
    {
        auto& environment = Environment( );
        auto& error = Error( );
        auto handle = (OCILobLocator*)Handle( );

        OCI::LobFileSetName( environment, error, &handle, directoryAlias.c_str( ), static_cast<UInt16>( directoryAlias.length( ) * sizeof( wchar_t ) ), filename.c_str( ), static_cast<UInt16>( filename.length( ) * sizeof( wchar_t ) ) );
        if ( handle != Handle( ) )
        {
            SetHandle( handle, true );
        }
    }
}