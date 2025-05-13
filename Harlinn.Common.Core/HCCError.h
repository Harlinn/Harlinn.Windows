#pragma once
#ifndef HARLINN_COMMON_CORE_HCCERROR_H_
#define HARLINN_COMMON_CORE_HCCERROR_H_

/*
   Copyright 2024-2025 Espen Harlinn

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

#include "HCCDef.h"
#include "HCCExport.h"

namespace Harlinn::Common::Core
{

    HCC_EXPORT void CheckHRESULT( HRESULT hresult );
    HCC_EXPORT WideString FormatHRESULT( HRESULT hresult );
    [[noreturn]] HCC_EXPORT void ThrowHRESULT( HRESULT hresult );
    HCC_EXPORT void CheckHRESULT( HRESULT hresult, IUnknown* itf );
    HCC_EXPORT void CheckHRESULT( HRESULT hresult, const wchar_t* function, const wchar_t* filename, int lineNumber );
    HCC_EXPORT void CheckHRESULT( HRESULT hresult, IUnknown* itf, const wchar_t* function, const wchar_t* filename, int lineNumber );
    HCC_EXPORT WideString FormatError( DWORD errorId );
    HCC_EXPORT AnsiString FormatErrorA( DWORD errorId );
    HCC_EXPORT void ThrowLastOSError( );
    HCC_EXPORT void ThrowOSError( DWORD errorId );
    [[noreturn]] HCC_EXPORT void ThrowNoInterface( );
    [[noreturn]] HCC_EXPORT void ThrowPointerIsNULL( );
    [[noreturn]] HCC_EXPORT void ThrowInvalidHandle( );
    [[noreturn]] HCC_EXPORT void ThrowNullReferenceException( );
    [[noreturn]] HCC_EXPORT void ThrowNullReferenceException( const char* message );
    [[noreturn]] HCC_EXPORT void ThrowNullReferenceException( const wchar_t* message );
    HCC_EXPORT HRESULT HRESULTFromException( const std::exception& exception );

    template <typename T>
    inline void CheckPointerNotNull( T* ptr )
    {
        if ( !ptr )
        {
            ThrowPointerIsNULL( );
        }
    }
    namespace Environment
    {
        HCC_EXPORT bool IsComputerDomainJoined( );
    }

    template<typename T>
    inline constexpr bool False_v = false;

    template<typename T>
    inline constexpr bool True_v = true;

    class Exception;
    HCC_EXPORT void ReportException( const Exception& exception, const wchar_t* function, const wchar_t* filename, int lineNumber );
    HCC_EXPORT void ReportException( const std::exception& exception, const wchar_t* function, const wchar_t* filename, int lineNumber );
    HCC_EXPORT void ReportUnknownException( const wchar_t* function, const wchar_t* filename, int lineNumber );

    /// <summary>
    /// Thrown by Thread::Exit 
    /// </summary>
    class ThreadAbortException
    {
        DWORD exitCode_;
    public:
        ThreadAbortException( DWORD exitCode )
            : exitCode_( exitCode )
        {
        }
        DWORD ExitCode( ) const
        {
            return exitCode_;
        }
    };

#define HCC_CATCH_ALL_AND_REPORT_EXCEPTION \
    catch ( const Harlinn::Common::Core::ThreadAbortException& /*exception*/ ) \
    { \
        throw; \
    } \
    catch ( const Harlinn::Common::Core::Exception& exception ) \
    { \
        Harlinn::Common::Core::ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
    } \
    catch ( const std::exception& exception ) \
    { \
        Harlinn::Common::Core::ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
    } \
    catch ( ... ) \
    { \
        Harlinn::Common::Core::ReportUnknownException( CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
    }

#define HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( ) \
    catch ( const Harlinn::Common::Core::Exception& exception ) \
    { \
        Harlinn::Common::Core::ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
        return exception.GetHRESULT( ); \
    } \
    catch ( const std::exception& exception ) \
    { \
        Harlinn::Common::Core::ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
        return E_FAIL; \
    } \
    catch ( ... ) \
    { \
        Harlinn::Common::Core::ReportUnknownException( CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
        return E_FAIL; \
    } \
    return S_OK

#define HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( ) \
    catch ( const Harlinn::Common::Core::Exception& exception ) \
    { \
        Harlinn::Common::Core::ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
    } \
    catch ( const std::exception& exception ) \
    { \
        Harlinn::Common::Core::ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
    } \
    catch ( ... ) \
    { \
        Harlinn::Common::Core::ReportUnknownException( CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
    } \
    return

}

#endif
