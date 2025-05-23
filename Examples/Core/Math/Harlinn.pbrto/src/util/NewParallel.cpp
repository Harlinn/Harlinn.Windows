#include "pch.h"

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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/util/NewParallel.h>
#include <pbrto/util/NewLog.h>

#include <pbrto/util/NewCheck.h>
#ifdef PBRT_BUILD_GPU_RENDERER
#include <pbrto/gpu/util.h>
#endif  // PBRT_BUILD_GPU_RENDERER

#include <algorithm>
#include <iterator>
#include <list>
#include <thread>
#include <vector>

namespace pbrto
{

    std::string AtomicFloat::ToString( ) const
    {
        return StringPrintf( "%f", float( *this ) );
    }

    std::string AtomicDouble::ToString( ) const
    {
        return StringPrintf( "%f", double( *this ) );
    }

    // Barrier Method Definitions
    bool Barrier::Block( )
    {
        std::unique_lock<std::mutex> lock( mutex );

        --numToBlock;
        NCHECK_GE( numToBlock, 0 );

        if ( numToBlock > 0 )
        {
            cv.wait( lock, [ this ]( ) { return numToBlock == 0; } );
        }
        else
            cv.notify_all( );

        return --numToExit == 0;
    }

    ThreadPool* ParallelJob::threadPool;

    // ThreadPool Method Definitions
    ThreadPool::ThreadPool( int nThreads )
    {
        for ( int i = 0; i < nThreads - 1; ++i )
            threads.push_back( std::thread( &ThreadPool::Worker, this ) );
    }

    void ThreadPool::Worker( )
    {
        NLOG_VERBOSE( "Started execution in worker thread" );

#ifdef PBRT_BUILD_GPU_RENDERER
        GPUThreadInit( );
#endif  // PBRT_BUILD_GPU_RENDERER

        std::unique_lock<std::mutex> lock( mutex );
        while ( !shutdownThreads )
            WorkOrWait( &lock, false );

        NLOG_VERBOSE( "Exiting worker thread" );
    }

    std::unique_lock<std::mutex> ThreadPool::AddToJobList( ParallelJob* job )
    {
        std::unique_lock<std::mutex> lock( mutex );
        // Add _job_ to head of _jobList_
        if ( jobList )
            jobList->prev = job;
        job->next = jobList;
        jobList = job;

        jobListCondition.notify_all( );
        return lock;
    }

    void ThreadPool::WorkOrWait( std::unique_lock<std::mutex>* lock, bool isEnqueuingThread )
    {
        NDCHECK( lock->owns_lock( ) );
        // Return if this is a worker thread and the thread pool is disabled
        if ( !isEnqueuingThread && disabled )
        {
            jobListCondition.wait( *lock );
            return;
        }

        ParallelJob* job = jobList;
        while ( job && !job->HaveWork( ) )
            job = job->next;
        if ( job )
        {
            // Execute work for _job_
            job->activeWorkers++;
            job->RunStep( lock );
            // Handle post-job-execution details
            NDCHECK( !lock->owns_lock( ) );
            lock->lock( );
            job->activeWorkers--;
            if ( job->Finished( ) )
                jobListCondition.notify_all( );

        }
        else
            // Wait for new work to arrive or the job to finish
            jobListCondition.wait( *lock );
    }

    void ThreadPool::RemoveFromJobList( ParallelJob* job )
    {
        NDCHECK( !job->removed );

        if ( job->prev )
            job->prev->next = job->next;
        else
        {
            NDCHECK( jobList == job );
            jobList = job->next;
        }
        if ( job->next )
            job->next->prev = job->prev;

        job->removed = true;
    }

    bool ThreadPool::WorkOrReturn( )
    {
        std::unique_lock<std::mutex> lock( mutex );

        ParallelJob* job = jobList;
        while ( job && !job->HaveWork( ) )
            job = job->next;
        if ( !job )
            return false;

        // Execute work for _job_
        job->activeWorkers++;
        job->RunStep( &lock );
        NDCHECK( !lock.owns_lock( ) );
        lock.lock( );
        job->activeWorkers--;
        if ( job->Finished( ) )
            jobListCondition.notify_all( );

        return true;
    }

