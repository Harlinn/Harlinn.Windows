#include "pch.h"

using namespace Harlinn::Common::Core;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( )
        {
        }
        ~LocalFixture( )
        {
        }
    };

    template<typename T, typename ValueT>
    void CheckBitVector( const BitVector<T>& bitVector, const ValueT value, size_t startIndex = 0 )
    {
        constexpr size_t BitsPerValue = sizeof( ValueT ) * CHAR_BIT;
        BOOST_CHECK( BitsPerValue >= bitVector.size( ) - startIndex );
        if ( BitsPerValue >= bitVector.size( ) - startIndex )
        {
            for ( size_t i = 0; i < BitsPerValue; i++ )
            {
                ValueT valueMask = static_cast<ValueT>( 1 ) << i;
                bool valueHasBitOn = ( value & valueMask ) != 0;
                size_t index = startIndex + i;
                bool bitVectorHasBitOn = bitVector[index];
                BOOST_CHECK( valueHasBitOn == bitVectorHasBitOn );
            }
        }
    }

    template<typename T>
        requires ( std::is_integral_v<T> || std::is_floating_point_v<T> )
    constexpr size_t BitSizeOf( )
    {
        return sizeof( T ) * CHAR_BIT;
    }
    template<typename T>
        requires ( std::is_integral_v<T> || std::is_floating_point_v<T> )
    constexpr size_t BitSizeOf( const T )
    {
        return sizeof( T ) * CHAR_BIT;
    }

    template<typename T>
    void BitVectorAllTest( )
    {
        using VectorType = std::vector<T>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = T;

        constexpr Byte byteAllSet = ~Byte( 0 );
        constexpr UInt16 uint16AllSet = ~UInt16( 0 );
        constexpr UInt32 uint32AllSet = ~UInt32( 0 );
        constexpr UInt64 uint64AllSet = ~UInt64( 0 );

        BitVectorType bitVector1;
        size_t bitVector1Size0 = bitVector1.size( );
        BOOST_CHECK( bitVector1Size0 == 0 );
        bool bitVector1Size0All = bitVector1.all( );
        BOOST_CHECK( bitVector1Size0All == true );
        bitVector1.push_back( true );
        size_t expectedSize = 1;
        size_t bitVector1Size1 = bitVector1.size( );
        BOOST_CHECK( bitVector1Size1 == expectedSize );

        bitVector1.append( byteAllSet );
        expectedSize += BitSizeOf<Byte>( );
        auto bitVector1Size = bitVector1.size( );
        BOOST_CHECK( bitVector1Size == expectedSize );
        auto bitVector1AllSet = bitVector1.all( );
        BOOST_CHECK( bitVector1AllSet == true );

        bitVector1.append( uint16AllSet );
        expectedSize += BitSizeOf<UInt16>( );
        bitVector1Size = bitVector1.size( );
        BOOST_CHECK( bitVector1Size == expectedSize );
        bitVector1AllSet = bitVector1.all( );
        BOOST_CHECK( bitVector1AllSet == true );

        bitVector1.append( uint32AllSet );
        expectedSize += BitSizeOf<UInt32>( );
        bitVector1Size = bitVector1.size( );
        BOOST_CHECK( bitVector1Size == expectedSize );
        bitVector1AllSet = bitVector1.all( );
        BOOST_CHECK( bitVector1AllSet == true );

        bitVector1.append( uint64AllSet );
        expectedSize += BitSizeOf<UInt64>( );
        bitVector1Size = bitVector1.size( );
        BOOST_CHECK( bitVector1Size == expectedSize );
        bitVector1AllSet = bitVector1.all( );
        BOOST_CHECK( bitVector1AllSet == true );

        for ( size_t i = 0; i < bitVector1Size; i++ )
        {
            bitVector1[i] = false;
            bool allSet = bitVector1.all( );
            BOOST_CHECK( allSet == false );
            bitVector1[i] = true;
            allSet = bitVector1.all( );
            BOOST_CHECK( allSet == true );
        }
    }

    template<typename T>
    void BitVectorNoneTest( )
    {
        using VectorType = std::vector<T>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = T;

        constexpr Byte byteNoneSet = Byte( 0 );
        constexpr UInt16 uint16NoneSet = UInt16( 0 );
        constexpr UInt32 uint32NoneSet = UInt32( 0 );
        constexpr UInt64 uint64NoneSet = UInt64( 0 );

        BitVectorType bitVector1;
        size_t bitVector1Size0 = bitVector1.size( );
        BOOST_CHECK( bitVector1Size0 == 0 );
        bool bitVector1Size0None = bitVector1.none( );
        BOOST_CHECK( bitVector1Size0None == true );
        bitVector1.push_back( false );
        size_t expectedSize = 1;
        size_t bitVector1Size1 = bitVector1.size( );
        BOOST_CHECK( bitVector1Size1 == expectedSize );

        bitVector1.append( byteNoneSet );
        expectedSize += BitSizeOf<Byte>( );
        auto bitVector1Size = bitVector1.size( );
        BOOST_CHECK( bitVector1Size == expectedSize );
        auto bitVector1NoneSet = bitVector1.none( );
        BOOST_CHECK( bitVector1NoneSet == true );

        bitVector1.append( uint16NoneSet );
        expectedSize += BitSizeOf<UInt16>( );
        bitVector1Size = bitVector1.size( );
        BOOST_CHECK( bitVector1Size == expectedSize );
        bitVector1NoneSet = bitVector1.none( );
        BOOST_CHECK( bitVector1NoneSet == true );

        bitVector1.append( uint32NoneSet );
        expectedSize += BitSizeOf<UInt32>( );
        bitVector1Size = bitVector1.size( );
        BOOST_CHECK( bitVector1Size == expectedSize );
        bitVector1NoneSet = bitVector1.none( );
        BOOST_CHECK( bitVector1NoneSet == true );

        bitVector1.append( uint64NoneSet );
        expectedSize += BitSizeOf<UInt64>( );
        bitVector1Size = bitVector1.size( );
        BOOST_CHECK( bitVector1Size == expectedSize );
        bitVector1NoneSet = bitVector1.none( );
        BOOST_CHECK( bitVector1NoneSet == true );

        for ( size_t i = 0; i < bitVector1Size; i++ )
        {
            bitVector1[i] = true;
            bool noneSet = bitVector1.none( );
            BOOST_CHECK( noneSet == false );
            bitVector1[i] = false;
            noneSet = bitVector1.none( );
            BOOST_CHECK( noneSet == true );
        }
    }

    template<typename T>
    void BitVectorFlipAnyTest( BitVector<T>& bitVector )
    {
        size_t bitVectorSize = bitVector.size( );
        for ( size_t i = 0; i < bitVectorSize; i++ )
        {
            bool anySet = bitVector.any( );
            BOOST_CHECK( anySet == false );
            bitVector[i] = true;
            anySet = bitVector.any( );
            BOOST_CHECK( anySet == true );
            bitVector[i] = false;
            anySet = bitVector.any( );
            BOOST_CHECK( anySet == false );
            
        }
    }

    template<typename T>
    void BitVectorAnyTest( )
    {
        using VectorType = std::vector<T>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = T;

        constexpr Byte byteNoneSet = Byte( 0 );
        constexpr UInt16 uint16NoneSet = UInt16( 0 );
        constexpr UInt32 uint32NoneSet = UInt32( 0 );
        constexpr UInt64 uint64NoneSet = UInt64( 0 );

        BitVectorType bitVector1;
        bitVector1.push_back( false );
        BitVectorFlipAnyTest( bitVector1 );

        bitVector1.append( byteNoneSet );
        BitVectorFlipAnyTest( bitVector1 );

        bitVector1.append( uint16NoneSet );
        BitVectorFlipAnyTest( bitVector1 );

        bitVector1.append( uint32NoneSet );
        BitVectorFlipAnyTest( bitVector1 );

        bitVector1.append( uint64NoneSet );
        BitVectorFlipAnyTest( bitVector1 );
    }

    template<size_t N, typename WordT>
    void BitVectorFlipTest( )
    {
        using VectorType = std::vector<WordT>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = WordT;
        constexpr Byte byteValue = 0b01010101;
        constexpr Byte flippedByteValue = ~byteValue;
        constexpr size_t fullBytes = N / CHAR_BIT;
        constexpr size_t remainingBits = N % CHAR_BIT;
        std::vector<Byte> bits;
        bits.resize( remainingBits ? fullBytes + 1 : fullBytes, byteValue );
        std::vector<Byte> flippedBits;
        flippedBits.resize( remainingBits ? fullBytes + 1 : fullBytes, flippedByteValue );
        BitVectorType bitVector( bits.data(), N );
        BitVectorType flippedBitVector( flippedBits.data( ), N );
        bitVector.flip( );
        bool equal = bitVector == flippedBitVector;
        BOOST_CHECK( equal );

    }

    template<typename T>
    void BitVectorFlipTest( )
    {
        using VectorType = std::vector<T>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = T;

        BitVectorFlipTest<1, WordType>( );
        BitVectorFlipTest<2, WordType>( );
        BitVectorFlipTest<7, WordType>( );
        BitVectorFlipTest<8, WordType>( );
        BitVectorFlipTest<9, WordType>( );
        BitVectorFlipTest<15, WordType>( );
        BitVectorFlipTest<16, WordType>( );
        BitVectorFlipTest<17, WordType>( );
        BitVectorFlipTest<31, WordType>( );
        BitVectorFlipTest<32, WordType>( );
        BitVectorFlipTest<33, WordType>( );
        BitVectorFlipTest<63, WordType>( );
        BitVectorFlipTest<64, WordType>( );
        BitVectorFlipTest<65, WordType>( );
        BitVectorFlipTest<95, WordType>( );
        BitVectorFlipTest<96, WordType>( );
        BitVectorFlipTest<97, WordType>( );
        BitVectorFlipTest<127, WordType>( );
        BitVectorFlipTest<128, WordType>( );
    }

    template<typename WordT>
    void BitVectorAndTest( )
    {
        using VectorType = std::vector<WordT>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = WordT;

        constexpr Byte firstByteValue =  0b10100101;
        constexpr Byte secondByteValue = 0b11000011;
        constexpr Byte expectedByteValue = firstByteValue & secondByteValue;
        

        constexpr std::array<size_t, 20> BitVectorSizes = {1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025};
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<Byte> firstBits;
            size_t firstFullBytes = firstSize / CHAR_BIT;
            size_t firstRemainingBits = firstSize % CHAR_BIT;
            firstBits.resize( firstRemainingBits ? firstFullBytes + 1 : firstFullBytes, firstByteValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<Byte> secondBits;
                size_t secondFullBytes = secondSize / CHAR_BIT;
                size_t secondRemainingBits = secondSize % CHAR_BIT;
                secondBits.resize( secondRemainingBits ? secondFullBytes + 1 : secondFullBytes, secondByteValue );
                BitVectorType secondBitVector( secondBits.data( ), secondSize );

                size_t expectedSize = std::max( firstSize, secondSize );
                BitVectorType expectedBitVector;
                expectedBitVector.resize( expectedSize );
                size_t minSize = std::min( firstSize, secondSize );
                for ( size_t i = 0; i < minSize; i++ )
                {
                    expectedBitVector[i] = firstBitVector[i] & secondBitVector[i];
                }
                
                BitVectorType firstAndSecondBitVector = firstBitVector & secondBitVector;
                bool equal = firstAndSecondBitVector == expectedBitVector;
                BOOST_CHECK( equal );
            }
        }
    }

    template<typename WordT>
    void BitVectorAndAssignTest( )
    {
        using VectorType = std::vector<WordT>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = WordT;

        constexpr Byte firstByteValue = 0b10100101;
        constexpr Byte secondByteValue = 0b11000011;
        constexpr Byte expectedByteValue = firstByteValue & secondByteValue;


        constexpr std::array<size_t, 20> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025 };
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<Byte> firstBits;
            size_t firstFullBytes = firstSize / CHAR_BIT;
            size_t firstRemainingBits = firstSize % CHAR_BIT;
            firstBits.resize( firstRemainingBits ? firstFullBytes + 1 : firstFullBytes, firstByteValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<Byte> secondBits;
                size_t secondFullBytes = secondSize / CHAR_BIT;
                size_t secondRemainingBits = secondSize % CHAR_BIT;
                secondBits.resize( secondRemainingBits ? secondFullBytes + 1 : secondFullBytes, secondByteValue );
                BitVectorType secondBitVector( secondBits.data( ), secondSize );

                size_t expectedSize = std::max( firstSize, secondSize );
                BitVectorType expectedBitVector;
                expectedBitVector.resize( expectedSize );
                size_t minSize = std::min( firstSize, secondSize );
                for ( size_t i = 0; i < minSize; i++ )
                {
                    expectedBitVector[i] = firstBitVector[i] & secondBitVector[i];
                }

                BitVectorType firstAndSecondBitVector = firstBitVector;
                firstAndSecondBitVector &= secondBitVector;
                bool equal = firstAndSecondBitVector == expectedBitVector;
                BOOST_CHECK( equal );
            }
        }
    }


    template<typename WordT>
    void BitVectorOrTest( )
    {
        using VectorType = std::vector<WordT>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = WordT;

        constexpr Byte firstByteValue =  0b10100101;
        constexpr Byte secondByteValue = 0b11000011;
        constexpr Byte expectedByteValue = firstByteValue | secondByteValue;

        constexpr std::array<size_t, 20> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025 };
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<Byte> firstBits;
            size_t firstFullBytes = firstSize / CHAR_BIT;
            size_t firstRemainingBits = firstSize % CHAR_BIT;
            firstBits.resize( firstRemainingBits ? firstFullBytes + 1 : firstFullBytes, firstByteValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<Byte> secondBits;
                size_t secondFullBytes = secondSize / CHAR_BIT;
                size_t secondRemainingBits = secondSize % CHAR_BIT;
                secondBits.resize( secondRemainingBits ? secondFullBytes + 1 : secondFullBytes, secondByteValue );
                BitVectorType secondBitVector( secondBits.data( ), secondSize );

                size_t expectedSize = std::max( firstSize, secondSize );
                BitVectorType expectedBitVector;
                expectedBitVector.resize( expectedSize );
                size_t minSize = std::min( firstSize, secondSize );
                size_t maxSize = std::max( firstSize, secondSize );
                size_t i = 0;
                for ( ; i < minSize; i++ )
                {
                    expectedBitVector[i] = firstBitVector[i] | secondBitVector[i];
                }
                if ( firstSize < secondSize )
                {
                    for ( ; i < maxSize; i++ )
                    {
                        expectedBitVector[i] = secondBitVector[i];
                    }
                }
                else if ( firstSize > secondSize )
                {
                    for ( ; i < maxSize; i++ )
                    {
                        expectedBitVector[i] = firstBitVector[i];
                    }
                }

                BitVectorType firstOrSecondBitVector = firstBitVector | secondBitVector;
                bool equal = firstOrSecondBitVector == expectedBitVector;
                BOOST_CHECK( equal );
            }
        }
    }

    template<typename WordT>
    void BitVectorOrAssignTest( )
    {
        using VectorType = std::vector<WordT>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = WordT;

        constexpr Byte firstByteValue = 0b10100101;
        constexpr Byte secondByteValue = 0b11000011;
        constexpr Byte expectedByteValue = firstByteValue | secondByteValue;

        constexpr std::array<size_t, 20> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025 };
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<Byte> firstBits;
            size_t firstFullBytes = firstSize / CHAR_BIT;
            size_t firstRemainingBits = firstSize % CHAR_BIT;
            firstBits.resize( firstRemainingBits ? firstFullBytes + 1 : firstFullBytes, firstByteValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<Byte> secondBits;
                size_t secondFullBytes = secondSize / CHAR_BIT;
                size_t secondRemainingBits = secondSize % CHAR_BIT;
                secondBits.resize( secondRemainingBits ? secondFullBytes + 1 : secondFullBytes, secondByteValue );
                BitVectorType secondBitVector( secondBits.data( ), secondSize );

                size_t expectedSize = std::max( firstSize, secondSize );
                BitVectorType expectedBitVector;
                expectedBitVector.resize( expectedSize );
                size_t minSize = std::min( firstSize, secondSize );
                size_t maxSize = std::max( firstSize, secondSize );
                size_t i = 0;
                for ( ; i < minSize; i++ )
                {
                    expectedBitVector[i] = firstBitVector[i] | secondBitVector[i];
                }
                if ( firstSize < secondSize )
                {
                    for ( ; i < maxSize; i++ )
                    {
                        expectedBitVector[i] = secondBitVector[i];
                    }
                }
                else if ( firstSize > secondSize )
                {
                    for ( ; i < maxSize; i++ )
                    {
                        expectedBitVector[i] = firstBitVector[i];
                    }
                }

                BitVectorType firstOrSecondBitVector = firstBitVector;

                firstOrSecondBitVector |= secondBitVector;
                bool equal = firstOrSecondBitVector == expectedBitVector;
                BOOST_CHECK( equal );
            }
        }
    }


    template<typename WordT>
    void BitVectorXorTest( )
    {
        using VectorType = std::vector<WordT>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = WordT;

        constexpr Byte firstByteValue = 0b10100101;
        constexpr Byte secondByteValue = 0b11000011;
        constexpr Byte expectedByteValue = firstByteValue | secondByteValue;

        constexpr std::array<size_t, 20> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025 };
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<Byte> firstBits;
            size_t firstFullBytes = firstSize / CHAR_BIT;
            size_t firstRemainingBits = firstSize % CHAR_BIT;
            firstBits.resize( firstRemainingBits ? firstFullBytes + 1 : firstFullBytes, firstByteValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<Byte> secondBits;
                size_t secondFullBytes = secondSize / CHAR_BIT;
                size_t secondRemainingBits = secondSize % CHAR_BIT;
                secondBits.resize( secondRemainingBits ? secondFullBytes + 1 : secondFullBytes, secondByteValue );
                BitVectorType secondBitVector( secondBits.data( ), secondSize );

                size_t expectedSize = std::max( firstSize, secondSize );
                BitVectorType expectedBitVector;
                expectedBitVector.resize( expectedSize );
                size_t minSize = std::min( firstSize, secondSize );
                size_t maxSize = std::max( firstSize, secondSize );
                size_t i = 0;
                for ( ; i < minSize; i++ )
                {
                    expectedBitVector[i] = firstBitVector[i] ^ secondBitVector[i];
                }
                if ( firstSize < secondSize )
                {
                    for ( ; i < maxSize; i++ )
                    {
                        expectedBitVector[i] = secondBitVector[i];
                    }
                }
                else if ( firstSize > secondSize )
                {
                    for ( ; i < maxSize; i++ )
                    {
                        expectedBitVector[i] = firstBitVector[i];
                    }
                }

                BitVectorType firstXorSecondBitVector = firstBitVector ^ secondBitVector;
                bool equal = firstXorSecondBitVector == expectedBitVector;
                BOOST_CHECK( equal );
            }
        }
    }

    template<typename WordT>
    void BitVectorXorAssignTest( )
    {
        using VectorType = std::vector<WordT>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = WordT;

        constexpr Byte firstByteValue = 0b10100101;
        constexpr Byte secondByteValue = 0b11000011;
        constexpr Byte expectedByteValue = firstByteValue | secondByteValue;

        constexpr std::array<size_t, 20> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025 };
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<Byte> firstBits;
            size_t firstFullBytes = firstSize / CHAR_BIT;
            size_t firstRemainingBits = firstSize % CHAR_BIT;
            firstBits.resize( firstRemainingBits ? firstFullBytes + 1 : firstFullBytes, firstByteValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<Byte> secondBits;
                size_t secondFullBytes = secondSize / CHAR_BIT;
                size_t secondRemainingBits = secondSize % CHAR_BIT;
                secondBits.resize( secondRemainingBits ? secondFullBytes + 1 : secondFullBytes, secondByteValue );
                BitVectorType secondBitVector( secondBits.data( ), secondSize );

                size_t expectedSize = std::max( firstSize, secondSize );
                BitVectorType expectedBitVector;
                expectedBitVector.resize( expectedSize );
                size_t minSize = std::min( firstSize, secondSize );
                size_t maxSize = std::max( firstSize, secondSize );
                size_t i = 0;
                for ( ; i < minSize; i++ )
                {
                    expectedBitVector[i] = firstBitVector[i] ^ secondBitVector[i];
                }
                if ( firstSize < secondSize )
                {
                    for ( ; i < maxSize; i++ )
                    {
                        expectedBitVector[i] = secondBitVector[i];
                    }
                }
                else if ( firstSize > secondSize )
                {
                    for ( ; i < maxSize; i++ )
                    {
                        expectedBitVector[i] = firstBitVector[i];
                    }
                }

                BitVectorType firstXorSecondBitVector = firstBitVector;
                firstXorSecondBitVector ^= secondBitVector;
                bool equal = firstXorSecondBitVector == expectedBitVector;
                BOOST_CHECK( equal );
            }
        }
    }

    template<typename WordT>
    void BitVectorAppendTest( )
    {
        using VectorType = std::vector<WordT>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = WordT;

        constexpr Byte firstByteValue = 0b10100101;
        constexpr Byte secondByteValue = 0b11000011;

        constexpr std::array<size_t, 20> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025 };
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<Byte> firstBits;
            size_t firstFullBytes = firstSize / CHAR_BIT;
            size_t firstRemainingBits = firstSize % CHAR_BIT;
            firstBits.resize( firstRemainingBits ? firstFullBytes + 1 : firstFullBytes, firstByteValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<Byte> secondBits;
                size_t secondFullBytes = secondSize / CHAR_BIT;
                size_t secondRemainingBits = secondSize % CHAR_BIT;
                secondBits.resize( secondRemainingBits ? secondFullBytes + 1 : secondFullBytes, secondByteValue );
                BitVectorType secondBitVector( secondBits.data( ), secondSize );

                BitVectorType expectedBitVector = firstBitVector;
                for ( size_t i = 0; i < secondSize; i++ )
                {
                    expectedBitVector.push_back( secondBitVector[i] );
                }

                BitVectorType result = firstBitVector;
                result.append( secondBitVector );
                
                bool equal = result == expectedBitVector;
                BOOST_CHECK( equal );
            }
        }
    }
    template<typename WordT>
    void BitVectorCountTest( )
    {
        using VectorType = std::vector<WordT>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = WordT;

        constexpr Byte byteValue = 0b10100101;

        constexpr std::array<size_t, 23> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,95,96,97,127,128,129, 1023, 1024, 1025 };
        for ( auto bitVectorSize : BitVectorSizes )
        {
            std::vector<Byte> bits;
            const size_t fullByteCount = bitVectorSize / CHAR_BIT;
            const size_t fullByteOverflowBitCount = bitVectorSize % CHAR_BIT;
            bits.resize( fullByteOverflowBitCount ? fullByteCount + 1 : fullByteCount, byteValue );
            const BitVectorType bitVector( bits.data( ), bitVectorSize );

            size_t count1 = 0;
            for ( size_t i = 0; i < bitVectorSize; i++ )
            {
                if ( bitVector[i] )
                {
                    count1++;
                }
            }
            size_t count2 = bitVector.count( );
            bool equal = count1 == count2;
            BOOST_CHECK( equal );
        }
    }



}

