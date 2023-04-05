#pragma once
#ifndef __HCCHANDLE_H__
#define __HCCHANDLE_H__

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
}

#endif
