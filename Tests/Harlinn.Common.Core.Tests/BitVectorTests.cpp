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

    template<size_t NumBits, typename WordT>
    void BitVectorFlipTest( )
    {
        using VectorType = std::vector<WordT>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = WordT;
        constexpr size_t bitsPerWord = sizeof( WordType ) * CHAR_BIT;
        constexpr size_t numberOfBits = NumBits;
        constexpr UInt64 bitsValue = 0b0101010101010101010101010101010101010101010101010101010101010101;
        constexpr UInt64 flippedBitsValue = ~bitsValue;
        constexpr size_t fullWords = numberOfBits / ( bitsPerWord );
        constexpr size_t remainingBits = numberOfBits % bitsPerWord;
        constexpr size_t vectorSize = remainingBits ? fullWords + 1 : fullWords;
        std::vector<WordT> bits;
        bits.resize( vectorSize, static_cast< WordType >( bitsValue ) );
        std::vector<WordT> flippedBits;
        flippedBits.resize( vectorSize, static_cast< WordType >( flippedBitsValue ) );
        BitVectorType bitVector( bits.data(), numberOfBits );
        BitVectorType flippedBitVector( flippedBits.data( ), numberOfBits );
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
    constexpr WordT MakeWordOf( Byte value )
    {
        if constexpr ( sizeof( WordT ) == 1 )
        {
            return static_cast< WordT >( value );
        }
        else if constexpr ( sizeof( WordT ) == 2 )
        {
            return (static_cast< WordT >( value ) << 8 ) + 
                static_cast< WordT >( value );
        }
        else if constexpr ( sizeof( WordT ) == 4 )
        {
            return ( static_cast< WordT >( value ) << 24 ) +
                ( static_cast< WordT >( value ) << 16 ) +
                ( static_cast< WordT >( value ) << 8 ) +
                static_cast< WordT >( value );
        }
        else 
        {
            return ( static_cast< WordT >( value ) << 56 ) +
                ( static_cast< WordT >( value ) << 48 ) +
                ( static_cast< WordT >( value ) << 40 ) +
                ( static_cast< WordT >( value ) << 32 ) +
                ( static_cast< WordT >( value ) << 24 ) +
                ( static_cast< WordT >( value ) << 16 ) +
                ( static_cast< WordT >( value ) << 8 ) +
                static_cast< WordT >( value );
        }
    }


    template<typename WordT>
    void BitVectorAndTest( )
    {
        using VectorType = std::vector<WordT>;
        using BitVectorType = BitVector<VectorType>;
        using WordType = WordT;

        constexpr size_t bitsPerWord = sizeof( WordType ) * CHAR_BIT;
        constexpr WordType firstWordValue = MakeWordOf<WordType>( 0b10100101 );
        constexpr WordType secondWordValue = MakeWordOf<WordType>( 0b11000011 );
        constexpr WordType expectedWordValue = firstWordValue & secondWordValue;
        

        constexpr std::array<size_t, 20> BitVectorSizes = {1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025};
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<WordType> firstBits;
            size_t firstFullWords = firstSize / bitsPerWord;
            size_t firstRemainingBits = firstSize % bitsPerWord;
            size_t firstVectorSize = firstRemainingBits ? firstFullWords + 1 : firstFullWords;
            firstBits.resize( firstVectorSize, firstWordValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<WordType> secondBits;
                size_t secondFullWords = secondSize / bitsPerWord;
                size_t secondRemainingBits = secondSize % bitsPerWord;
                size_t secondVectorSize = secondRemainingBits ? secondFullWords + 1 : secondFullWords;
                secondBits.resize( secondVectorSize, secondWordValue );
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

        constexpr size_t bitsPerWord = sizeof( WordType ) * CHAR_BIT;
        constexpr WordType firstWordValue = MakeWordOf<WordType>( 0b10100101 );
        constexpr WordType secondWordValue = MakeWordOf<WordType>( 0b11000011 );
        constexpr WordType expectedWordValue = firstWordValue & secondWordValue;


        constexpr std::array<size_t, 20> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025 };
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<WordType> firstBits;
            size_t firstFullWords = firstSize / bitsPerWord;
            size_t firstRemainingBits = firstSize % bitsPerWord;
            size_t firstVectorSize = firstRemainingBits ? firstFullWords + 1 : firstFullWords;
            firstBits.resize( firstVectorSize, firstWordValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<WordType> secondBits;
                size_t secondFullWords = secondSize / bitsPerWord;
                size_t secondRemainingBits = secondSize % bitsPerWord;
                size_t secondVectorSize = secondRemainingBits ? secondFullWords + 1 : secondFullWords;
                secondBits.resize( secondVectorSize, secondWordValue );

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

        constexpr size_t bitsPerWord = sizeof( WordType ) * CHAR_BIT;
        constexpr WordType firstWordValue = MakeWordOf<WordType>( 0b10100101 );
        constexpr WordType secondWordValue = MakeWordOf<WordType>( 0b11000011 );
        constexpr WordType expectedWordValue = firstWordValue | secondWordValue;

        constexpr std::array<size_t, 20> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025 };
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<WordType> firstBits;
            size_t firstFullWords = firstSize / bitsPerWord;
            size_t firstRemainingBits = firstSize % bitsPerWord;
            size_t firstVectorSize = firstRemainingBits ? firstFullWords + 1 : firstFullWords;
            firstBits.resize( firstVectorSize, firstWordValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<WordType> secondBits;
                size_t secondFullWords = secondSize / bitsPerWord;
                size_t secondRemainingBits = secondSize % bitsPerWord;
                size_t secondVectorSize = secondRemainingBits ? secondFullWords + 1 : secondFullWords;
                secondBits.resize( secondVectorSize, secondWordValue );
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

        constexpr size_t bitsPerWord = sizeof( WordType ) * CHAR_BIT;
        constexpr WordType firstWordValue = MakeWordOf<WordType>( 0b10100101 );
        constexpr WordType secondWordValue = MakeWordOf<WordType>( 0b11000011 );
        constexpr WordType expectedWordValue = firstWordValue | secondWordValue;

        constexpr std::array<size_t, 20> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025 };
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<WordType> firstBits;
            size_t firstFullWords = firstSize / bitsPerWord;
            size_t firstRemainingBits = firstSize % bitsPerWord;
            size_t firstVectorSize = firstRemainingBits ? firstFullWords + 1 : firstFullWords;
            firstBits.resize( firstVectorSize, firstWordValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<WordType> secondBits;
                size_t secondFullWords = secondSize / bitsPerWord;
                size_t secondRemainingBits = secondSize % bitsPerWord;
                size_t secondVectorSize = secondRemainingBits ? secondFullWords + 1 : secondFullWords;
                secondBits.resize( secondVectorSize, secondWordValue );
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

        constexpr size_t bitsPerWord = sizeof( WordType ) * CHAR_BIT;
        constexpr WordType firstWordValue = MakeWordOf<WordType>( 0b10100101 );
        constexpr WordType secondWordValue = MakeWordOf<WordType>( 0b11000011 );
        constexpr WordType expectedWordValue = firstWordValue ^ secondWordValue;

        constexpr std::array<size_t, 20> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025 };
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<WordType> firstBits;
            size_t firstFullWords = firstSize / bitsPerWord;
            size_t firstRemainingBits = firstSize % bitsPerWord;
            size_t firstVectorSize = firstRemainingBits ? firstFullWords + 1 : firstFullWords;
            firstBits.resize( firstVectorSize, firstWordValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<WordType> secondBits;
                size_t secondFullWords = secondSize / bitsPerWord;
                size_t secondRemainingBits = secondSize % bitsPerWord;
                size_t secondVectorSize = secondRemainingBits ? secondFullWords + 1 : secondFullWords;
                secondBits.resize( secondVectorSize, secondWordValue );
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

        constexpr size_t bitsPerWord = sizeof( WordType ) * CHAR_BIT;
        constexpr WordType firstWordValue = MakeWordOf<WordType>( 0b10100101 );
        constexpr WordType secondWordValue = MakeWordOf<WordType>( 0b11000011 );
        constexpr WordType expectedWordValue = firstWordValue ^ secondWordValue;

        constexpr std::array<size_t, 20> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025 };
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<WordType> firstBits;
            size_t firstFullWords = firstSize / bitsPerWord;
            size_t firstRemainingBits = firstSize % bitsPerWord;
            size_t firstVectorSize = firstRemainingBits ? firstFullWords + 1 : firstFullWords;
            firstBits.resize( firstVectorSize, firstWordValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<WordType> secondBits;
                size_t secondFullWords = secondSize / bitsPerWord;
                size_t secondRemainingBits = secondSize % bitsPerWord;
                size_t secondVectorSize = secondRemainingBits ? secondFullWords + 1 : secondFullWords;
                secondBits.resize( secondVectorSize, secondWordValue );
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

        constexpr size_t bitsPerWord = sizeof( WordType ) * CHAR_BIT;
        constexpr WordType firstWordValue = MakeWordOf<WordType>( 0b10100101 );
        constexpr WordType secondWordValue = MakeWordOf<WordType>( 0b11000011 );

        constexpr std::array<size_t, 20> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,127,128,129, 1023, 1024, 1025 };
        for ( auto firstSize : BitVectorSizes )
        {
            std::vector<WordType> firstBits;
            size_t firstFullWords = firstSize / bitsPerWord;
            size_t firstRemainingBits = firstSize % bitsPerWord;
            size_t firstVectorSize = firstRemainingBits ? firstFullWords + 1 : firstFullWords;
            firstBits.resize( firstVectorSize, firstWordValue );
            BitVectorType firstBitVector( firstBits.data( ), firstSize );

            for ( auto secondSize : BitVectorSizes )
            {
                std::vector<WordType> secondBits;
                size_t secondFullWords = secondSize / bitsPerWord;
                size_t secondRemainingBits = secondSize % bitsPerWord;
                size_t secondVectorSize = secondRemainingBits ? secondFullWords + 1 : secondFullWords;
                secondBits.resize( secondVectorSize, secondWordValue );
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

        constexpr size_t bitsPerWord = sizeof( WordType ) * CHAR_BIT;
        constexpr WordType wordValue = MakeWordOf<WordType>( 0b10100101 );

        constexpr std::array<size_t, 23> BitVectorSizes = { 1,2,7,8,9,15,16,17,31,32,33,63,64,65,95,96,97,127,128,129, 1023, 1024, 1025 };
        for ( auto bitVectorSize : BitVectorSizes )
        {
            std::vector<WordT> bits;
            const size_t fullWordCount = bitVectorSize / bitsPerWord;
            const size_t fullWordOverflowBitCount = bitVectorSize % bitsPerWord;
            const size_t vectorSize = fullWordOverflowBitCount ? fullWordCount + 1 : fullWordCount;
            bits.resize( vectorSize, wordValue );
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