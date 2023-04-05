#include "pch.h"
#include <hccfg/hccfg_node.h>
#include <boost/container/small_vector.hpp>
#include "hccfg_pathutil.h"

namespace Harlinn::Common::Config
{
    using namespace Harlinn::Common::Core;

    void Environment::Reload( )
    {
        std::set< std::wstring_view, iLess> keys;
        boost::container::small_vector< EnvironmentValue*, 256> newValues;
        boost::container::small_vector< Reference<EnvironmentValue>, 10> oldValues;
        
        auto start = GetEnvironmentStringsW( );
        auto ptr = start;
        {
            WriterLock lock( mutex_ );
            auto keys = InternalKeys( );

            while ( *ptr )
            {
                auto endPtr = wcschr( ptr, L'=' );
                if ( !endPtr )
                {
                    endPtr = ptr + wcslen( ptr );
                }
                std::wstring_view name( ptr, endPtr );

                auto it = items_.find( name );
                if ( it == items_.end( ) )
                {
                    Reference<EnvironmentValue> value( new EnvironmentValue( const_cast<Environment*>( this ), name ) );
                    newValues.push_back( value.get( ) );
                    std::wstring_view sv = value->Name( );
                    items_.emplace( sv, std::move( value ) );
                    keys.erase( sv );
                }
                auto remainingLength = wcslen( endPtr );
                ptr = endPtr + remainingLength + 1;
            }

            for ( const auto& name : keys )
            {
                auto it = items_.find( name );
                if ( it != items_.end( ) )
                {
                    oldValues.emplace_back( std::move( it->second ) );
                    items_.erase( it );
                }
            }

        }
        FreeEnvironmentStringsW( start );

        {
            ReaderLock lock( mutex_ );
            for ( auto* value : newValues )
            {
                this->DoOnNotification( InsertedNotificationId, value );
            }
        }
        for ( auto& ref : oldValues )
        {
            this->DoOnNotification( DeletedNotificationId, ref.get( ) );
        }


    }

    Reference<EnvironmentValue> Environment::Read( const std::wstring_view& name ) const
    {
        Reference<EnvironmentValue> result = LockedInternalFind( name );
        if ( result )
        {
            return result;
        }
        else
        {
            WriterLock lock( mutex_ );
            result = InternalFind( name );
            if ( result )
            {
                return result;
            }
            constexpr size_t SmallBufferSize = _MAX_PATH + 1;
            boost::container::small_vector<wchar_t, SmallBufferSize> buffer;
            buffer.resize( name.length( ) + 1 );
            auto ptr = buffer.data( );
            wmemcpy( ptr, name.data( ), name.length( ) );
            ptr[name.length( )] = 0;
            auto rc = GetEnvironmentVariableW( ptr, nullptr, 0 );
            if ( !rc )
            {
                auto err = GetLastError( );
                if ( err != ERROR_ENVVAR_NOT_FOUND )
                {
                    ThrowOSError( err );
                }
                return Reference<EnvironmentValue>( );
            }
            result.reset( new EnvironmentValue( const_cast<Environment*>( this ), name ) );
            std::wstring_view sv = result->Name( );
            items_.emplace( sv, result );
            return result;
        }
    }

    bool Environment::Write( const std::wstring_view& name, const std::wstring& value )
    {
        Reference<EnvironmentValue> ref = LockedInternalFind( name );
        if ( ref )
        {
            return ref->SetValue( value );
        }
        else
        {
            WriterLock lock( mutex_ );
            auto it = items_.find( name );
            if ( it == items_.end( ) )
            {
                ref.reset( new EnvironmentValue( const_cast<Environment*>( this ), name ) );
                std::wstring_view sv = ref->Name( );
                items_.emplace( sv, ref );
            }
            else
            {
                ref = it->second;
            }
        }
        return ref->SetValue( value );
    }

    bool Environment::Delete( const std::wstring_view& name )
    {
        Reference<EnvironmentValue> ref = LockedInternalFind( name );
        if ( ref )
        {
            {
                WriterLock lock( mutex_ );
                auto it = items_.find( name );
                if ( it != items_.end( ) )
                {
                    ref = it->second;
                    items_.erase( it );
                }
                else
                {
                    ref.reset( );
                }
            }
            if ( ref )
            {
                this->DoOnNotification( DeletedNotificationId, ref.get( ) );
            }
        }
        constexpr size_t SmallBufferSize = _MAX_PATH + 1;
        boost::container::small_vector<wchar_t, SmallBufferSize> buffer;
        buffer.resize( name.length( ) + 1 );
        auto ptr = buffer.data( );
        wmemcpy( ptr, name.data( ), name.length( ) );
        ptr[name.length( )] = 0;
        auto rc = GetEnvironmentVariableW( ptr, nullptr, 0 );
        if ( !rc )
        {
            auto err = GetLastError( );
            if ( err != ERROR_ENVVAR_NOT_FOUND )
            {
                ThrowOSError( err );
            }
            return false;
        }
        rc = SetEnvironmentVariableW( ptr, nullptr );
        if ( !rc )
        {
            auto err = GetLastError( );
            if ( err != ERROR_ENVVAR_NOT_FOUND )
            {
                ThrowOSError( err );
            }
            return false;
        }
        return true;
    }

    hcc::Reference<Node> Environment::FindByPath( const std::wstring_view& path ) const
    {
        return Internal::FindByPath( this, path );
    }

}
