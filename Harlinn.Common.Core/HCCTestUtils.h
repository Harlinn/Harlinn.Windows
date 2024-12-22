#pragma once
#ifndef HCCTESTUTILS_H_
#define HCCTESTUTILS_H_

#include "HCCMath.h"

namespace Harlinn::Common::Core::Test
{

    

    namespace Internal
    {
        template<typename T>
            requires std::is_floating_point_v<T>
        bool IsNaN( T v )
        {
            return std::isnan( v );
        }
        template<typename T>
            requires std::is_integral_v<T>
        bool IsNaN( T v )
        {
            return false;
        }

        template<typename T, typename U>
            requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
        bool IsNaN( const std::pair<T, U>& pair )
        {
            return IsNaN( pair.first ) || IsNaN( pair.second );
        }


        template<typename T>
            requires std::is_floating_point_v<T>
        bool IsInf( T v )
        {
            return std::isinf( v );
        }
        template<typename T>
            requires std::is_integral_v<T>
        bool IsInf( T v )
        {
            return false;
        }

        template<typename T, typename U>
            requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
        bool IsInf( const std::pair<T, U>& pair )
        {
            return IsInf( pair.first ) || IsInf( pair.second );
        }
    }

    inline double Deviation( double first, double second )
    {
        // If both is NaN, the results don't deviate
        if ( std::isnan( first ) )
        {
            if ( std::isnan( second ) )
            {
                return 0.0;
            }
            return std::numeric_limits<double>::infinity( );
        }
        else if ( std::isnan( second ) )
        {
            // The second value is NaN, but not the first
            return std::numeric_limits<double>::infinity( );
        }
        if ( std::isinf( first ) )
        {
            if ( std::isinf( second ) )
            {
                if ( first > 0. && second > 0. )
                {
                    // Both values are +infinity
                    return 0;
                }
                else if ( first < 0. && second < 0. )
                {
                    // Both values are -infinity
                    return 0;
                }
                // Opposite signs
                return std::numeric_limits<double>::infinity( );
            }
            // only the first value is infinite
            return std::numeric_limits<double>::infinity( );
        }
        else if ( std::isinf( second ) )
        {
            // only the second value is infinite
            return std::numeric_limits<double>::infinity( );
        }

        // Avoid division by zero
        if ( first != 0.0 )
        {
            using std::abs;
            if ( first <= second )
            {
                return abs( second - first ) / abs( first );
            }
            else
            {
                return abs( first - second ) / abs( first );
            }
        }
        else
        {
            // When second is very close to zero, the result is zero deviation
            constexpr double veryCloseToZero = 5e-323;
            auto absSecond = abs( second );
            if ( absSecond <= veryCloseToZero )
            {
                return 0.0;
            }
            // May still be very close to zero, but will cause the test to fail.
            return 1.0;
        }
    }

    template<typename T, typename U>
        requires std::is_arithmetic_v<T>&& std::is_arithmetic_v<U>
    inline double Deviation( const std::pair<T, U> first, const std::pair<T, U> second )
    {
        using std::abs;
        auto deviation1 = Deviation( first.first, second.first );
        auto deviation2 = Deviation( first.second, second.second );
        return std::max( deviation1, deviation2 );
    }

    
    namespace Generators
    {
        class RandomGeneratorBase
        {};


        /// <summary>
        /// Precomputes <c>N</c> random values.
        /// </summary>
        /// <typeparam name="ValueT">
        /// An arithmetic type
        /// </typeparam>
        /// <typeparam name="N">
        /// The number of values to generate.
        /// </typeparam>
        template<typename ValueT, size_t N >
            requires std::is_arithmetic_v<ValueT>
        struct RandomGenerator : public RandomGeneratorBase
        {
            using value_type = ValueT;
            static constexpr size_t Size = N;
            std::array<value_type, Size> Values;
            size_t Counter = 0;
            const value_type LowerBound;
            const value_type UpperBound;
            
            RandomGenerator( value_type lowerBound = -1e100, value_type upperBound = 1e100 )
                : LowerBound( lowerBound ), UpperBound( upperBound )
            {
                if constexpr ( std::is_floating_point_v<value_type> )
                {
                    std::uniform_real_distribution<value_type> unif( lowerBound, upperBound );
                    std::default_random_engine re;
                    for ( size_t i = 0; i < Size; i++ )
                    {
                        Values[ i ] = unif( re );
                    }
                }
                else
                {
                    std::uniform_int_distribution<value_type> unif( lowerBound, upperBound );
                    std::default_random_engine re;
                    for ( size_t i = 0; i < Size; i++ )
                    {
                        Values[ i ] = unif( re );
                    }
                }
            }

