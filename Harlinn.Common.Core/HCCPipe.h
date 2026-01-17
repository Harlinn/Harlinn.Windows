#pragma once
#ifndef __HCCPIPE_H__
#define __HCCPIPE_H__
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

#include <HCCIOContext.h>
#include <HCCString.h>

namespace Harlinn::Common::Core::IO
{
    /// <summary>
    /// Access rights for named pipe operations.
    /// </summary>
    /// <remarks>
    /// Represents individual and composite access rights used when creating or opening named pipes.
    /// Values map to Windows FILE_* and access-mask constants and can be combined using bitwise operators.
    /// </remarks>
    enum class PipeAccessRights : DWORD
    {
        /// <summary>
        /// Common enumeration values for access-right enums
        /// </summary>
        HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS,

        /// <summary>
        /// The right to read data from the pipe.
        /// </summary>
        ReadData = FILE_READ_DATA,
        /// <summary>
        /// The right to write data to the pipe.
        /// </summary>
        WriteData = FILE_WRITE_DATA,
        /// <summary>
        /// The right to create a pipe instance.
        /// </summary>

        CreateInstance = FILE_CREATE_PIPE_INSTANCE,

        // So far, I've been unable to determine
        // the meaning, if any, of the following three
        // access rights for named pipes
        ReadExtendedAttributes = FILE_READ_EA,
        WriteExtendedAttributes = FILE_WRITE_EA,
        //Execute = FILE_EXECUTE,


        /// <summary>
        /// The right to read file attributes (maps to FILE_READ_ATTRIBUTES).
        /// </summary>
        ReadAttributes = FILE_READ_ATTRIBUTES,

        /// <summary>
        /// The right to write file attributes (maps to FILE_WRITE_ATTRIBUTES).
        /// </summary>
        WriteAttributes = FILE_WRITE_ATTRIBUTES,

        /// <summary>
        /// Convenience flag combining the read-related rights (data, extended attributes, attributes) plus synchronize and read permissions.
        /// </summary>
        Read = ReadData | ReadExtendedAttributes | ReadAttributes | Synchronize | ReadPermissions,
        /// <summary>
        /// Convenience flag combining the write-related rights (data, extended attributes, attributes) plus synchronize and read permissions.
        /// </summary>
        Write = WriteData | WriteExtendedAttributes | WriteAttributes | Synchronize | ReadPermissions,

        /// <summary>
        /// Full control (maps to FILE_ALL_ACCESS).
        /// </summary>
        FullControl = FILE_ALL_ACCESS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( PipeAccessRights, DWORD );


    /// <summary>
    /// Access mask wrapper for pipe-specific access rights.
    /// </summary>
    /// <remarks>
    /// `PipeAccessMask` is a strongly-typed wrapper around an ACCESS_MASK value specialized
    /// for `PipeAccessRights`. It provides convenience constructors, accessors and mutators
    /// for common named pipe rights and exposes a `Mapping` that maps generic rights to the
    /// pipe-specific specific/standard rights. Use this type when composing or inspecting
    /// desired or granted access masks for named pipe operations.
    /// </remarks>
    class PipeAccessMask : public Security::AccessMaskT<PipeAccessMask, PipeAccessRights>
    {
    public:
        using Base = Security::AccessMaskT<PipeAccessMask, PipeAccessRights>;
        
        /// <summary>
        /// Generic mapping used to map generic access rights (GenericRead, GenericWrite, GenericExecute, GenericAll)
        /// to pipe-specific rights.
        /// </summary>
        static constexpr const Security::GenericMapping Mapping{
            static_cast<ACCESS_MASK>( FILE_GENERIC_READ ),
            static_cast<ACCESS_MASK>( FILE_GENERIC_WRITE ),
            static_cast<ACCESS_MASK>( FILE_GENERIC_EXECUTE ),
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( PipeAccessRights::FullControl ) ) };



        /// <summary>
        /// Default constructs an empty access mask (no rights).
        /// </summary>
        constexpr PipeAccessMask( ) noexcept
        {
        }
        /// <summary>
        /// Construct from a raw ACCESS_MASK value.
        /// </summary>
        /// <param name="mask">Raw ACCESS_MASK value to wrap.</param>
        constexpr explicit PipeAccessMask( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }

        /// <summary>
        /// Construct from a `PipeAccessRights` enum value or combination of values.
        /// </summary>
        /// <param name="rights">The pipe access rights to initialize the mask with.</param>
        constexpr explicit PipeAccessMask( PipeAccessRights rights ) noexcept
            : Base( rights )
        {
        }

