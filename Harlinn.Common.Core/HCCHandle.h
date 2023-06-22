#pragma once
#ifndef __HCCHANDLE_H__
#define __HCCHANDLE_H__

#include "HCCDef.h"

namespace Harlinn::Common::Core
{
    template<typename DerivedT, typename HandleT>
    class Handle
    {
    public:
        using DerivedType = DerivedT;
        using HandleType = HandleT;

    protected:
        HandleType value_;
    private:
        bool ownsHandle_;
    protected:
        constexpr Handle( ) noexcept
            : value_( DerivedType::InvalidHandleValue( ) ),
              ownsHandle_( false )
        {
        }
    protected:

        void SetValue( HandleType handle, bool ownsHandle = true )
        {
            if ( handle != value_ )
            {
                auto* derived = static_cast<DerivedType*>( this );
                if ( ownsHandle_ && derived->IsValid( ) )
                {
                    derived->Close( );
                }
                value_ = handle;
                ownsHandle_ = ownsHandle;
            }
            else if ( ownsHandle_ != ownsHandle )
            {
                ownsHandle_ = ownsHandle;
            }
        }
    protected:
        constexpr explicit Handle( HandleType handle, bool ownsHandle = true ) noexcept
            : value_( handle ),
            ownsHandle_( ownsHandle )
        {
        }

    public:
        virtual ~Handle( ) noexcept
        {
            auto* derived = static_cast<DerivedType*>( this );
            derived->Close( );
        }

        static constexpr HandleType InvalidHandleValue( ) noexcept
        {
            return static_cast<HandleType>( 0 );
        }

        constexpr bool IsValid( ) const noexcept
        {
            return value_ != static_cast<HandleType>( 0 );
        }


        Handle( const Handle& other ) = delete;
        Handle& operator = ( Handle& other ) = delete;

        Handle( Handle&& other ) noexcept
            : value_( other.value_ ),
              ownsHandle_( other.ownsHandle_ )
        {
            other.value_ = DerivedType::InvalidHandleValue( );
            other.ownsHandle_ = false;
        }
        Handle& operator = ( Handle&& other ) noexcept
        {
            if ( this != &other )
            {
                auto* derived = static_cast<DerivedType*>( this );

                if ( ownsHandle_ && derived->IsValid( ) )
                {
                    derived->Close( );
                }
                value_ = other.value_;
                ownsHandle_ = other.ownsHandle_;
                other.value_ = DerivedType::InvalidHandleValue( );
                other.ownsHandle_ = false;
            }
            return *this;
        }

        constexpr auto operator<=>( const Handle& other ) const noexcept
        {
            return value_ <=> other.value_;
        }
        constexpr bool operator==( const Handle& other ) const noexcept
        {
            return value_ == other.value_;
        }

        constexpr auto operator<=>( HandleType handle ) const noexcept
        {
            return value_ <=> handle;
        }
        constexpr bool operator==( HandleType handle ) const noexcept
        {
            return value_ == handle;
        }

        constexpr operator HandleType( ) const noexcept
        {
            return value_;
        }

        constexpr HandleType Value( ) const noexcept
        {
            return value_;
        }

        constexpr bool OwnsHandle( ) const noexcept
        {
            return ownsHandle_;
        }
    };


    class ModuleHandle final : public Handle<ModuleHandle, HMODULE>
    {
    public:
        using Base = Handle<ModuleHandle, HMODULE>;

        constexpr ModuleHandle( ) noexcept
            : Base( )
        {
        }

        explicit ModuleHandle( HMODULE hModule, bool closeHandle = true )
            : Base( hModule, closeHandle )
        {
        }

        ModuleHandle( const wchar_t* moduleName, DWORD flags = 0 )
        {
            CheckPointerNotNull( moduleName );
            HMODULE hModule = LoadLibraryExW( moduleName, nullptr, flags );
            if ( !hModule )
            {
                ThrowLastOSError( );
            }
            SetValue( hModule );
        }
        ModuleHandle( const WideString& moduleName, DWORD flags = 0 )
            : ModuleHandle( moduleName.c_str( ), flags )
        {
        }

        ModuleHandle( const char* moduleName, DWORD flags = 0 )
        {
            CheckPointerNotNull( moduleName );
            HMODULE hModule = LoadLibraryExA( moduleName, nullptr, flags );
            if ( !hModule )
            {
                ThrowLastOSError( );
            }
            SetValue( hModule );
        }
        ModuleHandle( const AnsiString& moduleName, DWORD flags = 0 )
            : ModuleHandle( moduleName.c_str( ), flags )
        {
        }

        void Close( ) noexcept
        {
            auto* derived = static_cast< DerivedType* >( this );
            if ( OwnsHandle( ) && derived->IsValid( ) )
            {
                FreeLibrary( value_ );
            }
        }


        using Base::SetValue;


        WideString ModuleFileName( ) const
        {
            if ( IsValid( ) )
            {
                wchar_t buffer[ 512 ];
                WideString::size_type length = ::GetModuleFileNameW( Value( ), buffer, 512 );
                if ( length == 0 )
                {
                    ThrowLastOSError( );
                }
                WideString result( buffer, length );
                return result;
            }
            return {};
        }


        static ModuleHandle Current( )
        {
            HMODULE hModule = GetModuleHandleW( nullptr );
            if ( !hModule )
            {
                ThrowLastOSError( );
            }
            ModuleHandle result( hModule, false );
            return result;
        }
    };

 
}

#endif