            /// <summary>
            /// Retrieves the random number at offset <c>Counter % N</c>, 
            /// incrementing <c>Counter</c>.
            /// </summary>
            /// <returns>
            /// A random number.
            /// </returns>
            __forceinline value_type operator( )( )
            {
                return Values[ Counter++ % Size ];
            }
            /// <summary>
            /// Resets <c>Counter</c>.
            /// </summary>
            void Reset( )
            {
                Counter = 0;
            }
        };

        template<typename T> 
        concept IsRandomGenerator = std::is_base_of_v<RandomGeneratorBase, std::remove_cvref_t<T>>;

        class RangeGeneratorBase
        {

        };

        template<typename T>
        concept IsRangeGenerator = std::is_base_of_v<RangeGeneratorBase, std::remove_cvref_t<T>>;

        template<typename ValueT >
            requires std::is_arithmetic_v<ValueT>
        struct RangeGenerator : public RangeGeneratorBase
        {
            using value_type = ValueT;
            value_type Value;
            const value_type LowerBound;
            const value_type UpperBound;
            RangeGenerator( value_type lowerBound, value_type upperBound )
                : Value( lowerBound ), LowerBound( lowerBound ), UpperBound( upperBound )
            {
            }

        private:
            value_type NextValue( )
            {
                if constexpr ( std::is_same_v<value_type, float> )
                {
                    return Math::NextUp( Value );
                }
                else if constexpr ( std::is_same_v<value_type, double> )
                {
                    return static_cast< double >( Math::NextUp( static_cast< float >( Value ) ) );
                }
                else
                {
                    return Value + static_cast< value_type >( 1 );
                }
            }
        public:

            /// <summary>
            /// Retrieves the current value of <c>Value</c>, 
            /// setting <c>Value</c> to the next value in the range.
            /// </summary>
            /// <returns>
            /// The current value of <c>Value</c>.
            /// </returns>
            __forceinline value_type operator( )( )
            {
                auto result = Value;
                Value = NextValue( );
                return result;
            }

            bool InRange( ) const
            {
                return Value >= LowerBound && Value <= UpperBound;
            }

            /// <summary>
            /// Resets <c>Value</c>.
            /// </summary>
            void Reset( )
            {
                Value = LowerBound;
            }
        };

    }

    struct NumericTest
    {
        std::string TestName;
        Int64 UnexpectedDeviationCount = 0;
        Int64 TestCount = 0;
        Int64 EqualCount = 0;
        bool IsFirst = true;
        double MaxDeviation = 0.0;
        double MaxDeviationFor = 0.0;
        double MaxDeviationExpectedResult = 0.0;
        double MaxDeviationMathResult = 0.0;
        double MaxAllowedDeviation = 1e-5;
        double FirstDeviation = 0.0;
        double LastDeviation = 0.0;

        NumericTest( const std::string& testName )
            : TestName( testName )
        { }
    private:
        template<typename T>
        bool NaNAndInfCheck( T expectedResult, T testResult )
        {
            if ( Test::Internal::IsNaN( expectedResult ) )
            {
                if ( Test::Internal::IsNaN( testResult ) == false )
                {
                    UnexpectedDeviationCount++;
                    return true;
                }
                return true;
            }
            else if ( Test::Internal::IsNaN( testResult ) )
            {
                UnexpectedDeviationCount++;
                return true;
            }
            if ( Test::Internal::IsInf( expectedResult ) )
            {
                if ( Test::Internal::IsInf( testResult ) == false )
                {
                    UnexpectedDeviationCount++;
                    return true;
                }
                return true;
            }
            else if ( Test::Internal::IsInf( testResult ) )
            {
                UnexpectedDeviationCount++;
                return true;
            }
            return false;
        }

        template<typename T, typename U>
        void DeviationCheck( T value, U expectedResult, U testResult )
        {
            if ( expectedResult == testResult )
            {
                EqualCount++;
            }
            auto deviation = Deviation( expectedResult, testResult );

            if ( deviation > MaxDeviation )
            {
                MaxDeviationFor = value;
                MaxDeviation = deviation;
                if constexpr ( IsStdPair<U> )
                {
                    MaxDeviationExpectedResult = expectedResult.first;
                    MaxDeviationMathResult = testResult.first;
                }
                else
                {
                    MaxDeviationExpectedResult = expectedResult;
                    MaxDeviationMathResult = testResult;
                }
            }

            if ( deviation > MaxAllowedDeviation )
            {
                if ( IsFirst )
                {
                    FirstDeviation = value;
                    IsFirst = false;
                }
                LastDeviation = value;
                UnexpectedDeviationCount++;
            }
        }

