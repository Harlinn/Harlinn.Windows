#pragma once
#ifndef HARLINN_COMMON_CORE_HCCCOMINTERFACES_H_
#define HARLINN_COMMON_CORE_HCCCOMINTERFACES_H_
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

#include <HCCDef.h>

namespace Harlinn::Common::Core::Com::Interfaces
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

#define HCC_COM_IMPLEMENT_INTERFACE_SPECIALIZATION( Itf, BaseItf ) \
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
    }




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

