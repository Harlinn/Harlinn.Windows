#pragma once
#ifndef __HCCIOCONTEXT_H__
#define __HCCIOCONTEXT_H__

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


#include <HCCIO.h>
#include <HCCIOCompletionPort.h>
#include <HCCThread.h>
#include <HCCSync.h>
#include <HCCMemory.h>

namespace Harlinn::Common::Core::IO
{
    class Context;
    /// <summary>
    /// Base class for asynchronous I/O notification handlers.
    /// </summary>
    /// <remarks>
    /// <p>
    /// Classes derived from <c>ContextHandler</c> are responsible for
    /// initializing asynchronous I/O requests, and handling I/O completion 
    /// notifications. 
    /// </p>
    /// <p>
    /// There are usually a one-to-one relationship between a handle and 
    /// an instance of a class derived from <c>ContextHandler</c>. 
    /// </p>
    /// </remarks>
    class ContextHandler abstract : public std::enable_shared_from_this<ContextHandler>
    {
        friend class Context;
        mutable std::weak_ptr<Context> context_;
    public:
        using Message = IOCompletionPort::Message;
    protected:
        /// <summary>
        /// Initializes a new instance of <c>ContextHandler</c>.
        /// </summary>
        /// <param name="context">
        /// A reference to the <c>Context</c> that the new 
        /// <c>ContextHandler</c> will be added to. 
        /// </param>
        ContextHandler( const std::shared_ptr<Context>& context );
    public:
        virtual ~ContextHandler( ) = default;

        /// <summary>
        /// Retrieves a const reference to the <c>IO::Context</c> that
        /// this <c>ContextHandler</c> is bound to.
        /// </summary>
        /// <returns>A const reference to the IO::Context</returns>
        std::shared_ptr<const IO::Context> Context( ) const noexcept
        {
            return context_.lock();
        }
        /// <summary>
        /// Retrieves a reference to the <c>IO::Context</c> that
        /// this <c>ContextHandler</c> is bound to.
        /// </summary>
        /// <returns>A reference to the IO::Context</returns>
        std::shared_ptr<IO::Context> Context( ) noexcept
        {
            return context_.lock( );
        }

        /// <summary>
        /// Starts the <c>ContextHandler</c>.
        /// </summary>
        /// <remarks>
        /// <p>
        /// Called by the <c>IO::Context</c> after the context has populated its thread-pool 
        /// for every <c>ContextHandler</c> added to the context before the context is started.
        /// </p>
        /// If a <c>ContextHandler</c> is added to the <c>IO::Context</c> after the 
        /// context is started, the caller must call <c>Start()</c> on the <c>ContextHandler</c>
        /// after it has been added to the <c>IO::Context</c>.
        /// </remarks>
        virtual void Start( )
        {
        }

        /// <summary>
        /// Called by the context when it stops.
        /// </summary>
        virtual void Stop( )
        {
        }
    protected:
        /// <summary>
        /// This function is responsible for handling the
        /// I/O completion notification messages
        /// </summary>
        /// <param name="message">
        /// The I/O completion notification received from the
        /// completion queue of the I/O completion port.
        /// </param>
        /// <returns>
        /// <c>true</c> if the handler successfully processed the I/O completion notification message, otherwise false.
        /// </returns>
        virtual bool Process( Message& message ) = 0;

        /// <summary>
        /// This is the last function that gets called when an 
        /// I/O completion notification message is processed 
        /// asynchronously be a thread in the thread-pool.
        /// </summary>
        /// <param name="message">
        /// The I/O completion notification received from the
        /// completion queue of the I/O completion port.
        /// </param>
        /// <remarks>
        /// <p>
        /// If the <c>IO::Request</c> object for the asynchronous operation
        /// was allocated dynamically, the this function must be overridden
        /// to release the <c>IO::Request</c> object.
        /// </p>
        /// <code>
        /// auto* request = message.Request( );
        /// delete request;
        /// </code>
        /// <p>
        /// It is generally simpler to have a single instance of each
        /// <c>IO::Request</c> derived type required for an implementation
        /// of an <c>IO::ContextHandler</c> that shares the lifetime of that 
        /// <c>IO::ContextHandler</c> implementation. If this is the case, 
        /// then there is no need to override this function.
        /// </p>
        /// <p>
        /// Another option would be to have a pool of <c>IO::Request</c> derived objects,
        /// and then override this function to release the <c>IO::Request</c> derived 
        /// objects back to the pool.
        /// </p>
        /// </remarks>
        virtual void ProcessDone( Message& message )
        {

        }