BOOST_FIXTURE_TEST_SUITE( BitVectorTests, LocalFixture )

// --run_test=BitVectorTests/AppendTest1
BOOST_AUTO_TEST_CASE( AppendTest1 )
{
    using BitVectorType = BitVector<std::vector<UInt16>>;
    
    constexpr Byte byteValue = 0x01;
    constexpr UInt16 uint16Value = 0x0201;
    constexpr UInt32 uint32Value = 0x04030201;
    constexpr UInt64 uint64Value = 0x0807060504030201;

    BitVectorType bitVector1;
    bitVector1.append( byteValue );
    CheckBitVector( bitVector1, byteValue );

    BitVectorType bitVector2;
    bitVector2.append( uint16Value );
    CheckBitVector( bitVector2, uint16Value );

    BitVectorType bitVector3;
    bitVector3.append( uint32Value );
    CheckBitVector( bitVector3, uint32Value );

    BitVectorType bitVector4;
    bitVector4.append( uint64Value );
    CheckBitVector( bitVector4, uint64Value );
}

// --run_test=BitVectorTests/AppendTest2
BOOST_AUTO_TEST_CASE( AppendTest2 )
{
    using BitVectorType = BitVector<std::vector<UInt16>>;

    constexpr Byte byteValue = 0x01;
    constexpr UInt16 uint16Value = 0x0201;
    constexpr UInt32 uint32Value = 0x04030201;
    constexpr UInt64 uint64Value = 0x0807060504030201;

    BitVectorType bitVector1;
    bitVector1.push_back( true );
    bitVector1.append( byteValue );
    CheckBitVector( bitVector1, byteValue, 1 );

    BitVectorType bitVector2;
    bitVector2.push_back( true );
    bitVector2.append( uint16Value );
    CheckBitVector( bitVector2, uint16Value, 1 );

    BitVectorType bitVector3;
    bitVector3.push_back( true );
    bitVector3.append( uint32Value );
    CheckBitVector( bitVector3, uint32Value, 1 );

    BitVectorType bitVector4;
    bitVector4.push_back( true );
    bitVector4.append( uint64Value );
    CheckBitVector( bitVector4, uint64Value, 1 );
}

