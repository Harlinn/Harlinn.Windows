#pragma once
#ifndef __SIMPLETESTDATA_H__
#define __SIMPLETESTDATA_H__

#include <HCCString.h>

using namespace Harlinn::Common::Core;

class SimpleTestData
{
    Int64 id_;
    Int64 optimisticLock_;
    std::wstring name_;
    std::wstring description_;
public:
    SimpleTestData()
        : id_(0), optimisticLock_(0)
    { }

    SimpleTestData( Int64 id, Int64 optimisticLock, const std::wstring& name, const std::wstring& description = std::wstring() )
        : id_( id ), optimisticLock_( optimisticLock ), name_( name ), description_( description )
    {
    }

    SimpleTestData( Int64 id, const std::wstring& name, const std::wstring& description = std::wstring( ) )
        : id_( id ), optimisticLock_( 0 ), name_( name ), description_( description )
    {
    }

    constexpr Int64 Id( ) const noexcept { return id_; }
    void SetId( Int64 id ) noexcept { id_ = id; }
    constexpr Int64 OptimisticLock( ) const noexcept { return optimisticLock_; }
    void SetOptimisticLock( Int64 optimisticLock ) noexcept { optimisticLock_ = optimisticLock; }
    constexpr const std::wstring& Name( ) const noexcept { return name_; }
    void SetName( const std::wstring& name ) { name_ = name; }
    constexpr const std::wstring& Description( ) const noexcept { return description_; }
    void SetDescription( const std::wstring& description ) { description_ = description; }

    void Assign( Int64 id, Int64 optimisticLock, const std::wstring& name, const std::wstring& description = std::wstring( ) )
    {
        id_ = id;
        optimisticLock_ = optimisticLock;
        name_ = name;
        description_ = description;
    }
    void Assign( Int64 id, const std::wstring& name, const std::wstring& description = std::wstring( ) )
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

    std::wstring ToString( ) const
    {
        return Format( L"Id: %llu, OptimisticLock: %llu, Name: %s, Description: %s", id_, optimisticLock_, name_.c_str( ), description_.c_str( ) );
    }


};

#endif