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

BOOST_FIXTURE_TEST_SUITE( TupleTests, LocalFixture )

// --run_test=TupleTests/SizeOfTest1
BOOST_AUTO_TEST_CASE( SizeOfTest1 )
{
    using TupleType0 = Tuple<>;
    constexpr size_t TupleType0Size = sizeof( TupleType0 );
    BOOST_CHECK( TupleType0Size == 1 );
    BOOST_CHECK( TupleType0::Size == 0 );

    using TupleType1 = Tuple<Byte>;
    constexpr size_t TupleType1Size = sizeof( TupleType1 );
    BOOST_CHECK( TupleType1Size == 1 );

    using TupleType2 = Tuple<Byte,UInt32>;
    constexpr size_t TupleType2Size = sizeof( TupleType2 );
    BOOST_CHECK( TupleType2Size == 5 );

    using TupleType3 = std::tuple<Byte>;
    constexpr size_t TupleType3Size = sizeof( TupleType3 );
    BOOST_CHECK( TupleType3Size == 1 );

    using TupleType4 = std::tuple<Byte, UInt32>;
    constexpr size_t TupleType4Size = sizeof( TupleType4 );
    BOOST_CHECK( TupleType4Size == 8 );

    BOOST_CHECK( TupleType4Size != TupleType2Size );

}

// --run_test=TupleTests/ByteSizeTest1
BOOST_AUTO_TEST_CASE( ByteSizeTest1 )
{
    using TupleType0 = Tuple<>;
    TupleType0 tuple0;
    auto tuple0Size = tuple0.size( );
    BOOST_CHECK( tuple0Size == 0 );
    auto tuple0ByteSize = tuple0.ByteSize( );
    auto sizeofTuple0 = sizeof( tuple0 );
    BOOST_CHECK( tuple0ByteSize == sizeofTuple0 );

    using TupleType1 = Tuple<Byte>;
    TupleType1 tuple1;
    auto tuple1Size = tuple1.size( );
    BOOST_CHECK( tuple1Size == 1 );
    auto tuple1ByteSize = tuple1.ByteSize( );
    BOOST_CHECK( tuple1ByteSize == 1 );

    using TupleType2 = Tuple<Byte,UInt32>;
    TupleType2 tuple2;
    auto tuple2Size = tuple2.size( );
    BOOST_CHECK( tuple2Size == 2 );
    auto tuple2ByteSize = tuple2.ByteSize( );
    BOOST_CHECK( tuple2ByteSize == 5 );
}

// --run_test=TupleTests/StdTupleTest1
BOOST_AUTO_TEST_CASE( StdTupleTest1 )
{
    using TupleType = std::tuple<int, double>;

    TupleType value( 1, 2.0 );
    int* intValuePtr = std::addressof( std::get<0>( value ) );
    double* doubleValuePtr = std::addressof( std::get<1>( value ) );

    if ( reinterpret_cast<Byte*>( intValuePtr ) > reinterpret_cast<Byte*>( doubleValuePtr ) )
    {
        puts( "std::tuple has reverse order\n" );
    }

}

// --run_test=TupleTests/TupleOrderTest1
BOOST_AUTO_TEST_CASE( TupleOrderTest1 )
{
    using TupleType = Tuple<int, double>;

    TupleType value( 1, 2.0 );
    int* intValuePtr = std::addressof( get<0>( value ) );
    double* doubleValuePtr = std::addressof( get<1>( value ) );

    if ( reinterpret_cast<const Byte*>( intValuePtr ) > reinterpret_cast<const Byte*>( doubleValuePtr ) )
    {
        puts( "Tuple has reverse order\n" );
    }
}

