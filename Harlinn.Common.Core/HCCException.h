#pragma once
#ifndef __HCCEXCEPTION_H__
#define __HCCEXCEPTION_H__

#include <HCCDef.h>


#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
#ifdef __midl
typedef LONG HRESULT;
#else
typedef _Return_type_success_( return >= 0 ) long HRESULT;
#endif
#endif


namespace Harlinn::Common::Core
{

    enum class ExceptionType
    {
        Unknown,
        exception,
        Exception,
        SystemException,
        AppDomainUnloadedException,
        ArrayTypeMismatchException,
        AccessViolationException,
        AggregateException,
        ApplicationException,
        ArgumentException,
        ArgumentNullException,
        ArgumentOutOfRangeException,
        ArithmeticException,
        BadImageFormatException,
        CannotUnloadAppDomainException,
        ContextMarshalException,
        DataMisalignedException,
        ExecutionEngineException,
        TypeLoadException,
        DivideByZeroException,
        DllNotFoundException,
        DuplicateWaitObjectException,
        EntryPointNotFoundException,
        MemberAccessException,
        FieldAccessException,
        FormatException,
        IndexOutOfRangeException,
        InsufficientExecutionStackException,
        OutOfMemoryException,
        InsufficientMemoryException,
        InvalidCastException,
        InvalidOperationException,
        InvalidProgramException,
        InvalidTimeZoneException,
        MethodAccessException,
        MissingMemberException,
        MissingFieldException,
        MissingMethodException,
        MulticastNotSupportedException,
        NotFiniteNumberException,
        NotImplementedException,
        NotSupportedException,
        NullReferenceException,
        OperationCanceledException,
        OverflowException,
        PlatformNotSupportedException,
        RankException,
        StackOverflowException,
        TimeoutException,
        TypeInitializationException,
        TypeUnloadedException,
        UnauthorizedAccessException,
        UriFormatException,
        UriTemplateMatchException,
        IOException,
        DirectoryNotFoundException,
        DriveNotFoundException,
        EndOfStreamException,
        FileLoadException,
        FileNotFoundException,
        PathTooLongException,
        PipeException,
        IsolatedStorageException,
        SocketException,
        CustomAttributeFormatException,
        InvalidFilterCriteriaException,
        ReflectionTypeLoadException,
        TargetException,
        TargetInvocationException,
        TargetParameterCountException,
        ExternalException,
        COMException,
        InvalidComObjectException,
        InvalidOleVariantTypeException,
        MarshalDirectiveException,
        SafeArrayTypeMismatchException,
        SafeArrayRankMismatchException,
        SEHException,
        RemotingException,
        RemotingTimeoutException,
        ServerException,
        SUDSGeneratorException,
        SUDSParserException,
        SerializationException,
        DbException,
        OracleException,
        ODBCException,
        MessageQueueException,
        MissingManifestResourceException,
        SecurityException,
        VerificationException,
        CryptographicException,
        CryptographicUnexpectedOperationException,
        PolicyException,
        SynchronizationLockException,
        ThreadAbortException,
        ThreadInterruptedException,
        ThreadStateException,
        ThreadStopException,
        WaitHandleCannotBeOpenedException
    };

    class ExceptionData;
    class ExceptionLocationData;
    // ----------------------------------------------------------------------------
    // ExceptionLocation
    // ----------------------------------------------------------------------------
    class ExceptionLocation
    {
        friend class ExceptionData;
        ExceptionLocationData* data_;
    public:
        ExceptionLocation( )
            : data_( nullptr )
        {
        }

        HCC_EXPORT ExceptionLocation( const char* function, const char* filename, int lineNumber );
        HCC_EXPORT ExceptionLocation( const wchar_t* function, const wchar_t* filename, int lineNumber );
        HCC_EXPORT ExceptionLocation( const std::wstring& function, const std::wstring& filename, int lineNumber );
        HCC_EXPORT ExceptionLocation( const std::string& function, const std::string& filename, int lineNumber );

        HCC_EXPORT ExceptionLocation( const ExceptionLocation& other );
        ExceptionLocation( ExceptionLocation&& other ) noexcept
        {
            data_ = other.data_;
            other.data_ = nullptr;
        }

        HCC_EXPORT ~ExceptionLocation( );

        explicit operator bool( ) const
        {
            return data_ != nullptr;
        }


        HCC_EXPORT ExceptionLocation& operator = ( const ExceptionLocation& other );

        ExceptionLocation& operator = ( ExceptionLocation&& other ) noexcept
        {
            if ( data_ != other.data_ )
            {
                data_ = other.data_;
                other.data_ = nullptr;
            }
            return *this;
        }

        HCC_EXPORT std::wstring Function( ) const;
        HCC_EXPORT std::wstring Filename( ) const;
        HCC_EXPORT int LineNumber( ) const;
    };



    // ----------------------------------------------------------------------------
    // Exception
    // ----------------------------------------------------------------------------
    class Exception : public std::exception
    {
        ExceptionData* data;
        HCC_EXPORT static std::string empty;
    protected:
        HCC_EXPORT const ExceptionData* GetExceptionData( ) const;
        HCC_EXPORT ExceptionData* GetExceptionData( );
        HCC_EXPORT std::wstring GetData( int id ) const;
        HCC_EXPORT Exception& SetData( int id, const char* theValue );
        HCC_EXPORT Exception& SetData( int id, const wchar_t* theValue );
        HCC_EXPORT Exception& SetData( int id, const std::string& theValue );
        HCC_EXPORT Exception& SetData( int id, const std::wstring& theValue );
    public:
        typedef Exception Type;
        static const ExceptionType KIND = ExceptionType::Exception;

        HCC_EXPORT static std::wstring Format( const char* fmt, ... );
        HCC_EXPORT static std::wstring Format( const wchar_t* fmt, ... );
        static const HRESULT HRESULTForExceptionType = COR_E_EXCEPTION;
    protected:
        HCC_EXPORT static std::wstring FormatList( const char* fmt, va_list args );
        HCC_EXPORT static std::wstring FormatList( const wchar_t* fmt, va_list args );
    public:
        HCC_EXPORT explicit Exception( );
        HCC_EXPORT Exception( const Exception& theException );
        HCC_EXPORT explicit Exception( const char* theMessage );
        HCC_EXPORT explicit Exception( const wchar_t* theMessage );
        HCC_EXPORT explicit Exception( const std::string& theMessage );
        HCC_EXPORT explicit Exception( const std::wstring& theMessage );
        HCC_EXPORT Exception( const char* theMessage, const Exception& theInnerException );
        HCC_EXPORT Exception( const wchar_t* theMessage, const Exception& theInnerException );
        HCC_EXPORT Exception( long long theCode, const char* theMessage );
        HCC_EXPORT Exception( long long theCode, const wchar_t* theMessage );
        HCC_EXPORT Exception( long long theCode, const std::string& theMessage );
        HCC_EXPORT Exception( long long theCode, const std::wstring& theMessage );
        HCC_EXPORT Exception( HRESULT hResult, long long theCode, const char* theMessage );
        HCC_EXPORT Exception( HRESULT hResult, long long theCode, const wchar_t* theMessage );
        HCC_EXPORT Exception( HRESULT hResult, long long theCode, const std::string& theMessage );
        HCC_EXPORT Exception( HRESULT hResult, long long theCode, const std::wstring& theMessage );

