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

BOOST_FIXTURE_TEST_SUITE( SimpleConcurrentQueueTests, LocalFixture )

// --run_test=SimpleConcurrentQueueTests/MPMCTest1
BOOST_AUTO_TEST_CASE( MPMCTest1 )
{
    constexpr size_t MessagesPerProducerCount = 10000;
    constexpr size_t ProducerCount = 10;
    constexpr size_t TotalExpectedMessageCount = ProducerCount * MessagesPerProducerCount;
    constexpr size_t ConsumerCount = 10;
    constexpr size_t QueueSize = 255;

    struct Message
    {
        size_t Id = 0;
        size_t Value = 0;
    };
    using MessagePtr = std::unique_ptr<Message>;

    static_assert( std::is_copy_assignable_v<SimpleConcurrentQueue<MessagePtr, QueueSize>> == false );
    static_assert( std::is_copy_constructible_v<SimpleConcurrentQueue<MessagePtr, QueueSize>> == false );
    static_assert( std::is_move_assignable_v<SimpleConcurrentQueue<MessagePtr, QueueSize>> == false );
    static_assert( std::is_move_constructible_v<SimpleConcurrentQueue<MessagePtr, QueueSize>> == false );

    SimpleConcurrentQueue<MessagePtr, QueueSize> queue;
    std::atomic<size_t> messagesConsumedCount;
    ThreadGroup threadGroup;
    for ( UInt32 i = 0; i < ConsumerCount; ++i )
    {
        threadGroup.Add( [&queue,&messagesConsumedCount]( )
        {
            MessagePtr messagePtr;
            while ( queue.Pop( messagePtr ) )
            {
                ++messagesConsumedCount;
            }
        } );
    }
    SynchronizationBarrier barrier( ProducerCount );
    for ( UInt32 i = 0; i < ProducerCount; ++i )
    {
        threadGroup.Add( [&queue, &barrier,MessagesPerProducerCount]( )
        {
            for ( size_t i = 0; i < MessagesPerProducerCount; ++i )
            {
                auto message = std::make_unique<Message>( );
                queue.Push( std::move( message ) );
            }
            if ( barrier.Enter( ) )
            {
                queue.Close( );
            }
        } );
    }
    threadGroup.join( );
    
    BOOST_CHECK( messagesConsumedCount.load( ) == TotalExpectedMessageCount );
}


// --run_test=SimpleConcurrentQueueTests/MPMCTest2
BOOST_AUTO_TEST_CASE( MPMCTest2 )
{
    constexpr size_t MessagesPerProducerCount = 1000000;
    constexpr size_t ProducerCount = 10;
    constexpr size_t TotalExpectedMessageCount = ProducerCount * MessagesPerProducerCount;
    constexpr size_t ConsumerCount = 10;
    constexpr size_t QueueSize = 255;

    struct Message
    {
        size_t Id = 0;
        size_t Value = 0;
    };

    SimpleConcurrentQueue<Message, QueueSize> queue;
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
            queue.Pop( message );
            
            Stopwatch stopwatch;
            stopwatch.Start( );

            ++messagesConsumedCount;
            while ( queue.Pop( message ) )
            {
                ++messagesConsumedCount;
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
            for ( size_t i = 0; i < MessagesPerProducerCount; ++i )
            {
                Message message;
                queue.Push( message );
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

    printf( "SimpleConcurrentQueue: Consumed %zu messages in %f seconds\n", messagesConsumedCount, totalTime );

    BOOST_CHECK( messagesConsumedCount == TotalExpectedMessageCount );
}



BOOST_AUTO_TEST_SUITE_END( )