        /// <summary>
        /// Construct from a raw ACCESS_MASK value and an explicit GENERIC_MAPPING.
        /// </summary>
        /// <param name="mask">Raw ACCESS_MASK value to wrap.</param>
        /// <param name="genericMapping">GENERIC_MAPPING to be used for mapping generic rights.</param>
        explicit PipeAccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }

        /// <summary>
        /// Construct from a raw ACCESS_MASK value and a repository GenericMapping wrapper.
        /// </summary>
        /// <param name="mask">Raw ACCESS_MASK value to wrap.</param>
        /// <param name="genericMapping">Repository GenericMapping to be used for mapping generic rights.</param>
        explicit PipeAccessMask( ACCESS_MASK mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        
        /// <summary>
        /// Construct from another PipeAccessMask and an explicit GENERIC_MAPPING.
        /// </summary>
        /// <param name="mask">Source mask to copy value from.</param>
        /// <param name="genericMapping">GENERIC_MAPPING to be used for mapping generic rights.</param>
        explicit PipeAccessMask( const PipeAccessMask& mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }
        
        /// <summary>
        /// Construct from another PipeAccessMask and a repository GenericMapping wrapper.
        /// </summary>
        /// <param name="mask">Source mask to copy value from.</param>
        /// <param name="genericMapping">Repository GenericMapping to be used for mapping generic rights.</param>
        explicit PipeAccessMask( const PipeAccessMask& mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }

        /// <summary>
        /// Construct from PipeAccessRights and an explicit GENERIC_MAPPING.
        /// </summary>
        /// <param name="rights">Rights to initialize the mask with.</param>
        /// <param name="genericMapping">GENERIC_MAPPING to be used for mapping generic rights.</param>
        explicit PipeAccessMask( PipeAccessRights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }

        /// <summary>
        /// Construct from PipeAccessRights and a repository GenericMapping wrapper.
        /// </summary>
        /// <param name="rights">Rights to initialize the mask with.</param>
        /// <param name="genericMapping">Repository GenericMapping to be used for mapping generic rights.</param>
        explicit PipeAccessMask( PipeAccessRights rights, const Security::GenericMapping& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }

        /// <summary>
        /// Returns true if the ReadData right is present in the mask.
        /// </summary>
        constexpr bool CanReadData( ) const noexcept
        {
            return Check<PipeAccessRights::ReadData>( );
        }

        /// <summary>
        /// Sets or clears the ReadData right in the mask.
        /// </summary>
        /// <param name="value">True to set the right, false to clear it.</param>
        constexpr void SetReadData( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::ReadData>( value );
        }

        /// <summary>
        /// Returns true if the WriteData right is present in the mask.
        /// </summary>
        constexpr bool CanWriteData( ) const noexcept
        {
            return Check<PipeAccessRights::WriteData>( );
        }
        /// <summary>
        /// Sets or clears the WriteData right in the mask.
        /// </summary>
        /// <param name="value">True to set the right, false to clear it.</param>
        constexpr void SetWriteData( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::WriteData>( value );
        }

        /// <summary>
        /// Sets or clears the CreateInstance right in the mask.
        /// </summary>
        /// <param name="value">True to set the right, false to clear it.</param>
        constexpr bool CanCreateInstance( ) const noexcept
        {
            return Check<PipeAccessRights::CreateInstance>( );
        }
        /// <summary>
        /// Sets or clears the CreateInstance right in the mask.
        /// </summary>
        /// <param name="value">True to set the right, false to clear it.</param>
        constexpr void SetCreateInstance( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::CreateInstance>( value );
        }

        /// <summary>
        /// Returns true if the ReadExtendedAttributes right is present in the mask.
        /// </summary>
        constexpr bool CanReadExtendedAttributes( ) const noexcept
        {
            return Check<PipeAccessRights::ReadExtendedAttributes>( );
        }
        /// <summary>
        /// Sets or clears the ReadExtendedAttributes right in the mask.
        /// </summary>
        /// <param name="value">True to set the right, false to clear it.</param>
        constexpr void SetReadExtendedAttributes( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::ReadExtendedAttributes>( value );
        }

        /// <summary>
        /// Returns true if the WriteExtendedAttributes right is present in the mask.
        /// </summary>
        constexpr bool CanWriteExtendedAttributes( ) const noexcept
        {
            return Check<PipeAccessRights::WriteExtendedAttributes>( );
        }
        
        /// <summary>
        /// Sets or clears the WriteExtendedAttributes right in the mask.
        /// </summary>
        /// <param name="value">True to set the right, false to clear it.</param>
        constexpr void SetWriteExtendedAttributes( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::WriteExtendedAttributes>( value );
        }

        /// <summary>
        /// Returns true if the ReadAttributes right is present in the mask.
        /// </summary>
        constexpr bool CanReadAttributes( ) const noexcept
        {
            return Check<PipeAccessRights::ReadAttributes>( );
        }
        
        /// <summary>
        /// Sets or clears the ReadAttributes right in the mask.
        /// </summary>
        /// <param name="value">True to set the right, false to clear it.</param>
        constexpr void SetReadAttributes( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::ReadAttributes>( value );
        }

        /// <summary>
        /// Returns true if the WriteAttributes right is present in the mask.
        /// </summary>
        constexpr bool CanWriteAttributes( ) const noexcept
        {
            return Check<PipeAccessRights::WriteAttributes>( );
        }
        /// <summary>
        /// Sets or clears the WriteAttributes right in the mask.
        /// </summary>
        /// <param name="value">True to set the right, false to clear it.</param>
        constexpr void SetWriteAttributes( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::WriteAttributes>( value );
        }

        /// <summary>
        /// Returns true if the convenience Read flag (combined read-related rights) is present.
        /// </summary>
        constexpr bool CanRead( ) const noexcept
        {
            return Check<PipeAccessRights::Read>( );
        }
        /// <summary>
        /// Sets or clears the convenience Read flag (combined read-related rights).
        /// </summary>
        /// <param name="value">True to set the flag, false to clear it.</param>
        constexpr void SetRead( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::Read>( value );
        }

        /// <summary>
        /// Returns true if the convenience Write flag (combined write-related rights) is present.
        /// </summary>
        constexpr bool CanWrite( ) const noexcept
        {
            return Check<PipeAccessRights::Write>( );
        }
        /// <summary>
        /// Sets or clears the convenience Write flag (combined write-related rights).
        /// </summary>
        /// <param name="value">True to set the flag, false to clear it.</param>
        constexpr void SetWrite( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::Write>( value );
        }

        /// <summary>
        /// Returns true if both the convenience Read and Write flags are present.
        /// </summary>
        constexpr bool CanReadAndWrite( ) const noexcept
        {
            return Check<PipeAccessRights::Read | PipeAccessRights::Write>( );
        }
        /// <summary>
        /// Sets or clears both the convenience Read and Write flags.
        /// </summary>
        /// <param name="value">True to set the flags, false to clear them.</param>
        constexpr void SetReadAndWrite( bool value = true ) noexcept
        {
            SetBitFlag<PipeAccessRights::Read | PipeAccessRights::Write>( value );
        }



    };