        HCC_EXPORT explicit Exception( const ExceptionLocation& theLocation );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, const char* theMessage );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, const wchar_t* theMessage );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, const std::string& theMessage );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, const std::wstring& theMessage );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, const char* theMessage, const Exception& theInnerException );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, const wchar_t* theMessage, const Exception& theInnerException );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, long long theCode, const char* theMessage );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, long long theCode, const wchar_t* theMessage );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, long long theCode, const std::string& theMessage );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, long long theCode, const std::wstring& theMessage );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const char* theMessage );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const wchar_t* theMessage );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const std::string& theMessage );
        HCC_EXPORT Exception( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const std::wstring& theMessage );

        HCC_EXPORT virtual ~Exception( );

        HCC_EXPORT Exception& operator = ( const Exception& theException );
    protected:
        bool _IsA( ExceptionType theKind ) const
        {
            return theKind == KIND;
        }
    public:
        HCC_EXPORT virtual bool IsA( ExceptionType theKind ) const;
        HCC_EXPORT virtual ExceptionType Kind( ) const;

        HCC_EXPORT virtual const char* what( ) const;

        HCC_EXPORT std::wstring Message( ) const;
        HCC_EXPORT Exception& SetMessage( const char* theValue );
        HCC_EXPORT Exception& SetMessage( const wchar_t* theValue );
        HCC_EXPORT Exception& SetMessage( const std::string& theValue );
        HCC_EXPORT Exception& SetMessage( const std::wstring& theValue );

        HCC_EXPORT std::wstring GetHelpLink( ) const;
        HCC_EXPORT Exception& SetHelpLink( const char* theValue );
        HCC_EXPORT Exception& SetHelpLink( const wchar_t* theValue );
        HCC_EXPORT Exception& SetHelpLink( const std::string& theValue );
        HCC_EXPORT Exception& SetHelpLink( const std::wstring& theValue );

        HCC_EXPORT HRESULT GetHRESULT( ) const;
        HCC_EXPORT Exception& SetHRESULT( HRESULT theValue );

        HCC_EXPORT long long GetCode( ) const;
        HCC_EXPORT Exception& SetCode( long long theValue );

        HCC_EXPORT const ExceptionData* GetInnerException( ) const;
        HCC_EXPORT Exception& SetInnerException( const Exception& theValue );

        HCC_EXPORT std::wstring GetSource( ) const;
        HCC_EXPORT Exception& SetSource( const char* theValue );
        HCC_EXPORT Exception& SetSource( const wchar_t* theValue );
        HCC_EXPORT Exception& SetSource( const std::string& theValue );
        HCC_EXPORT Exception& SetSource( const std::wstring& theValue );

        HCC_EXPORT ExceptionLocation GetLocation( ) const;

        HCC_EXPORT virtual void Log( ) noexcept;
        HCC_EXPORT std::wstring TypeName( ) const;

    };

#define HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( className ) \
HCC_EXPORT explicit className (); \
HCC_EXPORT className (const className & other );  \
HCC_EXPORT explicit className (const char* message);  \
HCC_EXPORT explicit className (const wchar_t* message);  \
HCC_EXPORT explicit className (const std::string& message);  \
HCC_EXPORT explicit className (const std::wstring& message);  \
HCC_EXPORT className ( long long code, const char* message ); \
HCC_EXPORT className ( long long code, const wchar_t* message ); \
HCC_EXPORT className ( long long code, const std::string& message );  \
HCC_EXPORT className ( long long code, const std::wstring& message );  \
HCC_EXPORT className ( HRESULT hResult, long long code, const char* message );  \
HCC_EXPORT className ( HRESULT hResult, long long code, const wchar_t* message );  \
HCC_EXPORT className ( HRESULT hResult, long long code, const std::string& message );  \
HCC_EXPORT className ( HRESULT hResult, long long code, const std::wstring& message );  \
HCC_EXPORT className (const char* message, const Exception& innerException);  \
HCC_EXPORT className (const wchar_t* message, const Exception& innerException);  \
HCC_EXPORT explicit className (const ExceptionLocation& location ); \
HCC_EXPORT className (const ExceptionLocation& location, const char* message);  \
HCC_EXPORT className (const ExceptionLocation& location, const wchar_t* message);  \
HCC_EXPORT className (const ExceptionLocation& location, const std::string& message);  \
HCC_EXPORT className (const ExceptionLocation& location, const std::wstring& message);  \
HCC_EXPORT className ( const ExceptionLocation& location, long long code, const char* message ); \
HCC_EXPORT className ( const ExceptionLocation& location, long long code, const wchar_t* message ); \
HCC_EXPORT className ( const ExceptionLocation& location, long long code, const std::string& message );  \
HCC_EXPORT className ( const ExceptionLocation& location, long long code, const std::wstring& message );  \
HCC_EXPORT className ( const ExceptionLocation& location, HRESULT hResult, long long theCode, const char* message );  \
HCC_EXPORT className ( const ExceptionLocation& location, HRESULT hResult, long long theCode, const wchar_t* message );  \
HCC_EXPORT className ( const ExceptionLocation& location, HRESULT hResult, long long theCode, const std::string& message );  \
HCC_EXPORT className ( const ExceptionLocation& location, HRESULT hResult, long long theCode, const std::wstring& message );  \
HCC_EXPORT className (const ExceptionLocation& location, const char* message, const Exception& innerException);  \
HCC_EXPORT className (const ExceptionLocation& location, const wchar_t* message, const Exception& innerException);  \
protected: \
bool _IsA( ExceptionType kind ) const \
{  \
    return kind == KIND || Base::_IsA( kind );  \
} \
public: \
HCC_EXPORT virtual bool IsA( ExceptionType kind ) const override; \
HCC_EXPORT virtual ExceptionType Kind( ) const override; \
HCC_EXPORT className & operator = (const className & other ) 


