#pragma once
#ifndef __HCCSYNC_H__
#define __HCCSYNC_H__
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

#include <HCCDef.h>
#include <HCCSecurity.h>
#include <HCCDateTime.h>

namespace Harlinn::Common::Core
{


    class ConditionVariable;
    /// <summary>
    /// A critical section object provides synchronization similar to that 
    /// provided by a mutex object, except that a critical section can be 
    /// used only by the threads of a single process. Critical section 
    /// objects cannot be shared across processes.
    /// </summary>
    class CriticalSection
    {
        friend class ConditionVariable;
        mutable CRITICAL_SECTION criticalSection_;
    public:
        static constexpr UInt32 DefaultSpinCount = 4000;

        explicit CriticalSection( UInt32 spinCount = DefaultSpinCount, bool noDebugInfo = true )
        {
            auto rc = InitializeCriticalSectionEx( &criticalSection_, spinCount, noDebugInfo? CRITICAL_SECTION_NO_DEBUG_INFO:0 );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        ~CriticalSection( ) noexcept
        {
            DeleteCriticalSection( &criticalSection_ );
        }

        CriticalSection( const CriticalSection& other ) = delete;
        CriticalSection( CriticalSection&& other ) = delete;
        CriticalSection& operator =( const CriticalSection& other ) = delete;
        CriticalSection& operator =( CriticalSection&& other ) = delete;


        /// <summary>
        /// Attempts to enter a critical section without blocking. If the 
        /// call is successful, the calling thread takes ownership of the 
        /// critical section
        /// </summary>
        /// <returns>
        /// If the critical section is successfully entered or the current 
        /// thread already owns the critical section, the return value is
        /// true. 
        /// 
        /// If another thread already owns the critical section, the 
        /// return value is false.
        /// </returns>
        bool TryEnter( ) const noexcept
        {
            return TryEnterCriticalSection( &criticalSection_ ) != 0;
        }

        /// <summary>
        /// Attempts to enter a critical section without blocking. If the 
        /// call is successful, the calling thread takes ownership of the 
        /// critical section
        /// </summary>
        /// <returns>
        /// If the critical section is successfully entered or the current 
        /// thread already owns the critical section, the return value is
        /// true. 
        /// 
        /// If another thread already owns the critical section, the 
        /// return value is false.
        /// </returns>
        bool try_lock( ) const noexcept
        {
            return TryEnter( );
        }

        /// <summary>
        /// Waits for ownership of the specified critical section object. The 
        /// function returns when the calling thread is granted ownership.
        /// </summary>
        /// <remarks>
        /// 
        /// </remarks>
        void Enter( ) const noexcept
        {
            EnterCriticalSection( &criticalSection_ );
        }

        /// <summary>
        /// Waits for ownership of the specified critical section object. The 
        /// function returns when the calling thread is granted ownership.
        /// </summary>
        void lock( ) const noexcept
        {
            Enter( );
        }

        /// <summary>
        /// Releases ownership of the specified critical section object.
        /// </summary>
        void Leave( ) const noexcept
        {
            LeaveCriticalSection( &criticalSection_ );
        }

        /// <summary>
        /// Releases ownership of the specified critical section object.
        /// </summary>
        void unlock( ) const noexcept
        {
            Leave( );
        }

        
        /// <summary>
        /// Sets the spin count for the specified critical section. Spinning 
        /// means that when a thread tries to acquire a critical section that 
        /// is locked, the thread enters a loop, checks to see if the lock is 
        /// released, and if the lock is not released, the thread goes to sleep.
        /// </summary>
        /// <param name="spinCount">The spin count for the critical section object.</param>
        /// <returns>The previous spin count for the critical section</returns>
        UInt32 SetSpinCount( UInt32 spinCount ) noexcept
        {
            return SetCriticalSectionSpinCount( &criticalSection_, spinCount );
        }
    };

    /// <summary>
    /// Flags that control the behavior of threads that enter a barrier
    /// </summary>
    enum class SynchronizationBarrierFlags : UInt32
    {
        None = 0,
        /// <summary>
        /// Specifies that the thread entering the barrier 
        /// should block immediately until the last thread 
        /// enters the barrier.
        /// </summary>
        BlockOnly = SYNCHRONIZATION_BARRIER_FLAGS_BLOCK_ONLY,

        /// <summary>
        /// Specifies that the thread entering the barrier 
        /// should spin until the last thread enters the 
        /// barrier, even if the spinning thread exceeds 
        /// the barrier's maximum spin count.
        /// </summary>
        SpinOnly = SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY,

        /// <summary>
        /// Specifies that the function can skip the work 
        /// required to ensure that it is safe to delete 
        /// the barrier, which can improve performance. 
        /// All threads that enter this barrier must specify 
        /// the flag; otherwise, the flag is ignored.
        /// </summary>
        NoDelete = SYNCHRONIZATION_BARRIER_FLAGS_NO_DELETE

    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( SynchronizationBarrierFlags, UInt32 );

    /// <summary>
    /// A synchronization barrier enables multiple threads to wait until 
    /// all threads have all reached a particular point of execution 
    /// before any thread continues. Synchronization barriers cannot be 
    /// shared across processes.
    /// </summary>
    class SynchronizationBarrier
    {
        mutable SYNCHRONIZATION_BARRIER synchronizationBarrier_;
    public:
        using Flags = SynchronizationBarrierFlags;

        explicit SynchronizationBarrier( UInt32 totalThreads, Int32 spinCount = -1 )
        {
            auto rc = InitializeSynchronizationBarrier( &synchronizationBarrier_, totalThreads, spinCount );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        ~SynchronizationBarrier( )
        {
            DeleteSynchronizationBarrier( &synchronizationBarrier_ );
        }


        SynchronizationBarrier( const SynchronizationBarrier& other ) = delete;
        SynchronizationBarrier( SynchronizationBarrier&& other ) = delete;
        SynchronizationBarrier& operator =( const SynchronizationBarrier& other ) = delete;
        SynchronizationBarrier& operator =( SynchronizationBarrier&& other ) = delete;


        /// <summary>
        /// Causes the calling thread to wait at a synchronization barrier 
        /// until the maximum number of threads have entered the barrier.
        /// </summary>
        /// <param name="flags">
        /// Flags that control the behavior of threads that enter this barrier.
        /// </param>
        /// <returns>
        /// true for the last thread to signal the barrier. Threads that 
        /// signal the barrier before the last thread signals it receive 
        /// a return value of false.
        /// </returns>
        bool Enter( Flags flags = Flags::None ) const
        {
            return EnterSynchronizationBarrier( &synchronizationBarrier_, static_cast<UInt32>( flags ) ) != 0;
        }
    };


    /// <summary>
    /// Slim reader/writer (SRW) locks enable the threads of 
    /// a single process to access shared resources; they are 
    /// optimized for speed and occupy very little memory. 
    /// Slim reader-writer locks cannot be shared across processes.
    /// </summary>
    class SlimReaderWriterLock
    {
        friend class ConditionVariable;
        mutable SRWLOCK lock_;
    public:
        SlimReaderWriterLock( ) noexcept
        {
            InitializeSRWLock( &lock_ );
        }

        SlimReaderWriterLock( const SlimReaderWriterLock& other ) = delete;
        SlimReaderWriterLock( SlimReaderWriterLock&& other ) = delete;
        SlimReaderWriterLock& operator =( const SlimReaderWriterLock& other ) = delete;
        SlimReaderWriterLock& operator =( SlimReaderWriterLock&& other ) = delete;

        /// <summary>
        /// Acquires a slim reader/writer (SRW) lock in exclusive mode.
        /// </summary>
        void AcquireExclusive( ) const
        {
            AcquireSRWLockExclusive( &lock_ );
        }

        /// <summary>
        /// Acquires a slim reader/writer (SRW) lock in exclusive mode.
        /// </summary>
        void lock( ) const
        {
            AcquireSRWLockExclusive( &lock_ );
        }

        /// <summary>
        /// Acquires a slim reader/writer (SRW) lock in shared mode.
        /// </summary>
        void AcquireShared( ) const
        {
            AcquireSRWLockShared( &lock_ );
        }

        /// <summary>
        /// Acquires a slim reader/writer (SRW) lock in shared mode.
        /// </summary>
        void lock_shared( ) const
        {
            AcquireShared( );
        }

        /// <summary>
        /// Attempts to acquire a slim reader/writer (SRW) lock in 
        /// exclusive mode. If the call is successful, the calling 
        /// thread takes ownership of the lock.
        /// </summary>
        /// <returns>If the lock is successfully acquired, the return value is true.</returns>
        bool TryAcquireExclusive( ) const
        {
            return TryAcquireSRWLockExclusive( &lock_ ) != 0;
        }

        /// <summary>
        /// Attempts to acquire a slim reader/writer (SRW) lock in 
        /// exclusive mode. If the call is successful, the calling 
        /// thread takes ownership of the lock.
        /// </summary>
        /// <returns>If the lock is successfully acquired, the return value is true.</returns>
        bool try_lock( ) const
        {
            return TryAcquireExclusive( );
        }