// --run_test=BitVectorTests/AllTest1
BOOST_AUTO_TEST_CASE( AllTest1 )
{
    BitVectorAllTest<Byte>( );
    BitVectorAllTest<UInt16>( );
    BitVectorAllTest<UInt32>( );
    BitVectorAllTest<UInt64>( );
}

// --run_test=BitVectorTests/NoneTest1
BOOST_AUTO_TEST_CASE( NoneTest1 )
{
    BitVectorNoneTest<Byte>( );
    BitVectorNoneTest<UInt16>( );
    BitVectorNoneTest<UInt32>( );
    BitVectorNoneTest<UInt64>( );
}

// --run_test=BitVectorTests/AnyTest1
BOOST_AUTO_TEST_CASE( AnyTest1 )
{
    BitVectorAnyTest<Byte>( );
    BitVectorAnyTest<UInt16>( );
    BitVectorAnyTest<UInt32>( );
    BitVectorAnyTest<UInt64>( );
}

// --run_test=BitVectorTests/IsEqualTest1
BOOST_AUTO_TEST_CASE( IsEqualTest1 )
{
    using BitVector2Type = BitVector<std::vector<UInt16>>;
    using BitVector4Type = BitVector<std::vector<UInt32>>;
    using BitVector8Type = BitVector<std::vector<UInt32>>;

    BitVector2Type bitVector2;
    BitVector4Type bitVector4;
    BitVector8Type bitVector8;

    auto assignBits = []<typename T>( BitVector<T>& bitVector )
    {
        for ( size_t i = 0; i < 64; i++ )
        {
            bitVector.push_back( true );
            bitVector.push_back( false );
            bitVector.push_back( false );
            bitVector.push_back( true );
            bitVector.push_back( true );
            bitVector.push_back( false );
            bitVector.push_back( true );
            bitVector.push_back( true );
            bitVector.push_back( true );
            bitVector.push_back( false );
        }
        
    };

    assignBits( bitVector2 );
    assignBits( bitVector4 );
    assignBits( bitVector8 );
    bool equal = bitVector2 == bitVector4;
    BOOST_CHECK( equal );
    equal = bitVector2 == bitVector8;
    BOOST_CHECK( equal );
    equal = bitVector4 == bitVector8;
    BOOST_CHECK( equal );

}

