#pragma once
#ifndef HCCREGISTRY_H_
#define HCCREGISTRY_H_

#include "HCCHandle.h"
#include "HCCException.h"
#include "HCCString.h"

namespace Harlinn::Common::Core
{
    enum class RegistryValueType : DWORD
    {
        // No value type
        None = REG_NONE,
        // Unicode nul terminated string
        String = REG_SZ,
        // Unicode nul terminated string (with environment variable references)
        ExpandString = REG_EXPAND_SZ,
        // Free form binary
        Binary = REG_BINARY,
        // 32-bit number
        Int32 = REG_DWORD,
        // 32-bit number (same as Int32)
        LittleEndianInt32 = REG_DWORD_LITTLE_ENDIAN,
        // 32-bit number
        BigEndianInt32 = REG_DWORD_BIG_ENDIAN, 
        // Symbolic Link (unicode)
        Link = REG_LINK, 
        // Multiple Unicode strings
        Strings = REG_MULTI_SZ, 
        // Resource list in the resource map
        ResourceList = REG_RESOURCE_LIST, 
        // Resource list in the hardware description
        FullResourceDescriptor = REG_FULL_RESOURCE_DESCRIPTOR, 
        ResourceRequirementsList = REG_RESOURCE_REQUIREMENTS_LIST,
        // 64-bit number
        Int64 = REG_QWORD, 
        // 64-bit number (same as Int64)
        LittleEndianInt64 = REG_QWORD_LITTLE_ENDIAN 
    };

    


    class RegistryHandle : public Handle<RegistryHandle, HKEY>
    {
    public:
        using Base = Handle<RegistryHandle, HKEY>;
    protected:

    public:
        RegistryHandle( )
            : Base( )
        {
        }

        RegistryHandle( void* initialHandleValue, bool ownsValue = true )
            : Base( static_cast< HKEY >( initialHandleValue ), ownsValue )
        {

        }


        static constexpr HKEY InvalidHandleValue( ) noexcept
        {
            return static_cast< HKEY >( INVALID_HANDLE_VALUE );
        }

        constexpr bool IsValid( ) const noexcept
        {
            return value_ != static_cast< HandleType >( 0 ) &&
                value_ != static_cast< HandleType >( INVALID_HANDLE_VALUE );
        }


        void Close( ) noexcept
        {
            if ( IsValid( ) )
            {
                auto handleValue = value_;
                value_ = this->InvalidHandleValue( );
                if ( OwnsHandle( ) )
                {
                    RegCloseKey( ( HKEY )handleValue );
                }
            }
        }


        static RegistryHandle ClassesRoot( )
        {
            RegistryHandle result( ( void* )HKEY_CLASSES_ROOT, false );
            return result;
        }

        static RegistryHandle CurrentUser( )
        {
            RegistryHandle result( ( void* )HKEY_CURRENT_USER, false );
            return result;
        }

        static RegistryHandle LocalMachine( )
        {
            RegistryHandle result( ( void* )HKEY_LOCAL_MACHINE, false );
            return result;
        }

        static RegistryHandle Users( )
        {
            RegistryHandle result( ( void* )HKEY_USERS, false );
            return result;
        }

        static RegistryHandle PerformanceData( )
        {
            RegistryHandle result( ( void* )HKEY_PERFORMANCE_DATA, false );
            return result;
        }

        static RegistryHandle PerformanceText( )
        {
            RegistryHandle result( ( void* )HKEY_PERFORMANCE_TEXT, false );
            return result;
        }

        static RegistryHandle PerformanceNlsText( )
        {
            RegistryHandle result( ( void* )HKEY_PERFORMANCE_NLSTEXT, false );
            return result;
        }

        static RegistryHandle CurrentConfig( )
        {
            RegistryHandle result( ( void* )HKEY_CURRENT_CONFIG, false );
            return result;
        }

        static RegistryHandle DynamicData( )
        {
            RegistryHandle result( ( void* )HKEY_DYN_DATA, false );
            return result;
        }

        static RegistryHandle CurrentUserLocalSettings( )
        {
            RegistryHandle result( ( void* )HKEY_CURRENT_USER_LOCAL_SETTINGS, false );
            return result;
        }


        void OverridePredefinedKey( const RegistryHandle& newHandle ) const
        {
            auto self = ( HKEY )Value( );
            if ( newHandle )
            {
                auto newHandleValue = ( HKEY )newHandle.Value( );
                auto result = RegOverridePredefKey( self, newHandleValue );
                if ( result != ERROR_SUCCESS )
                {
                    ThrowOSError( result );
                }
            }
            else
            {
                auto result = RegOverridePredefKey( self, 0 );
                if ( result != ERROR_SUCCESS )
                {
                    ThrowOSError( result );
                }
            }
        }

        void ResetPredefinedKey( ) const
        {
            auto self = ( HKEY )Value( );
            auto result = RegOverridePredefKey( self, 0 );
            if ( result != ERROR_SUCCESS )
            {
                ThrowOSError( result );
            }
        }

