#pragma once
#ifndef __HCCTHREADPOOLS_H__
#define __HCCTHREADPOOLS_H__

#include <HCCDef.h>
#include <HCCException.h>
#include <HCCDateTime.h>
#include <HCCSync.h>
#include <HCCIO.h>
#include <HCCSocket.h>

namespace Harlinn::Common::Core::ThreadPools
{
    /*
    class Environment;

    /// <summary>
    /// A thread pool timer object
    /// </summary>
    class ThreadPoolTimer
    {
        friend class Environment;
        PTP_TIMER timer_;
    public:
        constexpr ThreadPoolTimer( ) noexcept
            : timer_( nullptr )
        {
        }

        constexpr explicit ThreadPoolTimer( PTP_TIMER timer ) noexcept
            : timer_( timer )
        {
        }

        ThreadPoolTimer( const ThreadPoolTimer& other ) = delete;
        constexpr ThreadPoolTimer( ThreadPoolTimer&& other ) noexcept
            : timer_( other.timer_ )
        {
            other.timer_ = nullptr;
        }

        ~ThreadPoolTimer( )
        {
            if ( timer_ )
            {
                CloseThreadpoolTimer( timer_ );
            }
        }

        ThreadPoolTimer& operator = ( const ThreadPoolTimer& other ) = delete;
        ThreadPoolTimer& operator = ( ThreadPoolTimer&& other ) noexcept
        {
            std::swap( timer_, other.timer_ );
            return *this;
        }

        PTP_TIMER Object( ) const noexcept
        {
            return timer_;
        }

        /// <summary>
        /// Releases the timer object
        /// </summary>
        /// <remarks>
        /// <p>
        /// The timer object is freed immediately if there are no outstanding callbacks; 
        /// otherwise, the timer object is freed asynchronously after the outstanding 
        /// callback functions complete.
        /// </p>
        /// <p>
        /// <ol>
        /// <li>
        /// Call the SetTimer function with the dueTime parameter set to 
        /// NULL and the msPeriod and msWindowLength parameters set to 0. 
        /// </li>
        /// <li>
        /// Call the WaitForCallbacks function. 
        /// </li>
        /// <li>
        /// Call Close
        /// </li>
        /// </ol>
        /// </p>
        /// </remarks>
        void Close( )
        {
            if ( timer_ )
            {
                CloseThreadpoolTimer( timer_ );
                timer_ = nullptr;
            }
        }

        /// <summary>
        /// Waits for outstanding timer callbacks to complete and optionally 
        /// cancels pending callbacks that have not yet started to execute.
        /// </summary>
        /// <param name="cancelPendingCallbacks">
        /// Indicates whether to cancel queued callbacks that have not yet 
        /// started to execute.
        /// </param>
        void WaitForCallbacks( bool cancelPendingCallbacks = false ) const
        {
            if ( timer_ )
            {
                WaitForThreadpoolTimerCallbacks( timer_, cancelPendingCallbacks ? TRUE : FALSE );
            }
        }


        bool IsTimerSet( ) const
        {
            if ( timer_ )
            {
                return IsThreadpoolTimerSet( timer_ ) != false;
            }
            return false;
        }


        /// <summary>
        /// Sets the timer object. A worker thread calls the timer object's 
        /// callback after the specified timeout expires.
        /// </summary>
        /// <param name="dueTime">
        /// <p>
        /// A pointer to a FILETIME structure that specifies the absolute or 
        /// relative time at which the timer should expire. If positive or zero, 
        /// it indicates the absolute time since January 1, 1601 (UTC), measured in 
        /// 100 nanosecond units. If negative, it indicates the amount of time to 
        /// wait relative to the current time.
        /// </p>
        /// <p>
        /// If this parameter is NULL, the timer object will cease to queue new 
        /// callbacks (but callbacks already queued will still occur). 
        /// </p>
        /// <p>
        /// if this parameter is NULL, the timer will expire immediately.
        /// </p>
        /// </param>
        /// <param name="msPeriod">
        /// The timer period, in milliseconds. If this parameter is zero, the 
        /// timer is signaled once. If this parameter is greater than zero, the 
        /// timer is periodic. A periodic timer automatically reactivates each 
        /// time the period elapses, until the timer is canceled.
        /// </param>
        /// <param name="msWindowLength">
        /// The maximum amount of time the system can delay before calling 
        /// the timer callback. If this parameter is set, the system can 
        /// batch calls to conserve power.
        /// </param>
        /// <remarks>
        /// If the due time specified by dueTime is relative, the time 
        /// that the system spends in sleep or hibernation does not count 
        /// toward the expiration of the timer. The timer is signaled when 
        /// the cumulative amount of elapsed time the system spends in the 
        /// waking state equals the timer's relative due time or period. If 
        /// the due time specified by pftDueTime is absolute, the time that 
        /// the system spends in sleep or hibernation does count toward the 
        /// expiration of the timer. If the timer expires while the system 
        /// is sleeping, the timer is signaled immediately when the system 
        /// wakes.
        /// </remarks>
        void SetTimer( PFILETIME dueTime, DWORD msPeriod, DWORD msWindowLength ) const
        {
            if ( timer_ )
            {
                SetThreadpoolTimer( timer_, dueTime, msPeriod, msWindowLength );
            }
        }

        void SetTimer( const DateTime& dueTime, DWORD msPeriod, DWORD msWindowLength ) const
        {
            auto filetime = dueTime.ToFileTime( );
            SetTimer( reinterpret_cast<PFILETIME>( &filetime ), msPeriod, msWindowLength );
        }
        void SetTimer( const TimeSpan& dueTime, DWORD msPeriod, DWORD msWindowLength ) const
        {
            auto filetime = -dueTime.Ticks( );
            SetTimer( reinterpret_cast<PFILETIME>( &filetime ), msPeriod, msWindowLength );
        }


    };

    /// <summary>
    /// A thread pool work object
    /// </summary>
    class ThreadPoolWork
    {
        friend class Environment;
        PTP_WORK work_;
    public:
        constexpr ThreadPoolWork( ) noexcept
            : work_( nullptr )
        {
        }

        constexpr explicit ThreadPoolWork( PTP_WORK work ) noexcept
            : work_( work )
        {
        }

        ThreadPoolWork( const ThreadPoolWork& other ) = delete;
        constexpr ThreadPoolWork( ThreadPoolWork&& other ) noexcept
            : work_( other.work_ )
        {
            other.work_ = nullptr;
        }

        ~ThreadPoolWork( )
        {
            if ( work_ )
            {
                CloseThreadpoolWork( work_ );
            }
        }

        ThreadPoolWork& operator = ( const ThreadPoolWork& other ) = delete;
        ThreadPoolWork& operator = ( ThreadPoolWork&& other ) noexcept
        {
            std::swap( work_, other.work_ );
            return *this;
        }

        PTP_WORK Object( ) const noexcept
        {
            return work_;
        }

        /// <summary>
        /// Releases the work object
        /// </summary>
        /// <remarks>
        /// The work object is freed immediately if there are no outstanding 
        /// callbacks; otherwise, the work object is freed asynchronously 
        /// after the outstanding callbacks complete.
        /// </remarks>
        void Close( )
        {
            if ( work_ )
            {
                CloseThreadpoolWork( work_ );
                work_ = nullptr;
            }
        }

        /// <summary>
        /// Waits for outstanding work callbacks to complete and optionally 
        /// cancels pending callbacks that have not yet started to execute
        /// </summary>
        /// <param name="cancelPendingCallbacks">
        /// Indicates whether to cancel queued callbacks that have not yet 
        /// started to execute.
        /// </param>
        void WaitForCallbacks( bool cancelPendingCallbacks = false ) const
        {
            if ( work_ )
            {
                WaitForThreadpoolWorkCallbacks( work_, cancelPendingCallbacks ? TRUE : FALSE );
            }
        }


        /// <summary>
        /// Posts a work object to the thread pool. A worker thread calls 
        /// the work object's callback function.
        /// </summary>
        /// <remarks>
        /// You can post a work object one or more times (up to MAXULONG) 
        /// without waiting for prior callbacks to complete. The callbacks 
        /// will execute in parallel. To improve efficiency, the thread 
        /// pool may throttle the threads.
        /// </remarks>
        void Submit( ) const
        {
            if ( work_ )
            {
                SubmitThreadpoolWork( work_ );
            }
        }




    };

    /// <summary>
    /// A thread pool wait object
    /// </summary>
    class ThreadPoolWait
    {
        friend class Environment;
        PTP_WAIT wait_;
    public:
        constexpr ThreadPoolWait( ) noexcept
            : wait_( nullptr )
        {
        }

        constexpr explicit ThreadPoolWait( PTP_WAIT wait ) noexcept
            : wait_( wait )
        {
        }

        ThreadPoolWait( const ThreadPoolWait& other ) = delete;
        constexpr ThreadPoolWait( ThreadPoolWait&& other ) noexcept
            : wait_( other.wait_ )
        {
            other.wait_ = nullptr;
        }

        ~ThreadPoolWait( )
        {
            if ( wait_ )
            {
                CloseThreadpoolWait( wait_ );
            }
        }

        ThreadPoolWait& operator = ( const ThreadPoolWait& other ) = delete;
        ThreadPoolWait& operator = ( ThreadPoolWait&& other ) noexcept
        {
            std::swap( wait_, other.wait_ );
            return *this;
        }

        PTP_WAIT Object( ) const noexcept
        {
            return wait_;
        }


        /// <summary>
        /// Releases the wait object
        /// </summary>
        /// <remarks>
        /// The wait object is freed immediately if there are no outstanding callbacks; 
        /// otherwise, the timer object is freed asynchronously after the outstanding 
        /// callbacks complete.
        /// </remarks>
        void Close( )
        {
            if ( wait_ )
            {
                CloseThreadpoolWait( wait_ );
                wait_ = nullptr;
            }
        }

        /// <summary>
        /// Waits for outstanding wait callbacks to complete and optionally cancels 
        /// pending callbacks that have not yet started to execute.
        /// </summary>
        /// <param name="cancelPendingCallbacks">
        /// Indicates whether to cancel queued callbacks that have not yet started to execute.
        /// </param>
        void WaitForCallbacks( bool cancelPendingCallbacks = false ) const
        {
            if ( wait_ )
            {
                WaitForThreadpoolWaitCallbacks( wait_, cancelPendingCallbacks ? TRUE : FALSE );
            }
        }




        /// <summary>
        /// Sets the wait object, replacing the previous wait object, 
        /// if any. A worker thread calls the wait object's callback 
        /// function after the handle becomes signaled or after the 
        /// specified timeout expires.
        /// </summary>
        /// <param name="handle">
        /// <p>
        /// If this parameter is NULL, the wait object will cease to queue 
        /// new callbacks (but callbacks already queued will still occur).
        /// </p>
        /// <p>
        /// If this parameter is not NULL, it must refer to a valid 
        /// waitable object.
        /// </p>
        /// <p>
        /// If this handle is closed while the wait is still pending, 
        /// the function's behavior is undefined. If the wait is still 
        /// pending and the handle must be closed, use Close to cancel 
        /// the wait and then close the handle.
        /// </p>
        /// </param>
        /// <param name="timeout">
        /// <p>
        /// A pointer to a FILETIME structure that specifies the absolute 
        /// or relative time at which the wait operation should time out. 
        /// If this parameter points to a positive value, it indicates the 
        /// absolute time since January 1, 1601 (UTC), in 100-nanosecond 
        /// intervals. If this parameter points to a negative value, it 
        /// indicates the amount of time to wait relative to the current time.
        /// </p>
        /// <p>
        /// If this parameter points to 0, the wait times out immediately. 
        /// </p>
        /// <p>
        /// If this parameter is NULL, the wait will not time out.
        /// </p>
        /// </param>
        void SetWait( HANDLE handle, PFILETIME timeout = nullptr ) const
        {
            if ( wait_ )
            {
                SetThreadpoolWait( wait_, handle, timeout );
            }

        }

        void SetWait( HANDLE handle, const DateTime& timeout ) const
        {
            auto fileTime = timeout.ToFileTime( );
            SetWait( handle, reinterpret_cast<PFILETIME>( &fileTime ) );
        }
        void SetWait( HANDLE handle, const TimeSpan& timeout ) const
        {
            auto fileTime = -timeout.Ticks( );
            SetWait( handle, reinterpret_cast<PFILETIME>( &fileTime ) );
        }


    };


    /// <summary>
    /// A thread pool I/O completion object
    /// </summary>
    class ThreadPoolIO
    {
        friend class Environment;
        PTP_IO io_;
    public:
        constexpr ThreadPoolIO( ) noexcept
            : io_( nullptr )
        {
        }

        constexpr explicit ThreadPoolIO( PTP_IO io ) noexcept
            : io_( io )
        { }

        ThreadPoolIO( const ThreadPoolIO& other ) = delete;
        constexpr ThreadPoolIO( ThreadPoolIO&& other ) noexcept
            : io_( other.io_ )
        {
            other.io_ = nullptr;
        }

        ~ThreadPoolIO( )
        {
            if ( io_ )
            {
                CloseThreadpoolIo( io_ );
            }
        }

        ThreadPoolIO& operator = ( const ThreadPoolIO& other ) = delete;
        ThreadPoolIO& operator = ( ThreadPoolIO&& other ) noexcept
        {
            std::swap( io_, other.io_);
            return *this;
        }

        PTP_IO Object( ) const noexcept
        {
            return io_;
        }


        /// <summary>
        /// Waits for outstanding I/O completion callbacks to complete and 
        /// optionally cancels pending callbacks that have not yet started 
        /// to execute.
        /// </summary>
        /// <param name="cancelPendingCallbacks">
        /// Indicates whether to cancel queued callbacks that have not yet 
        /// started to execute
        /// </param>
        /// <remarks>
        /// When cancelPendingCallbacks is set to true, only queued callbacks 
        /// are canceled. Pending I/O requests are not canceled. Therefore, 
        /// the caller should call GetOverlappedResult for the OVERLAPPED 
        /// structure to check whether the I/O operation has completed before 
        /// freeing the structure. As an alternative, set cancelPendingCallbacks 
        /// to FALSE and have the associated I/O completion callback free the 
        /// OVERLAPPED structure. Be careful not to free the OVERLAPPED structure 
        /// while I/O requests are still pending; use GetOverlappedResult to determine 
        /// the status of the I/O operation and wait for the operation to complete. 
        /// The CancelIoEx function can optionally be used first to cancel outstanding 
        /// I/O requests, potentially shortening the wait. 
        /// </remarks>
        void WaitForCallbacks( bool cancelPendingCallbacks = false ) const
        {
            if ( io_ )
            {
                WaitForThreadpoolIoCallbacks( io_, cancelPendingCallbacks ? TRUE : FALSE );
            }
        }


        /// <summary>
        /// Notifies the thread pool that I/O operations may possibly 
        /// begin for the specified I/O completion object. A worker 
        /// thread calls the I/O completion object's callback function 
        /// after the operation completes on the file handle bound to 
        /// this object.
        /// </summary>
        /// <remarks>
        /// <p>
        /// You must call this function before initiating each asynchronous 
        /// I/O operation on the file handle bound to the I/O completion object. 
        /// Failure to do so will cause the thread pool to ignore an I/O 
        /// operation when it completes and will cause memory corruption.
        /// </p>
        /// <p>
        /// If the I/O operation fails, call the Cancel function to cancel 
        /// this notification.
        /// </p>
        /// <p>
        /// If the file handle bound to the I/O completion object has the 
        /// notification mode FILE_SKIP_COMPLETION_PORT_ON_SUCCESS and an 
        /// asynchronous I/O operation returns immediately with success, 
        /// the object's I/O completion callback function is not called and 
        /// threadpool I/O notifications must be canceled.
        /// </p>
        /// </remarks>
        void Start( ) const noexcept
        {
            if ( io_ )
            {
                StartThreadpoolIo( io_ );
            }
        }

        /// <summary>
        /// Cancels the notification from the Start function
        /// </summary>
        /// <remarks>
        /// To prevent memory leaks, you must call the CancelThreadpoolIo function 
        /// for either of the following scenarios:
        /// <ul>
        /// <li>
        /// An overlapped (asynchronous) I/O operation fails (that is, the 
        /// asynchronous I/O function call returns failure with an error code 
        /// other than ERROR_IO_PENDING)</li>
        /// <li>
        /// An asynchronous I/O operation returns immediately with success and 
        /// the file handle associated with the I/O completion object has the 
        /// notification mode FILE_SKIP_COMPLETION_PORT_ON_SUCCESS. The file 
        /// handle will not notify the I/O completion port and the associated 
        /// I/O callback function will not be called.
        /// </li>
        /// </ul>
        /// </remarks>
        void Cancel( ) const noexcept
        {
            if ( io_ )
            {
                CancelThreadpoolIo( io_ );
            }
        }

        /// <summary>
        /// Releases the specified I/O completion object
        /// </summary>
        /// <remarks>
        /// <p>
        /// The I/O completion object is freed immediately if there are no 
        /// outstanding callbacks; otherwise, the I/O completion object is 
        /// freed asynchronously after the outstanding callbacks complete.
        /// </p>
        /// <p>
        /// You should close the associated file handle and wait for all 
        /// outstanding overlapped I/O operations to complete before calling 
        /// this function. You must not cause any more overlapped I/O operations 
        /// to occur after calling this function.
        /// </p>
        /// <p>
        /// It may be necessary to cancel threadpool I/O notifications to 
        /// prevent memory leaks.
        /// </p>
        /// </remarks>
        void Close( ) noexcept
        {
            if ( io_ )
            {
                CloseThreadpoolIo( io_ );
                io_ = nullptr;
            }
        }
    };

    /// <summary>
    /// Represents the pool of callback threads
    /// for the environment
    /// </summary>
    class ThreadPool
    {
        PTP_POOL pool_;
    public:
        constexpr ThreadPool( ) noexcept
            : pool_( nullptr )
        {

        }

        constexpr explicit ThreadPool( PTP_POOL pool ) noexcept
            : pool_( pool )
        {

        }

        ThreadPool( const ThreadPool& other ) = delete;
        constexpr ThreadPool( ThreadPool&& other ) noexcept
            : pool_( other.pool_ )
        {
            other.pool_ = nullptr;
        }

        ~ThreadPool( ) noexcept
        {
            if ( pool_ )
            {
                CloseThreadpool( pool_ );
            }
        }

        ThreadPool& operator = ( const ThreadPool& other ) = delete;
        ThreadPool& operator = ( ThreadPool&& other ) noexcept
        {
            if ( this != &other )
            {
                if ( pool_ )
                {
                    CloseThreadpool( pool_ );
                }
                pool_ = other.pool_;
                other.pool_ = nullptr;
            }
            return *this;
        }

        constexpr PTP_POOL Pool( ) const noexcept
        {
            return pool_;
        }

        /// <summary>
        /// Sets the maximum number of threads that the specified thread pool can allocate to process callbacks.
        /// </summary>
        /// <param name="maximumThreads">The maximum number of threads.</param>
        void SetMaximumThreads( UInt32 maximumThreads )
        {
            SetThreadpoolThreadMaximum( pool_, maximumThreads );
        }

        /// <summary>
        /// Sets the minimum number of threads that the specified thread pool must make available to process callbacks.
        /// </summary>
        /// <param name="minimumThreads">The minimum number of threads.</param>
        void SetMinimumThreads( UInt32 minimumThreads )
        {
            auto rc = SetThreadpoolThreadMinimum( pool_, minimumThreads );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }


    };

    class CallbackInstance
    {
        PTP_CALLBACK_INSTANCE instance_;
    public:
        constexpr CallbackInstance( ) noexcept
            : instance_( nullptr )
        {
        }

        constexpr explicit CallbackInstance( PTP_CALLBACK_INSTANCE instance ) noexcept
            : instance_( instance )
        {
        }

        constexpr bool InCallback( ) const noexcept
        {
            return instance_ != nullptr;
        }


        void SetEventWhenCallbackReturns( HANDLE handle ) const noexcept
        {
            ::SetEventWhenCallbackReturns( instance_, handle );
        }

        void SetEventWhenCallbackReturns( const EventWaitHandle& eventWaitHandle ) const noexcept
        {
            ::SetEventWhenCallbackReturns( instance_, eventWaitHandle.GetHandle() );
        }

        void ReleaseSemaphoreWhenCallbackReturns( HANDLE handle, UInt32 releaseCount ) const noexcept
        {
            ::ReleaseSemaphoreWhenCallbackReturns( instance_, handle, releaseCount );
        }
        void ReleaseSemaphoreWhenCallbackReturns( const Semaphore& semaphore, UInt32 releaseCount ) const noexcept
        {
            ::ReleaseSemaphoreWhenCallbackReturns( instance_, semaphore.GetHandle( ), releaseCount );
        }

        void ReleaseMutexWhenCallbackReturns( HANDLE handle ) const noexcept
        {
            ::ReleaseMutexWhenCallbackReturns( instance_, handle );
        }
        void ReleaseMutexWhenCallbackReturns( const Mutex& mutex ) const noexcept
        {
            ::ReleaseMutexWhenCallbackReturns( instance_, mutex.GetHandle() );
        }

        void LeaveCriticalSectionWhenCallbackReturns( CRITICAL_SECTION* criticalSection ) const noexcept
        {
            ::LeaveCriticalSectionWhenCallbackReturns( instance_, criticalSection );
        }

        void LeaveCriticalSectionWhenCallbackReturns( CriticalSection& criticalSection ) const noexcept
        {
            static_assert( sizeof( CriticalSection ) == sizeof( CRITICAL_SECTION ) );
            ::LeaveCriticalSectionWhenCallbackReturns( instance_, (CRITICAL_SECTION*)&criticalSection );
        }

        void DisassociateCurrentThreadFromCallback( ) const noexcept
        {
            ::DisassociateCurrentThreadFromCallback( instance_ );
        }


    };


    /// <summary>
    /// 
    /// </summary>
    class Environment : protected TP_CALLBACK_ENVIRON
    {
        using Base = TP_CALLBACK_ENVIRON;
        ThreadPool threadPool_;
    public:
        using Timer = ThreadPoolTimer;
        using Work = ThreadPoolWork;
        using Wait = ThreadPoolWait;
        using IO = ThreadPoolIO;

        Environment( )
            : Base{}
        {
            InitializeThreadpoolEnvironment( this );
        }

        Environment( const Environment& other ) = delete;
        Environment( Environment&& other ) = delete;

        ~Environment( )
        {
            DestroyThreadpoolEnvironment( this );
        }

        Environment& operator = ( const Environment& other ) = delete;
        Environment& operator = ( Environment&& other ) = delete;


        void SetCallbackPool( ThreadPool&& threadPool )
        {

            SetThreadpoolCallbackPool( this, threadPool.Pool( ) );
            threadPool_ = std::move( threadPool );
        }


        template<typename T>
        requires std::is_base_of_v< ThreadPoolTimer, T>
            T Create( PTP_TIMER_CALLBACK callback, void* callbackArg )
        {
            auto timer = CreateThreadpoolTimer( callback, callbackArg, this );
            if ( !timer )
            {
                ThrowLastOSError( );
            }
            T result;
            result.timer_ = timer;
            return result;
        }

        template<typename T>
            requires std::is_base_of_v< ThreadPoolWork, T>
        T Create( PTP_WORK_CALLBACK callback, void* callbackArg )
        {
            auto work = CreateThreadpoolWork( callback, callbackArg, this );
            if ( !work )
            {
                ThrowLastOSError( );
            }
            T result;
            result.work_ = work;
            return result;
        }

        template<typename T>
            requires std::is_base_of_v< ThreadPoolWait, T>
        T Create( PTP_WAIT_CALLBACK callback, void* callbackArg )
        {
            auto wait = CreateThreadpoolWait( callback, callbackArg, this );
            if ( !wait )
            {
                ThrowLastOSError( );
            }
            T result;
            result.wait_ = wait;
            return result;
        }



        template<typename T>
            requires std::is_base_of_v< ThreadPoolIO, T>
        T Create(HANDLE handle, PTP_WIN32_IO_CALLBACK callback, void* callbackArg )
        {
            auto io = CreateThreadpoolIo( handle, callback, callbackArg, this );
            if ( !io )
            {
                ThrowLastOSError( );
            }
            T result;
            result.io_ = io;
            return result;
        }

        void TrySubmit( PTP_SIMPLE_CALLBACK callback, void* callbackArg )
        {
            auto rc = TrySubmitThreadpoolCallback( callback, callbackArg, this );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
    private:
        template <class TupleType, size_t... indices>
        static void __stdcall Invoke( PTP_CALLBACK_INSTANCE Instance, void* threadArgs ) noexcept
        {
            const std::unique_ptr<TupleType> callableAndArgs( static_cast<TupleType*>( threadArgs ) );
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
            requires ( std::is_same_v<std::remove_cvref_t<Function>, PTP_SIMPLE_CALLBACK> == false )
        void TrySubmit( Function&& function, Args&&... args )
        {
            using TupleType = std::tuple<std::decay_t<Function>, std::decay_t<Args>...>;
            auto decayCopied = std::make_unique<TupleType>( std::forward<Function>( function ), std::forward<Args>( args )... );
            constexpr auto invoker = MakeInvoke<TupleType>( std::make_index_sequence<1 + sizeof...( Args )>{} );

            TrySubmit( (PTP_SIMPLE_CALLBACK)invoker, decayCopied.get( ) );
            decayCopied.release( );
        }


    };




    /// <summary>
    /// This template can be used as a base for implementing a class that 
    /// receives timer callbacks from the thread pool
    /// </summary>
    /// <typeparam name="DerivedT">
    /// DerivedT must be a class derived from the this template that implements:
    /// void Callback( const CallbackInstance& instance )
    /// </typeparam>
    template<typename DerivedT>
    class TimerHandler
    {
    public:
        using DerivedType = DerivedT;
    private:
        template<typename T>
        static void __stdcall _callback( PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer )
        {
            auto handler = reinterpret_cast<T*>( Context );
            CallbackInstance instance( Instance );
            handler->Callback( instance );
        }
        ThreadPoolTimer threadPoolTimer_;
    protected:
        TimerHandler( Environment& environment )
            : threadPoolTimer_( environment.Create<ThreadPoolTimer>( _callback<DerivedType>, this ) )
        {

        }
    public:
        const ThreadPoolTimer& Timer( ) const
        {
            return threadPoolTimer_;
        }

        /// <summary>
        /// Waits for outstanding timer callbacks to complete and optionally 
        /// cancels pending callbacks that have not yet started to execute.
        /// </summary>
        /// <param name="cancelPendingCallbacks">
        /// Indicates whether to cancel queued callbacks that have not yet 
        /// started to execute.
        /// </param>
        void WaitForCallbacks( bool cancelPendingCallbacks = false ) const
        {
            threadPoolTimer_.WaitForCallbacks( cancelPendingCallbacks );
        }


        bool IsTimerSet( ) const
        {
            return threadPoolTimer_.IsTimerSet( );
        }


        void SetTimer( PFILETIME dueTime, DWORD msPeriod, DWORD msWindowLength ) const
        {
            threadPoolTimer_.SetTimer( dueTime, msPeriod, msWindowLength );
        }

        void SetTimer( const DateTime& dueTime, DWORD msPeriod, DWORD msWindowLength ) const
        {
            auto filetime = dueTime.ToFileTime( );
            SetTimer( reinterpret_cast<PFILETIME>( &filetime ), msPeriod, msWindowLength );
        }
        void SetTimer( const TimeSpan& dueTime, DWORD msPeriod, DWORD msWindowLength ) const
        {
            auto filetime = -dueTime.Ticks( );
            SetTimer( reinterpret_cast<PFILETIME>( &filetime ), msPeriod, msWindowLength );
        }
    };

    /// <summary>
    /// A class for handling subscriptions to timer events 
    /// </summary>
    class TimerDispatcher : public TimerHandler<TimerDispatcher>
    {
        template<typename DerivedT>
        friend class TimerHandler;
    public:
        using Base = TimerHandler<TimerDispatcher>;
        boost::signals2::signal<void( const TimerDispatcher& dispatcher, const CallbackInstance& instance )> OnCallback;
        TimerDispatcher( Environment& environment )
            : Base( environment )
        { }
    private:
        void Callback( const CallbackInstance& instance ) const
        {
            OnCallback( *this, instance );
        }
    };


    /// <summary>
    /// This template can be used as a base for implementing a class that 
    /// receives work callbacks from the thread pool
    /// </summary>
    /// <typeparam name="DerivedT">
    /// DerivedT must be a class derived from the this template that implements:
    /// void Callback( const CallbackInstance& instance )
    /// </typeparam>
    template<typename DerivedT>
    class WorkHandler
    {
    public:
        using DerivedType = DerivedT;
    private:
        template<typename T>
        static void __stdcall _callback( PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_WORK Work )
        {
            auto handler = reinterpret_cast<T*>( Context );
            CallbackInstance instance( Instance );
            handler->Callback( instance );
        }
        ThreadPoolWork threadPoolWork_;
    protected:
        WorkHandler( Environment& environment )
            : threadPoolWork_( environment.Create<ThreadPoolWork>( _callback<DerivedType>, this ) )
        {

        }
    public:
        const ThreadPoolWork& Work( ) const
        {
            return threadPoolWork_;
        }

        /// <summary>
        /// Waits for outstanding work callbacks to complete and optionally 
        /// cancels pending callbacks that have not yet started to execute
        /// </summary>
        /// <param name="cancelPendingCallbacks">
        /// Indicates whether to cancel queued callbacks that have not yet 
        /// started to execute.
        /// </param>
        void WaitForCallbacks( bool cancelPendingCallbacks = false ) const
        {
            threadPoolWork_.WaitForCallbacks( cancelPendingCallbacks );
        }

        
        void Submit( ) const
        {
            threadPoolWork_.Submit( );
        }
    };

    /// <summary>
    /// A class for handling subscriptions to work events 
    /// </summary>
    class WorkDispatcher : public WorkHandler<WorkDispatcher>
    {
        template<typename DerivedT>
        friend class WorkHandler;
    public:
        using Base = WorkHandler<WorkDispatcher>;
        boost::signals2::signal<void( const WorkDispatcher& dispatcher, const CallbackInstance& instance )> OnCallback;
        WorkDispatcher( Environment& environment )
            : Base( environment )
        {
        }
    private:
        void Callback( const CallbackInstance& instance ) const
        {
            OnCallback( *this, instance );
        }
    };


    /// <summary>
    /// This template can be used as a base for implementing a class that 
    /// receives wait callbacks from the thread pool
    /// </summary>
    /// <typeparam name="DerivedT">
    /// DerivedT must be a class derived from the this template that implements:
    /// void Callback( const CallbackInstance& instance, bool timedout )
    /// </typeparam>
    template<typename DerivedT>
    class WaitHandler
    {
    public:
        using DerivedType = DerivedT;
    private:
        template<typename T>
        static void __stdcall _callback( PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_WAIT Wait, TP_WAIT_RESULT WaitResult )
        {
            auto handler = reinterpret_cast<T*>( Context );
            CallbackInstance instance( Instance );
            handler->Callback( instance, WaitResult == WAIT_TIMEOUT ? true : false );
        }
        ThreadPoolWait threadPoolWait_;
    protected:
        WaitHandler( Environment& environment )
            : threadPoolWait_( environment.Create<ThreadPoolWait>( _callback<DerivedType>, this ) )
        {

        }
    public:
        const ThreadPoolWait& Wait( ) const
        {
            return threadPoolWait_;
        }

        /// <summary>
        /// Waits for outstanding wait callbacks to complete and optionally cancels 
        /// pending callbacks that have not yet started to execute.
        /// </summary>
        /// <param name="cancelPendingCallbacks">
        /// Indicates whether to cancel queued callbacks that have not yet started to execute.
        /// </param>
        void WaitForCallbacks( bool cancelPendingCallbacks = false ) const
        {
            threadPoolWait_.WaitForCallbacks( cancelPendingCallbacks );
        }

        void SetWait( HANDLE handle, PFILETIME timeout = nullptr ) const
        {
            threadPoolWait_.SetWait( handle, timeout );
        }

        void SetWait( HANDLE handle, const DateTime& timeout ) const
        {
            auto fileTime = timeout.ToFileTime( );
            SetWait( handle, reinterpret_cast<PFILETIME>( &fileTime ) );
        }
        void SetWait( HANDLE handle, const TimeSpan& timeout ) const
        {
            auto fileTime = -timeout.Ticks( );
            SetWait( handle, reinterpret_cast<PFILETIME>( &fileTime ) );
        }
    };


    /// <summary>
    /// A class for handling subscriptions to wait events 
    /// </summary>
    class WaitDispatcher : public WaitHandler<WaitDispatcher>
    {
        template<typename DerivedT>
        friend class WaitHandler;
    public:
        using Base = WaitHandler<WaitDispatcher>;
        boost::signals2::signal<void( const WaitDispatcher& dispatcher, const CallbackInstance& instance, bool timedout )> OnCallback;
        WaitDispatcher( Environment& environment )
            : Base( environment )
        {
        }
    private:
        void Callback( const CallbackInstance& instance, bool timedout ) const
        {
            OnCallback( *this, instance, timedout );
        }
    };


    /// <summary>
    /// This template can be used as a base for implementing a class that 
    /// receives IO callbacks from the thread pool
    /// </summary>
    /// <typeparam name="DerivedT">
    /// DerivedT must be a class derived from the this template that implements:
    /// void Callback( const CallbackInstance& instance, OVERLAPPED* overlapped, UInt32 ioResult, UInt64 numberOfBytesTransferred )
    /// </typeparam>
    template<typename DerivedT>
    class IOHandler
    {
        using DerivedType = DerivedT;
    private:
        static int filter( unsigned int code, struct _EXCEPTION_POINTERS* ep )
        {
            if ( code == EXCEPTION_ACCESS_VIOLATION )
            {
                return EXCEPTION_EXECUTE_HANDLER;
            }
            else
            {
                return EXCEPTION_CONTINUE_SEARCH;
            };
        }
        template<typename T>
        static void __stdcall callback( PTP_CALLBACK_INSTANCE Instance, PVOID Context, PVOID Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io )
        {
            auto handler = reinterpret_cast<T*>( Context );
            CallbackInstance instance( Instance );
            __try
            {
                handler->Callback( instance, reinterpret_cast<IO::Request*>( Overlapped ), IoResult, NumberOfBytesTransferred );
            }
            __except( filter( GetExceptionCode( ), GetExceptionInformation( ) ) )
            {

            }
        }
        ThreadPoolIO threadPoolIO_;
    protected:
        IOHandler( HANDLE handle, Environment& environment )
            : threadPoolIO_( environment.Create<ThreadPoolIO>( handle, callback< DerivedT >, this ) )
        { 
        }
    public:
        /// <summary>
        /// Waits for outstanding I/O completion callbacks to complete and 
        /// optionally cancels pending callbacks that have not yet started 
        /// to execute.
        /// </summary>
        /// <param name="cancelPendingCallbacks">
        /// Indicates whether to cancel queued callbacks that have not yet 
        /// started to execute
        /// </param>
        /// <remarks>
        /// When cancelPendingCallbacks is set to true, only queued callbacks 
        /// are canceled. Pending I/O requests are not canceled. Therefore, 
        /// the caller should call GetOverlappedResult for the OVERLAPPED 
        /// structure to check whether the I/O operation has completed before 
        /// freeing the structure. As an alternative, set cancelPendingCallbacks 
        /// to FALSE and have the associated I/O completion callback free the 
        /// OVERLAPPED structure. Be careful not to free the OVERLAPPED structure 
        /// while I/O requests are still pending; use GetOverlappedResult to determine 
        /// the status of the I/O operation and wait for the operation to complete. 
        /// The CancelIoEx function can optionally be used first to cancel outstanding 
        /// I/O requests, potentially shortening the wait. 
        /// </remarks>
        void WaitForCallbacks( bool cancelPendingCallbacks = false ) const
        {
            threadPoolIO_.WaitForCallbacks( cancelPendingCallbacks );
        }

        /// <summary>
        /// Releases the specified I/O completion object
        /// </summary>
        /// <remarks>
        /// <p>
        /// The I/O completion object is freed immediately if there are no 
        /// outstanding callbacks; otherwise, the I/O completion object is 
        /// freed asynchronously after the outstanding callbacks complete.
        /// </p>
        /// <p>
        /// You should close the associated file handle and wait for all 
        /// outstanding overlapped I/O operations to complete before calling 
        /// this function. You must not cause any more overlapped I/O operations 
        /// to occur after calling this function.
        /// </p>
        /// <p>
        /// It may be necessary to cancel threadpool I/O notifications to 
        /// prevent memory leaks.
        /// </p>
        /// </remarks>
        void Close( ) noexcept
        {
            threadPoolIO_.Close( );
        }


        /// <summary>
        /// Notifies the thread pool that I/O operations may possibly 
        /// begin for the specified I/O completion object. A worker 
        /// thread calls the I/O completion object's callback function 
        /// after the operation completes on the file handle bound to 
        /// this object.
        /// </summary>
        /// <remarks>
        /// <p>
        /// You must call this function before initiating each asynchronous 
        /// I/O operation on the file handle bound to the I/O completion object. 
        /// Failure to do so will cause the thread pool to ignore an I/O 
        /// operation when it completes and will cause memory corruption.
        /// </p>
        /// <p>
        /// If the I/O operation fails, call the Cancel function to cancel 
        /// this notification.
        /// </p>
        /// <p>
        /// If the file handle bound to the I/O completion object has the 
        /// notification mode FILE_SKIP_COMPLETION_PORT_ON_SUCCESS and an 
        /// asynchronous I/O operation returns immediately with success, 
        /// the object's I/O completion callback function is not called and 
        /// threadpool I/O notifications must be canceled.
        /// </p>
        /// </remarks>
        void Start( ) const noexcept
        {
            threadPoolIO_.Start( );
        }

        /// <summary>
        /// Cancels the notification from the Start function
        /// </summary>
        /// <remarks>
        /// To prevent memory leaks, you must call the Cancel function 
        /// for either of the following scenarios:
        /// <ul>
        /// <li>
        /// An overlapped (asynchronous) I/O operation fails (that is, the 
        /// asynchronous I/O function call returns failure with an error code 
        /// other than ERROR_IO_PENDING)</li>
        /// <li>
        /// An asynchronous I/O operation returns immediately with success and 
        /// the file handle associated with the I/O completion object has the 
        /// notification mode FILE_SKIP_COMPLETION_PORT_ON_SUCCESS. The file 
        /// handle will not notify the I/O completion port and the associated 
        /// I/O callback function will not be called.
        /// </li>
        /// </ul>
        /// </remarks>
        void Cancel( ) const noexcept
        {
            threadPoolIO_.Cancel( );
        }

    };


    class IORequest : public IO::Request
    {
    public:
        using Base = IO::Request;
    private:
    protected:
        IORequest( )
        { }

        explicit IORequest( HANDLE handle, void* context = nullptr )
            : Base( handle, context )
        {
        }
    };


    enum class FileRequestType
    {
        Unknown,
        Read,
        Write,
        ReadScatter,
        WriteGather
    };

    class FileRequest : public IORequest
    {
    public:
        using Base = IORequest;
    private:
        FileRequestType type_;
    protected:
        FileRequest( )
            : Base(), type_( FileRequestType::Unknown )
        {
        }

        explicit FileRequest( HANDLE handle, FileRequestType type, void* context = nullptr )
            : Base( handle, context ), type_( type )
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
    private:
        void* buffer_;
        UInt32 numberOfBytesToRead_;
    public:
        ReadFileRequest( HANDLE handle, UInt64 position, void* buffer, UInt32 numberOfBytesToRead, void* context = nullptr )
            : Base( handle, FileRequestType::Read, context ), buffer_( buffer ), numberOfBytesToRead_( numberOfBytesToRead )
        {
            SetPosition( position );
        }

        constexpr void* Buffer( ) const noexcept
        {
            return buffer_;
        }
        UInt32 NumberOfBytesToRead( ) const noexcept
        {
            return numberOfBytesToRead_;
        }

    };

    class WriteFileRequest : public FileRequest
    {
    public:
        using Base = FileRequest;
    private:
        void* buffer_;
        UInt32 numberOfBytesToWrite_;
    public:
        WriteFileRequest( HANDLE handle, UInt64 position, void* buffer, UInt32 numberOfBytesToWrite, void* context = nullptr )
            : Base( handle, FileRequestType::Write, context ), buffer_( buffer ), numberOfBytesToWrite_( numberOfBytesToWrite )
        {
            SetPosition( position );
        }

        constexpr void* Buffer( ) const noexcept
        {
            return buffer_;
        }
        UInt32 NumberOfBytesToWrite( ) const noexcept
        {
            return numberOfBytesToWrite_;
        }

    };



    template<typename DerivedT>
    class FileHandler : public IOHandler< DerivedT >
    {
        template<typename DerivedT>
        friend class IOHandler;
    public:
        using Base = IOHandler< DerivedT >;
        using FileStream = IO::FileStream;
    private:

    protected:
        FileHandler( HANDLE handle, Environment& environment )
            : Base( handle, environment )
        { }
        FileHandler( const FileStream& fileStream, Environment& environment )
            : Base( fileStream.Handle(), environment )
        {
        }
    public:
    protected:
        void Callback( const CallbackInstance& instance, IO::Request* overlapped, UInt32 ioResult, UInt64 numberOfBytesTransferred )
        {
            FileRequest* request = static_cast<FileRequest*>( overlapped );
            DerivedT* self = static_cast<DerivedT*>( this );
            auto requestType = request->Type( );
            switch ( requestType )
            {
                case FileRequestType::Read:
                {
                    self->HandleRead( instance, static_cast<ReadFileRequest*>( request ) );
                }
                break;
                case FileRequestType::Write:
                {
                    self->HandleWrite( instance, static_cast<WriteFileRequest*>( request ) );
                }
                break;
                case FileRequestType::ReadScatter:
                {
                }
                break;
                case FileRequestType::WriteGather:
                {
                }
                break;
            }
        }
        void HandleRead( const CallbackInstance& instance, ReadFileRequest* request )
        {

        }
        void HandleWrite( const CallbackInstance& instance, WriteFileRequest* request )
        {

        }
    public:
        void BeginRead( ReadFileRequest& request )
        {
            auto handle = request.Handle( );
            Base::Start( );
            auto rc = ReadFile( handle, request.Buffer(), request.NumberOfBytesToRead( ), nullptr, &request );
            if ( !rc )
            {
                auto errorCode = GetLastError( );
                if ( errorCode != ERROR_IO_PENDING )
                {
                    Base::Cancel( );
                    ThrowOSError( errorCode );
                }
            }
        }

        void BeginWrite( WriteFileRequest& request )
        {
            auto handle = request.Handle( );
            Base::Start( );
            auto rc = WriteFile( handle, request.Buffer( ), request.NumberOfBytesToWrite( ), nullptr, &request );
            if ( !rc )
            {
                auto errorCode = GetLastError( );
                if ( errorCode != ERROR_IO_PENDING )
                {
                    Base::Cancel( );
                    ThrowOSError( errorCode );
                }
            }
        }

    };


    class FileDispatcher : public FileHandler<FileDispatcher>
    {
        template<typename DerivedT>
        friend class FileHandler;
    public:
        using Base = FileHandler<FileDispatcher>;
        
        boost::signals2::signal<void( const FileDispatcher& dispatcher, const CallbackInstance& instance, ReadFileRequest* request )> OnRead;
        boost::signals2::signal<void( const FileDispatcher& dispatcher, const CallbackInstance& instance, WriteFileRequest* request )> OnWrite;

        FileDispatcher( HANDLE handle, Environment& environment )
            : Base( handle, environment )
        {
        }

        FileDispatcher( const FileStream& fileStream, Environment& environment )
            : Base( fileStream, environment )
        {
        }

    private:
        void HandleRead( const CallbackInstance& instance, ReadFileRequest* request )
        {
            OnRead( *this, instance, request );
        }
        void HandleWrite( const CallbackInstance& instance, WriteFileRequest* request )
        {
            OnWrite( *this, instance, request );
        }

    };



    template<typename DerivedT>
    class PipeHandler : public IOHandler< DerivedT >
    {
        template<typename DerivedT>
        friend class IOHandler;
    public:
        using Base = IOHandler< DerivedT >;
    private:

    protected:
        PipeHandler( HANDLE handle, Environment& environment )
            : Base( handle, environment )
        {
        }
    public:
    protected:
        void Callback( const CallbackInstance& instance, IO::Request* overlapped, UInt32 ioResult, UInt64 numberOfBytesTransferred )
        {
        }
    };


    enum class SocketRequestType
    {
        Unknown,
        Connect,
        Accept,
        Disconnect,
        Receive,
        ReceiveFrom,
        ReceiveMsg,
        Send,
        SendTo,
        SendMsg
    };

    class SocketRequest : public IORequest
    {
    public:
        using Base = IORequest;
        using Socket = IO::Sockets::Socket;
    private:
        SocketRequestType type_;
    protected:
        SocketRequest( )
            : Base( ), type_( SocketRequestType::Unknown )
        {
        }

        explicit SocketRequest( SOCKET socket, SocketRequestType type, void* context = nullptr )
            : Base( (HANDLE)socket, context ), type_( type )
        {
        }
        explicit SocketRequest( const Socket& socket, SocketRequestType type, void* context = nullptr )
            : Base( (HANDLE)socket.Handle(), context ), type_( type )
        {
        }

    public:
        constexpr SocketRequestType Type( ) const noexcept
        {
            return type_;
        }
    };

    class SocketConnectRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        using AddressType = IO::Sockets::Address;
    private:
        AddressType address_;
        void* buffer_;
        UInt32 numberOfBytesToSend_;
    public:
        explicit SocketConnectRequest( SOCKET socket, const AddressType& addr, void* buffer, UInt32 numberOfBytesToSend, void* context = nullptr ) noexcept
            : Base( socket, SocketRequestType::Connect,context ), address_(addr), buffer_( buffer ), numberOfBytesToSend_( numberOfBytesToSend )
        {
        }
        explicit SocketConnectRequest( SOCKET socket, const struct sockaddr* addr, size_t addrlen, void* buffer, UInt32 numberOfBytesToSend, void* context = nullptr ) noexcept
            : Base( socket, SocketRequestType::Connect, context ), address_( addr, addrlen ), buffer_( buffer ), numberOfBytesToSend_( numberOfBytesToSend )
        {
        }

        explicit SocketConnectRequest( const Socket& socket, const AddressType& addr, void* buffer, UInt32 numberOfBytesToSend, void* context = nullptr ) noexcept
            : Base( socket, SocketRequestType::Connect, context ), address_( addr ), buffer_( buffer ), numberOfBytesToSend_( numberOfBytesToSend )
        {
        }
        explicit SocketConnectRequest( const Socket& socket, const struct sockaddr* addr, size_t addrlen, void* buffer, UInt32 numberOfBytesToSend, void* context = nullptr ) noexcept
            : Base( socket, SocketRequestType::Connect, context ), address_( addr, addrlen ), buffer_( buffer ), numberOfBytesToSend_( numberOfBytesToSend )
        {
        }


        constexpr const AddressType& Address( ) const noexcept
        {
            return address_;
        }

        constexpr void* Buffer( ) const noexcept
        {
            return buffer_;
        }
        UInt32 NumberOfBytesToSend( ) const noexcept
        {
            return numberOfBytesToSend_;
        }

    };

    class SocketAcceptRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        using AddressType = IO::Sockets::Address;
        static constexpr UInt32 MaxLocalAddressLength = sizeof( SOCKADDR_STORAGE ) + 16;
        static constexpr UInt32 MaxRemoteAddressLength = sizeof( SOCKADDR_STORAGE ) + 16;
    private:
        SOCKET acceptSocket_;
        void* buffer_;
        UInt32 receiveDataLength_; 
        UInt32 localAddressLength_; 
        UInt32 remoteAddressLength_;
    public:
        static constexpr UInt32 CalculateBufferSizeFor( UInt32 receiveDataLength )
        {
            return receiveDataLength + MaxLocalAddressLength + MaxRemoteAddressLength;
        }

        explicit SocketAcceptRequest( SOCKET listenSocket, SOCKET acceptSocket, void* buffer, UInt32 receiveDataLength, UInt32 localAddressLength = MaxLocalAddressLength, UInt32 remoteAddressLength = MaxRemoteAddressLength, void* context = nullptr )
            : Base( listenSocket, SocketRequestType::Accept, context ),
              acceptSocket_( acceptSocket ), buffer_(buffer), receiveDataLength_( receiveDataLength ), localAddressLength_( localAddressLength ), remoteAddressLength_( remoteAddressLength )
        {
        }
        explicit SocketAcceptRequest( const Socket& listenSocket, const Socket& acceptSocket, void* buffer, UInt32 receiveDataLength, UInt32 localAddressLength = MaxLocalAddressLength, UInt32 remoteAddressLength = MaxRemoteAddressLength, void* context = nullptr )
            : Base( listenSocket, SocketRequestType::Accept, context ),
              acceptSocket_( acceptSocket.Handle( ) ), buffer_( buffer ), receiveDataLength_( receiveDataLength ), localAddressLength_( localAddressLength ), remoteAddressLength_( remoteAddressLength )
        {
        }

        constexpr SOCKET AcceptSocket( ) const noexcept
        {
            return acceptSocket_;
        }


        constexpr void* Buffer( ) const noexcept
        {
            return buffer_;
        }

        constexpr UInt32 ReceiveDataLength( ) const noexcept
        {
            return receiveDataLength_;
        }
        constexpr UInt32 LocalAddressLength( ) const noexcept
        {
            return localAddressLength_;
        }
        constexpr UInt32 RemoteAddressLength( ) const noexcept
        {
            return remoteAddressLength_;
        }

        void GetAddresses( AddressType& localAddress, AddressType& remoteAddress )
        {
            sockaddr* local = nullptr;
            int localLen = 0;
            sockaddr* remote = nullptr;
            int remoteLen = 0;

            GetAcceptExSockaddrs( buffer_, receiveDataLength_, localAddressLength_, remoteAddressLength_, &local, &localLen, &remote, &remoteLen );
            localAddress.Assign( local, localLen );
            remoteAddress.Assign( remote, remoteLen );
        }


    };

    class SocketDisconnectRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
    private:
        bool reuse_;
    public:
        explicit SocketDisconnectRequest( SOCKET socket, bool reuse, void* context = nullptr )
            : Base( socket, SocketRequestType::Disconnect, context ), reuse_( reuse )
        {
        }
        explicit SocketDisconnectRequest( const Socket& socket, bool reuse, void* context = nullptr )
            : Base( socket, SocketRequestType::Disconnect, context ), reuse_( reuse )
        {
        }

        constexpr bool Reuse( ) const noexcept
        {
            return reuse_;
        }

    };

    class SocketReceiveRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        using MessageFlags = IO::Sockets::MessageFlags;
    private:
        WSABUF* buffers_; 
        UInt32 bufferCount_; 
        MessageFlags flags_;
    public:
        explicit SocketReceiveRequest( SOCKET socket, WSABUF* buffers, UInt32 bufferCount, MessageFlags flags, void* context = nullptr )
            : Base( socket, SocketRequestType::Receive, context ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }
        explicit SocketReceiveRequest( const Socket& socket, WSABUF* buffers, UInt32 bufferCount, MessageFlags flags, void* context = nullptr )
            : Base( socket, SocketRequestType::Receive, context ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }

        constexpr WSABUF* Buffers( ) const noexcept
        {
            return buffers_;
        }
        constexpr UInt32 BufferCount( ) const noexcept
        {
            return bufferCount_;
        }
        constexpr MessageFlags Flags( ) const noexcept
        {
            return flags_;
        }

        constexpr DWORD* FlagsPtr( ) const noexcept
        {
            return (DWORD*)&flags_;
        }

    };

    class SocketReceiveFromRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
    private:

    public:
        explicit SocketReceiveFromRequest( SOCKET socket, void* context = nullptr )
            : Base( socket, SocketRequestType::ReceiveFrom, context )
        {
        }
        explicit SocketReceiveFromRequest( const Socket& socket, void* context = nullptr )
            : Base( socket, SocketRequestType::ReceiveFrom, context )
        {
        }
    };


    class SocketReceiveMsgRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
    private:

    public:
        explicit SocketReceiveMsgRequest( SOCKET socket, void* context = nullptr )
            : Base( socket, SocketRequestType::ReceiveMsg, context )
        {
        }
        explicit SocketReceiveMsgRequest( const Socket& socket, void* context = nullptr )
            : Base( socket, SocketRequestType::ReceiveMsg, context )
        {
        }
    };


    class SocketSendRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        using MessageFlags = IO::Sockets::MessageFlags;
    private:
        WSABUF* buffers_;
        UInt32 bufferCount_;
        MessageFlags flags_;
    public:
        explicit SocketSendRequest( SOCKET socket, WSABUF* buffers, UInt32 bufferCount, MessageFlags flags, void* context = nullptr )
            : Base( socket, SocketRequestType::Send, context ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }
        explicit SocketSendRequest( const Socket& socket, WSABUF* buffers, UInt32 bufferCount, MessageFlags flags, void* context = nullptr )
            : Base( socket, SocketRequestType::Send, context ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }

        constexpr WSABUF* Buffers( ) const noexcept
        {
            return buffers_;
        }
        constexpr UInt32 BufferCount( ) const noexcept
        {
            return bufferCount_;
        }
        constexpr MessageFlags Flags( ) const noexcept
        {
            return flags_;
        }
    };



    class SocketSendToRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
    private:

    public:
        explicit SocketSendToRequest( SOCKET socket, void* context = nullptr )
            : Base( socket, SocketRequestType::SendTo, context )
        {
        }
        explicit SocketSendToRequest( const Socket& socket, void* context = nullptr )
            : Base( socket, SocketRequestType::SendTo, context )
        {
        }
    };


    class SocketSendMsgRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
    private:

    public:
        explicit SocketSendMsgRequest( SOCKET socket, void* context = nullptr )
            : Base( socket, SocketRequestType::SendMsg, context )
        {
        }
        explicit SocketSendMsgRequest( const Socket& socket, void* context = nullptr )
            : Base( socket, SocketRequestType::SendMsg, context )
        {
        }
    };



    template<typename DerivedT>
    class SocketHandler : public IOHandler< DerivedT >
    {
        template<typename DerivedT>
        friend class IOHandler;
    public:
        using Base = IOHandler< DerivedT >;
        using Socket = IO::Sockets::Socket;
        using Address = IO::Sockets::Address;
    private:

    protected:
        SocketHandler( SOCKET socket, Environment& environment )
            : Base( (HANDLE)socket, environment )
        {
        }
        SocketHandler( const Socket& socket, Environment& environment )
            : Base( (HANDLE)socket.Handle(), environment )
        {
        }
    public:
        bool BeginConnect( SocketConnectRequest& request )
        {
            auto completed = false;
            Base::Start( );
            try
            {
                auto socket = (SOCKET)request.Handle( );
                const Address& address = request.Address( );
                auto buffer = request.Buffer( );
                DWORD bytesSent = 0;
                auto numberOfBytesToSend = request.NumberOfBytesToSend( );
                completed = Socket::ConnectEx( socket, address.data( ), address.length( ), buffer, numberOfBytesToSend, nullptr, &request );
                if ( completed )
                {
                    request.SetResult(NO_ERROR, bytesSent );
                    CallbackInstance instance;
                    DerivedT* self = static_cast<DerivedT*>( this );
                    self->HandleConnect( instance, &request );
                }
            }
            catch ( ... )
            {
                Base::Cancel( );
                throw;
            }
            return completed;
        }
        bool BeginAccept( SocketAcceptRequest& request )
        {
            auto completed = false;
            Base::Start( );
            try
            {
                auto listenSocket = (SOCKET)request.Handle( );
                auto acceptSocket = request.AcceptSocket( );
                auto buffer = request.Buffer( );
                DWORD receiveDataLength = request.ReceiveDataLength( );
                DWORD localAddressLength = request.LocalAddressLength( );
                DWORD remoteAddressLength = request.RemoteAddressLength( );
                DWORD bytesReceived = 0;

                completed = Socket::AcceptEx( listenSocket, acceptSocket, buffer, receiveDataLength, localAddressLength, remoteAddressLength, &bytesReceived, &request );
                if ( completed )
                {
                    request.SetResult( NO_ERROR, bytesReceived );
                    CallbackInstance instance;
                    DerivedT* self = static_cast<DerivedT*>( this );
                    self->HandleAccept( instance, &request );
                }
            }
            catch ( ... )
            {
                Base::Cancel( );
                throw;
            }
            return completed;
        }
        bool BeginDisconnect( SocketDisconnectRequest& request )
        {
            auto completed = false;
            Base::Start( );
            try
            {
                auto socket = (SOCKET)request.Handle( );
                bool reuse = request.Reuse( );

                completed = Socket::DisconnectEx( socket, &request, reuse );
                if ( completed )
                {
                    request.SetResult( NO_ERROR, 0 );
                    CallbackInstance instance;
                    DerivedT* self = static_cast<DerivedT*>( this );
                    self->HandleDisconnect( instance, &request );
                }
            }
            catch ( ... )
            {
                Base::Cancel( );
                throw;
            }
            return completed;
        }
        void BeginReceive( SocketReceiveRequest& request )
        {
            Base::Start( );
            try
            {
                auto socket = (SOCKET)request.Handle( );
                auto buffers = request.Buffers( );
                auto bufferCount = request.BufferCount( );
                auto flags = request.FlagsPtr( );

                auto rc = WSARecv( socket, buffers, bufferCount, nullptr ,flags, &request, nullptr );
                if ( rc == SOCKET_ERROR )
                {
                    auto err = IO::Sockets::Socket::LastSocketError( );
                    if ( err != WSA_IO_PENDING )
                    {
                        IO::Sockets::Socket::ThrowSocketError( err );
                    }
                }
            }
            catch ( ... )
            {
                Base::Cancel( );
                throw;
            }
        }

        bool BeginReceiveFrom( SocketReceiveFromRequest& request )
        {

        }

        void BeginSend( SocketSendRequest& request )
        {
            Base::Start( );
            try
            {
                auto socket = (SOCKET)request.Handle( );
                auto buffers = request.Buffers( );
                auto bufferCount = request.BufferCount( );
                auto flags = static_cast<DWORD>( request.Flags( ) );

                auto rc = WSASend( socket, buffers, bufferCount, nullptr, flags, &request, nullptr );
                if ( rc == SOCKET_ERROR )
                {
                    auto err = IO::Sockets::Socket::LastSocketError( );
                    if ( err != WSA_IO_PENDING )
                    {
                        IO::Sockets::Socket::ThrowSocketError( err );
                    }
                }
            }
            catch ( ... )
            {
                Base::Cancel( );
                throw;
            }
        }
        bool BeginSendMsg( SocketSendMsgRequest& request )
        {
        }

    protected:
        void Callback( const CallbackInstance& instance, IO::Request* overlapped, UInt32 ioResult, UInt64 numberOfBytesTransferred )
        {
            SocketRequest* request = static_cast<SocketRequest*>( overlapped );
            DerivedT* self = static_cast<DerivedT*>( this );
            auto requestType = request->Type( );
            switch ( requestType )
            {
                case SocketRequestType::Connect:
                {
                    self->HandleConnect( instance, static_cast<SocketConnectRequest*>( request ) );
                }
                break;
                case SocketRequestType::Accept:
                {
                    self->HandleAccept( instance, static_cast<SocketAcceptRequest*>( request ) );
                }
                break;
                case SocketRequestType::Disconnect:
                {
                    self->HandleDisconnect( instance, static_cast<SocketDisconnectRequest*>( request ) );
                }
                break;
                case SocketRequestType::Receive:
                {
                    self->HandleReceive( instance, static_cast<SocketReceiveRequest*>( request ) );
                }
                break;
                case SocketRequestType::ReceiveFrom:
                {
                    self->HandleReceiveFrom( instance, static_cast<SocketReceiveFromRequest*>( request ) );
                }
                break;
                case SocketRequestType::ReceiveMsg:
                {
                    self->HandleReceiveMsg( instance, static_cast<SocketReceiveMsgRequest*>( request ) );
                }
                break;
                case SocketRequestType::Send:
                {
                    self->HandleSend( instance, static_cast<SocketSendRequest*>( request ) );
                }
                break;
                case SocketRequestType::SendTo:
                {
                    self->HandleSendTo( instance, static_cast<SocketSendToRequest*>( request ) );
                }
                break;
                case SocketRequestType::SendMsg:
                {
                    self->HandleSendMsg( instance, static_cast<SocketSendMsgRequest*>( request ) );
                }
                break;
            }
        }

        void HandleConnect( const CallbackInstance& instance, SocketConnectRequest* request )
        {

        }
        void HandleAccept( const CallbackInstance& instance, SocketAcceptRequest* request )
        {

        }
        void HandleDisconnect( const CallbackInstance& instance, SocketDisconnectRequest* request )
        {

        }
        void HandleReceive( const CallbackInstance& instance, SocketReceiveRequest* request )
        {

        }

        void HandleReceiveFrom( const CallbackInstance& instance, SocketReceiveFromRequest* request )
        {

        }

        void HandleReceiveMsg( const CallbackInstance& instance, SocketReceiveMsgRequest* request )
        {

        }

        void HandleSend( const CallbackInstance& instance, SocketSendRequest* request )
        {

        }

        void HandleSendTo( const CallbackInstance& instance, SocketSendToRequest* request )
        {

        }

        void HandleSendMsg( const CallbackInstance& instance, SocketSendMsgRequest* request )
        {

        }
    };


    class SocketDispatcher : public SocketHandler<SocketDispatcher>
    {
        template<typename DerivedT>
        friend class SocketHandler;
    public:
        using Base = SocketHandler<SocketDispatcher>;

        boost::signals2::signal<void( const SocketDispatcher& dispatcher, const CallbackInstance& instance, SocketConnectRequest* request )> OnConnect;
        boost::signals2::signal<void( const SocketDispatcher& dispatcher, const CallbackInstance& instance, SocketAcceptRequest* request )> OnAccept;
        boost::signals2::signal<void( const SocketDispatcher& dispatcher, const CallbackInstance& instance, SocketDisconnectRequest* request )> OnDisconnect;
        boost::signals2::signal<void( const SocketDispatcher& dispatcher, const CallbackInstance& instance, SocketReceiveRequest* request )> OnReceive;
        boost::signals2::signal<void( const SocketDispatcher& dispatcher, const CallbackInstance& instance, SocketReceiveFromRequest* request )> OnReceiveFrom;
        boost::signals2::signal<void( const SocketDispatcher& dispatcher, const CallbackInstance& instance, SocketReceiveMsgRequest* request )> OnReceiveMsg;
        boost::signals2::signal<void( const SocketDispatcher& dispatcher, const CallbackInstance& instance, SocketSendRequest* request )> OnSend;
        boost::signals2::signal<void( const SocketDispatcher& dispatcher, const CallbackInstance& instance, SocketSendToRequest* request )> OnSendTo;
        boost::signals2::signal<void( const SocketDispatcher& dispatcher, const CallbackInstance& instance, SocketSendMsgRequest* request )> OnSendMsg;

        SocketDispatcher( SOCKET socket, Environment& environment )
            : Base( socket, environment )
        {
        }
        SocketDispatcher( const Socket& socket, Environment& environment )
            : Base( socket, environment )
        {
        }

    private:
        void HandleConnect( const CallbackInstance& instance, SocketConnectRequest* request )
        {
            OnConnect( *this, instance, request );
        }
        void HandleAccept( const CallbackInstance& instance, SocketAcceptRequest* request )
        {
            OnAccept( *this, instance, request );
        }
        void HandleDisconnect( const CallbackInstance& instance, SocketDisconnectRequest* request )
        {
            OnDisconnect( *this, instance, request );
        }
        void HandleReceive( const CallbackInstance& instance, SocketReceiveRequest* request )
        {
            OnReceive( *this, instance, request );
        }

        void HandleReceiveFrom( const CallbackInstance& instance, SocketReceiveFromRequest* request )
        {
            OnReceiveFrom( *this, instance, request );
        }

        void HandleReceiveMsg( const CallbackInstance& instance, SocketReceiveMsgRequest* request )
        {
            OnReceiveMsg( *this, instance, request );
        }

        void HandleSend( const CallbackInstance& instance, SocketSendRequest* request )
        {
            OnSend( *this, instance, request );
        }

        void HandleSendTo( const CallbackInstance& instance, SocketSendToRequest* request )
        {
            OnSendTo( *this, instance, request );
        }

        void HandleSendMsg( const CallbackInstance& instance, SocketSendMsgRequest* request )
        {
            OnSendMsg( *this, instance, request );
        }

    };


    template<typename DerivedT>
    class HttpHandler : public IOHandler< DerivedT >
    {
        template<typename DerivedT>
        friend class IOHandler;
    public:
        using Base = IOHandler< DerivedT >;
    private:

    protected:
        HttpHandler( HANDLE handle, Environment& environment )
            : Base( handle, environment )
        {
        }
    public:
    protected:
        void Callback( const CallbackInstance& instance, IO::Request* overlapped, UInt32 ioResult, UInt64 numberOfBytesTransferred )
        {
        }
    };
    */


}

#endif
