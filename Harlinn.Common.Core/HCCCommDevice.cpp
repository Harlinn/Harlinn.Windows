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
#include "HCCCommDevice.h"

namespace Harlinn::Common::Core::IO
{
    WideString SerialPort::Name( ) const
    {
        wchar_t buffer[16];
        buffer[0] = 0;
        swprintf_s( buffer, L"COM%d", portNumber_ );
        return WideString(buffer);
    }

    SerialPorts::SerialPorts( )
    {
        ULONG portNumbers[32];
        ULONG portNumbersFound = 0;
        auto rc = GetCommPorts( portNumbers, 32, &portNumbersFound );
        if ( rc != ERROR_FILE_NOT_FOUND )
        {
            if ( rc == ERROR_SUCCESS )
            {
                for ( ULONG i = 0; i < portNumbersFound; ++i )
                {
                    auto portNumber = portNumbers[i];
                    emplace_back( SerialPort( portNumber ) );
                }
            }
            else
            {
                std::vector<ULONG> portNumbersVector;
                portNumbersVector.resize( portNumbersFound );
                portNumbersFound = 0;
                auto rc = GetCommPorts( portNumbersVector.data( ), static_cast<ULONG>( portNumbersVector.size( ) ), &portNumbersFound );
                if ( rc == ERROR_SUCCESS )
                {
                    for ( ULONG i = 0; i < portNumbersFound; ++i )
                    {
                        auto portNumber = portNumbersVector[i];
                        emplace_back( SerialPort( portNumber ) );
                    }
                }
            }
        }
    }

    HANDLE CommDeviceStream::Create( ULONG portNumber, bool overlapped, DWORD desiredAccess )
    {
        auto result = OpenCommPort( portNumber, desiredAccess, overlapped ? FILE_FLAG_OVERLAPPED : 0 );
        if ( result == INVALID_HANDLE_VALUE )
        {
            ThrowLastOSError( );
        }
        return result;
    }
    HANDLE CommDeviceStream::Create( const wchar_t* name, bool overlapped )
    {
        auto result = CreateFileW( name, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, overlapped ? FILE_FLAG_OVERLAPPED : 0, nullptr );
        if ( result == INVALID_HANDLE_VALUE )
        {
            ThrowLastOSError( );
        }
        return result;
    }
    HANDLE CommDeviceStream::Create( const char* name, bool overlapped )
    {
        auto result = CreateFileA( name, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, overlapped ? FILE_FLAG_OVERLAPPED : 0, nullptr );
        if ( result == INVALID_HANDLE_VALUE )
        {
            ThrowLastOSError( );
        }
        return result;
    }
    namespace
    {
        void InitializeHandle(HANDLE handle, UInt32 baudRate, Parity parity, Byte dataBits, StopBits stopBits, FlowControl flowControl )
        {
            //Get the current state prior to changing it
            DCB dcb{ sizeof( DCB ), 0, };
            auto rc = GetCommState( handle, &dcb );
            if ( !rc )
            {
                auto error = GetLastError( );
                CloseHandle( handle );
                ThrowOSError( error );
            }

            dcb.BaudRate = baudRate;
            dcb.Parity = static_cast<BYTE>( parity );
            dcb.ByteSize = dataBits;
            dcb.StopBits = static_cast<BYTE>( stopBits );

            //Setup the flow control
            dcb.fDsrSensitivity = FALSE;
            switch ( flowControl )
            {
                case FlowControl::None:
                {
                    dcb.fOutxCtsFlow = FALSE;
                    dcb.fOutxDsrFlow = FALSE;
                    dcb.fOutX = FALSE;
                    dcb.fInX = FALSE;
                }
                break;
                case FlowControl::XonXoff:
                {
                    dcb.fOutxCtsFlow = FALSE;
                    dcb.fOutxDsrFlow = FALSE;
                    dcb.fOutX = TRUE;
                    dcb.fInX = TRUE;
                    dcb.XonChar = 0x11;
                    dcb.XoffChar = 0x13;
                    dcb.XoffLim = 100;
                    dcb.XonLim = 100;
                }
                break;
                case FlowControl::CtsRts:
                {
                    dcb.fOutxCtsFlow = TRUE;
                    dcb.fOutxDsrFlow = FALSE;
                    dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
                    dcb.fOutX = FALSE;
                    dcb.fInX = FALSE;
                }
                break;
                case FlowControl::CtsDtr:
                {
                    dcb.fOutxCtsFlow = TRUE;
                    dcb.fOutxDsrFlow = FALSE;
                    dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;
                    dcb.fOutX = FALSE;
                    dcb.fInX = FALSE;
                }
                break;
                case FlowControl::DsrRts:
                {
                    dcb.fOutxCtsFlow = FALSE;
                    dcb.fOutxDsrFlow = TRUE;
                    dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
                    dcb.fOutX = FALSE;
                    dcb.fInX = FALSE;
                }
                break;
                case FlowControl::DsrDtr:
                {
                    dcb.fOutxCtsFlow = FALSE;
                    dcb.fOutxDsrFlow = TRUE;
                    dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;
                    dcb.fOutX = FALSE;
                    dcb.fInX = FALSE;
                }
                break;
            }

            rc = SetCommState( handle, &dcb );
            if ( !rc )
            {
                auto error = GetLastError( );
                CloseHandle( handle );
                ThrowOSError( error );
            }
        }
    }
    HANDLE CommDeviceStream::Create( const wchar_t* name, UInt32 baudRate, Parity parity, Byte dataBits, StopBits stopBits, FlowControl flowControl, bool overlapped )
    {
        auto result = Create( name, overlapped );
        InitializeHandle( result, baudRate, parity, dataBits, stopBits, flowControl );
        return result;
    }
    HANDLE CommDeviceStream::Create( const char* name, UInt32 baudRate, Parity parity, Byte dataBits, StopBits stopBits, FlowControl flowControl, bool overlapped )
    {
        auto result = Create( name, overlapped );
        InitializeHandle( result, baudRate, parity, dataBits, stopBits, flowControl );
        return result;
    }


}