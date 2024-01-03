#pragma once
#ifndef __SIMPLETESTDATA_H__
#define __SIMPLETESTDATA_H__
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


#include <HCCString.h>

using namespace Harlinn::Common::Core;

class SimpleTestData
{
    Int64 id_;
    Int64 optimisticLock_;
    WideString name_;
    WideString description_;
public:
    SimpleTestData()
        : id_(0), optimisticLock_(0)
    { }

    SimpleTestData( Int64 id, Int64 optimisticLock, const WideString& name, const WideString& description = WideString() )
        : id_( id ), optimisticLock_( optimisticLock ), name_( name ), description_( description )
    {
    }

    SimpleTestData( Int64 id, const WideString& name, const WideString& description = WideString( ) )
        : id_( id ), optimisticLock_( 0 ), name_( name ), description_( description )
    {
    }

    constexpr Int64 Id( ) const noexcept { return id_; }
    void SetId( Int64 id ) noexcept { id_ = id; }
    constexpr Int64 OptimisticLock( ) const noexcept { return optimisticLock_; }
    void SetOptimisticLock( Int64 optimisticLock ) noexcept { optimisticLock_ = optimisticLock; }
    constexpr const WideString& Name( ) const noexcept { return name_; }
    void SetName( const WideString& name ) { name_ = name; }
    constexpr const WideString& Description( ) const noexcept { return description_; }
    void SetDescription( const WideString& description ) { description_ = description; }

    void Assign( Int64 id, Int64 optimisticLock, const WideString& name, const WideString& description = WideString( ) )
    {
        id_ = id;
        optimisticLock_ = optimisticLock;
        name_ = name;
        description_ = description;
    }
    void Assign( Int64 id, const WideString& name, const WideString& description = WideString( ) )
    {
        id_ = id;
        optimisticLock_ = 0;
        name_ = name;
        description_ = description;
    }

    bool Equals( const SimpleTestData& other ) const
    {
        return id_ == other.id_ &&
            optimisticLock_ == other.optimisticLock_ &&
            name_ == other.name_ &&
            description_ == other.description_;
    }
    bool Equals( const std::unique_ptr<SimpleTestData>& other ) const
    {
        return Equals( *other );
    }

    WideString ToString( ) const
    {
        return Format( L"Id: {}, OptimisticLock: {}, Name: {}, Description: {}", id_, optimisticLock_, name_, description_ );
    }


};

#endif