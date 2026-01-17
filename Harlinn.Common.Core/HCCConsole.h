#pragma once
#ifndef __HCCCONSOLE_H__
#define __HCCCONSOLE_H__

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


#include <HCCDef.h>
#include <HCCError.h>
#include <HCCString.h>
#include <HCCIO.h>

namespace Harlinn::Common::Core
{
    /// <summary>
    /// Lightweight wrapper around relevant Win32 Console APIs.
    /// </summary>
    /// <remarks>
    /// All Win32 failures are converted to exceptions by calling <see cref="ThrowLastOSError"/>.
    /// Methods are small convenience helpers and operate on the standard console handles by default.
    /// Thread-safety: callers must synchronize console usage when required by their application.
    /// </remarks>
    class Console
    {
    public:
        /// <summary>
        /// Obtain the standard input handle.
        /// </summary>
        /// <returns>The Win32 HANDLE for STD_INPUT_HANDLE.</returns>
        /// <exception cref="SystemException">When the underlying Win32 call fails.</exception>
        static HANDLE GetStdInputHandle( )
        {
            HANDLE h = ::GetStdHandle( STD_INPUT_HANDLE );
            if ( h == INVALID_HANDLE_VALUE )
            {
                ThrowLastOSError( );
            }
            return h;
        }

        /// <summary>
        /// Obtain the standard output handle.
        /// </summary>
        /// <returns>The Win32 HANDLE for STD_OUTPUT_HANDLE.</returns>
        /// <exception cref="SystemException">When the underlying Win32 call fails.</exception>
        static HANDLE GetStdOutputHandle( )
        {
            HANDLE h = ::GetStdHandle( STD_OUTPUT_HANDLE );
            if ( h == INVALID_HANDLE_VALUE )
            {
                ThrowLastOSError( );
            }
            return h;
        }

        /// <summary>
        /// Obtain the standard error handle.
        /// </summary>
        /// <returns>The Win32 HANDLE for STD_ERROR_HANDLE.</returns>
        /// <exception cref="SystemException">When the underlying Win32 call fails.</exception>
        static HANDLE GetStdErrorHandle( )
        {
            HANDLE h = ::GetStdHandle( STD_ERROR_HANDLE );
            if ( h == INVALID_HANDLE_VALUE )
            {
                ThrowLastOSError( );
            }
            return h;
        }

        /// <summary>
        /// Get the current console text attributes for the specified output handle.
        /// </summary>
        /// <param name="outputHandle">Handle to query. If nullptr, the standard output handle is used.</param>
        /// <returns>Current text attribute WORD.</returns>
        /// <exception cref="SystemException">When the underlying Win32 call fails.</exception>
        static WORD GetTextAttribute( HANDLE outputHandle = nullptr )
        {
            HANDLE h = outputHandle ? outputHandle : GetStdOutputHandle( );
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if ( !::GetConsoleScreenBufferInfo( h, &csbi ) )
            {
                ThrowLastOSError( );
            }
            return csbi.wAttributes;
        }