// --run_test=TupleTests/StdTupleCatTest1
BOOST_AUTO_TEST_CASE( StdTupleCatTest1 )
{
    using TupleType1 = std::tuple<int, double>;
    using TupleType2 = std::tuple<bool, Int64>;
    TupleType1 tuple1( 1, 2.0 );
    TupleType2 tuple2( false, 4 );

    auto tuple3 = std::tuple_cat( tuple1, tuple2 );
    constexpr auto tuple3Size = std::tuple_size_v<decltype( tuple3 )>;
    BOOST_CHECK( tuple3Size == 4 );

}

// --run_test=TupleTests/StdTupleCatTest2
BOOST_AUTO_TEST_CASE( StdTupleCatTest2 )
{
    using TupleType1 = std::tuple<int, double>;
    using TupleType2 = std::tuple<>;
    TupleType1 tuple1( 1, 2.0 );
    TupleType2 tuple2;

    auto tuple3 = std::tuple_cat( tuple1, tuple2 );
    constexpr auto tuple3Size = std::tuple_size_v<decltype( tuple3 )>;
    BOOST_CHECK( tuple3Size == 2 );

}



// --run_test=TupleTests/TupleAssignTest1
BOOST_AUTO_TEST_CASE( TupleAssignTest1 )
{
    using TupleType = Tuple<int, double>;
    TupleType tuple1( 1, 2.0 );
    TupleType tuple2;

    tuple2 = tuple1;
    bool firstEqual = get<0>( tuple1 ) == get<0>( tuple2 );
    bool secondEqual = get<1>( tuple1 ) == get<1>( tuple2 );

    BOOST_CHECK( firstEqual );
    BOOST_CHECK( secondEqual );

}

// --run_test=TupleTests/TupleAssignTest2
BOOST_AUTO_TEST_CASE( TupleAssignTest2 )
{
    // The real test here is to see if the code compiles
    using TupleType = Tuple<>;
    TupleType tuple1;
    TupleType tuple2;

    tuple2 = tuple1;
    BOOST_CHECK( tuple2.size( ) == tuple1.size( ) );

}



// --run_test=TupleTests/TupleCopyConstructTest1
BOOST_AUTO_TEST_CASE( TupleCopyConstructTest1 )
{
    using TupleType = Tuple<int, double>;
    TupleType tuple1( 1, 2.0 );
    Tuple tuple2( tuple1 );

    tuple2 = tuple1;
    bool firstEqual = get<0>( tuple1 ) == get<0>( tuple2 );
    bool secondEqual = get<1>( tuple1 ) == get<1>( tuple2 );

    BOOST_CHECK( firstEqual );
    BOOST_CHECK( secondEqual );

}

// --run_test=TupleTests/TupleEqualTest1
BOOST_AUTO_TEST_CASE( TupleEqualTest1 )
{
    using TupleType = Tuple<int, double>;
    TupleType tuple1( 1, 2.0 );
    Tuple tuple2( tuple1 );
    Tuple tuple3( 2, 2.0 );

    tuple2 = tuple1;
    
    bool firstEqual = tuple1 == tuple2;
    bool secondEqual = tuple1 == tuple3;

    bool isLess1 = tuple1 < tuple3;
    bool isGreater1 = tuple3 > tuple1;

    BOOST_CHECK( firstEqual );
    BOOST_CHECK( secondEqual == false );
    BOOST_CHECK( isLess1 );
    BOOST_CHECK( isGreater1 );
}




// --run_test=TupleTests/ForwardAsTupleTest1
BOOST_AUTO_TEST_CASE( ForwardAsTupleTest1 )
{
    auto result_0 = ForwardAsTuple( );
    BOOST_CHECK( result_0.size( ) == 0 );

    auto result_1 = ForwardAsTuple( 0, "text" );
    BOOST_CHECK( result_1.size( ) == 2 );
}

// --run_test=TupleTests/TupleCatTest1
BOOST_AUTO_TEST_CASE( TupleCatTest1 )
{
    using TupleType1 = Tuple<int, double>;
    using TupleType2 = Tuple<bool, Int64>;
    TupleType1 tuple1( 1, 2.0 );
    TupleType2 tuple2( false, 4 );

    auto tuple3 = TupleCat( tuple1, tuple2 );

    auto tuple3Size = tuple3.size( );
    BOOST_CHECK( tuple3Size == 4 );
}

