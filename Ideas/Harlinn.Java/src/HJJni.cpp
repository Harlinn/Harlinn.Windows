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

#include "pch.h"
#include "HJJni.h"
#include "HCCEnvironment.h"
#include "HCCIO.h"

namespace Harlinn::Java
{
    namespace hcc = Harlinn::Common::Core;
    namespace
    {


        using JNI_GetDefaultJavaVMInitArgsFuncDef = jint __stdcall ( void* args );
        using JNI_CreateJavaVMFuncDef = jint __stdcall( JavaVM** pvm, void** penv, void* args );
        using JNI_GetCreatedJavaVMsFuncDef = jint __stdcall( JavaVM**, jsize, jsize* );

        HMODULE JvmDll = nullptr;
        JNI_GetDefaultJavaVMInitArgsFuncDef* JNI_GetDefaultJavaVMInitArgsFunc = nullptr;
        JNI_CreateJavaVMFuncDef* JNI_CreateJavaVMFunc = nullptr;
        JNI_GetCreatedJavaVMsFuncDef* JNI_GetCreatedJavaVMsFunc = nullptr;

        
        bool FindJVMInPath( hcc::WideString& location )
        {
            auto jvmDll = hcc::Environment::Where( L"jvm.dll" );
            if ( jvmDll.size( ) )
            {
                location = jvmDll;
                return true;
            }
            return false;
        }


        bool FindJdkJVM( HKEY rootKey, hcc::WideString& location )
        {
            hcc::WideString keyPath( L"SOFTWARE\\JavaSoft\\JDK" );
            DWORD rc = NO_ERROR;
            HKEY jrtKey = nullptr;
            if ( rc = RegOpenKeyExW( rootKey, keyPath.c_str(), 0, KEY_READ, &jrtKey ) )
            {
                RegCloseKey( jrtKey );
                return false;
            }

            wchar_t versionString[32];
            DWORD bufsize = 32 * sizeof( TCHAR );
            if ( rc = RegGetValue( jrtKey, NULL, TEXT( "CurrentVersion" ), RRF_RT_REG_SZ, NULL, versionString, &bufsize ) )
            {
                RegCloseKey( jrtKey );
                return false;
            }
            RegCloseKey( jrtKey );
            keyPath += L"\\";
            keyPath += versionString;

            if ( rc = RegOpenKeyExW( rootKey, keyPath.c_str( ), 0, KEY_READ, &jrtKey ) )
            {
                RegCloseKey( jrtKey );
                return false;
            }

            wchar_t jdkHome[512];
            bufsize = 512 * sizeof( TCHAR );
            rc = RegGetValue( jrtKey, versionString, TEXT( "JavaHome" ), RRF_RT_REG_SZ, NULL, jdkHome, &bufsize );
            RegCloseKey( jrtKey );
            if ( rc )
            {
                return false;
            }
            return hcc::IO::File::Search( hcc::WideString( jdkHome ), hcc::WideString(L"jvm.dll"), true, location );
        }

        bool FindJrtJVM( HKEY rootKey, hcc::WideString& location )
        {
            DWORD rc = NO_ERROR;
            HKEY jrtKey = nullptr;
            if ( rc = RegOpenKeyEx( rootKey, TEXT( "SOFTWARE\\JavaSoft\\Java Runtime Environment" ), 0, KEY_READ, &jrtKey ) )
            {
                RegCloseKey( jrtKey );
                return false;
            }

            TCHAR versionString[32]; 
            DWORD bufsize = 32 * sizeof( TCHAR );
            if ( rc = RegGetValue( jrtKey, NULL, TEXT( "CurrentVersion" ), RRF_RT_REG_SZ, NULL, versionString, &bufsize ) )
            {
                RegCloseKey( jrtKey );
                return false;
            }

            TCHAR dllpath[512];
            bufsize = 512 * sizeof( TCHAR );
            rc = RegGetValue( jrtKey, versionString, TEXT( "RuntimeLib" ), RRF_RT_REG_SZ, NULL, dllpath, &bufsize );
            RegCloseKey( jrtKey );
            if ( rc )
            {
                return false;
            }
            location = dllpath;
            return true;
        }

        bool FindJVM( hcc::WideString& location )
        {
            if ( !FindJVMInPath( location ) )
            {
                if ( !FindJdkJVM( HKEY_LOCAL_MACHINE, location ) )
                {
                    if ( !FindJdkJVM( HKEY_CURRENT_USER, location ) )
                    {
                        if ( !FindJrtJVM( HKEY_LOCAL_MACHINE, location ) )
                        {
                            if ( !FindJrtJVM( HKEY_CURRENT_USER, location ) )
                            {
                                return false;
                            }
                        }
                    }
                }      
            }
            return true;
        }


        bool InitJVM( )
        {
            if ( !JvmDll )
            {
                hcc::WideString location;
                if ( FindJVM( location ) )
                {
                    JvmDll = LoadLibraryW( location.c_str( ) );
                    if ( JvmDll )
                    {
                        JNI_GetDefaultJavaVMInitArgsFunc = (JNI_GetDefaultJavaVMInitArgsFuncDef*)GetProcAddress( JvmDll,"JNI_GetDefaultJavaVMInitArgs" );
                        if ( JNI_GetDefaultJavaVMInitArgsFunc )
                        {
                            JNI_CreateJavaVMFunc = (JNI_CreateJavaVMFuncDef*)GetProcAddress( JvmDll, "JNI_CreateJavaVM" );
                            if ( JNI_CreateJavaVMFunc )
                            {
                                JNI_GetCreatedJavaVMsFunc = (JNI_GetCreatedJavaVMsFuncDef*)GetProcAddress( JvmDll, "JNI_GetCreatedJavaVMs" );
                                if ( JNI_GetCreatedJavaVMsFunc )
                                {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }


    }


    jint JNI_GetDefaultJavaVMInitArgs( void* args )
    {
        if ( InitJVM( ) )
        {
            return JNI_GetDefaultJavaVMInitArgsFunc( args );
        }
        return JNI_ERR;
    }

    jint JNI_CreateJavaVM( JavaVM** pvm, void** penv, void* args )
    {
        if ( InitJVM( ) )
        {
            return JNI_CreateJavaVMFunc( pvm, penv, args );
        }

        return JNI_ERR;
    }

    jint JNI_GetCreatedJavaVMs( JavaVM** pvm, jsize sz, jsize* psz)
    {
        if ( InitJVM( ) )
        {
            return JNI_GetCreatedJavaVMsFunc( pvm, sz, psz );
        }
        return JNI_ERR;
    }



}