    /// <summary>
    /// Pipe open modes and flags used when creating or opening named pipes.
    /// </summary>
    enum class PipeOpenMode : UInt32
    {

        /// <summary>
        /// Open the pipe for inbound (read) access only (maps to PIPE_ACCESS_INBOUND).
        /// </summary>
        In = PIPE_ACCESS_INBOUND,
        /// <summary>
        /// Open the pipe for outbound (write) access only (maps to PIPE_ACCESS_OUTBOUND).
        /// </summary>
        Out = PIPE_ACCESS_OUTBOUND,
        /// <summary>
        /// Open the pipe for duplex access (read/write) (maps to PIPE_ACCESS_DUPLEX).
        /// </summary>
        InOut = PIPE_ACCESS_DUPLEX,
        /// <summary>
        /// Create the first instance of the pipe (maps to FILE_FLAG_FIRST_PIPE_INSTANCE).
        /// </summary>
        FirstInstance = FILE_FLAG_FIRST_PIPE_INSTANCE,
        /// <summary>
        /// Writes to the pipe will be performed with write-through semantics (maps to FILE_FLAG_WRITE_THROUGH).
        /// </summary>
        WriteThrough = FILE_FLAG_WRITE_THROUGH,
        /// <summary>
        /// Use overlapped (asynchronous) I/O for the pipe handle (maps to FILE_FLAG_OVERLAPPED).
        /// </summary>
        Overlapped = FILE_FLAG_OVERLAPPED,
        /// <summary>
        /// Allows changing the DACL (maps to WRITE_DAC).
        /// </summary>
        WriteACL = WRITE_DAC,
        /// <summary>
        /// Allows changing the owner (maps to WRITE_OWNER).
        /// </summary>
        WriteOwner = WRITE_OWNER,
        /// <summary>
        /// Access to system security information (maps to ACCESS_SYSTEM_SECURITY).
        /// </summary>
        SystemSecurity = ACCESS_SYSTEM_SECURITY
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( PipeOpenMode, UInt32 );