#define HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS2( className, exp ) \
exp explicit className (); \
exp className (const className & theException);  \
exp explicit className (const char* theMessage);  \
exp explicit className (const wchar_t* theMessage);  \
exp explicit className (const Common:: std::string& theMessage);  \
exp explicit className (const Common:: std::wstring& theMessage);  \
exp className ( long long theCode, const char* theMessage ); \
exp className ( long long theCode, const wchar_t* theMessage ); \
exp className ( long long theCode, const Common:: std::string& theMessage );  \
exp className ( long long theCode, const Common:: std::wstring& theMessage );  \
exp className ( HRESULT hResult, long long theCode, const char* theMessage );  \
exp className ( HRESULT hResult, long long theCode, const wchar_t* theMessage );  \
exp className ( HRESULT hResult, long long theCode, const Common:: std::string& theMessage );  \
exp className ( HRESULT hResult, long long theCode, const Common:: std::wstring& theMessage );  \
exp className (const char* theMessage, const Common:: Exception& theInnerException);  \
exp className (const wchar_t* theMessage, const Common:: Exception& theInnerException);  \
exp explicit className (const Common:: ExceptionLocation& theLocation ); \
exp className (const Common:: ExceptionLocation& theLocation, const char* theMessage);  \
exp className (const Common:: ExceptionLocation& theLocation, const wchar_t* theMessage);  \
exp className (const Common:: ExceptionLocation& theLocation, const Common:: std::string& theMessage);  \
exp className (const Common:: ExceptionLocation& theLocation, const Common:: std::wstring& theMessage);  \
exp className ( const Common:: ExceptionLocation& theLocation, long long theCode, const char* theMessage ); \
exp className ( const Common:: ExceptionLocation& theLocation, long long theCode, const wchar_t* theMessage ); \
exp className ( const Common:: ExceptionLocation& theLocation, long long theCode, const Common:: std::string& theMessage );  \
exp className ( const Common:: ExceptionLocation& theLocation, long long theCode, const Common:: std::wstring& theMessage );  \
exp className ( const Common:: ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const char* theMessage );  \
exp className ( const Common:: ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const wchar_t* theMessage );  \
exp className ( const Common:: ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const Common:: std::string& theMessage );  \
exp className ( const Common:: ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const Common:: std::wstring& theMessage );  \
exp className (const Common:: ExceptionLocation& theLocation, const char* theMessage, const Exception& theInnerException);  \
exp className (const Common:: ExceptionLocation& theLocation, const wchar_t* theMessage, const Exception& theInnerException);  \
protected: \
bool _IsA( Common:: ExceptionType theKind ) const \
{  \
    return theKind == KIND || Base::_IsA( theKind );  \
} \
public: \
exp virtual bool IsA( Common:: ExceptionType theKind ) const override; \
exp virtual Common:: ExceptionType Kind( ) const override; \
exp className & operator = (const className & theException) 