    public:
        template<typename GeneratorT>
            requires Generators::IsRandomGenerator<GeneratorT>
        bool Run( GeneratorT& generator, 
            std::function<typename GeneratorT::value_type( typename GeneratorT::value_type)> expectedFunc, 
            std::function<typename GeneratorT::value_type( typename GeneratorT::value_type )> testFunc, 
            std::initializer_list<typename GeneratorT::value_type> specialValues )
        {
            for ( auto value : specialValues )
            {
                auto expectedResult = expectedFunc( value );
                auto testResult = testFunc( value );
                if ( NaNAndInfCheck( expectedResult, testResult ) == false )
                {
                    DeviationCheck( value, expectedResult, testResult );
                }
                TestCount++;
            }

            for ( size_t i = 0; i < GeneratorT::Size; i++ )
            {
                auto value = generator( );
                auto expectedResult = expectedFunc( value );
                auto testResult = testFunc( value );
                if ( NaNAndInfCheck( expectedResult, testResult ) == false )
                {
                    DeviationCheck( value, expectedResult, testResult );
                }
                TestCount++;
            }
            Print( );
            return UnexpectedDeviationCount == 0;
        }
        
        template<typename GeneratorT>
            //requires Generators::IsRandomGenerator<GeneratorT>
        bool Run( GeneratorT& generator,
            std::function<typename GeneratorT::value_type( typename GeneratorT::value_type )> expectedFunc,
            std::function<typename GeneratorT::value_type( typename GeneratorT::value_type )> testFunc )
        {
            return operator()( generator, expectedFunc, testFunc, {} );
        }

        template<typename GeneratorT>
            requires Generators::IsRandomGenerator<GeneratorT>
        bool Run( GeneratorT& generator,
            std::function<std::pair<typename GeneratorT::value_type, typename GeneratorT::value_type>( typename GeneratorT::value_type )> expectedFunc,
            std::function<std::pair<typename GeneratorT::value_type, typename GeneratorT::value_type>( typename GeneratorT::value_type )> testFunc,
            std::initializer_list<typename GeneratorT::value_type> specialValues )
        {
            for ( auto value : specialValues )
            {
                auto expectedResult = expectedFunc( value );
                auto testResult = testFunc( value );
                if ( NaNAndInfCheck( expectedResult, testResult ) == false )
                {
                    DeviationCheck( value, expectedResult, testResult );
                }
                TestCount++;
            }

            for ( size_t i = 0; i < GeneratorT::Size; i++ )
            {
                auto value = generator( );
                auto expectedResult = expectedFunc( value );
                auto testResult = testFunc( value );
                if ( NaNAndInfCheck( expectedResult, testResult ) == false )
                {
                    DeviationCheck( value, expectedResult, testResult );
                }
                TestCount++;
            }
            Print( );
            return UnexpectedDeviationCount == 0;
        }

        
        template<typename GeneratorT>
            requires Generators::IsRangeGenerator<GeneratorT>
        bool Run( GeneratorT& generator, 
            std::function<typename GeneratorT::value_type( typename GeneratorT::value_type )> expectedFunc,
            std::function<typename GeneratorT::value_type( typename GeneratorT::value_type )> testFunc,
            std::initializer_list<typename GeneratorT::value_type> specialValues )
        {
            for ( auto value : specialValues )
            {
                auto expectedResult = expectedFunc( value );
                auto testResult = testFunc( value );
                if ( NaNAndInfCheck( expectedResult, testResult ) == false )
                {
                    DeviationCheck( value, expectedResult, testResult );
                }
                TestCount++;
            }

            while ( generator.InRange( ) )
            {
                auto value = generator( );
                auto expectedResult = expectedFunc( value );
                auto testResult = testFunc( value );

                if ( NaNAndInfCheck( expectedResult, testResult ) == false )
                {
                    DeviationCheck( value, expectedResult, testResult );
                }
                TestCount++;
            }
            Print( );
            return UnexpectedDeviationCount == 0;
        }
        

        void Print( )
        {
            if ( UnexpectedDeviationCount )
            {
                std::println(std::cout, "{} -> Iterations: {}, Equal {}, unexpected deviations: {}, max deviation: {:.12g}, for: {:.12g}, expected: {:.12g}, test: {:.12g}, first unexpected: {:g}, last unexpected: {:g}",
                    TestName, TestCount, EqualCount, UnexpectedDeviationCount, MaxDeviation, MaxDeviationFor, MaxDeviationExpectedResult, MaxDeviationMathResult, FirstDeviation, LastDeviation );
            }
            else
            {
                if ( MaxDeviation )
                {
                    std::println( std::cout, "{} -> Iterations: {}, Equal {}, no unexpected deviations, max deviation: {:.12g}, for: {:.12g}, expected: {:.12g}, test: {:.12g}",
                        TestName, TestCount, EqualCount, MaxDeviation, MaxDeviationFor, MaxDeviationExpectedResult, MaxDeviationMathResult );
                }
                else
                {
                    std::println( std::cout, "{} -> Iterations: {}, Equal {}, no unexpected deviations.", TestName, TestCount, EqualCount );
                }
            }
        }

    };






}

#endif