    /// <summary>
    /// Pipe data and read/write modes used to control message/byte semantics and client policy.
    /// </summary>
    enum class PipeMode : UInt32
    {
        /// <summary>
        /// Data is written to the pipe as a stream of bytes (maps to PIPE_TYPE_BYTE).
        /// </summary>
        WriteByte = PIPE_TYPE_BYTE,
        /// <summary>
        /// Data is written to the pipe as a stream of messages. Each write operation is a message (maps to PIPE_TYPE_MESSAGE).
        /// </summary>
        WriteMessage = PIPE_TYPE_MESSAGE,
        /// <summary>
        /// Data is read from the pipe as a stream of bytes (maps to PIPE_READMODE_BYTE).
        /// </summary>
        ReadByte = PIPE_READMODE_BYTE,
        /// <summary>
        /// Data is read from the pipe as a stream of messages (maps to PIPE_READMODE_MESSAGE).
        /// </summary>
        ReadMessage = PIPE_READMODE_MESSAGE,
        /// <summary>
        /// Convenience flag for both write and read byte modes.
        /// </summary>
        Byte = WriteByte | ReadByte,
        /// <summary>
        /// Convenience flag for both write and read message modes.
        /// </summary>
        Message = WriteMessage | ReadMessage,
        /// <summary>
        /// Connections from remote clients are automatically rejected (maps to PIPE_REJECT_REMOTE_CLIENTS).
        /// </summary>
        RejectRemoteClients = PIPE_REJECT_REMOTE_CLIENTS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( PipeMode, UInt32 );


    /// <summary>
    /// Wrapper for a named pipe handle providing creation and common pipe operations.
    /// </summary>
    /// <remarks>
    /// The `Pipe` class is a thin RAII wrapper around a Windows named pipe handle.
    /// It inherits from `SystemStream<Pipe>` which provides platform stream semantics.
    /// </remarks>
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

        /// <summary>
        /// The value used to specify unlimited pipe instances.
        /// </summary>
        static constexpr DWORD UnlimitedInstances = PIPE_UNLIMITED_INSTANCES;
        
        static constexpr DWORD DefaultOutBufferSize = 8192;
        static constexpr DWORD DefaultInBufferSize = 8192;

        // A value of zero will result in a default time-out of 50 milliseconds.
        static constexpr DWORD DefaultTimeout = 0;
        static constexpr DWORD NoWait = NMPWAIT_NOWAIT;
        static constexpr DWORD WaitForever = NMPWAIT_WAIT_FOREVER;
        static constexpr DWORD UseDefaultWait = NMPWAIT_USE_DEFAULT_WAIT;

        /// <summary>
        /// Constructs a named-pipe server instance and takes ownership of the created pipe handle.
        /// </summary>
        /// <param name="pipeName">
        /// Fully qualified pipe name (for example, "\\.\pipe\MyPipe"). Must be a null-terminated 
        /// wide string. The server must use a local server name (period) when creating the pipe.
        /// </param>
        /// <param name="pipeOpenMode">
        /// Open mode and access flags for the pipe (maps to PIPE_ACCESS_* and file-flag/privilege flags). 
        /// Defaults to <see cref="PipeOpenMode::InOut"/> for duplex access. Use <see cref="PipeOpenMode::Overlapped"/> 
        /// to create an overlapped handle suitable for asynchronous I/O.
        /// </param>
        /// <param name="pipeMode">
        /// Pipe type, read and wait mode flags (maps to PIPE_TYPE_*, PIPE_READMODE_*, 
        /// PIPE_WAIT/PIPE_NOWAIT and related constants). Defaults to message mode and 
        /// <see cref="PipeMode::RejectRemoteClients"/>.
        /// </param>
        /// <param name="maxInstances">
        /// Maximum number of instances that may be created for this pipe name. Use <see cref="UnlimitedInstances"/> 
        /// to allow PIPE_UNLIMITED_INSTANCES.
        /// </param>
        /// <param name="outBufferSize">
        /// Size, in bytes, of the outbound buffer for the pipe instance. This parameter 
        /// maps to the nOutBufferSize argument of CreateNamedPipeW.
        /// </param>
        /// <param name="inBufferSize">
        /// Size, in bytes, of the inbound buffer for the pipe instance. This parameter maps 
        /// to the nInBufferSize argument of CreateNamedPipeW.
        /// </param>
        /// <param name="defaultTimeout">
        /// Default time-out in milliseconds for the pipe instance. A value of zero allows 
        /// the system default (50 ms) to apply. This parameter maps to the nDefaultTimeOut 
        /// argument of CreateNamedPipeW.
        /// </param>
        /// <param name="lpSecurityAttributes">
        /// Optional pointer to a SECURITY_ATTRIBUTES structure that determines whether the 
        /// returned handle can be inherited and optionally supplies a security descriptor. 
        /// If null, the pipe receives the default security descriptor.
        /// </param>
        /// <remarks>
        /// This constructor calls CreateNamedPipeW and, on success, the created handle is owned 
        /// by the resulting Pipe object (the underlying handle will be closed by the stream base / destructor).
        /// If <see cref="PipeOpenMode::Overlapped"/> is specified the returned handle supports 
        /// overlapped I/O; callers are responsible for using appropriate OVERLAPPED structures 
        /// when performing asynchronous operations.
        /// The handle returned by CreateNamedPipeW always includes SYNCHRONIZE access and includes 
        /// GENERIC_READ, GENERIC_WRITE, or both depending on the chosen open mode.
        /// Use explicit rights and modes rather than generic mappings if you need 
        /// fine-grained access control or to avoid FILE_GENERIC_WRITE enabling 
        /// creation rights.
        /// </remarks>
        /// <exception cref="SystemException">
        /// Thrown when CreateNamedPipeW fails; the exception wraps the last Win32 error (GetLastError()).
        /// </exception>
        /// <example>
        /// <code language="cpp">
        /// // Server: create a duplex message pipe and wait for a client.
        /// Pipe serverPipe( L"\\\\.\\pipe\\MyPipe",
        ///                  PipeOpenMode::InOut,
        ///                  PipeMode::Message | PipeMode::RejectRemoteClients,
        ///                  Pipe::UnlimitedInstances,
        ///                  Pipe::DefaultOutBufferSize,
        ///                  Pipe::DefaultInBufferSize );
        ///
        /// // Blocking connect (for overlapped use PipeOpenMode::Overlapped and Connect with an OVERLAPPED).
        /// serverPipe.Connect();
        ///
        /// // Client: open an existing pipe (blocks up to timeout).
        /// auto clientPipe = Pipe::Open( L"\\\\.\\pipe\\MyPipe", TimeSpan::FromSeconds(30) );
        ///
        /// // After connection you can use ReadFile/WriteFile (or overlapped variants) on the pipe handles.
        /// </code>
        /// </example>
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
            const auto startTick = ::GetTickCount64( );

