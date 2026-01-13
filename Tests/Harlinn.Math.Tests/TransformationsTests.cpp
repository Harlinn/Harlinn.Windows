#include "pch.h"

/*
   Copyright 2024-2026 Espen Harlinn

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

#include <Harlinn/Math/Transformations.h>
#include <HUTTransformations.h>

using namespace Harlinn;
using namespace Harlinn::Common::Core;
using namespace Harlinn::Util::Test;

namespace
{
    void Check( const pbrt::Transform& pbrtTransform, const Math::AffineTransformation& mathTransformation )
    {
        pbrt::Vector3f pbrtVector( 4.f, 5.f, 6.f );
        Math::Vector3f mathVector( 4.f, 5.f, 6.f );

        pbrt::Vector3f pbrtVectorTransformed = pbrtTransform( pbrtVector );
        Math::Vector3f mathVectorTransformed = mathTransformation( mathVector );

        auto equal = Equal( pbrtVectorTransformed, mathVectorTransformed );
        BOOST_CHECK( equal );

        pbrt::Vector3f pbrtVectorInverseTransformed = pbrtTransform.ApplyInverse( pbrtVectorTransformed );
        Math::Vector3f mathVectorInverseTransformed = mathTransformation.ApplyInverse( mathVectorTransformed );

        equal = Equal( pbrtVectorInverseTransformed, mathVectorInverseTransformed );
        BOOST_CHECK( equal );


        pbrt::Point3f pbrtPoint( 4.f, 5.f, 6.f );
        Math::Point3f mathPoint( 4.f, 5.f, 6.f );

        pbrt::Point3f pbrtPointTransformed = pbrtTransform( pbrtPoint );
        Math::Point3f mathPointTransformed = mathTransformation( mathPoint );

        equal = Equal( pbrtPointTransformed, mathPointTransformed );
        BOOST_CHECK( equal );

        pbrt::Point3f pbrtPointInverseTransformed = pbrtTransform.ApplyInverse( pbrtPointTransformed );
        Math::Point3f mathPointInverseTransformed = mathTransformation.ApplyInverse( mathPointTransformed );

        equal = Equal( pbrtPointInverseTransformed, mathPointInverseTransformed );
        BOOST_CHECK( equal );

        pbrt::Normal3f pbrtNormal( 4.f, 5.f, 6.f );
        Math::Normal3f mathNormal( 4.f, 5.f, 6.f );

        pbrt::Normal3f pbrtNormalTransformed = pbrtTransform( pbrtNormal );
        Math::Normal3f mathNormalTransformed = mathTransformation( mathNormal );

        equal = Equal( pbrtNormalTransformed, mathNormalTransformed );
        BOOST_CHECK( equal );

        pbrt::Normal3f pbrtNormalInverseTransformed = pbrtTransform.ApplyInverse( pbrtNormalTransformed );
        Math::Normal3f mathNormalInverseTransformed = mathTransformation.ApplyInverse( mathNormalTransformed );

        equal = Equal( pbrtNormalInverseTransformed, mathNormalInverseTransformed );
        BOOST_CHECK( equal );

    }
}


BOOST_FIXTURE_TEST_SUITE( TransformationsTests, LocalFixture )

// --run_test=TransformationsTests/DefaultConstructorTest1
BOOST_AUTO_TEST_CASE( DefaultConstructorTest1 )
{
    pbrt::Transform pbrtTransform;
    Math::AffineTransformation mathTransformation;

    Check( pbrtTransform, mathTransformation );
}


// --run_test=TransformationsTests/TranslateTest1
BOOST_AUTO_TEST_CASE( TranslateTest1 )
{
    pbrt::Transform pbrtTransform = pbrt::Translate( pbrt::Vector3f(1.5f, 2.5f, 3.f) );
    Math::AffineTransformation mathTransformation = Math::AffineTransformation::Translate( 1.5f, 2.5f, 3.f );

    Check( pbrtTransform, mathTransformation );
}


// --run_test=TransformationsTests/ScaleTest1
BOOST_AUTO_TEST_CASE( ScaleTest1 )
{
    pbrt::Transform pbrtTransform = pbrt::Scale( 1.5f, 2.5f, 3.f );
    Math::AffineTransformation mathTransformation = Math::AffineTransformation::Scale( 1.5f, 2.5f, 3.f );

    Check( pbrtTransform, mathTransformation );

}

// --run_test=TransformationsTests/RotateXTest1
BOOST_AUTO_TEST_CASE( RotateXTest1 )
{
    float angle = 30.f;
    float angleInRadians = Math::Deg2Rad( angle );
    pbrt::Transform pbrtTransform = pbrt::RotateX( angle );
    Math::AffineTransformation mathTransformation = Math::AffineTransformation::RotateX( angleInRadians );

    Check( pbrtTransform, mathTransformation );

}

// --run_test=TransformationsTests/RotateYTest1
BOOST_AUTO_TEST_CASE( RotateYTest1 )
{
    float angle = 30.f;
    float angleInRadians = Math::Deg2Rad( angle );
    pbrt::Transform pbrtTransform = pbrt::RotateY( angle );
    Math::AffineTransformation mathTransformation = Math::AffineTransformation::RotateY( angleInRadians );

    Check( pbrtTransform, mathTransformation );

}

// --run_test=TransformationsTests/RotateZTest1
BOOST_AUTO_TEST_CASE( RotateZTest1 )
{
    float angle = 30.f;
    float angleInRadians = Math::Deg2Rad( angle );
    pbrt::Transform pbrtTransform = pbrt::RotateZ( angle );
    Math::AffineTransformation mathTransformation = Math::AffineTransformation::RotateZ( angleInRadians );

    Check( pbrtTransform, mathTransformation );
}


// --run_test=TransformationsTests/LookAtTest1
BOOST_AUTO_TEST_CASE( LookAtTest1 )
{
    pbrt::Point3f pbrtCameraPosition( 1.f, -1.5f, 2.f );
    pbrt::Point3f pbrtFocusPosition( 20.f, 20.f, 20.f );
    pbrt::Vector3f pbrtUpDirection( 0.f, 1.f, 0.f );

    Math::Point3f mathCameraPosition( 1.f, -1.5f, 2.f );
    Math::Point3f mathFocusPosition( 20.f, 20.f, 20.f );
    Math::Vector3f mathUpDirection( 0.f, 1.f, 0.f );

    pbrt::Transform pbrtTransform = pbrt::LookAt( pbrtCameraPosition, pbrtFocusPosition, pbrtUpDirection );
    Math::AffineTransformation mathTransformation = Math::AffineTransformation::LookAt( mathCameraPosition, mathFocusPosition, mathUpDirection );

    Check( pbrtTransform, mathTransformation );
}









BOOST_AUTO_TEST_SUITE_END( )