    void ThreadPool::ForEachThread( std::function<void( void )> func )
    {
        Barrier* barrier = new Barrier( threads.size( ) + 1 );

        ParallelFor( 0, threads.size( ) + 1, [ barrier, &func ]( int64_t ) {
            func( );
            if ( barrier->Block( ) )
                delete barrier;
            } );
    }

    void ThreadPool::Disable( )
    {
        NCHECK( !disabled );
        disabled = true;
        NCHECK( jobList == nullptr );  // Nothing should be running when Disable() is called.
    }

    void ThreadPool::Reenable( )
    {
        NCHECK( disabled );
        disabled = false;
    }

    ThreadPool::~ThreadPool( )
    {
        if ( threads.empty( ) )
            return;

        {
            std::lock_guard<std::mutex> lock( mutex );
            shutdownThreads = true;
            jobListCondition.notify_all( );
        }

        for ( std::thread& thread : threads )
            thread.join( );
    }

    std::string ThreadPool::ToString( ) const
    {
        std::string s = StringPrintf( "[ ThreadPool threads.size(): %d shutdownThreads: %s ",
            threads.size( ), shutdownThreads );
        if ( mutex.try_lock( ) )
        {
            s += "jobList: [ ";
            ParallelJob* job = jobList;
            while ( job )
            {
                s += job->ToString( ) + " ";
                job = job->next;
            }
            s += "] ";
            mutex.unlock( );
        }
        else
            s += "(job list mutex locked) ";
        return s + "]";
    }

    bool DoParallelWork( )
    {
        NCHECK( ParallelJob::threadPool );
        // lock should be held when this is called...
        return ParallelJob::threadPool->WorkOrReturn( );
    }

    // ParallelForLoop1D Definition
    class ParallelForLoop1D : public ParallelJob
    {
    public:
        // ParallelForLoop1D Public Methods
        ParallelForLoop1D( int64_t startIndex, int64_t endIndex, int chunkSize,
            std::function<void( int64_t, int64_t )> func )
            : func( std::move( func ) ),
            nextIndex( startIndex ),
            endIndex( endIndex ),
            chunkSize( chunkSize )
        {
        }

        bool HaveWork( ) const { return nextIndex < endIndex; }

        void RunStep( std::unique_lock<std::mutex>* lock );

        std::string ToString( ) const
        {
            return StringPrintf( "[ ParallelForLoop1D nextIndex: %d endIndex: %d "
                "chunkSize: %d ]",
                nextIndex, endIndex, chunkSize );
        }

    private:
        // ParallelForLoop1D Private Members
        std::function<void( int64_t, int64_t )> func;
        int64_t nextIndex, endIndex;
        int chunkSize;
    };

    class ParallelForLoop2D : public ParallelJob
    {
    public:
        ParallelForLoop2D( const Bounds2i& extent, int chunkSize,
            std::function<void( Bounds2i )> func )
            : func( std::move( func ) ),
            extent( extent ),
            nextStart( extent.pMin ),
            chunkSize( chunkSize )
        {
        }

        bool HaveWork( ) const { return nextStart.y < extent.pMax.y; }
        void RunStep( std::unique_lock<std::mutex>* lock );

        std::string ToString( ) const
        {
            return StringPrintf( "[ ParallelForLoop2D extent: %s nextStart: %s "
                "chunkSize: %d ]",
                extent, nextStart, chunkSize );
        }

    private:
        std::function<void( Bounds2i )> func;
        const Bounds2i extent;
        Point2i nextStart;
        int chunkSize;
    };

    // ParallelForLoop1D Method Definitions
    void ParallelForLoop1D::RunStep( std::unique_lock<std::mutex>* lock )
    {
        // Determine the range of loop iterations to run in this step
        int64_t indexStart = nextIndex;
        int64_t indexEnd = std::min( indexStart + chunkSize, endIndex );
        nextIndex = indexEnd;

        // Remove job from list if all work has been started
        if ( !HaveWork( ) )
            threadPool->RemoveFromJobList( this );

        // Release lock and execute loop iterations in _[indexStart, indexEnd)_
        lock->unlock( );
        func( indexStart, indexEnd );
    }