        /// <summary>
        /// Attempts to acquire a slim reader/writer (SRW) lock in 
        /// shared mode. If the call is successful, the calling thread 
        /// takes ownership of the lock.
        /// </summary>
        /// <returns>If the lock is successfully acquired, the return value is true.</returns>
        bool TryAcquireShared( ) const
        {
            return TryAcquireSRWLockShared( &lock_ ) != 0;
        }

        /// <summary>
        /// Attempts to acquire a slim reader/writer (SRW) lock in 
        /// shared mode. If the call is successful, the calling thread 
        /// takes ownership of the lock.
        /// </summary>
        /// <returns>If the lock is successfully acquired, the return value is true.</returns>
        bool try_lock_shared( ) const
        {
            return TryAcquireShared( );
        }


        /// <summary>
        /// Releases a slim reader/writer (SRW) lock that was acquired in exclusive mode.
        /// </summary>
        void ReleaseExclusive( ) const
        {
            ReleaseSRWLockExclusive( &lock_ );
        }

        /// <summary>
        /// Releases a slim reader/writer (SRW) lock that was acquired in exclusive mode.
        /// </summary>
        void unlock( ) const
        {
            ReleaseExclusive( );
        }

        /// <summary>
        /// Releases a slim reader/writer (SRW) lock that was acquired in shared mode.
        /// </summary>
        void ReleaseShared( ) const
        {
            ReleaseSRWLockShared( &lock_ );
        }

        /// <summary>
        /// Releases a slim reader/writer (SRW) lock that was acquired in shared mode.
        /// </summary>
        void unlock_shared( ) const
        {
            ReleaseShared( );
        }

    };


    /// <summary>
    /// Condition variables are synchronization primitives that enable 
    /// threads to wait until a particular condition occurs. Condition 
    /// variables are user-mode objects that cannot be shared across 
    /// processes.
    /// </summary>
    class ConditionVariable
    {
        mutable CONDITION_VARIABLE conditionVariable_;
    public:
        ConditionVariable( ) noexcept
        {
            InitializeConditionVariable( &conditionVariable_ );
        }

        ConditionVariable( const ConditionVariable& other ) = delete;
        ConditionVariable( ConditionVariable&& other ) = delete;
        ConditionVariable& operator =( const ConditionVariable& other ) = delete;
        ConditionVariable& operator =( ConditionVariable&& other ) = delete;

        /// <summary>
        /// Wake a single thread waiting on the specified condition variable.
        /// </summary>
        void Wake( ) const
        {
            WakeConditionVariable( (PCONDITION_VARIABLE)&conditionVariable_ );
        }

        /// <summary>
        /// Wake all threads waiting on the specified condition variable.
        /// </summary>
        void WakeAll( ) const
        {
            WakeAllConditionVariable( (PCONDITION_VARIABLE)&conditionVariable_ );
        }

        /// <summary>
        /// Sleeps on the specified condition variable and releases the specified critical section as an atomic operation.
        /// </summary>
        /// <param name="criticalSection">
        /// The critical section object. This critical section 
        /// must be entered exactly once by the caller at the time of the call.
        /// </param>
        /// <param name="timeoutInMillis">
        /// The time-out interval, in milliseconds. If the time-out 
        /// interval elapses, the function re-acquires the critical 
        /// section and returns zero. If dwMilliseconds is zero, the 
        /// function tests the states of the specified objects and 
        /// returns immediately. If dwMilliseconds is INFINITE, the 
        /// function's time-out interval never elapses.
        /// </param>
        /// <returns>
        /// If the function succeeds, the return value is true. 
        /// If function returns false to indicate that the time-out 
        /// interval has elapsed before another thread has attempted 
        /// to wake the sleeping thread.
        /// </returns>
        bool Sleep( const CriticalSection& criticalSection, DWORD timeoutInMillis = INFINITE ) const
        {
            auto rc = SleepConditionVariableCS( (PCONDITION_VARIABLE)&conditionVariable_, (PCRITICAL_SECTION)&criticalSection.criticalSection_, timeoutInMillis );
            if ( !rc )
            {
                auto err = GetLastError( );
                if ( err != ERROR_TIMEOUT )
                {
                    ThrowOSError( err );
                }
                return false;
            }
            else
            {
                return true;
            }
        }

        bool Sleep( const CriticalSection& criticalSection, const TimeSpan& timeout ) const
        {
            return Sleep( criticalSection, timeout ? static_cast<DWORD>( timeout.ToMilliseconds() ) : 0 );
        }


        bool Sleep( const SlimReaderWriterLock& slimReaderWriterLock, DWORD timeoutInMillis = INFINITE, bool sharedMode = false ) const
        {
            auto rc = SleepConditionVariableSRW( (PCONDITION_VARIABLE)&conditionVariable_, (PSRWLOCK)&slimReaderWriterLock.lock_, timeoutInMillis, sharedMode? CONDITION_VARIABLE_LOCKMODE_SHARED:0 );
            if ( !rc )
            {
                auto err = GetLastError( );
                if ( err != ERROR_TIMEOUT )
                {
                    ThrowOSError( err );
                }
                return false;
            }
            else
            {
                return true;
            }
        }

        bool Sleep( const SlimReaderWriterLock& slimReaderWriterLock, const TimeSpan& timeout, bool sharedMode = false ) const
        {
            return Sleep( slimReaderWriterLock, timeout ? static_cast<DWORD>( timeout.ToMilliseconds( ) ) : 0, sharedMode );
        }
    };

    /// <summary>
    /// Simple blocking fixed size queue.
    /// </summary>
    /// <remarks>
    /// Pop will return false when the queue is empty *and* closed.
    /// Push will return false when the queue is closed. If the producer
    /// was waiting for the queue, the item will *not* be placed in the 
    /// queue.
    /// </remarks>
    /// <typeparam name="T">The type of elements to put in the queue</typeparam>
    template<typename T, size_t maxQueueSize>
    class SimpleConcurrentQueue
    {
        ConditionVariable queueEmpty_;
        ConditionVariable queueFull_;
        CriticalSection criticalSection_;
        std::atomic<size_t> lastItemProduced_ = 0;
        std::atomic<size_t> queueSize_ = 0;
        std::atomic<size_t> startOffset_ = 0;
        std::atomic<bool> closed_ = false;

    public:
        static constexpr size_t MaxQueueSize = maxQueueSize;
        using Container = std::array<T, MaxQueueSize>;
    private:
        Container conatainer_;
    public:
        SimpleConcurrentQueue( )
            : conatainer_{}
        {
        }

        SimpleConcurrentQueue( const SimpleConcurrentQueue& other ) = delete;
        SimpleConcurrentQueue( SimpleConcurrentQueue&& other ) = delete;
        SimpleConcurrentQueue& operator = ( const SimpleConcurrentQueue& other ) = delete;
        SimpleConcurrentQueue& operator = ( SimpleConcurrentQueue&& other ) = delete;

        void Close( )
        {
            {
                std::unique_lock lock( criticalSection_ );
                closed_ = true;
            }
            queueEmpty_.WakeAll( );
            queueFull_.WakeAll( );
        }

        bool IsClosed() const noexcept
        {
            std::unique_lock lock(criticalSection_);
            return closed_;
        }

        bool Push( T&& item )
        {
            {
                std::unique_lock lock( criticalSection_ );
                while ( queueSize_ == MaxQueueSize && closed_ == false )
                {
                    queueFull_.Sleep( criticalSection_ );
                }
                if ( closed_ )
                {
                    return false;
                }
                auto containerOffset = ( startOffset_ + queueSize_ ) % MaxQueueSize;
                conatainer_[containerOffset] = std::move(item);
                queueSize_++;
            }
            queueEmpty_.Wake( );
            return true;
        }
        bool Push( const T& item )
        {
            {
                std::unique_lock lock( criticalSection_ );
                while ( queueSize_ == MaxQueueSize && closed_ == false )
                {
                    queueFull_.Sleep( criticalSection_ );
                }
                if ( closed_ )
                {
                    return false;
                }
                auto containerOffset = ( startOffset_ + queueSize_ ) % MaxQueueSize;
                conatainer_[containerOffset] = item;
                queueSize_++;
            }
            queueEmpty_.Wake( );
            return true;
        }
    private:
        void PopValue(T& value )
        {
            if constexpr ( std::is_move_assignable_v<T> )
            {
                value = std::move(conatainer_[ startOffset_ ]);
            }
            else
            {
                value = conatainer_[ startOffset_ ];
                conatainer_[ startOffset_ ] = {};
            }
            

            queueSize_--;
            startOffset_++;

            if ( startOffset_ == MaxQueueSize )
            {
                startOffset_ = 0;
            }
        }
    public:
        bool Pop( T& item )
        {
            bool result = false;
            {
                std::unique_lock lock( criticalSection_ );
                if ( closed_ == false )
                {
                    while ( queueSize_ == 0 && closed_ == false )
                    {
                        queueEmpty_.Sleep( criticalSection_ );
                    }
                }
                if ( queueSize_ )
                {
                    PopValue( item );
                    result = true;
                }
            }
            if ( result && closed_ == false )
            {
                queueFull_.Wake( );
            }
            return result;
        }
    };





    


    class WaitableHandle
    {
    public:
        
