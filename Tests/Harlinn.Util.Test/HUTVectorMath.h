#pragma once
#ifndef HARLINN_UTIL_TEST_HUTVECTORMATH_H_
#define HARLINN_UTIL_TEST_HUTVECTORMATH_H_

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

#include "HUTDef.h"
#include <HCCVectorMath.h>

namespace Harlinn::Util::Test
{
    inline bool Equal( float first, float second, float epsilon = 0.0001f )
    {
        auto delta = first - second;
        return std::abs( delta ) <= epsilon;
    }


    inline Common::Core::Math::SquareMatrix<float, 4> ConvertMatrix( const pbrt::SquareMatrix<4>& m )
    {
        Common::Core::Math::SquareMatrix<float, 4> result(
            m[ 0 ][ 0 ], m[ 0 ][ 1 ], m[ 0 ][ 2 ], m[ 0 ][ 3 ],
            m[ 1 ][ 0 ], m[ 1 ][ 1 ], m[ 1 ][ 2 ], m[ 1 ][ 3 ],
            m[ 2 ][ 0 ], m[ 2 ][ 1 ], m[ 2 ][ 2 ], m[ 2 ][ 3 ],
            m[ 3 ][ 0 ], m[ 3 ][ 1 ], m[ 3 ][ 2 ], m[ 3 ][ 3 ] );
        return result;
    }

    inline pbrt::SquareMatrix<4> ConvertMatrix( const Common::Core::Math::SquareMatrix<float, 4>& m )
    {
        pbrt::SquareMatrix<4> result(
            m[ 0 ][ 0 ], m[ 0 ][ 1 ], m[ 0 ][ 2 ], m[ 0 ][ 3 ],
            m[ 1 ][ 0 ], m[ 1 ][ 1 ], m[ 1 ][ 2 ], m[ 1 ][ 3 ],
            m[ 2 ][ 0 ], m[ 2 ][ 1 ], m[ 2 ][ 2 ], m[ 2 ][ 3 ],
            m[ 3 ][ 0 ], m[ 3 ][ 1 ], m[ 3 ][ 2 ], m[ 3 ][ 3 ] );
        return result;
    }


    inline bool Equal( const Common::Core::Math::SquareMatrix<float, 4>& m1, const Common::Core::Math::SquareMatrix<float, 4>& m2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 4; i++ )
        {
            for ( size_t j = 0; j < 4; j++ )
            {
                auto v1 = m1[ i ][ j ];
                float v2 = m2[ i ][ j ];
                auto delta = v1 - v2;
                if ( std::abs( delta ) > epsilon )
                {
                    return false;
                }
            }
        }
        return true;
    }

    inline bool Equal( const Common::Core::Math::SquareMatrix<float, 4>& m1, const Common::Core::Math::SquareMatrix<float, 4>::Simd& m2simd, float epsilon = 0.0001f )
    {
        Common::Core::Math::SquareMatrix<float, 4> m2( m2simd );
        return Equal( m1, m2 );
    }

    inline bool Equal( const Common::Core::Math::SquareMatrix<float, 4>::Simd& m1simd, const Common::Core::Math::SquareMatrix<float, 4>& m2, float epsilon = 0.0001f )
    {
        Common::Core::Math::SquareMatrix<float, 4> m1( m1simd );
        return Equal( m1, m2 );
    }

    inline bool Equal( const Common::Core::Math::SquareMatrix<float, 4>::Simd& m1simd, const Common::Core::Math::SquareMatrix<float, 4>::Simd& m2simd, float epsilon = 0.0001f )
    {
        Common::Core::Math::SquareMatrix<float, 4> m1( m1simd );
        Common::Core::Math::SquareMatrix<float, 4> m2( m2simd );
        return Equal( m1, m2 );
    }


#ifndef PBRT_USES_HCCMATH
    inline bool Equal( const pbrt::SquareMatrix<4>& m1, const pbrt::SquareMatrix<4>& m2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 4; i++ )
        {
            for ( size_t j = 0; j < 4; j++ )
            {
                auto v1 = m1[ i ][ j ];
                float v2 = m2[ i ][ j ];
                auto delta = v1 - v2;
                if ( std::abs( delta ) > epsilon )
                {
                    return false;
                }
            }
        }
        return true;
    }