            // Normalize requested timeout.
            // Clamp to 64-bit non-negative and then to a reasonable maximum when passing to Win32 APIs.
            auto requestedMsD = timeout.TotalMilliseconds( );
            if ( requestedMsD < 0.0 )
            {
                requestedMsD = 0.0;
            }
            
            // Cap requestedMs to a 64-bit integer to avoid surprises.
            const auto requestedMs = static_cast< UInt64 >( std::min( requestedMsD, static_cast< double >( INFINITE ) ) );
            const auto endTick = startTick + requestedMs;

            for ( ;;)
            {
                // Try opening the pipe. Keep flags = 0 (blocking/compat) to preserve existing behavior.
                auto handle = CreateFileW( pipeName, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr );
                if ( handle != INVALID_HANDLE_VALUE )
                {
                    // Success
                    return Pipe( handle );
                }

                auto error = ::GetLastError( );
                // If failure is not "pipe busy", propagate the error.
                if ( error != ERROR_PIPE_BUSY )
                {
                    ThrowOSError( error );
                }

                // Compute remaining time (ms). If zero or expired, break and signal timeout below.
                const auto nowTick = ::GetTickCount64( );
                if ( nowTick >= endTick )
                {
                    // Ensure a meaningful timeout error is reported.
                    ::SetLastError( ERROR_SEM_TIMEOUT );
                    ThrowLastOSError( );
                }
                auto remainingMs64 = endTick - nowTick;

                // WaitNamedPipeW accepts a DWORD timeout. Clamp to MAXDWORD if remaining is larger.
                DWORD waitTimeout = ( remainingMs64 > static_cast< ULONGLONG >( MAXDWORD ) ) ? MAXDWORD : static_cast< DWORD >( remainingMs64 );

                // Wait for an instance to become available, but do not wait longer than remaining time.
                if ( WaitNamedPipeW( pipeName, waitTimeout ) == 0 )
                {
                    // WaitNamedPipeW failed / timed out -> throw with the last error.
                    ThrowLastOSError( );
                }

                // At this point, WaitNamedPipeW returned success (an instance should be available),
                // but there is a race: CreateFileW may still return ERROR_PIPE_BUSY. Loop will retry.
                // To avoid a tight spin when the pipe appears and still races, yield briefly.
                // The yield is intentionally tiny; it reduces CPU usage on spurious busy spins.
                constexpr DWORD SpinYieldMs = 1;
                if ( remainingMs64 > SpinYieldMs )
                {
                    ::Sleep( SpinYieldMs );
                }
            }
            
        }