        void BindRequestToContext( IO::Request* request ) const
        {
            assert( request != nullptr );
            request->SetContext( context_ );
        }

    };
    /// <summary>
    /// Context is an I/O completion port with an attached thread-pool
    /// that services I/O completion notifications.
    /// </summary>
    class Context : public std::enable_shared_from_this<Context>, public IOCompletionPort
    {
    private:
        EventWaitHandle event_;
        DWORD numberOfThreads_;
        ThreadGroup threads_;
        CriticalSection criticalSection_;
        std::set<std::shared_ptr<ContextHandler>> handlers_;
    public:
        using Base = IOCompletionPort;
        static constexpr ULONG_PTR StopId = 1;
        static constexpr ULONG_PTR AsynchId = 2;

        /// <summary>
        /// Initializes a new Context object.
        /// </summary>
        /// <param name="numberOfThreads">
        /// The number of threads that will be added to
        /// the thread-pool when the <c>Context</c> is started.
        /// </param>
        /// <param name="numberOfConcurrentThreads">
        /// The number of threads that will be allowed to execute
        /// concurrently.
        /// </param>
        explicit Context( DWORD numberOfThreads, DWORD numberOfConcurrentThreads )
            : Base( numberOfConcurrentThreads ), event_( true ), numberOfThreads_( numberOfThreads )
        {
            assert( (numberOfConcurrentThreads <= numberOfThreads ) &&
                (numberOfConcurrentThreads > 0) && 
                ( numberOfThreads > 0) );
        }
        explicit Context( DWORD numberOfThreads )
            : Context( numberOfThreads, numberOfThreads / 2 )
        {
            assert( numberOfThreads >= 2 );
        }
        Context( const Context& other ) = delete;
        Context( Context&& other ) = delete;

        HCC_EXPORT virtual ~Context( );

        Context& operator = ( const Context& other ) = delete;
        Context& operator = ( Context&& other ) = delete;


        /// <summary>
        /// Adds the specified <c>ContextHandler</c> to this context.
        /// </summary>
        /// <param name="handler">
        /// Pointer to the <c>ContextHandler</c> that will be added to the context.
        /// </param>
        /// <remarks>
        /// This function gets called by the <c>ContextHandler</c> constructor.
        /// </remarks>
        /// <returns>
        /// <c>true</c> if the <c>ContextHandler</c> that was added to the context.
        /// </returns>
        bool Add( std::shared_ptr<ContextHandler> handler )
        {
            std::lock_guard guard( criticalSection_ );
            auto rc = handlers_.emplace( handler );
            return rc.second;
        }

        /// <summary>
        /// Removes the specified <c>ContextHandler</c> from this
        /// context. There should be no outstanding I/O requests 
        /// for this <c>ContextHandler</c>.
        /// </summary>
        /// <remarks>
        /// This is called by the <c>ContextHandler</c> destructor.
        /// </remarks>
        /// <param name="handler">
        /// Pointer to the <c>ContextHandler</c> that will be removed.
        /// </param>
        /// <returns>
        /// <c>true</c> if the <c>ContextHandler</c> was removed.
        /// </returns>
        bool Remove( std::shared_ptr<ContextHandler> handler )
        {
            std::lock_guard guard( criticalSection_ );
            return handlers_.erase( handler ) != 0;
        }

        /// <summary>
        /// Populates the thread-pool before calling Start on each
        /// instance of a <c>ContextHandler</c> derived class that 
        /// has been added to the context.
        /// </summary>
        HCC_EXPORT void Start( );

        /// <summary>
        /// Sends a stop signal to each thread in the thread-pool, and 
        /// then waits for all of them to terminate.
        /// </summary>
        /// <returns></returns>
        HCC_EXPORT void Stop( );
    protected:
        /// <summary>
        /// Called for messages that were not successfully handled
        /// by their associated <c>ContextHandler</c>.
        /// </summary>
        /// <param name="message">
        /// The I/O completion notification received from the
        /// completion queue of the I/O completion port.
        /// </param>
        /// <remarks>
        /// The current default implementation does nothing.
        /// </remakrs>
        HCC_EXPORT virtual void HandleUnprocessedMessage( Message& message );
        /// <summary>
        /// Implements the per thread message loop.
        /// </summary>
        HCC_EXPORT virtual void ProcessRequests( );
    private:
        typedef void ( __stdcall* InvokeFunctionType )( void* );
        struct AsyncOverlappedBase : public IO::Request
        {
            InvokeFunctionType invokeFunction_ = nullptr;
            AsyncOverlappedBase( InvokeFunctionType invokeFunction )
                : invokeFunction_( invokeFunction )
            {
            }
        };