// --run_test=BitVectorTests/BitVectorFlip1
BOOST_AUTO_TEST_CASE( BitVectorFlip1 )
{
    BitVectorFlipTest<Byte>( );
    BitVectorFlipTest<SByte>( );
    BitVectorFlipTest<Int16>( );
    BitVectorFlipTest<UInt16>( );
    BitVectorFlipTest<Int32>( );
    BitVectorFlipTest<UInt32>( );
    BitVectorFlipTest<Int64>( );
    BitVectorFlipTest<UInt64>( );
}

// --run_test=BitVectorTests/BitVectorAndTest1
BOOST_AUTO_TEST_CASE( BitVectorAndTest1 )
{
    BitVectorAndTest<Byte>( );
    BitVectorAndTest<SByte>( );
    BitVectorAndTest<Int16>( );
    BitVectorAndTest<UInt16>( );
    BitVectorAndTest<Int32>( );
    BitVectorAndTest<UInt32>( );
    BitVectorAndTest<Int64>( );
    BitVectorAndTest<UInt64>( );
}

// --run_test=BitVectorTests/BitVectorAndAssignTest1
BOOST_AUTO_TEST_CASE( BitVectorAndAssignTest1 )
{
    BitVectorAndAssignTest<Byte>( );
    BitVectorAndAssignTest<SByte>( );
    BitVectorAndAssignTest<Int16>( );
    BitVectorAndAssignTest<UInt16>( );
    BitVectorAndAssignTest<Int32>( );
    BitVectorAndAssignTest<UInt32>( );
    BitVectorAndAssignTest<Int64>( );
    BitVectorAndAssignTest<UInt64>( );
}


