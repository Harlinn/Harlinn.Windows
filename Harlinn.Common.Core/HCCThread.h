#pragma once
#ifndef __HCCTHREAD_H__
#define __HCCTHREAD_H__
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
#include <HCCSync.h>


namespace Harlinn::Common::Core
{
    
    enum class ThreadAccessRights : DWORD
    {
        HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS,
        Terminate = THREAD_TERMINATE,
        SuspendAndResume = THREAD_SUSPEND_RESUME,
        GetContext = THREAD_GET_CONTEXT,
        SetContext = THREAD_SET_CONTEXT,
        ReadInformation = THREAD_QUERY_INFORMATION,
        WriteInformation = THREAD_SET_INFORMATION,
        WriteThreadToken = THREAD_SET_THREAD_TOKEN,
        Impersonate = THREAD_IMPERSONATE,
        ImpersonateClient = THREAD_DIRECT_IMPERSONATION,
        WriteLimitedInformation = THREAD_SET_LIMITED_INFORMATION,
        ReadLimitedInformation = THREAD_QUERY_LIMITED_INFORMATION,
        Resume = THREAD_RESUME,
        FullControl = THREAD_ALL_ACCESS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ThreadAccessRights, DWORD );


    class ThreadAccessMask : public Security::AccessMaskT<ThreadAccessMask, ThreadAccessRights>
    {
    public:
        using Base = Security::AccessMaskT<ThreadAccessMask, ThreadAccessRights>;
        static constexpr const Security::GenericMapping Mapping{
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( ThreadAccessRights::FullControl ) ) };

        constexpr ThreadAccessMask( ) noexcept
        {
        }
        constexpr explicit ThreadAccessMask( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }

        constexpr explicit ThreadAccessMask( ThreadAccessRights rights ) noexcept
            : Base( rights )
        {
        }

        explicit ThreadAccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit ThreadAccessMask( ACCESS_MASK mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }

        explicit ThreadAccessMask( const ThreadAccessMask& mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }
        explicit ThreadAccessMask( const ThreadAccessMask& mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }

        explicit ThreadAccessMask( ThreadAccessRights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }
        explicit ThreadAccessMask( ThreadAccessRights rights, const Security::GenericMapping& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }


        constexpr bool CanTerminate( ) const noexcept
        {
            return Check<ThreadAccessRights::Terminate>( );
        }
        constexpr void SetTerminate( bool value = true ) noexcept
        {
            SetBitFlag<ThreadAccessRights::Terminate>( value );
        }

        constexpr bool CanSuspendAndResume( ) const noexcept
        {
            return Check<ThreadAccessRights::SuspendAndResume>( );
        }
        constexpr void SetSuspendAndResume( bool value = true ) noexcept
        {
            SetBitFlag<ThreadAccessRights::SuspendAndResume>( value );
        }

        constexpr bool CanGetContext( ) const noexcept
        {
            return Check<ThreadAccessRights::GetContext>( );
        }
        constexpr void SetGetContext( bool value = true ) noexcept
        {
            SetBitFlag<ThreadAccessRights::GetContext>( value );
        }

        constexpr bool CanSetContext( ) const noexcept
        {
            return Check<ThreadAccessRights::SetContext>( );
        }
        constexpr void SetSetContext( bool value = true ) noexcept
        {
            SetBitFlag<ThreadAccessRights::SetContext>( value );
        }

        constexpr bool CanReadInformation( ) const noexcept
        {
            return Check<ThreadAccessRights::ReadInformation>( );
        }
        constexpr void SetReadInformation( bool value = true ) noexcept
        {
            SetBitFlag<ThreadAccessRights::ReadInformation>( value );
        }

        constexpr bool CanWriteInformation( ) const noexcept
        {
            return Check<ThreadAccessRights::WriteInformation>( );
        }
        constexpr void SetWriteInformation( bool value = true ) noexcept
        {
            SetBitFlag<ThreadAccessRights::WriteInformation>( value );
        }

        constexpr bool CanWriteThreadToken( ) const noexcept
        {
            return Check<ThreadAccessRights::WriteThreadToken>( );
        }
        constexpr void SetWriteThreadToken( bool value = true ) noexcept
        {
            SetBitFlag<ThreadAccessRights::WriteThreadToken>( value );
        }

