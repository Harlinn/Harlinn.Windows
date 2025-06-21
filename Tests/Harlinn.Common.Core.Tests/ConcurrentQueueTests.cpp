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
#include "pch.h"
#include <HCCConcurrentQueue.h>

using namespace Harlinn::Common;
using namespace Harlinn::Common::Core;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) = default;
        ~LocalFixture( ) = default;
    };
}

BOOST_FIXTURE_TEST_SUITE( ConcurrentQueueTests, LocalFixture )

// --run_test=ConcurrentQueueTests/MPMCTest1
BOOST_AUTO_TEST_CASE( MPMCTest1 )
{
    constexpr size_t MessagesPerProducerCount = 10000;
    constexpr size_t ProducerCount = 10;
    constexpr size_t TotalExpectedMessageCount = ProducerCount * MessagesPerProducerCount;
    constexpr size_t ConsumerCount = 10;

    struct Message
    {
        size_t Id = 0;
        size_t Value = 0;
        Message( ) = default;
        Message( size_t v ) 
            : Id(v), Value(v)
        { }

    };
    using MessagePtr = std::unique_ptr<Message>;


    ConcurrentQueue<MessagePtr> queue;
    std::atomic<size_t> messagesConsumedCount;
    ThreadGroup threadGroup;
    for ( UInt32 i = 0; i < ConsumerCount; ++i )
    {
        threadGroup.Add( [&queue, &messagesConsumedCount]( )
        {
            MessagePtr messagePtr;
            
            while ( true )
            {
                if ( queue.try_dequeue( messagePtr ) )
                {
                    if ( messagePtr->Id == 0 )
                    {
                        ++messagesConsumedCount;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            
        } );
    }

    for ( UInt32 i = 0; i < ProducerCount; ++i )
    {
        threadGroup.Add( [&queue, MessagesPerProducerCount]( )
        {
            for ( size_t i = 0; i < MessagesPerProducerCount; ++i )
            {
                auto message = std::make_unique<Message>( );
                queue.enqueue( std::move( message ) );
            }
            auto message = std::make_unique<Message>(1);
            queue.enqueue( std::move( message ) );
        } );
    }
    threadGroup.join( );

    BOOST_CHECK( messagesConsumedCount.load( ) == TotalExpectedMessageCount );
}

// --run_test=ConcurrentQueueTests/MPMCTest2
BOOST_AUTO_TEST_CASE( MPMCTest2 )
{
    constexpr size_t MessagesPerProducerCount = 1000000;
    constexpr size_t ProducerCount = 10;
    constexpr size_t TotalExpectedMessageCount = ProducerCount * MessagesPerProducerCount;
    constexpr size_t ConsumerCount = 10;

    struct Message
    {
        size_t Id = 0;
        size_t Value = 0;
    };

    ConcurrentQueue<Message> queue;
    ThreadGroup threadGroup;
    double totalSeconds[ConsumerCount] = {};
    size_t totalMessagesConsumed[ConsumerCount] = {};

    for ( UInt32 i = 0; i < ConsumerCount; ++i )
    {
        double* seconds = &totalSeconds[i];
        size_t* messagesConsumed = &totalMessagesConsumed[i];
        threadGroup.Add( [&queue, seconds, messagesConsumed]( )
        {
            size_t messagesConsumedCount = 0;
            Message message;
            Stopwatch stopwatch;

            bool waitingForFirstMessage = true;
            bool running = true;

            while ( running && waitingForFirstMessage )
            {
                if ( queue.try_dequeue( message ) )
                {
                    waitingForFirstMessage = false;
                    if ( message.Id == 0 )
                    {
                        stopwatch.Start( );
                        ++messagesConsumedCount;
                    }
                    else
                    {
                        running = false;
                    }
                }
            }

            while ( running )
            {
                if ( queue.try_dequeue( message ) )
                {
                    if ( message.Id == 0 )
                    {
                        ++messagesConsumedCount;
                    }
                    else
                    {
                        running = false;
                    }
                }
            }

            stopwatch.Stop( );
            *seconds = stopwatch.Elapsed( ).TotalSeconds( );
            *messagesConsumed = messagesConsumedCount;

        } );
    }
    for ( UInt32 i = 0; i < ProducerCount; ++i )
    {
        threadGroup.Add( [&queue, MessagesPerProducerCount]( )
        {
            Message message;
            for ( size_t i = 0; i < MessagesPerProducerCount; ++i )
            {
                queue.enqueue( message );
            }
            message.Id = 1;
            queue.enqueue( message );
        } );
    }
    threadGroup.join( );

    size_t messagesConsumedCount = 0;
    double totalTime = 0.0;

    for ( UInt32 i = 0; i < ConsumerCount; ++i )
    {
        messagesConsumedCount += totalMessagesConsumed[i];
        totalTime += totalSeconds[i];
    }

    printf( "ConcurrentQueue: Consumed %zu messages in %f seconds\n", messagesConsumedCount, totalTime );

    BOOST_CHECK( messagesConsumedCount == TotalExpectedMessageCount );
}


// --run_test=ConcurrentQueueTests/MPMCTest3
BOOST_AUTO_TEST_CASE( MPMCTest3 )
{
    constexpr size_t MessagesPerProducerCount = 1000000;
    constexpr size_t ProducerCount = 10;
    constexpr size_t TotalExpectedMessageCount = ProducerCount * MessagesPerProducerCount;
    constexpr size_t ConsumerCount = 10;

    struct Message
    {
        size_t Id = 0;
        size_t Value = 0;
    };

    BlockingConcurrentQueue<Message> queue;
    ThreadGroup threadGroup;
    double totalSeconds[ConsumerCount] = {};
    size_t totalMessagesConsumed[ConsumerCount] = {};

    for ( UInt32 i = 0; i < ConsumerCount; ++i )
    {
        double* seconds = &totalSeconds[i];
        size_t* messagesConsumed = &totalMessagesConsumed[i];
        threadGroup.Add( [&queue, seconds, messagesConsumed]( )
        {
            bool running = true;
            size_t messagesConsumedCount = 0;
            Message message;
            queue.wait_dequeue( message );
            if ( message.Id == 1 )
            {
                running = false;
            }
            else
            {
                ++messagesConsumedCount;
            }
            Stopwatch stopwatch;
            stopwatch.Start( );

            
            while ( running )
            {
                queue.wait_dequeue( message );
                if ( message.Id == 1 )
                {
                    running = false;
                }
                else
                {
                    ++messagesConsumedCount;
                }
            }
            stopwatch.Stop( );
            *seconds = stopwatch.Elapsed( ).TotalSeconds( );
            *messagesConsumed = messagesConsumedCount;
        } );
    }
    for ( UInt32 i = 0; i < ProducerCount; ++i )
    {
        threadGroup.Add( [&queue, MessagesPerProducerCount]( )
        {
            Message message;
            for ( size_t i = 0; i < MessagesPerProducerCount; ++i )
            {
                queue.enqueue( message );
            }
            message.Id = 1;
            queue.enqueue( message );
        } );
    }
    threadGroup.join( );

    size_t messagesConsumedCount = 0;
    double totalTime = 0.0;

    for ( UInt32 i = 0; i < ConsumerCount; ++i )
    {
        messagesConsumedCount += totalMessagesConsumed[i];
        totalTime += totalSeconds[i];
    }

    printf( "ConcurrentQueue: Consumed %zu messages in %f seconds\n", messagesConsumedCount, totalTime );

    BOOST_CHECK( messagesConsumedCount == TotalExpectedMessageCount );
}

// --run_test=ConcurrentQueueTests/MPMCTest4
BOOST_AUTO_TEST_CASE( MPMCTest4 )
{
    constexpr size_t MessagesPerProducerCount = 1000000;
    constexpr size_t ProducerCount = 10;
    constexpr size_t EnqueueMessageCount = 3;
    constexpr size_t TotalExpectedMessageCount = ProducerCount * MessagesPerProducerCount;
    constexpr size_t ConsumerCount = 2;
    constexpr size_t DequeueMessageCount = 71;

    struct Message
    {
        size_t Id = 0;
        size_t Value = 0;
    };

    BlockingConcurrentQueue<Message> queue;
    ThreadGroup threadGroup;
    double totalSeconds[ConsumerCount] = {};
    size_t totalMessagesConsumed[ConsumerCount] = {};

    for ( UInt32 i = 0; i < ConsumerCount; ++i )
    {
        double* seconds = &totalSeconds[i];
        size_t* messagesConsumed = &totalMessagesConsumed[i];
        threadGroup.Add( [&queue, seconds, messagesConsumed]( )
        {
            Stopwatch stopwatch;
            size_t messagesConsumedCount = 0;
            Message messages[DequeueMessageCount];
            auto count = queue.wait_dequeue_bulk( messages, DequeueMessageCount );
            bool running = count > 0;
            stopwatch.Start( );
            if ( running )
            {
                messagesConsumedCount += count;
            }

            while ( running )
            {
                count = queue.wait_dequeue_bulk( messages, DequeueMessageCount );
                running = count > 0;
                if ( running )
                {
                    messagesConsumedCount += count;
                }
            }
            stopwatch.Stop( );
            *seconds = stopwatch.Elapsed( ).TotalSeconds( );
            *messagesConsumed = messagesConsumedCount;
        } );
    }

    SynchronizationBarrier barrier( ProducerCount );
    for ( UInt32 i = 0; i < ProducerCount; ++i )
    {
        threadGroup.Add( [&queue, &barrier, MessagesPerProducerCount]( )
        {
            Message messages[EnqueueMessageCount];
            size_t fullInsertIterations = MessagesPerProducerCount / EnqueueMessageCount;
            size_t remainder = MessagesPerProducerCount % EnqueueMessageCount;
            for ( size_t i = 0; i < fullInsertIterations; ++i )
            {
                queue.enqueue_bulk( messages, EnqueueMessageCount );
            }
            if ( remainder )
            {
                queue.enqueue_bulk( messages, remainder );
            }
            if ( barrier.Enter( ) )
            {
                queue.Close( );
            }
        } );
    }
    threadGroup.join( );

    size_t messagesConsumedCount = 0;
    double totalTime = 0.0;

    for ( UInt32 i = 0; i < ConsumerCount; ++i )
    {
        messagesConsumedCount += totalMessagesConsumed[i];
        totalTime += totalSeconds[i];
    }

    printf( "ConcurrentQueue: Consumed %zu messages in %f seconds\n", messagesConsumedCount, totalTime );

    BOOST_CHECK( messagesConsumedCount == TotalExpectedMessageCount );
}

// --run_test=ConcurrentQueueTests/MPMCTest5
BOOST_AUTO_TEST_CASE( MPMCTest5 )
{
    constexpr size_t MessagesPerProducerCount = 1000000;
    constexpr size_t ProducerCount = 10;
    constexpr size_t EnqueueMessageCount = 7;

    constexpr size_t TotalExpectedMessageCount = ProducerCount * MessagesPerProducerCount;
    constexpr size_t ConsumerCount = 1;

    struct Message
    {
        size_t Id = 0;
        size_t Value = 0;
    };

    BlockingConcurrentQueue<Message> queue;
    ThreadGroup threadGroup;
    double totalSeconds[ConsumerCount] = {};
    size_t totalMessagesConsumed[ConsumerCount] = {};

    for ( UInt32 i = 0; i < ConsumerCount; ++i )
    {
        double* seconds = &totalSeconds[i];
        size_t* messagesConsumed = &totalMessagesConsumed[i];
        threadGroup.Add( [&queue, seconds, messagesConsumed]( )
        {
            Stopwatch stopwatch;
            size_t messagesConsumedCount = 0;
            Message message;
            if ( queue.wait_dequeue( message ) )
            {
                stopwatch.Start( );
                messagesConsumedCount++;

                while ( queue.wait_dequeue( message ) )
                {
                    messagesConsumedCount++;
                }
                stopwatch.Stop( );
            }
            *seconds = stopwatch.Elapsed( ).TotalSeconds( );
            *messagesConsumed = messagesConsumedCount;
        } );
    }
    SynchronizationBarrier barrier( ProducerCount );
    for ( UInt32 i = 0; i < ProducerCount; ++i )
    {
        threadGroup.Add( [&queue, &barrier,MessagesPerProducerCount]( )
        {
            Message messages[EnqueueMessageCount];
            size_t fullInsertIterations = MessagesPerProducerCount / EnqueueMessageCount;
            size_t remainder = MessagesPerProducerCount % EnqueueMessageCount;
            for ( size_t i = 0; i < fullInsertIterations; ++i )
            {
                queue.enqueue_bulk( messages, EnqueueMessageCount );
            }
            if ( remainder )
            {
                queue.enqueue_bulk( messages, remainder );
            }
            if ( barrier.Enter( ) )
            {
                queue.Close( );
            }
        } );
    }
    threadGroup.join( );

    size_t messagesConsumedCount = 0;
    double totalTime = 0.0;

    for ( UInt32 i = 0; i < ConsumerCount; ++i )
    {
        messagesConsumedCount += totalMessagesConsumed[i];
        totalTime += totalSeconds[i];
    }

    printf( "ConcurrentQueue: Consumed %zu messages in %f seconds\n", messagesConsumedCount, totalTime );

    BOOST_CHECK( messagesConsumedCount == TotalExpectedMessageCount );
}



BOOST_AUTO_TEST_SUITE_END( )