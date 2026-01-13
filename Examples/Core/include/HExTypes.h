#pragma once
#ifndef __HEXSENSOR_H__
#define __HEXSENSOR_H__
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


#include <HCCGuid.h>
#include <HCCDateTime.h>
#include <HCCString.h>

#include <variant>

namespace Harlinn::Common::Core::Examples
{
    struct SensorPoint
    {
        DateTime Timestamp;
        Int64 Flags = 0;
        Double Value = 0.0;

        template<typename T>
        void Read( T& reader )
        {
            reader.Read( Timestamp );
            reader.Read( Flags );
            reader.Read( Value );
        }

        template<typename T>
        void Write( T& writer ) const
        {
            writer.Write( Timestamp );
            writer.Write( Flags );
            writer.Write( Value );
        }


    };

    struct SensorValue
    {
        Guid Sensor;
        DateTime Timestamp;
        Int64 Flags = 0;
        Double Value = 0.0;

        template<typename T>
        void Read( T& reader )
        {
            reader.Read( Sensor );
            reader.Read( Timestamp );
            reader.Read( Flags );
            reader.Read( Value );
        }

        template<typename T>
        void Write( T& writer ) const
        {
            writer.Write( Sensor );
            writer.Write( Timestamp );
            writer.Write( Flags );
            writer.Write( Value );
        }

    };

    struct Named
    {
        Guid Id;
        std::string Name;
        Named( )
        {
        }

        template<typename T>
        void Read( T& reader )
        {
            reader.Read( Id );
            reader.Read( Name );
        }

        template<typename T>
        void Write( T& writer ) const
        {
            writer.Write( Id );
            writer.Write( Name );
        }

    };

    struct Owned : Named
    {
        using Base = Named;
        Guid Owner;
        Owned( )
        {
        }

        template<typename T>
        void Read( T& reader )
        {
            Base::Read( reader );
            reader.Read( Owner );
        }

        template<typename T>
        void Write( T& writer ) const
        {
            Base::Write( writer );
            writer.Write( Owner );
        }

    };


    enum class CatalogItemType : Int16 
    { 
        Unknown, Catalog, Asset 
    };

    struct CatalogItemBase : Owned 
    { 
        using Base = Owned;
        CatalogItemType Type = CatalogItemType::Unknown; 

        CatalogItemBase( )
        {
        }
        CatalogItemBase( CatalogItemType type )
            : Type( type )
        {
        }

        template<typename T>
        static CatalogItemType ReadType( T& reader )
        {
            auto kind = reader.ReadInt16( );
            return static_cast<CatalogItemType>( kind );
        }

        template<typename T>
        void Write( T& writer ) const
        {
            writer.Write( static_cast<Int16>( Type ) );
            Base::Write( writer );
        }

    };

    struct Catalog : CatalogItemBase
    {
        using Base = CatalogItemBase;
        Catalog( )
            : Base( CatalogItemType::Catalog )
        {
        }

    };

    struct Asset : CatalogItemBase
    {
        using Base = CatalogItemBase;
        Asset( )
            : Base( CatalogItemType::Asset )
        {
        }
    };

    using CatalogItem = std::variant<Catalog, Asset>;

    struct Sensor : Owned
    {
        using Base = Owned;
    };

}

#endif