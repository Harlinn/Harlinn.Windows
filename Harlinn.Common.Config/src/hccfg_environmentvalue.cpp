#include "pch.h"
#include <hccfg/hccfg_node.h>
#include <HCCEnvironment.h>

namespace Harlinn::Common::Config
{
    using namespace Harlinn::Common::Core;

	std::wstring EnvironmentValue::Value( ) const
	{
		return Core::Environment::EnvironmentVariable( Name( ).c_str( ) );
	}

    bool EnvironmentValue::SetValue( const std::wstring& value ) const
	{
        bool result = false;
        wchar_t buffer[MAX_PATH + 1];
        constexpr DWORD bufferLength = sizeof( buffer ) / sizeof( wchar_t );
        auto rc = GetEnvironmentVariableW( Name().c_str( ), buffer, bufferLength );
        if ( !rc )
        {
            auto err = GetLastError( );
            if ( err != ERROR_ENVVAR_NOT_FOUND )
            {
                ThrowOSError( err );
            }
        }
        if ( rc > MAX_PATH + 1 )
        {
            std::wstring s;
            s.resize( static_cast<size_t>(rc) - 1 );
            rc = GetEnvironmentVariableW( Name().c_str( ), s.data( ), rc );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            if ( value != s )
            {
                rc = SetEnvironmentVariableW( Name( ).c_str( ), value.c_str( ) );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                result = true;
                this->DoOnNotification( ValueChangedNotificationId, const_cast<wchar_t*>( value.c_str( ) ) );
            }
        }
        else
        {
            if ( value != buffer )
            {
                rc = SetEnvironmentVariableW( Name( ).c_str( ), value.c_str( ) );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                result = true;
                this->DoOnNotification( ValueChangedNotificationId, const_cast<wchar_t*>( value.c_str( ) ) );
            }
        }
        return result;
	}

}