#endif

    inline bool Equal( const DirectX::XMFLOAT4X4& m1, const DirectX::XMFLOAT4X4& m2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 4; i++ )
        {
            for ( size_t j = 0; j < 4; j++ )
            {
                auto v1 = m1.m[ i ][ j ];
                float v2 = m2.m[ i ][ j ];
                auto delta = v1 - v2;
                if ( std::abs( delta ) > epsilon )
                {
                    return false;
                }
            }
        }
        return true;
    }

#ifndef PBRT_USES_HCCMATH
    inline bool Equal( const pbrt::SquareMatrix<4>& m1, const Common::Core::Math::SquareMatrix<float, 4>& m2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 4; i++ )
        {
            for ( size_t j = 0; j < 4; j++ )
            {
                auto v1 = m1[ i ][ j ];
                float v2 = m2[ i ][ j ];
                auto delta = v1 - v2;
                if ( std::abs( delta ) > epsilon )
                {
                    return false;
                }
            }
        }
        return true;
    }
    inline bool Equal( const Common::Core::Math::SquareMatrix<float, 4>& m1, const pbrt::SquareMatrix<4>& m2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 4; i++ )
        {
            for ( size_t j = 0; j < 4; j++ )
            {
                auto v1 = m1[ i ][ j ];
                float v2 = m2[ i ][ j ];
                auto delta = v1 - v2;
                if ( std::abs( delta ) > epsilon )
                {
                    return false;
                }
            }
        }
        return true;
    }