        template <class Function, class... Args>
        struct AsyncOverlapped : public AsyncOverlappedBase
        {
            using TupleType = std::tuple<std::decay_t<Function>, std::decay_t<Args>...>;
            TupleType tuple_;

            AsyncOverlapped( InvokeFunctionType invokeFunction, Function&& function, Args&&... args )
                : AsyncOverlappedBase( invokeFunction ),tuple_( std::forward<Function>( function ), std::forward<Args>( args )... )
            {
            }
        };
        template <class AsyncOverlappedType, size_t... indices>
        static void __stdcall Invoke( void* taskArgs ) noexcept
        {
            using TupleType = typename AsyncOverlappedType::TupleType;
            // Take ownership of the arguments
            const std::unique_ptr<AsyncOverlappedType> callableAndArgs( static_cast<AsyncOverlappedType*>( taskArgs ) );

            TupleType& tuple = callableAndArgs->tuple_;
            std::invoke( std::move( std::get<indices>( tuple ) )... );
            
        }
        template <class AsyncOverlappedType, size_t... indices>
        static constexpr auto MakeInvoke( std::index_sequence<indices...> ) noexcept
        {
            return &Invoke<AsyncOverlappedType, indices...>;
        }
    public:
        /// <summary>
        /// Delegates the execution of a callable object to a 
        /// thread in the thread-pool.
        /// </summary>
        /// <param name="function">
        /// The callable object to execute in a thread in the 
        /// thread-pool.
        /// </param>
        /// <param name="...args">
        /// arguments to pass to the callable object.
        /// </param>
        template <class Function, class... Args>
        void Async( Function&& function, Args&&... args ) const
        {
            using AsyncOverlappedType = AsyncOverlapped<std::decay_t<Function>, std::decay_t<Args>...>;
            constexpr auto invoker = MakeInvoke<AsyncOverlappedType>( std::make_index_sequence<1 + sizeof...( Args )>{} );
            auto decayCopied = std::make_unique<AsyncOverlappedType>( invoker, std::forward<Function>( function ), std::forward<Args>( args )... );
            Post( 0, reinterpret_cast<void*>( AsynchId ), decayCopied.get( ) );
            decayCopied.release( );
        }
    };

    
    inline ContextHandler::ContextHandler( const std::shared_ptr<IO::Context>& context )
        : context_( context )
    {
    }
    
    

    enum class FileRequestType
    {
        Unknown,
        Read,
        Write,
        ReadScatter,
        WriteGather
    };


    class FileRequest : public IO::Request
    {
    public:
        using Base = IO::Request;
    private:
        FileRequestType type_;
    protected:
        FileRequest( HANDLE handle, FileRequestType type )
            : Base( handle ), type_( type )
        {
        }

        constexpr FileRequest( HANDLE handle, HANDLE manualResetEvent, bool ownsEvent, FileRequestType type ) noexcept
            : Base( handle, manualResetEvent, ownsEvent ), type_( type )
        {
        }
    public:
        constexpr FileRequestType Type( ) const noexcept
        {
            return type_;
        }
    };



    
    class ReadFileRequest : public FileRequest
    {
    public:
        using Base = FileRequest;
        static constexpr FileRequestType RequestType = FileRequestType::Read;
    private:
        Byte* buffer_;
        UInt32 numberOfBytesToRead_;
    public:
        ReadFileRequest( HANDLE handle, Byte* buffer, UInt32 numberOfBytesToRead )
            : Base( handle, RequestType ), buffer_( buffer ), numberOfBytesToRead_( numberOfBytesToRead )
        { }

        constexpr ReadFileRequest( HANDLE handle, HANDLE manualResetEvent, bool ownsEvent, Byte* buffer, UInt32 numberOfBytesToRead ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), buffer_( buffer ), numberOfBytesToRead_( numberOfBytesToRead )
        { }

        ReadFileRequest( const FileStream& fileStream, Byte* buffer, UInt32 numberOfBytesToRead )
            : Base( fileStream.Handle( ), RequestType ), buffer_( buffer ), numberOfBytesToRead_( numberOfBytesToRead )
        { }

        constexpr ReadFileRequest( const FileStream& fileStream, HANDLE manualResetEvent, bool ownsEvent, Byte* buffer, UInt32 numberOfBytesToRead ) noexcept
            : Base( fileStream.Handle( ), manualResetEvent, ownsEvent, RequestType ), buffer_( buffer ), numberOfBytesToRead_( numberOfBytesToRead )
        { }

