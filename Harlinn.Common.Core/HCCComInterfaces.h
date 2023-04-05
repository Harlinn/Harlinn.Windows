#pragma once
#ifndef HARLINN_COMMON_CORE_HCCCOMINTERFACES_H_
#define HARLINN_COMMON_CORE_HCCCOMINTERFACES_H_

#include <HCCDef.h>

namespace Harlinn::Common::Core::Com
{
    template<typename ...InterfaceTypes>
    struct Interface : std::false_type
    {

    };

    template<>
    struct Interface<IUnknown> : std::true_type
    {
        using InterfaceType = IUnknown;
        template<typename DerivedInterfaceType>
        static void* QueryInterface( const Guid& interfaceId, const DerivedInterfaceType* impl )
        {
            if ( interfaceId == __uuidof( InterfaceType ) )
            {
                auto* result = static_cast<InterfaceType*>( const_cast<DerivedInterfaceType*>( impl ) );
                return result;
            }
            else
            {
                return nullptr;
            }
        }
    };

#define X( Itf, BaseItf ) \
    template<>  \
    struct Interface<Itf> : Interface<BaseItf>  \
    {  \
        using Base = Interface<BaseItf>; \
        using InterfaceType = Itf;  \
        template<typename DerivedInterfaceType>  \
        static void* QueryInterface( const Guid& interfaceId, const DerivedInterfaceType* impl )  \
        {  \
            if ( interfaceId == __uuidof( InterfaceType ) )  \
            {  \
                auto* result = static_cast<InterfaceType*>( const_cast<DerivedInterfaceType*>( impl ) ); \
                return result; \
            }  \
            else  \
            { \
                return Base::QueryInterface<DerivedInterfaceType>( interfaceId, impl ); \
            }  \
        }  \
    };


#include "HCCComInterfaces.xm"

#undef X


}
#endif