        /// <summary>
        /// Set the console text attributes (colors) for the specified output handle.
        /// </summary>
        /// <param name="attributes">Attributes to set (foreground/background color flags).</param>
        /// <param name="outputHandle">Handle to set. If nullptr, the standard output handle is used.</param>
        /// <exception cref="SystemException">When the underlying Win32 call fails.</exception>
        static void SetTextAttribute( WORD attributes, HANDLE outputHandle = nullptr )
        {
            HANDLE h = outputHandle ? outputHandle : GetStdOutputHandle( );
            if ( !::SetConsoleTextAttribute( h, attributes ) )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Write raw bytes to a console handle (or stdout by default).
        /// </summary>
        /// <param name="buffer">Pointer to data to write.</param>
        /// <param name="numberOfBytes">Number of bytes to write.</param>
        /// <param name="outputHandle">Handle to write to. If nullptr, the standard output handle is used.</param>
        /// <returns>Number of bytes actually written.</returns>
        /// <exception cref="SystemException">When the underlying Win32 call fails.</exception>
        static DWORD Write( const void* buffer, DWORD numberOfBytes, HANDLE outputHandle = nullptr )
        {
            if ( buffer == nullptr || numberOfBytes == 0 )
            {
                return 0;
            }
            HANDLE h = outputHandle ? outputHandle : GetStdOutputHandle( );
            DWORD written = 0;
            // Use WriteFile which works when output is redirected to a pipe/file and also works for console.
            if ( !::WriteFile( h, buffer, numberOfBytes, &written, nullptr ) )
            {
                ThrowLastOSError( );
            }
            return written;
        }

        /// <summary>
        /// Convenience overload to write a UTF-16 string to the console output handle.
        /// </summary>
        /// <param name="text">UTF-16 string to write.</param>
        /// <param name="outputHandle">Handle to write to. If nullptr, the standard output handle is used.</param>
        /// <returns>Number of characters written.</returns>
        /// <exception cref="SystemException">When the underlying Win32 call fails.</exception>
        static DWORD Write( const std::wstring& text, HANDLE outputHandle = nullptr )
        {
            if ( text.empty( ) )
            {
                return 0;
            }
            HANDLE h = outputHandle ? outputHandle : GetStdOutputHandle( );

            // Prefer WriteConsoleW when console is attached (writes characters).
            // If output is redirected, WriteConsoleW fails; in that case fall back to WriteFile using UTF-8 conversion.
            DWORD written = 0;
            if ( ::WriteConsoleW( h, text.c_str( ), static_cast<DWORD>( text.size( ) ), &written, nullptr ) )
            {
                return written;
            }
            // If WriteConsoleW failed with ERROR_INVALID_HANDLE or other, fall back to WriteFile with UTF-8 bytes.
            const DWORD err = ::GetLastError( );
            if ( err != ERROR_INVALID_HANDLE && err != ERROR_INVALID_NAME )
            {
                // If it's an unexpected error, rethrow
                ThrowLastOSError( );
            }

            // fallback: convert to UTF-8 and write bytes
            int utf8Len = ::WideCharToMultiByte( CP_UTF8, 0, text.c_str( ), static_cast<int>( text.size( ) ), nullptr, 0, nullptr, nullptr );
            if ( utf8Len <= 0 )
            {
                ThrowLastOSError( );
            }
            std::string utf8;
            utf8.resize( utf8Len );
            if ( ::WideCharToMultiByte( CP_UTF8, 0, text.c_str( ), static_cast<int>( text.size( ) ), utf8.data( ), utf8Len, nullptr, nullptr ) == 0 )
            {
                ThrowLastOSError( );
            }
            return Write( utf8.data( ), static_cast<DWORD>( utf8.size( ) ), h );
        }

        /// <summary>
        /// Read raw bytes from the console input handle (or stdin by default).
        /// </summary>
        /// <param name="buffer">Pointer to receive data.</param>
        /// <param name="numberOfBytesToRead">Maximum number of bytes to read.</param>
        /// <param name="inputHandle">Handle to read from. If nullptr, the standard input handle is used.</param>
        /// <returns>Number of bytes actually read.</returns>
        /// <exception cref="SystemException">When the underlying Win32 call fails.</exception>
        static DWORD Read( void* buffer, DWORD numberOfBytesToRead, HANDLE inputHandle = nullptr )
        {
            if ( buffer == nullptr || numberOfBytesToRead == 0 )
            {
                return 0;
            }
            HANDLE h = inputHandle ? inputHandle : GetStdInputHandle( );
            DWORD read = 0;
            if ( !::ReadFile( h, buffer, numberOfBytesToRead, &read, nullptr ) )
            {
                ThrowLastOSError( );
            }
            return read;
        }

        /// <summary>
        /// Clear the entire console screen and reset the cursor to (0,0).
        /// </summary>
        /// <param name="outputHandle">Handle to the console screen buffer. If nullptr, the standard output handle is used.</param>
        /// <exception cref="SystemException">When the underlying Win32 call fails.</exception>
        static void ClearScreen( HANDLE outputHandle = nullptr )
        {
            HANDLE h = outputHandle ? outputHandle : GetStdOutputHandle( );

            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if ( !::GetConsoleScreenBufferInfo( h, &csbi ) )
            {
                ThrowLastOSError( );
            }

            const DWORD cellCount = static_cast<DWORD>( csbi.dwSize.X ) * static_cast<DWORD>( csbi.dwSize.Y );
            COORD homeCoords = { 0, 0 };

            DWORD written = 0;
            if ( !::FillConsoleOutputCharacterW( h, L' ', cellCount, homeCoords, &written ) )
            {
                ThrowLastOSError( );
            }
            if ( !::FillConsoleOutputAttribute( h, csbi.wAttributes, cellCount, homeCoords, &written ) )
            {
                ThrowLastOSError( );
            }
            if ( !::SetConsoleCursorPosition( h, homeCoords ) )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Get the current cursor position for the specified output handle.
        /// </summary>
        /// <param name="outputHandle">Handle to query. If nullptr, the standard output handle is used.</param>
        /// <returns>Pair of (x, y) cursor coordinates.</returns>
        /// <exception cref="SystemException">When the underlying Win32 call fails.</exception>
        static std::pair<SHORT, SHORT> GetCursorPosition( HANDLE outputHandle = nullptr )
        {
            HANDLE h = outputHandle ? outputHandle : GetStdOutputHandle( );
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if ( !::GetConsoleScreenBufferInfo( h, &csbi ) )
            {
                ThrowLastOSError( );
            }
            return { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y };
        }

        /// <summary>
        /// Set the console cursor position for the specified output handle.
        /// </summary>
        /// <param name="x">X coordinate (column)</param>
        /// <param name="y">Y coordinate (row)</param>
        /// <param name="outputHandle">Handle to set. If nullptr, the standard output handle is used.</param>
        /// <exception cref="SystemException">When the underlying Win32 call fails.</exception>
        static void SetCursorPosition( SHORT x, SHORT y, HANDLE outputHandle = nullptr )
        {
            HANDLE h = outputHandle ? outputHandle : GetStdOutputHandle( );
            COORD coord = { x, y };
            if ( !::SetConsoleCursorPosition( h, coord ) )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Enable or disable virtual terminal processing on the specified output handle.
        /// </summary>
        /// <param name="enable">True to enable, false to disable.</param>
        /// <param name="outputHandle">Handle to modify. If nullptr, the standard output handle is used.</param>
        /// <exception cref="SystemException">When the underlying Win32 call fails.</exception>
        static void EnableVirtualTerminalProcessing( bool enable, HANDLE outputHandle = nullptr )
        {
            HANDLE h = outputHandle ? outputHandle : GetStdOutputHandle( );
            DWORD mode = 0;
            if ( !::GetConsoleMode( h, &mode ) )
            {
                ThrowLastOSError( );
            }
            if ( enable )
            {
                mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            }
            else
            {
                mode &= ~ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            }
            if ( !::SetConsoleMode( h, mode ) )
            {
                ThrowLastOSError( );
            }
        }
    };
}

#endif
