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
    /// <summary>
    /// Checks an HRESULT value and throws a COM exception if the result indicates failure.
    /// </summary>
    /// <param name="hresult">The HRESULT to check.</param>
    /// <remarks>
    /// This is a convenience helper that throws a COMException when FAILED(hresult) is true.
    /// It delegates the actual exception construction to <see cref="ThrowHRESULT" />.
    /// </remarks>
    HCC_EXPORT void CheckHRESULT( HRESULT hresult );

    /// <summary>
    /// Formats an HRESULT into a readable wide string message.
    /// </summary>
    /// <param name="hresult">The HRESULT value to format.</param>
    /// <returns>
    /// A human-readable message describing the HRESULT. If <paramref name="hresult"/> is 0, returns "No error".
    /// If the system cannot resolve a message for the HRESULT, returns a hex representation.
    /// </returns>
    /// <remarks>
    /// Uses a thread-local buffer to hold the formatted message during construction.
    /// The returned string includes both the textual message (if available) and the hex value of the HRESULT.
    /// </remarks>
    HCC_EXPORT WideString FormatHRESULT( HRESULT hresult );
    /// <summary>
    /// Throws a runtime COM exception for the provided HRESULT.
    /// </summary>
    /// <param name="hresult">The HRESULT value describing the error.</param>
    /// <remarks>
    /// This function attempts to format a human-readable message for the HRESULT using
    /// <see cref="FormatMessageW" /> into a thread-local buffer. If a message is available,
    /// it constructs and throws a <see cref="Runtime::InteropServices::COMException" /> using that message.
    /// If no message can be found, a generic "Unknown error" message is used instead.
    /// This function is marked [[noreturn]] and will always throw an exception.
    /// </remarks>
    [[noreturn]] HCC_EXPORT void ThrowHRESULT( HRESULT hresult );

    /// <summary>
    /// Checks a COM HRESULT and throws a rich COMException if it indicates failure.
    /// </summary>
    /// <param name="hresult">
    /// The HRESULT value to validate. If it indicates failure (FAILED(hresult)), the function 
    /// will attempt to obtain rich error information and throw.
    /// </param>
    /// <param name="itf">
    /// Optional pointer to the COM object (IUnknown) that produced the HRESULT. When provided, 
    /// this function will QueryInterface for ISupportErrorInfo and prefer component-provided 
    /// error information from IErrorInfo associated with the current thread. May be nullptr.
    /// </param>
    /// <exception cref="Runtime::InteropServices::COMException">
    /// Thrown when <paramref name="hresult"/> indicates failure. The thrown exception message will 
    /// prefer the component-provided IErrorInfo description when available, otherwise the thread 
    /// IErrorInfo description, and as a last resort the system message for the HRESULT.
    /// </exception>
    /// <remarks>
    /// - Prefer passing the COM object that generated the HRESULT so richer, component-specific error descriptions can be retrieved.
    /// - The function attempts ISupportErrorInfo -> GetErrorInfo -> IErrorInfo::GetDescription, releasing all COM pointers it obtains.
    /// - If no richer information is available, the function falls back to using the system message via ThrowHRESULT.
    /// - This function does not modify thread error state beyond reading it; it always releases any COM interfaces it acquires.
    /// </remarks>
    HCC_EXPORT void CheckHRESULT( HRESULT hresult, IUnknown* itf );
    
    /// <summary>
    /// Validates a COM <paramref name="hresult"/> and throws a rich <see cref="Runtime::InteropServices::COMException"/>
    /// when the result indicates failure.
    /// </summary>
    /// <param name="hresult">
    /// The HRESULT value to check. If FAILED(hresult) the function attempts to retrieve richer error information and will throw.
    /// </param>
    /// <param name="function">
    /// Name of the function (or symbolic location) where the check is performed. Used to populate the thrown exception's location.
    /// </param>
    /// <param name="filename">
    /// Source file name where the check is performed. Used to populate the thrown exception's location.
    /// </param>
    /// <param name="lineNumber">
    /// Source line number where the check is performed. Used to populate the thrown exception's location.
    /// </param>
    /// <exception cref="Runtime::InteropServices::COMException">
    /// Thrown when <paramref name="hresult"/> indicates failure. The thrown exception will prefer the component-provided
    /// <c>IErrorInfo</c> description when available, otherwise the thread <c>IErrorInfo</c> description, and as a last resort
    /// the system message for the HRESULT.
    /// </exception>
    /// <remarks>
    /// - If a COM object pointer is available at the call site, pass it to overloads that accept an <c>IUnknown*</c> so the implementation
    ///   can QueryInterface for <c>ISupportErrorInfo</c> and prefer component-provided error descriptions.
    /// - All COM interfaces and BSTRs acquired are released/freed before throwing.
    /// - The function constructs an <c>ExceptionLocation</c> from <paramref name="function"/>, <paramref name="filename"/> and <paramref name="lineNumber"/>
    ///   and uses it when throwing to provide source location context.
    /// </remarks>
    HCC_EXPORT void CheckHRESULT( HRESULT hresult, const wchar_t* function, const wchar_t* filename, int lineNumber );

    // <summary>
    // Checks a COM HRESULT and throws a rich <see cref="Runtime::InteropServices::COMException"/> 
    // when it indicates failure.
    // </summary>
    // <param name="hresult">
    // The HRESULT value to verify. If it indicates failure (FAILED(hresult)), the function will attempt to 
    // obtain rich error information and throw an exception.
    // </param>
    // <param name="itf">
    // Optional pointer to the COM object (IUnknown) that produced the HRESULT. When provided, the function 
    // will QueryInterface for <c>ISupportErrorInfo</c> and prefer component-provided error information 
    // retrieved via the thread <c>IErrorInfo</c>. May be <c>nullptr</c>.
    // </param>
    // <param name="function">
    // Name of the function where the HRESULT was checked. Used to create an <c>ExceptionLocation</c> for 
    // the thrown exception.
    // </param>
    // <param name="filename">
    // Source file name where the HRESULT was checked. Used to create an <c>ExceptionLocation</c> for the 
    // thrown exception.
    // </param>
    // <param name="lineNumber">
    // Source line number where the HRESULT was checked. Used to create an <c>ExceptionLocation</c> for 
    // the thrown exception.
    // </param>
    // <exception cref="Runtime::InteropServices::COMException">
    // Thrown when <paramref name="hresult"/> indicates failure. The exception message will prefer 
    // component-provided <c>IErrorInfo</c> description when available, otherwise the thread <c>IErrorInfo</c> 
    // description, and as a last resort the system message for the HRESULT.
    // </exception>
    // <remarks>
    // - The function releases any COM interfaces it obtains (<c>ISupportErrorInfo</c>, <c>IErrorInfo</c>).
    // - Prefer passing the producing COM object as <paramref name="itf"/> to obtain richer error descriptions.
    // - This routine constructs an <c>ExceptionLocation</c> from <paramref name="function"/>, <paramref name="filename"/>, and <paramref name="lineNumber"/> and uses it when throwing.
    // <seealso cref="ThrowHRESULT"/>
    // </remarks>
    HCC_EXPORT void CheckHRESULT( HRESULT hresult, IUnknown* itf, const wchar_t* function, const wchar_t* filename, int lineNumber );
    /// <summary>
    /// Formats a Windows system error code (DWORD) into a wide string using system message tables.
    /// </summary>
    /// <param name="errorId">The system error code to format (GetLastError() style).</param>
    /// <returns>A wide string containing the formatted error message. If no message is found, the returned string may be empty.</returns>
    HCC_EXPORT WideString FormatError( DWORD errorId );
    /// <summary>
    /// Formats a Windows system error code (DWORD) into an ANSI string using system message tables.
    /// </summary>
    /// <param name="errorId">The system error code to format.</param>
    /// <returns>An ANSI string containing the formatted error message.</returns>
    HCC_EXPORT AnsiString FormatErrorA( DWORD errorId );
    /// <summary>
    /// Throws a typed exception corresponding to the calling thread's last Win32 error.
    /// </summary>
    /// <remarks>
    /// This convenience wrapper retrieves the last error code for the calling thread by calling
    /// <c>GetLastError()</c> and forwards it to <see cref="ThrowOSError"/> which formats the
    /// system message and throws a <see cref="Harlinn::Common::Core::SystemException"/> when
    /// the error code is non-zero. Use this function immediately after a failing Win32 API
    /// call to convert the thread-local error code into a descriptive exception.
    /// </remarks>
    /// <exception cref="Harlinn::Common::Core::SystemException">
    /// Thrown when the last Win32 error code is non-zero. The message will contain the system
    /// description for the error code when available, otherwise "Unknown error".
    /// </exception>
    /// <seealso cref="ThrowOSError"/>
    /// <example>
    /// try
    /// {
    ///     // Win32 call that fails:
    ///     // ::SomeWin32Api(...);
    ///     ThrowLastOSError(); // throws if ::GetLastError() != 0
    /// }
    /// catch ( const Harlinn::Common::Core::SystemException& ex )
    /// {
    ///     // handle error
    /// }
    /// </example>
    HCC_EXPORT void ThrowLastOSError( );
    /// <summary>
    /// Throws a Core::SystemException corresponding to a Win32 error code.
    /// </summary>
    /// <param name="errorId">
    /// The Win32 error code to translate and throw as an exception.
    /// Typically obtained from ::GetLastError() or other Win32 APIs.
    /// If <c>errorId</c> is zero this function does nothing.
    /// </param>
    /// <exception cref="Harlinn::Common::Core::SystemException">
    /// Thrown when <paramref name="errorId"/> is non-zero. If a system
    /// message can be obtained using <c>FormatMessageW</c> it will be used as the
    /// exception message; otherwise the literal "Unknown error" is used.
    /// </exception>
    HCC_EXPORT void ThrowOSError( DWORD errorId );
    /// <summary>
    /// Throws a COMException indicating that a queried interface is not available.
    /// </summary>
    /// <remarks>Convenience helper that throws a COM-specific exception with a short message.</remarks>
    [[noreturn]] HCC_EXPORT void ThrowNoInterface( );
    /// <summary>
    /// Throws a generic exception indicating a null pointer was encountered.
    /// </summary>
    /// <remarks>Convenience helper used to signal null pointer errors in native code.</remarks>
    [[noreturn]] HCC_EXPORT void ThrowPointerIsNULL( );
    /// <summary>
    /// Throws a SystemException indicating an invalid handle was encountered.
    /// </summary>
    /// <remarks>Convenience helper used where an invalid or closed handle is detected.</remarks>
    [[noreturn]] HCC_EXPORT void ThrowInvalidHandle( );
    /// <summary>
    /// Throws a NullReferenceException with no message.
    /// </summary>
    [[noreturn]] HCC_EXPORT void ThrowNullReferenceException( );
    /// <summary>
    /// Throws a NullReferenceException with a narrow-string message.
    /// </summary>
    /// <param name="message">A null-terminated narrow (UTF-8/ANSI) message describing the error.</param>
    [[noreturn]] HCC_EXPORT void ThrowNullReferenceException( const char* message );
    /// <summary>
    /// Throws a NullReferenceException with a wide-string message.
    /// </summary>
    /// <param name="message">A null-terminated wide (UTF-16) message describing the error.</param>
    [[noreturn]] HCC_EXPORT void ThrowNullReferenceException( const wchar_t* message );

    /// <summary>
    /// Maps an std::exception to an HRESULT when possible.
    /// </summary>
    /// <param name="exception">The source exception reference.</param>
    /// <returns>
    /// If the exception is derived from the project's Exception type, the stored HRESULT is returned.
    /// Otherwise E_FAIL is returned as a generic failure code.
    /// </returns>
    HCC_EXPORT HRESULT HRESULTFromException( const std::exception& exception );

    /// <summary>
    /// Checks that the supplied pointer is not null and throws a native pointer exception if it is.
    /// </summary>
    /// <typeparam name="T">The type of the object pointed to by <paramref name="ptr"/>.</typeparam>
    /// <param name="ptr">Pointer to validate. If null, <see cref="ThrowPointerIsNULL"/> is called which raises a project-defined exception.</param>
    /// <remarks>
    /// This inline helper simplifies repetitive null-pointer checks in native code paths.
    /// It does not take ownership of the pointer. Use this when you need a concise guard
    /// that enforces non-null pointers and reports errors consistently via the project's
    /// exception mechanism.
    /// </remarks>
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
        /// <summary>
        /// Determines whether the local computer is joined to an Active Directory domain.
        /// </summary>
        /// <remarks>
        /// This function attempts an implicit bind to a domain controller using <c>DsBindW(nullptr, nullptr, &handle)</c>.
        /// A successful bind indicates the machine is domain-joined. The outcome is cached in a function-local
        /// static <c>std::optional&lt;bool&gt;</c> to avoid repeated network operations on subsequent calls.
        /// <para/>
        /// The method intentionally preserves the original behavior: a failed bind results in <c>false</c> and
        /// no exception is thrown. No explicit credentials are supplied; the bind uses the current machine/process context.
        /// </remarks>
        /// <returns>
        /// <c>true</c> if the computer is domain-joined; otherwise <c>false</c>.
        /// </returns>
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

    // <summary>
    // <para>
    // Thrown by Thread::Exit 
    // </para>
    // <para>
    // Exception used to signal an explicit thread exit or abort carrying an exit code.
    // </para>
    // </summary>
    // <remarks>
    // Instances of this exception are thrown by thread control utilities (for example, Thread::Exit)
    // to unwind native thread execution and communicate an exit code to the thread manager.
    // Callers should only catch this exception if they intend to rethrow it or convert the exit code
    // into an appropriate thread termination path. Treat this as a control-flow exception rather than
    // an error condition: resources should rely on RAII for cleanup when this exception propagates.
    // </remarks>
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


