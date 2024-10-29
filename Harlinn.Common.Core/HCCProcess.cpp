/*
   Copyright 2024 Espen Harlinn

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
        primaryThread_ = Thread( processInformation.hThread, (UInt32)processInformation.dwThreadId );


    }
}