#pragma once
#ifndef __HCCPIPE_H__
#define __HCCPIPE_H__
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

#include <HCCIOContext.h>
#include <HCCString.h>

namespace Harlinn::Common::Core::IO
{
    enum class PipeAccessRights : DWORD
    {
        HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS,
        /// <summary>
        /// The right to write data to the pipe.
        /// </summary>
        ReadData = FILE_READ_DATA,
        /// <summary>
        /// The right to write data to the pipe.
        /// </summary>
        WriteData = FILE_WRITE_DATA,
        /// <summary>
        /// The right to create a pipe. 
        /// </summary>
        CreateInstance = FILE_CREATE_PIPE_INSTANCE,

        // So far, I've been unable to determine
        // the meaning, if any, of the following three
        // access rights for named pipes
        ReadExtendedAttributes = FILE_READ_EA,
        WriteExtendedAttributes = FILE_WRITE_EA,
        //Execute = FILE_EXECUTE,


        /// <summary>
        /// The right to read file attributes.
        /// </summary>
        ReadAttributes = FILE_READ_ATTRIBUTES,
        WriteAttributes = FILE_WRITE_ATTRIBUTES,

        Read = ReadData | ReadExtendedAttributes | ReadAttributes | Synchronize | ReadPermissions,
        Write = WriteData | WriteExtendedAttributes | WriteAttributes | Synchronize | ReadPermissions,

        FullControl = FILE_ALL_ACCESS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( PipeAccessRights, DWORD );


    class PipeAccessMask : public Security::AccessMaskT<PipeAccessMask, PipeAccessRights>
    {
    public:
        using Base = Security::AccessMaskT<PipeAccessMask, PipeAccessRights>;
        static constexpr const Security::GenericMapping Mapping{
            static_cast<ACCESS_MASK>( FILE_GENERIC_READ ),
            static_cast<ACCESS_MASK>( FILE_GENERIC_WRITE ),
            static_cast<ACCESS_MASK>( FILE_GENERIC_EXECUTE ),
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( PipeAccessRights::FullControl ) ) };



        constexpr PipeAccessMask( ) noexcept
        {
        }
        constexpr explicit PipeAccessMask( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }

        constexpr explicit PipeAccessMask( PipeAccessRights rights ) noexcept
            : Base( rights )
        {
        }

        explicit PipeAccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit PipeAccessMask( ACCESS_MASK mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }

        explicit PipeAccessMask( const PipeAccessMask& mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }
        explicit PipeAccessMask( const PipeAccessMask& mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }

        explicit PipeAccessMask( PipeAccessRights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }
        explicit PipeAccessMask( PipeAccessRights rights, const Security::GenericMapping& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }

        constexpr bool CanReadData( ) const noexcept
        {
            return Check<PipeAccessRights::ReadData>( );
        }
        constexpr void SetReadData( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::ReadData>( value );
        }

        constexpr bool CanWriteData( ) const noexcept
        {
            return Check<PipeAccessRights::WriteData>( );
        }
        constexpr void SetWriteData( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::WriteData>( value );
        }

        constexpr bool CanCreateInstance( ) const noexcept
        {
            return Check<PipeAccessRights::CreateInstance>( );
        }
        constexpr void SetCreateInstance( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::CreateInstance>( value );
        }

        constexpr bool CanReadExtendedAttributes( ) const noexcept
        {
            return Check<PipeAccessRights::ReadExtendedAttributes>( );
        }
        constexpr void SetReadExtendedAttributes( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::ReadExtendedAttributes>( value );
        }

        constexpr bool CanWriteExtendedAttributes( ) const noexcept
        {
            return Check<PipeAccessRights::WriteExtendedAttributes>( );
        }
        constexpr void SetWriteExtendedAttributes( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::WriteExtendedAttributes>( value );
        }

        constexpr bool CanReadAttributes( ) const noexcept
        {
            return Check<PipeAccessRights::ReadAttributes>( );
        }
        constexpr void SetReadAttributes( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::ReadAttributes>( value );
        }

        constexpr bool CanWriteAttributes( ) const noexcept
        {
            return Check<PipeAccessRights::WriteAttributes>( );
        }
        constexpr void SetWriteAttributes( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::WriteAttributes>( value );
        }