#pragma pack(push,1)

struct TupleCatA
{
    Int32 int32Val;
    double dblVal;
};

struct TupleCatB
{
    bool boolVal;
    Int64 int64Val;
};

struct TupleCatC
{
    Int32 int32Val;
    double dblVal;
    bool boolVal;
    Int64 int64Val;
};


#pragma pack(pop)

// --run_test=TupleTests/TupleCatTest2
BOOST_AUTO_TEST_CASE( TupleCatTest2 )
{
    using TupleType1 = Tuple<int, double>;
    constexpr size_t sizeofTupleType1 = sizeof( TupleType1 );
    constexpr size_t sizeofTupleCatA = sizeof( TupleCatA );
    BOOST_CHECK( sizeofTupleType1 == sizeofTupleCatA );

    using TupleType2 = Tuple<bool, Int64>;
    constexpr size_t sizeofTupleType2 = sizeof( TupleType2 );
    constexpr size_t sizeofTupleCatB = sizeof( TupleCatB );
    BOOST_CHECK( sizeofTupleType2 == sizeofTupleCatB );

    TupleType1 tuple1( 1, 2.0 );
    TupleCatA tupleCatA{ 1, 2.0 };
    TupleType2 tuple2( false, 4 );
    TupleCatB tupleCatB{ false, 4 };

    TupleCatC tupleCatC{ 1, 2.0, false, 4 };

    auto tuple3 = TupleCat( tuple1, tuple2 );
    using TupleType3 = decltype( tuple3 );
    constexpr size_t sizeofTupleType3 = sizeof( TupleType3 );
    constexpr size_t sizeofTupleCatC = sizeof( TupleCatC );
    BOOST_CHECK( sizeofTupleType3 == sizeofTupleCatC );

    auto tuple3Size = tuple3.size( );
    BOOST_CHECK( tuple3Size == 4 );

    bool areEqual = memcmp(&tuple3, &tupleCatC, sizeof( TupleCatC ) ) == 0;
    BOOST_CHECK( areEqual );
}

// --run_test=TupleTests/TupleCatTest3
BOOST_AUTO_TEST_CASE( TupleCatTest3 )
{
    using TupleType1 = Tuple<int, double>;
    using TupleType2 = Tuple<>;
    TupleType1 tuple1( 1, 2.0 );
    TupleType2 tuple2;

    auto tuple3 = TupleCat( tuple1, tuple2 );
    using TupleType3 = decltype( tuple3 );
    constexpr auto tuple3Size = TupleType3::Size;
    BOOST_CHECK( tuple3Size == 2 );
}

// --run_test=TupleTests/TupleCatTest4
BOOST_AUTO_TEST_CASE( TupleCatTest4 )
{
    using TupleType1 = Tuple<>;
    using TupleType2 = Tuple<>;
    TupleType1 tuple1;
    TupleType2 tuple2;

    auto tuple3 = TupleCat( tuple1, tuple2 );
    using TupleType3 = decltype( tuple3 );
    constexpr auto tuple3Size = TupleType3::Size;
    BOOST_CHECK( tuple3Size == 0 );
}

// --run_test=TupleTests/TupleCatTest5
BOOST_AUTO_TEST_CASE( TupleCatTest5 )
{
    using Type1 = Tuple<>;
    using Type2 = Tuple<>;
    Type1 tuple1;
    Type2 tuple2;

    auto tuple3 = TupleCat( tuple1, tuple2 );
    using Type3 = decltype( tuple3 );
    constexpr auto tuple3Size = Type3::Size;
    BOOST_CHECK( tuple3Size == 0 );
}


BOOST_AUTO_TEST_SUITE_END( )