        static void Call( const wchar_t* pipeName, const void* inBuffer, size_t inBufferSize, void* outBuffer, size_t outBufferSize, size_t* bytesRead, UInt32 timeout )
        {
            if ( pipeName == nullptr )
            {
                throw ArgumentNullException( L"pipeName" );
            }
            if ( inBuffer == nullptr && inBufferSize != 0 )
            {
                throw ArgumentNullException( L"inBuffer" );
            }
            if ( outBuffer == nullptr && outBufferSize != 0 )
            {
                throw ArgumentNullException( L"outBuffer" );
            }

            if ( inBufferSize > static_cast< size_t >( MAXDWORD ) || outBufferSize > static_cast< size_t >( MAXDWORD ) )
            {
                throw ArgumentOutOfRangeException( L"Buffer sizes must be <= MAXDWORD." );
            }

            DWORD inSize = static_cast< DWORD >( inBufferSize );
            DWORD outSize = static_cast< DWORD >( outBufferSize );

            DWORD numberOfBytesRead = 0;
            BOOL result = CallNamedPipeW( pipeName, const_cast< LPVOID >( inBuffer ), inSize, outBuffer, outSize, &numberOfBytesRead, static_cast< DWORD >( timeout ) );
            if ( !result )
            {
                ThrowLastOSError( );
            }

            if ( bytesRead )
            {
                *bytesRead = numberOfBytesRead;
            }
        }

        /// <summary>
        /// Performs a combined write-request and read-reply operation on a connected, message-type named pipe.
        /// </summary>
        /// <param name="inBuffer">Pointer to the request buffer to send. May be null only if <paramref name="inBufferSize"/> is zero.</param>
        /// <param name="inBufferSize">Size, in bytes, of the data to send. Must be <= MAXDWORD.</param>
        /// <param name="outBuffer">Pointer to the buffer that receives the reply. May be null only if <paramref name="outBufferSize"/> is zero.</param>
        /// <param name="outBufferSize">Size, in bytes, of the reply buffer. Must be <= MAXDWORD.</param>
        /// <param name="bytesRead">Optional pointer that receives the number of bytes read from the pipe when the operation completes synchronously. Not set when the operation is pending.</param>
        /// <param name="overlapped">
        /// Optional pointer to an OVERLAPPED structure for overlapped (asynchronous) operation.
        /// If non-null, the pipe handle must have been opened for overlapped I/O (FILE_FLAG_OVERLAPPED).
        /// When overlapped is provided and the operation is pending (GetLastError()==ERROR_IO_PENDING), this method returns without throwing and the caller must use the overlapped mechanism to obtain completion.
        /// </param>
        /// <remarks>
        /// This is a thin wrapper around the Win32 TransactNamedPipe function.
        /// - Validates parameters to avoid undefined behaviour (null pointers with non-zero sizes, and sizes larger than MAXDWORD).
        /// - Uses const_cast to pass the input buffer to the API (the Win32 API expects a non-const LPVOID).
        /// - If called for synchronous operation (overlapped == nullptr), the call either completes and fills <paramref name="bytesRead"/> (if provided),
        ///   or throws a SystemException (via ThrowLastOSError) on failure.
        /// - If called with <paramref name="overlapped"/> != nullptr and the call returns ERROR_IO_PENDING, the function returns without throwing and the operation is pending.
        /// </remarks>
        /// <exception cref="SystemException">Thrown when the underlying TransactNamedPipe fails for reasons other than ERROR_IO_PENDING when overlapped is provided, or for any failure when used synchronously.</exception>
        void Transact( const void* inBuffer, size_t inBufferSize, void* outBuffer, size_t outBufferSize, size_t* bytesRead, OVERLAPPED* overlapped ) const
        {
            if ( inBuffer == nullptr && inBufferSize != 0 )
            {
                throw ArgumentNullException( L"inBuffer" );
            }
            if ( outBuffer == nullptr && outBufferSize != 0 )
            {
                throw ArgumentNullException( L"outBuffer" );
            }

            if ( inBufferSize > static_cast< size_t >( MAXDWORD ) || outBufferSize > static_cast< size_t >( MAXDWORD ) )
            {
                throw ArgumentOutOfRangeException( L"Buffer sizes must be <= MAXDWORD." );
            }

            DWORD inSize = static_cast< DWORD >( inBufferSize );
            DWORD outSize = static_cast< DWORD >( outBufferSize );

            DWORD numberOfBytesRead = 0;
            auto handle = Handle( );

            BOOL result = TransactNamedPipe( handle, const_cast< LPVOID >( inBuffer ), inSize, outBuffer, outSize, &numberOfBytesRead, overlapped );

            if ( !result )
            {
                DWORD error = ::GetLastError( );
                
                if ( overlapped != nullptr && error == ERROR_IO_PENDING )
                {
                    // If operation is overlapped and pending, do not throw since 
                    // caller is expected to complete via overlapped I/O.
                    return;
                }
                // Otherwise, throw an exception with the last Win32 error.
                ThrowLastOSError( );
            }

            // The operation completed synchronously and numberOfBytesRead is valid.
            if ( bytesRead )
            {
                *bytesRead = static_cast< size_t >( numberOfBytesRead );
            }
        }