        constexpr bool CanRead( ) const noexcept
        {
            return Check<PipeAccessRights::Read>( );
        }
        constexpr void SetRead( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::Read>( value );
        }

        constexpr bool CanWrite( ) const noexcept
        {
            return Check<PipeAccessRights::Write>( );
        }
        constexpr void SetWrite( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::Write>( value );
        }

        constexpr bool CanReadAndWrite( ) const noexcept
        {
            return Check<PipeAccessRights::Read | PipeAccessRights::Write>( );
        }
        constexpr void SetReadAndWrite( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::Read | PipeAccessRights::Write>( value );
        }


    };


    enum class PipeOpenMode : UInt32
    {

        In = PIPE_ACCESS_INBOUND,
        Out = PIPE_ACCESS_OUTBOUND,
        InOut = PIPE_ACCESS_DUPLEX,
        FirstInstance = FILE_FLAG_FIRST_PIPE_INSTANCE,
        WriteThrough = FILE_FLAG_WRITE_THROUGH,
        Overlapped = FILE_FLAG_OVERLAPPED,
        WriteACL = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        SystemSecurity = ACCESS_SYSTEM_SECURITY
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( PipeOpenMode, UInt32 );

    enum class PipeMode : UInt32
    {
        // Data is written to the pipe as a stream of bytes.
        WriteByte = PIPE_TYPE_BYTE,
        // Data is written to the pipe as a stream of messages. The pipe 
        // treats the bytes written during each write operation as a message unit.
        WriteMessage = PIPE_TYPE_MESSAGE,
        // Data is read from the pipe as a stream of bytes.
        ReadByte = PIPE_READMODE_BYTE,
        // Data is read from the pipe as a stream of messages.
        ReadMessage = PIPE_READMODE_MESSAGE,
        Byte = WriteByte | ReadByte,
        Message = WriteMessage | ReadMessage,
        // Connections from remote clients are automatically rejected.
        RejectRemoteClients = PIPE_REJECT_REMOTE_CLIENTS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( PipeMode, UInt32 );


    class Pipe : public SystemStream<Pipe>
    {
        static HANDLE Create( const wchar_t* pipeName, PipeOpenMode pipeOpenMode,
                                PipeMode pipeMode, UInt32 maxInstances, UInt32 outBufferSize,
                                UInt32 inBufferSize, UInt32 defaultTimeout,
                                LPSECURITY_ATTRIBUTES lpSecurityAttributes )
        {
            auto result = CreateNamedPipeW( pipeName,
                                        static_cast<DWORD>( pipeOpenMode ),
                                        static_cast<DWORD>( pipeMode ),
                                        maxInstances, outBufferSize, inBufferSize, 
                                        defaultTimeout, lpSecurityAttributes );

            if ( result == INVALID_HANDLE_VALUE )
            {
                ThrowLastOSError( );
            }
            return result;
        }
    public:
        using Base = SystemStream<Pipe>;

        static constexpr DWORD UnlimitedInstances = PIPE_UNLIMITED_INSTANCES;
        static constexpr DWORD DefaultOutBufferSize = 8192;
        static constexpr DWORD DefaultInBufferSize = 8192;

        // A value of zero will result in a default time-out of 50 milliseconds.
        static constexpr DWORD DefaultTimeout = 0;
        static constexpr DWORD NoWait = NMPWAIT_NOWAIT;
        static constexpr DWORD WaitForever = NMPWAIT_WAIT_FOREVER;
        static constexpr DWORD UseDefaultWait = NMPWAIT_USE_DEFAULT_WAIT;

        Pipe( const wchar_t* pipeName, PipeOpenMode pipeOpenMode = PipeOpenMode::InOut, 
                PipeMode pipeMode = PipeMode::Message | PipeMode::RejectRemoteClients, 
                UInt32 maxInstances = UnlimitedInstances, 
                UInt32 outBufferSize = DefaultOutBufferSize, 
                UInt32 inBufferSize = DefaultInBufferSize, 
                UInt32 defaultTimeout = DefaultTimeout, 
                LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr )
            : Base( Create( pipeName, pipeOpenMode, pipeMode, maxInstances, 
                outBufferSize, inBufferSize, defaultTimeout, lpSecurityAttributes ) )
        {
        }
    private:
        Pipe( HANDLE handle )
            : Base( handle )
        {
        }
    public:



        static Pipe Open( const wchar_t* pipeName, TimeSpan timeout = TimeSpan::FromMinutes(1) )
        {
            DWORD timeoutInMillis = static_cast<DWORD>( timeout.TotalMilliseconds( ) );
            DateTime now = DateTime::UtcNow( );
            DateTime end = now + timeout;
            while ( now < end )
            {
                auto handle = CreateFileW( pipeName, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr );
                if ( handle != INVALID_HANDLE_VALUE )
                {
                    return Pipe( handle );
                }
                auto error = GetLastError( );
                if ( error != ERROR_PIPE_BUSY )
                {
                    ThrowOSError( error );
                }
                if ( WaitNamedPipeW( pipeName, timeoutInMillis ) == 0 )
                {
                    ThrowLastOSError( );
                }

                now = DateTime::UtcNow( );
            }
            ThrowLastOSError( );
            return Pipe( INVALID_HANDLE_VALUE );
            
        }


        static void Call( const wchar_t* pipeName, const void* inBuffer, size_t inBufferSize, void* outBuffer, size_t outBufferSize, size_t* bytesRead, UInt32 timeout )
        {
            DWORD numberOfBytesRead = 0;
            auto result = CallNamedPipeW( pipeName, (LPVOID)inBuffer, static_cast<DWORD>( inBufferSize ), outBuffer, static_cast<DWORD>( outBufferSize ), &numberOfBytesRead, timeout );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            if ( bytesRead )
            {
                *bytesRead = numberOfBytesRead;
            }
        }

        void Transact( const void* inBuffer, size_t inBufferSize, void* outBuffer, size_t outBufferSize, size_t* bytesRead, OVERLAPPED* overlapped ) const
        {
            DWORD numberOfBytesRead = 0;
            auto handle = Handle( );
            auto result = TransactNamedPipe( handle, (LPVOID)inBuffer, static_cast<DWORD>( inBufferSize ), outBuffer, static_cast<DWORD>( outBufferSize ), &numberOfBytesRead, overlapped );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            if ( bytesRead )
            {
                *bytesRead = numberOfBytesRead;
            }
        }

        void Connect( OVERLAPPED* overlapped = nullptr ) const
        {
            auto handle = Handle( );
            auto result = ConnectNamedPipe( handle, overlapped );
            if ( !result )
            {
                auto error = GetLastError( );
                if ( error != ERROR_PIPE_CONNECTED && error != ERROR_IO_PENDING )
                {
                    ThrowOSError( error );
                }
            }
        }
        void Disconnect( ) const
        {
            auto handle = Handle( );
            auto result = DisconnectNamedPipe( handle );
            if ( !result )
            {
                ThrowLastOSError( );
            }
        }
        void Peek( void* outBuffer, size_t outBufferSize, size_t* bytesRead, size_t* totalBytesAvail, size_t* bytesLeftThisMessage ) const
        {
            DWORD numberOfBytesRead = 0;
            DWORD totalNumberOfBytesAvail = 0;
            DWORD numberOfBytesLeftThisMessage = 0;
            auto handle = Handle( );
            auto result = PeekNamedPipe( handle, outBuffer, static_cast<DWORD>( outBufferSize ), &numberOfBytesRead, &totalNumberOfBytesAvail, &numberOfBytesLeftThisMessage );
            if ( !result )
            {
                ThrowLastOSError( );
            }

            if ( bytesRead )
            {
                *bytesRead = numberOfBytesRead;
            }
            if ( totalBytesAvail )
            {
                *totalBytesAvail = totalNumberOfBytesAvail;
            }
            if ( bytesLeftThisMessage )
            {
                *bytesLeftThisMessage = numberOfBytesLeftThisMessage;
            }
        }

        WideString GetClientComputerName( ) const
        {
            wchar_t buffer[512] = {};
            auto handle = Handle( );
            auto result = GetNamedPipeClientComputerNameW( handle, buffer, sizeof( buffer ) );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return WideString( buffer );
        }
    };


    enum class PipeRequestType
    {
        Unknown,
        Read,
        Write,
        ReadScatter,
        WriteGather,
        Connect,
        Transact
    };


    class PipeRequest : public IO::Request
    {
    public:
        using Base = IO::Request;
    private:
        PipeRequestType type_;
    protected:
        PipeRequest( HANDLE handle, PipeRequestType type )
            : Base( handle ), type_( type )
        {
        }

