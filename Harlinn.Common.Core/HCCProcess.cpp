#include "pch.h"
#include "HCCProcess.h"

namespace Harlinn::Common::Core
{

    Process::Process( const ProcessOptions& options )
        : processId_( 0 )
    {
        LPCWSTR applicationName = options.ApplicationName( ).size( ) ? options.ApplicationName( ).c_str( ) : nullptr;
        LPCWSTR commandLine = options.CommandLine( ).size( ) ? options.CommandLine( ).c_str( ) : nullptr;
        LPSECURITY_ATTRIBUTES processAttributes = options.ProcessAttributes( );
        LPSECURITY_ATTRIBUTES threadAttributes = options.ThreadAttributes( );
        BOOL inheritHandles = options.InheritHandles( );
        DWORD creationFlags = static_cast<DWORD>( options.CreationFlags() );
        LPCWSTR environment = options.Environment( ).size( ) ? options.Environment( ).c_str( ) : nullptr;
        LPCWSTR currentDirectory = options.CurrentDirectory( ).size( ) ? options.CurrentDirectory( ).c_str( ) : nullptr;
        auto& startupInfoRef = options.StartupInfo( );
        const STARTUPINFOW* startupInfo = &startupInfoRef;
        PROCESS_INFORMATION processInformation;

        auto rc = CreateProcessW( applicationName, (LPWSTR)commandLine, processAttributes, threadAttributes, inheritHandles, creationFlags, (LPVOID)environment, currentDirectory, (LPSTARTUPINFOW)startupInfo, &processInformation );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        SetHandle( processInformation.hProcess );
        thread_ = Thread( processInformation.hThread, (UInt32)processInformation.dwThreadId );


    }
}