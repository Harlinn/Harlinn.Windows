#pragma once

#include <HCCVectorMath.h>
#include <HCCString.h>
#include <random>
#include <pbrto/util/vecmath.h>
#include <DirectXMath.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

template<typename FloatT, size_t N >
struct RandomGenerator
{
    using FloatType = FloatT;
    std::array<FloatType, N> Values;
    size_t Counter = 0;
    RandomGenerator( FloatT lowerBound = -10000, FloatT upperBound = 10000 )
    {
        std::uniform_real_distribution<FloatType> unif( lowerBound, upperBound );
        std::default_random_engine re;
        for ( size_t i = 0; i < N; i++ )
        {
            Values[ i ] = unif( re );
        }
    }
    __forceinline FloatType operator( )( )
    {
        return Values[ Counter++ % N ];
    }
    void Reset( )
    {
        Counter = 0;
    }
};

inline double Deviation( double first, double second )
{
    return Harlinn::Common::Core::Math::Abs( first - second ) / Harlinn::Common::Core::Math::Abs( first );
}