        constexpr PipeRequest( HANDLE handle, HANDLE manualResetEvent, bool ownsEvent, PipeRequestType type ) noexcept
            : Base( handle, manualResetEvent, ownsEvent ), type_( type )
        {
        }
    public:
        constexpr PipeRequestType Type( ) const noexcept
        {
            return type_;
        }
    };




    class ReadPipeRequest : public PipeRequest
    {
    public:
        using Base = PipeRequest;
        static constexpr PipeRequestType RequestType = PipeRequestType::Read;
    private:
        Byte* buffer_;
        UInt32 numberOfBytesToRead_;
    public:
        ReadPipeRequest( HANDLE handle, Byte* buffer, UInt32 numberOfBytesToRead )
            : Base( handle, RequestType ), buffer_( buffer ), numberOfBytesToRead_( numberOfBytesToRead )
        {
        }

        constexpr ReadPipeRequest( HANDLE handle, HANDLE manualResetEvent, bool ownsEvent, Byte* buffer, UInt32 numberOfBytesToRead ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), buffer_( buffer ), numberOfBytesToRead_( numberOfBytesToRead )
        {
        }

        ReadPipeRequest( const Pipe& pipe, Byte* buffer, UInt32 numberOfBytesToRead )
            : Base( pipe.Handle( ), RequestType ), buffer_( buffer ), numberOfBytesToRead_( numberOfBytesToRead )
        {
        }

        constexpr ReadPipeRequest( const Pipe& pipe, HANDLE manualResetEvent, bool ownsEvent, Byte* buffer, UInt32 numberOfBytesToRead ) noexcept
            : Base( pipe.Handle( ), manualResetEvent, ownsEvent, RequestType ), buffer_( buffer ), numberOfBytesToRead_( numberOfBytesToRead )
        {
        }

        constexpr Byte* Buffer( ) const noexcept
        {
            return buffer_;
        }
        constexpr UInt32 NumberOfBytesToRead( ) const noexcept
        {
            return numberOfBytesToRead_;
        }

    };

    class WritePipeRequest : public PipeRequest
    {
    public:
        using Base = PipeRequest;
        static constexpr PipeRequestType RequestType = PipeRequestType::Write;
    private:
        Byte* buffer_;
        UInt32 numberOfBytesToWrite_;
    public:
        WritePipeRequest( HANDLE handle, Byte* buffer, UInt32 numberOfBytesToWrite )
            : Base( handle, RequestType ), buffer_( buffer ), numberOfBytesToWrite_( numberOfBytesToWrite )
        {
        }

        constexpr WritePipeRequest( HANDLE handle, HANDLE manualResetEvent, bool ownsEvent, Byte* buffer, UInt32 numberOfBytesToWrite ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), buffer_( buffer ), numberOfBytesToWrite_( numberOfBytesToWrite )
        {
        }

        WritePipeRequest( const Pipe& pipe, Byte* buffer, UInt32 numberOfBytesToWrite )
            : Base( pipe.Handle( ), RequestType ), buffer_( buffer ), numberOfBytesToWrite_( numberOfBytesToWrite )
        {
        }

        constexpr WritePipeRequest( const Pipe& pipe, HANDLE manualResetEvent, bool ownsEvent, Byte* buffer, UInt32 numberOfBytesToWrite  ) noexcept
            : Base( pipe.Handle( ), manualResetEvent, ownsEvent, RequestType ), buffer_( buffer ), numberOfBytesToWrite_( numberOfBytesToWrite )
        {
        }

        constexpr Byte* Buffer( ) const noexcept
        {
            return buffer_;
        }
        constexpr UInt32 NumberOfBytesToWrite( ) const noexcept
        {
            return numberOfBytesToWrite_;
        }
    };

    class ConnectPipeRequest : public PipeRequest
    {
    public:
        using Base = PipeRequest;
        static constexpr PipeRequestType RequestType = PipeRequestType::Connect;
        ConnectPipeRequest( HANDLE handle )
            : Base( handle, RequestType ) 
        {
        }

        constexpr ConnectPipeRequest( HANDLE handle, HANDLE manualResetEvent, bool ownsEvent ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType )
        {
        }

        ConnectPipeRequest( const Pipe& pipe )
            : Base( pipe.Handle( ), RequestType )
        {
        }