// --run_test=BitVectorTests/BitVectorOrTest1
BOOST_AUTO_TEST_CASE( BitVectorOrTest1 )
{
    BitVectorOrTest<Byte>( );
    BitVectorOrTest<SByte>( );
    BitVectorOrTest<Int16>( );
    BitVectorOrTest<UInt16>( );
    BitVectorOrTest<Int32>( );
    BitVectorOrTest<UInt32>( );
    BitVectorOrTest<Int64>( );
    BitVectorOrTest<UInt64>( );
}

// --run_test=BitVectorTests/BitVectorOrAssignTest1
BOOST_AUTO_TEST_CASE( BitVectorOrAssignTest1 )
{
    BitVectorOrAssignTest<Byte>( );
    BitVectorOrAssignTest<SByte>( );
    BitVectorOrAssignTest<Int16>( );
    BitVectorOrAssignTest<UInt16>( );
    BitVectorOrAssignTest<Int32>( );
    BitVectorOrAssignTest<UInt32>( );
    BitVectorOrAssignTest<Int64>( );
    BitVectorOrAssignTest<UInt64>( );
}


// --run_test=BitVectorTests/BitVectorXorTest1
BOOST_AUTO_TEST_CASE( BitVectorXorTest1 )
{
    BitVectorXorTest<Byte>( );
    BitVectorXorTest<SByte>( );
    BitVectorXorTest<Int16>( );
    BitVectorXorTest<UInt16>( );
    BitVectorXorTest<Int32>( );
    BitVectorXorTest<UInt32>( );
    BitVectorXorTest<Int64>( );
    BitVectorXorTest<UInt64>( );
}

