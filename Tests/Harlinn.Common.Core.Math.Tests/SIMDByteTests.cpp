#include "pch.h"

#include <HCCMath.h>


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
BOOST_FIXTURE_TEST_SUITE( SIMDByteTests, LocalFixture )

struct LoadStore1Test1Impl
{
    template<size_t N>
    static void Run( const std::array<Byte, 32>& values )
    {
        using Traits = SIMD::Traits<Byte, N>;
        auto rmm1 = Traits::Load( values.data( ) );
        alignas( Traits::AlignAs ) std::array<Byte, 32> result{};
        Traits::Store( result.data( ), rmm1 );

        for ( size_t i = 0; i < N; i++ )
        {
            BOOST_CHECK( result[ i ] == values[ i ] );
        }
        for ( size_t i = N; i < 32; i++ )
        {
            BOOST_CHECK( result[ i ] == 0x00 );
        }
    };
};

// --run_test=SIMDByteTests/LoadStore1Test1
BOOST_AUTO_TEST_CASE( LoadStore1Test1 )
{
    std::array<Byte, 32> values
    {
        1,2,3,4,5,6,7,8,
        9,10,11,12,13,14,15,16,
        17,18,19,20,21,22,23,24,
        25,26,27,28,29,30,31,32
    };
    LoadStore1Test1Impl::Run<1>( values );
    LoadStore1Test1Impl::Run<2>( values );
    LoadStore1Test1Impl::Run<3>( values );
    LoadStore1Test1Impl::Run<4>( values );
    LoadStore1Test1Impl::Run<5>( values );
    LoadStore1Test1Impl::Run<6>( values );
    LoadStore1Test1Impl::Run<7>( values );
    LoadStore1Test1Impl::Run<8>( values );
    LoadStore1Test1Impl::Run<9>( values );
    LoadStore1Test1Impl::Run<10>( values );
    LoadStore1Test1Impl::Run<11>( values );
    LoadStore1Test1Impl::Run<12>( values );
    LoadStore1Test1Impl::Run<13>( values );
    LoadStore1Test1Impl::Run<14>( values );
    LoadStore1Test1Impl::Run<15>( values );
    LoadStore1Test1Impl::Run<16>( values );
    LoadStore1Test1Impl::Run<17>( values );
    LoadStore1Test1Impl::Run<18>( values );
    LoadStore1Test1Impl::Run<19>( values );
    LoadStore1Test1Impl::Run<20>( values );
    LoadStore1Test1Impl::Run<21>( values );
    LoadStore1Test1Impl::Run<22>( values );
    LoadStore1Test1Impl::Run<23>( values );
    LoadStore1Test1Impl::Run<24>( values );
    LoadStore1Test1Impl::Run<25>( values );
    LoadStore1Test1Impl::Run<26>( values );
    LoadStore1Test1Impl::Run<27>( values );
    LoadStore1Test1Impl::Run<28>( values );
    LoadStore1Test1Impl::Run<29>( values );
    LoadStore1Test1Impl::Run<30>( values );
    LoadStore1Test1Impl::Run<31>( values );
    LoadStore1Test1Impl::Run<32>( values );
    
    
}
BOOST_AUTO_TEST_SUITE_END( )