#endif

    inline bool Equal( const DirectX::XMFLOAT4X4& m1, const Common::Core::Math::SquareMatrix<float, 4>& m2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 4; i++ )
        {
            for ( size_t j = 0; j < 4; j++ )
            {
                auto v1 = m1.m[ i ][ j ];
                float v2 = m2[ i ][ j ];
                auto delta = v1 - v2;
                if ( std::abs( delta ) > epsilon )
                {
                    return false;
                }
            }
        }
        return true;
    }
    inline bool Equal( const Common::Core::Math::SquareMatrix<float, 4>& m1, const DirectX::XMFLOAT4X4& m2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 4; i++ )
        {
            for ( size_t j = 0; j < 4; j++ )
            {
                auto v1 = m1[ i ][ j ];
                float v2 = m2.m[ i ][ j ];
                auto delta = v1 - v2;
                if ( std::abs( delta ) > epsilon )
                {
                    return false;
                }
            }
        }
        return true;
    }

    inline bool Equal( const DirectX::FXMMATRIX& m1, const Common::Core::Math::SquareMatrix<float, 4>& m2, float epsilon = 0.0001f )
    {
        DirectX::XMFLOAT4X4 m;
        DirectX::XMStoreFloat4x4( &m, m1 );
        return Equal( m, m2 );

    }
    inline bool Equal( const Common::Core::Math::SquareMatrix<float, 4>& m1, const DirectX::FXMMATRIX& m2, float epsilon = 0.0001f )
    {
        DirectX::XMFLOAT4X4 m;
        DirectX::XMStoreFloat4x4( &m, m2 );
        return Equal( m1, m );
    }


    template<Common::Core::Math::TupleType T>
    inline bool Equal( const DirectX::XMFLOAT3& v1, const T& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const T& v1, const DirectX::XMFLOAT3& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            float value2 = ( &v2.x )[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    inline bool Equal( const DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = ( &v2.x )[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

#ifndef PBRT_USES_HCCMATH
    template<Common::Core::Math::TupleType T>
    inline bool Equal( const pbrt::Vector2f& v1, const T& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 2; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const T& v1, const pbrt::Vector2f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 2; i++ )
        {
            auto value1 = v1[ i ];
            float value2 = ( &v2.x )[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const pbrt::Point2f& v1, const T& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 2; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const T& v1, const pbrt::Point2f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 2; i++ )
        {
            auto value1 = v1[ i ];
            float value2 = ( &v2.x )[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }




    template<Common::Core::Math::TupleType T>
    inline bool Equal( const pbrt::Vector3f& v1, const T& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const T& v1, const pbrt::Vector3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            float value2 = ( &v2.x )[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const pbrt::Point3f& v1, const T& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const T& v1, const pbrt::Point3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            float value2 = ( &v2.x )[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const pbrt::Normal3f& v1, const T& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const T& v1, const pbrt::Normal3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            float value2 = ( &v2.x )[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }
#endif
    template<Common::Core::Math::TupleType T>
    inline bool Equal( const pbrto::Vector3f& v1, const T& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const T& v1, const pbrto::Vector3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            float value2 = ( &v2.x )[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const pbrto::Point3f& v1, const T& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const T& v1, const pbrto::Point3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            float value2 = ( &v2.x )[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const pbrto::Normal3f& v1, const T& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Common::Core::Math::TupleType T>
    inline bool Equal( const T& v1, const pbrto::Normal3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            float value2 = ( &v2.x )[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    inline bool Equal( const pbrto::Vector3f& v1, const pbrto::Vector3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    inline bool Equal( const pbrto::Vector3f& v1, const pbrt::Vector3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            float value2 = ( &v2.x )[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }
    inline bool Equal( const pbrt::Vector3f& v1, const pbrto::Vector3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }
    inline bool Equal( const pbrt::Vector3f& v1, const pbrt::Vector3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    inline bool Equal( const pbrto::Point3f& v1, const pbrto::Point3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }
    inline bool Equal( const pbrto::Point3f& v1, const pbrt::Point3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    inline bool Equal( const pbrt::Point3f& v1, const pbrto::Point3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    inline bool Equal( const pbrt::Point3f& v1, const pbrt::Point3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    inline bool Equal( const pbrto::Normal3f& v1, const pbrto::Normal3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    inline bool Equal( const pbrto::Normal3f& v1, const pbrt::Normal3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    inline bool Equal( const pbrt::Normal3f& v1, const pbrto::Normal3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    inline bool Equal( const pbrt::Normal3f& v1, const pbrt::Normal3f& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }


    inline bool Equal( const pbrt::Interval& v1, const pbrt::Interval& v2, float epsilon = 0.0001f )
    {
        auto value1 = v1.LowerBound( );
        auto value2 = v2.LowerBound( );
        auto delta = value1 - value2;
        if ( std::abs( delta ) > epsilon )
        {
                return false;
        }
        value1 = v1.UpperBound( );
        value2 = v2.UpperBound( );
        delta = value1 - value2;
        if ( std::abs( delta ) > epsilon )
        {
            return false;
        }
        
        return true;
    }

    inline bool Equal( const pbrt::Point3fi& v1, const pbrt::Point3fi& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            auto value2 = v2[ i ];
            if ( !Equal( value1, value2, epsilon ) )
            {
                return false;
            }
        }
        return true;
    }
    inline bool Equal( const pbrt::Vector3fi& v1, const pbrt::Vector3fi& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            auto value2 = v2[ i ];
            if ( !Equal( value1, value2, epsilon ) )
            {
                return false;
            }
        }
        return true;
    }

    inline bool Equal( const pbrto::Interval& v1, const pbrto::Interval& v2, float epsilon = 0.0001f )
    {
        auto value1 = v1.LowerBound( );
        auto value2 = v2.LowerBound( );
        auto delta = value1 - value2;
        if ( std::abs( delta ) > epsilon )
        {
            return false;
        }
        value1 = v1.UpperBound( );
        value2 = v2.UpperBound( );
        delta = value1 - value2;
        if ( std::abs( delta ) > epsilon )
        {
            return false;
        }

        return true;
    }

    inline bool Equal( const pbrto::Point3fi& v1, const pbrto::Point3fi& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            auto value2 = v2[ i ];
            if ( !Equal( value1, value2, epsilon ) )
            {
                return false;
            }
        }
        return true;
    }
    inline bool Equal( const pbrto::Vector3fi& v1, const pbrto::Vector3fi& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            auto value2 = v2[ i ];
            if ( !Equal( value1, value2, epsilon ) )
            {
                return false;
            }
        }
        return true;
    }





}


#endif