#define HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( className ) \
className :: className () : Base() { SetHRESULT( className :: HRESULTForExceptionType); } \
className :: className (const className & theException) : Base(theException) { }  \
className :: className (const char* theMessage) : Base(theMessage) { SetHRESULT( className :: HRESULTForExceptionType); }  \
className :: className (const wchar_t* theMessage) : Base(theMessage) { SetHRESULT( className :: HRESULTForExceptionType); }  \
className :: className (const std::string& theMessage) : Base(theMessage) { SetHRESULT( className :: HRESULTForExceptionType); }  \
className :: className (const std::wstring& theMessage) : Base(theMessage) { SetHRESULT( className :: HRESULTForExceptionType); }  \
className :: className (const char* theMessage, const Exception& theInnerException) : Base(theMessage,theInnerException) { SetHRESULT( className :: HRESULTForExceptionType); }  \
className :: className (const wchar_t* theMessage, const Exception& theInnerException) : Base(theMessage,theInnerException) { SetHRESULT( className :: HRESULTForExceptionType); }  \
className :: className ( long long theCode, const char* theMessage ) : Base(className :: HRESULTForExceptionType, theCode, theMessage) { }  \
className :: className ( long long theCode, const wchar_t* theMessage ) : Base(className :: HRESULTForExceptionType, theCode, theMessage) { }  \
className :: className ( long long theCode, const std::string& theMessage ) : Base(className :: HRESULTForExceptionType, theCode, theMessage) { }  \
className :: className ( long long theCode, const std::wstring& theMessage ) : Base(className :: HRESULTForExceptionType, theCode, theMessage) { }  \
className :: className ( HRESULT hResult, long long theCode, const char* theMessage ) : Base(hResult, theCode, theMessage) { }  \
className :: className ( HRESULT hResult, long long theCode, const wchar_t* theMessage ) : Base(hResult, theCode, theMessage) { }  \
className :: className ( HRESULT hResult, long long theCode, const std::string& theMessage ) : Base(hResult, theCode, theMessage) { }  \
className :: className ( HRESULT hResult, long long theCode, const std::wstring& theMessage ) : Base(hResult, theCode, theMessage) { }  \
className :: className ( const ExceptionLocation& theLocation ) : Base( theLocation ) { SetHRESULT( className :: HRESULTForExceptionType); } \
className :: className ( const ExceptionLocation& theLocation, const char* theMessage) : Base(theLocation, theMessage) { SetHRESULT( className :: HRESULTForExceptionType); }  \
className :: className ( const ExceptionLocation& theLocation, const wchar_t* theMessage) : Base(theLocation, theMessage) { SetHRESULT( className :: HRESULTForExceptionType); }  \
className :: className ( const ExceptionLocation& theLocation, const std::string& theMessage) : Base(theLocation, theMessage) { SetHRESULT( className :: HRESULTForExceptionType); }  \
className :: className ( const ExceptionLocation& theLocation, const std::wstring& theMessage) : Base(theLocation, theMessage) { SetHRESULT( className :: HRESULTForExceptionType); }  \
className :: className ( const ExceptionLocation& theLocation, const char* theMessage, const Exception& theInnerException) : Base(theLocation, theMessage,theInnerException) { SetHRESULT( className :: HRESULTForExceptionType); }  \
className :: className ( const ExceptionLocation& theLocation, const wchar_t* theMessage, const Exception& theInnerException) : Base(theLocation, theMessage,theInnerException) { SetHRESULT( className :: HRESULTForExceptionType); }  \
className :: className ( const ExceptionLocation& theLocation, long long theCode, const char* theMessage ) : Base(theLocation, className :: HRESULTForExceptionType, theCode, theMessage) { }  \
className :: className ( const ExceptionLocation& theLocation, long long theCode, const wchar_t* theMessage ) : Base(theLocation, className :: HRESULTForExceptionType, theCode, theMessage) { }  \
className :: className ( const ExceptionLocation& theLocation, long long theCode, const std::string& theMessage ) : Base(theLocation, className :: HRESULTForExceptionType, theCode, theMessage) { }  \
className :: className ( const ExceptionLocation& theLocation, long long theCode, const std::wstring& theMessage ) : Base(theLocation, className :: HRESULTForExceptionType, theCode, theMessage) { }  \
className :: className ( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const char* theMessage ) : Base(theLocation, hResult, theCode, theMessage) { }  \
className :: className ( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const wchar_t* theMessage ) : Base(theLocation, hResult, theCode, theMessage) { }  \
className :: className ( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const std::string& theMessage ) : Base(theLocation, hResult, theCode, theMessage) { }  \
className :: className ( const ExceptionLocation& theLocation, HRESULT hResult, long long theCode, const std::wstring& theMessage ) : Base(theLocation, hResult, theCode, theMessage) { }  \
bool className :: IsA( ExceptionType theKind ) const { return _IsA(theKind); } \
ExceptionType className :: Kind( ) const { return KIND; } \
className & className :: operator = (const className & theException ) { Base :: operator = ( reinterpret_cast< const Base & > (theException) ); return *this; }  

    class SystemException : public Exception
    {
    public:
        typedef Exception Base;
        static const HRESULT HRESULTForExceptionType = COR_E_SYSTEM;
        typedef SystemException Type;
        static const ExceptionType KIND = ExceptionType::SystemException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( SystemException );
    };

    class AppDomainUnloadedException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = 0x80131015; //MSEE_E_APPDOMAINUNLOADED;
        typedef AppDomainUnloadedException Type;
        static const ExceptionType KIND = ExceptionType::AppDomainUnloadedException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( AppDomainUnloadedException );
    };

    class ArrayTypeMismatchException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_ARRAYTYPEMISMATCH;
        typedef ArrayTypeMismatchException Type;
        static const ExceptionType KIND = ExceptionType::ArrayTypeMismatchException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ArrayTypeMismatchException );
    };


    class AccessViolationException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = E_POINTER;
        typedef AccessViolationException Type;
        static const ExceptionType KIND = ExceptionType::AccessViolationException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( AccessViolationException );
    };

    class AggregateException : public Exception
    {
    public:
        typedef Exception Base;

        typedef AggregateException Type;
        static const ExceptionType KIND = ExceptionType::AggregateException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( AggregateException );
    };

    class ApplicationException : public Exception
    {
    public:
        typedef Exception Base;

        static const HRESULT HRESULTForExceptionType = COR_E_APPLICATION;

        typedef ApplicationException Type;
        static const ExceptionType KIND = ExceptionType::ApplicationException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ApplicationException );
    };

    class ArgumentException : public SystemException
    {
    protected:
        static const int ParamNameId = 1000;
    public:
        typedef SystemException Base;

        static const HRESULT HRESULTForExceptionType = COR_E_ARGUMENT;

        typedef ArgumentException Type;
        static const ExceptionType KIND = ExceptionType::ArgumentException;


        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ArgumentException );

        HCC_EXPORT ArgumentException( const char* message, const char* argument );
        HCC_EXPORT ArgumentException( const wchar_t* message, const wchar_t* argument );
        HCC_EXPORT ArgumentException( const std::wstring& message, const char* argument );
        HCC_EXPORT ArgumentException( const std::wstring& message, const wchar_t* argument );
        HCC_EXPORT ArgumentException( const std::wstring& message, const std::wstring& argument );

        HCC_EXPORT ArgumentException( const ExceptionLocation& theLocation, const char* message, const char* argument );
        HCC_EXPORT ArgumentException( const ExceptionLocation& theLocation, const wchar_t* message, const wchar_t* argument );
        HCC_EXPORT ArgumentException( const ExceptionLocation& theLocation, const std::wstring& message, const char* argument );
        HCC_EXPORT ArgumentException( const ExceptionLocation& theLocation, const std::wstring& message, const wchar_t* argument );
        HCC_EXPORT ArgumentException( const ExceptionLocation& theLocation, const std::wstring& message, const std::wstring& argument );


        HCC_EXPORT std::wstring GetParamName( ) const;
    };

    class ArgumentNullException : public ArgumentException
    {
    public:
        typedef ArgumentException Base;
        static const HRESULT HRESULTForExceptionType = E_POINTER;

        typedef ArgumentNullException Type;
        static const ExceptionType KIND = ExceptionType::ArgumentNullException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ArgumentNullException );

        HCC_EXPORT ArgumentNullException( const char* argument, const char* message );
        HCC_EXPORT ArgumentNullException( const wchar_t* argument, const wchar_t* message );
        HCC_EXPORT ArgumentNullException( const char* argument, const std::wstring& message );
        HCC_EXPORT ArgumentNullException( const wchar_t* argument, const std::wstring& message );
        HCC_EXPORT ArgumentNullException( const std::wstring& argument, const std::wstring& message );

        HCC_EXPORT ArgumentNullException( const ExceptionLocation& theLocation, const char* argument, const char* message );
        HCC_EXPORT ArgumentNullException( const ExceptionLocation& theLocation, const wchar_t* argument, const wchar_t* message );
        HCC_EXPORT ArgumentNullException( const ExceptionLocation& theLocation, const char* argument, const std::wstring& message );
        HCC_EXPORT ArgumentNullException( const ExceptionLocation& theLocation, const wchar_t* argument, const std::wstring& message );
        HCC_EXPORT ArgumentNullException( const ExceptionLocation& theLocation, const std::wstring& argument, const std::wstring& message );

    };

    class ArgumentOutOfRangeException : public ArgumentException
    {
    public:
        typedef ArgumentException Base;

        static const HRESULT HRESULTForExceptionType = COR_E_ARGUMENTOUTOFRANGE;

        typedef ArgumentOutOfRangeException Type;
        static const ExceptionType KIND = ExceptionType::ArgumentOutOfRangeException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ArgumentOutOfRangeException );

        HCC_EXPORT ArgumentOutOfRangeException( const char* argument, const char* message );
        HCC_EXPORT ArgumentOutOfRangeException( const wchar_t* argument, const wchar_t* message );
        HCC_EXPORT ArgumentOutOfRangeException( const char* argument, const std::wstring& message );
        HCC_EXPORT ArgumentOutOfRangeException( const wchar_t* argument, const std::wstring& message );
        HCC_EXPORT ArgumentOutOfRangeException( const std::wstring& argument, const std::wstring& message );

        HCC_EXPORT ArgumentOutOfRangeException( const ExceptionLocation& theLocation, const char* argument, const char* message );
        HCC_EXPORT ArgumentOutOfRangeException( const ExceptionLocation& theLocation, const wchar_t* argument, const wchar_t* message );
        HCC_EXPORT ArgumentOutOfRangeException( const ExceptionLocation& theLocation, const char* argument, const std::wstring& message );
        HCC_EXPORT ArgumentOutOfRangeException( const ExceptionLocation& theLocation, const wchar_t* argument, const std::wstring& message );
        HCC_EXPORT ArgumentOutOfRangeException( const ExceptionLocation& theLocation, const std::wstring& argument, const std::wstring& message );

    };


    class ArithmeticException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_ARITHMETIC;

        typedef ArithmeticException Type;
        static const ExceptionType KIND = ExceptionType::ArithmeticException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ArithmeticException );

    };

    class BadImageFormatException : public SystemException
    {
    public:
        typedef SystemException Base;

        static const HRESULT HRESULTForExceptionType = COR_E_BADIMAGEFORMAT;

        typedef BadImageFormatException Type;
        static const ExceptionType KIND = ExceptionType::BadImageFormatException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( BadImageFormatException );
    };

    class CannotUnloadAppDomainException : public SystemException
    {
    public:
        typedef SystemException Base;

        static const HRESULT HRESULTForExceptionType = COR_E_CANNOTUNLOADAPPDOMAIN;

        typedef CannotUnloadAppDomainException Type;
        static const ExceptionType KIND = ExceptionType::CannotUnloadAppDomainException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( CannotUnloadAppDomainException );
    };

    class ContextMarshalException : public SystemException
    {
    public:
        typedef SystemException Base;

        static const HRESULT HRESULTForExceptionType = COR_E_CONTEXTMARSHAL;

        typedef ContextMarshalException Type;
        static const ExceptionType KIND = ExceptionType::ContextMarshalException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ContextMarshalException );
    };



    class DataMisalignedException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_DATAMISALIGNED;

        typedef DataMisalignedException Type;
        static const ExceptionType KIND = ExceptionType::DataMisalignedException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( DataMisalignedException );
    };


    class ExecutionEngineException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_EXECUTIONENGINE;

        typedef ExecutionEngineException Type;
        static const ExceptionType KIND = ExceptionType::ExecutionEngineException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ExecutionEngineException );
    };


    class TypeLoadException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_TYPELOAD;

        typedef TypeLoadException Type;
        static const ExceptionType KIND = ExceptionType::TypeLoadException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( TypeLoadException );
    };

    class DivideByZeroException : public ArithmeticException
    {
    public:
        typedef ArithmeticException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_DIVIDEBYZERO;

        typedef DivideByZeroException Type;
        static const ExceptionType KIND = ExceptionType::DivideByZeroException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( DivideByZeroException );
    };

    class DllNotFoundException : public TypeLoadException
    {
    public:
        typedef TypeLoadException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_DLLNOTFOUND;

        typedef DllNotFoundException Type;
        static const ExceptionType KIND = ExceptionType::DllNotFoundException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( DllNotFoundException );
    };

    class DuplicateWaitObjectException : public ArgumentException
    {
    public:
        typedef ArgumentException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_DUPLICATEWAITOBJECT;

        typedef DuplicateWaitObjectException Type;
        static const ExceptionType KIND = ExceptionType::DuplicateWaitObjectException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( DuplicateWaitObjectException );
    };

    class EntryPointNotFoundException : public TypeLoadException
    {
    public:
        typedef TypeLoadException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_TYPELOAD;

        typedef EntryPointNotFoundException Type;
        static const ExceptionType KIND = ExceptionType::EntryPointNotFoundException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( EntryPointNotFoundException );
    };

    class MemberAccessException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_MEMBERACCESS;

        typedef MemberAccessException Type;
        static const ExceptionType KIND = ExceptionType::MemberAccessException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( MemberAccessException );
    };

    class FieldAccessException : public MemberAccessException
    {
    public:
        typedef MemberAccessException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_FIELDACCESS;

        typedef FieldAccessException Type;
        static const ExceptionType KIND = ExceptionType::FieldAccessException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( FieldAccessException );
    };


    class FormatException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_FORMAT;

        typedef FormatException Type;
        static const ExceptionType KIND = ExceptionType::FormatException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( FormatException );
    };

    class IndexOutOfRangeException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_INDEXOUTOFRANGE;

        typedef IndexOutOfRangeException Type;
        static const ExceptionType KIND = ExceptionType::IndexOutOfRangeException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( IndexOutOfRangeException );
    };


    class InsufficientExecutionStackException : public SystemException
    {
    public:
        typedef SystemException Base;

        typedef InsufficientExecutionStackException Type;
        static const ExceptionType KIND = ExceptionType::InsufficientExecutionStackException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( InsufficientExecutionStackException );
    };

    class OutOfMemoryException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_OUTOFMEMORY;

        typedef OutOfMemoryException Type;
        static const ExceptionType KIND = ExceptionType::OutOfMemoryException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( OutOfMemoryException );

    };

    class InsufficientMemoryException : public OutOfMemoryException
    {
    public:
        typedef OutOfMemoryException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_INSUFFICIENTMEMORY;

        typedef InsufficientMemoryException Type;
        static const ExceptionType KIND = ExceptionType::InsufficientMemoryException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( InsufficientMemoryException );
    };

    class InvalidCastException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_INVALIDCAST;

        typedef InvalidCastException Type;
        static const ExceptionType KIND = ExceptionType::InvalidCastException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( InvalidCastException );
    };


    class InvalidOperationException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_INVALIDOPERATION;

        typedef InvalidOperationException Type;
        static const ExceptionType KIND = ExceptionType::InvalidOperationException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( InvalidOperationException );
    };

    class InvalidProgramException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_INVALIDPROGRAM;

        typedef InvalidProgramException Type;
        static const ExceptionType KIND = ExceptionType::InvalidProgramException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( InvalidProgramException );
    };

    class InvalidTimeZoneException : public Exception
    {
    public:
        typedef Exception Base;

        typedef InvalidTimeZoneException Type;
        static const ExceptionType KIND = ExceptionType::InvalidTimeZoneException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( InvalidTimeZoneException );
    };

    class MethodAccessException : public MemberAccessException
    {
    public:
        typedef MemberAccessException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_METHODACCESS;

        typedef MethodAccessException Type;
        static const ExceptionType KIND = ExceptionType::MethodAccessException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( MethodAccessException );
    };

    class MissingMemberException : public MemberAccessException
    {
    public:
        typedef MemberAccessException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_MISSINGMEMBER;

        typedef MissingMemberException Type;
        static const ExceptionType KIND = ExceptionType::MissingMemberException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( MissingMemberException );
    };

    class MissingFieldException : public MissingMemberException
    {
    public:
        typedef MissingMemberException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_MISSINGFIELD;

        typedef MissingFieldException Type;
        static const ExceptionType KIND = ExceptionType::MissingFieldException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( MissingFieldException );
    };


    class MissingMethodException : public MissingMemberException
    {
    public:
        typedef MissingMemberException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_MISSINGMETHOD;

        typedef MissingMethodException Type;
        static const ExceptionType KIND = ExceptionType::MissingMethodException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( MissingMethodException );
    };

    class MulticastNotSupportedException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_MULTICASTNOTSUPPORTED;

        typedef MulticastNotSupportedException Type;
        static const ExceptionType KIND = ExceptionType::MulticastNotSupportedException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( MulticastNotSupportedException );
    };

    class NotFiniteNumberException : public ArithmeticException
    {
    public:
        typedef ArithmeticException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_NOTFINITENUMBER;

        typedef NotFiniteNumberException Type;
        static const ExceptionType KIND = ExceptionType::NotFiniteNumberException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( NotFiniteNumberException );
    };

    class NotImplementedException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = E_NOTIMPL;

        typedef NotImplementedException Type;
        static const ExceptionType KIND = ExceptionType::NotImplementedException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( NotImplementedException );
    };

    class NotSupportedException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_NOTSUPPORTED;

        typedef NotSupportedException Type;
        static const ExceptionType KIND = ExceptionType::NotSupportedException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( NotSupportedException );
    };

    class NullReferenceException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_NULLREFERENCE;

        typedef NullReferenceException Type;
        static const ExceptionType KIND = ExceptionType::NullReferenceException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( NullReferenceException );
    };

    class OperationCanceledException : public SystemException
    {
    public:
        typedef SystemException Base;

        typedef OperationCanceledException Type;
        static const ExceptionType KIND = ExceptionType::OperationCanceledException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( OperationCanceledException );
    };

    class OverflowException : public ArithmeticException
    {
    public:
        typedef ArithmeticException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_OVERFLOW;

        typedef OverflowException Type;
        static const ExceptionType KIND = ExceptionType::OverflowException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( OverflowException );
    };


    class PlatformNotSupportedException : public NotSupportedException
    {
    public:
        typedef NotSupportedException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_PLATFORMNOTSUPPORTED;

        typedef PlatformNotSupportedException Type;
        static const ExceptionType KIND = ExceptionType::PlatformNotSupportedException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( PlatformNotSupportedException );
    };

    class RankException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_RANK;

        typedef RankException Type;
        static const ExceptionType KIND = ExceptionType::RankException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( RankException );
    };


    class StackOverflowException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_STACKOVERFLOW;

        typedef StackOverflowException Type;
        static const ExceptionType KIND = ExceptionType::StackOverflowException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( StackOverflowException );
    };



    class TimeoutException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_TIMEOUT;

        typedef TimeoutException Type;
        static const ExceptionType KIND = ExceptionType::TimeoutException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( TimeoutException );
    };


    class TypeInitializationException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_TYPEINITIALIZATION;

        typedef TypeInitializationException Type;
        static const ExceptionType KIND = ExceptionType::TypeInitializationException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( TypeInitializationException );
    };

    class TypeUnloadedException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_TYPEUNLOADED;

        typedef TypeUnloadedException Type;
        static const ExceptionType KIND = ExceptionType::TypeUnloadedException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( TypeUnloadedException );
    };

    class UnauthorizedAccessException : public SystemException
    {
    public:
        typedef SystemException Base;
        static const HRESULT HRESULTForExceptionType = COR_E_UNAUTHORIZEDACCESS;

        typedef UnauthorizedAccessException Type;
        static const ExceptionType KIND = ExceptionType::UnauthorizedAccessException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( UnauthorizedAccessException );
    };

    class UriFormatException : public FormatException
    {
    public:
        typedef FormatException Base;

        typedef UriFormatException Type;
        static const ExceptionType KIND = ExceptionType::UriFormatException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( UriFormatException );
    };

    class UriTemplateMatchException : public SystemException
    {
    public:
        typedef SystemException Base;

        typedef UriTemplateMatchException Type;
        static const ExceptionType KIND = ExceptionType::UriTemplateMatchException;

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( UriTemplateMatchException );
    };

    namespace IO
    {
        class IOException : public SystemException
        {
        public:
            typedef SystemException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_IO;

            typedef IOException Type;
            static const ExceptionType KIND = ExceptionType::IOException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( IOException );
        };

        class DirectoryNotFoundException : public IOException
        {
        public:
            typedef IOException Base;
            static const HRESULT HRESULTForExceptionType = STG_E_PATHNOTFOUND;
            static const HRESULT HRESULTForExceptionType2 = COR_E_DIRECTORYNOTFOUND;

            typedef DirectoryNotFoundException Type;
            static const ExceptionType KIND = ExceptionType::DirectoryNotFoundException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( DirectoryNotFoundException );
        };


        class DriveNotFoundException : public IOException
        {
        public:
            typedef IOException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_DIRECTORYNOTFOUND;

            typedef DriveNotFoundException Type;
            static const ExceptionType KIND = ExceptionType::DriveNotFoundException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( DriveNotFoundException );
        };

        class EndOfStreamException : public IOException
        {
        public:
            typedef IOException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_ENDOFSTREAM;

            typedef EndOfStreamException Type;
            static const ExceptionType KIND = ExceptionType::EndOfStreamException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( EndOfStreamException );
        };

        class FileLoadException : public IOException
        {
        public:
            typedef IOException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_FILELOAD;
            typedef FileLoadException Type;
            static const ExceptionType KIND = ExceptionType::FileLoadException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( FileLoadException );
        };


        class FileNotFoundException : public IOException
        {
        public:
            typedef IOException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_FILENOTFOUND;

            typedef FileNotFoundException Type;
            static const ExceptionType KIND = ExceptionType::FileNotFoundException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( FileNotFoundException );
        };

        class PathTooLongException : public IOException
        {
        public:
            typedef IOException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_PATHTOOLONG;

            typedef PathTooLongException Type;
            static const ExceptionType KIND = ExceptionType::PathTooLongException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( PathTooLongException );
        };

        class PipeException : public IOException
        {
        public:
            typedef IOException Base;

            typedef PipeException Type;
            static const ExceptionType KIND = ExceptionType::PipeException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( PipeException );
        };

        namespace IsolatedStorage
        {
            class IsolatedStorageException : public Exception
            {
            public:
                typedef Exception Base;
                static const HRESULT HRESULTForExceptionType = ISS_E_ISOSTORE;

                typedef IsolatedStorageException Type;
                static const ExceptionType KIND = ExceptionType::IsolatedStorageException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( IsolatedStorageException );
            };

        }

        namespace Sockets
        {
            class SocketException : public IOException
            {
            public:
                typedef IOException Base;

                typedef DirectoryNotFoundException Type;
                static const ExceptionType KIND = ExceptionType::SocketException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( SocketException );
            };
        }

    }



    namespace Reflection
    {
        class CustomAttributeFormatException : public FormatException
        {
        public:
            typedef FormatException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_FORMAT;

            typedef CustomAttributeFormatException Type;
            static const ExceptionType KIND = ExceptionType::CustomAttributeFormatException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( CustomAttributeFormatException );
        };

        class InvalidFilterCriteriaException : public ApplicationException
        {
        public:
            typedef ApplicationException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_INVALIDFILTERCRITERIA;

            typedef InvalidFilterCriteriaException Type;
            static const ExceptionType KIND = ExceptionType::InvalidFilterCriteriaException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( InvalidFilterCriteriaException );
        };

        class ReflectionTypeLoadException : public SystemException
        {
        public:
            typedef SystemException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_REFLECTIONTYPELOAD;

            typedef ReflectionTypeLoadException Type;
            static const ExceptionType KIND = ExceptionType::ReflectionTypeLoadException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ReflectionTypeLoadException );
        };

        class TargetException : public ApplicationException
        {
        public:
            typedef ApplicationException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_TARGET;

            typedef TargetException Type;
            static const ExceptionType KIND = ExceptionType::TargetException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( TargetException );
        };

        class TargetInvocationException : public ApplicationException
        {
        public:
            typedef ApplicationException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_TARGETINVOCATION;

            typedef TargetInvocationException Type;
            static const ExceptionType KIND = ExceptionType::TargetInvocationException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( TargetInvocationException );
        };

        class TargetParameterCountException : public ApplicationException
        {
        public:
            typedef ApplicationException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_TARGETPARAMCOUNT;

            typedef TargetParameterCountException Type;
            static const ExceptionType KIND = ExceptionType::TargetParameterCountException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( TargetParameterCountException );
        };




    }

    namespace Runtime
    {
        namespace InteropServices
        {
            class ExternalException : public SystemException
            {
            public:
                typedef SystemException Base;
                static const HRESULT HRESULTForExceptionType = E_FAIL;

                typedef ExternalException Type;
                static const ExceptionType KIND = ExceptionType::ExternalException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ExternalException );
            };

            class COMException : public ExternalException
            {
            public:
                typedef ExternalException Base;
                static const HRESULT HRESULTForExceptionType = E_FAIL;

                typedef COMException Type;
                static const ExceptionType KIND = ExceptionType::COMException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( COMException );
            };

            class InvalidComObjectException : public SystemException
            {
            public:
                typedef SystemException Base;
                static const HRESULT HRESULTForExceptionType = COR_E_INVALIDCOMOBJECT;

                typedef InvalidComObjectException Type;
                static const ExceptionType KIND = ExceptionType::InvalidComObjectException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( InvalidComObjectException );
            };

            class InvalidOleVariantTypeException : public SystemException
            {
            public:
                typedef SystemException Base;
                static const HRESULT HRESULTForExceptionType = COR_E_INVALIDOLEVARIANTTYPE;

                typedef InvalidOleVariantTypeException Type;
                static const ExceptionType KIND = ExceptionType::InvalidOleVariantTypeException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( InvalidOleVariantTypeException );
            };

            class MarshalDirectiveException : public SystemException
            {
            public:
                typedef SystemException Base;
                static const HRESULT HRESULTForExceptionType = COR_E_MARSHALDIRECTIVE;

                typedef MarshalDirectiveException Type;
                static const ExceptionType KIND = ExceptionType::MarshalDirectiveException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( MarshalDirectiveException );
            };

            class SafeArrayTypeMismatchException : public SystemException
            {
            public:
                typedef SystemException Base;
                static const HRESULT HRESULTForExceptionType = COR_E_SAFEARRAYTYPEMISMATCH;

                typedef SafeArrayTypeMismatchException Type;
                static const ExceptionType KIND = ExceptionType::SafeArrayTypeMismatchException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( SafeArrayTypeMismatchException );
            };

            class SafeArrayRankMismatchException : public SystemException
            {
            public:
                typedef SystemException Base;
                static const HRESULT HRESULTForExceptionType = COR_E_SAFEARRAYRANKMISMATCH;

                typedef SafeArrayRankMismatchException Type;
                static const ExceptionType KIND = ExceptionType::SafeArrayRankMismatchException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( SafeArrayRankMismatchException );
            };

            class SEHException : public ExternalException
            {
            public:
                typedef ExternalException Base;
                static const HRESULT HRESULTForExceptionType = E_FAIL;

                typedef SEHException Type;
                static const ExceptionType KIND = ExceptionType::SEHException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( SEHException );
            };


        }

        namespace Remoting
        {
            class RemotingException : public SystemException
            {
            public:
                typedef SystemException Base;
                static const HRESULT HRESULTForExceptionType = COR_E_REMOTING;

                typedef RemotingException Type;
                static const ExceptionType KIND = ExceptionType::RemotingException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( RemotingException );
            };


            class RemotingTimeoutException : public RemotingException
            {
            public:
                typedef RemotingException Base;
                static const HRESULT HRESULTForExceptionType = COR_E_REMOTING;

                typedef RemotingTimeoutException Type;
                static const ExceptionType KIND = ExceptionType::RemotingTimeoutException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( RemotingTimeoutException );
            };

            class ServerException : public SystemException
            {
            public:
                typedef SystemException Base;
                static const HRESULT HRESULTForExceptionType = COR_E_SERVER;

                typedef ServerException Type;
                static const ExceptionType KIND = ExceptionType::ServerException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ServerException );
            };

            namespace MetadataServices
            {
                class SUDSGeneratorException : public Exception
                {
                public:
                    typedef Exception Base;
                    static const HRESULT HRESULTForExceptionType = COR_E_EXCEPTION;

                    typedef SUDSGeneratorException Type;
                    static const ExceptionType KIND = ExceptionType::SUDSGeneratorException;

                    HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( SUDSGeneratorException );
                };

                class SUDSParserException : public Exception
                {
                public:
                    typedef Exception Base;
                    static const HRESULT HRESULTForExceptionType = COR_E_EXCEPTION;

                    typedef SUDSParserException Type;
                    static const ExceptionType KIND = ExceptionType::SUDSParserException;

                    HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( SUDSParserException );
                };
            }

        }

        namespace Serialization
        {
            class SerializationException : public SystemException
            {
            public:
                typedef SystemException Base;
                static const HRESULT HRESULTForExceptionType = COR_E_SERIALIZATION;

                typedef SerializationException Type;
                static const ExceptionType KIND = ExceptionType::SerializationException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( SerializationException );
            };
        }
    }

    namespace Data
    {
        class DbException : public Runtime::InteropServices::ExternalException
        {
        public:
            typedef Runtime::InteropServices::ExternalException Base;

            typedef DbException Type;
            static const ExceptionType KIND = ExceptionType::DbException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( DbException );
        };

        namespace OracleClient
        {
            class OracleException : public DbException
            {
            public:
                typedef DbException Base;

                typedef OracleException Type;
                static const ExceptionType KIND = ExceptionType::OracleException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( OracleException );
            };
        }

    }

    namespace Messaging
    {
        class MessageQueueException : public Runtime::InteropServices::ExternalException
        {
        public:
            typedef Runtime::InteropServices::ExternalException Base;

            typedef MessageQueueException Type;
            static const ExceptionType KIND = ExceptionType::MessageQueueException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( MessageQueueException );
        };
    }



    namespace Resources
    {
        class MissingManifestResourceException : public SystemException
        {
        public:
            typedef SystemException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_MISSINGMANIFESTRESOURCE;

            typedef MissingManifestResourceException Type;
            static const ExceptionType KIND = ExceptionType::MissingManifestResourceException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( MissingManifestResourceException );
        };

    }

    namespace Security
    {

        class SecurityException : public SystemException
        {
        public:
            typedef SystemException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_SECURITY;

            typedef SecurityException Type;
            static const ExceptionType KIND = ExceptionType::SecurityException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( SecurityException );
        };

        class VerificationException : public SystemException
        {
        public:
            typedef SystemException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_VERIFICATION;

            typedef VerificationException Type;
            static const ExceptionType KIND = ExceptionType::VerificationException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( VerificationException );
        };



        namespace Cryptography
        {
            class CryptographicException : public SystemException
            {
            public:
                typedef SystemException Base;
                static const HRESULT HRESULTForExceptionType = NTE_FAIL;

                typedef CryptographicException Type;
                static const ExceptionType KIND = ExceptionType::CryptographicException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( CryptographicException );
            };

            class CryptographicUnexpectedOperationException : public CryptographicException
            {
            public:
                typedef CryptographicException Base;
                static const HRESULT HRESULTForExceptionType = CORSEC_E_CRYPTO_UNEX_OPER;

                typedef CryptographicUnexpectedOperationException Type;
                static const ExceptionType KIND = ExceptionType::CryptographicUnexpectedOperationException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( CryptographicUnexpectedOperationException );
            };

        }

        namespace Policy
        {
            class PolicyException : public SystemException
            {
            public:
                typedef SystemException Base;
                static const HRESULT HRESULTForExceptionType = CORSEC_E_POLICY_EXCEPTION;

                typedef PolicyException Type;
                static const ExceptionType KIND = ExceptionType::PolicyException;

                HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( PolicyException );
            };
        }
    }

    namespace Threading
    {
        class SynchronizationLockException : public SystemException
        {
        public:
            typedef SystemException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_SYNCHRONIZATIONLOCK;

            typedef SynchronizationLockException Type;
            static const ExceptionType KIND = ExceptionType::SynchronizationLockException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( SynchronizationLockException );
        };

        class ThreadAbortException : public SystemException
        {
        public:
            typedef SystemException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_THREADABORTED;

            typedef ThreadAbortException Type;
            static const ExceptionType KIND = ExceptionType::ThreadAbortException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ThreadAbortException );
        };

        class ThreadInterruptedException : public SystemException
        {
        public:
            typedef SystemException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_THREADINTERRUPTED;

            typedef ThreadInterruptedException Type;
            static const ExceptionType KIND = ExceptionType::ThreadInterruptedException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ThreadInterruptedException );
        };

        class ThreadStateException : public SystemException
        {
        public:
            typedef SystemException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_THREADSTATE;

            typedef ThreadStateException Type;
            static const ExceptionType KIND = ExceptionType::ThreadStateException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ThreadStateException );
        };

        class ThreadStopException : public SystemException
        {
        public:
            typedef SystemException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_THREADSTOP;

            typedef ThreadStopException Type;
            static const ExceptionType KIND = ExceptionType::ThreadStopException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( ThreadStopException );
        };


        class WaitHandleCannotBeOpenedException : public SystemException
        {
        public:
            typedef SystemException Base;
            static const HRESULT HRESULTForExceptionType = COR_E_WAITHANDLECANNOTBEOPENED;

            typedef WaitHandleCannotBeOpenedException Type;
            static const ExceptionType KIND = ExceptionType::WaitHandleCannotBeOpenedException;

            HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS( WaitHandleCannotBeOpenedException );
        };






    }


    /// <summary>
    /// Mandatory base class for exception reporters.
    /// </summary>
    class ExceptionReporter : public std::enable_shared_from_this<ExceptionReporter>
    {
        HCC_EXPORT static std::shared_ptr<ExceptionReporter> defaultExceptionReporter_;
        HCC_EXPORT static std::shared_ptr<ExceptionReporter> currentExceptionReporter_;
    public:
        HCC_EXPORT ExceptionReporter( );
        HCC_EXPORT virtual ~ExceptionReporter( );

        HCC_EXPORT static std::shared_ptr<ExceptionReporter> Default( );
        HCC_EXPORT static std::shared_ptr<ExceptionReporter> Current( );
        HCC_EXPORT static void SetCurrent( std::shared_ptr<ExceptionReporter> exceptionReporter );

        virtual void ReportException( const Exception& exception, const wchar_t* function, const wchar_t* filename, int lineNumber ) = 0;
        virtual void ReportException( const std::exception& exception, const wchar_t* function, const wchar_t* filename, int lineNumber ) = 0;
        virtual void ReportUnknownException( const wchar_t* function, const wchar_t* filename, int lineNumber ) = 0;
    };

    /// <summary>
    /// The default exception reporter implementation.
    /// </summary>
    class DefaultExceptionReporter : public ExceptionReporter
    {
    public:
        HCC_EXPORT DefaultExceptionReporter( );
        HCC_EXPORT virtual ~DefaultExceptionReporter( );
        HCC_EXPORT virtual void ReportException( const Exception& exception, const wchar_t* function, const wchar_t* filename, int lineNumber ) override;
        HCC_EXPORT virtual void ReportException( const std::exception& exception, const wchar_t* function, const wchar_t* filename, int lineNumber ) override;
        HCC_EXPORT virtual void ReportUnknownException( const wchar_t* function, const wchar_t* filename, int lineNumber ) override;
    };


    

}


#endif