        static RegistryHandle OpenUserClassesRoot( HANDLE hToken, REGSAM desiredAccess )
        {
            HKEY hKey = 0;
            auto rc = RegOpenUserClassesRoot( hToken, 0, desiredAccess, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle OpenCurrentUser( REGSAM desiredAccess )
        {
            HKEY hKey = 0;
            auto rc = RegOpenCurrentUser( desiredAccess, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static void DisablePredefinedCache( )
        {
            auto rc = RegDisablePredefinedCache( );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        static void DisablePredefinedCacheEx( )
        {
            auto rc = RegDisablePredefinedCacheEx( );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        static RegistryHandle ConnectRegistry( const RegistryHandle& predefinedHandle )
        {
            HKEY hKey = 0;
            auto predefinedHandleValue = ( HKEY )predefinedHandle.Value( );
            auto rc = RegConnectRegistryW( nullptr, predefinedHandleValue, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const AnsiString& theMachineName, const RegistryHandle& predefinedHandle )
        {
            HKEY hKey = 0;
            auto predefinedHandleValue = ( HKEY )predefinedHandle.Value( );
            auto rc = RegConnectRegistryA( theMachineName.data( ), predefinedHandleValue, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const WideString& theMachineName, const RegistryHandle& thePredefinedHandle )
        {
            HKEY hKey = 0;
            auto predefinedHandle = ( HKEY )thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryW( theMachineName.data( ), predefinedHandle, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const char* theMachineName, const RegistryHandle& thePredefinedHandle )
        {
            HKEY hKey = 0;
            auto predefinedHandle = ( HKEY )thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryA( theMachineName, predefinedHandle, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const wchar_t* theMachineName, const RegistryHandle& thePredefinedHandle )
        {
            HKEY hKey = 0;
            auto predefinedHandle = ( HKEY )thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryW( theMachineName, predefinedHandle, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }


        static RegistryHandle ConnectRegistry( const RegistryHandle& thePredefinedHandle, ULONG theFlags )
        {
            HKEY hKey = 0;
            auto predefinedHandle = ( HKEY )thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryExW( nullptr, predefinedHandle, theFlags, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const AnsiString& theMachineName, const RegistryHandle& thePredefinedHandle, ULONG theFlags )
        {
            HKEY hKey = 0;
            auto predefinedHandle = ( HKEY )thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryExA( theMachineName.data( ), predefinedHandle, theFlags, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const WideString& theMachineName, const RegistryHandle& thePredefinedHandle, ULONG theFlags )
        {
            HKEY hKey = 0;
            auto predefinedHandle = ( HKEY )thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryExW( theMachineName.data( ), predefinedHandle, theFlags, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const char* theMachineName, const RegistryHandle& thePredefinedHandle, ULONG theFlags )
        {
            HKEY hKey = 0;
            auto predefinedHandle = ( HKEY )thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryExA( theMachineName, predefinedHandle, theFlags, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const wchar_t* theMachineName, const RegistryHandle& thePredefinedHandle, ULONG theFlags )
        {
            HKEY hKey = 0;
            auto predefinedHandle = ( HKEY )thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryExW( theMachineName, predefinedHandle, theFlags, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const char* theSubKey ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            auto rc = RegCreateKeyA( self, theSubKey, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const wchar_t* theSubKey ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            auto rc = RegCreateKeyW( self, theSubKey, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const AnsiString& theSubKey ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            auto rc = RegCreateKeyA( self, theSubKey.data( ), &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const WideString& theSubKey ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            auto rc = RegCreateKeyW( self, theSubKey.data( ), &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const AnsiString& theSubKey, const AnsiString& theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyExA( self, theSubKey.data( ), 0, const_cast< char* >( theClass.data( ) ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const char* theSubKey, const char* theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyExA( self, theSubKey, 0, const_cast< char* >( theClass ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }


        RegistryHandle CreateKey( const WideString& theSubKey, const WideString& theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyExW( self, theSubKey.data( ), 0, const_cast< wchar_t* >( theClass.data( ) ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const wchar_t* theSubKey, const wchar_t* theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyExW( self, theSubKey, 0, const_cast< wchar_t* >( theClass ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const AnsiString& theSubKey, const AnsiString& theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated, HANDLE hTransaction ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyTransactedA( self, theSubKey.data( ), 0, const_cast< char* >( theClass.data( ) ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const char* theSubKey, const char* theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated, HANDLE hTransaction ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyTransactedA( self, theSubKey, 0, const_cast< char* >( theClass ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }


        RegistryHandle CreateKey( const WideString& theSubKey, const WideString& theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated, HANDLE hTransaction ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyTransactedW( self, theSubKey.data( ), 0, const_cast< wchar_t* >( theClass.data( ) ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const wchar_t* theSubKey, const wchar_t* theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated, HANDLE hTransaction ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyTransactedW( self, theSubKey, 0, const_cast< wchar_t* >( theClass ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }


        void DeleteKey( const AnsiString& theSubKey ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyA( self, theSubKey.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKey( const char* theSubKey ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyA( self, theSubKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }


        void DeleteKey( const WideString& theSubKey ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            auto rc = RegDeleteKeyW( self, theSubKey.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKey( const wchar_t* theSubKey ) const
        {
            auto self = ( HKEY )Value( );
            HKEY hKey = 0;
            auto rc = RegDeleteKeyW( self, theSubKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKey( const AnsiString& theSubKey, REGSAM desiredRegistryView ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyExA( self, theSubKey.data( ), desiredRegistryView, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKey( const char* theSubKey, REGSAM desiredRegistryView ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyExA( self, theSubKey, desiredRegistryView, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKey( const WideString& theSubKey, REGSAM desiredRegistryView ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyExW( self, theSubKey.data( ), desiredRegistryView, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKey( const wchar_t* theSubKey, REGSAM desiredRegistryView ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyExW( self, theSubKey, desiredRegistryView, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKey( const AnsiString& theSubKey, REGSAM desiredRegistryView, HANDLE hTransaction ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyTransactedA( self, theSubKey.data( ), desiredRegistryView, 0, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKey( const char* theSubKey, REGSAM desiredRegistryView, HANDLE hTransaction ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyTransactedA( self, theSubKey, desiredRegistryView, 0, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKey( const WideString& theSubKey, REGSAM desiredRegistryView, HANDLE hTransaction ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyTransactedW( self, theSubKey.data( ), desiredRegistryView, 0, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKey( const wchar_t* theSubKey, REGSAM desiredRegistryView, HANDLE hTransaction ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyTransactedW( self, theSubKey, desiredRegistryView, 0, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKeyValue( ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyValueW( self, nullptr, nullptr );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKeyValue( const AnsiString& theValueName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyValueA( self, nullptr, theValueName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKeyValue( const char* theValueName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyValueA( self, nullptr, theValueName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKeyValue( const AnsiString& theSubKey, const AnsiString& theValueName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyValueA( self, theSubKey.data( ), theValueName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKeyValue( const char* theSubKey, const char* theValueName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyValueA( self, theSubKey, theValueName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKeyValue( const WideString& theValueName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyValueW( self, nullptr, theValueName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKeyValue( const wchar_t* theValueName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyValueW( self, nullptr, theValueName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKeyValue( const WideString& theSubKey, const WideString& theValueName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyValueW( self, theSubKey.data( ), theValueName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteKeyValue( const wchar_t* theSubKey, const wchar_t* theValueName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteKeyValueW( self, theSubKey, theValueName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DisableReflectionKey( ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDisableReflectionKey( self );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void EnableReflectionKey( ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegEnableReflectionKey( self );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        bool QueryReflectionKey( ) const
        {
            auto self = ( HKEY )Value( );
            BOOL isReflectionDisabled = FALSE;
            auto rc = RegQueryReflectionKey( self, &isReflectionDisabled );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return isReflectionDisabled != FALSE;
        }

        bool IsReflectionDisabled( ) const
        {
            return QueryReflectionKey( );
        }

        bool IsReflectionEnabled( ) const
        {
            return QueryReflectionKey( ) == false;
        }

        void DeleteValue( ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteValueW( self, nullptr );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteValue( const AnsiString& theValueName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteValueA( self, theValueName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteValue( const char* theValueName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteValueA( self, theValueName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }


        void DeleteValue( const WideString& theValueName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteValueW( self, theValueName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void DeleteValue( const wchar_t* theValueName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegDeleteValueW( self, theValueName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }


        long EnumKey( DWORD theIndex, char* theNameBuffer, DWORD& theSizeOfTheNameBuffer, char* theClassNameBuffer, DWORD& theSizeOfTheClassNameBuffer, FILETIME& theLastWriteTime ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegEnumKeyExA( self, theIndex, theNameBuffer, &theSizeOfTheNameBuffer, nullptr, theClassNameBuffer, &theSizeOfTheClassNameBuffer, &theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long EnumKey( DWORD theIndex, char* theNameBuffer, DWORD& theSizeOfTheNameBuffer, FILETIME& theLastWriteTime ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegEnumKeyExA( self, theIndex, theNameBuffer, &theSizeOfTheNameBuffer, nullptr, nullptr, 0, &theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
            {
                ThrowOSError( rc );
            }
            return rc;
        }


        long EnumKey( DWORD theIndex, wchar_t* theNameBuffer, DWORD& theSizeOfTheNameBuffer, wchar_t* theClassNameBuffer, DWORD& theSizeOfTheClassNameBuffer, FILETIME& theLastWriteTime ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegEnumKeyExW( self, theIndex, theNameBuffer, &theSizeOfTheNameBuffer, nullptr, theClassNameBuffer, &theSizeOfTheClassNameBuffer, &theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long EnumKey( DWORD theIndex, wchar_t* theNameBuffer, DWORD& theSizeOfTheNameBuffer, FILETIME& theLastWriteTime ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegEnumKeyExW( self, theIndex, theNameBuffer, &theSizeOfTheNameBuffer, nullptr, nullptr, 0, &theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
            {
                ThrowOSError( rc );
            }
            return rc;
        }


        long EnumKeyNames( std::vector<WideString>& result ) const
        {
            long rc = ERROR_SUCCESS;
            DWORD index = 0;
            wchar_t nameBuffer[ 256 ] = { 0, };
            result.clear( );
            auto self = ( HKEY )Value( );
            do
            {
                DWORD sizeOfTheNameBuffer = 256;
                rc = RegEnumKeyExW( self, index, nameBuffer, &sizeOfTheNameBuffer, nullptr, nullptr, 0, nullptr );
                if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
                {
                    ThrowOSError( rc );
                }
                else if ( rc == ERROR_SUCCESS )
                {
                    WideString name( nameBuffer, static_cast< size_t >( sizeOfTheNameBuffer ) );
                    result.push_back( name );
                }
                index++;
            } while ( rc == ERROR_SUCCESS );
            return rc;
        }


        long EnumKeyNames( std::vector<AnsiString>& result ) const
        {
            long rc = ERROR_SUCCESS;
            DWORD index = 0;
            char nameBuffer[ 256 ] = { 0, };
            result.clear( );
            auto self = ( HKEY )Value( );
            do
            {
                DWORD sizeOfTheNameBuffer = 256;
                rc = RegEnumKeyExA( self, index, nameBuffer, &sizeOfTheNameBuffer, nullptr, nullptr, 0, nullptr );
                if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
                {
                    ThrowOSError( rc );
                }
                else if ( rc == ERROR_SUCCESS )
                {
                    AnsiString name( nameBuffer, static_cast< size_t >( sizeOfTheNameBuffer ) );
                    result.push_back( name );
                }
                index++;
            } while ( rc == ERROR_SUCCESS );
            return rc;
        }


        long EnumValue( DWORD theIndex, char* theNameBuffer, DWORD& theSizeOfTheNameBuffer, DWORD& theType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegEnumValueA( self, theIndex, theNameBuffer, &theSizeOfTheNameBuffer, nullptr, &theType, ( LPBYTE )theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long EnumValue( DWORD theIndex, wchar_t* theNameBuffer, DWORD& theSizeOfTheNameBuffer, DWORD& theType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegEnumValueW( self, theIndex, theNameBuffer, &theSizeOfTheNameBuffer, nullptr, &theType, ( LPBYTE )theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        RegistryHandle& FlushKey( )
        {
            auto self = ( HKEY )Value( );
            auto rc = RegFlushKey( self );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        long GetKeySecurity( SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR theSecurityDescriptor, DWORD& theSizeOfTheSecurityDescriptor ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegGetKeySecurity( self, SecurityInformation, theSecurityDescriptor, &theSizeOfTheSecurityDescriptor );
            if ( rc != ERROR_SUCCESS && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        void LoadKey( const AnsiString& theSubKey, const AnsiString& theFilename ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegLoadKeyA( self, theSubKey.data( ), theFilename.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void LoadKey( const char* theSubKey, const char* theFilename ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegLoadKeyA( self, theSubKey, theFilename );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void LoadKey( const AnsiString& theFilename ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegLoadKeyA( self, nullptr, theFilename.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void LoadKey( const char* theFilename ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegLoadKeyA( self, nullptr, theFilename );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void LoadKey( const WideString& theSubKey, const WideString& theFilename ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegLoadKeyW( self, theSubKey.data( ), theFilename.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void LoadKey( const wchar_t* theSubKey, const wchar_t* theFilename ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegLoadKeyW( self, theSubKey, theFilename );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void LoadKey( const WideString& theFilename ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegLoadKeyW( self, nullptr, theFilename.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void LoadKey( const wchar_t* theFilename ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegLoadKeyW( self, nullptr, theFilename );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        static RegistryHandle LoadAppKey( const AnsiString& theFilename, REGSAM desiredAccess, DWORD theOptions )
        {
            HKEY hKey = 0;
            auto rc = RegLoadAppKeyA( theFilename.data( ), &hKey, desiredAccess, theOptions, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle LoadAppKey( const char* theFilename, REGSAM desiredAccess, DWORD theOptions )
        {
            HKEY hKey = 0;
            auto rc = RegLoadAppKeyA( theFilename, &hKey, desiredAccess, theOptions, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle LoadAppKey( const WideString& theFilename, REGSAM desiredAccess, DWORD theOptions )
        {
            HKEY hKey = 0;
            auto rc = RegLoadAppKeyW( theFilename.data( ), &hKey, desiredAccess, theOptions, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle LoadAppKey( const wchar_t* theFilename, REGSAM desiredAccess, DWORD theOptions )
        {
            HKEY hKey = 0;
            auto rc = RegLoadAppKeyW( theFilename, &hKey, desiredAccess, theOptions, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        void NotifyChangeKeyValue( bool watchSubtree, DWORD dwNotifyFilter, HANDLE hEvent, bool asynchronous ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegNotifyChangeKeyValue( self, watchSubtree ? TRUE : FALSE, dwNotifyFilter, hEvent, asynchronous ? TRUE : FALSE );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        bool KeyExists( const AnsiString& theSubKey ) const
        {
            if ( theSubKey.length( ) )
            {
                HKEY hKey = 0;
                auto self = ( HKEY )Value( );
                auto rc = RegOpenKeyExA( self, theSubKey.data( ), 0, KEY_READ, &hKey );
                if ( rc == ERROR_SUCCESS )
                {
                    RegCloseKey( hKey );
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                throw ArgumentException( L"Invalid key name", L"theSubKey" );
            }
        }

        bool KeyExists( const WideString& theSubKey ) const
        {
            if ( theSubKey.length( ) )
            {
                HKEY hKey = 0;
                auto self = ( HKEY )Value( );
                auto rc = RegOpenKeyExW( self, theSubKey.data( ), 0, KEY_READ, &hKey );
                if ( rc == ERROR_SUCCESS )
                {
                    RegCloseKey( hKey );
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                throw ArgumentException( L"Invalid key name", L"theSubKey" );
            }
        }


        RegistryHandle OpenKey( const AnsiString& theSubKey, REGSAM desiredAccess ) const
        {
            HKEY hKey = 0;
            auto self = Value( );
            if ( self == HKEY_CLASSES_ROOT && theSubKey.data( ) == nullptr )
            {
                return RegistryHandle( HKEY_CLASSES_ROOT, false );
            }
            auto rc = RegOpenKeyExA( self, theSubKey.data( ), 0, desiredAccess, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle OpenKey( const char* theSubKey, REGSAM desiredAccess ) const
        {
            HKEY hKey = 0;
            auto self = ( HKEY )Value( );
            if ( self == HKEY_CLASSES_ROOT && theSubKey == nullptr )
            {
                return RegistryHandle( HKEY_CLASSES_ROOT, false );
            }
            auto rc = RegOpenKeyExA( self, theSubKey, 0, desiredAccess, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }


        RegistryHandle OpenKey( const WideString& theSubKey, REGSAM desiredAccess ) const
        {
            HKEY hKey = 0;
            auto self = ( HKEY )Value( );
            if ( self == HKEY_CLASSES_ROOT && theSubKey.data( ) == nullptr )
            {
                return RegistryHandle( HKEY_CLASSES_ROOT, false );
            }
            auto rc = RegOpenKeyExW( self, theSubKey.data( ), 0, desiredAccess, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle OpenKey( const wchar_t* theSubKey, REGSAM desiredAccess ) const
        {
            HKEY hKey = 0;
            auto self = ( HKEY )Value( );
            if ( self == HKEY_CLASSES_ROOT && theSubKey == nullptr )
            {
                return RegistryHandle( HKEY_CLASSES_ROOT, false );
            }
            auto rc = RegOpenKeyExW( self, theSubKey, 0, desiredAccess, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle OpenKey( const AnsiString& theSubKey, REGSAM desiredAccess, HANDLE hTransaction ) const
        {
            HKEY hKey = 0;
            auto self = ( HKEY )Value( );
            auto rc = RegOpenKeyTransactedA( self, theSubKey.data( ), 0, desiredAccess, &hKey, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle OpenKey( const char* theSubKey, REGSAM desiredAccess, HANDLE hTransaction ) const
        {
            HKEY hKey = 0;
            auto self = ( HKEY )Value( );
            auto rc = RegOpenKeyTransactedA( self, theSubKey, 0, desiredAccess, &hKey, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }


        RegistryHandle OpenKey( const WideString& theSubKey, REGSAM desiredAccess, HANDLE hTransaction ) const
        {
            HKEY hKey = 0;
            auto self = ( HKEY )Value( );
            auto rc = RegOpenKeyTransactedW( self, theSubKey.data( ), 0, desiredAccess, &hKey, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle OpenKey( const wchar_t* theSubKey, REGSAM desiredAccess, HANDLE hTransaction ) const
        {
            HKEY hKey = 0;
            auto self = ( HKEY )Value( );
            auto rc = RegOpenKeyTransactedW( self, theSubKey, 0, desiredAccess, &hKey, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        long QueryInfoKey( char* theClassNameBuffer, DWORD& theSizeOfTheClassNameBuffer,
            DWORD& theNumberOfSubKeys, DWORD& theMaxSubKeyLen, DWORD& theMaxClassLen, DWORD& theNumberOfValues,
            DWORD& theMaxValueNameLen, DWORD& theMaxValueLen, DWORD& theSecurityDescriptorSize, FILETIME& theLastWriteTime ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegQueryInfoKeyA( self, theClassNameBuffer, &theSizeOfTheClassNameBuffer, nullptr,
                &theNumberOfSubKeys, &theMaxSubKeyLen, &theMaxClassLen, &theNumberOfValues,
                &theMaxValueNameLen, &theMaxValueLen, &theSecurityDescriptorSize, &theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryInfoKey( char* theClassNameBuffer, DWORD* theSizeOfTheClassNameBuffer,
            DWORD* theNumberOfSubKeys, DWORD* theMaxSubKeyLen, DWORD* theMaxClassLen, DWORD* theNumberOfValues,
            DWORD* theMaxValueNameLen, DWORD* theMaxValueLen, DWORD* theSecurityDescriptorSize, FILETIME* theLastWriteTime ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegQueryInfoKeyA( self, theClassNameBuffer, theSizeOfTheClassNameBuffer, nullptr,
                theNumberOfSubKeys, theMaxSubKeyLen, theMaxClassLen, theNumberOfValues,
                theMaxValueNameLen, theMaxValueLen, theSecurityDescriptorSize, theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA )
            {
                ThrowOSError( rc );
            }
            return rc;
        }



        long QueryInfoKey( wchar_t* theClassNameBuffer, DWORD& theSizeOfTheClassNameBuffer,
            DWORD& theNumberOfSubKeys, DWORD& theMaxSubKeyLen, DWORD& theMaxClassLen, DWORD& theNumberOfValues,
            DWORD& theMaxValueNameLen, DWORD& theMaxValueLen, DWORD& theSecurityDescriptorSize, FILETIME& theLastWriteTime ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegQueryInfoKeyW( self, theClassNameBuffer, &theSizeOfTheClassNameBuffer, nullptr,
                &theNumberOfSubKeys, &theMaxSubKeyLen, &theMaxClassLen, &theNumberOfValues,
                &theMaxValueNameLen, &theMaxValueLen, &theSecurityDescriptorSize, &theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryInfoKey( wchar_t* theClassNameBuffer, DWORD* theSizeOfTheClassNameBuffer,
            DWORD* theNumberOfSubKeys, DWORD* theMaxSubKeyLen, DWORD* theMaxClassLen, DWORD* theNumberOfValues,
            DWORD* theMaxValueNameLen, DWORD* theMaxValueLen, DWORD* theSecurityDescriptorSize, FILETIME* theLastWriteTime ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegQueryInfoKeyW( self, theClassNameBuffer, theSizeOfTheClassNameBuffer, nullptr,
                theNumberOfSubKeys, theMaxSubKeyLen, theMaxClassLen, theNumberOfValues,
                theMaxValueNameLen, theMaxValueLen, theSecurityDescriptorSize, theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryMultipleValues( PVALENTA theValueList, DWORD theNumberOfEntriesInTheValueList, char* theBuffer, DWORD& theBufferSize ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegQueryMultipleValuesA( self, theValueList, theNumberOfEntriesInTheValueList, theBuffer, &theBufferSize );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryMultipleValues( PVALENTW theValueList, DWORD theNumberOfEntriesInTheValueList, wchar_t* theBuffer, DWORD& theBufferSize ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegQueryMultipleValuesW( self, theValueList, theNumberOfEntriesInTheValueList, theBuffer, &theBufferSize );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryValue( const AnsiString& theValueName, DWORD& theValueType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegQueryValueExA( self, theValueName.data( ), nullptr, &theValueType, ( LPBYTE )theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryValue( const char* theValueName, DWORD& theValueType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegQueryValueExA( self, theValueName, nullptr, &theValueType, ( LPBYTE )theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryValue( const WideString& theValueName, DWORD& theValueType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegQueryValueExW( self, theValueName.data( ), nullptr, &theValueType, ( LPBYTE )theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryValue( const wchar_t* theValueName, DWORD& theValueType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegQueryValueExW( self, theValueName, nullptr, &theValueType, ( LPBYTE )theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryValue( DWORD& theValueType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegQueryValueExW( self, nullptr, nullptr, &theValueType, ( LPBYTE )theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }


    private:
        WideString ToString( const std::vector<char>& theData ) const
        {
            WideString result;
            size_t length = theData.size( ) / 2;
            if ( length )
            {
                auto data = ( const wchar_t* )theData.data( );
                while ( ( length ) && ( data[ length - 1 ] == 0 ) )
                {
                    length--;
                }
                if ( length )
                {
                    result = WideString( data, length );
                }
            }
            return result;
        }


        bool ToBoolean( DWORD theValueType, const std::vector<char>& theData ) const
        {
            bool result = false;
            switch ( theValueType )
            {
                case REG_DWORD:
                case REG_QWORD:
                case REG_BINARY:
                {
                    switch ( theData.size( ) )
                    {
                        case 1:
                        {
                            auto data = ( const char* )theData.data( );
                            result = *data ? true : false;
                        }
                        break;
                        case 2:
                        {
                            auto data = ( const short* )theData.data( );
                            result = *data ? true : false;
                        }
                        break;
                        case 4:
                        {
                            auto data = ( const int* )theData.data( );
                            result = *data ? true : false;
                        }
                        break;
                        case 8:
                        {
                            auto data = ( const long long* )theData.data( );
                            result = *data ? true : false;
                        }
                        break;
                    }
                }
                break;
                case REG_EXPAND_SZ:
                case REG_MULTI_SZ:
                case REG_SZ:
                {
                    auto s = ToString( theData );
                    result = Common::Core::ToBoolean( s );
                }
                break;
            }
            return result;
        }

        int ToInt32( DWORD theValueType, const std::vector<char>& theData ) const
        {
            int result = 0;
            switch ( theValueType )
            {
                case REG_DWORD:
                case REG_QWORD:
                case REG_BINARY:
                {
                    switch ( theData.size( ) )
                    {
                        case 1:
                        {
                            auto data = ( const char* )theData.data( );
                            result = static_cast< int >( *data );
                        }
                        break;
                        case 2:
                        {
                            auto data = ( const short* )theData.data( );
                            result = static_cast< int >( *data );
                        }
                        break;
                        case 4:
                        {
                            auto data = ( const int* )theData.data( );
                            result = static_cast< int >( *data );
                        }
                        break;
                        case 8:
                        {
                            auto data = ( const long long* )theData.data( );
                            result = static_cast< int >( *data );
                        }
                        break;
                    }
                }
                break;
                case REG_EXPAND_SZ:
                case REG_MULTI_SZ:
                case REG_SZ:
                {
                    auto s = ToString( theData );
                    result = Common::Core::ToInt32( s );
                }
                break;
            }
            return result;
        }

        unsigned int ToUInt32( DWORD theValueType, const std::vector<char>& theData ) const
        {
            unsigned int result = 0;
            switch ( theValueType )
            {
                case REG_DWORD:
                case REG_QWORD:
                case REG_BINARY:
                {
                    switch ( theData.size( ) )
                    {
                        case 1:
                        {
                            auto data = ( const unsigned char* )theData.data( );
                            result = static_cast< unsigned int >( *data );
                        }
                        break;
                        case 2:
                        {
                            auto data = ( const unsigned short* )theData.data( );
                            result = static_cast< unsigned int >( *data );
                        }
                        break;
                        case 4:
                        {
                            auto data = ( const unsigned int* )theData.data( );
                            result = static_cast< unsigned int >( *data );
                        }
                        break;
                        case 8:
                        {
                            auto data = ( const unsigned long long* )theData.data( );
                            result = static_cast< unsigned int >( *data );
                        }
                        break;
                    }
                }
                break;
                case REG_EXPAND_SZ:
                case REG_MULTI_SZ:
                case REG_SZ:
                {
                    auto s = ToString( theData );
                    result = Common::Core::ToUInt32( s );
                }
                break;
            }
            return result;
        }

        long long ToInt64( DWORD theValueType, const std::vector<char>& theData ) const
        {
            long long result = 0;
            switch ( theValueType )
            {
                case REG_DWORD:
                case REG_QWORD:
                case REG_BINARY:
                {
                    switch ( theData.size( ) )
                    {
                        case 1:
                        {
                            auto data = ( const char* )theData.data( );
                            result = static_cast< long long >( *data );
                        }
                        break;
                        case 2:
                        {
                            auto data = ( const short* )theData.data( );
                            result = static_cast< long long >( *data );
                        }
                        break;
                        case 4:
                        {
                            auto data = ( const int* )theData.data( );
                            result = static_cast< long long >( *data );
                        }
                        break;
                        case 8:
                        {
                            auto data = ( const long long* )theData.data( );
                            result = static_cast< long long >( *data );
                        }
                        break;
                    }
                }
                break;
                case REG_EXPAND_SZ:
                case REG_MULTI_SZ:
                case REG_SZ:
                {
                    auto s = ToString( theData );
                    result = Common::Core::ToInt64( s );
                }
                break;
            }
            return result;
        }

        unsigned long long ToUInt64( DWORD theValueType, const std::vector<char>& theData ) const
        {
            unsigned long long result = 0;
            switch ( theValueType )
            {
                case REG_DWORD:
                case REG_QWORD:
                case REG_BINARY:
                {
                    switch ( theData.size( ) )
                    {
                        case 1:
                        {
                            auto data = ( const unsigned char* )theData.data( );
                            result = static_cast< unsigned long long >( *data );
                        }
                        break;
                        case 2:
                        {
                            auto data = ( const unsigned short* )theData.data( );
                            result = static_cast< unsigned long long >( *data );
                        }
                        break;
                        case 4:
                        {
                            auto data = ( const unsigned int* )theData.data( );
                            result = static_cast< unsigned long long >( *data );
                        }
                        break;
                        case 8:
                        {
                            auto data = ( const unsigned long long* )theData.data( );
                            result = static_cast< unsigned long long >( *data );
                        }
                        break;
                    }
                }
                break;
                case REG_EXPAND_SZ:
                case REG_MULTI_SZ:
                case REG_SZ:
                {
                    auto s = ToString( theData );
                    result = Common::Core::ToUInt64( s );
                }
                break;
            }
            return result;
        }

        char ToSByte( DWORD theValueType, const std::vector<char>& theData ) const
        {
            return static_cast< char >( ToInt32( theValueType, theData ) );
        }

        unsigned char ToByte( DWORD theValueType, const std::vector<char>& theData ) const
        {
            return static_cast< unsigned char >( ToUInt32( theValueType, theData ) );
        }

        short ToInt16( DWORD theValueType, const std::vector<char>& theData ) const
        {
            return static_cast< char >( ToInt32( theValueType, theData ) );
        }

        unsigned short ToUInt16( DWORD theValueType, const std::vector<char>& theData ) const
        {
            return static_cast< unsigned char >( ToUInt32( theValueType, theData ) );
        }

        double ToDouble( DWORD theValueType, const std::vector<char>& theData ) const
        {
            auto v = ToUInt64( theValueType, theData );
            double result = *( double* )&v;
            return result;
        }

        float ToSingle( DWORD theValueType, const std::vector<char>& theData ) const
        {
            auto v = ToUInt32( theValueType, theData );
            float result = *( float* )&v;
            return result;
        }

        WideString ToString( DWORD theValueType, const std::vector<char>& theData ) const
        {
            WideString result;
            switch ( theValueType )
            {
                case REG_EXPAND_SZ:
                case REG_MULTI_SZ:
                case REG_SZ:
                case REG_BINARY:
                {
                    size_t length = theData.size( ) / 2;
                    if ( length )
                    {
                        auto data = ( const wchar_t* )theData.data( );
                        while ( ( length ) && ( data[ length - 1 ] == 0 ) )
                        {
                            length--;
                        }
                        if ( length )
                        {
                            result = WideString( data, length );
                        }
                    }
                }
                break;
                case REG_DWORD:
                {
                    size_t length = theData.size( );
                    if ( length == sizeof( int ) )
                    {
                        auto data = ( const int* )theData.data( );
#ifdef HCC_WITH_BASIC_STRING
                        result = ToWideString( *data );
#else
                        result = std::to_wstring( *data );
#endif
                    }
                }

                break;
                case REG_QWORD:
                {
                    size_t length = theData.size( );
                    if ( length == sizeof( long long ) )
                    {
                        auto data = ( const long long* )theData.data( );
#ifdef HCC_WITH_BASIC_STRING
                        result = ToWideString( *data );
#else
                        result = std::to_wstring( *data );
#endif
                    }
                }
                break;

            }
            return result;
        }

    public:
        bool ReadValue( const wchar_t* theValueName, DWORD& theValueType, std::vector<char>& theData ) const
        {
            DWORD sizeOfTheDataBuffer = 128 * sizeof( WCHAR );
            theData.clear( );
            theData.resize( sizeOfTheDataBuffer );
            auto self = ( HKEY )Value( );
            auto rc = RegQueryValueExW( self, theValueName, nullptr, &theValueType, ( LPBYTE )theData.data( ), &sizeOfTheDataBuffer );
            if ( rc == ERROR_SUCCESS )
            {
                theData.resize( sizeOfTheDataBuffer );
            }
            else if ( rc == ERROR_FILE_NOT_FOUND )
            {
                return false;
            }
            else
            {
                if ( rc == ERROR_MORE_DATA )
                {
                    theData.resize( sizeOfTheDataBuffer );
                    rc = RegQueryValueExW( self, nullptr, nullptr, &theValueType, ( LPBYTE )theData.data( ), &sizeOfTheDataBuffer );
                    if ( rc != ERROR_SUCCESS )
                    {
                        ThrowOSError( rc );
                    }
                }

                else
                {
                    ThrowOSError( rc );
                }
            }
            return true;
        }


        bool ReadBoolean( const wchar_t* theValueName, bool& theResult ) const
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToBoolean( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadSByte( const wchar_t* theValueName, char& theResult ) const
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToSByte( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadByte( const wchar_t* theValueName, unsigned char& theResult ) const
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToByte( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadInt16( const wchar_t* theValueName, short& theResult ) const
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToInt16( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadUInt16( const wchar_t* theValueName, unsigned short& theResult ) const
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToUInt16( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }


        bool ReadInt32( const wchar_t* theValueName, int& theResult ) const
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToInt32( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadUInt32( const wchar_t* theValueName, unsigned int& theResult ) const
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToUInt32( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadInt64( const wchar_t* theValueName, long long& theResult ) const
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToInt64( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadUInt64( const wchar_t* theValueName, unsigned long long& theResult ) const
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToUInt64( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadSingle( const wchar_t* theValueName, float& theResult ) const
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToSingle( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadDouble( const wchar_t* theValueName, double& theResult ) const
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToDouble( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }



        bool ReadString( const wchar_t* theValueName, WideString& theResult ) const
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToString( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }



        void ReplaceKey( const AnsiString& theSubKey, const AnsiString& newFile, const AnsiString& oldFile ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegReplaceKeyA( self, theSubKey.data( ), newFile.data( ), oldFile.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void ReplaceKey( const char* theSubKey, const char* newFile, const char* oldFile ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegReplaceKeyA( self, theSubKey, newFile, oldFile );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void ReplaceKey( const AnsiString& newFile, const AnsiString& oldFile ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegReplaceKeyA( self, nullptr, newFile.data( ), oldFile.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void ReplaceKey( const char* newFile, const char* oldFile ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegReplaceKeyA( self, nullptr, newFile, oldFile );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }


        void ReplaceKey( const WideString& theSubKey, const WideString& newFile, const WideString& oldFile ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegReplaceKeyW( self, theSubKey.data( ), newFile.data( ), oldFile.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void ReplaceKey( const wchar_t* theSubKey, const wchar_t* newFile, const wchar_t* oldFile ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegReplaceKeyW( self, theSubKey, newFile, oldFile );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void ReplaceKey( const WideString& newFile, const WideString& oldFile ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegReplaceKeyW( self, nullptr, newFile.data( ), oldFile.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void ReplaceKey( const wchar_t* newFile, const wchar_t* oldFile ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegReplaceKeyW( self, nullptr, newFile, oldFile );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void RestoreKey( const AnsiString& oldFile, DWORD theFlags ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegRestoreKeyA( self, oldFile.data( ), theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }


        void RestoreKey( const char* oldFile, DWORD theFlags ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegRestoreKeyA( self, oldFile, theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void RestoreKey( const WideString& oldFile, DWORD theFlags ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegRestoreKeyW( self, oldFile.data( ), theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void RestoreKey( const wchar_t* oldFile, DWORD theFlags ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegRestoreKeyW( self, oldFile, theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void RenameKey( const WideString& oldSubKeyName, const WideString& newSubKeyName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegRenameKey( self, oldSubKeyName.data( ), newSubKeyName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void RenameKey( const AnsiString& oldSubKeyName, const AnsiString& newSubKeyName ) const
        {
            auto on = ToWideString( oldSubKeyName );
            auto nn = ToWideString( newSubKeyName );
            RenameKey( on, nn );
        }


        void RenameKey( const wchar_t* oldSubKeyName, const wchar_t* newSubKeyName ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegRenameKey( self, oldSubKeyName, newSubKeyName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void SaveKey( const AnsiString& theFilename, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegSaveKeyA( self, theFilename.data( ), theSecurityAttributes );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void SaveKey( const char* theFilename, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegSaveKeyA( self, theFilename, theSecurityAttributes );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void SaveKey( const WideString& theFilename, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegSaveKeyW( self, theFilename.data( ), theSecurityAttributes );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void SaveKey( const wchar_t* theFilename, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegSaveKeyW( self, theFilename, theSecurityAttributes );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void SaveKey( const AnsiString& theFilename, DWORD theFlags, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegSaveKeyExA( self, theFilename.data( ), theSecurityAttributes, theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void SaveKey( const char* theFilename, DWORD theFlags, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegSaveKeyExA( self, theFilename, theSecurityAttributes, theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }


        void SaveKey( const WideString& theFilename, DWORD theFlags, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegSaveKeyExW( self, theFilename.data( ), theSecurityAttributes, theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void SaveKey( const wchar_t* theFilename, DWORD theFlags, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegSaveKeyExW( self, theFilename, theSecurityAttributes, theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void SetKeySecurity( SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegSetKeySecurity( self, SecurityInformation, pSecurityDescriptor );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        

        void SetValue( const char* valueName, DWORD valueType, const void* data, DWORD sizeOfData ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegSetValueExA( self, valueName, 0, valueType, ( const BYTE* )data, sizeOfData );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }
        void SetValue( const wchar_t* valueName, DWORD valueType, const void* data, DWORD sizeOfData ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegSetValueExW( self, valueName, 0, valueType, ( const BYTE* )data, sizeOfData );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        void SetValue( DWORD valueType, const void* data, DWORD sizeOfData ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegSetValueExW( self, nullptr, 0, valueType, ( const BYTE* )data, sizeOfData );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }
        void SetValueA( DWORD valueType, const void* data, DWORD sizeOfData ) const
        {
            auto self = ( HKEY )Value( );
            auto rc = RegSetValueExA( self, nullptr, 0, valueType, ( const BYTE* )data, sizeOfData );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }


        void SetValue( const AnsiString& valueName, DWORD valueType, const void* data, DWORD sizeOfData ) const
        {
            SetValue( valueName.c_str( ), valueType, data, sizeOfData );
        }

        void SetValue( const WideString& valueName, DWORD valueType, const void* data, DWORD sizeOfData ) const
        {
            SetValue( valueName.c_str( ), valueType, data, sizeOfData );
        }

        void SetValue( const char* valueName, RegistryValueType valueType, const void* data, DWORD sizeOfData ) const
        {
            SetValue( valueName, static_cast<DWORD>(valueType), data, sizeOfData );
        }
        void SetValue( const wchar_t* valueName, RegistryValueType valueType, const void* data, DWORD sizeOfData ) const
        {
            SetValue( valueName, static_cast< DWORD >( valueType ), data, sizeOfData );
        }
        void SetValue( const AnsiString& valueName, RegistryValueType valueType, const void* data, DWORD sizeOfData ) const
        {
            SetValue( valueName, static_cast< DWORD >( valueType ), data, sizeOfData );
        }
        void SetValue( const WideString& valueName, RegistryValueType valueType, const void* data, DWORD sizeOfData ) const
        {
            SetValue( valueName, static_cast< DWORD >( valueType ), data, sizeOfData );
        }

        void SetValue( RegistryValueType valueType, const void* data, DWORD sizeOfData ) const
        {
            SetValue( static_cast< DWORD >( valueType ), data, sizeOfData );
        }

        void SetValueA( RegistryValueType valueType, const void* data, DWORD sizeOfData ) const
        {
            SetValueA( static_cast< DWORD >( valueType ), data, sizeOfData );
        }

        void SetValue( const AnsiString& valueName, const AnsiString& value ) const
        {
            SetValue( valueName, RegistryValueType::String, value.c_str(), static_cast<DWORD>( value.size() + 1 ) );
        }

        void SetValue( const WideString& valueName, const WideString& value ) const
        {
            SetValue( valueName, RegistryValueType::String, value.c_str( ), static_cast< DWORD >( (value.size( ) + 1) * sizeof(wchar_t) ) );
        }

        void SetValue( const AnsiString& value ) const
        {
            SetValueA( RegistryValueType::String, value.c_str( ), static_cast< DWORD >( value.size( ) + 1 ) );
        }

        void SetValue( const WideString& value ) const
        {
            SetValue( RegistryValueType::String, value.c_str( ), static_cast< DWORD >( ( value.size( ) + 1 ) * sizeof( wchar_t ) ) );
        }


    };

}

#endif