    void ParallelForLoop2D::RunStep( std::unique_lock<std::mutex>* lock )
    {
        // Compute extent for this step
        Point2i end = nextStart + Vector2i( chunkSize, chunkSize );
        Bounds2i b = Intersect( Bounds2i( nextStart, end ), extent );
        NCHECK( !b.IsEmpty( ) );

        // Advance to be ready for the next extent.
        nextStart.x += chunkSize;
        if ( nextStart.x >= extent.pMax.x )
        {
            nextStart.x = extent.pMin.x;
            nextStart.y += chunkSize;
        }

        if ( !HaveWork( ) )
            threadPool->RemoveFromJobList( this );

        lock->unlock( );

        // Run the loop iteration
        func( b );
    }

    // Parallel Function Definitions
    PBRTO_EXPORT void ParallelFor( int64_t start, int64_t end, std::function<void( int64_t, int64_t )> func )
    {
        NCHECK( ParallelJob::threadPool );
        if ( start == end )
            return;
        // Compute chunk size for parallel loop
        int64_t chunkSize = std::max<int64_t>( 1, ( end - start ) / ( 8 * RunningThreads( ) ) );

        // Create and enqueue _ParallelForLoop1D_ for this loop
        ParallelForLoop1D loop( start, end, chunkSize, std::move( func ) );
        std::unique_lock<std::mutex> lock = ParallelJob::threadPool->AddToJobList( &loop );

        // Help out with parallel loop iterations in the current thread
        while ( !loop.Finished( ) )
            ParallelJob::threadPool->WorkOrWait( &lock, true );
    }

    PBRTO_EXPORT void ParallelFor2D( const Bounds2i& extent, std::function<void( Bounds2i )> func )
    {
        NCHECK( ParallelJob::threadPool );

        if ( extent.IsEmpty( ) )
            return;
        if ( extent.Area( ) == 1 )
        {
            func( extent );
            return;
        }

        // Want at least 8 tiles per thread, subject to not too big and not too
        // small.
        // TODO: should we do non-square?
        int tileSize = Clamp( int( Math::Sqrt( static_cast< float >( extent.Diagonal( ).x * extent.Diagonal( ).y /
            ( 8 * RunningThreads( ) ) ) ) ),
            1, 32 );

        ParallelForLoop2D loop( extent, tileSize, std::move( func ) );
        std::unique_lock<std::mutex> lock = ParallelJob::threadPool->AddToJobList( &loop );

        // Help out with parallel loop iterations in the current thread
        while ( !loop.Finished( ) )
            ParallelJob::threadPool->WorkOrWait( &lock, true );
    }

    ///////////////////////////////////////////////////////////////////////////

    PBRTO_EXPORT int AvailableCores( )
    {
        return std::max<int>( 1, std::thread::hardware_concurrency( ) );
    }

    PBRTO_EXPORT int RunningThreads( )
    {
        return ParallelJob::threadPool ? ( 1 + ParallelJob::threadPool->size( ) ) : 1;
    }

    PBRTO_EXPORT void ParallelInit( int nThreads )
    {
        NCHECK( !ParallelJob::threadPool );
        if ( nThreads <= 0 )
            nThreads = AvailableCores( );
        ParallelJob::threadPool = new ThreadPool( nThreads );
    }

    PBRTO_EXPORT void ParallelCleanup( )
    {
        delete ParallelJob::threadPool;
        ParallelJob::threadPool = nullptr;
    }

    PBRTO_EXPORT void ForEachThread( std::function<void( void )> func )
    {
        if ( ParallelJob::threadPool )
            ParallelJob::threadPool->ForEachThread( std::move( func ) );
    }

    PBRTO_EXPORT void DisableThreadPool( )
    {
        NCHECK( ParallelJob::threadPool );
        ParallelJob::threadPool->Disable( );
    }

    PBRTO_EXPORT void ReenableThreadPool( )
    {
        NCHECK( ParallelJob::threadPool );
        ParallelJob::threadPool->Reenable( );
    }

}