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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/util/NewVecMath.h>
#include <pbrto/util/NewTransform.h>

namespace pbrto
{

    // DirectionCone Function Definitions
    PBRTO_EXPORT DirectionCone Union( const DirectionCone& a, const DirectionCone& b )
    {
        // Handle the cases where one or both cones are empty
        if ( a.IsEmpty( ) )
            return b;
        if ( b.IsEmpty( ) )
            return a;

        // Handle the cases where one cone is inside the other
        Float theta_a = Math::SafeACos( a.cosTheta ); 
        Float theta_b = Math::SafeACos( b.cosTheta );

        Float theta_d = Math::ScalarAngleBetween( a.w, b.w );
        if ( std::min( theta_d + theta_b, Pi ) <= theta_a )
            return a;
        if ( std::min( theta_d + theta_a, Pi ) <= theta_b )
            return b;

        // Compute the spread angle of the merged cone, $\theta_o$
        Float theta_o = ( theta_a + theta_d + theta_b ) / 2;
        if ( theta_o >= Pi )
        {
            return DirectionCone::EntireSphere( );
        }

        // Find the merged cone's axis and return cone union
        Float theta_r = theta_o - theta_a;
        Vector3f wr = Cross( a.w, b.w );
        if ( ScalarLengthSquared( wr ) == 0 )
        {
            return DirectionCone::EntireSphere( );
        }
        Vector3f w = RotateRadians( theta_r, wr )( a.w );
        return DirectionCone( w, Math::Cos( theta_o ) );
    }

}