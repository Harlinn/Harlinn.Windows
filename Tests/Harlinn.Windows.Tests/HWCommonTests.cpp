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

#include <HWCommon.h>
#include <HCCDateTime.h>
#include <HCCGuid.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Windows;
using namespace Harlinn::Windows::Graphics;


namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( HWCommonTests, LocalFixture )


// --run_test=HWCommonTests/PointConstructorTest1
BOOST_AUTO_TEST_CASE( PointConstructorTest1 )
{
    Point point;
    BOOST_CHECK( point.X( ) == 0 );
    BOOST_CHECK( point.Y( ) == 0 );

    POINT pt = point;

}

// --run_test=HWCommonTests/PointConstructorTest2
BOOST_AUTO_TEST_CASE( PointConstructorTest2 )
{
    SByte x = 1;
    SByte y = 1;
    Point point( x, y );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest3
BOOST_AUTO_TEST_CASE( PointConstructorTest3 )
{
    SByte x = 1;
    bool y = true;
    Point point( x, y );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest4
BOOST_AUTO_TEST_CASE( PointConstructorTest4 )
{
    SByte x = 1;
    double y = 1;
    Point point( x, y );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest5
BOOST_AUTO_TEST_CASE( PointConstructorTest5 )
{
    int x = 1;
    int y = 1;
    POINT pt{ x,y };

    Point point( pt );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest6
BOOST_AUTO_TEST_CASE( PointConstructorTest6 )
{
    int x = 1;
    int y = 1;
    SIZE sz{ x,y };

    Point point( sz );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest7
BOOST_AUTO_TEST_CASE( PointConstructorTest7 )
{
    float x = 1;
    float y = 1;
    D2D_POINT_2F pt{ x,y };

    Point point( pt );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest8
BOOST_AUTO_TEST_CASE( PointConstructorTest8 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    D2D_POINT_2U pt{ x,y };

    Point point( pt );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest9
BOOST_AUTO_TEST_CASE( PointConstructorTest9 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::PointF pt{ x,y };

    Point point( pt );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest10
BOOST_AUTO_TEST_CASE( PointConstructorTest10 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::PointU pt{ x,y };

    Point point( pt );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest11
BOOST_AUTO_TEST_CASE( PointConstructorTest11 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::SizeF sz{ x,y };

    Point point( sz );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest12
BOOST_AUTO_TEST_CASE( PointConstructorTest12 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::SizeU sz{ x,y };

    Point point( sz );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}



// --run_test=HWCommonTests/PointConstructorTest13
BOOST_AUTO_TEST_CASE( PointConstructorTest13 )
{
    float x = 1;
    float y = 1;
    D2D_SIZE_F sz{ x,y };

    Point point( sz );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest14
BOOST_AUTO_TEST_CASE( PointConstructorTest14 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    D2D_SIZE_U sz{ x,y };

    Point point( sz );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest15
BOOST_AUTO_TEST_CASE( PointConstructorTest15 )
{
    
    int x = 1;
    int y = 1;
    Harlinn::Windows::Rectangle rect( x, y, 5, 5 );

    Point point( rect );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest16
BOOST_AUTO_TEST_CASE( PointConstructorTest16 )
{
    int x = 1;
    int y = 1;
    Graphics::RectangleF rect( x, y, 5, 5 );

    Point point( rect );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointConstructorTest17
BOOST_AUTO_TEST_CASE( PointConstructorTest17 )
{
    int x = 1;
    int y = 1;
    Graphics::RectangleU rect( x, y, 5, 5 );

    Point point( rect );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}



// --run_test=HWCommonTests/PointConstructorTest18
BOOST_AUTO_TEST_CASE( PointConstructorTest18 )
{
    int x = 1;

    Point point( x );
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( x ) );
}


// --run_test=HWCommonTests/PointAssignTest1
BOOST_AUTO_TEST_CASE( PointAssignTest1 )
{
    int x = 1;
    int y = 1;
    POINT pt{ x,y };

    Point point;
    point = pt;
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointAssignTest2
BOOST_AUTO_TEST_CASE( PointAssignTest2 )
{
    int x = 1;
    int y = 1;
    SIZE sz{ x,y };

    Point point;
    point = sz;
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointAssignTest3
BOOST_AUTO_TEST_CASE( PointAssignTest3 )
{
    float x = 1;
    float y = 1;
    D2D_POINT_2F pt{ x,y };

    Point point;
    point = pt;
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointAssignTest4
BOOST_AUTO_TEST_CASE( PointAssignTest4 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    D2D_POINT_2U pt{ x,y };

    Point point;
    point = pt;
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointAssignTest5
BOOST_AUTO_TEST_CASE( PointAssignTest5 )
{
    float x = 1;
    float y = 1;
    D2D_SIZE_F sz{ x,y };

    Point point;
    point = sz;
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointAssignTest6
BOOST_AUTO_TEST_CASE( PointAssignTest6 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    D2D_SIZE_U sz{ x,y };

    Point point;
    point = sz;
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointAssignTest7
BOOST_AUTO_TEST_CASE( PointAssignTest7 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::PointF pt{ x,y };

    Point point;
    point = pt;
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointAssignTest8
BOOST_AUTO_TEST_CASE( PointAssignTest8 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::PointU pt{ x,y };

    Point point;
    point = pt;
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointAssignTest9
BOOST_AUTO_TEST_CASE( PointAssignTest9 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::SizeF sz{ x,y };

    Point point;
    point = sz;
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointAssignTest10
BOOST_AUTO_TEST_CASE( PointAssignTest10 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::SizeU sz{ x,y };

    Point point;
    point = sz;
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}


// --run_test=HWCommonTests/PointAssignTest11
BOOST_AUTO_TEST_CASE( PointAssignTest11 )
{
    int x = 1;
    int y = 1;
    Harlinn::Windows::Rectangle rect( x, y, 5, 5 );

    Point point;
    point = rect;
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointAssignTest12
BOOST_AUTO_TEST_CASE( PointAssignTest12 )
{
    int x = 1;
    int y = 1;
    Graphics::RectangleF rect( x, y, 5, 5 );

    Point point;
    point = rect;
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointAssignTest13
BOOST_AUTO_TEST_CASE( PointAssignTest13 )
{
    int x = 1;
    int y = 1;
    Graphics::RectangleU rect( x, y, 5, 5 );

    Point point;
    point = rect;
    BOOST_CHECK( point.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Point::value_type>( y ) );
}

// --run_test=HWCommonTests/PointAssignTest14
BOOST_AUTO_TEST_CASE( PointAssignTest14 )
{
    int x = 1;
    Point point1( x );

    Point point2;
    point2 = point1;
    BOOST_CHECK( point2.X( ) == static_cast<Point::value_type>( x ) );
    BOOST_CHECK( point2.Y( ) == static_cast<Point::value_type>( x ) );
}

// --run_test=HWCommonTests/SizeConstructorTest1
BOOST_AUTO_TEST_CASE( SizeConstructorTest1 )
{
    Size size;
    BOOST_CHECK( size.Width( ) == 0 );
    BOOST_CHECK( size.Height( ) == 0 );
}

// --run_test=HWCommonTests/SizeConstructorTest2
BOOST_AUTO_TEST_CASE( SizeConstructorTest2 )
{
    SByte x = 1;
    SByte y = 1;
    Size size( x, y );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest3
BOOST_AUTO_TEST_CASE( SizeConstructorTest3 )
{
    SByte x = 1;
    bool y = true;
    Size size( x, y );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest4
BOOST_AUTO_TEST_CASE( SizeConstructorTest4 )
{
    SByte x = 1;
    double y = 1;
    Size size( x, y );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest5
BOOST_AUTO_TEST_CASE( SizeConstructorTest5 )
{
    int x = 1;
    int y = 1;
    POINT pt{ x,y };

    Size size( pt );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest6
BOOST_AUTO_TEST_CASE( SizeConstructorTest6 )
{
    int x = 1;
    int y = 1;
    SIZE sz{ x,y };

    Size size( sz );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest7
BOOST_AUTO_TEST_CASE( SizeConstructorTest7 )
{
    float x = 1;
    float y = 1;
    D2D_POINT_2F pt{ x,y };

    Size size( pt );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest8
BOOST_AUTO_TEST_CASE( SizeConstructorTest8 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    D2D_POINT_2U pt{ x,y };

    Size size( pt );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest9
BOOST_AUTO_TEST_CASE( SizeConstructorTest9 )
{
    float x = 1;
    float y = 1;
    D2D_SIZE_F sz{ x,y };

    Size size( sz );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest10
BOOST_AUTO_TEST_CASE( SizeConstructorTest10 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    D2D_SIZE_U sz{ x,y };

    Size size( sz );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest11
BOOST_AUTO_TEST_CASE( SizeConstructorTest11 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::PointF pt{ x,y };

    Size size( pt );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest12
BOOST_AUTO_TEST_CASE( SizeConstructorTest12 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::PointU pt{ x,y };

    Size size( pt );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest13
BOOST_AUTO_TEST_CASE( SizeConstructorTest13 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::SizeF sz{ x,y };

    Size size( sz );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest14
BOOST_AUTO_TEST_CASE( SizeConstructorTest14 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::SizeU sz{ x,y };

    Size size( sz );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}



// --run_test=HWCommonTests/SizeConstructorTest15
BOOST_AUTO_TEST_CASE( SizeConstructorTest15 )
{
    int x = 1;
    int y = 1;
    Harlinn::Windows::Rectangle rect( 0, 0, x, y );

    Size size( rect );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest16
BOOST_AUTO_TEST_CASE( SizeConstructorTest16 )
{
    int x = 1;
    int y = 1;
    Graphics::RectangleF rect( 0, 0, x, y );

    Size size( rect );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeConstructorTest17
BOOST_AUTO_TEST_CASE( SizeConstructorTest17 )
{
    int x = 1;
    int y = 1;
    Graphics::RectangleF rect( 0, 0, x, y );

    Size size( rect );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}



// --run_test=HWCommonTests/SizeConstructorTest18
BOOST_AUTO_TEST_CASE( SizeConstructorTest18 )
{
    int x = 1;

    Size size( x );
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( x ) );
}


// --run_test=HWCommonTests/SizeAssignTest1
BOOST_AUTO_TEST_CASE( SizeAssignTest1 )
{
    int x = 1;
    int y = 1;
    POINT pt{ x,y };

    Size size;
    size = pt;
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeAssignTest2
BOOST_AUTO_TEST_CASE( SizeAssignTest2 )
{
    int x = 1;
    int y = 1;
    SIZE sz{ x,y };

    Size size;
    size = sz;
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeAssignTest3
BOOST_AUTO_TEST_CASE( SizeAssignTest3 )
{
    float x = 1;
    float y = 1;
    D2D_POINT_2F pt{ x,y };

    Size size;
    size = pt;
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeAssignTest4
BOOST_AUTO_TEST_CASE( SizeAssignTest4 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    D2D_POINT_2U pt{ x,y };

    Size size;
    size = pt;
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeAssignTest5
BOOST_AUTO_TEST_CASE( SizeAssignTest5 )
{
    float x = 1;
    float y = 1;
    D2D_SIZE_F sz{ x,y };

    Size size;
    size = sz;
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeAssignTest6
BOOST_AUTO_TEST_CASE( SizeAssignTest6 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    D2D_SIZE_U sz{ x,y };

    Size size;
    size = sz;
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeAssignTest7
BOOST_AUTO_TEST_CASE( SizeAssignTest7 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::PointF pt{ x,y };

    Size size;
    size = pt;
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeAssignTest8
BOOST_AUTO_TEST_CASE( SizeAssignTest8 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::PointU pt{ x,y };

    Size size;
    size = pt;
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeAssignTest9
BOOST_AUTO_TEST_CASE( SizeAssignTest9 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::SizeF sz{ x,y };

    Size size;
    size = sz;
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeAssignTest10
BOOST_AUTO_TEST_CASE( SizeAssignTest10 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::SizeU sz{ x,y };

    Size size;
    size = sz;
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}


// --run_test=HWCommonTests/SizeAssignTest11
BOOST_AUTO_TEST_CASE( SizeAssignTest11 )
{
    int x = 1;
    int y = 1;
    Harlinn::Windows::Rectangle rect( 0, 0, x, y );

    Size size;
    size = rect;
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}

// --run_test=HWCommonTests/SizeAssignTest12
BOOST_AUTO_TEST_CASE( SizeAssignTest12 )
{
    int x = 1;
    int y = 1;
    Graphics::RectangleF rect( 0, 0, x, y );

    Size size;
    size = rect;
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}


// --run_test=HWCommonTests/SizeAssignTest13
BOOST_AUTO_TEST_CASE( SizeAssignTest13 )
{
    int x = 1;
    int y = 1;
    Graphics::RectangleU rect( 0, 0, x, y );

    Size size;
    size = rect;
    BOOST_CHECK( size.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size.Height( ) == static_cast<Size::value_type>( y ) );
}


// --run_test=HWCommonTests/SizeAssignTest14
BOOST_AUTO_TEST_CASE( SizeAssignTest14 )
{
    int x = 1;
    Size size1( x );

    Size size2;
    size2 = size1;
    BOOST_CHECK( size2.Width( ) == static_cast<Size::value_type>( x ) );
    BOOST_CHECK( size2.Height( ) == static_cast<Size::value_type>( x ) );
}

// --run_test=HWCommonTests/PointFConstructorTest1
BOOST_AUTO_TEST_CASE( PointFConstructorTest1 )
{
    Graphics::PointF point;
    BOOST_CHECK( point.X( ) == 0 );
    BOOST_CHECK( point.Y( ) == 0 );
}

// --run_test=HWCommonTests/PointFConstructorTest2
BOOST_AUTO_TEST_CASE( PointFConstructorTest2 )
{
    SByte x = 1;
    SByte y = 1;
    Graphics::PointF point( x, y );
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFConstructorTest3
BOOST_AUTO_TEST_CASE( PointFConstructorTest3 )
{
    SByte x = 1;
    bool y = true;
    Graphics::PointF point( x, y );
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFConstructorTest4
BOOST_AUTO_TEST_CASE( PointFConstructorTest4 )
{
    SByte x = 1;
    double y = 1.5;
    Graphics::PointF point( x, y );
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == y );
}

// --run_test=HWCommonTests/PointFConstructorTest5
BOOST_AUTO_TEST_CASE( PointFConstructorTest5 )
{
    int x = 1;
    int y = 1;
    POINT pt{ x,y };

    Graphics::PointF point( pt );
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFConstructorTest6
BOOST_AUTO_TEST_CASE( PointFConstructorTest6 )
{
    int x = 1;
    int y = 1;
    SIZE sz{ x,y };

    Graphics::PointF point( sz );
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFConstructorTest7
BOOST_AUTO_TEST_CASE( PointFConstructorTest7 )
{
    float x = 1.4f;
    float y = 1.6f;
    D2D_POINT_2F pt{ x,y };

    Graphics::PointF point( pt );
    BOOST_CHECK( point.X( ) == x );
    BOOST_CHECK( point.Y( ) == y );
}

// --run_test=HWCommonTests/PointFConstructorTest8
BOOST_AUTO_TEST_CASE( PointFConstructorTest8 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    D2D_POINT_2U pt{ x,y };

    Graphics::PointF point( pt );
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFConstructorTest9
BOOST_AUTO_TEST_CASE( PointFConstructorTest9 )
{
    float x = 1.4f;
    float y = 1.6f;
    Graphics::PointF pt{ x,y };

    Graphics::PointF point( pt );
    BOOST_CHECK( point.X( ) == x );
    BOOST_CHECK( point.Y( ) == y );
}

// --run_test=HWCommonTests/PointFConstructorTest10
BOOST_AUTO_TEST_CASE( PointFConstructorTest10 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::PointU pt{ x,y };

    Graphics::PointF point( pt );
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFConstructorTest11
BOOST_AUTO_TEST_CASE( PointFConstructorTest11 )
{
    float x = 1.4f;
    float y = 1.6f;
    Graphics::SizeF sz{ x,y };

    Graphics::PointF point( sz );
    BOOST_CHECK( point.X( ) == x );
    BOOST_CHECK( point.Y( ) == y );
}

// --run_test=HWCommonTests/PointFConstructorTest12
BOOST_AUTO_TEST_CASE( PointFConstructorTest12 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::SizeU sz{ x,y };

    Graphics::PointF point( sz );
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}



// --run_test=HWCommonTests/PointFConstructorTest13
BOOST_AUTO_TEST_CASE( PointFConstructorTest13 )
{
    float x = 1.4f;
    float y = 1.6f;
    D2D_SIZE_F sz{ x,y };

    Graphics::PointF point( sz );
    BOOST_CHECK( point.X( ) == x );
    BOOST_CHECK( point.Y( ) == y );
}

// --run_test=HWCommonTests/PointFConstructorTest14
BOOST_AUTO_TEST_CASE( PointFConstructorTest14 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    D2D_SIZE_U sz{ x,y };

    Graphics::PointF point( sz );
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFConstructorTest15
BOOST_AUTO_TEST_CASE( PointFConstructorTest15 )
{

    int x = 1;
    int y = 1;
    Harlinn::Windows::Rectangle rect( x, y, 5, 5 );

    Graphics::PointF point( rect );
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFConstructorTest16
BOOST_AUTO_TEST_CASE( PointFConstructorTest16 )
{
    float x = 1.4f;
    float y = 1.6f;
    Graphics::RectangleF rect( x, y, 5, 5 );;

    Graphics::PointF point( rect );
    BOOST_CHECK( point.X( ) == x );
    BOOST_CHECK( point.Y( ) == y );
}

// --run_test=HWCommonTests/PointFConstructorTest17
BOOST_AUTO_TEST_CASE( PointFConstructorTest17 )
{
    int x = 1;
    int y = 1;
    Graphics::RectangleU rect( x, y, 5, 5 );;

    Graphics::PointF point( rect );
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}



// --run_test=HWCommonTests/PointFConstructorTest18
BOOST_AUTO_TEST_CASE( PointFConstructorTest18 )
{
    int x = 1;

    Graphics::PointF point( x );
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( x ) );
}

// --run_test=HWCommonTests/PointFConstructorTest19
BOOST_AUTO_TEST_CASE( PointFConstructorTest19 )
{
    float x = 1.5;

    Graphics::PointF point( x );
    BOOST_CHECK( point.X( ) == x );
    BOOST_CHECK( point.Y( ) == x );
}



// --run_test=HWCommonTests/PointFAssignOperatorTest1
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest1 )
{
    int x = 1;
    int y = 1;
    POINT pt{ x,y };

    Graphics::PointF point;
    point = pt;
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFAssignOperatorTest2
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest2 )
{
    int x = 1;
    int y = 1;
    SIZE sz{ x,y };

    Graphics::PointF point;
    point = sz;
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFAssignOperatorTest3
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest3 )
{
    float x = 1.4f;
    float y = 1.6f;
    D2D_POINT_2F pt{ x,y };

    Graphics::PointF point;
    point = pt;
    BOOST_CHECK( point.X( ) == x );
    BOOST_CHECK( point.Y( ) == y );
}

// --run_test=HWCommonTests/PointFAssignOperatorTest4
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest4 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    D2D_POINT_2U pt{ x,y };

    Graphics::PointF point;
    point = pt;
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFAssignOperatorTest5
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest5 )
{
    float x = 1.4f;
    float y = 1.6f;
    D2D_SIZE_F sz{ x,y };

    Graphics::PointF point;
    point = sz;
    BOOST_CHECK( point.X( ) == x );
    BOOST_CHECK( point.Y( ) == y );
}

// --run_test=HWCommonTests/PointFAssignOperatorTest6
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest6 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    D2D_SIZE_U sz{ x,y };

    Graphics::PointF point;
    point = sz;
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFAssignOperatorTest7
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest7 )
{
    float x = 1.4f;
    float y = 1.6f;
    Graphics::PointF pt{ x,y };

    Graphics::PointF point;
    point = pt;
    BOOST_CHECK( point.X( ) == x );
    BOOST_CHECK( point.Y( ) == y );
}

// --run_test=HWCommonTests/PointFAssignOperatorTest8
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest8 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::PointU pt{ x,y };

    Graphics::PointF point;
    point = pt;
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFAssignOperatorTest9
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest9 )
{
    float x = 1.4f;
    float y = 1.6f;
    Graphics::SizeF sz{ x,y };

    Graphics::PointF point;
    point = sz;
    BOOST_CHECK( point.X( ) == x );
    BOOST_CHECK( point.Y( ) == y );
}

// --run_test=HWCommonTests/PointFAssignOperatorTest10
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest10 )
{
    UInt32 x = 1;
    UInt32 y = 1;
    Graphics::SizeU sz{ x,y };

    Graphics::PointF point;
    point = sz;
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}


// --run_test=HWCommonTests/PointFAssignOperatorTest11
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest11 )
{
    int x = 1;
    int y = 1;
    Harlinn::Windows::Rectangle rect( x, y, 5, 5 );

    Graphics::PointF point;
    point = rect;
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFAssignOperatorTest12
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest12 )
{
    float x = 1.4f;
    float y = 1.6f;
    Graphics::RectangleF rect( x, y, 5, 5 );

    Graphics::PointF point;
    point = rect;
    BOOST_CHECK( point.X( ) == x );
    BOOST_CHECK( point.Y( ) == y );
}

// --run_test=HWCommonTests/PointFAssignOperatorTest13
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest13 )
{
    int x = 1;
    int y = 1;
    Graphics::RectangleU rect( x, y, 5, 5 );

    Graphics::PointF point;
    point = rect;
    BOOST_CHECK( point.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point.Y( ) == static_cast<Graphics::PointF::value_type>( y ) );
}

// --run_test=HWCommonTests/PointFAssignOperatorTest14
BOOST_AUTO_TEST_CASE( PointFAssignOperatorTest14 )
{
    int x = 1;
    Point point1( x );

    Graphics::PointF point2;
    point2 = point1;
    BOOST_CHECK( point2.X( ) == static_cast<Graphics::PointF::value_type>( x ) );
    BOOST_CHECK( point2.Y( ) == static_cast<Graphics::PointF::value_type>( x ) );
}

// --run_test=HWCommonTests/PointFOperatorBoolTest1
BOOST_AUTO_TEST_CASE( PointFOperatorBoolTest1 )
{
    PointF point1;
    bool check = !!point1;
    BOOST_CHECK( check == false );
    PointF point2(1.f);
    check = !!point2;
    BOOST_CHECK( check == true );

    PointF point3( 1.f, 0.f );
    check = !!point3;
    BOOST_CHECK( check == true );

    PointF point4( 0.f, 1.f );
    check = !!point4;
    BOOST_CHECK( check == true );

    PointF point5( -1.f, 0.f );
    check = !!point5;
    BOOST_CHECK( check == true );

    PointF point6( 0.f, -1.f );
    check = !!point6;
    BOOST_CHECK( check == true );
}


// --run_test=HWCommonTests/PointFPlusOperatorTest1
BOOST_AUTO_TEST_CASE( PointFPlusOperatorTest1 )
{
    PointF p1( 1.4f, 1.6f );
    PointF p2 = p1 + 1.f;

    BOOST_CHECK( p2.X( ) == 2.4f );
    BOOST_CHECK( p2.Y( ) == 2.6f );
}

// --run_test=HWCommonTests/PointFPlusOperatorTest2
BOOST_AUTO_TEST_CASE( PointFPlusOperatorTest2 )
{
    PointF p1( 1.4f, 1.6f );
    PointF p2( 1.4f, 1.6f );
    auto p3 = p1 + p2;

    BOOST_CHECK( p3.X( ) == 2.8f );
    BOOST_CHECK( p3.Y( ) == 3.2f );
}

// --run_test=HWCommonTests/PointFPlusOperatorTest3
BOOST_AUTO_TEST_CASE( PointFPlusOperatorTest3 )
{
    PointF p1( 1.4f, 1.6f );
    SizeF s1( 1.4f, 1.6f );
    auto p2 = p1 + s1;

    BOOST_CHECK( p2.X( ) == 2.8f );
    BOOST_CHECK( p2.Y( ) == 3.2f );
}

// --run_test=HWCommonTests/PointFMinusOperatorTest1
BOOST_AUTO_TEST_CASE( PointFMinusOperatorTest1 )
{
    PointF p1( 1.4f, 1.6f );
    PointF p2 = p1 - 1.f;
    float expectedX = 1.4f - 1.f;
    float expectedY = 1.6f - 1.f;

    BOOST_CHECK( p2.X( ) == expectedX );
    BOOST_CHECK( p2.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMinusOperatorTest2
BOOST_AUTO_TEST_CASE( PointFMinusOperatorTest2 )
{
    PointF p1( 1.4f, 1.6f );
    PointF p2( 1.2f, 1.0f );

    float expectedX = 1.4f - 1.2f;
    float expectedY = 1.6f - 1.0f;

    auto p3 = p1 - p2;

    BOOST_CHECK( p3.X( ) == expectedX );
    BOOST_CHECK( p3.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMinusOperatorTest3
BOOST_AUTO_TEST_CASE( PointFMinusOperatorTest3 )
{
    PointF p1( 1.4f, 1.6f );
    SizeF s1( 1.2f, 1.0f );

    float expectedX = 1.4f - 1.2f;
    float expectedY = 1.6f - 1.0f;

    auto p2 = p1 - s1;

    BOOST_CHECK( p2.X( ) == expectedX );
    BOOST_CHECK( p2.Y( ) == expectedY );
}


// --run_test=HWCommonTests/PointFMultiplyOperatorTest1
BOOST_AUTO_TEST_CASE( PointFMultiplyOperatorTest1 )
{
    PointF p1( 1.4f, 1.6f );
    PointF p2 = p1 * 2.3f;
    float expectedX = 1.4f * 2.3f;
    float expectedY = 1.6f * 2.3f;

    BOOST_CHECK( p2.X( ) == expectedX );
    BOOST_CHECK( p2.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMultiplyOperatorTest2
BOOST_AUTO_TEST_CASE( PointFMultiplyOperatorTest2 )
{
    PointF p1( 1.4f, 1.6f );
    PointF p2( 1.2f, 1.4f );

    float expectedX = 1.4f * 1.2f;
    float expectedY = 1.6f * 1.4f;

    auto p3 = p1 * p2;

    BOOST_CHECK( p3.X( ) == expectedX );
    BOOST_CHECK( p3.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMultiplyOperatorTest3
BOOST_AUTO_TEST_CASE( PointFMultiplyOperatorTest3 )
{
    PointF p1( 1.4f, 1.6f );
    SizeF s1( 1.2f, 1.4f );

    float expectedX = 1.4f * 1.2f;
    float expectedY = 1.6f * 1.4f;

    auto p2 = p1 * s1;

    BOOST_CHECK( p2.X( ) == expectedX );
    BOOST_CHECK( p2.Y( ) == expectedY );
}


// --run_test=HWCommonTests/PointFDivideOperatorTest1
BOOST_AUTO_TEST_CASE( PointFDivideOperatorTest1 )
{
    PointF p1( 1.4f, 1.6f );
    PointF p2 = p1 / 2.3f;
    float expectedX = 1.4f / 2.3f;
    float expectedY = 1.6f / 2.3f;

    BOOST_CHECK( p2.X( ) == expectedX );
    BOOST_CHECK( p2.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFDivideOperatorTest2
BOOST_AUTO_TEST_CASE( PointFDivideOperatorTest2 )
{
    PointF p1( 1.4f, 1.6f );
    PointF p2( 1.2f, 1.4f );

    float expectedX = 1.4f / 1.2f;
    float expectedY = 1.6f / 1.4f;

    auto p3 = p1 / p2;

    BOOST_CHECK( p3.X( ) == expectedX );
    BOOST_CHECK( p3.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFDivideOperatorTest3
BOOST_AUTO_TEST_CASE( PointFDivideOperatorTest3 )
{
    PointF p1( 1.4f, 1.6f );
    SizeF s1( 1.2f, 1.4f );

    float expectedX = 1.4f / 1.2f;
    float expectedY = 1.6f / 1.4f;

    auto p2 = p1 / s1;

    BOOST_CHECK( p2.X( ) == expectedX );
    BOOST_CHECK( p2.Y( ) == expectedY );
}


// --run_test=HWCommonTests/PointFPlusAssignOperatorTest1
BOOST_AUTO_TEST_CASE( PointFPlusAssignOperatorTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = v1 + v3;
    float expectedY = v2 + v3;

    p1 += v3;

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFPlusAssignOperatorTest2
BOOST_AUTO_TEST_CASE( PointFPlusAssignOperatorTest2 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX = v1 + v3;
    float expectedY = v2 + v4;

    p1 += p2;

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFPlusAssignOperatorTest3
BOOST_AUTO_TEST_CASE( PointFPlusAssignOperatorTest3 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    SizeF s1( v3, v4 );

    float expectedX = v1 + v3;
    float expectedY = v2 + v4;

    p1 += s1;

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}


// --run_test=HWCommonTests/PointFMinusAssignOperatorTest1
BOOST_AUTO_TEST_CASE( PointFMinusAssignOperatorTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = v1 - v3;
    float expectedY = v2 - v3;

    p1 -= v3;

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMinusAssignOperatorTest2
BOOST_AUTO_TEST_CASE( PointFMinusAssignOperatorTest2 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX = v1 - v3;
    float expectedY = v2 - v4;

    p1 -= p2;

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMinusAssignOperatorTest3
BOOST_AUTO_TEST_CASE( PointFMinusAssignOperatorTest3 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    SizeF s1( v3, v4 );

    float expectedX = v1 - v3;
    float expectedY = v2 - v4;

    p1 -= s1;

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMultiplyAssignOperatorTest1
BOOST_AUTO_TEST_CASE( PointFMultiplyAssignOperatorTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = v1 * v3;
    float expectedY = v2 * v3;

    p1 *= v3;

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMultiplyAssignOperatorTest2
BOOST_AUTO_TEST_CASE( PointFMultiplyAssignOperatorTest2 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX = v1 * v3;
    float expectedY = v2 * v4;

    p1 *= p2;

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMultiplyAssignOperatorTest3
BOOST_AUTO_TEST_CASE( PointFMultiplyAssignOperatorTest3 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    SizeF s1( v3, v4 );

    float expectedX = v1 * v3;
    float expectedY = v2 * v4;

    p1 *= s1;

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFDivideAssignOperatorTest1
BOOST_AUTO_TEST_CASE( PointFDivideAssignOperatorTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = v1 / v3;
    float expectedY = v2 / v3;

    p1 /= v3;

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFDivideAssignOperatorTest2
BOOST_AUTO_TEST_CASE( PointFDivideAssignOperatorTest2 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX = v1 / v3;
    float expectedY = v2 / v4;

    p1 /= p2;

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFDivideAssignOperatorTest3
BOOST_AUTO_TEST_CASE( PointFDivideAssignOperatorTest3 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    SizeF s1( v3, v4 );

    float expectedX = v1 / v3;
    float expectedY = v2 / v4;

    p1 /= s1;

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}


// --run_test=HWCommonTests/PointFSetXTest1
BOOST_AUTO_TEST_CASE( PointFSetXTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = v3;
    float expectedY = v2;

    p1.SetX( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFSetYTest1
BOOST_AUTO_TEST_CASE( PointFSetYTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = v1;
    float expectedY = v3;

    p1.SetY( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFAddToXTest1
BOOST_AUTO_TEST_CASE( PointFAddToXTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = v1 + v3;
    float expectedY = v2;

    p1.AddToX( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFAddToYTest1
BOOST_AUTO_TEST_CASE( PointFAddToYTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = v1;
    float expectedY = v2 + v3;

    p1.AddToY( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFSubtractFromXTest1
BOOST_AUTO_TEST_CASE( PointFSubtractFromXTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = v1 - v3;
    float expectedY = v2;

    p1.SubtractFromX( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFSubtractFromYTest1
BOOST_AUTO_TEST_CASE( PointFSubtractFromYTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = v1;
    float expectedY = v2 - v3;

    p1.SubtractFromY( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMinXTest1
BOOST_AUTO_TEST_CASE( PointFMinXTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = std::min(v1, v3);
    float expectedY = v2;

    p1.MinX( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMinXTest2
BOOST_AUTO_TEST_CASE( PointFMinXTest2 )
{
    float v1 = 2.4f;
    float v2 = 1.6f;
    float v3 = 1.4f;

    PointF p1( v1, v2 );

    float expectedX = std::min( v1, v3 );
    float expectedY = v2;

    p1.MinX( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMinYTest1
BOOST_AUTO_TEST_CASE( PointFMinYTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = v1;
    float expectedY = std::min( v2, v3 );

    p1.MinY( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMinYTest2
BOOST_AUTO_TEST_CASE( PointFMinYTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;

    PointF p1( v1, v2 );

    float expectedX = v1;
    float expectedY = std::min( v2, v3 );

    p1.MinY( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMaxXTest1
BOOST_AUTO_TEST_CASE( PointFMaxXTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = std::max( v1, v3 );
    float expectedY = v2;

    p1.MaxX( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMaxXTest2
BOOST_AUTO_TEST_CASE( PointFMaxXTest2 )
{
    float v1 = 2.4f;
    float v2 = 1.6f;
    float v3 = 1.4f;

    PointF p1( v1, v2 );

    float expectedX = std::max( v1, v3 );
    float expectedY = v2;

    p1.MaxX( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMaxYTest1
BOOST_AUTO_TEST_CASE( PointFMaxYTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    PointF p1( v1, v2 );

    float expectedX = v1;
    float expectedY = std::max( v2, v3 );

    p1.MaxY( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMaxYTest2
BOOST_AUTO_TEST_CASE( PointFMaxYTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;

    PointF p1( v1, v2 );

    float expectedX = v1;
    float expectedY = std::max( v2, v3 );

    p1.MaxY( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFSwapXTest1
BOOST_AUTO_TEST_CASE( PointFSwapXTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;

    PointF p1( v1, v2 );

    float expectedX = v3;
    float expectedY = v2;

    p1.SwapX( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
    BOOST_CHECK( v1 == v3 );
}

// --run_test=HWCommonTests/PointFSwapXTest2
BOOST_AUTO_TEST_CASE( PointFSwapXTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX1 = v3;
    float expectedY1 = v2;
    float expectedX2 = v1;
    float expectedY2 = v4;

    p1.SwapX( p2 );

    BOOST_CHECK( p1.X( ) == expectedX1 );
    BOOST_CHECK( p1.Y( ) == expectedY1 );
    BOOST_CHECK( p2.X( ) == expectedX2 );
    BOOST_CHECK( p2.Y( ) == expectedY2 );
}

// --run_test=HWCommonTests/PointFSwapYTest1
BOOST_AUTO_TEST_CASE( PointFSwapYTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;

    PointF p1( v1, v2 );

    float expectedX = v1;
    float expectedY = v3;

    p1.SwapY( v3 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
    BOOST_CHECK( v2 == v3 );
}

// --run_test=HWCommonTests/PointFSwapYTest2
BOOST_AUTO_TEST_CASE( PointFSwapYTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX1 = v1;
    float expectedY1 = v4;
    float expectedX2 = v3;
    float expectedY2 = v2;

    p1.SwapY( p2 );

    BOOST_CHECK( p1.X( ) == expectedX1 );
    BOOST_CHECK( p1.Y( ) == expectedY1 );
    BOOST_CHECK( p2.X( ) == expectedX2 );
    BOOST_CHECK( p2.Y( ) == expectedY2 );
}

// --run_test=HWCommonTests/PointFSwapTest1
BOOST_AUTO_TEST_CASE( PointFSwapTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX1 = v3;
    float expectedY1 = v4;
    float expectedX2 = v1;
    float expectedY2 = v2;

    std::swap( p1, p2 );

    BOOST_CHECK( p1.X( ) == expectedX1 );
    BOOST_CHECK( p1.Y( ) == expectedY1 );
    BOOST_CHECK( p2.X( ) == expectedX2 );
    BOOST_CHECK( p2.Y( ) == expectedY2 );
}

// --run_test=HWCommonTests/PointFSwapTest2
BOOST_AUTO_TEST_CASE( PointFSwapTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX1 = v3;
    float expectedY1 = v4;
    float expectedX2 = v1;
    float expectedY2 = v2;

    p1.swap( p2 );

    BOOST_CHECK( p1.X( ) == expectedX1 );
    BOOST_CHECK( p1.Y( ) == expectedY1 );
    BOOST_CHECK( p2.X( ) == expectedX2 );
    BOOST_CHECK( p2.Y( ) == expectedY2 );
}

// --run_test=HWCommonTests/PointFAssignTest1
BOOST_AUTO_TEST_CASE( PointFAssignTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );

    float expectedX = v3;
    float expectedY = v4;

    p1.Assign( v3, v4 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFAddTest1
BOOST_AUTO_TEST_CASE( PointFAddTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );

    float expectedX = v1 + v3;
    float expectedY = v2 + v4;

    p1.Add( v3, v4 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFAssignMinTest1
BOOST_AUTO_TEST_CASE( PointFAssignMinTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );

    float expectedX = std::min( v1 , v3 );
    float expectedY = std::min( v2 , v4 );

    p1.AssignMin( v3, v4 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFAssignMinTest2
BOOST_AUTO_TEST_CASE( PointFAssignMinTest2 )
{
    float v1 = 1.8f;
    float v2 = 3.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );

    float expectedX = std::min( v1, v3 );
    float expectedY = std::min( v2, v4 );

    p1.AssignMin( v3, v4 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFAssignMaxTest1
BOOST_AUTO_TEST_CASE( PointFAssignMaxTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );

    float expectedX = std::max( v1, v3 );
    float expectedY = std::max( v2, v4 );

    p1.AssignMax( v3, v4 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFAssignMaxTest2
BOOST_AUTO_TEST_CASE( PointFAssignMaxTest2 )
{
    float v1 = 1.8f;
    float v2 = 3.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );

    float expectedX = std::max( v1, v3 );
    float expectedY = std::max( v2, v4 );

    p1.AssignMax( v3, v4 );

    BOOST_CHECK( p1.X( ) == expectedX );
    BOOST_CHECK( p1.Y( ) == expectedY );
}


// --run_test=HWCommonTests/PointFMinTest1
BOOST_AUTO_TEST_CASE( PointFMinTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX = std::min( v1, v3 );
    float expectedY = std::min( v2, v4 );

    auto p3 = p1.Min( p2 );

    BOOST_CHECK( p3.X( ) == expectedX );
    BOOST_CHECK( p3.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMinTest2
BOOST_AUTO_TEST_CASE( PointFMinTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX = std::min( v1, v3 );
    float expectedY = std::min( v2, v4 );

    auto p3 = std::min( p1, p2 );

    BOOST_CHECK( p3.X( ) == expectedX );
    BOOST_CHECK( p3.Y( ) == expectedY );
}


// --run_test=HWCommonTests/PointFMinTest3
BOOST_AUTO_TEST_CASE( PointFMinTest3 )
{
    float v1 = 1.6f;
    float v2 = 2.6f;
    float v3 = 1.4f;
    float v4 = 2.4f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX = std::min( v1, v3 );
    float expectedY = std::min( v2, v4 );

    auto p3 = p1.Min( p2 );

    BOOST_CHECK( p3.X( ) == expectedX );
    BOOST_CHECK( p3.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMinTest4
BOOST_AUTO_TEST_CASE( PointFMinTest4 )
{
    float v1 = 1.6f;
    float v2 = 2.6f;
    float v3 = 1.4f;
    float v4 = 2.4f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX = std::min( v1, v3 );
    float expectedY = std::min( v2, v4 );

    auto p3 = std::min( p1, p2 );

    BOOST_CHECK( p3.X( ) == expectedX );
    BOOST_CHECK( p3.Y( ) == expectedY );
}


// --run_test=HWCommonTests/PointFMaxTest1
BOOST_AUTO_TEST_CASE( PointFMaxTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX = std::max( v1, v3 );
    float expectedY = std::max( v2, v4 );

    auto p3 = p1.Max( p2 );

    BOOST_CHECK( p3.X( ) == expectedX );
    BOOST_CHECK( p3.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMaxTest2
BOOST_AUTO_TEST_CASE( PointFMaxTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX = std::max( v1, v3 );
    float expectedY = std::max( v2, v4 );

    auto p3 = std::max( p1, p2 );

    BOOST_CHECK( p3.X( ) == expectedX );
    BOOST_CHECK( p3.Y( ) == expectedY );
}


// --run_test=HWCommonTests/PointFMaxTest3
BOOST_AUTO_TEST_CASE( PointFMaxTest3 )
{
    float v1 = 1.6f;
    float v2 = 2.6f;
    float v3 = 1.4f;
    float v4 = 2.4f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX = std::max( v1, v3 );
    float expectedY = std::max( v2, v4 );

    auto p3 = p1.Max( p2 );

    BOOST_CHECK( p3.X( ) == expectedX );
    BOOST_CHECK( p3.Y( ) == expectedY );
}

// --run_test=HWCommonTests/PointFMaxTest4
BOOST_AUTO_TEST_CASE( PointFMaxTest4 )
{
    float v1 = 1.6f;
    float v2 = 2.6f;
    float v3 = 1.4f;
    float v4 = 2.4f;

    PointF p1( v1, v2 );
    PointF p2( v3, v4 );

    float expectedX = std::max( v1, v3 );
    float expectedY = std::max( v2, v4 );

    auto p3 = std::max( p1, p2 );

    BOOST_CHECK( p3.X( ) == expectedX );
    BOOST_CHECK( p3.Y( ) == expectedY );
}


// --run_test=HWCommonTests/SizeFConstructorTest1
BOOST_AUTO_TEST_CASE( SizeFConstructorTest1 )
{
    Graphics::SizeF size;
    BOOST_CHECK( size.Width( ) == 0 );
    BOOST_CHECK( size.Height( ) == 0 );
}

// --run_test=HWCommonTests/SizeFConstructorTest2
BOOST_AUTO_TEST_CASE( SizeFConstructorTest2 )
{
    SByte width = 1;
    SByte height = 1;
    Graphics::SizeF size( width, height );
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFConstructorTest3
BOOST_AUTO_TEST_CASE( SizeFConstructorTest3 )
{
    SByte width = 1;
    bool height = true;
    Graphics::SizeF size( width, height );
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFConstructorTest4
BOOST_AUTO_TEST_CASE( SizeFConstructorTest4 )
{
    SByte width = 1;
    double height = 1.5;
    Graphics::SizeF size( width, height );
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == height );
}

// --run_test=HWCommonTests/SizeFConstructorTest5
BOOST_AUTO_TEST_CASE( SizeFConstructorTest5 )
{
    int width = 1;
    int height = 1;
    SIZE sz{ width,height };

    Graphics::SizeF size( sz );
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFConstructorTest6
BOOST_AUTO_TEST_CASE( SizeFConstructorTest6 )
{
    int width = 1;
    int height = 1;
    POINT pt{ width,height };

    Graphics::SizeF size( pt );
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFConstructorTest7
BOOST_AUTO_TEST_CASE( SizeFConstructorTest7 )
{
    float width = 1.4f;
    float height = 1.6f;
    D2D_POINT_2F pt{ width,height };

    Graphics::SizeF size( pt );
    BOOST_CHECK( size.Width( ) == width );
    BOOST_CHECK( size.Height( ) == height );
}

// --run_test=HWCommonTests/SizeFConstructorTest8
BOOST_AUTO_TEST_CASE( SizeFConstructorTest8 )
{
    UInt32 width = 1;
    UInt32 height = 1;
    D2D_POINT_2U pt{ width,height };

    Graphics::SizeF size( pt );
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFConstructorTest9
BOOST_AUTO_TEST_CASE( SizeFConstructorTest9 )
{
    float width = 1.4f;
    float height = 1.6f;
    Graphics::SizeF sz{ width,height };

    Graphics::SizeF size( sz );
    BOOST_CHECK( size.Width( ) == width );
    BOOST_CHECK( size.Height( ) == height );
}

// --run_test=HWCommonTests/SizeFConstructorTest10
BOOST_AUTO_TEST_CASE( SizeFConstructorTest10 )
{
    UInt32 width = 1;
    UInt32 height = 1;
    Graphics::PointU pt{ width,height };

    Graphics::SizeF size( pt );
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFConstructorTest11
BOOST_AUTO_TEST_CASE( SizeFConstructorTest11 )
{
    float width = 1.4f;
    float height = 1.6f;
    Graphics::PointF pt{ width,height };

    Graphics::SizeF size( pt );
    BOOST_CHECK( size.Width( ) == width );
    BOOST_CHECK( size.Height( ) == height );
}

// --run_test=HWCommonTests/SizeFConstructorTest12
BOOST_AUTO_TEST_CASE( SizeFConstructorTest12 )
{
    UInt32 width = 1;
    UInt32 height = 1;
    Graphics::SizeU sz{ width,height };

    Graphics::SizeF size( sz );
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}



// --run_test=HWCommonTests/SizeFConstructorTest13
BOOST_AUTO_TEST_CASE( SizeFConstructorTest13 )
{
    float width = 1.4f;
    float height = 1.6f;
    D2D_SIZE_F sz{ width,height };

    Graphics::SizeF size( sz );
    BOOST_CHECK( size.Width( ) == width );
    BOOST_CHECK( size.Height( ) == height );
}

// --run_test=HWCommonTests/SizeFConstructorTest14
BOOST_AUTO_TEST_CASE( SizeFConstructorTest14 )
{
    UInt32 width = 1;
    UInt32 height = 1;
    D2D_SIZE_U sz{ width,height };

    Graphics::SizeF size( sz );
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFConstructorTest15
BOOST_AUTO_TEST_CASE( SizeFConstructorTest15 )
{

    int x = 1;
    int y = 1;
    Harlinn::Windows::Rectangle rect( x, y, 5, 5 );

    auto width = rect.Width( );
    auto height = rect.Height( );

    Graphics::SizeF size( rect );
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFConstructorTest16
BOOST_AUTO_TEST_CASE( SizeFConstructorTest16 )
{
    float x = 1.4f;
    float y = 1.6f;
    Graphics::RectangleF rect( x, y, 5, 5 );

    auto width = rect.Width( );
    auto height = rect.Height( );

    Graphics::SizeF size( rect );
    BOOST_CHECK( size.Width( ) == width );
    BOOST_CHECK( size.Height( ) == height );
}

// --run_test=HWCommonTests/SizeFConstructorTest17
BOOST_AUTO_TEST_CASE( SizeFConstructorTest17 )
{
    int x = 1;
    int y = 1;
    Graphics::RectangleU rect( x, y, 5, 5 );;

    auto width = rect.Width( );
    auto height = rect.Height( );

    Graphics::SizeF size( rect );
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}



// --run_test=HWCommonTests/SizeFConstructorTest18
BOOST_AUTO_TEST_CASE( SizeFConstructorTest18 )
{
    int width = 1;

    Graphics::SizeF size( width );
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( width ) );
}

// --run_test=HWCommonTests/SizeFConstructorTest19
BOOST_AUTO_TEST_CASE( SizeFConstructorTest19 )
{
    float width = 1.5;

    Graphics::SizeF size( width );
    BOOST_CHECK( size.Width( ) == width );
    BOOST_CHECK( size.Height( ) == width );
}



// --run_test=HWCommonTests/SizeFAssignOperatorTest1
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest1 )
{
    int width = 1;
    int height = 1;
    POINT pt{ width,height };

    Graphics::SizeF size;
    size = pt;
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFAssignOperatorTest2
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest2 )
{
    int width = 1;
    int height = 1;
    SIZE sz{ width,height };

    Graphics::SizeF size;
    size = sz;
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFAssignOperatorTest3
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest3 )
{
    float width = 1.4f;
    float height = 1.6f;
    D2D_POINT_2F pt{ width,height };

    Graphics::SizeF size;
    size = pt;
    BOOST_CHECK( size.Width( ) == width );
    BOOST_CHECK( size.Height( ) == height );
}

// --run_test=HWCommonTests/SizeFAssignOperatorTest4
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest4 )
{
    UInt32 width = 1;
    UInt32 height = 1;
    D2D_POINT_2U pt{ width,height };

    Graphics::SizeF size;
    size = pt;
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFAssignOperatorTest5
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest5 )
{
    float width = 1.4f;
    float height = 1.6f;
    D2D_SIZE_F sz{ width,height };

    Graphics::SizeF size;
    size = sz;
    BOOST_CHECK( size.Width( ) == width );
    BOOST_CHECK( size.Height( ) == height );
}

// --run_test=HWCommonTests/SizeFAssignOperatorTest6
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest6 )
{
    UInt32 width = 1;
    UInt32 height = 1;
    D2D_SIZE_U sz{ width,height };

    Graphics::SizeF size;
    size = sz;
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFAssignOperatorTest7
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest7 )
{
    float width = 1.4f;
    float height = 1.6f;
    Graphics::SizeF sz{ width,height };

    Graphics::SizeF size;
    size = sz;
    BOOST_CHECK( size.Width( ) == width );
    BOOST_CHECK( size.Height( ) == height );
}

// --run_test=HWCommonTests/SizeFAssignOperatorTest8
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest8 )
{
    UInt32 width = 1;
    UInt32 height = 1;
    Graphics::PointU pt{ width,height };

    Graphics::SizeF size;
    size = pt;
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFAssignOperatorTest9
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest9 )
{
    float width = 1.4f;
    float height = 1.6f;
    Graphics::PointF pt{ width,height };

    Graphics::SizeF size;
    size = pt;
    BOOST_CHECK( size.Width( ) == width );
    BOOST_CHECK( size.Height( ) == height );
}

// --run_test=HWCommonTests/SizeFAssignOperatorTest10
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest10 )
{
    UInt32 width = 1;
    UInt32 height = 1;
    Graphics::SizeU sz{ width,height };

    Graphics::SizeF size;
    size = sz;
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}


// --run_test=HWCommonTests/SizeFAssignOperatorTest11
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest11 )
{
    int x = 1;
    int y = 1;
    Harlinn::Windows::Rectangle rect( x, y, 5, 5 );

    auto width = rect.Width( );
    auto height = rect.Height( );

    Graphics::SizeF size;
    size = rect;
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFAssignOperatorTest12
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest12 )
{
    float x = 1.4f;
    float y = 1.6f;
    Graphics::RectangleF rect( x, y, 5, 5 );

    auto width = rect.Width( );
    auto height = rect.Height( );

    Graphics::SizeF size;
    size = rect;
    BOOST_CHECK( size.Width( ) == width );
    BOOST_CHECK( size.Height( ) == height );
}

// --run_test=HWCommonTests/SizeFAssignOperatorTest13
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest13 )
{
    int x = 1;
    int y = 1;
    Graphics::RectangleU rect( x, y, 5, 5 );

    auto width = rect.Width( );
    auto height = rect.Height( );

    Graphics::SizeF size;
    size = rect;
    BOOST_CHECK( size.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size.Height( ) == static_cast<Graphics::SizeF::value_type>( height ) );
}

// --run_test=HWCommonTests/SizeFAssignOperatorTest14
BOOST_AUTO_TEST_CASE( SizeFAssignOperatorTest14 )
{
    int width = 1;
    Point point1( width );

    Graphics::SizeF size2;
    size2 = point1;
    BOOST_CHECK( size2.Width( ) == static_cast<Graphics::SizeF::value_type>( width ) );
    BOOST_CHECK( size2.Height( ) == static_cast<Graphics::SizeF::value_type>( width ) );
}

// --run_test=HWCommonTests/SizeFOperatorBoolTest1
BOOST_AUTO_TEST_CASE( SizeFOperatorBoolTest1 )
{
    SizeF point1;
    bool check = !!point1;
    BOOST_CHECK( check == false );
    SizeF point2( 1.f );
    check = !!point2;
    BOOST_CHECK( check == true );

    SizeF point3( 1.f, 0.f );
    check = !!point3;
    BOOST_CHECK( check == true );

    SizeF point4( 0.f, 1.f );
    check = !!point4;
    BOOST_CHECK( check == true );

    SizeF point5( -1.f, 0.f );
    check = !!point5;
    BOOST_CHECK( check == true );

    SizeF point6( 0.f, -1.f );
    check = !!point6;
    BOOST_CHECK( check == true );
}


// --run_test=HWCommonTests/SizeFPlusOperatorTest1
BOOST_AUTO_TEST_CASE( SizeFPlusOperatorTest1 )
{
    SizeF s1( 1.4f, 1.6f );
    SizeF s2 = s1 + 1.f;

    BOOST_CHECK( s2.Width( ) == 2.4f );
    BOOST_CHECK( s2.Height( ) == 2.6f );
}

// --run_test=HWCommonTests/SizeFPlusOperatorTest2
BOOST_AUTO_TEST_CASE( SizeFPlusOperatorTest2 )
{
    SizeF s1( 1.4f, 1.6f );
    SizeF s2( 1.4f, 1.6f );
    auto s3 = s1 + s2;

    BOOST_CHECK( s3.Width( ) == 2.8f );
    BOOST_CHECK( s3.Height( ) == 3.2f );
}

// --run_test=HWCommonTests/SizeFPlusOperatorTest3
BOOST_AUTO_TEST_CASE( SizeFPlusOperatorTest3 )
{
    SizeF s1( 1.4f, 1.6f );
    PointF p1( 1.4f, 1.6f );
    auto s2 = s1 + p1;

    BOOST_CHECK( s2.Width( ) == 2.8f );
    BOOST_CHECK( s2.Height( ) == 3.2f );
}

// --run_test=HWCommonTests/SizeFMinusOperatorTest1
BOOST_AUTO_TEST_CASE( SizeFMinusOperatorTest1 )
{
    SizeF s1( 1.4f, 1.6f );
    SizeF s2 = s1 - 1.f;
    float expectedWidth = 1.4f - 1.f;
    float expectedHeight = 1.6f - 1.f;

    BOOST_CHECK( s2.Width( ) == expectedWidth );
    BOOST_CHECK( s2.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMinusOperatorTest2
BOOST_AUTO_TEST_CASE( SizeFMinusOperatorTest2 )
{
    SizeF s1( 1.4f, 1.6f );
    SizeF s2( 1.2f, 1.0f );

    float expectedWidth = 1.4f - 1.2f;
    float expectedHeight = 1.6f - 1.0f;

    auto s3 = s1 - s2;

    BOOST_CHECK( s3.Width( ) == expectedWidth );
    BOOST_CHECK( s3.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMinusOperatorTest3
BOOST_AUTO_TEST_CASE( SizeFMinusOperatorTest3 )
{
    SizeF s1( 1.4f, 1.6f );
    PointF p1( 1.2f, 1.0f );

    float expectedWidth = 1.4f - 1.2f;
    float expectedHeight = 1.6f - 1.0f;

    auto s2 = s1 - p1;

    BOOST_CHECK( s2.Width( ) == expectedWidth );
    BOOST_CHECK( s2.Height( ) == expectedHeight );
}


// --run_test=HWCommonTests/SizeFMultiplyOperatorTest1
BOOST_AUTO_TEST_CASE( SizeFMultiplyOperatorTest1 )
{
    SizeF s1( 1.4f, 1.6f );
    SizeF s2 = s1 * 2.3f;
    float expectedWidth = 1.4f * 2.3f;
    float expectedHeight = 1.6f * 2.3f;

    BOOST_CHECK( s2.Width( ) == expectedWidth );
    BOOST_CHECK( s2.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMultiplyOperatorTest2
BOOST_AUTO_TEST_CASE( SizeFMultiplyOperatorTest2 )
{
    SizeF s1( 1.4f, 1.6f );
    SizeF s2( 1.2f, 1.4f );

    float expectedWidth = 1.4f * 1.2f;
    float expectedHeight = 1.6f * 1.4f;

    auto s3 = s1 * s2;

    BOOST_CHECK( s3.Width( ) == expectedWidth );
    BOOST_CHECK( s3.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMultiplyOperatorTest3
BOOST_AUTO_TEST_CASE( SizeFMultiplyOperatorTest3 )
{
    SizeF s1( 1.4f, 1.6f );
    PointF p1( 1.2f, 1.4f );

    float expectedWidth = 1.4f * 1.2f;
    float expectedHeight = 1.6f * 1.4f;

    auto s2 = s1 * p1;

    BOOST_CHECK( s2.Width( ) == expectedWidth );
    BOOST_CHECK( s2.Height( ) == expectedHeight );
}


// --run_test=HWCommonTests/SizeFDivideOperatorTest1
BOOST_AUTO_TEST_CASE( SizeFDivideOperatorTest1 )
{
    SizeF s1( 1.4f, 1.6f );
    SizeF s2 = s1 / 2.3f;
    float expectedWidth = 1.4f / 2.3f;
    float expectedHeight = 1.6f / 2.3f;

    BOOST_CHECK( s2.Width( ) == expectedWidth );
    BOOST_CHECK( s2.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFDivideOperatorTest2
BOOST_AUTO_TEST_CASE( SizeFDivideOperatorTest2 )
{
    SizeF s1( 1.4f, 1.6f );
    SizeF s2( 1.2f, 1.4f );

    float expectedWidth = 1.4f / 1.2f;
    float expectedHeight = 1.6f / 1.4f;

    auto s3 = s1 / s2;

    BOOST_CHECK( s3.Width( ) == expectedWidth );
    BOOST_CHECK( s3.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFDivideOperatorTest3
BOOST_AUTO_TEST_CASE( SizeFDivideOperatorTest3 )
{
    SizeF s1( 1.4f, 1.6f );
    PointF p1( 1.2f, 1.4f );

    float expectedWidth = 1.4f / 1.2f;
    float expectedHeight = 1.6f / 1.4f;

    auto s2 = s1 / p1;

    BOOST_CHECK( s2.Width( ) == expectedWidth );
    BOOST_CHECK( s2.Height( ) == expectedHeight );
}


// --run_test=HWCommonTests/SizeFPlusAssignOperatorTest1
BOOST_AUTO_TEST_CASE( SizeFPlusAssignOperatorTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1 + v3;
    float expectedHeight = v2 + v3;

    s1 += v3;

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFPlusAssignOperatorTest2
BOOST_AUTO_TEST_CASE( SizeFPlusAssignOperatorTest2 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedWidth = v1 + v3;
    float expectedHeight = v2 + v4;

    s1 += s2;

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFPlusAssignOperatorTest3
BOOST_AUTO_TEST_CASE( SizeFPlusAssignOperatorTest3 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    PointF p1( v3, v4 );

    float expectedWidth = v1 + v3;
    float expectedHeight = v2 + v4;

    s1 += p1;

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}


// --run_test=HWCommonTests/SizeFMinusAssignOperatorTest1
BOOST_AUTO_TEST_CASE( SizeFMinusAssignOperatorTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1 - v3;
    float expectedHeight = v2 - v3;

    s1 -= v3;

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMinusAssignOperatorTest2
BOOST_AUTO_TEST_CASE( SizeFMinusAssignOperatorTest2 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedWidth = v1 - v3;
    float expectedHeight = v2 - v4;

    s1 -= s2;

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMinusAssignOperatorTest3
BOOST_AUTO_TEST_CASE( SizeFMinusAssignOperatorTest3 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    PointF p1( v3, v4 );

    float expectedWidth = v1 - v3;
    float expectedHeight = v2 - v4;

    s1 -= p1;

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMultiplyAssignOperatorTest1
BOOST_AUTO_TEST_CASE( SizeFMultiplyAssignOperatorTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1 * v3;
    float expectedHeight = v2 * v3;

    s1 *= v3;

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMultiplyAssignOperatorTest2
BOOST_AUTO_TEST_CASE( SizeFMultiplyAssignOperatorTest2 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedWidth = v1 * v3;
    float expectedHeight = v2 * v4;

    s1 *= s2;

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMultiplyAssignOperatorTest3
BOOST_AUTO_TEST_CASE( SizeFMultiplyAssignOperatorTest3 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    PointF p1( v3, v4 );

    float expectedWidth = v1 * v3;
    float expectedHeight = v2 * v4;

    s1 *= p1;

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFDivideAssignOperatorTest1
BOOST_AUTO_TEST_CASE( SizeFDivideAssignOperatorTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1 / v3;
    float expectedHeight = v2 / v3;

    s1 /= v3;

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFDivideAssignOperatorTest2
BOOST_AUTO_TEST_CASE( SizeFDivideAssignOperatorTest2 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedWidth = v1 / v3;
    float expectedHeight = v2 / v4;

    s1 /= s2;

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFDivideAssignOperatorTest3
BOOST_AUTO_TEST_CASE( SizeFDivideAssignOperatorTest3 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    PointF p1( v3, v4 );

    float expectedWidth = v1 / v3;
    float expectedHeight = v2 / v4;

    s1 /= p1;

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}


// --run_test=HWCommonTests/SizeFSetXTest1
BOOST_AUTO_TEST_CASE( SizeFSetXTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = v3;
    float expectedHeight = v2;

    s1.SetWidth( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFSetYTest1
BOOST_AUTO_TEST_CASE( SizeFSetYTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1;
    float expectedHeight = v3;

    s1.SetHeight( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFAddToXTest1
BOOST_AUTO_TEST_CASE( SizeFAddToXTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1 + v3;
    float expectedHeight = v2;

    s1.AddToWidth( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFAddToYTest1
BOOST_AUTO_TEST_CASE( SizeFAddToYTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1;
    float expectedHeight = v2 + v3;

    s1.AddToHeight( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFSubtractFromXTest1
BOOST_AUTO_TEST_CASE( SizeFSubtractFromXTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1 - v3;
    float expectedHeight = v2;

    s1.SubtractFromWidth( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFSubtractFromYTest1
BOOST_AUTO_TEST_CASE( SizeFSubtractFromYTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1;
    float expectedHeight = v2 - v3;

    s1.SubtractFromHeight( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMinXTest1
BOOST_AUTO_TEST_CASE( SizeFMinXTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = std::min( v1, v3 );
    float expectedHeight = v2;

    s1.MinWidth( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMinXTest2
BOOST_AUTO_TEST_CASE( SizeFMinXTest2 )
{
    float v1 = 2.4f;
    float v2 = 1.6f;
    float v3 = 1.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = std::min( v1, v3 );
    float expectedHeight = v2;

    s1.MinWidth( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMinYTest1
BOOST_AUTO_TEST_CASE( SizeFMinYTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1;
    float expectedHeight = std::min( v2, v3 );

    s1.MinHeight( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMinYTest2
BOOST_AUTO_TEST_CASE( SizeFMinYTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1;
    float expectedHeight = std::min( v2, v3 );

    s1.MinHeight( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMaxXTest1
BOOST_AUTO_TEST_CASE( SizeFMaxXTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = std::max( v1, v3 );
    float expectedHeight = v2;

    s1.MaxWidth( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMaxXTest2
BOOST_AUTO_TEST_CASE( SizeFMaxXTest2 )
{
    float v1 = 2.4f;
    float v2 = 1.6f;
    float v3 = 1.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = std::max( v1, v3 );
    float expectedHeight = v2;

    s1.MaxWidth( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMaxYTest1
BOOST_AUTO_TEST_CASE( SizeFMaxYTest1 )
{
    float v1 = 1.4f;
    float v2 = 1.6f;
    float v3 = 2.4f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1;
    float expectedHeight = std::max( v2, v3 );

    s1.MaxHeight( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMaxYTest2
BOOST_AUTO_TEST_CASE( SizeFMaxYTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1;
    float expectedHeight = std::max( v2, v3 );

    s1.MaxHeight( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFSwapXTest1
BOOST_AUTO_TEST_CASE( SizeFSwapXTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;

    SizeF s1( v1, v2 );

    float expectedWidth = v3;
    float expectedHeight = v2;

    s1.SwapWidth( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
    BOOST_CHECK( v1 == v3 );
}

// --run_test=HWCommonTests/SizeFSwapXTest2
BOOST_AUTO_TEST_CASE( SizeFSwapXTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedX1 = v3;
    float expectedY1 = v2;
    float expectedX2 = v1;
    float expectedY2 = v4;

    s1.SwapWidth( s2 );

    BOOST_CHECK( s1.Width( ) == expectedX1 );
    BOOST_CHECK( s1.Height( ) == expectedY1 );
    BOOST_CHECK( s2.Width( ) == expectedX2 );
    BOOST_CHECK( s2.Height( ) == expectedY2 );
}

// --run_test=HWCommonTests/SizeFSwapYTest1
BOOST_AUTO_TEST_CASE( SizeFSwapYTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1;
    float expectedHeight = v3;

    s1.SwapHeight( v3 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
    BOOST_CHECK( v2 == v3 );
}

// --run_test=HWCommonTests/SizeFSwapYTest2
BOOST_AUTO_TEST_CASE( SizeFSwapYTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedX1 = v1;
    float expectedY1 = v4;
    float expectedX2 = v3;
    float expectedY2 = v2;

    s1.SwapHeight( s2 );

    BOOST_CHECK( s1.Width( ) == expectedX1 );
    BOOST_CHECK( s1.Height( ) == expectedY1 );
    BOOST_CHECK( s2.Width( ) == expectedX2 );
    BOOST_CHECK( s2.Height( ) == expectedY2 );
}

// --run_test=HWCommonTests/SizeFSwapTest1
BOOST_AUTO_TEST_CASE( SizeFSwapTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedX1 = v3;
    float expectedY1 = v4;
    float expectedX2 = v1;
    float expectedY2 = v2;

    std::swap( s1, s2 );

    BOOST_CHECK( s1.Width( ) == expectedX1 );
    BOOST_CHECK( s1.Height( ) == expectedY1 );
    BOOST_CHECK( s2.Width( ) == expectedX2 );
    BOOST_CHECK( s2.Height( ) == expectedY2 );
}

// --run_test=HWCommonTests/SizeFSwapTest2
BOOST_AUTO_TEST_CASE( SizeFSwapTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedX1 = v3;
    float expectedY1 = v4;
    float expectedX2 = v1;
    float expectedY2 = v2;

    s1.swap( s2 );

    BOOST_CHECK( s1.Width( ) == expectedX1 );
    BOOST_CHECK( s1.Height( ) == expectedY1 );
    BOOST_CHECK( s2.Width( ) == expectedX2 );
    BOOST_CHECK( s2.Height( ) == expectedY2 );
}

// --run_test=HWCommonTests/SizeFAssignTest1
BOOST_AUTO_TEST_CASE( SizeFAssignTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );

    float expectedWidth = v3;
    float expectedHeight = v4;

    s1.Assign( v3, v4 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFAddTest1
BOOST_AUTO_TEST_CASE( SizeFAddTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );

    float expectedWidth = v1 + v3;
    float expectedHeight = v2 + v4;

    s1.Add( v3, v4 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFAssignMinTest1
BOOST_AUTO_TEST_CASE( SizeFAssignMinTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );

    float expectedWidth = std::min( v1, v3 );
    float expectedHeight = std::min( v2, v4 );

    s1.AssignMin( v3, v4 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFAssignMinTest2
BOOST_AUTO_TEST_CASE( SizeFAssignMinTest2 )
{
    float v1 = 1.8f;
    float v2 = 3.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );

    float expectedWidth = std::min( v1, v3 );
    float expectedHeight = std::min( v2, v4 );

    s1.AssignMin( v3, v4 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFAssignMaxTest1
BOOST_AUTO_TEST_CASE( SizeFAssignMaxTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );

    float expectedWidth = std::max( v1, v3 );
    float expectedHeight = std::max( v2, v4 );

    s1.AssignMax( v3, v4 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFAssignMaxTest2
BOOST_AUTO_TEST_CASE( SizeFAssignMaxTest2 )
{
    float v1 = 1.8f;
    float v2 = 3.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );

    float expectedWidth = std::max( v1, v3 );
    float expectedHeight = std::max( v2, v4 );

    s1.AssignMax( v3, v4 );

    BOOST_CHECK( s1.Width( ) == expectedWidth );
    BOOST_CHECK( s1.Height( ) == expectedHeight );
}


// --run_test=HWCommonTests/SizeFMinTest1
BOOST_AUTO_TEST_CASE( SizeFMinTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedWidth = std::min( v1, v3 );
    float expectedHeight = std::min( v2, v4 );

    auto s3 = s1.Min( s2 );

    BOOST_CHECK( s3.Width( ) == expectedWidth );
    BOOST_CHECK( s3.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMinTest2
BOOST_AUTO_TEST_CASE( SizeFMinTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedWidth = std::min( v1, v3 );
    float expectedHeight = std::min( v2, v4 );

    auto s3 = std::min( s1, s2 );

    BOOST_CHECK( s3.Width( ) == expectedWidth );
    BOOST_CHECK( s3.Height( ) == expectedHeight );
}


// --run_test=HWCommonTests/SizeFMinTest3
BOOST_AUTO_TEST_CASE( SizeFMinTest3 )
{
    float v1 = 1.6f;
    float v2 = 2.6f;
    float v3 = 1.4f;
    float v4 = 2.4f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedWidth = std::min( v1, v3 );
    float expectedHeight = std::min( v2, v4 );

    auto s3 = s1.Min( s2 );

    BOOST_CHECK( s3.Width( ) == expectedWidth );
    BOOST_CHECK( s3.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMinTest4
BOOST_AUTO_TEST_CASE( SizeFMinTest4 )
{
    float v1 = 1.6f;
    float v2 = 2.6f;
    float v3 = 1.4f;
    float v4 = 2.4f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedWidth = std::min( v1, v3 );
    float expectedHeight = std::min( v2, v4 );

    auto s3 = std::min( s1, s2 );

    BOOST_CHECK( s3.Width( ) == expectedWidth );
    BOOST_CHECK( s3.Height( ) == expectedHeight );
}


// --run_test=HWCommonTests/SizeFMaxTest1
BOOST_AUTO_TEST_CASE( SizeFMaxTest1 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedWidth = std::max( v1, v3 );
    float expectedHeight = std::max( v2, v4 );

    auto s3 = s1.Max( s2 );

    BOOST_CHECK( s3.Width( ) == expectedWidth );
    BOOST_CHECK( s3.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMaxTest2
BOOST_AUTO_TEST_CASE( SizeFMaxTest2 )
{
    float v1 = 1.4f;
    float v2 = 2.4f;
    float v3 = 1.6f;
    float v4 = 2.6f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedWidth = std::max( v1, v3 );
    float expectedHeight = std::max( v2, v4 );

    auto s3 = std::max( s1, s2 );

    BOOST_CHECK( s3.Width( ) == expectedWidth );
    BOOST_CHECK( s3.Height( ) == expectedHeight );
}


// --run_test=HWCommonTests/SizeFMaxTest3
BOOST_AUTO_TEST_CASE( SizeFMaxTest3 )
{
    float v1 = 1.6f;
    float v2 = 2.6f;
    float v3 = 1.4f;
    float v4 = 2.4f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedWidth = std::max( v1, v3 );
    float expectedHeight = std::max( v2, v4 );

    auto s3 = s1.Max( s2 );

    BOOST_CHECK( s3.Width( ) == expectedWidth );
    BOOST_CHECK( s3.Height( ) == expectedHeight );
}

// --run_test=HWCommonTests/SizeFMaxTest4
BOOST_AUTO_TEST_CASE( SizeFMaxTest4 )
{
    float v1 = 1.6f;
    float v2 = 2.6f;
    float v3 = 1.4f;
    float v4 = 2.4f;

    SizeF s1( v1, v2 );
    SizeF s2( v3, v4 );

    float expectedWidth = std::max( v1, v3 );
    float expectedHeight = std::max( v2, v4 );

    auto s3 = std::max( s1, s2 );

    BOOST_CHECK( s3.Width( ) == expectedWidth );
    BOOST_CHECK( s3.Height( ) == expectedHeight );
}


// --run_test=HWCommonTests/RectangleFConstructorTest1
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest1 )
{
    constexpr float r1Left = 0.0f;
    constexpr float r1Top = 0.0f;
    constexpr float r1Right = 0.0f;
    constexpr float r1Bottom = 0.0f;

    constexpr float expectedLeft = r1Left;
    constexpr float expectedTop = r1Top;
    constexpr float expectedRight = r1Right;
    constexpr float expectedBottom = r1Bottom;

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;


    constexpr RectangleF rect;

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = expectedLeft == rect.Left( );
    constexpr bool topCheckOk = expectedTop == rect.Top( );
    constexpr bool rightCheckOk = expectedRight == rect.Right( );
    constexpr bool bottomCheckOk = expectedBottom == rect.Bottom( );
    constexpr bool widthCheckOk = expectedWidth == rectSize.Width( );
    constexpr bool heightCheckOk = expectedHeight == rectSize.Height( );

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );

}


// --run_test=HWCommonTests/RectangleFConstructorTest2
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest2 )
{
    constexpr float r1Left = 1.1f;
    constexpr float r1Top = 1.1f;
    constexpr float r1Right = 3.3f;
    constexpr float r1Bottom = 3.3f;

    constexpr float expectedLeft = r1Left;
    constexpr float expectedTop = r1Top;
    constexpr float expectedRight = r1Right;
    constexpr float expectedBottom = r1Bottom;

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;

    constexpr D2D_RECT_F rectSrc{ r1Left, r1Top, r1Right, r1Bottom };

    constexpr RectangleF rect( rectSrc );

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = expectedLeft == rect.Left( );
    constexpr bool topCheckOk = expectedTop == rect.Top( );
    constexpr bool rightCheckOk = expectedRight == rect.Right( );
    constexpr bool bottomCheckOk = expectedBottom == rect.Bottom( );
    constexpr bool widthCheckOk = expectedWidth == rectSize.Width( );
    constexpr bool heightCheckOk = expectedHeight == rectSize.Height( );

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}


// --run_test=HWCommonTests/RectangleFConstructorTest3
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest3 )
{
    constexpr float r1Left = 1.1f;
    constexpr float r1Top = 1.1f;
    constexpr float r1Right = 3.3f;
    constexpr float r1Bottom = 3.3f;

    constexpr float expectedLeft = r1Left;
    constexpr float expectedTop = r1Top;
    constexpr float expectedRight = r1Right;
    constexpr float expectedBottom = r1Bottom;

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;

    constexpr RectangleF rectSrc( r1Left, r1Top, r1Right, r1Bottom );

    constexpr RectangleF rect( rectSrc );

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = expectedLeft == rect.Left( );
    constexpr bool topCheckOk = expectedTop == rect.Top( );
    constexpr bool rightCheckOk = expectedRight == rect.Right( );
    constexpr bool bottomCheckOk = expectedBottom == rect.Bottom( );
    constexpr bool widthCheckOk = expectedWidth == rectSize.Width( );
    constexpr bool heightCheckOk = expectedHeight == rectSize.Height( );

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}

// --run_test=HWCommonTests/RectangleFConstructorTest4
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest4 )
{
    constexpr long r1Left = 1;
    constexpr long r1Top = 1;
    constexpr long r1Right = 3;
    constexpr long r1Bottom = 3;

    constexpr float expectedLeft = static_cast<float>(r1Left );
    constexpr float expectedTop = static_cast<float>( r1Top );
    constexpr float expectedRight = static_cast<float>( r1Right );
    constexpr float expectedBottom = static_cast<float>( r1Bottom );

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;

    constexpr D2D_RECT_L rectSrc{ r1Left, r1Top, r1Right, r1Bottom };

    constexpr RectangleF rect( rectSrc );

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = expectedLeft == rect.Left( );
    constexpr bool topCheckOk = expectedTop == rect.Top( );
    constexpr bool rightCheckOk = expectedRight == rect.Right( );
    constexpr bool bottomCheckOk = expectedBottom == rect.Bottom( );
    constexpr bool widthCheckOk = expectedWidth == rectSize.Width( );
    constexpr bool heightCheckOk = expectedHeight == rectSize.Height( );

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}

// --run_test=HWCommonTests/RectangleFConstructorTest5
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest5 )
{
    constexpr UInt32 r1Left = 1;
    constexpr UInt32 r1Top = 1;
    constexpr UInt32 r1Right = 3;
    constexpr UInt32 r1Bottom = 3;

    constexpr float expectedLeft = static_cast<float>( r1Left );
    constexpr float expectedTop = static_cast<float>( r1Top );
    constexpr float expectedRight = static_cast<float>( r1Right );
    constexpr float expectedBottom = static_cast<float>( r1Bottom );

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;

    constexpr D2D_RECT_U rectSrc{ r1Left, r1Top, r1Right, r1Bottom };

    constexpr RectangleF rect( rectSrc );

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = expectedLeft == rect.Left( );
    constexpr bool topCheckOk = expectedTop == rect.Top( );
    constexpr bool rightCheckOk = expectedRight == rect.Right( );
    constexpr bool bottomCheckOk = expectedBottom == rect.Bottom( );
    constexpr bool widthCheckOk = expectedWidth == rectSize.Width( );
    constexpr bool heightCheckOk = expectedHeight == rectSize.Height( );

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}

// --run_test=HWCommonTests/RectangleFConstructorTest6
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest6 )
{
    constexpr float r1Left = 1.1f;
    constexpr float r1Top = 1.1f;
    constexpr float r1Right = 3.3f;
    constexpr float r1Bottom = 3.3f;

    constexpr float expectedLeft = r1Left;
    constexpr float expectedTop = r1Top;
    constexpr float expectedRight = r1Right;
    constexpr float expectedBottom = r1Bottom;

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;


    constexpr RectangleF rect( r1Left, r1Top, r1Right, r1Bottom );

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = expectedLeft == rect.Left( );
    constexpr bool topCheckOk = expectedTop == rect.Top( );
    constexpr bool rightCheckOk = expectedRight == rect.Right( );
    constexpr bool bottomCheckOk = expectedBottom == rect.Bottom( );
    constexpr bool widthCheckOk = expectedWidth == rectSize.Width( );
    constexpr bool heightCheckOk = expectedHeight == rectSize.Height( );

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );

}

// --run_test=HWCommonTests/RectangleFConstructorTest7
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest7 )
{
    constexpr float r1Left = 1.1f;
    constexpr float r1Top = 1.1f;
    constexpr float r1Right = 3.3f;
    constexpr float r1Bottom = 3.3f;

    constexpr float expectedLeft = r1Left;
    constexpr float expectedTop = r1Top;
    constexpr float expectedRight = r1Right;
    constexpr float expectedBottom = r1Bottom;

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;

    constexpr PointF leftTop( r1Left, r1Top );
    constexpr PointF rightBottom( r1Right, r1Bottom );

    constexpr RectangleF rect( leftTop, rightBottom );

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = expectedLeft == rect.Left( );
    constexpr bool topCheckOk = expectedTop == rect.Top( );
    constexpr bool rightCheckOk = expectedRight == rect.Right( );
    constexpr bool bottomCheckOk = expectedBottom == rect.Bottom( );
    constexpr bool widthCheckOk = expectedWidth == rectSize.Width( );
    constexpr bool heightCheckOk = expectedHeight == rectSize.Height( );
    constexpr bool allCheckOk = leftCheckOk && topCheckOk && rightCheckOk && bottomCheckOk && widthCheckOk && heightCheckOk;

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );

}

// --run_test=HWCommonTests/RectangleFConstructorTest8
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest8 )
{
    constexpr float r1Left = 1.1f;
    constexpr float r1Top = 1.1f;
    constexpr float r1Right = 3.3f;
    constexpr float r1Bottom = 3.3f;

    constexpr float expectedLeft = r1Left;
    constexpr float expectedTop = r1Top;
    constexpr float expectedRight = r1Right;
    constexpr float expectedBottom = r1Bottom;

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;

    constexpr D2D_POINT_2F leftTop( r1Left, r1Top );
    constexpr D2D_POINT_2F rightBottom( r1Right, r1Bottom );

    constexpr RectangleF rect( leftTop, rightBottom );

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = expectedLeft == rect.Left( );
    constexpr bool topCheckOk = expectedTop == rect.Top( );
    constexpr bool rightCheckOk = expectedRight == rect.Right( );
    constexpr bool bottomCheckOk = expectedBottom == rect.Bottom( );
    constexpr bool widthCheckOk = expectedWidth == rectSize.Width( );
    constexpr bool heightCheckOk = expectedHeight == rectSize.Height( );
    constexpr bool allCheckOk = leftCheckOk && topCheckOk && rightCheckOk && bottomCheckOk && widthCheckOk && heightCheckOk;

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}

// --run_test=HWCommonTests/RectangleFConstructorTest9
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest9 )
{
    constexpr float r1Left = 1.1f;
    constexpr float r1Top = 1.1f;
    constexpr float r1Right = 3.f;
    constexpr float r1Bottom = 3.f;

    constexpr float expectedLeft = r1Left;
    constexpr float expectedTop = r1Top;
    constexpr float expectedRight = r1Right;
    constexpr float expectedBottom = r1Bottom;

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;

    constexpr D2D_POINT_2F leftTop( r1Left, r1Top );
    constexpr D2D_POINT_2L rightBottom( static_cast<Int32>( r1Right ), static_cast<Int32>( r1Bottom ) );

    constexpr RectangleF rect( leftTop, rightBottom );

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = expectedLeft == rect.Left( );
    constexpr bool topCheckOk = expectedTop == rect.Top( );
    constexpr bool rightCheckOk = expectedRight == rect.Right( );
    constexpr bool bottomCheckOk = expectedBottom == rect.Bottom( );
    constexpr bool widthCheckOk = expectedWidth == rectSize.Width( );
    constexpr bool heightCheckOk = expectedHeight == rectSize.Height( );
    constexpr bool allCheckOk = leftCheckOk && topCheckOk && rightCheckOk && bottomCheckOk && widthCheckOk && heightCheckOk;

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}

// --run_test=HWCommonTests/RectangleFConstructorTest10
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest10 )
{
    constexpr float r1Left = 1.f;
    constexpr float r1Top = 1.f;
    constexpr float r1Right = 3.3f;
    constexpr float r1Bottom = 3.3f;

    constexpr float expectedLeft = r1Left;
    constexpr float expectedTop = r1Top;
    constexpr float expectedRight = r1Right;
    constexpr float expectedBottom = r1Bottom;

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;

    constexpr D2D_POINT_2L leftTop( static_cast<Int32>( r1Left ), static_cast<Int32>( r1Top ) );
    constexpr D2D_POINT_2F rightBottom( r1Right, r1Bottom );

    constexpr RectangleF rect( leftTop, rightBottom );

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = expectedLeft == rect.Left( );
    constexpr bool topCheckOk = expectedTop == rect.Top( );
    constexpr bool rightCheckOk = expectedRight == rect.Right( );
    constexpr bool bottomCheckOk = expectedBottom == rect.Bottom( );
    constexpr bool widthCheckOk = expectedWidth == rectSize.Width( );
    constexpr bool heightCheckOk = expectedHeight == rectSize.Height( );
    constexpr bool allCheckOk = leftCheckOk && topCheckOk && rightCheckOk && bottomCheckOk && widthCheckOk && heightCheckOk;

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}


// --run_test=HWCommonTests/RectangleFConstructorTest11
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest11 )
{
    constexpr float r1Left = 1.1f;
    constexpr float r1Top = 1.1f;
    constexpr float r1Right = 3.3f;
    constexpr float r1Bottom = 3.3f;

    constexpr float expectedLeft = r1Left;
    constexpr float expectedTop = r1Top;
    constexpr float expectedRight = r1Right;
    constexpr float expectedBottom = r1Bottom;

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;

    constexpr PointF leftTop( r1Left, r1Top );
    constexpr SizeF size( r1Right - r1Left, r1Bottom - r1Top );

    constexpr RectangleF rect( leftTop, size );

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = AreNearlyEqual( expectedLeft, rect.Left( ) );
    constexpr bool topCheckOk = AreNearlyEqual( expectedTop, rect.Top( ) );
    constexpr bool rightCheckOk = AreNearlyEqual( expectedRight, rect.Right( ) );
    constexpr bool bottomCheckOk = AreNearlyEqual( expectedBottom, rect.Bottom( ) );
    constexpr bool widthCheckOk = AreNearlyEqual( expectedWidth, rectSize.Width( ) );
    constexpr bool heightCheckOk = AreNearlyEqual( expectedHeight, rectSize.Height( ) );
    constexpr bool allCheckOk = leftCheckOk && topCheckOk && rightCheckOk && bottomCheckOk && widthCheckOk && heightCheckOk;

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}


// --run_test=HWCommonTests/RectangleFConstructorTest12
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest12 )
{
    constexpr float r1Left = 1.f;
    constexpr float r1Top = 1.f;
    constexpr float r1Right = 3.f;
    constexpr float r1Bottom = 3.f;

    constexpr float expectedLeft = r1Left;
    constexpr float expectedTop = r1Top;
    constexpr float expectedRight = r1Right;
    constexpr float expectedBottom = r1Bottom;

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;

    constexpr PointF leftTop( r1Left, r1Top );
    constexpr SIZE size( static_cast<LONG>( r1Right - r1Left ), static_cast<LONG>( r1Bottom - r1Top ) );

    constexpr RectangleF rect( leftTop, size );

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = AreNearlyEqual( expectedLeft, rect.Left( ) );
    constexpr bool topCheckOk = AreNearlyEqual( expectedTop, rect.Top( ) );
    constexpr bool rightCheckOk = AreNearlyEqual( expectedRight, rect.Right( ) );
    constexpr bool bottomCheckOk = AreNearlyEqual( expectedBottom, rect.Bottom( ) );
    constexpr bool widthCheckOk = AreNearlyEqual( expectedWidth, rectSize.Width( ) );
    constexpr bool heightCheckOk = AreNearlyEqual( expectedHeight, rectSize.Height( ) );
    constexpr bool allCheckOk = leftCheckOk && topCheckOk && rightCheckOk && bottomCheckOk && widthCheckOk && heightCheckOk;

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}

// --run_test=HWCommonTests/RectangleFConstructorTest13
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest13 )
{
    constexpr float r1Left = 1.f;
    constexpr float r1Top = 1.f;
    constexpr float r1Right = 3.f;
    constexpr float r1Bottom = 3.f;

    constexpr float expectedLeft = r1Left;
    constexpr float expectedTop = r1Top;
    constexpr float expectedRight = r1Right;
    constexpr float expectedBottom = r1Bottom;

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;

    constexpr PointF leftTop( r1Left, r1Top );
    constexpr D2D_SIZE_U size( static_cast<LONG>( r1Right - r1Left ), static_cast<LONG>( r1Bottom - r1Top ) );

    constexpr RectangleF rect( leftTop, size );

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = AreNearlyEqual( expectedLeft, rect.Left( ) );
    constexpr bool topCheckOk = AreNearlyEqual( expectedTop, rect.Top( ) );
    constexpr bool rightCheckOk = AreNearlyEqual( expectedRight, rect.Right( ) );
    constexpr bool bottomCheckOk = AreNearlyEqual( expectedBottom, rect.Bottom( ) );
    constexpr bool widthCheckOk = AreNearlyEqual( expectedWidth, rectSize.Width( ) );
    constexpr bool heightCheckOk = AreNearlyEqual( expectedHeight, rectSize.Height( ) );
    constexpr bool allCheckOk = leftCheckOk && topCheckOk && rightCheckOk && bottomCheckOk && widthCheckOk && heightCheckOk;

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}

// --run_test=HWCommonTests/RectangleFConstructorTest14
BOOST_AUTO_TEST_CASE( RectangleFConstructorTest14 )
{
    constexpr float r1Left = 0.f;
    constexpr float r1Top = 0.f;
    constexpr float r1Right = 3.f;
    constexpr float r1Bottom = 3.f;

    constexpr float expectedLeft = r1Left;
    constexpr float expectedTop = r1Top;
    constexpr float expectedRight = r1Right;
    constexpr float expectedBottom = r1Bottom;

    constexpr float expectedWidth = expectedRight - expectedLeft;
    constexpr float expectedHeight = expectedBottom - expectedTop;

    constexpr PointF leftTop( r1Left, r1Top );
    constexpr SizeF size( r1Right - r1Left, r1Bottom - r1Top );

    constexpr RectangleF rect( size );

    constexpr SizeF rectSize = rect.Size( );

    constexpr bool leftCheckOk = AreNearlyEqual( expectedLeft, rect.Left( ) );
    constexpr bool topCheckOk = AreNearlyEqual( expectedTop, rect.Top( ) );
    constexpr bool rightCheckOk = AreNearlyEqual( expectedRight, rect.Right( ) );
    constexpr bool bottomCheckOk = AreNearlyEqual( expectedBottom, rect.Bottom( ) );
    constexpr bool widthCheckOk = AreNearlyEqual( expectedWidth, rectSize.Width( ) );
    constexpr bool heightCheckOk = AreNearlyEqual( expectedHeight, rectSize.Height( ) );
    constexpr bool allCheckOk = leftCheckOk && topCheckOk && rightCheckOk && bottomCheckOk && widthCheckOk && heightCheckOk;

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}


// --run_test=HWCommonTests/RectangleFAssignmentOperatorTest1
BOOST_AUTO_TEST_CASE( RectangleFAssignmentOperatorTest1 )
{
    float r1Left = 1.4f;
    float r1Top = 1.6f;
    float r1Right = 3.5f;
    float r1Bottom = 3.6f;

    float expectedLeft = r1Left;
    float expectedTop = r1Top;
    float expectedRight = r1Right;
    float expectedBottom = r1Bottom;

    float expectedWidth = expectedRight - expectedLeft;
    float expectedHeight = expectedBottom - expectedTop;

    RectangleF rectSrc( r1Left, r1Top, r1Right, r1Bottom );
    RectangleF rect;
    rect = rectSrc;

    SizeF rectSize = rect.Size( );

    bool leftCheckOk = AreNearlyEqual( expectedLeft, rect.Left( ) );
    bool topCheckOk = AreNearlyEqual( expectedTop, rect.Top( ) );
    bool rightCheckOk = AreNearlyEqual( expectedRight, rect.Right( ) );
    bool bottomCheckOk = AreNearlyEqual( expectedBottom, rect.Bottom( ) );
    bool widthCheckOk = AreNearlyEqual( expectedWidth, rectSize.Width( ) );
    bool heightCheckOk = AreNearlyEqual( expectedHeight, rectSize.Height( ) );
    bool allCheckOk = leftCheckOk && topCheckOk && rightCheckOk && bottomCheckOk && widthCheckOk && heightCheckOk;

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}

// --run_test=HWCommonTests/RectangleFAssignmentOperatorTest2
BOOST_AUTO_TEST_CASE( RectangleFAssignmentOperatorTest2 )
{
    float r1Left = 1.4f;
    float r1Top = 1.6f;
    float r1Right = 3.5f;
    float r1Bottom = 3.6f;

    float expectedLeft = r1Left;
    float expectedTop = r1Top;
    float expectedRight = r1Right;
    float expectedBottom = r1Bottom;

    float expectedWidth = expectedRight - expectedLeft;
    float expectedHeight = expectedBottom - expectedTop;

    D2D_RECT_F rectSrc( r1Left, r1Top, r1Right, r1Bottom );
    RectangleF rect;
    rect = rectSrc;

    SizeF rectSize = rect.Size( );

    bool leftCheckOk = AreNearlyEqual( expectedLeft, rect.Left( ) );
    bool topCheckOk = AreNearlyEqual( expectedTop, rect.Top( ) );
    bool rightCheckOk = AreNearlyEqual( expectedRight, rect.Right( ) );
    bool bottomCheckOk = AreNearlyEqual( expectedBottom, rect.Bottom( ) );
    bool widthCheckOk = AreNearlyEqual( expectedWidth, rectSize.Width( ) );
    bool heightCheckOk = AreNearlyEqual( expectedHeight, rectSize.Height( ) );
    bool allCheckOk = leftCheckOk && topCheckOk && rightCheckOk && bottomCheckOk && widthCheckOk && heightCheckOk;

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}


// --run_test=HWCommonTests/RectangleFAssignmentOperatorTest3
BOOST_AUTO_TEST_CASE( RectangleFAssignmentOperatorTest3 )
{
    float r1Left = 2.f;
    float r1Top = 3.f;
    float r1Right = 5.f;
    float r1Bottom = 6.f;

    float expectedLeft = r1Left;
    float expectedTop = r1Top;
    float expectedRight = r1Right;
    float expectedBottom = r1Bottom;

    float expectedWidth = expectedRight - expectedLeft;
    float expectedHeight = expectedBottom - expectedTop;

    D2D_RECT_L rectSrc( static_cast<LONG>( r1Left ), static_cast<LONG>( r1Top ), static_cast<LONG>( r1Right ), static_cast<LONG>( r1Bottom ) );
    RectangleF rect;
    rect = rectSrc;

    SizeF rectSize = rect.Size( );

    bool leftCheckOk = AreNearlyEqual( expectedLeft, rect.Left( ) );
    bool topCheckOk = AreNearlyEqual( expectedTop, rect.Top( ) );
    bool rightCheckOk = AreNearlyEqual( expectedRight, rect.Right( ) );
    bool bottomCheckOk = AreNearlyEqual( expectedBottom, rect.Bottom( ) );
    bool widthCheckOk = AreNearlyEqual( expectedWidth, rectSize.Width( ) );
    bool heightCheckOk = AreNearlyEqual( expectedHeight, rectSize.Height( ) );
    bool allCheckOk = leftCheckOk && topCheckOk && rightCheckOk && bottomCheckOk && widthCheckOk && heightCheckOk;

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}

// --run_test=HWCommonTests/RectangleFAssignmentOperatorTest4
BOOST_AUTO_TEST_CASE( RectangleFAssignmentOperatorTest4 )
{
    float r1Left = 2.f;
    float r1Top = 3.f;
    float r1Right = 5.f;
    float r1Bottom = 6.f;

    float expectedLeft = r1Left;
    float expectedTop = r1Top;
    float expectedRight = r1Right;
    float expectedBottom = r1Bottom;

    float expectedWidth = expectedRight - expectedLeft;
    float expectedHeight = expectedBottom - expectedTop;

    D2D_RECT_U rectSrc( static_cast<UInt32>( r1Left ), static_cast<UInt32>( r1Top ), static_cast<UInt32>( r1Right ), static_cast<UInt32>( r1Bottom ) );
    RectangleF rect;
    rect = rectSrc;

    SizeF rectSize = rect.Size( );

    bool leftCheckOk = AreNearlyEqual( expectedLeft, rect.Left( ) );
    bool topCheckOk = AreNearlyEqual( expectedTop, rect.Top( ) );
    bool rightCheckOk = AreNearlyEqual( expectedRight, rect.Right( ) );
    bool bottomCheckOk = AreNearlyEqual( expectedBottom, rect.Bottom( ) );
    bool widthCheckOk = AreNearlyEqual( expectedWidth, rectSize.Width( ) );
    bool heightCheckOk = AreNearlyEqual( expectedHeight, rectSize.Height( ) );
    bool allCheckOk = leftCheckOk && topCheckOk && rightCheckOk && bottomCheckOk && widthCheckOk && heightCheckOk;

    BOOST_CHECK( leftCheckOk );
    BOOST_CHECK( topCheckOk );
    BOOST_CHECK( rightCheckOk );
    BOOST_CHECK( bottomCheckOk );
    BOOST_CHECK( widthCheckOk );
    BOOST_CHECK( heightCheckOk );
}

// --run_test=HWCommonTests/RectangleFIntersectWithTest1
BOOST_AUTO_TEST_CASE( RectangleFIntersectWithTest1 )
{
    RectangleF rect1( 1, 1, 3, 3 );
    RectangleF rect2( 2, 2, 4, 4 );

    RectangleF expected( 2, 2, 3, 3 );
    rect1.IntersectWith( rect2 );

    bool asExpected = expected == rect1;

    BOOST_CHECK( asExpected );
}

// --run_test=HWCommonTests/RectangleFIntersectWithTest2
BOOST_AUTO_TEST_CASE( RectangleFIntersectWithTest2 )
{
    RectangleF rect1( 3, 3, 1, 1 );
    RectangleF rect2( 4, 4, 2, 2 );

    RectangleF expected( 2, 2, 3, 3 );
    rect1.IntersectWith( rect2 );

    bool asExpected = expected == rect1;

    BOOST_CHECK( asExpected );
}


// --run_test=HWCommonTests/RectangleFIntersectWithTest3
BOOST_AUTO_TEST_CASE( RectangleFIntersectWithTest3 )
{
    RectangleF rect1( 3, 1, 1, 3 );
    RectangleF rect2( 4, 2, 2, 4 );

    RectangleF expected( 2, 2, 3, 3 );
    rect1.IntersectWith( rect2 );

    bool asExpected = expected == rect1;

    BOOST_CHECK( asExpected );
}


// --run_test=HWCommonTests/RectangleFIntersectWithTest4
BOOST_AUTO_TEST_CASE( RectangleFIntersectWithTest4 )
{
    RectangleF rect1( 1, 1, 4, 4 );
    RectangleF rect2( 3, 3, 5, 5 );

    RectangleF expected( 3, 3, 4, 4 );
    rect1.IntersectWith( rect2 );

    bool asExpected = expected == rect1;

    BOOST_CHECK( asExpected );
}


// --run_test=HWCommonTests/RectangleFIntersectWithTest5
BOOST_AUTO_TEST_CASE( RectangleFIntersectWithTest5 )
{
    RectangleF rect1( 1, 4, 4, 6 );
    RectangleF rect2( 3, 3, 5, 5 );

    RectangleF expected( 3, 4, 4, 5 );
    rect1.IntersectWith( rect2 );

    bool asExpected = expected == rect1;

    BOOST_CHECK( asExpected );
}




BOOST_AUTO_TEST_SUITE_END( )