        constexpr ConnectPipeRequest( const Pipe& pipe, HANDLE manualResetEvent, bool ownsEvent ) noexcept
            : Base( pipe.Handle( ), manualResetEvent, ownsEvent, RequestType )
        {
        }
    };

    class TransactPipeRequest : public PipeRequest
    {
    public:
        using Base = PipeRequest;
        static constexpr PipeRequestType RequestType = PipeRequestType::Write;
    private:
        Byte* writeBuffer_;
        UInt32 numberOfBytesToWrite_;
        Byte* readBuffer_;
        UInt32 readBufferSize_;
    public:
        TransactPipeRequest( HANDLE handle, Byte* writeBuffer, UInt32 numberOfBytesToWrite, Byte* readBuffer, UInt32 readBufferSize )
            : Base( handle, RequestType ), writeBuffer_( writeBuffer ), numberOfBytesToWrite_( numberOfBytesToWrite ), readBuffer_( readBuffer ), readBufferSize_( readBufferSize )
        {
        }

        constexpr TransactPipeRequest( HANDLE handle, HANDLE manualResetEvent, bool ownsEvent, Byte* writeBuffer, UInt32 numberOfBytesToWrite, Byte* readBuffer, UInt32 readBufferSize ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), writeBuffer_( writeBuffer ), numberOfBytesToWrite_( numberOfBytesToWrite ), readBuffer_( readBuffer ), readBufferSize_( readBufferSize )
        {
        }

        TransactPipeRequest( const Pipe& pipe, Byte* writeBuffer, UInt32 numberOfBytesToWrite, Byte* readBuffer, UInt32 readBufferSize )
            : Base( pipe.Handle( ), RequestType ), writeBuffer_( writeBuffer ), numberOfBytesToWrite_( numberOfBytesToWrite ), readBuffer_( readBuffer ), readBufferSize_( readBufferSize )
        {
        }

        constexpr TransactPipeRequest( const Pipe& pipe, HANDLE manualResetEvent, bool ownsEvent, Byte* writeBuffer, UInt32 numberOfBytesToWrite, Byte* readBuffer, UInt32 readBufferSize ) noexcept
            : Base( pipe.Handle( ), manualResetEvent, ownsEvent, RequestType ), writeBuffer_( writeBuffer ), numberOfBytesToWrite_( numberOfBytesToWrite ), readBuffer_( readBuffer ), readBufferSize_( readBufferSize )
        {
        }

        constexpr Byte* WriteBuffer( ) const noexcept
        {
            return writeBuffer_;
        }
        constexpr UInt32 NumberOfBytesToWrite( ) const noexcept
        {
            return numberOfBytesToWrite_;
        }

        constexpr Byte* ReadBuffer( ) const noexcept
        {
            return readBuffer_;
        }
        constexpr UInt32 ReadBufferSize( ) const noexcept
        {
            return readBufferSize_;
        }
    };



    template<typename DerivedT>
    class PipeHandler : public ContextHandler
    {
    public:
        using Base = ContextHandler;
        using DerivedType = DerivedT;
    private:
        Pipe& pipe_;
    protected:
        PipeHandler( const std::shared_ptr<IO::Context>& context, Pipe& pipe )
            : Base( context ), pipe_( pipe )
        {
            context->Bind( pipe.Handle( ), this );
        }
    public:
        constexpr const Pipe& Stream( ) const noexcept
        {
            return pipe_;
        }

        bool BeginAsyncReadFile( ReadPipeRequest* request )
        {
            BindRequestToContext( request );
            auto handle = request->Handle( );
            auto rc = ReadFile( handle, request->Buffer( ), request->NumberOfBytesToRead( ), nullptr, request );
            if ( !rc )
            {
                auto errorCode = GetLastError( );
                if ( errorCode != ERROR_IO_PENDING )
                {
                    ThrowOSError( errorCode );
                }
            }
            return false;
        }

        bool BeginAsyncWriteFile( WritePipeRequest* request )
        {
            BindRequestToContext( request );
            auto handle = request->Handle( );
            auto rc = WriteFile( handle, request->Buffer( ), request->NumberOfBytesToWrite( ), nullptr, request );
            if ( !rc )
            {
                auto errorCode = GetLastError( );
                if ( errorCode != ERROR_IO_PENDING )
                {
                    ThrowOSError( errorCode );
                }
            }
            return false;
        }