/// <summary>
/// Catches any exceptions thrown by the preceding try block and reports them using the project's
/// centralized exception reporting functions.
/// </summary>
/// <remarks>
/// Behavior:
/// - Rethrows <c>Harlinn::Common::Core::ThreadAbortException</c> to preserve thread-exit control flow.
/// - Catches <c>Harlinn::Common::Core::Exception</c> and forwards it to <c>ReportException</c> together
///   with the current function, file and line information (via <c>CURRENT_FUNCTION</c>, <c>CURRENT_FILE</c> and <c>__LINE__</c>).
/// - Catches <c>std::exception</c> and forwards it to <c>ReportException</c> with the same location info.
/// - Catches all other exception types and forwards them to <c>ReportUnknownException</c> with location info.
/// Use:
/// - Place this macro immediately after a try block to ensure all exceptions are consistently logged and reported.
/// </remarks>
/// <example>
/// try
/// {
///     // Do work that may throw
/// }
/// HCC_CATCH_ALL_AND_REPORT_EXCEPTION;
/// </example>
/// <seealso cref="HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT">HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT</seealso>
/// <seealso cref="HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN">HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN</seealso>

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

/// <summary>
/// Catches exceptions from a preceding try block, reports them and returns an HRESULT.
/// </summary>
/// <remarks>
/// - Intended for COM-style functions that return an HRESULT. Place this macro immediately
///   after a try block so all exceptions are converted to an HRESULT and reported.
/// - Behavior:
///   - Catches <c>Harlinn::Common::Core::Exception</c>, reports it with <c>ReportException</c>
///     and returns the HRESULT carried by that exception (<c>exception.GetHRESULT()</c>).
///   - Catches <c>std::exception</c>, reports it and returns <c>E_FAIL</c>.
///   - Catches all other exceptions, reports them via <c>ReportUnknownException</c> and returns <c>E_FAIL</c>.
/// - The macro appends a final <c>return S_OK</c> after the catch handlers so it can be used
///   at the end of functions that return <c>HRESULT</c>.
/// - Location information passed to the reporting functions uses <c>CURRENT_FUNCTION</c>, <c>CURRENT_FILE</c> and <c>__LINE__</c>.
/// </remarks>
/// <example>
/// try
/// {
///     // COM operation that may throw
/// }
/// HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
/// </example>
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


// <summary>
/// Catches exceptions from a preceding try block, reports them using the project's centralized
/// exception reporting functions and then returns from the current function.
/// </summary>
/// <remarks>
/// Intended for use at the end of functions that return no value (for example, <c>void</c> functions)
/// or in places where a plain <c>return</c> is the desired control-flow to exit the function after
/// reporting. Place this macro immediately after a corresponding <c>try</c> block so all exceptions
/// are consistently logged and reported.
/// <para/>
/// Behavior:
/// - Catches <c>Harlinn::Common::Core::Exception</c> and forwards it to <c>ReportException</c>
///   together with location information provided by <c>CURRENT_FUNCTION</c>, <c>CURRENT_FILE</c> and <c>__LINE__</c>.
/// - Catches <c>std::exception</c> and forwards it to <c>ReportException</c> with the same location info.
/// - Catches all other exception types and forwards them to <c>ReportUnknownException</c> with location info.
/// After handling, the macro executes a bare <c>return</c> to exit the enclosing function.
/// </remarks>
/// <example>
/// try
/// {
///     // Do work that may throw
/// }
/// HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN();
/// </example>
/// <seealso cref="HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT">
/// Use the _RETURN_HRESULT variant for COM methods that return an HRESULT.
/// </seealso>
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
