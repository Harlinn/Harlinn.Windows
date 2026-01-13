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
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard 
//

#include "pch.h"
#include "HDMCBoundingSphere.h"
#include "HDMCVectorMath.h"

namespace Harlinn::Windows::DirectX::MiniEngine::Math
{
    BoundingSphere BoundingSphere::Union( const BoundingSphere& rhs )
    {
#ifdef HDMC_USES_HCC_MATH
        auto radA = GetRadius( );
        if ( m::Traits::First( radA.simd ) == 0.0f )
            return rhs;

        auto radB = rhs.GetRadius( );
        if ( m::Traits::First( radB.simd ) == 0.0f )
            return *this;

        Vector3 diff = GetCenter( ) - rhs.GetCenter( );
        auto dist = Length( diff );

        // Safe normalize vector between sphere centers
        diff = m::Traits::First( dist.simd ) < 1e-6f ? Vector3( Constants::IdentityR1 ) : diff * m::Reciprocal( dist );

        Vector3 extremeA = GetCenter( ) + diff * m::Max( Vector3( radA.simd ), Vector3( radB.simd ) - dist );
        Vector3 extremeB = rhs.GetCenter( ) - diff * m::Max( Vector3( radB.simd ), Vector3( radA.simd ) - dist );

        return BoundingSphere( ( extremeA + extremeB ) * 0.5f, Scalar( m::ScalarLength( extremeA - extremeB ) * 0.5f) );
#else
        float radA = GetRadius( );
        if ( radA == 0.0f )
            return rhs;

        float radB = rhs.GetRadius( );
        if ( radB == 0.0f )
            return *this;

        Vector3 diff = GetCenter( ) - rhs.GetCenter( );
        float dist = Length( diff );

        // Safe normalize vector between sphere centers
        diff = dist < 1e-6f ? Vector3( kXUnitVector ) : diff * Recip( dist );
        Vector3 extremeA = GetCenter( ) + diff * Max( radA, radB - dist );
        Vector3 extremeB = rhs.GetCenter( ) - diff * Max( radB, radA - dist );

        return BoundingSphere( ( extremeA + extremeB ) * 0.5f, Length( extremeA - extremeB ) * 0.5f );
#endif

        
        
    }
}