    private:
        HANDLE handle_;
    public:
        constexpr WaitableHandle( ) noexcept
            : handle_( 0 )
        {
        }
    protected:
        constexpr explicit WaitableHandle( HANDLE handle ) noexcept
            : handle_( handle )
        {
        }
    public:
        WaitableHandle( const WaitableHandle& other ) = delete;

        WaitableHandle( WaitableHandle&& other ) noexcept
            : handle_( other.handle_ )
        {
            other.handle_ = nullptr;
        }


        ~WaitableHandle( ) noexcept
        {
            Close( );
        }

        WaitableHandle& operator = ( const WaitableHandle& other ) = delete;

    protected:
        template<typename T>
            requires std::is_base_of_v< WaitableHandle, T>
        void TakeOwnership( T&& other )
        {
            if ( &other != this )
            {
                Close( );
                handle_ = other.handle_;
                other.handle_ = nullptr;
            }
        }
    public:
        constexpr operator bool( ) const noexcept
        {
            return handle_ != nullptr;
        }

        WaitableHandle& operator = ( WaitableHandle&& other ) noexcept
        {
            TakeOwnership( std::move( other ) );
            return *this;
        }


        void Close( ) noexcept
        {
            if ( handle_ )
            {
                CloseHandle( handle_ );
                handle_ = nullptr;
            }
        }

        constexpr HANDLE GetHandle( ) const noexcept
        {
            return handle_;
        }
        void SetHandle( HANDLE value ) noexcept
        {
            if ( handle_ != value )
            {
                Close( );
                handle_ = value;
            }
        }

        [[nodiscard]] HANDLE ReleaseHandle( ) noexcept
        {
            auto result = handle_;
            handle_ = nullptr;
            return result;
        }


        bool Wait( UInt32 timeoutInMillis = INFINITE ) const
        {
            auto rc = WaitForSingleObject( handle_, timeoutInMillis );
            if ( rc == WAIT_FAILED )
            {
                ThrowLastOSError( );
            }
            return rc == WAIT_TIMEOUT ? false : true;
        }
        bool Wait( const TimeSpan& timeout ) const
        {
            UInt32 timeoutInMillis = timeout ? static_cast<DWORD>( timeout.ToMilliseconds( ) ) : 0;
            return Wait( timeoutInMillis );
        }

        bool TryWait( ) const
        {
            return Wait( 0 );
        }


        void lock( ) const
        {
            Wait( );
        }
        bool try_lock( ) const
        {
            return Wait( 0 );
        }
    };

    enum class EventWaitHandleRights : DWORD
    {
        HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS,
        Modify = EVENT_MODIFY_STATE,
        FullControl = EVENT_ALL_ACCESS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( EventWaitHandleRights, DWORD );


    class EventWaitHandleAccessMask : public Security::AccessMaskT<EventWaitHandleAccessMask,EventWaitHandleRights>
    {
    public:
        using Base = Security::AccessMaskT<EventWaitHandleAccessMask, EventWaitHandleRights>;
        static constexpr const Security::GenericMapping Mapping{
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( EventWaitHandleRights::FullControl ) ) };

        constexpr EventWaitHandleAccessMask( ) noexcept
        {
        }
        constexpr explicit EventWaitHandleAccessMask( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }

        constexpr explicit EventWaitHandleAccessMask( EventWaitHandleRights rights ) noexcept
            : Base( rights )
        {
        }

        explicit EventWaitHandleAccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit EventWaitHandleAccessMask( ACCESS_MASK mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }

        explicit EventWaitHandleAccessMask( const EventWaitHandleAccessMask& mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask.Value(), genericMapping )
        {
        }
        explicit EventWaitHandleAccessMask( const EventWaitHandleAccessMask& mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }

        explicit EventWaitHandleAccessMask( EventWaitHandleRights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }
        explicit EventWaitHandleAccessMask( EventWaitHandleRights rights, const Security::GenericMapping& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }


        constexpr bool CanModify( ) const noexcept
        {
            return Check<EventWaitHandleRights::Modify>( );
        }
        constexpr void SetModify( bool value = true ) noexcept
        {
            SetBitFlag<EventWaitHandleRights::Modify>( value );
        }


    };



    class EventWaitHandle : public WaitableHandle
    {
    public:
        using Base = WaitableHandle;
    private:
        static HANDLE Create( LPSECURITY_ATTRIBUTES securityAttributes, bool manualReset, bool initialState, EventWaitHandleRights desiredAccess, LPCWSTR name )
        {
            DWORD flags = manualReset? CREATE_EVENT_MANUAL_RESET:0;
            if ( initialState )
            {
                flags |= CREATE_EVENT_INITIAL_SET;
            }

            auto result = CreateEventExW( securityAttributes, name, flags, static_cast<DWORD>( desiredAccess ) );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        static HANDLE Create( LPSECURITY_ATTRIBUTES securityAttributes, bool manualReset, bool initialState, EventWaitHandleRights desiredAccess, LPCSTR name )
        {
            DWORD flags = manualReset ? CREATE_EVENT_MANUAL_RESET : 0;
            if ( initialState )
            {
                flags |= CREATE_EVENT_INITIAL_SET;
            }
            auto result = CreateEventExA( securityAttributes, name, flags, static_cast<DWORD>( desiredAccess ) );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        static HANDLE Open( EventWaitHandleRights desiredAccess, bool inheritHandle, LPCWSTR name )
        {
            auto result = OpenEventW( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        static HANDLE Open( EventWaitHandleRights desiredAccess, bool inheritHandle, LPCSTR name )
        {
            auto result = OpenEventA( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        static HANDLE TryOpen( EventWaitHandleRights desiredAccess, bool inheritHandle, LPCWSTR name )
        {
            auto result = OpenEventW( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            return result;
        }
        static HANDLE TryOpen( EventWaitHandleRights desiredAccess, bool inheritHandle, LPCSTR name )
        {
            auto result = OpenEventA( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            return result;
        }


        explicit EventWaitHandle( HANDLE handle ) noexcept
            : Base( handle )
        {
        }
    public:
        constexpr EventWaitHandle( ) noexcept
            : Base( )
        {
        }

        explicit EventWaitHandle( bool manualReset, bool initialState = false, EventWaitHandleRights desiredAccess = EventWaitHandleRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, manualReset, initialState, desiredAccess, static_cast<LPCWSTR>( nullptr ) ) )
        {
        }

        explicit EventWaitHandle( LPCWSTR name, bool manualReset = true, bool initialState = false, EventWaitHandleRights desiredAccess = EventWaitHandleRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, manualReset, initialState, desiredAccess, name ) )
        {
        }
        explicit EventWaitHandle( LPCSTR name, bool manualReset = true, bool initialState = false, EventWaitHandleRights desiredAccess = EventWaitHandleRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, manualReset, initialState, desiredAccess, name ) )
        {
        }
        explicit EventWaitHandle( const WideString& name, bool manualReset = true, bool initialState = false, EventWaitHandleRights desiredAccess = EventWaitHandleRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, manualReset, initialState, desiredAccess, name.empty()? static_cast<LPCWSTR>(nullptr):name.c_str() ) )
        {
        }
        explicit EventWaitHandle( const AnsiString& name, bool manualReset = true, bool initialState = false, EventWaitHandleRights desiredAccess = EventWaitHandleRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, manualReset, initialState, desiredAccess, name.empty( ) ? static_cast<LPCSTR>( nullptr ) : name.c_str( ) ) )
        {
        }

        static EventWaitHandle New( bool manualReset = true, bool initialState = false, EventWaitHandleRights desiredAccess = EventWaitHandleRights::FullControl )
        {
            auto handle = Create( nullptr, manualReset, initialState, desiredAccess,static_cast<LPCWSTR>( nullptr ) );
            return EventWaitHandle( handle );
        }

        static EventWaitHandle OpenExisting( LPCWSTR name, EventWaitHandleRights desiredAccess = EventWaitHandleRights::Synchronize | EventWaitHandleRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name );
            return EventWaitHandle( handle );
        }
        static EventWaitHandle OpenExisting( LPCSTR name, EventWaitHandleRights desiredAccess = EventWaitHandleRights::Synchronize | EventWaitHandleRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name );
            return EventWaitHandle( handle );
        }
        static EventWaitHandle OpenExisting( const WideString& name, EventWaitHandleRights desiredAccess = EventWaitHandleRights::Synchronize | EventWaitHandleRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name.c_str() );
            return EventWaitHandle( handle );
        }
        static EventWaitHandle OpenExisting( const AnsiString& name, EventWaitHandleRights desiredAccess = EventWaitHandleRights::Synchronize | EventWaitHandleRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name.c_str( ) );
            return EventWaitHandle( handle );
        }

