#pragma once
#ifndef __HCCTIMESERIESMATH_H__
#define __HCCTIMESERIESMATH_H__

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