        constexpr bool CanImpersonate( ) const noexcept
        {
            return Check<ThreadAccessRights::Impersonate>( );
        }
        constexpr void SetImpersonate( bool value = true ) noexcept
        {
            SetBitFlag<ThreadAccessRights::Impersonate>( value );
        }

        constexpr bool CanImpersonateClient( ) const noexcept
        {
            return Check<ThreadAccessRights::ImpersonateClient>( );
        }
        constexpr void SetImpersonateClient( bool value = true ) noexcept
        {
            SetBitFlag<ThreadAccessRights::ImpersonateClient>( value );
        }

        constexpr bool CanWriteLimitedInformation( ) const noexcept
        {
            return Check<ThreadAccessRights::WriteLimitedInformation>( );
        }
        constexpr void SetWriteLimitedInformation( bool value = true ) noexcept
        {
            SetBitFlag<ThreadAccessRights::WriteLimitedInformation>( value );
        }

        constexpr bool CanReadLimitedInformation( ) const noexcept
        {
            return Check<ThreadAccessRights::ReadLimitedInformation>( );
        }
        constexpr void SetReadLimitedInformation( bool value = true ) noexcept
        {
            SetBitFlag<ThreadAccessRights::ReadLimitedInformation>( value );
        }

        constexpr bool CanResume( ) const noexcept
        {
            return Check<ThreadAccessRights::Resume>( );
        }
        constexpr void SetResume( bool value = true ) noexcept
        {
            SetBitFlag<ThreadAccessRights::Resume>( value );
        }

    };


    enum class ThreadPriority
    {
        Idle = THREAD_PRIORITY_IDLE,
        Lowest = THREAD_PRIORITY_LOWEST,
        BelowNormal = THREAD_PRIORITY_BELOW_NORMAL,
        Normal = THREAD_PRIORITY_NORMAL,
        AboveNormal = THREAD_PRIORITY_ABOVE_NORMAL,
        Highest = THREAD_PRIORITY_HIGHEST,
        TimeCritical = THREAD_PRIORITY_TIME_CRITICAL,
        BackgroundBegin = THREAD_MODE_BACKGROUND_BEGIN,
        BackgroundEnd = THREAD_MODE_BACKGROUND_END
    };


    namespace CurrentThread
    {
        namespace Internal
        {
            struct ClientId
            {
#ifdef WIN64
                UInt64 Process;
                UInt64 Thread;
#else
                UInt32 Process;
                UInt32 Thread;
#endif
            };
            struct ThreadEnvironmentBlock : public NT_TIB
            {
                PVOID EnvironmentPointer;
                ClientId ClientId;
            };
        }

        inline UInt32 Id( )
        {
            return GetCurrentThreadId( );
        }
        inline HANDLE Handle( )
        {
            return GetCurrentThread( );
        }

        inline CurrentThread::Internal::ThreadEnvironmentBlock* EnvironmentBlock( )
        {
            return (CurrentThread::Internal::ThreadEnvironmentBlock*)NtCurrentTeb( );
        }


        inline WideString Description( )
        {
            PWSTR data = nullptr;
            HRESULT hr = GetThreadDescription( GetCurrentThread( ), &data );
            if ( FAILED( hr ) )
            {
                ThrowOSError( hr );
            }
            if ( data )
            {
                WideString result( data );
                LocalFree( data );
                return result;
            }
            else
            {
                return WideString( );
            }
        }
        inline void SetDescription( const wchar_t* threadDescription )
        {
            HRESULT hr = ::SetThreadDescription( GetCurrentThread( ), threadDescription );
            if ( FAILED( hr ) )
            {
                ThrowOSError( hr );;
            }
        }

        inline [[nodiscard]] ThreadPriority Priority( )
        {
            return static_cast<ThreadPriority>( GetThreadPriority( GetCurrentThread( ) ) );
        }

        inline void SetPriority( ThreadPriority priority )
        {
            auto rc = SetThreadPriority( GetCurrentThread( ), static_cast<int>( priority ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }


#ifdef Yield
#undef Yield
#endif
        /// <summary>
        /// Causes the calling thread to yield execution to another 
        /// thread that is ready to run on the current processor. 
        /// The operating system selects the next thread to be executed.
        /// </summary>
        /// <returns>
        /// If the operating system to switched execution to another thread, 
        /// the return value is true, otherwise it is false.
        /// </returns>
        inline bool Yield( ) noexcept
        {
            return SwitchToThread( );
        }
        /// <summary>
        /// Causes the calling thread to yield execution to another 
        /// thread that is ready to run on the current processor. 
        /// The operating system selects the next thread to be executed.
        /// </summary>
        /// <returns>
        /// If the operating system to switched execution to another thread, 
        /// the return value is true, otherwise it is false.
        /// </returns>
        inline bool yield( ) noexcept
        {
            return SwitchToThread( );
        }

        inline void Sleep( DWORD milliSeconds )
        {
            ::Sleep( milliSeconds );
        }
        inline void sleep( DWORD milliSeconds )
        {
            ::Sleep( milliSeconds );
        }

        inline void Sleep( const TimeSpan& period )
        {
            DWORD duration = period.Ticks( ) ? static_cast<DWORD>( period.TotalMilliseconds( ) ) : 0;
            ::Sleep( duration );
        }
        inline void sleep( const TimeSpan& period )
        {
            DWORD duration = period.Ticks( ) ? static_cast<DWORD>( period.TotalMilliseconds( ) ) : 0;
            ::Sleep( duration );
        }

        inline UInt64 QueryCycleTime( )
        {
            UInt64 result;
            auto rc = QueryThreadCycleTime( Handle( ), &result );
            if ( rc == static_cast<DWORD>( -1 ) )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        inline Security::Token OpenToken( Security::TokenAccessMask desiredAccess, bool useProcessSecurityContext = false )
        {
            HANDLE threadTokenHandle = 0;
            HANDLE currentThreadHandle = Handle( );
            auto rc = OpenThreadToken( currentThreadHandle, desiredAccess.Value(), useProcessSecurityContext,&threadTokenHandle );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return Security::Token( threadTokenHandle );
        }

        inline Security::Token OpenToken( Security::TokenAccessRights desiredAccess, bool useProcessSecurityContext = false )
        {
            Security::TokenAccessMask mask( desiredAccess );
            return OpenToken( mask, useProcessSecurityContext );
        }

    }




    class Thread : public WaitableHandle
    {
        UInt32 threadId_;
    public:
        using Base = WaitableHandle;
        using native_handle_type = HANDLE;
    private:
        template <class TupleType, size_t... indices>
        static UInt32 __stdcall Invoke( void* threadArgs ) noexcept
        {
            UInt32 result = 0;
            // Take ownership of the arguments
            const std::unique_ptr<TupleType> callableAndArgs( static_cast<TupleType*>( threadArgs ) );
            TupleType& tuple = *callableAndArgs;
            try
            {
                if constexpr ( std::is_integral_v < decltype( std::invoke( std::move( std::get<indices>( tuple ) )... ) ) > )
                {
                    result = std::invoke( std::move( std::get<indices>( tuple ) )... );
                }
                else
                {
                    std::invoke( std::move( std::get<indices>( tuple ) )... );
                }
            }
            catch ( ThreadAbortException& abortException )
            {
                result = abortException.ExitCode( );
            }
            _Cnd_do_broadcast_at_thread_exit( );
            return result;
        }

        template <class TupleType, size_t... indices>
        static constexpr auto MakeInvoke( std::index_sequence<indices...> ) noexcept
        {
            return &Invoke<TupleType, indices...>;
        }
    public:
        constexpr Thread( ) noexcept
            : threadId_( 0 )
        {
        }

        constexpr Thread( HANDLE handle, UInt32 threadId ) noexcept
            : Base( handle ), threadId_( threadId )
        {
        }


        template <class Function, class... Args>
            requires (std::is_same_v<std::remove_cvref_t<Function>, Thread> == false)
        explicit Thread( Function&& function, Args&&... args )
            : Base(nullptr), threadId_(0)
        {
            using TupleType = std::tuple<std::decay_t<Function>, std::decay_t<Args>...>;
            auto decayCopied = std::make_unique<TupleType>( std::forward<Function>( function ), std::forward<Args>( args )... );
            constexpr auto invoker = MakeInvoke<TupleType>( std::make_index_sequence<1 + sizeof...( Args )>{} );

            UInt32 threadId = 0;
#pragma warning(push)
#pragma warning(disable : 5039)
            auto handle = reinterpret_cast<void*>( _beginthreadex( nullptr, 0, invoker, decayCopied.get( ), 0, &threadId ) );
#pragma warning(pop)

            if ( handle )
            { 
                // Release ownership of the arguments, they are now 
                // owned by the thread
                decayCopied.release( );
                SetHandle( handle );
                threadId_ = threadId;
            }
            else
            { 
                ThrowLastOSError( );
            }
        }

        template <class Function, class... Args>
        requires ( std::is_same_v<std::remove_cvref_t<Function>, Thread> == false )
            explicit Thread( LPSECURITY_ATTRIBUTES securityAttributes, Function&& function, Args&&... args )
            : Base(nullptr), threadId_(0)
        {
            using TupleType = std::tuple<std::decay_t<Function>, std::decay_t<Args>...>;
            auto decayCopied = std::make_unique<TupleType>( std::forward<Function>( function ), std::forward<Args>( args )... );
            constexpr auto invoker = MakeInvoke<TupleType>( std::make_index_sequence<1 + sizeof...( Args )>{} );

            UInt32 threadId = 0;
#pragma warning(push)
#pragma warning(disable : 5039)
            auto handle = reinterpret_cast<void*>( _beginthreadex( securityAttributes, 0, invoker, decayCopied.get( ), 0, &threadId ) );
#pragma warning(pop)

            if ( handle )
            { 
                // Release ownership of the arguments, they are now 
                // owned by the thread
                decayCopied.release( );
                SetHandle( handle );
                threadId_ = threadId;
            }
            else
            { 
                ThrowLastOSError( );
            }
        }

        Thread( const Thread& other ) = delete;
        Thread( Thread&& other ) noexcept
            : Base( other.ReleaseHandle() ), threadId_( other.threadId_ )
        {
            other.threadId_ = 0;
        }


        Thread& operator = ( const Thread& other ) = delete;
        Thread& operator = ( Thread&& other ) noexcept
        {
            if ( this != &other )
            {
                TakeOwnership( std::move( other ) );
                threadId_ = other.threadId_;
                other.threadId_ = 0;
            }
            return *this;
        }


        bool joinable( ) const
        {
            return GetHandle() && threadId_ != CurrentThread::Id( );
        }

        void join( ) const
        {
            Wait( );
        }

        constexpr UInt32 get_id( ) const noexcept
        {
            return threadId_;
        }
        constexpr UInt32 Id( ) const noexcept
        {
            return threadId_;
        }

        constexpr native_handle_type native_handle( ) const noexcept
        {
            return GetHandle( );
        }

        [[noreturn]] void Exit( DWORD exitcode )
        {
            throw ThreadAbortException( exitcode );
        }

        /// <summary>
        /// Attaches or detaches the input processing mechanism of the argument thread 
        /// to that this thread.
        /// </summary>
        /// <remarks>
        /// The AttachInput function lets a thread can share its input states (such as 
        /// keyboard states and the current focus window) with another thread. Keyboard 
        /// and mouse events received by both threads are processed in the order they 
        /// were received until the threads are detached by calling AttachInput a second 
        /// time and specifying false for the attach parameter.
        /// 
        /// The function fails if either of the specified threads does not have a message 
        /// queue. The system creates a thread's message queue when the thread makes its 
        /// first call to one of the USER or GDI functions. The function also fails if a 
        /// journal record hook is installed. Journal record hooks attach all input 
        /// queues together.
        /// 
        /// Note that key state, which can be ascertained by calls to the GetKeyState 
        /// or GetKeyboardState function, is reset after a call to this function. You cannot 
        /// attach a thread to a thread in another desktop.
        /// </remarks>
        /// <param name="attachFrom">The thread to be attached to this thread. The thread to be attached cannot be a system thread</param>
        /// <param name="attach">If this parameter is true, the threads are attached. If the parameter is false, the threads are detached.</param>
        void AttachInput( const Thread& attachFrom, bool attach = true ) const
        {
            auto rc = AttachThreadInput( attachFrom.Id( ), Id( ), attach );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        static constexpr DWORD StillActive = STILL_ACTIVE;

        /// <summary>
        /// Retrieves the termination status of the specified thread
        /// </summary>
        /// <returns>The thread termination status</returns>
        DWORD ExitCode( ) const
        {
            DWORD exitCode = 0;
            auto rc = GetExitCodeThread( GetHandle(), &exitCode );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return exitCode;
        }

        /// <summary>
        /// Check if the thread is still active
        /// </summary>
        /// <returns>True if the thread is still active</returns>
        bool IsStillActive( ) const
        {
            return ExitCode( ) == StillActive;
        }

        [[nodiscard]] WideString Description( ) const
        {
            PWSTR data = nullptr;
            HRESULT hr = GetThreadDescription( GetHandle(), &data );
            if ( FAILED( hr ) )
            {
                ThrowOSError( hr );
            }
            if ( data )
            {
                WideString result( data );
                LocalFree( data );
                return result;
            }
            else
            {
                return WideString( );
            }
        }
        void SetDescription( const wchar_t* threadDescription ) const
        {
            HRESULT hr = ::SetThreadDescription( GetHandle(), threadDescription );
            if ( FAILED( hr ) )
            {
                ThrowOSError( hr );;
            }
        }

        /// <summary>
        /// Retrieves the processor group affinity of the thread
        /// </summary>
        /// <returns>The group affinity of the thread</returns>
        [[nodiscard]] GROUP_AFFINITY Affinity( ) const
        {
            GROUP_AFFINITY affinity;
            auto rc = GetThreadGroupAffinity( GetHandle( ), &affinity );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return affinity;
        }

        /// <summary>
        /// Sets the processor group affinity for the specified thread
        /// </summary>
        /// <param name="affinity">The GROUP_AFFINITY structure that specifies the processor group affinity to be used for the thread</param>
        /// <returns>The thread's previous group affinity</returns>
        GROUP_AFFINITY SetAffinity( const GROUP_AFFINITY& affinity ) const
        {
            GROUP_AFFINITY previousAffinity;
            auto rc = SetThreadGroupAffinity( GetHandle( ), &affinity, &previousAffinity );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return previousAffinity;
        }

        /// <summary>
        /// Retrieves the processor number of the ideal processor for the specified thread.
        /// </summary>
        /// <returns>PROCESSOR_NUMBER structure with number of the ideal processor</returns>
        [[nodiscard]] PROCESSOR_NUMBER IdealProcessor( ) const
        {
            PROCESSOR_NUMBER result;
            auto rc = GetThreadIdealProcessorEx( GetHandle( ), &result );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        /// <summary>
        /// Sets the ideal processor for the specified thread
        /// </summary>
        /// <param name="processorNumber">The PROCESSOR_NUMBER structure that specifies the processor number of the desired ideal processor.</param>
        /// <returns>The previous ideal processor</returns>
        PROCESSOR_NUMBER SetIdealProcessor(const PROCESSOR_NUMBER& processorNumber ) const
        {
            PROCESSOR_NUMBER result;
            auto rc = SetThreadIdealProcessorEx( GetHandle( ), const_cast<PROCESSOR_NUMBER*>(&processorNumber), &result );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        void GetInformation( MEMORY_PRIORITY_INFORMATION& memoryPriorityInformation ) const
        {
            auto rc = GetThreadInformation( GetHandle(), ThreadMemoryPriority, &memoryPriorityInformation, sizeof( MEMORY_PRIORITY_INFORMATION ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
        void SetInformation( const MEMORY_PRIORITY_INFORMATION& memoryPriorityInformation ) const
        {
            auto rc = SetThreadInformation( GetHandle( ), ThreadMemoryPriority, const_cast<MEMORY_PRIORITY_INFORMATION*>(&memoryPriorityInformation), sizeof( MEMORY_PRIORITY_INFORMATION ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        void GetInformation( THREAD_POWER_THROTTLING_STATE& threadPowerThrottlingState ) const
        {
            auto rc = GetThreadInformation( GetHandle( ), ThreadPowerThrottling, &threadPowerThrottlingState, sizeof( THREAD_POWER_THROTTLING_STATE ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
        void SetInformation( const THREAD_POWER_THROTTLING_STATE& threadPowerThrottlingState ) const
        {
            auto rc = SetThreadInformation( GetHandle( ), ThreadPowerThrottling, const_cast<THREAD_POWER_THROTTLING_STATE*>(&threadPowerThrottlingState), sizeof( THREAD_POWER_THROTTLING_STATE ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Determines whether the thread has any pending I/O requests 
        /// </summary>
        /// <returns>True if the thread has one or more pending I/O requests</returns>
        bool HasIOPending( ) const
        {
            BOOL result;
            auto rc = GetThreadIOPendingFlag( GetHandle( ), &result );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return result != 0;
        }


        /// <summary>
        /// Retrieves the priority for the thread
        /// </summary>
        /// <returns>The priority for the thread</returns>
        [[nodiscard]] ThreadPriority Priority( ) const
        {
            return static_cast<ThreadPriority>( GetThreadPriority( GetHandle() ) );
        }

        void SetPriority( ThreadPriority priority ) const
        {
            auto rc = SetThreadPriority( GetHandle( ), static_cast<int>( priority ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Check if dynamic boosting is disabled
        /// </summary>
        /// <returns>True if dynamic boosting is disabled</returns>
        bool PriorityBoostDisabled( ) const
        {
            BOOL result;
            auto rc = GetThreadPriorityBoost( GetHandle( ), &result );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return result != 0;
        }

        void SetPriorityBoostDisabled( bool disablePriorityBoost = true ) const
        {
            auto rc = SetThreadPriorityBoost( GetHandle( ), disablePriorityBoost );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Decrements the thread's suspend count
        /// </summary>
        DWORD Resume( ) const
        {
            auto rc = ResumeThread( GetHandle( ) );
            if ( rc == static_cast<DWORD>( -1 ) )
            {
                ThrowLastOSError( );
            }
            return rc;
        }

        /// <summary>
        /// Suspends the specified thread
        /// </summary>
        /// <returns>The previous suspend count</returns>
        DWORD Suspend( )  const
        {
            auto rc = SuspendThread( GetHandle( ) );
            if ( rc == static_cast<DWORD>( -1 ) )
            {
                ThrowLastOSError( );
            }
            return rc;
        }

        /// <summary>
        /// Retrieves the cycle time for the thread
        /// </summary>
        /// <returns>The number of CPU clock cycles used by the thread.</returns>
        UInt64 QueryCycleTime( ) const
        {
            UInt64 result;
            auto rc = QueryThreadCycleTime( GetHandle( ), &result );
            if ( rc == static_cast<DWORD>( -1 ) )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        Security::Token OpenToken( Security::TokenAccessMask desiredAccess, bool useProcessSecurityContext = false ) const
        {
            HANDLE threadTokenHandle = 0;
            HANDLE currentThreadHandle = GetHandle( );
            auto rc = OpenThreadToken( currentThreadHandle, desiredAccess.Value( ), useProcessSecurityContext, &threadTokenHandle );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return Security::Token( threadTokenHandle );
        }

        Security::Token OpenToken( Security::TokenAccessRights desiredAccess, bool useProcessSecurityContext = false ) const
        {
            Security::TokenAccessMask mask( desiredAccess );
            return OpenToken( mask, useProcessSecurityContext );
        }

        static size_t HardwareConcurrency( )
        {
            SYSTEM_INFO systemInfo{};
            GetNativeSystemInfo( &systemInfo );
            return systemInfo.dwNumberOfProcessors;
        }





    };

    class ThreadGroup
    {
        CriticalSection criticalSection_;
        std::unordered_map<HANDLE, Thread> threads_;
    public:
        ThreadGroup( )
        {
        }


        ThreadGroup( const ThreadGroup& other ) = delete;
        ThreadGroup& operator = ( const ThreadGroup& other ) = delete;

        template <class Function, class... Args>
        void Add( Function&& function, Args&&... args )
            requires ( std::is_invocable_v<Function, Args...> && 
                std::is_same_v<std::remove_cvref_t<Function>, Thread> == false )
        {
            Thread thread( std::forward<Function>( function ), std::forward<Args>( args )... );
            auto handle = thread.GetHandle( );
            {
                std::lock_guard lock_guard( criticalSection_ );
                threads_.emplace( handle, std::move( thread ) );
            }
        }

        bool Wait(DWORD timeout = INFINITE ) const
        {   
            if ( threads_.size( ) <= MAXIMUM_WAIT_OBJECTS )
            {
                DWORD count = static_cast<DWORD>( threads_.size( ) );
                std::array<HANDLE, MAXIMUM_WAIT_OBJECTS> handles;
                size_t handleIndex = 0;
                for ( const auto& entry : threads_ )
                {
                    handles[handleIndex] = entry.first;
                    handleIndex++;
                }
                auto rc = WaitForMultipleObjects( count, handles.data( ), true, timeout );
                if ( rc == WAIT_FAILED )
                {
                    ThrowLastOSError( );
                }
                return rc != WAIT_TIMEOUT;
            }
            else
            {
                throw std::exception( "Too many threads, cannot call WaitForMultipleObjects" );
            }
        }

        void join( ) const
        {
            for ( auto& entry : threads_ )
            {
                entry.second.join( );
            }
        }

    };




}

#endif