        bool BeginAsyncConnect( ConnectPipeRequest* request )
        {
            BindRequestToContext( request );
            auto handle = request->Handle( );
            auto rc = ConnectNamedPipe( handle, request );
            if ( !rc )
            {
                auto errorCode = GetLastError( );
                if ( errorCode == ERROR_PIPE_CONNECTED )
                {
                    request->SetResult( NO_ERROR );
                    DerivedType& self = static_cast<DerivedType&>( *this );
                    self.HandleConnectCompleted( static_cast<ConnectPipeRequest*>( request ) );
                    return true;
                }
                if ( errorCode != ERROR_IO_PENDING )
                {
                    ThrowOSError( errorCode );
                }
            }
            return false;
        }

        bool BeginAsyncTransact( TransactPipeRequest* request )
        {
            BindRequestToContext( request );
            auto handle = request->Handle( );
            auto rc = TransactNamedPipe( handle, request->WriteBuffer( ), request->NumberOfBytesToWrite( ), 
                                                request->ReadBuffer( ), request->ReadBufferSize( ), 
                                                nullptr, request );
            if ( !rc )
            {
                auto errorCode = GetLastError( );
                if ( errorCode != ERROR_IO_PENDING )
                {
                    ThrowOSError( errorCode );
                }
            }
            return false;
        }



        virtual bool Process( Message& message ) override
        {
            bool result = false;
            auto request = static_cast<PipeRequest*>( message.Request( ) );
            PipeRequestType requestType = request->Type( );
            DerivedType& self = static_cast<DerivedType&>( *this );
            switch ( requestType )
            {
                case PipeRequestType::Read:
                {
                    result = self.HandleReadCompleted( static_cast<ReadPipeRequest*>( request ) );
                }
                break;
                case PipeRequestType::Write:
                {
                    result = self.HandleWriteCompleted( static_cast<WritePipeRequest*>( request ) );
                }
                break;
                case PipeRequestType::Connect:
                {
                    result = self.HandleConnectCompleted( static_cast<ConnectPipeRequest*>( request ) );
                }
                break;
                case PipeRequestType::Transact:
                {
                    result = self.HandleTransactCompleted( static_cast<TransactPipeRequest*>( request ) );
                }
                break;
            }
            return result;
        }
    protected:
        constexpr bool HandleReadCompleted( ReadPipeRequest* request ) noexcept
        {
            return false;
        }

        constexpr bool HandleWriteCompleted( WritePipeRequest* request ) noexcept
        {
            return false;
        }

        constexpr bool HandleConnectCompleted( ConnectPipeRequest* request ) noexcept
        {
            return false;
        }

        constexpr bool HandleTransactCompleted( TransactPipeRequest* request ) noexcept
        {
            return false;
        }
    };

    class PipeDispatcher : public PipeHandler<PipeDispatcher>
    {
        template<typename DerivedT>
        friend class PipeHandler;
    public:
        using Base = PipeHandler<PipeDispatcher>;
        boost::signals2::signal<void( const PipeDispatcher& dispatcher, ReadPipeRequest* request )> OnReadCompleted;
        boost::signals2::signal<void( const PipeDispatcher& dispatcher, WritePipeRequest* request )> OnWriteCompleted;
        boost::signals2::signal<void( const PipeDispatcher& dispatcher, ConnectPipeRequest* request )> OnConnectCompleted;
        boost::signals2::signal<void( const PipeDispatcher& dispatcher, TransactPipeRequest* request )> OnTransactCompleted;

        PipeDispatcher( const std::shared_ptr<IO::Context>& context, Pipe& pipe )
            : Base( context, pipe )
        {
        }

    private:
        bool HandleReadCompleted( ReadPipeRequest* request )
        {
            OnReadCompleted( *this, request );
            return true;
        }

        bool HandleWriteCompleted( WritePipeRequest* request )
        {
            OnWriteCompleted( *this, request );
            return true;
        }

        bool HandleConnectCompleted( ConnectPipeRequest* request )
        {
            OnConnectCompleted( *this, request );
            return true;
        }

        bool HandleTransactCompleted( TransactPipeRequest* request )
        {
            OnTransactCompleted( *this, request );
            return true;
        }

    };


}

#endif
