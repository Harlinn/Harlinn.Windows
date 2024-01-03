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



using namespace Harlinn::Common::Core;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( ThreadTests, LocalFixture )


// --run_test=ThreadTests/RunThreadTest1
BOOST_AUTO_TEST_CASE( RunThreadTest1 )
{
    EventWaitHandle event1( true );
    EventWaitHandle event2( true );
    Thread thread( [&event1, &event2]( )
    {
        event1.Signal( );
        event2.Wait( );
    } );
    BOOST_CHECK( thread.GetHandle( ) != nullptr );
    BOOST_CHECK( event1.Wait( ) );
    event2.Signal( );
    BOOST_CHECK( thread.Wait( ) );
}


// --run_test=ThreadTests/RunThreadTest2
BOOST_AUTO_TEST_CASE( RunThreadTest2 )
{
    size_t counter = 0;
    Mutex mutex( true );
    ThreadGroup threadGroup;
    for ( int i = 0; i < 100; ++i )
    {
        threadGroup.Add( [i, &mutex, &counter]( )
        {
            auto id = i + 1;
            for ( int i = 0; i < 10; ++i )
            {
                std::unique_lock lock( mutex );
                ++counter;
            }
        } );
    }
    mutex.unlock( );
    threadGroup.join();
    BOOST_CHECK( counter == 1000 );
}

// --run_test=ThreadTests/RunThreadTest3
BOOST_AUTO_TEST_CASE( RunThreadTest3 )
{
    size_t counter = 0;
    Spinlock spinlock;
    spinlock.lock( );
    ThreadGroup threadGroup;
    for ( int i = 0; i < 10; ++i )
    {
        threadGroup.Add( [i, &spinlock, &counter]( )
        {
            auto id = i + 1;
            for ( int i = 0; i < 100; ++i )
            {
                std::unique_lock lock( spinlock );
                ++counter;
            }
        } );
    }
    spinlock.unlock( );
    threadGroup.join( );
    BOOST_CHECK( counter == 1000 );
}


// --run_test=ThreadTests/RunThreadTest4a
BOOST_AUTO_TEST_CASE( RunThreadTest4a )
{
    EventWaitHandle event( true );
    WaitableTimer timer(true, false ,TimeSpan::FromSeconds( 5 ) );
    Thread thread( [&timer, &event]( )
    {
        timer.Wait( );
        event.Signal( );
    } );
    BOOST_CHECK( event.Wait( ) );
    BOOST_CHECK( thread.Wait( ) );
}


// --run_test=ThreadTests/RunThreadTest4b
BOOST_AUTO_TEST_CASE( RunThreadTest4b )
{
    constexpr size_t Iterations = 10000;
    EventWaitHandle event( true );
    WaitableTimer timer( false, true, TimeSpan::FromMilliseconds( 3 ), TimeSpan::FromMilliseconds( 3 ) );
    std::array<Stopwatch, Iterations> stopwatches;
    Thread thread( [&timer, &event,&stopwatches]( )
    {
        CurrentThread::SetPriority( ThreadPriority::TimeCritical );
        for ( size_t i = 0; i < Iterations; i++ )
        {
            stopwatches[i].Start( );
            timer.Wait( );
            stopwatches[i].Stop( );
        }
        CurrentThread::SetPriority( ThreadPriority::Normal );
        event.Signal( );
    } );
    BOOST_CHECK( event.Wait( ) );
    BOOST_CHECK( thread.Wait( ) );

    double minWaitTime = std::numeric_limits<double>::max();
    double maxWaitTime = 0;
    double totalDuration = 0.0;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto duration = stopwatches[i].TotalSeconds( );
        totalDuration += duration;
        if ( duration < minWaitTime && i != 0)
        {
            minWaitTime = duration;
        }
        if ( duration > maxWaitTime )
        {
            maxWaitTime = duration;
        }
    }
    double averageDuration = totalDuration / Iterations;

    printf("Total wait time: %f, average wait time %f, min wait time %f, max wait time %f\n" , totalDuration, averageDuration, minWaitTime, maxWaitTime );

}



namespace ResourceManager
{
    struct Resource
    {
        long long counter_ = 0;
    };

    class Resources
    {
        constexpr static size_t ResourceCount = 5;
        Semaphore semaphore_;
        Mutex mutex_;
        std::array<Resource, ResourceCount> resources_;
        std::list< Resource* > freeList_;
    public:
        Resources( )
            : semaphore_( ResourceCount, ResourceCount ), mutex_( false )
        {
            for ( auto& r : resources_ )
            {
                freeList_.push_back( &r );
            }
        }
        Resource* GetResource( )
        {
            if ( semaphore_.Wait( ) )
            {
                std::unique_lock lock( mutex_ );
                auto* result = freeList_.back( );
                freeList_.pop_back( );
                return result;
            }
            return nullptr;
        }
        void Release( Resource* r )
        {
            std::unique_lock lock( mutex_ );
            freeList_.push_back( r );
            semaphore_.Release( );
        }
        size_t Sum( ) const
        {
            size_t result = 0;
            for ( auto& r : resources_ )
            {
                result += r.counter_;
            }
            return result;
        }
    };
}