        /// <summary>
        /// Accepts a client connection to the server end of this named pipe.
        /// </summary>
        /// <param name="overlapped">
        /// Optional pointer to an OVERLAPPED structure for overlapped (asynchronous) connect.
        /// If non-null, the pipe handle MUST have been created with <c>FILE_FLAG_OVERLAPPED</c>.
        /// </param>
        /// <remarks>
        /// - This is a thin wrapper around <c>ConnectNamedPipe</c>.
        /// - If the call succeeds or the client was already connected (GetLastError()==ERROR_PIPE_CONNECTED),
        ///   this method returns normally.
        /// - If <paramref name="overlapped"/> is non-null and the connection is pending
        ///   (GetLastError()==ERROR_IO_PENDING) the method returns without throwing; completion is delivered via the overlapped mechanism.
        /// - Any other failure results in a thrown SystemException (via <c>ThrowOSError</c>).
        /// - The function validates the underlying handle and avoids undefined behavior by checking for an invalid handle.
        /// </remarks>
        /// <exception cref="SystemException">Thrown when ConnectNamedPipe fails for reasons other than ERROR_PIPE_CONNECTED or ERROR_IO_PENDING.</exception>
        void Connect( OVERLAPPED* overlapped = nullptr ) const
        {
            auto handle = Handle( );
            if ( handle == INVALID_HANDLE_VALUE )
            {
                // Defensive: underlying stream/RAII wrapper should normally prevent this,
                // but avoid calling Win32 API with an invalid handle.
                throw InvalidOperationException( L"Invalid pipe handle." );
            }

            // Clear last error to avoid stale error values if ConnectNamedPipe returns FALSE.
            ::SetLastError( 0 );

            BOOL result = ConnectNamedPipe( handle, overlapped );
            if ( result )
            {
                // Connected synchronously.
                return;
            }

            DWORD error = ::GetLastError( );
            
            if ( error == ERROR_PIPE_CONNECTED )
            {
                // Handle already connected ...
                return;
            }
            if ( overlapped != nullptr && error == ERROR_IO_PENDING )
            {
                // Overlapped connect is pending ... 
                return;
            }

            // All other errors are real failures.
            ThrowOSError( error );
        }
        /// <summary>
        /// Disconnects the server end of the named-pipe instance.
        /// </summary>
        /// <remarks>
        /// Calls the Win32 <c>DisconnectNamedPipe</c> function. If no client is connected when
        /// this function is called the call is treated as a no-op (no exception).
        /// This method validates the underlying handle before calling the Win32 API to avoid
        /// undefined behaviour. It clears the thread last-error before calling for deterministic
        /// error handling.
        /// Threading: callers must ensure proper synchronization if multiple threads may call
        /// disconnect/connect concurrently on the same pipe handle.
        /// </remarks>
        /// <exception cref="SystemException">Thrown when DisconnectNamedPipe fails for reasons
        /// other than the pipe not being connected or no client data available.</exception>
        void Disconnect( ) const
        {
            auto handle = Handle( );
            if ( handle == nullptr || handle == INVALID_HANDLE_VALUE )
            {
                // Defensive: avoid calling Win32 with an invalid handle.
                throw InvalidOperationException( L"Invalid pipe handle." );
            }

            // Clear last error for deterministic GetLastError() after the API call.
            ::SetLastError( 0 );

            BOOL result = DisconnectNamedPipe( handle );
            if ( result )
            {
                // Success.
                return;
            }

            DWORD error = ::GetLastError( );
            // If there is no client connected or no data, treat as non-fatal (no-op).
            if ( error == ERROR_NO_DATA || error == ERROR_PIPE_NOT_CONNECTED )
            {
                return;
            }

            // All other errors are considered fatal for this operation.
            ThrowLastOSError( );
        }

