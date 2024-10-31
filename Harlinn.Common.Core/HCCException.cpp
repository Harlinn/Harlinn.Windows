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
#include <HCCException.h>
#include <HCCString.h>
#include <HCCLogging.h>
#include <HCCThread.h>

#pragma comment(lib,"DbgHelp.lib" )

namespace Harlinn::Common::Core
{
    void LogStackTrace( )
    {
        HANDLE process = GetCurrentProcess( );
        HANDLE thread = GetCurrentThread( );

        CONTEXT context = { 0, };
        context.ContextFlags = CONTEXT_FULL;
        RtlCaptureContext( &context );

        SymInitialize( process, NULL, TRUE );

        STACKFRAME64 stackframe = { 0, };

#ifdef _M_IX86
        DWORD image = IMAGE_FILE_MACHINE_I386;
        stackframe.AddrPC.Offset = context.Eip;
        stackframe.AddrPC.Mode = AddrModeFlat;
        stackframe.AddrFrame.Offset = context.Ebp;
        stackframe.AddrFrame.Mode = AddrModeFlat;
        stackframe.AddrStack.Offset = context.Esp;
        stackframe.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
        DWORD image = IMAGE_FILE_MACHINE_AMD64;
        stackframe.AddrPC.Offset = context.Rip;
        stackframe.AddrPC.Mode = AddrModeFlat;
        stackframe.AddrFrame.Offset = context.Rsp;
        stackframe.AddrFrame.Mode = AddrModeFlat;
        stackframe.AddrStack.Offset = context.Rsp;
        stackframe.AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
        DWORD image = IMAGE_FILE_MACHINE_IA64;
        stackframe.AddrPC.Offset = context.StIIP;
        stackframe.AddrPC.Mode = AddrModeFlat;
        stackframe.AddrFrame.Offset = context.IntSp;
        stackframe.AddrFrame.Mode = AddrModeFlat;
        stackframe.AddrBStore.Offset = context.RsBSP;
        stackframe.AddrBStore.Mode = AddrModeFlat;
        stackframe.AddrStack.Offset = context.IntSp;
        stackframe.AddrStack.Mode = AddrModeFlat;
#endif
        for ( size_t i = 0; i < 50; i++ )
        {
            auto result = StackWalk64( image, process, thread, &stackframe, &context, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL );

            if ( result )
            {
                char buffer[sizeof( SYMBOL_INFO ) + MAX_SYM_NAME * sizeof( TCHAR )];
                PSYMBOL_INFO symbol = (PSYMBOL_INFO)buffer;
                symbol->SizeOfStruct = sizeof( SYMBOL_INFO );
                symbol->MaxNameLen = MAX_SYM_NAME;

                DWORD64 displacement = 0;
                if ( SymFromAddr( process, stackframe.AddrPC.Offset, &displacement, symbol ) )
                {
                    //HCC_INFO( L"[%d] %C\n", i, symbol->Name );
                }
                else
                {
                    //HCC_INFO( L"[%d] <missing symbol info>\n", i );
                }
            }
            else
            {
                break;
            }

        }
        SymCleanup( process );
    }



    HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( SystemException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( AppDomainUnloadedException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ArrayTypeMismatchException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( AccessViolationException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( AggregateException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ApplicationException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ArgumentException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ArgumentNullException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ArgumentOutOfRangeException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ArithmeticException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( BadImageFormatException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( CannotUnloadAppDomainException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ContextMarshalException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( DataMisalignedException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ExecutionEngineException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( TypeLoadException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( DivideByZeroException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( DllNotFoundException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( DuplicateWaitObjectException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( EntryPointNotFoundException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( MemberAccessException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( FieldAccessException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( FormatException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( IndexOutOfRangeException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( InsufficientExecutionStackException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( OutOfMemoryException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( InsufficientMemoryException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( InvalidCastException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( InvalidOperationException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( InvalidProgramException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( InvalidTimeZoneException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( MethodAccessException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( MissingMemberException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( MissingFieldException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( MissingMethodException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( MulticastNotSupportedException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( NotFiniteNumberException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( NotImplementedException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( NotSupportedException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( NullReferenceException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( OperationCanceledException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( OverflowException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( PlatformNotSupportedException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( RankException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( StackOverflowException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( TimeoutException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( TypeInitializationException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( TypeUnloadedException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( UnauthorizedAccessException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( UriFormatException )
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( UriTemplateMatchException )

    namespace IO
    {
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( IOException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( DirectoryNotFoundException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( DriveNotFoundException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( EndOfStreamException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( FileLoadException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( FileNotFoundException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( PathTooLongException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( PipeException )

        namespace IsolatedStorage
        {
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( IsolatedStorageException )
        }
        namespace Sockets
        {
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( SocketException )
        }

    };


    namespace Reflection
    {
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( CustomAttributeFormatException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( InvalidFilterCriteriaException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ReflectionTypeLoadException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( TargetException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( TargetInvocationException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( TargetParameterCountException )
    }

    namespace Runtime
    {
        namespace InteropServices
        {
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ExternalException )
                HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( COMException )
                HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( InvalidComObjectException )
                HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( InvalidOleVariantTypeException )
                HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( MarshalDirectiveException )
                HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( SafeArrayTypeMismatchException )
                HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( SafeArrayRankMismatchException )
                HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( SEHException )
        }
        namespace Remoting
        {
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( RemotingException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( RemotingTimeoutException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ServerException )
            namespace MetadataServices
            {
                HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( SUDSGeneratorException )
                    HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( SUDSParserException )
            }
        }
        namespace Serialization
        {
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( SerializationException )
        }
    }

    namespace Data
    {
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( DbException )
        namespace OracleClient
        {
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( OracleException )
        }
    }

    namespace Messaging
    {
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( MessageQueueException )
    }


    namespace Resources
    {
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( MissingManifestResourceException )
    }


    namespace Security
    {
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( SecurityException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( VerificationException )

            namespace Cryptography
        {
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( CryptographicException )
                HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( CryptographicUnexpectedOperationException )
        }
        namespace Policy
        {
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( PolicyException )
        }
    }

    namespace Threading
    {
        HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( SynchronizationLockException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ThreadAbortException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ThreadInterruptedException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ThreadStateException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( ThreadStopException )
            HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( WaitHandleCannotBeOpenedException )
    }

    // ----------------------------------------------------------------------------
    // ExceptionLocationData
    // ----------------------------------------------------------------------------
    class ExceptionLocationData
    {
        long referenceCount_;
        WideString function_;
        WideString filename_;
        int lineNumber_;
    public:
        ExceptionLocationData( const char* function, const char* filename, int lineNumber )
            : referenceCount_( 1 ), function_( ToWideString( function ) ), filename_( ToWideString( filename ) ), lineNumber_( lineNumber )
        {
        }
        ExceptionLocationData( const wchar_t* function, const wchar_t* filename, int lineNumber )
            : referenceCount_( 1 ), function_( function ), filename_( filename ), lineNumber_( lineNumber )
        {
        }
        ExceptionLocationData( const WideString& function, const WideString& filename, int lineNumber )
            : referenceCount_( 1 ), function_( function ), filename_( filename ), lineNumber_( lineNumber )
        {
        }
        ExceptionLocationData( const AnsiString& function, const AnsiString& filename, int lineNumber )
            : referenceCount_( 1 ), function_( ToWideString( function ) ), filename_( ToWideString( filename ) ), lineNumber_( lineNumber )
        {
        }

        long AddReference( )
        {
            return InterlockedIncrement( &referenceCount_ );
        }

        long Release( )
        {
            auto result = InterlockedDecrement( &referenceCount_ );
            if ( !result )
            {
                delete this;
            }
            return result;
        }



        const WideString& Function( ) const
        {
            return function_;
        }
        const WideString& Filename( ) const
        {
            return filename_;
        }
        int LineNumber( ) const
        {
            return lineNumber_;
        }
    };

    // ----------------------------------------------------------------------------
    // ExceptionLocation
    // ----------------------------------------------------------------------------

    ExceptionLocation::ExceptionLocation( const char* function, const char* filename, int lineNumber )
        : data_( new ExceptionLocationData( function, filename, lineNumber ) )
    {
    }
    ExceptionLocation::ExceptionLocation( const wchar_t* function, const wchar_t* filename, int lineNumber )
        : data_( new ExceptionLocationData( function, filename, lineNumber ) )
    {
    }
    ExceptionLocation::ExceptionLocation( const WideString& function, const WideString& filename, int lineNumber )
        : data_( new ExceptionLocationData( function, filename, lineNumber ) )
    {
    }
    ExceptionLocation::ExceptionLocation( const AnsiString& function, const AnsiString& filename, int lineNumber )
        : data_( new ExceptionLocationData( function, filename, lineNumber ) )
    {
    }

    ExceptionLocation::ExceptionLocation( const ExceptionLocation& theOther )
        : data_( theOther.data_ )
    {
        if ( data_ )
        {
            data_->AddReference( );
        }
    }

    ExceptionLocation::~ExceptionLocation( )
    {
        if ( data_ )
        {
            data_->Release( );
        }
    }

    ExceptionLocation& ExceptionLocation::operator = ( const ExceptionLocation& theOther )
    {
        if ( data_ != theOther.data_ )
        {
            if ( data_ )
            {
                data_->Release( );
            }
            data_ = theOther.data_;
            if ( data_ )
            {
                data_->AddReference( );
            }
        }
        return *this;
    }

    WideString ExceptionLocation::Function( ) const
    {
        if ( data_ )
        {
            return data_->Function( );
        }
        return {};
    }
    WideString ExceptionLocation::Filename( ) const
    {
        if ( data_ )
        {
            return data_->Filename( );
        }
        return {};
    }
    int ExceptionLocation::LineNumber( ) const
    {
        if ( data_ )
        {
            return data_->LineNumber( );
        }
        return -1;
    }



    // ----------------------------------------------------------------------------
    // ExceptionData
    // ----------------------------------------------------------------------------
    class ExceptionData
    {

        mutable AnsiString ansiMessage_;
        WideString message_;
        WideString helpLink_;
        WideString source_;
        HRESULT hResult_;
        long long code_;
        ExceptionData* innerException_;
        std::unordered_map<int, WideString> data_;
        ExceptionLocation location_;
    public:
        explicit ExceptionData( );
        explicit ExceptionData( const ExceptionData& theInnerException );
        explicit ExceptionData( const char* theMessage );
        explicit ExceptionData( const wchar_t* theMessage );
        explicit ExceptionData( const AnsiString& theMessage );
        explicit ExceptionData( const WideString& theMessage );
        ExceptionData( const char* theMessage, const ExceptionData* theInnerException );
        ExceptionData( const wchar_t* theMessage, const ExceptionData* theInnerException );
        ExceptionData( long long theCode, const char* theMessage );
        ExceptionData( long long theCode, const wchar_t* theMessage );
        ExceptionData( long long theCode, const AnsiString& theMessage );
        ExceptionData( long long theCode, const WideString& theMessage );
        ExceptionData( HRESULT hResult, long long theCode, const char* theMessage );
        ExceptionData( HRESULT hResult, long long theCode, const wchar_t* theMessage );
        ExceptionData( HRESULT hResult, long long theCode, const AnsiString& theMessage );
        ExceptionData( HRESULT hResult, long long theCode, const WideString& theMessage );

        explicit ExceptionData( const ExceptionLocation& theLocation );
        ExceptionData( const ExceptionLocation& theLocation, const ExceptionData& theInnerException );
        ExceptionData( const ExceptionLocation& theLocation, const char* theMessage );
        ExceptionData( const ExceptionLocation& theLocation, const wchar_t* theMessage );
        ExceptionData( const ExceptionLocation& theLocation, const AnsiString& theMessage );
        ExceptionData( const ExceptionLocation& theLocation, const WideString& theMessage );
        ExceptionData( const ExceptionLocation& theLocation, const char* theMessage, const ExceptionData* theInnerException );
        ExceptionData( const ExceptionLocation& theLocation, const wchar_t* theMessage, const ExceptionData* theInnerException );
        ExceptionData( const ExceptionLocation& theLocation, long long theCode, const char* theMessage );
        ExceptionData( const ExceptionLocation& theLocation, long long theCode, const wchar_t* theMessage );
        ExceptionData( const ExceptionLocation& theLocation, long long theCode, const AnsiString& theMessage );
        ExceptionData( const ExceptionLocation& theLocation, long long theCode, const WideString& theMessage );
        ExceptionData( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const char* theMessage );
        ExceptionData( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const wchar_t* theMessage );
        ExceptionData( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const AnsiString& theMessage );
        ExceptionData( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const WideString& theMessage );


        ~ExceptionData( );

        ExceptionData* Clone( ) const;


        const AnsiString& AnsiMessage( ) const
        {
            if ( ansiMessage_.empty() )
            {
                ansiMessage_ = ToAnsiString( message_ );
            }
            return ansiMessage_;
        }

        const WideString& Message( ) const;
        const char* what( ) const;
        ExceptionData& SetMessage( const char* theValue );
        ExceptionData& SetMessage( const wchar_t* theValue );
        ExceptionData& SetMessage( const AnsiString& theValue );
        ExceptionData& SetMessage( const WideString& theValue );

        WideString GetHelpLink( ) const;
        ExceptionData& SetHelpLink( const char* theValue );
        ExceptionData& SetHelpLink( const wchar_t* theValue );
        ExceptionData& SetHelpLink( const AnsiString& theValue );
        ExceptionData& SetHelpLink( const WideString& theValue );

        HRESULT GetHRESULT( ) const;
        ExceptionData& SetHRESULT( HRESULT theValue );

        long long GetCode( ) const;
        ExceptionData& SetCode( long long theValue );


        const ExceptionData* GetInnerException( ) const;
        ExceptionData& SetInnerException( const ExceptionData* theValue );

        WideString GetSource( ) const;
        ExceptionData& SetSource( const char* theValue );
        ExceptionData& SetSource( const wchar_t* theValue );
        ExceptionData& SetSource( const AnsiString& theValue );
        ExceptionData& SetSource( const WideString& theValue );

        WideString GetData( int id ) const;
        ExceptionData& SetData( int id, const char* theValue );
        ExceptionData& SetData( int id, const wchar_t* theValue );
        ExceptionData& SetData( int id, const AnsiString& theValue );
        ExceptionData& SetData( int id, const WideString& theValue );

        ExceptionLocation GetLocation( ) const
        {
            return location_;
        }

    };


    // ----------------------------------------------------------------------
    // ExceptionData
    // ----------------------------------------------------------------------
    ExceptionData::ExceptionData( )
        : hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const ExceptionData& other )
        : message_( other.message_ ),
          helpLink_( other.helpLink_ ),
          source_( other.source_ ),
          hResult_( other.hResult_ ),
          code_( other.code_ ),
          innerException_( nullptr ),
          data_( other.data_ )
    {
        if ( other.innerException_ )
        {
            innerException_ = other.innerException_->Clone( );
        }
    }

    ExceptionData::ExceptionData( const char* theMessage )
        : message_( ToWideString( theMessage ) ),
          hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const wchar_t* theMessage )
        : message_( theMessage ),
          hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
    }



    ExceptionData::ExceptionData( const AnsiString& theMessage )
        : message_( ToWideString( theMessage ) ),
          hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const WideString& theMessage )
        : message_( theMessage ),
          hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const char* theMessage, const ExceptionData* theInnerException )
        : message_( ToWideString( theMessage ) ),
          hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
        if ( theInnerException )
        {
            innerException_ = theInnerException->Clone( );
        }
    }

    ExceptionData::ExceptionData( const wchar_t* theMessage, const ExceptionData* theInnerException )
        : message_( theMessage ),
          hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
        if ( theInnerException )
        {
            innerException_ = theInnerException->Clone( );
        }
    }

    ExceptionData::ExceptionData( long long theCode, const char* theMessage )
        : message_( ToWideString( theMessage ) ),
          hResult_( 0 ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( long long theCode, const wchar_t* theMessage )
        : message_( theMessage ),
          hResult_( 0 ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( long long theCode, const AnsiString& theMessage )
        : message_( ToWideString( theMessage ) ),
          hResult_( 0 ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( long long theCode, const WideString& theMessage )
        : message_( theMessage ),
          hResult_( 0 ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( HRESULT hResult, long long theCode, const char* theMessage )
        : message_( ToWideString( theMessage ) ),
          hResult_( hResult ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( HRESULT hResult, long long theCode, const wchar_t* theMessage )
        : message_( theMessage ),
          hResult_( hResult ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( HRESULT hResult, long long theCode, const AnsiString& theMessage )
        : message_( ToWideString( theMessage ) ),
          hResult_( hResult ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( HRESULT hResult, long long theCode, const WideString& theMessage )
        : message_( theMessage ),
          hResult_( hResult ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    // ------------------------------------------------------------
    ExceptionData::ExceptionData( const ExceptionLocation& theLocation )
        : location_( theLocation ),
          hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, const ExceptionData& theException )
        : location_( theLocation ),
        message_( theException.message_ ),
        helpLink_( theException.helpLink_ ),
        source_( theException.source_ ),
        hResult_( theException.hResult_ ),
        code_( theException.code_ ),
        innerException_( nullptr ),
        data_( theException.data_ )
    {
        if ( theException.innerException_ )
        {
            innerException_ = theException.innerException_->Clone( );
        }
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, const char* theMessage )
        : location_( theLocation ), 
          message_( ToWideString( theMessage ) ),
          hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, const wchar_t* theMessage )
        : location_( theLocation ), 
          message_( theMessage ),
          hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
    }



    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, const AnsiString& theMessage )
        : location_( theLocation ), 
          message_( ToWideString( theMessage ) ),
          hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, const WideString& theMessage )
        : location_( theLocation ), 
          message_( theMessage ),
          hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, const char* theMessage, const ExceptionData* theInnerException )
        : location_( theLocation ), 
          message_( ToWideString( theMessage ) ),
          hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
        if ( theInnerException )
        {
            innerException_ = theInnerException->Clone( );
        }
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, const wchar_t* theMessage, const ExceptionData* theInnerException )
        : location_( theLocation ), 
          message_( theMessage ),
          hResult_( 0 ),
          code_( 0 ),
          innerException_( nullptr )
    {
        if ( theInnerException )
        {
            innerException_ = theInnerException->Clone( );
        }
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, long long theCode, const char* theMessage )
        : location_( theLocation ), 
          message_( ToWideString( theMessage ) ),
          hResult_( 0 ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, long long theCode, const wchar_t* theMessage )
        : location_( theLocation ), 
          message_( theMessage ),
          hResult_( 0 ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, long long theCode, const AnsiString& theMessage )
        : location_( theLocation ), 
          message_( ToWideString( theMessage ) ),
          hResult_( 0 ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, long long theCode, const WideString& theMessage )
        : location_( theLocation ), 
          message_( theMessage ),
          hResult_( 0 ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const char* theMessage )
        : location_( theLocation ), 
          message_( ToWideString( theMessage ) ),
          hResult_( hResult ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const wchar_t* theMessage )
        : location_( theLocation ), 
          message_( theMessage ),
          hResult_( hResult ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const AnsiString& theMessage )
        : location_( theLocation ), 
          message_( ToWideString( theMessage ) ),
          hResult_( hResult ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }

    ExceptionData::ExceptionData( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const WideString& theMessage )
        : location_( theLocation ), 
          message_( theMessage ),
          hResult_( hResult ),
          code_( theCode ),
          innerException_( nullptr )
    {
    }


    ExceptionData::~ExceptionData( )
    {
        if ( innerException_ )
        {
            delete innerException_;
        }
    }

    ExceptionData* ExceptionData::Clone( ) const
    {
        ExceptionData* result = new ExceptionData( *this );
        return result;
    }

    const WideString& ExceptionData::Message( ) const
    {
        return message_;
    }

    const char* ExceptionData::what( ) const
    {
        if ( ansiMessage_.empty( ) )
        {
            ansiMessage_ = ToAnsiString( message_ );
        }
        return ansiMessage_.c_str( );
    }

    ExceptionData& ExceptionData::SetMessage( const char* theValue )
    {
        message_ = ToWideString( theValue );
        ansiMessage_ = AnsiString( );
        return *this;
    }

    ExceptionData& ExceptionData::SetMessage( const wchar_t* theValue )
    {
        message_ = ToWideString( theValue );
        ansiMessage_ = AnsiString( );
        return *this;
    }

    ExceptionData& ExceptionData::SetMessage( const AnsiString& theValue )
    {
        message_ = ToWideString( theValue );
        ansiMessage_ = theValue;
        return *this;
    }

    ExceptionData& ExceptionData::SetMessage( const WideString& theValue )
    {
        message_ = theValue;
        ansiMessage_ = AnsiString( );
        return *this;
    }

    WideString ExceptionData::GetHelpLink( ) const
    {
        return helpLink_;
    }
    ExceptionData& ExceptionData::SetHelpLink( const char* theValue )
    {
        helpLink_ = ToWideString( theValue );
        return *this;
    }

    ExceptionData& ExceptionData::SetHelpLink( const wchar_t* theValue )
    {
        helpLink_ = ToWideString( theValue );
        return *this;
    }

    ExceptionData& ExceptionData::SetHelpLink( const AnsiString& theValue )
    {
        helpLink_ = ToWideString( theValue );
        return *this;
    }

    ExceptionData& ExceptionData::SetHelpLink( const WideString& theValue )
    {
        helpLink_ = theValue;
        return *this;
    }

    HRESULT ExceptionData::GetHRESULT( ) const
    {
        return hResult_;
    }
    ExceptionData& ExceptionData::SetHRESULT( HRESULT theValue )
    {
        hResult_ = theValue;
        return *this;
    }

    long long ExceptionData::GetCode( ) const
    {
        return code_;
    }
    ExceptionData& ExceptionData::SetCode( long long theValue )
    {
        code_ = theValue;
        return *this;
    }


    const ExceptionData* ExceptionData::GetInnerException( ) const
    {
        return innerException_;
    }
    ExceptionData& ExceptionData::SetInnerException( const ExceptionData* theValue )
    {
        if ( innerException_ != theValue )
        {
            if ( innerException_ )
            {
                delete innerException_;
            }
            innerException_ = nullptr;
            if ( theValue )
            {
                innerException_ = theValue->Clone( );
            }
        }
        return *this;
    }

    WideString ExceptionData::GetSource( ) const
    {
        return source_;
    }
    ExceptionData& ExceptionData::SetSource( const char* theValue )
    {
        source_ = ToWideString( theValue );
        return *this;
    }

    ExceptionData& ExceptionData::SetSource( const wchar_t* theValue )
    {
        source_ = ToWideString( theValue );
        return *this;
    }

    ExceptionData& ExceptionData::SetSource( const AnsiString& theValue )
    {
        source_ = ToWideString( theValue );
        return *this;
    }

    ExceptionData& ExceptionData::SetSource( const WideString& theValue )
    {
        source_ = theValue;
        return *this;
    }

    WideString ExceptionData::GetData( int id ) const
    {
        auto parameter = data_.find( id );
        return parameter != data_.end( ) ? parameter->second : WideString( );
    }

    ExceptionData& ExceptionData::SetData( const int id, const char* theValue )
    {
        data_[id] = ToWideString( theValue );
        return *this;
    }

    ExceptionData& ExceptionData::SetData( const int id, const wchar_t* theValue )
    {
        data_[id] = ToWideString( theValue );
        return *this;
    }

    ExceptionData& ExceptionData::SetData( const int id, const AnsiString& theValue )
    {
        data_[id] = ToWideString( theValue );
        return *this;
    }

    ExceptionData& ExceptionData::SetData( const int id, const WideString& theValue )
    {
        data_[id] = theValue;
        return *this;
    }



    // ----------------------------------------------------------------------
    // Exception
    // ----------------------------------------------------------------------
    AnsiString Exception::empty;
    const ExceptionData* Exception::GetExceptionData( ) const
    {
        return data;
    }
    ExceptionData* Exception::GetExceptionData( )
    {
        if ( !data )
        {
            data = new ExceptionData( );
        }
        return data;
    }

    __declspec( thread ) wchar_t ExceptionFormatBuffer[1024];
    WideString Exception::Format( const char* fmt, ... )
    {
        va_list args;
        va_start( args, fmt );
        char* buffer = (char*)ExceptionFormatBuffer;
        AnsiString::size_type length = vsnprintf_s( buffer, 1023, _TRUNCATE, fmt, args );
        buffer[1023] = '\x0';
        AnsiString result( buffer, length );
        va_end( args );
        return ToWideString( result );
    }

    WideString Exception::Format( const wchar_t* fmt, ... )
    {
        va_list args;
        va_start( args, fmt );
        WideString::size_type length = _vsnwprintf_s( ExceptionFormatBuffer, 1023, fmt, args );
        ExceptionFormatBuffer[1023] = '\x0';
        WideString result( ExceptionFormatBuffer, length );
        va_end( args );
        return result;
    }

    WideString Exception::FormatList( const char* fmt, va_list args )
    {
        char* buffer = (char*)ExceptionFormatBuffer;
        AnsiString::size_type length = vsnprintf_s( buffer, 1023, _TRUNCATE, fmt, args );
        buffer[1023] = '\x0';
        AnsiString result( buffer, length );
        return ToWideString( result );
    }

    WideString Exception::FormatList( const wchar_t* fmt, va_list args )
    {
        WideString::size_type length = _vsnwprintf_s( ExceptionFormatBuffer, 1023, fmt, args );
        ExceptionFormatBuffer[1023] = '\x0';
        WideString result( ExceptionFormatBuffer, length );
        return result;
    }


    Exception::Exception( )
        : data( nullptr )
    {

    }

    Exception::Exception( const Exception& theException )
        : data( nullptr )
    {
        if ( theException.data )
        {
            data = theException.data->Clone( );
        }
    }

    Exception::Exception( const char* theMessage )
        : data( nullptr )
    {
        if ( theMessage )
        {
            data = new ExceptionData( theMessage );
        }
    }

    Exception::Exception( const wchar_t* theMessage )
        : data( nullptr )
    {
        if ( theMessage )
        {
            data = new ExceptionData( theMessage );
        }
    }

    Exception::Exception( const AnsiString& theMessage )
        : data( nullptr )
    {
        data = new ExceptionData( theMessage );
    }

    Exception::Exception( const WideString& theMessage )
        : data( nullptr )
    {
        data = new ExceptionData( theMessage );
    }

    Exception::Exception( const char* theMessage, const Exception& theInnerException )
    {
        data = new ExceptionData( theMessage, theInnerException.data );
    }

    Exception::Exception( const wchar_t* theMessage, const Exception& theInnerException )
    {
        data = new ExceptionData( theMessage, theInnerException.data );
    }

    Exception::Exception( long long theCode, const char* theMessage )
    {
        data = new ExceptionData( theCode, theMessage );
    }

    Exception::Exception( long long code, const wchar_t* message )
    {
        data = new ExceptionData( code, message );
    }

    Exception::Exception( long long theCode, const AnsiString& theMessage )
    {
        data = new ExceptionData( theCode, theMessage );
    }

    Exception::Exception( long long theCode, const WideString& theMessage )
    {
        data = new ExceptionData( theCode, theMessage );
    }

    Exception::Exception( HRESULT hResult, long long theCode, const char* theMessage )
    {
        data = new ExceptionData( hResult, theCode, theMessage );
    }

    Exception::Exception( HRESULT hResult, long long theCode, const wchar_t* theMessage )
    {
        data = new ExceptionData( hResult, theCode, theMessage );
    }

    Exception::Exception( HRESULT hResult, long long theCode, const AnsiString& theMessage )
    {
        data = new ExceptionData( hResult, theCode, theMessage );
    }

    Exception::Exception( HRESULT hResult, long long theCode, const WideString& theMessage )
    {
        data = new ExceptionData( hResult, theCode, theMessage );
    }



    // -----------------------------------------------------------------------
    Exception::Exception( const ExceptionLocation& theLocation )
        : data( nullptr )
    {
        data = new ExceptionData( theLocation );
    }

    Exception::Exception( const ExceptionLocation& theLocation, const char* theMessage )
        : data( nullptr )
    {
        data = new ExceptionData( theLocation, theMessage );
    }

    Exception::Exception( const ExceptionLocation& theLocation, const wchar_t* theMessage )
        : data( nullptr )
    {
        data = new ExceptionData( theLocation, theMessage );
    }

    Exception::Exception( const ExceptionLocation& theLocation, const AnsiString& theMessage )
        : data( nullptr )
    {
        data = new ExceptionData( theLocation, theMessage );
    }

    Exception::Exception( const ExceptionLocation& theLocation, const WideString& theMessage )
        : data( nullptr )
    {
        data = new ExceptionData( theLocation, theMessage );
    }

    Exception::Exception( const ExceptionLocation& theLocation, const char* theMessage, const Exception& theInnerException )
    {
        data = new ExceptionData( theLocation, theMessage, theInnerException.data );
    }

    Exception::Exception( const ExceptionLocation& theLocation, const wchar_t* theMessage, const Exception& theInnerException )
    {
        data = new ExceptionData( theLocation, theMessage, theInnerException.data );
    }

    Exception::Exception( const ExceptionLocation& theLocation, long long theCode, const char* theMessage )
    {
        data = new ExceptionData( theLocation, theCode, theMessage );
    }

    Exception::Exception( const ExceptionLocation& theLocation, long long theCode, const AnsiString& theMessage )
    {
        data = new ExceptionData( theLocation, theCode, theMessage );
    }

    Exception::Exception( const ExceptionLocation& theLocation, long long theCode, const WideString& theMessage )
    {
        data = new ExceptionData( theLocation, theCode, theMessage );
    }

    Exception::Exception( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const char* theMessage )
    {
        data = new ExceptionData( theLocation, hResult, theCode, theMessage );
    }

    Exception::Exception( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const wchar_t* theMessage )
    {
        data = new ExceptionData( theLocation, hResult, theCode, theMessage );
    }

    Exception::Exception( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const AnsiString& theMessage )
    {
        data = new ExceptionData( theLocation, hResult, theCode, theMessage );
    }

    Exception::Exception( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const WideString& theMessage )
    {
        data = new ExceptionData( theLocation, hResult, theCode, theMessage );
    }


    Exception::~Exception( )
    {
        if ( data )
        {
            delete data;
        }
    }


    Exception& Exception::operator = ( const Exception& theException )
    {
        if ( data != theException.data )
        {
            if ( data )
            {
                delete data;
                data = nullptr;
            }
            if ( theException.data )
            {
                data = theException.data->Clone( );
            }
        }
        return *this;
    }

    bool Exception::IsA( ExceptionType theKind ) const
    {
        return _IsA( theKind );
    }

    ExceptionType Exception::Kind( ) const
    {
        return KIND;
    }

    const char* Exception::what( ) const
    {
        auto exceptionData = GetExceptionData( );
        if ( exceptionData )
        {
            return exceptionData->what( );
        }
        return empty.c_str( );
    }


    WideString Exception::Message( ) const
    {
        auto exceptionData = GetExceptionData( );
        if ( exceptionData )
        {
            return exceptionData->Message( );
        }
        return WideString( );
    }

    Exception& Exception::SetMessage( const char* theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetMessage( theValue );
        return *this;
    }

    Exception& Exception::SetMessage( const wchar_t* theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetMessage( theValue );
        return *this;
    }

    Exception& Exception::SetMessage( const AnsiString& theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetMessage( theValue );
        return *this;
    }

    Exception& Exception::SetMessage( const WideString& theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetMessage( theValue );
        return *this;
    }



    WideString Exception::GetHelpLink( ) const
    {
        auto exceptionData = GetExceptionData( );
        if ( exceptionData )
        {
            return exceptionData->GetHelpLink( );
        }
        return WideString( );
    }

    Exception& Exception::SetHelpLink( const char* theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetHelpLink( theValue );
        return *this;
    }

    Exception& Exception::SetHelpLink( const wchar_t* theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetHelpLink( theValue );
        return *this;
    }

    Exception& Exception::SetHelpLink( const AnsiString& theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetHelpLink( theValue );
        return *this;
    }

    Exception& Exception::SetHelpLink( const WideString& theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetHelpLink( theValue );
        return *this;
    }


    HRESULT Exception::GetHRESULT( ) const
    {
        auto exceptionData = GetExceptionData( );
        if ( exceptionData )
        {
            return exceptionData->GetHRESULT( );
        }
        return 0;
    }

    Exception& Exception::SetHRESULT( HRESULT theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetHRESULT( theValue );
        return *this;
    }


    long long Exception::GetCode( ) const
    {
        auto exceptionData = GetExceptionData( );
        if ( exceptionData )
        {
            return exceptionData->GetCode( );
        }
        return 0;
    }

    Exception& Exception::SetCode( long long theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetCode( theValue );
        return *this;
    }


    const ExceptionData* Exception::GetInnerException( ) const
    {
        auto exceptionData = GetExceptionData( );
        if ( exceptionData )
        {
            return exceptionData->GetInnerException( );
        }
        return nullptr;
    }

    Exception& Exception::SetInnerException( const Exception& theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetInnerException( theValue.data );
        return *this;
    }

    WideString Exception::GetSource( ) const
    {
        auto exceptionData = GetExceptionData( );
        if ( exceptionData )
        {
            return exceptionData->GetSource( );
        }
        return WideString( );
    }

    Exception& Exception::SetSource( const char* theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetSource( theValue );
        return *this;
    }

    Exception& Exception::SetSource( const AnsiString& theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetSource( theValue );
        return *this;
    }

    Exception& Exception::SetSource( const WideString& theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetSource( theValue );
        return *this;
    }

    WideString Exception::GetData( int id ) const
    {
        auto exceptionData = GetExceptionData( );
        auto result = exceptionData->GetData( id );
        return result;
    }
    Exception& Exception::SetData( int id, const char* theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetData( id, theValue );
        return *this;
    }
    Exception& Exception::SetData( int id, const AnsiString& theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetData( id, theValue );
        return *this;
    }

    Exception& Exception::SetData( int id, const WideString& theValue )
    {
        auto exceptionData = GetExceptionData( );
        exceptionData->SetData( id, theValue );
        return *this;
    }

    ExceptionLocation Exception::GetLocation( ) const
    {
        auto exceptionData = GetExceptionData( );
        if ( exceptionData )
        {
            return exceptionData->GetLocation( );
        }
        return ExceptionLocation( );
    }

    void Exception::Log( ) throw( )
    {
        try
        {
            auto exceptionLocation = GetLocation( );
            WideString file = exceptionLocation.Filename( );
            WideString function = exceptionLocation.Function( );
            auto lineNumber = exceptionLocation.LineNumber( );

            auto message = this->Message( );
            WideString messageText;
            if ( !message.empty() )
            {
                messageText = TypeName( ) + L":" + message;
            }
            else
            {
                messageText = TypeName( );
            }
            wprintf( L"Exception in %s (%s:%d) %s\n", function.c_str(), file.c_str(), lineNumber, messageText.c_str() );
        }
        catch ( ... )
        {
            DebugBreak( );
        }
    }


    WideString Exception::TypeName( ) const
    {
        const char* name = typeid( *this ).name( );
        return ToWideString( name );
    }


    // ----------------------------------------------------------------------
    // ExceptionReporter
    // ----------------------------------------------------------------------
    std::shared_ptr<ExceptionReporter> ExceptionReporter::defaultExceptionReporter_ = std::make_shared<DefaultExceptionReporter>();
    std::shared_ptr<ExceptionReporter> ExceptionReporter::currentExceptionReporter_ = defaultExceptionReporter_;
    ExceptionReporter::ExceptionReporter( ) = default;
    ExceptionReporter::~ExceptionReporter( ) = default;

    std::shared_ptr<ExceptionReporter> ExceptionReporter::Default( )
    {
        return defaultExceptionReporter_;
    }

    std::shared_ptr<ExceptionReporter> ExceptionReporter::Current( )
    {
        auto result = currentExceptionReporter_;
        if ( result )
        {
            return result;
        }
        else
        {
            return defaultExceptionReporter_;
        }
    }
    void ExceptionReporter::SetCurrent( std::shared_ptr<ExceptionReporter> exceptionReporter )
    {
        currentExceptionReporter_ = exceptionReporter;
    }


    namespace
    {
        void InternalReportException( const WideString& exceptionType, ExceptionLocation exceptionLocation, const WideString& exceptionMessage, const wchar_t* function, const wchar_t* filename, int lineNumber )
        {
            auto threadId = CurrentThread::Id( );
            auto threadDescription = CurrentThread::Description( );
            if ( threadDescription.empty( ) == false )
            {
                wprintf_s( L"%s exception caught in %s. Location: %s( %d ), Thread: Id=%d, Description=%s\n", exceptionType.c_str(), function, filename, lineNumber, threadId, threadDescription.c_str( ) );
            }
            else
            {
                wprintf_s( L"%s exception caught in %s. Location: %s( %d ), Thread: Id=%d\n", exceptionType.c_str( ), function, filename, lineNumber, threadId );
            }

            if ( exceptionLocation )
            {
                wprintf_s( L"\tThrown from %s, Location: %s( %d )\n", exceptionLocation.Function( ).c_str( ), exceptionLocation.Filename( ).c_str( ), exceptionLocation.LineNumber( ) );
            }
            if ( exceptionMessage.empty( ) == false )
            {
                wprintf_s( L"\t%s\n\n", exceptionMessage.c_str() );
            }
            else
            {
                wprintf_s( L"\n" );
            }
        }
    }

    // ----------------------------------------------------------------------
    // DefaultExceptionReporter
    // ----------------------------------------------------------------------
    DefaultExceptionReporter::DefaultExceptionReporter( ) = default;
    DefaultExceptionReporter::~DefaultExceptionReporter( ) = default;

    void DefaultExceptionReporter::ReportException( const Exception& exception, const wchar_t* function, const wchar_t* filename, int lineNumber )
    {
        auto name = exception.TypeName( );
        auto location = exception.GetLocation( );
        auto message = exception.Message( );

        InternalReportException( name, location, message, function, filename, lineNumber );
    }
    void DefaultExceptionReporter::ReportException( const std::exception& exception, const wchar_t* function, const wchar_t* filename, int lineNumber )
    {
        const char* nameStr = typeid( *this ).name( );
        auto name = ToWideString( nameStr );
        ExceptionLocation location;
        auto message = ToWideString( exception.what() );

        InternalReportException( name, location, message, function, filename, lineNumber );

    }
    void DefaultExceptionReporter::ReportUnknownException( const wchar_t* function, const wchar_t* filename, int lineNumber )
    {
        if ( function && filename )
        {
            auto threadId = CurrentThread::Id( );
            auto threadDescription = CurrentThread::Description( );
            if ( threadDescription.empty( ) == false )
            {
                wprintf_s( L"Unknown exception caught in %s. Location: %s( %d ), Thread: Id=%d, Description=%s\n", function, filename, lineNumber, threadId, threadDescription.c_str() );
            }
            else
            {
                wprintf_s( L"Unknown exception caught in %s. Location: %s( %d ), Thread: Id=%d\n", function, filename, lineNumber, threadId );
            }
        }
    }





    // ----------------------------------------------------------------------
    // ArgumentException
    // ----------------------------------------------------------------------
    ArgumentException::ArgumentException( const char* message, const char* argument )
    {
        SetMessage( message );
        GetExceptionData( )->SetData( ParamNameId, argument );
    }

    ArgumentException::ArgumentException( const wchar_t* message, const wchar_t* argument )
    {
        SetMessage( message );
        GetExceptionData( )->SetData( ParamNameId, argument );
    }

    ArgumentException::ArgumentException( const WideString& message, const char* argument )
    {
        SetMessage( message );
        GetExceptionData( )->SetData( ParamNameId, argument );
    }

    ArgumentException::ArgumentException( const WideString& message, const wchar_t* argument )
    {
        SetMessage( message );
        GetExceptionData( )->SetData( ParamNameId, argument );
    }

    ArgumentException::ArgumentException( const WideString& message, const WideString& argument )
    {
        SetMessage( message );
        GetExceptionData( )->SetData( ParamNameId, argument );
    }

    //
    ArgumentException::ArgumentException( const ExceptionLocation& theLocation, const char* message, const char* argument )
        : Base( theLocation )
    {
        SetMessage( message );
        GetExceptionData( )->SetData( ParamNameId, argument );
    }

    ArgumentException::ArgumentException( const ExceptionLocation& theLocation, const wchar_t* message, const wchar_t* argument )
        : Base( theLocation )
    {
        SetMessage( message );
        GetExceptionData( )->SetData( ParamNameId, argument );
    }

    ArgumentException::ArgumentException( const ExceptionLocation& theLocation, const WideString& message, const char* argument )
        : Base( theLocation )
    {
        SetMessage( message );
        GetExceptionData( )->SetData( ParamNameId, argument );
    }

    ArgumentException::ArgumentException( const ExceptionLocation& theLocation, const WideString& message, const wchar_t* argument )
        : Base( theLocation )
    {
        SetMessage( message );
        GetExceptionData( )->SetData( ParamNameId, argument );
    }

    ArgumentException::ArgumentException( const ExceptionLocation& theLocation, const WideString& message, const WideString& argument )
        : Base( theLocation )
    {
        SetMessage( message );
        GetExceptionData( )->SetData( ParamNameId, argument );
    }


    WideString ArgumentException::GetParamName( ) const
    {
        return GetExceptionData( )->GetData( ParamNameId );
    }

    // ----------------------------------------------------------------------
    // ArgumentOutOfRangeException
    // ----------------------------------------------------------------------
    ArgumentNullException::ArgumentNullException( const char* argument, const char* message )
        : ArgumentException( message, argument )
    {
    }

    ArgumentNullException::ArgumentNullException( const wchar_t* argument, const wchar_t* message )
        : ArgumentException( message, argument )
    {
    }


    ArgumentNullException::ArgumentNullException( const char* argument, const WideString& message )
        : ArgumentException( message, argument )
    {
    }

    ArgumentNullException::ArgumentNullException( const wchar_t* argument, const WideString& message )
        : ArgumentException( message, argument )
    {
    }

    ArgumentNullException::ArgumentNullException( const WideString& argument, const WideString& message )
        : ArgumentException( message, argument )
    {
    }


    //
    ArgumentNullException::ArgumentNullException( const ExceptionLocation& theLocation, const char* argument, const char* message )
        : ArgumentException( theLocation, message, argument )
    {
    }

    ArgumentNullException::ArgumentNullException( const ExceptionLocation& theLocation, const wchar_t* argument, const wchar_t* message )
        : ArgumentException( theLocation, message, argument )
    {
    }


    ArgumentNullException::ArgumentNullException( const ExceptionLocation& theLocation, const char* argument, const WideString& message )
        : ArgumentException( theLocation, message, argument )
    {
    }

    ArgumentNullException::ArgumentNullException( const ExceptionLocation& theLocation, const wchar_t* argument, const WideString& message )
        : ArgumentException( theLocation, message, argument )
    {
    }

    ArgumentNullException::ArgumentNullException( const ExceptionLocation& theLocation, const WideString& argument, const WideString& message )
        : ArgumentException( theLocation, message, argument )
    {
    }

    // ----------------------------------------------------------------------
    //
    // ----------------------------------------------------------------------
    ArgumentOutOfRangeException::ArgumentOutOfRangeException( const char* argument, const char* message )
        : ArgumentException( message, argument )
    {
    }

    ArgumentOutOfRangeException::ArgumentOutOfRangeException( const wchar_t* argument, const wchar_t* message )
        : ArgumentException( message, argument )
    {
    }

    ArgumentOutOfRangeException::ArgumentOutOfRangeException( const char* argument, const WideString& message )
        : ArgumentException( message, argument )
    {
    }

    ArgumentOutOfRangeException::ArgumentOutOfRangeException( const wchar_t* argument, const WideString& message )
        : ArgumentException( message, argument )
    {
    }


    ArgumentOutOfRangeException::ArgumentOutOfRangeException( const WideString& argument, const WideString& message )
        : ArgumentException( message, argument )
    {
    }

    //
    ArgumentOutOfRangeException::ArgumentOutOfRangeException( const ExceptionLocation& theLocation, const char* argument, const char* message )
        : ArgumentException( theLocation, message, argument )
    {
    }

    ArgumentOutOfRangeException::ArgumentOutOfRangeException( const ExceptionLocation& theLocation, const wchar_t* argument, const wchar_t* message )
        : ArgumentException( theLocation, message, argument )
    {
    }

    ArgumentOutOfRangeException::ArgumentOutOfRangeException( const ExceptionLocation& theLocation, const char* argument, const WideString& message )
        : ArgumentException( theLocation, message, argument )
    {
    }

    ArgumentOutOfRangeException::ArgumentOutOfRangeException( const ExceptionLocation& theLocation, const wchar_t* argument, const WideString& message )
        : ArgumentException( theLocation, message, argument )
    {
    }


    ArgumentOutOfRangeException::ArgumentOutOfRangeException( const ExceptionLocation& theLocation, const WideString& argument, const WideString& message )
        : ArgumentException( theLocation, message, argument )
    {
    }



    // ----------------------------------------------------------------------
    //
    // ----------------------------------------------------------------------
    __declspec( thread ) wchar_t buffer[512] = { 0, };
    void CheckHRESULT( HRESULT hresult )
    {
        if ( FAILED( hresult ) )
        {
            ThrowHRESULT( hresult );
        }
    }

    [[noreturn]] void ThrowHRESULT( HRESULT hresult )
    {
        int length = FormatMessageW( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hresult, 0, ( wchar_t* )buffer, 512, nullptr );
        if ( length )
        {
            wchar_t* ptr = ( wchar_t* )buffer;
            throw Runtime::InteropServices::COMException( hresult, 0, ptr );
        }
        else
        {
            throw Runtime::InteropServices::COMException( hresult, 0, L"Unknown error" );
        }
    }

    void CheckHRESULT( HRESULT hresult, IUnknown* itf )
    {
        CheckHRESULT( hresult );
    }

    void CheckHRESULT( HRESULT hresult, const wchar_t* function, const wchar_t* filename, int lineNumber )
    {
        CheckHRESULT( hresult );
    }
    void CheckHRESULT( HRESULT hresult, IUnknown* itf, const wchar_t* function, const wchar_t* filename, int lineNumber )
    {
        CheckHRESULT( hresult );
    }


    WideString FormatError( DWORD errorId )
    {
        int length = FormatMessageW( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, errorId, 0, buffer, 512, nullptr );
        return WideString( buffer, static_cast<size_t>( length ) );
    }
    AnsiString FormatErrorA( DWORD errorId )
    {
        int length = FormatMessageA( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, errorId, 0, (char*)buffer, 512, nullptr );
        return AnsiString( (char*)buffer, static_cast<size_t>( length ) );
    }


    void ThrowLastOSError( )
    {
        DWORD errorId = ::GetLastError( );
        ThrowOSError( errorId );
    }



    void ThrowOSError( DWORD errorId )
    {
        int length = 0;
        if ( errorId )
        {
            wchar_t* ptr = (wchar_t*)buffer;
            length = FormatMessageW( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, errorId, 0, (wchar_t*)buffer, 512, nullptr );
            if ( length )
            {
                throw SystemException( errorId, ptr );
            }
            else
            {
                throw SystemException( errorId, "Unknown error" );
            }
        }
    }


    void ThrowNoInterface( )
    {
        throw Runtime::InteropServices::COMException( "No interface" );
    }

    void ThrowPointerIsNULL( )
    {
        throw Exception( "pointer is null" );
    }

    void ThrowInvalidHandle( )
    {
        throw SystemException( "invalid handle" );
    }

    void ThrowNullReferenceException( )
    {
        throw NullReferenceException( );
    }
    void ThrowNullReferenceException( const char* message )
    {
        throw NullReferenceException( message );
    }
    void ThrowNullReferenceException( const wchar_t* message )
    {
        throw NullReferenceException( message );
    }


    HRESULT HRESULTFromException( const std::exception& exception )
    {
        const std::exception* ptr = &exception;
        const Exception* pException = dynamic_cast<const Exception*>( ptr );
        if ( pException )
        {
            return pException->GetHRESULT( );
        }
        else
        {
            return E_FAIL;
        }
    }



    void ReportException( const Exception& exception, const wchar_t* function, const wchar_t* filename, int lineNumber )
    {
        auto exceptionReporter = ExceptionReporter::Current( );
        exceptionReporter->ReportException( exception, function, filename, lineNumber );
    }
    void ReportException( const std::exception& exception, const wchar_t* function, const wchar_t* filename, int lineNumber )
    {
        auto exceptionReporter = ExceptionReporter::Current( );
        exceptionReporter->ReportException( exception, function, filename, lineNumber );
    }
    void ReportUnknownException( const wchar_t* function, const wchar_t* filename, int lineNumber )
    {
        auto exceptionReporter = ExceptionReporter::Current( );
        exceptionReporter->ReportUnknownException( function, filename, lineNumber );
    }

    /*
    void __cdecl NativeStructuredExceptionTranslator( unsigned int theExceptionCode, struct _EXCEPTION_POINTERS* theExceptionPointers )
    {
        switch ( theExceptionCode )
        {
            case EXCEPTION_ACCESS_VIOLATION:
                HCC_THROW( Core::AccessViolationException );
                break;
            case EXCEPTION_DATATYPE_MISALIGNMENT:
                HCC_THROW( Core::DataMisalignedException );
                break;
            case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
                HCC_THROW( Core::IndexOutOfRangeException );
                break;
            case EXCEPTION_FLT_DENORMAL_OPERAND:
                // do something sensible
                HCC_THROW( Core::ArithmeticException );
                break;
            case EXCEPTION_FLT_DIVIDE_BY_ZERO:
                // do something sensible
                HCC_THROW( Core::DivideByZeroException );
                break;
            case EXCEPTION_FLT_INEXACT_RESULT:
                // do something sensible
                HCC_THROW( Core::ArithmeticException );
                break;
            case EXCEPTION_FLT_INVALID_OPERATION:
                // do something sensible
                HCC_THROW( Core::InvalidOperationException );
                break;
            case EXCEPTION_FLT_OVERFLOW:
                // do something sensible
                HCC_THROW( Core::OverflowException );
                break;
            case EXCEPTION_FLT_STACK_CHECK:
                // do something sensible
                HCC_THROW( Core::ArithmeticException );
                break;
            case EXCEPTION_FLT_UNDERFLOW:
                // do something sensible
                HCC_THROW( Core::OverflowException );
                break;
            case EXCEPTION_INT_DIVIDE_BY_ZERO:
                // do something sensible
                HCC_THROW( Core::DivideByZeroException );
                break;
            case EXCEPTION_INT_OVERFLOW:
                // do something sensible
                HCC_THROW( Core::OverflowException );
                break;
            case EXCEPTION_PRIV_INSTRUCTION:
                // do something sensible
                HCC_THROW( Core::InvalidProgramException );
                break;
            case EXCEPTION_IN_PAGE_ERROR:
                // do something sensible
                HCC_THROW( Core::SystemException );
                break;
            case EXCEPTION_ILLEGAL_INSTRUCTION:
                // do something sensible
                HCC_THROW( Core::InvalidProgramException );
                break;
            case EXCEPTION_NONCONTINUABLE_EXCEPTION:
                // do something sensible
                HCC_THROW( Core::SystemException );
                break;
            case EXCEPTION_STACK_OVERFLOW:
                // do something sensible
                HCC_THROW( Core::InsufficientExecutionStackException );
                break;
            case EXCEPTION_INVALID_DISPOSITION:
                // do something sensible
                HCC_THROW( Core::SystemException );
                break;
            case EXCEPTION_GUARD_PAGE:
                // do something sensible
                HCC_THROW( Core::SystemException );
                break;
            case EXCEPTION_INVALID_HANDLE:
                // do something sensible
                HCC_THROW( Core::SystemException );
                break;
            case 0xC0000194: //EXCEPTION_POSSIBLE_DEADLOCK:
                // do something sensible
                HCC_THROW( Core::SystemException );
                break;
        }
    }

    */

}
