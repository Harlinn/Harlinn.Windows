/*
* Copyright 2016 Google Inc.
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#include <windows.h>
#include <tchar.h>

#include "skia/core/SkTypes.h"
#include "skia/tools/sk_app/Application.h"
#include "skia/tools/sk_app/win/Window_win.h"
#include "skia/tools/timer/Timer.h"

namespace sk_app
{
    namespace
    {
        static char* tchar_to_utf8( const TCHAR* str )
        {
#ifdef _UNICODE
            int size = WideCharToMultiByte( CP_UTF8, 0, str, wcslen( str ), NULL, 0, NULL, NULL );
            char* str8 = (char*)sk_malloc_throw( size + 1 );
            WideCharToMultiByte( CP_UTF8, 0, str, wcslen( str ), str8, size, NULL, NULL );
            str8[size] = '\0';
            return str8;
#else
            return _strdup( str );
#endif
        }
    }

    int Application::Run( ApplicationFactory& applicationFactory, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
    {

        // convert from lpCmdLine to argc, argv.
        char* argv[4096];
        int argc = 0;
        TCHAR exename[1024], * next;
        int exenameLen = GetModuleFileName( NULL, exename, SK_ARRAY_COUNT( exename ) );
        // we're ignoring the possibility that the exe name exceeds the exename buffer
        (void)exenameLen;
        argv[argc++] = tchar_to_utf8( exename );
        TCHAR* arg = _tcstok_s( lpCmdLine, _T( " " ), &next );
        while ( arg != NULL )
        {
            argv[argc++] = tchar_to_utf8( arg );
            arg = _tcstok_s( NULL, _T( " " ), &next );
        }
        int result = Run( applicationFactory, hInstance, nCmdShow, argc, argv );
        for ( int i = 0; i < argc; ++i )
        {
            sk_free( argv[i] );
        }
        return result;
    }

    int Application::Run( ApplicationFactory& applicationFactory, int argc, char** argv )
    {
        return Run( applicationFactory, GetModuleHandle( NULL ), SW_SHOW, argc, argv );
    }

    int Application::Run( ApplicationFactory& applicationFactory, HINSTANCE hInstance, int show, int argc, char** argv )
    {
        Application* app = applicationFactory.Create( argc, argv, (void*)hInstance );

        MSG msg;
        memset( &msg, 0, sizeof( msg ) );

        bool idled = false;

        // Main message loop
        while ( WM_QUIT != msg.message )
        {
            if ( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
            {
                TranslateMessage( &msg );

                if ( WM_PAINT == msg.message )
                {
                    // Ensure that call onIdle at least once per WM_PAINT, or mouse events can
                    // overwhelm the message processing loop, and prevent animation from running.
                    if ( !idled )
                    {
                        app->onIdle( );
                    }
                    idled = false;
                }
                DispatchMessage( &msg );
            }
            else
            {
                app->onIdle( );
                idled = true;
            }
        }

        delete app;

        return (int)msg.wParam;
    }
}