        /// <summary>
        /// Peeks at data in the pipe without removing it from the queue.
        /// </summary>
        /// <param name="outBuffer">
        /// Pointer to a buffer that receives data from the pipe. May be null if <paramref name="outBufferSize"/> is zero.
        /// </param>
        /// <param name="outBufferSize">Size, in bytes, of <paramref name="outBuffer"/>. Must be <= MAXDWORD.</param>
        /// <param name="bytesRead">
        /// Optional pointer that receives the number of bytes copied to <paramref name="outBuffer"/> by this call when the call completes synchronously.
        /// </param>
        /// <param name="totalBytesAvail">
        /// Optional pointer that receives the total number of bytes available to be read from the pipe (does not remove them).
        /// </param>
        /// <param name="bytesLeftThisMessage">
        /// Optional pointer that receives the number of bytes left to read in this message (for message-type pipes).
        /// </param>
        /// <remarks>
        /// Wrapper around the Win32 `PeekNamedPipe` API:
        /// - Validates arguments to avoid undefined behaviour (null buffer with non-zero size, oversized buffer).
        /// - Validates the underlying handle before calling the Win32 API.
        /// - Passes `nullptr` for optional output pointers the caller did not supply to avoid unnecessary work.
        /// - Clears the thread last-error before the call for deterministic error reporting and calls `ThrowLastOSError` on failure.
        /// </remarks>
        /// <exception cref="SystemException">Thrown when the underlying Win32 call fails.</exception>
        void Peek( void* outBuffer, size_t outBufferSize, size_t* bytesRead, size_t* totalBytesAvail, size_t* bytesLeftThisMessage ) const
        {
            // Parameter validation
            if ( outBuffer == nullptr && outBufferSize != 0 )
            {
                throw ArgumentNullException( L"outBuffer" );
            }
            if ( outBufferSize > static_cast< size_t >( MAXDWORD ) )
            {
                throw ArgumentOutOfRangeException( L"outBufferSize" );
            }

            auto handle = Handle( );
            if ( handle == nullptr || handle == INVALID_HANDLE_VALUE )
            {
                throw InvalidOperationException( L"Invalid pipe handle." );
            }

            // Local temporaries for values we may or may not return to caller.
            DWORD numberOfBytesRead = 0;
            DWORD totalNumberOfBytesAvail = 0;
            DWORD numberOfBytesLeftThisMessage = 0;

            // Clear last error to ensure GetLastError() reflects this call.
            ::SetLastError( 0 );

            // Only pass addresses to PeekNamedPipe for outputs the caller actually requested.
            BOOL result = PeekNamedPipe( handle, outBuffer, static_cast< DWORD >( outBufferSize ), ( bytesRead ? &numberOfBytesRead : nullptr ), ( totalBytesAvail ? &totalNumberOfBytesAvail : nullptr ), ( bytesLeftThisMessage ? &numberOfBytesLeftThisMessage : nullptr ) );

            if ( !result )
            {
                ThrowLastOSError( );
            }

            // Copy results into caller-provided outputs.
            if ( bytesRead )
            {
                *bytesRead = static_cast< size_t >( numberOfBytesRead );
            }
            if ( totalBytesAvail )
            {
                *totalBytesAvail = static_cast< size_t >( totalNumberOfBytesAvail );
            }
            if ( bytesLeftThisMessage )
            {
                *bytesLeftThisMessage = static_cast< size_t >( numberOfBytesLeftThisMessage );
            }
        }

        /// <summary>
        /// Retrieves the client computer name for the client connected to this named-pipe instance.
        /// </summary>
        /// <typeparam name="T">The string-like type to return. Must be constructible from <c>const wchar_t*</c>. Defaults to <c>WideString</c>.</typeparam>
        /// <returns>An instance of <typeparamref name="T"/> containing the client computer name (null-terminated).</returns>
        /// <remarks>
        /// - Wraps the Win32 API <c>GetNamedPipeClientComputerNameW</c>. The API expects the buffer size in characters (wchar_t), not bytes.
        /// - Starts with a small stack buffer for the common case. If the stack buffer is too small the implementation retries with a dynamically-sized heap buffer.
        /// - The pipe handle must be a valid server end handle and a client must be connected; otherwise the call fails.
        /// - This method sets thread last-error to 0 before calling the API to guarantee deterministic error reporting.
        /// - Ownership: returned string is owned by the caller (constructed copy). No ownership or lifetime requirements apply to the pipe handle beyond it being valid and connected for the call.
        /// </remarks>
        /// <exception cref="SystemException">Thrown when the underlying Win32 call fails (GetLastError is propagated).</exception>
        template<WideStringLike T = WideString>
            requires std::is_constructible_v<T, const wchar_t*>
        T GetClientComputerName( ) const
        {
            // The maximum length of the name of a Windows named pipe is 256 characters,
            // so 512 characters is more than enough for the computer name.
            constexpr size_t maxChars = 512;
            wchar_t buffer[ maxChars ];

            auto handle = Handle( );
            if ( handle == nullptr || handle == INVALID_HANDLE_VALUE )
            {
                throw InvalidOperationException( L"Invalid pipe handle." );
            }

            ::SetLastError( 0 );

            if ( GetNamedPipeClientComputerNameW( handle, buffer, static_cast< DWORD >( maxChars ) ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return T( buffer );
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