// --run_test=ThreadTests/RunThreadTest5
BOOST_AUTO_TEST_CASE( RunThreadTest5 )
{
    using namespace ResourceManager;
    Resources resources;

    ThreadGroup threadGroup;
    for ( int i = 0; i < 100; ++i )
    {
        threadGroup.Add( [i, &resources]( )
        {
            auto id = i + 1;
            for ( int i = 0; i < 10; ++i )
            {
                auto* r = resources.GetResource( );
                r->counter_++;
                resources.Release( r );
            }
        } );
    }
    threadGroup.join( );
    auto sum = resources.Sum( );
    BOOST_CHECK( sum == 1000 );
}



class SimpleQueue
{
    ConditionVariable queueEmpty_;
    ConditionVariable queueFull_;
    CriticalSection criticalSection_;
    size_t lastItemProduced_ = 0;
    size_t queueSize_ = 0;
    size_t startOffset_ = 0;
    bool closed_ = false;
public:
    static constexpr size_t MaxQueueSize = 50;
    using Container = std::array<size_t, MaxQueueSize>;
private:
    Container conatainer_;
public:
    SimpleQueue( )
        : conatainer_{}
    {
    }

    void Close( )
    {
        {
            std::unique_lock lock( criticalSection_ );
            closed_ = true;
        }
        queueEmpty_.WakeAll( );
        queueFull_.WakeAll( );
    }

    bool Push( size_t item )
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
    size_t PopValue( )
    {
        auto result = conatainer_[startOffset_];

        queueSize_--;
        startOffset_++;

        if ( startOffset_ == MaxQueueSize )
        {
            startOffset_ = 0;
        }
        return result;
    }
public:
    bool Pop( size_t& item )
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
            if( queueSize_ )
            {
                item = PopValue( );
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


// --run_test=ThreadTests/RunThreadTest6
BOOST_AUTO_TEST_CASE( RunThreadTest6 )
{
    SimpleQueue queue;
    std::atomic<size_t> generated;
    std::atomic<size_t> consumed;
    ThreadGroup producerThreadGroup;
    ThreadGroup consumerThreadGroup;

    for ( int i = 0; i < 4; ++i )
    {
        producerThreadGroup.Add( [i , &queue,&generated]( )
        {
            while ( queue.Push( 1 ) )
            {
                ++generated;
            }
        } );
    }
    for ( int i = 0; i < 4; ++i )
    {
        consumerThreadGroup.Add( [i, &queue, &consumed]( )
        {
            size_t value = 0;
            while ( queue.Pop( value ) )
            {
                ++consumed;
            }
        } );
    }

    CurrentThread::Sleep( TimeSpan::FromSeconds( 2 ) );
    queue.Close( );
    producerThreadGroup.join( );
    consumerThreadGroup.join( );
    size_t sent = generated;
    size_t received = consumed;
    BOOST_CHECK( sent == received );
}


// --run_test=ThreadTests/RunThreadTest7
BOOST_AUTO_TEST_CASE( RunThreadTest7 )
{
    size_t counter = 0;
    CriticalSection criticalSection;
    criticalSection.Enter( );
    ThreadGroup threadGroup;
    for ( int i = 0; i < 100; ++i )
    {
        threadGroup.Add( [i, &criticalSection, &counter]( )
        {
            auto id = i + 1;
            for ( int i = 0; i < 10; ++i )
            {
                std::unique_lock lock( criticalSection );
                ++counter;
            }
        } );
    }
    criticalSection.Leave( );
    threadGroup.join( );
    BOOST_CHECK( counter == 1000 );
}



// --run_test=ThreadTests/RunThreadTest8
BOOST_AUTO_TEST_CASE( RunThreadTest8 )
{
    constexpr size_t ThreadCount = 4;
    constexpr size_t ThreadIterationCount = 400'000;
    struct Data
    {
        Spinlock spinlock;
        size_t counter = 0;
    };
    Data data;
    std::array<size_t, ThreadCount> threadCounters = {};
    
    ThreadGroup threadGroup;
    for ( size_t i = 0; i < ThreadCount; ++i )
    {
        threadGroup.Add( [i, &data,&threadCounters]( )
        {
            for ( size_t j = 0; j < ThreadIterationCount; ++j )
            {
                std::unique_lock lock( data.spinlock );
                data.counter++;
                threadCounters[i]++;
            }
        } );
    }
    threadGroup.join( );

    BOOST_CHECK( data.counter == (ThreadIterationCount * ThreadCount) );
    for ( size_t i = 0; i < ThreadCount; ++i )
    {
        BOOST_CHECK( threadCounters[i] == ThreadIterationCount );
    }
}






// --run_test=ThreadTests/RunThreadTest9
BOOST_AUTO_TEST_CASE( RunThreadTest9 )
{
    Thread thread( []( ) { return 5; } );
    thread.join( );
    auto exitCode = thread.ExitCode( );
    BOOST_CHECK( exitCode == 5 );
}







BOOST_AUTO_TEST_SUITE_END( )