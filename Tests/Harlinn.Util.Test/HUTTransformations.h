#pragma once
#ifndef HARLINN_UTIL_TEST_HUTTRANSFORMATION_H_
#define HARLINN_UTIL_TEST_HUTTRANSFORMATION_H_

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

#include "HUTVectorMath.h"
#include <Harlinn/Math/Transformations.h>

namespace Harlinn::Util::Test
{
    inline pbrto::Transform ConvertTransform( const pbrt::Transform& transform )
    {
        pbrt::SquareMatrix<4> pm = transform.GetMatrix( );
        pbrto::SquareMatrix<4> m(
            pm[ 0 ][ 0 ], pm[ 0 ][ 1 ], pm[ 0 ][ 2 ], pm[ 0 ][ 3 ],
            pm[ 1 ][ 0 ], pm[ 1 ][ 1 ], pm[ 1 ][ 2 ], pm[ 1 ][ 3 ],
            pm[ 2 ][ 0 ], pm[ 2 ][ 1 ], pm[ 2 ][ 2 ], pm[ 2 ][ 3 ],
            pm[ 3 ][ 0 ], pm[ 3 ][ 1 ], pm[ 3 ][ 2 ], pm[ 3 ][ 3 ] );
        return pbrto::Transform( m );
    }

    inline pbrt::Transform ConvertTransform( const pbrto::Transform& transform )
    {
        pbrto::SquareMatrix<4> pm = transform.GetMatrix( );
        pbrt::SquareMatrix<4> m(
            pm[ 0 ][ 0 ], pm[ 0 ][ 1 ], pm[ 0 ][ 2 ], pm[ 0 ][ 3 ],
            pm[ 1 ][ 0 ], pm[ 1 ][ 1 ], pm[ 1 ][ 2 ], pm[ 1 ][ 3 ],
            pm[ 2 ][ 0 ], pm[ 2 ][ 1 ], pm[ 2 ][ 2 ], pm[ 2 ][ 3 ],
            pm[ 3 ][ 0 ], pm[ 3 ][ 1 ], pm[ 3 ][ 2 ], pm[ 3 ][ 3 ] );
        return pbrt::Transform( m );
    }

    inline bool Equal( const pbrto::Transform& t1, const pbrto::Transform& t2, float epsilon = 0.0001f )
    {
        return Equal( t1.GetMatrix( ), t2.GetMatrix( ), epsilon );
    }

    inline bool Equal( const pbrto::Transform& t1, const pbrt::Transform& t2, float epsilon = 0.0001f )
    {
        return Equal( t1.GetMatrix( ), ConvertMatrix( t2.GetMatrix( ) ), epsilon );
    }

    inline bool Equal( const pbrt::Transform& t1, const pbrto::Transform& t2, float epsilon = 0.0001f )
    {
        return Equal( ConvertMatrix( t1.GetMatrix( ) ), t2.GetMatrix( ), epsilon );
    }


    inline bool Equal( const pbrt::Transform& t1, const pbrt::Transform& t2, float epsilon = 0.0001f )
    {
        return Equal( t1.GetMatrix( ), t2.GetMatrix( ), epsilon );
    }




}

#endif