        static EventWaitHandle TryOpenExisting( LPCWSTR name, EventWaitHandleRights desiredAccess = EventWaitHandleRights::Synchronize | EventWaitHandleRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name );
            return EventWaitHandle( handle );
        }
        static EventWaitHandle TryOpenExisting( LPCSTR name, EventWaitHandleRights desiredAccess = EventWaitHandleRights::Synchronize | EventWaitHandleRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name );
            return EventWaitHandle( handle );
        }
        static EventWaitHandle TryOpenExisting( const WideString& name, EventWaitHandleRights desiredAccess = EventWaitHandleRights::Synchronize | EventWaitHandleRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name.c_str( ) );
            return EventWaitHandle( handle );
        }
        static EventWaitHandle TryOpenExisting( const AnsiString& name, EventWaitHandleRights desiredAccess = EventWaitHandleRights::Synchronize | EventWaitHandleRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name.c_str( ) );
            return EventWaitHandle( handle );
        }


        void SetEvent( ) const
        {
            auto rc = ::SetEvent( GetHandle( ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        void PulseEvent( ) const
        {
            auto rc = ::PulseEvent( GetHandle( ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        void Signal( ) const
        {
            SetEvent( );
        }


        void ResetEvent( ) const
        {
            auto rc = ::ResetEvent( GetHandle( ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
            
        void Reset( ) const
        {
            ResetEvent( );
        }

        void unlock( ) const
        {
            ResetEvent( );
        }

    };

    

    enum class MutexRights : DWORD
    {
        HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS,
        Modify = MUTEX_MODIFY_STATE,
        FullControl = MUTEX_ALL_ACCESS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( MutexRights, DWORD );

    class MutexAccessMask : public Security::AccessMaskT<MutexAccessMask, MutexRights>
    {
    public:
        using Base = Security::AccessMaskT<MutexAccessMask, MutexRights>;
        static constexpr const Security::GenericMapping Mapping{
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( MutexRights::FullControl ) ) };

        constexpr MutexAccessMask( ) noexcept
        {
        }
        constexpr explicit MutexAccessMask( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }

        constexpr explicit MutexAccessMask( MutexRights rights ) noexcept
            : Base( rights )
        {
        }

        explicit MutexAccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit MutexAccessMask( ACCESS_MASK mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }

        explicit MutexAccessMask( const MutexAccessMask& mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }
        explicit MutexAccessMask( const MutexAccessMask& mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }

        explicit MutexAccessMask( MutexRights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }
        explicit MutexAccessMask( MutexRights rights, const Security::GenericMapping& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }


        constexpr bool CanModify( ) const noexcept
        {
            return Check<MutexRights::Modify>( );
        }
        constexpr void SetModify( bool value = true ) noexcept
        {
            SetBitFlag<MutexRights::Modify>( value );
        }


    };


    class Mutex : public WaitableHandle
    {
    public:
        using Base = WaitableHandle;
    private:
    private:
        static HANDLE Create( LPSECURITY_ATTRIBUTES securityAttributes, bool initiallyOwned, MutexRights desiredAccess, LPCWSTR name )
        {
            auto result = CreateMutexExW( securityAttributes, name, initiallyOwned ? CREATE_MUTEX_INITIAL_OWNER : 0, static_cast<DWORD>( desiredAccess ) );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        static HANDLE Create( LPSECURITY_ATTRIBUTES securityAttributes, bool initiallyOwned, MutexRights desiredAccess, LPCSTR name )
        {
            auto result = CreateMutexExA( securityAttributes, name, initiallyOwned ? CREATE_MUTEX_INITIAL_OWNER : 0, static_cast<DWORD>( desiredAccess ) );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        static HANDLE Open( MutexRights desiredAccess, bool inheritHandle, LPCWSTR name )
        {
            auto result = OpenMutexW( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        static HANDLE Open( MutexRights desiredAccess, bool inheritHandle, LPCSTR name )
        {
            auto result = OpenMutexA( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        static HANDLE TryOpen( MutexRights desiredAccess, bool inheritHandle, LPCWSTR name )
        {
            auto result = OpenMutexW( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            return result;
        }
        static HANDLE TryOpen( MutexRights desiredAccess, bool inheritHandle, LPCSTR name )
        {
            auto result = OpenMutexA( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            return result;
        }

        explicit Mutex( HANDLE handle ) noexcept
            : Base( handle )
        {
        }
    public:
        constexpr Mutex( ) noexcept
            : Base( )
        {
        }

        explicit Mutex( bool initiallyOwned, MutexRights desiredAccess = MutexRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, initiallyOwned, desiredAccess, static_cast<LPCWSTR>( nullptr ) ) )
        {
        }

        explicit Mutex( LPCWSTR name, bool initiallyOwned = true, MutexRights desiredAccess = MutexRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, initiallyOwned, desiredAccess, name ) )
        {
        }
        explicit Mutex( LPCSTR name, bool initiallyOwned = true, MutexRights desiredAccess = MutexRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, initiallyOwned, desiredAccess, name ) )
        {
        }
        explicit Mutex( const WideString& name, bool initiallyOwned = true, MutexRights desiredAccess = MutexRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, initiallyOwned, desiredAccess, name.empty( ) ? static_cast<LPCWSTR>( nullptr ) : name.c_str( ) ) )
        {
        }
        explicit Mutex( const AnsiString& name, bool initiallyOwned = true, MutexRights desiredAccess = MutexRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, initiallyOwned, desiredAccess, name.empty( ) ? static_cast<LPCSTR>( nullptr ) : name.c_str( ) ) )
        {
        }

        static Mutex New( bool initiallyOwned = false, MutexRights desiredAccess = MutexRights::FullControl )
        {
            auto handle = Create( nullptr, initiallyOwned, desiredAccess, static_cast<LPCWSTR>( nullptr ) );
            return Mutex( handle );
        }

        static Mutex OpenExisting( LPCWSTR name, MutexRights desiredAccess = MutexRights::Synchronize | MutexRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name );
            return Mutex( handle );
        }
        static Mutex OpenExisting( LPCSTR name, MutexRights desiredAccess = MutexRights::Synchronize | MutexRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name );
            return Mutex( handle );
        }
        static Mutex OpenExisting( const WideString& name, MutexRights desiredAccess = MutexRights::Synchronize | MutexRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name.c_str( ) );
            return Mutex( handle );
        }
        static Mutex OpenExisting( const AnsiString& name, MutexRights desiredAccess = MutexRights::Synchronize | MutexRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name.c_str( ) );
            return Mutex( handle );
        }

        static Mutex TryOpenExisting( LPCWSTR name, MutexRights desiredAccess = MutexRights::Synchronize | MutexRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name );
            return Mutex( handle );
        }
        static Mutex TryOpenExisting( LPCSTR name, MutexRights desiredAccess = MutexRights::Synchronize | MutexRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name );
            return Mutex( handle );
        }
        static Mutex TryOpenExisting( const WideString& name, MutexRights desiredAccess = MutexRights::Synchronize | MutexRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name.c_str( ) );
            return Mutex( handle );
        }
        static Mutex TryOpenExisting( const AnsiString& name, MutexRights desiredAccess = MutexRights::Synchronize | MutexRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name.c_str( ) );
            return Mutex( handle );
        }

        void ReleaseMutex( ) const
        {
            auto rc = ::ReleaseMutex( GetHandle( ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        void Release( ) const
        {
            ReleaseMutex( );
        }

        void unlock( ) const
        {
            ReleaseMutex( );
        }
    };


    enum class SemaphoreRights : DWORD
    {
        HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS,
        Modify = SEMAPHORE_MODIFY_STATE,
        FullControl = SEMAPHORE_ALL_ACCESS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( SemaphoreRights, DWORD );

    class SemaphoreAccessMask : public Security::AccessMaskT<SemaphoreAccessMask, SemaphoreRights>
    {
    public:
        using Base = Security::AccessMaskT<SemaphoreAccessMask, SemaphoreRights>;
        static constexpr const Security::GenericMapping Mapping{
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( SemaphoreRights::FullControl ) ) };

        constexpr SemaphoreAccessMask( ) noexcept
        {
        }
        constexpr explicit SemaphoreAccessMask( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }

        constexpr explicit SemaphoreAccessMask( SemaphoreRights rights ) noexcept
            : Base( rights )
        {
        }

        explicit SemaphoreAccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit SemaphoreAccessMask( ACCESS_MASK mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }

        explicit SemaphoreAccessMask( const SemaphoreAccessMask& mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }
        explicit SemaphoreAccessMask( const SemaphoreAccessMask& mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }

        explicit SemaphoreAccessMask( SemaphoreRights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }
        explicit SemaphoreAccessMask( SemaphoreRights rights, const Security::GenericMapping& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }


        constexpr bool CanModify( ) const noexcept
        {
            return Check<SemaphoreRights::Modify>( );
        }
        constexpr void SetModify( bool value = true ) noexcept
        {
            SetBitFlag<SemaphoreRights::Modify>( value );
        }


    };
        

    class Semaphore : public WaitableHandle
    {
    public:
        using Base = WaitableHandle;
        static constexpr long MaximumCount = 0x7FFFFFFF;
    private:
        static HANDLE Create( LPSECURITY_ATTRIBUTES securityAttributes, long initialCount, long maximumCount, SemaphoreRights desiredAccess, LPCWSTR name )
        {
            auto result = CreateSemaphoreExW( securityAttributes, initialCount, maximumCount, name, 0, static_cast<DWORD>( desiredAccess ) );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        static HANDLE Create( LPSECURITY_ATTRIBUTES securityAttributes, long initialCount, long maximumCount, SemaphoreRights desiredAccess, LPCSTR name )
        {
            auto result = CreateSemaphoreExA( securityAttributes, initialCount, maximumCount, name, 0, static_cast<DWORD>( desiredAccess ) );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        static HANDLE Open( SemaphoreRights desiredAccess, bool inheritHandle, LPCWSTR name )
        {
            auto result = OpenSemaphoreW( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        static HANDLE Open( SemaphoreRights desiredAccess, bool inheritHandle, LPCSTR name )
        {
            auto result = OpenSemaphoreA( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        static HANDLE TryOpen( SemaphoreRights desiredAccess, bool inheritHandle, LPCWSTR name )
        {
            auto result = OpenSemaphoreW( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            return result;
        }
        static HANDLE TryOpen( SemaphoreRights desiredAccess, bool inheritHandle, LPCSTR name )
        {
            auto result = OpenSemaphoreA( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            return result;
        }

        explicit Semaphore( HANDLE handle ) noexcept
            : Base( handle )
        {
        }
    public:
        constexpr Semaphore( ) noexcept
            : Base( )
        {
        }

        explicit Semaphore( long initialCount, long maximumCount = MaximumCount, SemaphoreRights desiredAccess = SemaphoreRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, initialCount, maximumCount, desiredAccess, static_cast<LPCWSTR>( nullptr ) ) )
        {
        }

        explicit Semaphore( LPCWSTR name, long initialCount, long maximumCount = MaximumCount, SemaphoreRights desiredAccess = SemaphoreRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, initialCount, maximumCount, desiredAccess, name ) )
        {
        }
        explicit Semaphore( LPCSTR name, long initialCount, long maximumCount = MaximumCount, SemaphoreRights desiredAccess = SemaphoreRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, initialCount, maximumCount, desiredAccess, name ) )
        {
        }
        explicit Semaphore( const WideString& name, long initialCount, long maximumCount = MaximumCount, SemaphoreRights desiredAccess = SemaphoreRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, initialCount, maximumCount, desiredAccess, name.empty( ) ? static_cast<LPCWSTR>( nullptr ) : name.c_str( ) ) )
        {
        }
        explicit Semaphore( const AnsiString& name, long initialCount, long maximumCount = MaximumCount, SemaphoreRights desiredAccess = SemaphoreRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, initialCount, maximumCount, desiredAccess, name.empty( ) ? static_cast<LPCSTR>( nullptr ) : name.c_str( ) ) )
        {
        }

        static Semaphore New( long initialCount = 0, long maximumCount = MaximumCount, SemaphoreRights desiredAccess = SemaphoreRights::FullControl )
        {
            auto handle = Create( nullptr, initialCount, maximumCount, desiredAccess, static_cast<LPCWSTR>( nullptr ) );
            return Semaphore( handle );
        }

        static Semaphore OpenExisting( LPCWSTR name, SemaphoreRights desiredAccess = SemaphoreRights::Synchronize | SemaphoreRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name );
            return Semaphore( handle );
        }
        static Semaphore OpenExisting( LPCSTR name, SemaphoreRights desiredAccess = SemaphoreRights::Synchronize | SemaphoreRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name );
            return Semaphore( handle );
        }
        static Semaphore OpenExisting( const WideString& name, SemaphoreRights desiredAccess = SemaphoreRights::Synchronize | SemaphoreRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name.c_str( ) );
            return Semaphore( handle );
        }
        static Semaphore OpenExisting( const AnsiString& name, SemaphoreRights desiredAccess = SemaphoreRights::Synchronize | SemaphoreRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name.c_str( ) );
            return Semaphore( handle );
        }

        static Semaphore TryOpenExisting( LPCWSTR name, SemaphoreRights desiredAccess = SemaphoreRights::Synchronize | SemaphoreRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name );
            return Semaphore( handle );
        }
        static Semaphore TryOpenExisting( LPCSTR name, SemaphoreRights desiredAccess = SemaphoreRights::Synchronize | SemaphoreRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name );
            return Semaphore( handle );
        }
        static Semaphore TryOpenExisting( const WideString& name, SemaphoreRights desiredAccess = SemaphoreRights::Synchronize | SemaphoreRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name.c_str( ) );
            return Semaphore( handle );
        }
        static Semaphore TryOpenExisting( const AnsiString& name, SemaphoreRights desiredAccess = SemaphoreRights::Synchronize | SemaphoreRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name.c_str( ) );
            return Semaphore( handle );
        }


        long ReleaseSemaphore( long releaseCount = 1 ) const
        {
            long previousReleaseCount = 0;
            auto rc = ::ReleaseSemaphore( GetHandle( ), releaseCount, &previousReleaseCount );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return previousReleaseCount;
        }
        long Release( long releaseCount = 1 ) const
        {
            return ReleaseSemaphore( releaseCount );
        }
        long Signal( long releaseCount = 1 ) const
        {
            return ReleaseSemaphore( releaseCount );
        }

        void unlock( ) const
        {
            ReleaseSemaphore( 1 );
        }
    };

    enum class WaitableTimerRights : DWORD
    {
        HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS,
        Query = TIMER_QUERY_STATE,
        Modify = TIMER_MODIFY_STATE,
        FullControl = TIMER_ALL_ACCESS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( WaitableTimerRights, DWORD );


    class WaitableTimerAccessMask : public Security::AccessMaskT<WaitableTimerAccessMask,WaitableTimerRights>
    {
    public:
        using Base = Security::AccessMaskT<WaitableTimerAccessMask, WaitableTimerRights>;
        static constexpr const Security::GenericMapping Mapping{
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( 0 ),
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( WaitableTimerRights::FullControl ) ) };

        constexpr WaitableTimerAccessMask( ) noexcept
        {
        }
        constexpr explicit WaitableTimerAccessMask( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }

        constexpr explicit WaitableTimerAccessMask( WaitableTimerRights rights ) noexcept
            : Base( rights )
        {
        }

        explicit WaitableTimerAccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit WaitableTimerAccessMask( ACCESS_MASK mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }

        explicit WaitableTimerAccessMask( const WaitableTimerAccessMask& mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask.Value(), genericMapping )
        {
        }
        explicit WaitableTimerAccessMask( const WaitableTimerAccessMask& mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }

        explicit WaitableTimerAccessMask( WaitableTimerRights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }
        explicit WaitableTimerAccessMask( WaitableTimerRights rights, const Security::GenericMapping& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }

        constexpr bool CanQuery( ) const noexcept
        {
            return Check<WaitableTimerRights::Query>( );
        }
        constexpr void SetQuery( bool value = true ) noexcept
        {
            SetBitFlag<WaitableTimerRights::Query>( value );
        }

        constexpr bool CanModify( ) const noexcept
        {
            return Check<WaitableTimerRights::Modify>( );
        }
        constexpr void SetModify( bool value = true ) noexcept
        {
            SetBitFlag<WaitableTimerRights::Modify>( value );
        }


    };

    class WaitableTimer : public WaitableHandle
    {
    public:
        using Base = WaitableHandle;
    private:
        static HANDLE Create( LPSECURITY_ATTRIBUTES securityAttributes, bool manualReset, bool highResolution, WaitableTimerRights desiredAccess, LPCWSTR name )
        {
            DWORD flags = manualReset ? CREATE_WAITABLE_TIMER_MANUAL_RESET : 0;
            if ( highResolution )
            {
                flags |= CREATE_WAITABLE_TIMER_HIGH_RESOLUTION;
            }

            auto result = CreateWaitableTimerExW( securityAttributes, name, flags, static_cast<DWORD>( desiredAccess ) );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        static HANDLE Create( LPSECURITY_ATTRIBUTES securityAttributes, bool manualReset, bool highResolution, WaitableTimerRights desiredAccess, LPCSTR name )
        {
            DWORD flags = manualReset ? CREATE_WAITABLE_TIMER_MANUAL_RESET : 0;
            if ( highResolution )
            {
                flags |= CREATE_WAITABLE_TIMER_HIGH_RESOLUTION;
            }

            auto result = CreateWaitableTimerExA( securityAttributes, name, flags, static_cast<DWORD>( desiredAccess ) );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        static HANDLE Open( WaitableTimerRights desiredAccess, bool inheritHandle, LPCWSTR name )
        {
            auto result = OpenWaitableTimerW( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        static HANDLE Open( WaitableTimerRights desiredAccess, bool inheritHandle, LPCSTR name )
        {
            auto result = OpenWaitableTimerA( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        static HANDLE TryOpen( WaitableTimerRights desiredAccess, bool inheritHandle, LPCWSTR name )
        {
            auto result = OpenWaitableTimerW( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            return result;
        }
        static HANDLE TryOpen( WaitableTimerRights desiredAccess, bool inheritHandle, LPCSTR name )
        {
            auto result = OpenWaitableTimerA( static_cast<DWORD>( desiredAccess ), inheritHandle, name );
            return result;
        }

        explicit WaitableTimer( HANDLE handle ) noexcept
            : Base( handle )
        {
        }
    public:
        constexpr WaitableTimer( ) noexcept
            : Base( )
        {
        }

        explicit WaitableTimer( bool manualReset, bool highResolution = false, WaitableTimerRights desiredAccess = WaitableTimerRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, manualReset, highResolution, desiredAccess, static_cast<LPCWSTR>( nullptr ) ) )
        {
        }

        explicit WaitableTimer( bool manualReset, bool highResolution, const DateTime& dueTime, const TimeSpan& interval = TimeSpan( ), WaitableTimerRights desiredAccess = WaitableTimerRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, manualReset, highResolution, desiredAccess, static_cast<LPCWSTR>( nullptr ) ) )
        {
            SetTimer( dueTime, interval );
        }

        explicit WaitableTimer( bool manualReset, bool highResolution, const TimeSpan& dueTime, const TimeSpan& interval = TimeSpan( ), WaitableTimerRights desiredAccess = WaitableTimerRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, manualReset, highResolution, desiredAccess, static_cast<LPCWSTR>( nullptr ) ) )
        {
            SetTimer( dueTime, interval );
        }


        explicit WaitableTimer( LPCWSTR name, bool manualReset = true, bool highResolution = false, WaitableTimerRights desiredAccess = WaitableTimerRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, manualReset, highResolution, desiredAccess, name ) )
        {
        }
        explicit WaitableTimer( LPCSTR name, bool manualReset = true, bool highResolution = false, WaitableTimerRights desiredAccess = WaitableTimerRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, manualReset, highResolution, desiredAccess, name ) )
        {
        }
        explicit WaitableTimer( const WideString& name, bool manualReset = true, bool highResolution = false, WaitableTimerRights desiredAccess = WaitableTimerRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, manualReset, highResolution, desiredAccess, name.empty( ) ? static_cast<LPCWSTR>( nullptr ) : name.c_str( ) ) )
        {
        }
        explicit WaitableTimer( const AnsiString& name, bool manualReset = true, bool highResolution = false, WaitableTimerRights desiredAccess = WaitableTimerRights::FullControl, LPSECURITY_ATTRIBUTES securityAttributes = nullptr )
            : Base( Create( securityAttributes, manualReset, highResolution, desiredAccess, name.empty( ) ? static_cast<LPCSTR>( nullptr ) : name.c_str( ) ) )
        {
        }

        static WaitableTimer New( bool manualReset = true, bool highResolution = false, WaitableTimerRights desiredAccess = WaitableTimerRights::FullControl )
        {
            auto handle = Create( nullptr, manualReset, highResolution, desiredAccess, static_cast<LPCWSTR>( nullptr ) );
            return WaitableTimer( handle );
        }

        static WaitableTimer OpenExisting( LPCWSTR name, WaitableTimerRights desiredAccess = WaitableTimerRights::Synchronize | WaitableTimerRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name );
            return WaitableTimer( handle );
        }
        static WaitableTimer OpenExisting( LPCSTR name, WaitableTimerRights desiredAccess = WaitableTimerRights::Synchronize | WaitableTimerRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name );
            return WaitableTimer( handle );
        }
        static WaitableTimer OpenExisting( const WideString& name, WaitableTimerRights desiredAccess = WaitableTimerRights::Synchronize | WaitableTimerRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name.c_str( ) );
            return WaitableTimer( handle );
        }
        static WaitableTimer OpenExisting( const AnsiString& name, WaitableTimerRights desiredAccess = WaitableTimerRights::Synchronize | WaitableTimerRights::Modify, bool inheritHandle = false )
        {
            auto handle = Open( desiredAccess, inheritHandle, name.c_str( ) );
            return WaitableTimer( handle );
        }

        static WaitableTimer TryOpenExisting( LPCWSTR name, WaitableTimerRights desiredAccess = WaitableTimerRights::Synchronize | WaitableTimerRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name );
            return WaitableTimer( handle );
        }
        static WaitableTimer TryOpenExisting( LPCSTR name, WaitableTimerRights desiredAccess = WaitableTimerRights::Synchronize | WaitableTimerRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name );
            return WaitableTimer( handle );
        }
        static WaitableTimer TryOpenExisting( const WideString& name, WaitableTimerRights desiredAccess = WaitableTimerRights::Synchronize | WaitableTimerRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name.c_str( ) );
            return WaitableTimer( handle );
        }
        static WaitableTimer TryOpenExisting( const AnsiString& name, WaitableTimerRights desiredAccess = WaitableTimerRights::Synchronize | WaitableTimerRights::Modify, bool inheritHandle = false )
        {
            auto handle = TryOpen( desiredAccess, inheritHandle, name.c_str( ) );
            return WaitableTimer( handle );
        }

        void SetTimer( LARGE_INTEGER dueTime, DWORD interval, PTIMERAPCROUTINE completionRoutine, void* argToCompletionRoutine, bool resumeSystemIfSuspended ) const
        {
            auto rc = SetWaitableTimer( GetHandle( ), &dueTime, interval, completionRoutine, argToCompletionRoutine, resumeSystemIfSuspended );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        void SetTimer( LARGE_INTEGER dueTime, DWORD interval, bool resumeSystemIfSuspended = false ) const
        {
            SetTimer( dueTime, interval, nullptr, nullptr, resumeSystemIfSuspended );
        }

        void SetTimer( const DateTime& dueTime, const TimeSpan& interval, PTIMERAPCROUTINE completionRoutine, void* argToCompletionRoutine, bool resumeSystemIfSuspended ) const
        {
            LARGE_INTEGER fileTime;
            fileTime.QuadPart =  dueTime.ToFileTime( );
            DWORD period = interval ? static_cast<DWORD>( interval.ToMilliseconds( ) ) : 0;
            SetTimer( fileTime, period, completionRoutine, argToCompletionRoutine, resumeSystemIfSuspended );
        }

        void SetTimer( const TimeSpan& dueTime, const TimeSpan& interval, PTIMERAPCROUTINE completionRoutine, void* argToCompletionRoutine, bool resumeSystemIfSuspended ) const
        {
            LARGE_INTEGER fileTime;
            fileTime.QuadPart = -dueTime.Ticks( );
            DWORD period = interval ? static_cast<DWORD>( interval.ToMilliseconds( ) ) : 0;
            SetTimer( fileTime, period, completionRoutine, argToCompletionRoutine, resumeSystemIfSuspended );
        }

        void SetTimer( const DateTime& dueTime, const TimeSpan& interval = TimeSpan( ), bool resumeSystemIfSuspended = false ) const
        {
            SetTimer( dueTime, interval, nullptr, nullptr, resumeSystemIfSuspended );
        }

        void SetTimer( const TimeSpan& dueTime, const TimeSpan& interval = TimeSpan( ), bool resumeSystemIfSuspended = false ) const
        {
            SetTimer( dueTime, interval, nullptr, nullptr, resumeSystemIfSuspended );
        }

        void Cancel( ) const
        {
            auto rc = CancelWaitableTimer( GetHandle( ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
    };


    enum class TimerQueueTimerFlags : DWORD
    {
        /// <summary>
        /// By default, the callback function is queued to a non-I/O worker thread.
        /// </summary>
        Default = WT_EXECUTEDEFAULT,

        /// <summary>
        /// The callback function is invoked by the timer thread itself. 
        /// This flag should be used only for short tasks or it could 
        /// affect other timer operations.
        /// <p>
        /// The callback function is queued as an APC. It should not 
        /// perform alertable wait operations.
        /// </p>
        /// </summary>
        ExecuteInTimerThread = WT_EXECUTEINTIMERTHREAD,

        /// <summary>
        /// The callback function is queued to a thread that never 
        /// terminates. It does not guarantee that the same thread 
        /// is used each time. This flag should be used only for 
        /// short tasks or it could affect other timer operations.
        /// 
        /// This flag must be set if the thread calls functions that 
        /// use APCs.
        /// </summary>
        ExecuteInPersistentThread = WT_EXECUTEINPERSISTENTTHREAD,

        /// <summary>
        /// The callback function can perform a long wait. This flag 
        /// helps the system to decide if it should create a new thread.
        /// </summary>
        ExecuteLongFunction = WT_EXECUTELONGFUNCTION,

        /// <summary>
        /// The timer will be set to the signaled state only once. 
        /// If this flag is set, the Period parameter must be zero.
        /// </summary>
        ExecuteOnlyOnce = WT_EXECUTEONLYONCE,

        /// <summary>
        /// Callback functions will use the current access token, 
        /// whether it is a process or impersonation token. If this 
        /// flag is not specified, callback functions execute only 
        /// with the process token.
        /// </summary>
        TransferImpersonation = WT_TRANSFER_IMPERSONATION

    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TimerQueueTimerFlags, DWORD );

    class TimerQueue;
    class TimerQueueTimer
    {
        friend class TimerQueue;

        class Args
        {
        public:
            virtual ~Args( )
            {
            }
        };

        template<typename ...Types>
        class ArgsTuple : public Args, public std::tuple<Types...>
        {
        public:
            ArgsTuple( Types&& ...args )
                : std::tuple<Types...>( std::forward<Types>( args )... )
            { }
        };


        HANDLE queueHanedle_;
        HANDLE handle_;
        std::unique_ptr<Args> args_;
        explicit TimerQueueTimer( HANDLE queueHanedle, HANDLE handle, std::unique_ptr<Args>&& args )
            : queueHanedle_( queueHanedle ), handle_( handle ), args_( std::move( args ) )
        {
        }
    public:
        TimerQueueTimer( )
            : queueHanedle_( nullptr ), handle_( nullptr )
        {
        }

        TimerQueueTimer( const TimerQueueTimer& other ) = delete;
        TimerQueueTimer( TimerQueueTimer&& other ) noexcept
            : queueHanedle_( other.queueHanedle_ ), handle_( other.handle_ ), args_( std::move( other.args_ ) )
        {
            other.queueHanedle_ = nullptr;
            other.handle_ = nullptr;
        }


        ~TimerQueueTimer( )
        {
            Close( );
        }

        bool Close( bool wait = true )
        {
            if ( queueHanedle_ && handle_ )
            {
                auto rc = DeleteTimerQueueTimer( queueHanedle_, handle_, wait? INVALID_HANDLE_VALUE : nullptr );
                if ( !rc )
                {
                    auto error = GetLastError( );
                    if ( error != ERROR_IO_PENDING )
                    {
                        ThrowOSError( error );
                    }
                }
                queueHanedle_ = nullptr; 
                handle_ = nullptr;
                return true;
            }
            else
            {
                return false;
            }
        }

        void SetTimer(ULONG dueTimeInMillis, ULONG periodInMillis )
        {
            if ( queueHanedle_ && handle_ )
            {
                auto rc = ChangeTimerQueueTimer( queueHanedle_, handle_, dueTimeInMillis, periodInMillis );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
            else
            {
                ThrowNullReferenceException( L"Invalid TimerQueueTimer" );
            }
        }

        void SetTimer( const DateTime& dueTime, const TimeSpan& period )
        {
            ULONG dueTimeInMillis = 0; 
            ULONG periodInMillis = 0;
            if ( dueTime )
            {
                auto when = dueTime - DateTime::UtcNow( );
                dueTimeInMillis = static_cast<ULONG>( when.TotalMilliseconds( ) );
            }
            if ( period )
            {
                periodInMillis = static_cast<ULONG>( period.TotalMilliseconds( ) );
            }
            SetTimer( dueTimeInMillis, periodInMillis );
        }



        TimerQueueTimer& operator = ( const TimerQueueTimer& other ) = delete;
        TimerQueueTimer& operator = ( TimerQueueTimer&& other ) noexcept
        {
            if ( &other != this )
            {
                std::swap(queueHanedle_, other.queueHanedle_ );
                std::swap( handle_, other.handle_ );
                std::swap( args_, other.args_ );
            }
            return *this;
        }
    };

    class TimerQueue
    {
        HANDLE handle_;
        explicit TimerQueue( HANDLE handle )
            : handle_( handle )
        {
        }
    public:
        TimerQueue( )
            : handle_( nullptr )
        {
        }

        TimerQueue( const TimerQueue& other ) = delete;
        TimerQueue( TimerQueue&& other ) noexcept
            : handle_( other.handle_ )
        {
            other.handle_ = nullptr;
        }


        ~TimerQueue( )
        {
            if ( handle_ )
            {
                DeleteTimerQueueEx( handle_, INVALID_HANDLE_VALUE );
            }
        }

        static TimerQueue Create( )
        {
            auto handle = CreateTimerQueue( );
            if ( !handle )
            {
                ThrowLastOSError( );
            }
            return TimerQueue( handle );
        }


        TimerQueue& operator = ( const TimerQueue& other ) = delete;
        TimerQueue& operator = ( TimerQueue&& other ) noexcept
        {
            if ( handle_ != other.handle_ )
            {
                std::swap( handle_, other.handle_ );
            }
            return *this;
        }

        HANDLE Value( )
        {
            if ( handle_ )
            {
                return handle_;
            }
            else
            {
                auto handle = CreateTimerQueue( );
                if ( !handle )
                {
                    ThrowLastOSError( );
                }
                handle_ = handle;
                return handle;
            }
        }


        bool Close( bool waitForAll = true )
        {
            if ( handle_ )
            {
                auto rc = DeleteTimerQueueEx( handle_, waitForAll ? INVALID_HANDLE_VALUE : nullptr );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                handle_ = nullptr;
                return true;
            }
            else
            { 
                return false;
            }
        }

        bool Close( HANDLE eventHandle )
        {
            if ( handle_ )
            {
                auto rc = DeleteTimerQueueEx( handle_, eventHandle );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                handle_ = nullptr;
                return true;
            }
            else
            {
                return false;
            }
        }

        bool Close( const EventWaitHandle& eventWaitHandle )
        {
            if ( handle_ )
            {
                auto rc = DeleteTimerQueueEx( handle_, eventWaitHandle.GetHandle( ) );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                handle_ = nullptr;
                return true;
            }
            else
            {
                return false;
            }
        }

    private:
        template <class TupleType, size_t... indices>
        static void __stdcall Invoke( void* callbackArgs, BOOLEAN TimerOrWaitFired ) noexcept
        {
            TupleType* callableAndArgs( static_cast<TupleType*>( callbackArgs ) );
            TupleType& tuple = *callableAndArgs;
            try
            {
                std::invoke( std::move( std::get<indices>( tuple ) )... );
            }
            catch ( ... )
            {
                    
            }
        }

        template <class TupleType, size_t... indices>
        static constexpr auto MakeInvoke( std::index_sequence<indices...> ) noexcept
        {
            return &Invoke<TupleType, indices...>;
        }
    public:


        template <class Function, class... Args>
            requires ( std::is_same_v<std::remove_cvref_t<Function>, TimerQueue> == false )
        [[nodiscard]] TimerQueueTimer CreateTimer( ULONG dueTime, ULONG period, TimerQueueTimerFlags flags, Function&& function, Args&&... args )
        {
            using TupleType = TimerQueueTimer::ArgsTuple<std::decay_t<Function>, std::decay_t<Args>...>;
            auto decayCopied = std::make_unique<TupleType>( std::forward<Function>( function ), std::forward<Args>( args )... );
            constexpr auto invoker = MakeInvoke<TupleType>( std::make_index_sequence<1 + sizeof...( Args )>{} );
            HANDLE queueHandle = Value( );
            HANDLE timerHandle = nullptr;
            auto rc = CreateTimerQueueTimer( &timerHandle, queueHandle, invoker, decayCopied.get( ), dueTime, period, static_cast<DWORD>( flags ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return TimerQueueTimer( queueHandle, timerHandle, std::move( decayCopied ) );
        }

        template <class Function, class... Args>
            requires ( std::is_same_v<std::remove_cvref_t<Function>, TimerQueue> == false )
        [[nodiscard]] TimerQueueTimer CreateTimer( TimeSpan period, TimerQueueTimerFlags flags, Function&& function, Args&&... args )
        {
            ULONG periodInMillis = static_cast< ULONG >( period.TotalMilliseconds( ) );
            return CreateTimer( periodInMillis, periodInMillis, flags, std::forward<Function>( function ), std::forward<Args>( args )... );
        }

        template <class Function, class... Args>
            requires ( std::is_same_v<std::remove_cvref_t<Function>, TimerQueue> == false )
        [[nodiscard]] TimerQueueTimer CreateTimer( DateTime dueTime, TimerQueueTimerFlags flags, Function&& function, Args&&... args )
        {
            TimeSpan timeSpan = dueTime - DateTime::UtcNow( );
            ULONG dueTimeInMillis = static_cast< ULONG >( timeSpan.TotalMilliseconds( ) );
            return CreateTimer( dueTimeInMillis, 0, flags, std::forward<Function>( function ), std::forward<Args>( args )... );
        }

        template <class Function, class... Args>
            requires ( std::is_same_v<std::remove_cvref_t<Function>, TimerQueue> == false )
        [[nodiscard]] TimerQueueTimer CreateTimer( DateTime dueTime, TimeSpan period, TimerQueueTimerFlags flags, Function&& function, Args&&... args )
        {
            TimeSpan timeSpan = dueTime - DateTime::UtcNow( );
            ULONG dueTimeInMillis = static_cast< ULONG >( timeSpan.TotalMilliseconds( ) );
            ULONG periodInMillis = static_cast< ULONG >( period.TotalMilliseconds( ) );
            return CreateTimer( dueTimeInMillis, periodInMillis, flags, std::forward<Function>( function ), std::forward<Args>( args )... );
        }


    };


    class Spinlock
    {
    private:
        enum LockState
        { 
            Locked, Unlocked 
        };
        std::atomic<LockState> state_;
    public:
        constexpr Spinlock( ) noexcept
            : state_( Unlocked ) 
        {}

        constexpr explicit Spinlock( bool locked ) noexcept
            : state_( locked ? Locked : Unlocked )
        {
        }


        Spinlock( const Spinlock& other ) = delete;
        Spinlock( Spinlock&& other ) = delete;
        Spinlock& operator = ( const Spinlock& other ) = delete;
        Spinlock& operator = ( Spinlock&& other ) = delete;


        void lock( ) noexcept
        {
            while ( state_.exchange( Locked, std::memory_order_acquire ) == Locked )
            {
            }
        }
        bool try_lock( ) noexcept
        {
            return state_.exchange( Locked, std::memory_order_acquire ) == Unlocked;
        }
        void unlock( ) noexcept
        {
            state_.store( Unlocked, std::memory_order_release );
        }
    };



    class SemaphoreEx
    {
        Semaphore semaphore_;
        EventWaitHandle event_;
        std::array<HANDLE, 2> handles_{};
    public:
        SemaphoreEx( Int32 initialCount = 0 )
            : semaphore_( initialCount ), event_( true )
        {
            handles_[0] = semaphore_.GetHandle( );
            handles_[1] = event_.GetHandle( );
        }

        const Core::Semaphore& Semaphore( ) const noexcept
        {
            return semaphore_;
        }
        const Core::EventWaitHandle& Event( ) const noexcept
        {
            return event_;
        }

        bool TryWait( ) const
        {
            return semaphore_.TryWait( );
        }

        bool Wait( DWORD timeoutInMilliseconds = INFINITE ) const
        {
            bool result = false;
            if ( timeoutInMilliseconds )
            {
                auto rc = WaitForMultipleObjects( static_cast<DWORD>( handles_.size( ) ), handles_.data( ), false, timeoutInMilliseconds );
                switch ( rc )
                {
                    case WAIT_OBJECT_0:
                    {
                        result = true;
                    }
                    break;
                    case WAIT_OBJECT_0 + 1:
                    case WAIT_TIMEOUT:
                    {
                        result = false;
                    }
                    break;
                    default:
                    {
                        ThrowLastOSError( );
                    }
                }
            }
            else
            {
                return semaphore_.TryWait( );
            }
            return result;
        }

        long ReleaseSemaphore( long releaseCount = 1 ) const
        {
            return semaphore_.ReleaseSemaphore( releaseCount );
        }
        long Release( long releaseCount = 1 ) const
        {
            return ReleaseSemaphore( releaseCount );
        }
        long Signal( long releaseCount = 1 ) const
        {
            return ReleaseSemaphore( releaseCount );
        }


        void lock( )
        {
            Wait( );
        }
        bool try_lock( )
        {
            return TryWait( );
        }

        void unlock( )
        {
            Release( );
        }
    };

    namespace Internal
    {
        /// <summary>
        /// LightweightSemaphoreImpl
        /// </summary>
        /// <remarks>
        /// <p>
        /// This is a modified version of Cameron Desrochers LightweightSemaphore.
        /// </p>
        /// <p>
        /// I have changed it to work with my Semaphore class, and converted it into 
        /// a template that takes an <c>Int32</c> argument specifying the maximum
        /// spin count. Timeout are specified in milliseconds.
        /// </p>
        /// <code>
        /// Original file comment:
        ///      Provides an efficient implementation of a semaphore (LightweightSemaphore).
        ///      This is an extension of Jeff Preshing's sempahore implementation (licensed 
        ///      under the terms of its separate zlib license) that has been adapted and
        ///      extended by Cameron Desrochers.
        /// </code>
        /// </remarks>
        template<typename SemaphoreT = Semaphore, Int32 maxSpins = 10000>
        class LightweightSemaphoreImpl
        {
        public:
            using SemaphoreType = SemaphoreT;
            static constexpr Int32 MaxSpins = maxSpins;
            static_assert( MaxSpins >= 0 );
        private:
            std::atomic<Int32> count_;
            SemaphoreType semaphore_;
        public:
            LightweightSemaphoreImpl( Int32 initialCount = 0 )
                : count_( initialCount ), semaphore_( initialCount )
            {
                assert( initialCount >= 0 );
            }
            const SemaphoreType& Semaphore( ) const
            {
                return semaphore_;
            }
        private:
            bool WaitWithPartialSpinning( DWORD timeoutInMilliseconds = INFINITE )
            {
                Int32 oldCount;
                int spin = MaxSpins;
                while ( --spin >= 0 )
                {
                    oldCount = count_.load( std::memory_order_relaxed );
                    if ( ( oldCount > 0 ) && count_.compare_exchange_strong( oldCount, oldCount - 1, std::memory_order_acquire, std::memory_order_relaxed ) )
                    {
                        return true;
                    }
                    // Prevent the compiler from collapsing the loop.
                    std::atomic_signal_fence( std::memory_order_acquire );
                }
                oldCount = count_.fetch_sub( 1, std::memory_order_acquire );
                if ( oldCount > 0 )
                {
                    return true;
                }
                if ( timeoutInMilliseconds != 0 )
                {
                    if ( semaphore_.Wait( timeoutInMilliseconds ) )
                    {
                        return true;
                    }
                }

                // At this point, we've timed out waiting for the semaphore, but the
                // count is still decremented indicating we may still be waiting on
                // it. So we have to re-adjust the count, but only if the semaphore
                // wasn't signaled enough times for us too since then. If it was, we
                // need to release the semaphore too.
                while ( true )
                {
                    oldCount = count_.load( std::memory_order_acquire );
                    if ( oldCount >= 0 && semaphore_.Wait( 0 ) )
                    {
                        return true;
                    }
                    if ( oldCount < 0 && count_.compare_exchange_strong( oldCount, oldCount + 1, std::memory_order_relaxed, std::memory_order_relaxed ) )
                    {
                        return false;
                    }
                }
            }

            Int32 WaitManyWithPartialSpinning( Int32 max, DWORD timeoutInMilliseconds = INFINITE )
            {
                assert( max > 0 );
                Int32 oldCount;
                int spin = MaxSpins;
                while ( --spin >= 0 )
                {
                    oldCount = count_.load( std::memory_order_relaxed );
                    if ( oldCount > 0 )
                    {
                        Int32 newCount = oldCount > max ? oldCount - max : 0;
                        if ( count_.compare_exchange_strong( oldCount, newCount, std::memory_order_acquire, std::memory_order_relaxed ) )
                        {
                            return oldCount - newCount;
                        }
                    }
                    std::atomic_signal_fence( std::memory_order_acquire );
                }
                oldCount = count_.fetch_sub( 1, std::memory_order_acquire );
                if ( oldCount <= 0 )
                {
                    if ( ( timeoutInMilliseconds == 0 ) || ( timeoutInMilliseconds != 0 && !semaphore_.Wait( timeoutInMilliseconds ) ) )
                    {
                        while ( true )
                        {
                            oldCount = count_.load( std::memory_order_acquire );
                            if ( oldCount >= 0 && semaphore_.Wait( 0 ) )
                            {
                                break;
                            }
                            if ( oldCount < 0 && count_.compare_exchange_strong( oldCount, oldCount + 1, std::memory_order_relaxed, std::memory_order_relaxed ) )
                            {
                                return 0;
                            }
                        }
                    }
                }
                if ( max > 1 )
                {
                    return 1 + TryWaitMany( max - 1 );
                }
                return 1;
            }

        public:

            bool TryWait( )
            {
                Int32 oldCount = count_.load( std::memory_order_relaxed );
                while ( oldCount > 0 )
                {
                    if ( count_.compare_exchange_weak( oldCount, oldCount - 1, std::memory_order_acquire, std::memory_order_relaxed ) )
                    {
                        return true;
                    }
                }
                return false;
            }

            bool Wait( DWORD timeoutInMilliseconds = INFINITE )
            {
                return TryWait( ) || WaitWithPartialSpinning( timeoutInMilliseconds );
            }

            // Acquires between 0 and (greedily) max, inclusive
            Int32 TryWaitMany( Int32 max )
            {
                assert( max >= 0 );
                Int32 oldCount = count_.load( std::memory_order_relaxed );
                while ( oldCount > 0 )
                {
                    Int32 newCount = oldCount > max ? oldCount - max : 0;
                    if ( count_.compare_exchange_weak( oldCount, newCount, std::memory_order_acquire, std::memory_order_relaxed ) )
                    {
                        return oldCount - newCount;
                    }
                }
                return 0;
            }

            // Acquires at least one, and (greedily) at most max
            Int32 WaitMany( Int32 max, DWORD timeoutInMilliseconds = INFINITE )
            {
                assert( max >= 0 );
                Int32 result = TryWaitMany( max );
                if ( result == 0 && max > 0 )
                {
                    result = WaitManyWithPartialSpinning( max, timeoutInMilliseconds );
                }
                return result;
            }

            void Release( Int32 count = 1 )
            {
                assert( count >= 0 );
                Int32 oldCount = count_.fetch_add( count, std::memory_order_release );
                Int32 toRelease = -oldCount < count ? -oldCount : count;
                if ( toRelease > 0 )
                {
                    semaphore_.Release( toRelease );
                }
            }
            void Signal( Int32 count = 1 )
            {
                Release( count );
            }


            size_t Available( ) const
            {
                Int32 count = count_.load( std::memory_order_relaxed );
                return count > 0 ? static_cast<size_t>( count ) : 0;
            }

            void lock( )
            {
                Wait( );
            }
            bool try_lock( )
            {
                return Wait( 0 );
            }

            void unlock( )
            {
                Release( );
            }
        };
    }


    class LightweightSemaphore : public Core::Internal::LightweightSemaphoreImpl<>
    {
    public:
        using Base = Core::Internal::LightweightSemaphoreImpl<>;
        LightweightSemaphore( Int32 initialCount = 0 )
            : Base( initialCount )
        { }
    };


    




}

#endif
