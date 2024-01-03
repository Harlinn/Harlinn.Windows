#pragma once
#ifndef __HCCTIMESERIESMATH_H__
#define __HCCTIMESERIESMATH_H__
/*
   Copyright 2024 Espen Harlinn

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

#include <HCCDateTime.h>

namespace Harlinn::Common::Core::Timeseries::Math
{
    template<typename DerivedT> 
    class Expression
    {
    public:
        using DerivedType = DerivedT;
    };

    template<typename LT, typename RT>
    class Add : public Expression< Add<LT, RT> >
    {
    public:
        using Base = Expression< Add<LT, RT> >;
    private:
        const LT& lhs_;
        const RT& rhs_;
    public:
        constexpr Add( const LT& lhs, const RT& rhs ) noexcept
            : lhs_( lhs ), rhs_( rhs )
        { }
    };

    template<typename LT, typename RT>
    Add<LT, RT> operator+( const Expression<LT>& u, const Expression<RT>& v )
    {
        return Add<LT, RT>( *static_cast<const E1*>( &u ), *static_cast<const E2*>( &v ) );
    }


}

#endif