// --run_test=BitVectorTests/BitVectorXorAssignTest1
BOOST_AUTO_TEST_CASE( BitVectorXorAssignTest1 )
{
    BitVectorXorAssignTest<Byte>( );
    BitVectorXorAssignTest<SByte>( );
    BitVectorXorAssignTest<Int16>( );
    BitVectorXorAssignTest<UInt16>( );
    BitVectorXorAssignTest<Int32>( );
    BitVectorXorAssignTest<UInt32>( );
    BitVectorXorAssignTest<Int64>( );
    BitVectorXorAssignTest<UInt64>( );
}

// --run_test=BitVectorTests/BitVectorAppendTest1
BOOST_AUTO_TEST_CASE( BitVectorAppendTest1 )
{
    BitVectorAppendTest<Byte>( );
    BitVectorAppendTest<SByte>( );
    BitVectorAppendTest<Int16>( );
    BitVectorAppendTest<UInt16>( );
    BitVectorAppendTest<Int32>( );
    BitVectorAppendTest<UInt32>( );
    BitVectorAppendTest<Int64>( );
    BitVectorAppendTest<UInt64>( );
}


// --run_test=BitVectorTests/BitVectorCountTest1
BOOST_AUTO_TEST_CASE( BitVectorCountTest1 )
{
    BitVectorCountTest<Byte>( );
    BitVectorCountTest<SByte>( );
    BitVectorCountTest<Int16>( );
    BitVectorCountTest<UInt16>( );
    BitVectorCountTest<Int32>( );
    BitVectorCountTest<UInt32>( );
    BitVectorCountTest<Int64>( );
    BitVectorCountTest<UInt64>( );
}



BOOST_AUTO_TEST_SUITE_END( )