        constexpr Byte* Buffer( ) const noexcept
        {
            return buffer_;
        }
        constexpr UInt32 NumberOfBytesToRead( ) const noexcept
        {
            return numberOfBytesToRead_;
        }

    };

    class WriteFileRequest : public FileRequest
    {
    public:
        using Base = FileRequest;
        static constexpr FileRequestType RequestType = FileRequestType::Write;
    private:
        Byte* buffer_;
        UInt32 numberOfBytesToWrite_;
    public:
        WriteFileRequest( HANDLE handle, Byte* buffer, UInt32 numberOfBytesToWrite )
            : Base( handle, RequestType ), buffer_( buffer ), numberOfBytesToWrite_( numberOfBytesToWrite )
        { }

        constexpr WriteFileRequest( HANDLE handle, HANDLE manualResetEvent, bool ownsEvent, Byte* buffer, UInt32 numberOfBytesToWrite ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), buffer_( buffer ), numberOfBytesToWrite_( numberOfBytesToWrite )
        { }

        WriteFileRequest( const FileStream& fileStream, Byte* buffer, UInt32 numberOfBytesToWrite )
            : Base( fileStream.Handle( ), RequestType ), buffer_( buffer ), numberOfBytesToWrite_( numberOfBytesToWrite )
        { }

        constexpr WriteFileRequest( const FileStream& fileStream, HANDLE manualResetEvent, bool ownsEvent, Byte* buffer, UInt32 numberOfBytesToWrite ) noexcept
            : Base( fileStream.Handle( ), manualResetEvent, ownsEvent, RequestType ), buffer_( buffer ), numberOfBytesToWrite_( numberOfBytesToWrite )
        { }

        constexpr Byte* Buffer( ) const noexcept
        {
            return buffer_;
        }
        constexpr UInt32 NumberOfBytesToWrite( ) const noexcept
        {
            return numberOfBytesToWrite_;
        }

    };

    template<typename DerivedT>
    class FileHandler : public ContextHandler
    {
    public:
        using Base = ContextHandler;
        using DerivedType = DerivedT;
    private:
        FileStream& fileStream_;
    public:
        FileHandler( std::shared_ptr<IO::Context>& context, FileStream& fileStream )
            : Base( context ), fileStream_( fileStream )
        { 
            context->Bind( fileStream.Handle(), this );
        }
    public:
        constexpr const FileStream& Stream( ) const noexcept
        {
            return fileStream_;
        }

        bool BeginAsyncRead( ReadFileRequest* request )
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

        bool BeginAsyncWrite( WriteFileRequest* request )
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

        virtual bool Process( Message& message ) override
        {
            bool result = false;
            auto request = static_cast<FileRequest*>( message.Request( ) );
            FileRequestType requestType = request->Type( );
            DerivedType& self = static_cast<DerivedType&>( *this );
            switch ( requestType )
            {
                case FileRequestType::Read:
                {
                    result = self.HandleReadCompleted( static_cast<ReadFileRequest*>( request ) );
                }
                break;
                case FileRequestType::Write:
                {
                    result = self.HandleWriteCompleted( static_cast<WriteFileRequest*>( request ) );
                }
                break;
            }
            return result;
        }
    protected:
        constexpr bool HandleReadCompleted( ReadFileRequest* request ) noexcept
        {
            return false;
        }

        constexpr bool HandleWriteCompleted( WriteFileRequest* request ) noexcept
        {
            return false;
        }
    };


    class FileDispatcher : public FileHandler<FileDispatcher>
    {
        template<typename DerivedT>
        friend class FileHandler;
    public:
        using Base = FileHandler<FileDispatcher>;
        boost::signals2::signal<void( const FileDispatcher& dispatcher, ReadFileRequest* request )> OnReadCompleted;
        boost::signals2::signal<void( const FileDispatcher& dispatcher, WriteFileRequest* request )> OnWriteCompleted;

        FileDispatcher( std::shared_ptr<IO::Context>& context, FileStream& fileStream )
            : Base( context, fileStream )
        {
        }

    private:
        bool HandleReadCompleted( ReadFileRequest* request )
        {
            OnReadCompleted( *this, request );
            return true;
        }

        bool HandleWriteCompleted( WriteFileRequest* request )
        {
            OnWriteCompleted( *this, request );
            return true;
        }

    };
}

#endif
