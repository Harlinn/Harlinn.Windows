#pragma once
#ifndef HARLINN_COMMON_CORE_HCCPROPERTYVARIANT_H_
#define HARLINN_COMMON_CORE_HCCPROPERTYVARIANT_H_
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

#include <HCCVariant.h>

namespace Harlinn::Common::Core
{
    class PropertyVariant : public PROPVARIANT
    {
    public:
        using Base = PROPVARIANT;

        static constexpr LANGID InvariantLanguageId = MAKELANGID( LANG_INVARIANT, SUBLANG_NEUTRAL );
        static constexpr LCID InvariantLocaleId = MAKELCID( InvariantLanguageId, SORT_DEFAULT );

        
    private:
        void SetVariantType( VariantType variantType ) noexcept
        {
            Base::vt = USHORT( variantType );
        }

    public:


        static int Compare( const PROPVARIANT& first, const PROPVARIANT& second )
        {

            if ( first.vt == USHORT( VariantType::Empty ) )
            {
                if ( second.vt == USHORT( VariantType::Empty ) )
                {
                    return 0;
                }
                return -1;
            }
            else if ( second.vt == USHORT( VariantType::Empty ) )
            {
                return 1;
            }
            else if ( first.vt == USHORT( VariantType::Null ) )
            {
                if ( second.vt == USHORT( VariantType::Null ) )
                {
                    return 0;
                }
                return -1;
            }
            else if ( second.vt == USHORT( VariantType::Null ) )
            {
                return 1;
            }
            return PropVariantCompare( first, second );
        }

        constexpr VariantType Type( ) const noexcept
        {
            return VariantType( Base::vt );
        }

        constexpr VariantType ElementType( ) const noexcept
        {
            return VariantType( Base::vt & VT_TYPEMASK );
        }

        constexpr bool IsEmpty( ) const noexcept
        {
            return Type( ) == VariantType::Empty;
        }

        constexpr bool IsNull( ) const noexcept
        {
            return Type( ) == VariantType::Null;
        }

        constexpr bool IsReference( ) const noexcept
        {
            return ( Type( ) & VariantType::Byref ) != VariantType::Empty;
        }

        constexpr bool IsArray( ) const noexcept
        {
            return ( Type( ) & VariantType::Array ) != VariantType::Empty;
        }



        constexpr PropertyVariant( ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Empty );
        }
        constexpr explicit PropertyVariant( Int64 value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Int64 );
            Base::hVal.QuadPart = value;
        }
        constexpr explicit PropertyVariant( UInt64 value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::UInt64 );
            Base::uhVal.QuadPart = value;
        }
        constexpr explicit PropertyVariant( LONG value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Long );
            Base::lVal = value;
        }

        constexpr explicit PropertyVariant( Int32 value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Long );
            Base::lVal = value;
        }

        explicit PropertyVariant( LONG value, VariantType variantType )
            : Base( )
        {
            if ( variantType == VariantType::Long || variantType == VariantType::Error )
            {
                Base::vt = static_cast< USHORT >( variantType );
                Base::lVal = value;
            }
            else
            {
                Base::vt = static_cast< USHORT >( VariantType::Error );
                Base::scode = E_INVALIDARG;
                CheckHRESULT( Base::scode );
            }
        }

        constexpr explicit PropertyVariant( BYTE value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Byte );
            Base::bVal = value;
        }
        constexpr explicit PropertyVariant( SHORT value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Short );
            Base::iVal = value;
        }
        constexpr explicit PropertyVariant( FLOAT Value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Float );
            Base::fltVal = Value;
        }
        constexpr explicit PropertyVariant( DOUBLE value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Double );
            Base::dblVal = value;
        }

        explicit PropertyVariant( DOUBLE value, VariantType variantType )
            : Base( )
        {
            if ( variantType == VariantType::Double || variantType == VariantType::DateTime )
            {
                Base::vt = static_cast< USHORT >( variantType );
                Base::dblVal = value;
            }
            else
            {
                Base::vt = static_cast< USHORT >( VariantType::Error );
                Base::scode = E_INVALIDARG;
                CheckHRESULT( Base::scode );
            }
        }

        constexpr explicit PropertyVariant( bool value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Bool );
            Base::boolVal = value ? VARIANT_TRUE : VARIANT_FALSE;
        }

        constexpr explicit PropertyVariant( const CY& value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Currency );
            Base::cyVal = value;
        }
        constexpr explicit PropertyVariant( const Currency& value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Currency );
            Base::cyVal.int64 = value.Value( );
        }

        explicit PropertyVariant( const DateTime& value )
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::DateTime );
            Base::date = value.ToOADate( );
        }


        constexpr explicit PropertyVariant( const TimeSpan& value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::DateTime );
            Base::date = value.TotalDays( );
        }


        explicit PropertyVariant( const SysString& value )
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::BStr );
            Base::bstrVal = value.Copy( );
        }

        explicit PropertyVariant( SysString&& value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::BStr );
            Base::bstrVal = value.Detach( );
        }

        explicit PropertyVariant( const WideString& value )
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::BStr );
            Base::bstrVal = nullptr;
            if ( value.length( ) )
            {
                Base::bstrVal = SysAllocStringLen( value.c_str( ), static_cast< UINT >( value.length( ) ) );
                if ( !Base::bstrVal )
                {
                    CheckHRESULT( E_OUTOFMEMORY );
                }
            }
        }

        explicit PropertyVariant( const wchar_t* value )
            : Base( )
        {
            if ( value && value[ 0 ] )
            {
                auto length = wcslen( value );
                Base::vt = static_cast< USHORT >( VariantType::BStr );
                Base::bstrVal = SysAllocStringLen( value, static_cast< UINT >( length ) );
                if ( !Base::bstrVal )
                {
                    CheckHRESULT( E_OUTOFMEMORY );
                }
            }
        }



        explicit PropertyVariant( IUnknown* pInterface ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Unknown );
            Base::punkVal = pInterface;
            if ( Base::punkVal )
            {
                Base::punkVal->AddRef( );
            }
        }

        explicit PropertyVariant( IDispatch* pInterface ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Dispatch );
            Base::pdispVal = pInterface;
            if ( Base::pdispVal )
            {
                Base::pdispVal->AddRef( );
            }
        }

        explicit PropertyVariant( SAFEARRAY* safeArray )
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Array );
            if ( safeArray )
            {
                auto vType = SafeArray::GetElementVariantType( safeArray );
                Base::vt |= static_cast< USHORT >( vType );
                auto hr = SafeArrayCopy( safeArray, &parray );
                CheckHRESULT( hr );
            }
            else
            {
                Base::parray = nullptr;
            }
        }

        explicit PropertyVariant( const SafeArray& safeArray )
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Array );
            if ( safeArray.ptr_ )
            {
                auto vType = SafeArray::GetElementVariantType( safeArray.ptr_ );
                Base::vt |= static_cast< USHORT >( vType );
                auto hr = SafeArrayCopy( safeArray.ptr_, &parray );
                CheckHRESULT( hr );
            }
            else
            {
                Base::parray = nullptr;
            }
        }
        explicit PropertyVariant( SafeArray&& safeArray )
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Array );
            if ( safeArray.ptr_ )
            {
                auto vType = SafeArray::GetElementVariantType( safeArray.ptr_ );
                Base::vt |= static_cast< USHORT >( vType );
                Base::parray = safeArray.ptr_;
                safeArray.ptr_ = nullptr;
            }
            else
            {
                Base::parray = nullptr;
            }
        }



        constexpr explicit PropertyVariant( char value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::SByte );
            Base::cVal = value;
        }
        constexpr explicit PropertyVariant( signed char value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::SByte );
            Base::cVal = value;
        }

        constexpr explicit PropertyVariant( USHORT value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::UShort );
            Base::uiVal = value;
        }

        constexpr explicit PropertyVariant( ULONG value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::ULong );
            Base::ulVal = value;
        }
        constexpr explicit PropertyVariant( UInt32 value ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::ULong );
            Base::ulVal = value;
        }



        PropertyVariant( const PropertyVariant& other )
        {
            switch ( other.vt )
            {
                case VT_EMPTY:
                case VT_NULL:
                case VT_I1:
                case VT_I2:
                case VT_I4:
                case VT_I8:
                case VT_UI1:
                case VT_UI2:
                case VT_UI4:
                case VT_UI8:
                case VT_R4:
                case VT_R8:
                case VT_CY:
                case VT_DATE:
                    Base::vt = other.vt;
                    Base::uhVal.QuadPart = other.uhVal.QuadPart;
                    break;
                default:
                    PropVariantInit( this );
                    auto hr = PropVariantCopy( ( PROPVARIANT* )this, &other );
                    CheckHRESULT( hr );
                    break;

            }
        }

        PropertyVariant( PropertyVariant&& other ) noexcept
        {
            Base* self = this;
            Base* otherPtr = &other;
            memcpy( self, otherPtr, sizeof( PROPVARIANT ) );
            other.vt = static_cast< USHORT >( VariantType::Empty );
        }

        void Clear( )
        {
            switch ( Base::vt )
            {
                case VT_EMPTY:
                case VT_NULL:
                case VT_I1:
                case VT_I2:
                case VT_I4:
                case VT_I8:
                case VT_UI1:
                case VT_UI2:
                case VT_UI4:
                case VT_UI8:
                case VT_R4:
                case VT_R8:
                case VT_CY:
                case VT_DATE:
                    Base::vt = VT_EMPTY;
                    break;
                default:
                    auto hr = PropVariantClear( ( PROPVARIANT* )this );
                    CheckHRESULT( hr );
                    break;

            }
        }

        ~PropertyVariant( )
        {
            if ( Base::vt != VT_EMPTY )
            {
                Clear( );
            }
        }

        PropertyVariant& operator = ( const PropertyVariant& other )
        {
            if ( &vt != &other.vt )
            {
                if ( Base::vt != VT_EMPTY )
                {
                    Clear( );
                }
                switch ( other.vt )
                {
                    case VT_EMPTY:
                    case VT_NULL:
                    case VT_I1:
                    case VT_I2:
                    case VT_I4:
                    case VT_I8:
                    case VT_UI1:
                    case VT_UI2:
                    case VT_UI4:
                    case VT_UI8:
                    case VT_R4:
                    case VT_R8:
                    case VT_CY:
                    case VT_DATE:
                        Base::vt = other.vt;
                        Base::uhVal.QuadPart = other.uhVal.QuadPart;
                        break;
                    default:
                        auto hr = PropVariantCopy( this, &other );
                        CheckHRESULT( hr );
                        break;

                }
            }
            return *this;
        }

        PropertyVariant& operator = ( PropertyVariant&& other ) noexcept
        {
            if ( this != &other )
            {
                if ( Base::vt != VT_EMPTY )
                {
                    Clear( );
                }

                Base* self = this;
                Base* otherPtr = &other;
                memcpy( self, otherPtr, sizeof( PROPVARIANT ) );
                other.vt = VT_EMPTY;
            }
            return *this;
        }

        int CompareTo( const PROPVARIANT& other ) const
        {
            return Compare( *this, other );
        }

        int CompareTo( const PropertyVariant& other ) const
        {
            return Compare( *this, other );
        }

        bool operator == ( const PROPVARIANT& other ) const { return CompareTo( other ) == 0; }
        bool operator != ( const PROPVARIANT& other ) const { return CompareTo( other ) != 0; }
        bool operator <= ( const PROPVARIANT& other ) const { return CompareTo( other ) <= 0; }
        bool operator <  ( const PROPVARIANT& other ) const { return CompareTo( other ) < 0; }
        bool operator >  ( const PROPVARIANT& other ) const { return CompareTo( other ) > 0; }
        bool operator >= ( const PROPVARIANT& other ) const { return CompareTo( other ) >= 0; }

        bool operator == ( const PropertyVariant& other ) const { return CompareTo( other ) == 0; }
        bool operator != ( const PropertyVariant& other ) const { return CompareTo( other ) != 0; }
        bool operator <= ( const PropertyVariant& other ) const { return CompareTo( other ) <= 0; }
        bool operator <  ( const PropertyVariant& other ) const { return CompareTo( other ) < 0; }
        bool operator >  ( const PropertyVariant& other ) const { return CompareTo( other ) > 0; }
        bool operator >= ( const PropertyVariant& other ) const { return CompareTo( other ) >= 0; }


        HRESULT AssignTo( PROPVARIANT& other ) const
        {
            HRESULT result = S_OK;
            if ( other.vt != VT_EMPTY )
            {
                result = PropVariantClear( &other );
                if ( FAILED( result ) )
                {
                    return result;
                }
                other.vt = VT_EMPTY;
            }
            if ( IsEmpty( ) == FALSE )
            {
                result = PropVariantCopy( &other, this );
            }
            return result;
        }

        void Assign( Int64 value )
        {
            Clear( );
            SetVariantType( VariantType::Int64 );
            Base::hVal.QuadPart = value;
        }
        void Assign( UInt64 value )
        {
            Clear( );
            SetVariantType( VariantType::UInt64 );
            Base::uhVal.QuadPart = value;
        }
        void Assign( LONG value )
        {
            Clear( );
            SetVariantType( VariantType::Long );
            Base::lVal = value;
        }

        void Assign( LONG value, VariantType variantType )
        {
            Clear( );
            if ( variantType == VariantType::Long || variantType == VariantType::Error )
            {
                SetVariantType( variantType );
                Base::lVal = value;
            }
            else
            {
                SetVariantType( VariantType::Error );
                Base::scode = E_INVALIDARG;
                CheckHRESULT( Base::scode );
            }
        }

        void Assign( BYTE value )
        {
            Clear( );
            SetVariantType( VariantType::Byte );
            Base::bVal = value;
        }
        void Assign( SHORT value )
        {
            Clear( );
            SetVariantType( VariantType::Short );
            Base::iVal = value;
        }
        void Assign( FLOAT value )
        {
            Clear( );
            SetVariantType( VariantType::Float );
            Base::fltVal = value;
        }
        void Assign( DOUBLE value )
        {
            Clear( );
            SetVariantType( VariantType::Double );
            Base::dblVal = value;
        }

        void Assign( DOUBLE value, VariantType variantType )
        {
            Clear( );
            if ( variantType == VariantType::Double || variantType == VariantType::DateTime )
            {
                SetVariantType( variantType );
                Base::dblVal = value;
            }
            else
            {
                SetVariantType( VariantType::Error );
                Base::scode = E_INVALIDARG;
                CheckHRESULT( Base::scode );
            }
        }

        void Assign( bool value )
        {
            Clear( );
            SetVariantType( VariantType::Bool );
            Base::boolVal = value ? VARIANT_TRUE : VARIANT_FALSE;
        }

        void Assign( const CY& value )
        {
            Clear( );
            SetVariantType( VariantType::Currency );
            Base::cyVal = value;
        }
        void Assign( const Currency& value )
        {
            Clear( );
            SetVariantType( VariantType::Currency );
            Base::cyVal.int64 = value.Value( );
        }

        void Assign( const DateTime& value )
        {
            Clear( );
            SetVariantType( VariantType::DateTime );
            Base::date = value.ToOADate( );
        }

        void Assign( const TimeSpan& value )
        {
            Clear( );
            SetVariantType( VariantType::Double );
            Base::date = value.TotalDays( );
        }

        void Assign( const SysString& value )
        {
            Clear( );
            SetVariantType( VariantType::BStr );
            Base::bstrVal = value.Copy( );
        }

        void Assign( const WideString& value )
        {
            Clear( );
            SetVariantType( VariantType::BStr );
            Base::bstrVal = nullptr;
            if ( value.length( ) )
            {
                Base::bstrVal = SysAllocStringLen( value.c_str( ), UINT( value.length( ) ) );
                if ( !Base::bstrVal )
                {
                    CheckHRESULT( E_OUTOFMEMORY );
                }
            }
        }


        void Assign( IUnknown* pInterface )
        {
            Clear( );
            SetVariantType( VariantType::Unknown );
            Base::punkVal = pInterface;
            if ( Base::punkVal )
            {
                Base::punkVal->AddRef( );
            }
        }

        void Assign( IDispatch* pInterface )
        {
            Clear( );
            SetVariantType( VariantType::Dispatch );
            Base::pdispVal = pInterface;
            if ( Base::pdispVal )
            {
                Base::pdispVal->AddRef( );
            }
        }

        void Assign( SAFEARRAY* safeArray )
        {
            Clear( );
            SetVariantType( VariantType::Array );
            if ( safeArray )
            {
                auto vType = SafeArray::GetElementVariantType( safeArray );
                SetVariantType( VariantType::Array | vType );
                auto hr = SafeArrayCopy( safeArray, &parray );
                CheckHRESULT( hr );
            }
            else
            {
                Base::parray = nullptr;
            }
        }

        void Assign( signed char value )
        {
            Clear( );
            SetVariantType( VariantType::SByte );
            Base::cVal = value;
        }

        void Assign( USHORT value )
        {
            Clear( );
            SetVariantType( VariantType::UShort );
            Base::uiVal = value;
        }

        void Assign( wchar_t value )
        {
            Clear( );
            SetVariantType( VariantType::UShort );
            Base::uiVal = static_cast< UInt16 >( value );
        }


        void Assign( ULONG value )
        {
            Clear( );
            SetVariantType( VariantType::ULong );
            Base::ulVal = value;
        }

        template <typename T>
        PropertyVariant& operator = ( const T& value )
        {
            Assign( value );
            return *this;
        }

    private:
        template<VariantType variantType>
        void ChangeType( PROPVARIANT& destination ) const
        {
            auto hr = PropVariantChangeType( &destination, *( ( PROPVARIANT* )this ), 0, static_cast< VARTYPE >( variantType ) );
            CheckHRESULT( hr );
        }
    public:
        bool AsBoolean( ) const
        {
            switch ( Type( ) )
            {
                case VariantType::Empty:
                    return false;
                    break;
                case VariantType::Null:
                    return false;
                    break;
                case VariantType::Bool:
                    return Base::boolVal != VARIANT_FALSE;
                    break;
                case VariantType::Int1:
                    return Base::cVal != 0;
                    break;
                case VariantType::UInt1:
                    return Base::bVal != 0;
                    break;
                case VariantType::Int2:
                    return Base::iVal != 0;
                    break;
                case VariantType::UInt2:
                    return Base::uiVal != 0;
                    break;
                case VariantType::Int4:
                    return Base::lVal != 0;
                    break;
                case VariantType::UInt4:
                    return Base::ulVal != 0;
                    break;
                case VariantType::Int8:
                    return Base::hVal.QuadPart != 0;
                    break;
                case VariantType::UInt8:
                    return Base::uhVal.QuadPart != 0;
                    break;
                case VariantType::Real4:
                    return Base::fltVal != 0.0f;
                    break;
                case VariantType::Real8:
                    return Base::dblVal != 0.0;
                    break;
                default:
                {
                    PROPVARIANT result = { 0, };
                    ChangeType<VariantType::Bool>( result );
                    return result.boolVal != VARIANT_FALSE;
                }
                break;
            }
        }
        template<typename T>
        T As( ) const
        {
            static_assert( AlwaysFalse<T>::value, "Unsupported conversion" );
        }

        template<>
        bool As<bool>( ) const
        {
            return AsBoolean( );
        }

        template<>
        std::optional<bool> As<std::optional<bool>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsBoolean( );
            }
            return {};
        }

    private:
        template<typename T>
        bool ConvertTo( T& result ) const noexcept
        {
            switch ( Type( ) )
            {
                case VariantType::Bool:
                    result = Base::boolVal != VARIANT_FALSE ? static_cast< T >( 1 ): static_cast< T >( 0 );
                    return true;
                    break;
                case VariantType::Int1:
                    result = static_cast< T >( Base::cVal );
                    return true;
                    break;
                case VariantType::UInt1:
                    result = static_cast< T >( Base::bVal );
                    return true;
                    break;
                case VariantType::Int2:
                    result = static_cast< T >( Base::iVal );
                    return true;
                    break;
                case VariantType::UInt2:
                    result = static_cast< T >( Base::uiVal );
                    return true;
                    break;
                case VariantType::Int4:
                    result = static_cast< T >( Base::lVal );
                    return true;
                    break;
                case VariantType::UInt4:
                    result = static_cast< T >( Base::ulVal );
                    return true;
                    break;
                case VariantType::Int8:
                    result = static_cast< T >( Base::hVal.QuadPart );
                    return true;
                    break;
                case VariantType::UInt8:
                    result = static_cast< T >( Base::uhVal.QuadPart );
                    return true;
                    break;
                case VariantType::Real4:
                    result = static_cast< T >( Base::fltVal );
                    return true;
                    break;
                case VariantType::Real8:
                    result = static_cast< T >( Base::dblVal );
                    return true;
                    break;
            }
            return false;
        }



    public:
        signed char AsSByte( ) const
        {
            char result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                PROPVARIANT variant = { 0, };
                ChangeType<VariantType::Int1>( variant );
                return variant.cVal;
            }
        }
        template<>
        char As<char>( ) const
        {
            return AsSByte( );
        }
        template<>
        signed char As<signed char>( ) const
        {
            return AsSByte( );
        }

        template<>
        std::optional<char> As<std::optional<char>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsSByte( );
            }
            return {};
        }
        template<>
        std::optional<signed char> As<std::optional<signed char>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsSByte( );
            }
            return {};
        }

        unsigned char AsByte( ) const
        {
            unsigned char result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                PROPVARIANT variant = { 0, };
                ChangeType<VariantType::UInt1>( variant );
                return variant.bVal;
            }
        }

        template<>
        unsigned char As<unsigned char>( ) const
        {
            return AsByte( );
        }

        template<>
        std::optional<unsigned char> As<std::optional<unsigned char>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsByte( );
            }
            return {};
        }


        Int16 AsInt16( ) const
        {
            Int16 result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                PROPVARIANT variant = { 0, };
                ChangeType<VariantType::Int2>( variant );
                return variant.iVal;
            }
        }



        template<>
        Int16 As<Int16>( ) const
        {
            return AsInt16( );
        }

        template<>
        std::optional<Int16> As<std::optional<Int16>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsInt16( );
            }
            return {};
        }

        UInt16 AsUInt16( ) const
        {
            UInt16 result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                PROPVARIANT variant = { 0, };
                ChangeType<VariantType::UInt2>( variant );
                return variant.uiVal;
            }
        }

        template<>
        UInt16 As<UInt16>( ) const
        {
            return AsUInt16( );
        }

        template<>
        wchar_t As<wchar_t>( ) const
        {
            return AsUInt16( );
        }

        template<>
        std::optional<UInt16> As<std::optional<UInt16>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsUInt16( );
            }
            return {};
        }

        template<>
        std::optional<wchar_t> As<std::optional<wchar_t>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsUInt16( );
            }
            return {};
        }


        Int32 AsInt32( ) const
        {
            Int32 result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                PROPVARIANT variant = { 0, };
                ChangeType<VariantType::Int4>( variant );
                return variant.lVal;
            }
        }

        template<>
        Int32 As<Int32>( ) const
        {
            return AsInt32( );
        }

        template<>
        long As<long>( ) const
        {
            return AsInt32( );
        }


        template<>
        std::optional<Int32> As<std::optional<Int32>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsInt32( );
            }
            return {};
        }

        template<>
        std::optional<long> As<std::optional<long>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsInt32( );
            }
            return {};
        }

        UInt32 AsUInt32( ) const
        {
            UInt32 result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                PROPVARIANT variant = { 0, };
                ChangeType<VariantType::UInt4>( variant );
                return variant.ulVal;
            }
        }

        template<>
        UInt32 As<UInt32>( ) const
        {
            return AsUInt32( );
        }

        template<>
        unsigned long As<unsigned long>( ) const
        {
            return AsUInt32( );
        }

        template<>
        std::optional<UInt32> As<std::optional<UInt32>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsUInt32( );
            }
            return {};
        }

        template<>
        std::optional<unsigned long> As<std::optional<unsigned long>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsUInt32( );
            }
            return {};
        }


        Int64 AsInt64( ) const
        {
            Int64 result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                PROPVARIANT variant = { 0, };
                ChangeType<VariantType::Int64>( variant );
                return variant.hVal.QuadPart;
            }
        }

        template<>
        Int64 As<Int64>( ) const
        {
            return AsInt64( );
        }

        template<>
        std::optional<Int64> As<std::optional<Int64>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsInt64( );
            }
            return {};
        }


        UInt64 AsUInt64( ) const
        {
            UInt64 result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                PROPVARIANT variant = { 0, };
                ChangeType<VariantType::UInt64>( variant );
                return variant.uhVal.QuadPart;
            }
        }

        template<>
        UInt64 As<UInt64>( ) const
        {
            return AsUInt64( );
        }

        template<>
        std::optional<UInt64> As<std::optional<UInt64>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsUInt64( );
            }
            return {};
        }

        Single AsSingle( ) const
        {
            Single result = 0;
            auto type = Type( );
            if ( type == VariantType::Real4 )
            {
                return Base::fltVal;
            }
            else if ( type == VariantType::BStr )
            {
                if ( TryParseInvariant( static_cast< const wchar_t* >( Base::bstrVal ), result ) )
                {
                    return result;
                }
                if ( TryParse( static_cast< const wchar_t* >( Base::bstrVal ), result ) )
                {
                    return result;
                }
            }

            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                PROPVARIANT variant = { 0, };
                ChangeType<VariantType::Real4>( variant );
                return variant.fltVal;
            }
        }

        template<>
        Single As<Single>( ) const
        {
            return AsSingle( );
        }

        template<>
        std::optional<Single> As<std::optional<Single>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsSingle( );
            }
            return {};
        }

        Double AsDouble( ) const
        {
            Double result = 0;
            auto type = Type( );
            if ( type == VariantType::Real8 )
            {
                return Base::dblVal;
            }
            else if ( type == VariantType::BStr )
            {
                if ( TryParseInvariant( static_cast< const wchar_t* >( Base::bstrVal ), result ) )
                {
                    return result;
                }
                if ( TryParse( static_cast< const wchar_t* >( Base::bstrVal ), result ) )
                {
                    return result;
                }
            }


            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                PROPVARIANT variant = { 0, };
                ChangeType<VariantType::Real8>( variant );
                return variant.dblVal;
            }
        }

        template<>
        Double As<Double>( ) const
        {
            return AsDouble( );
        }

        template<>
        std::optional<Double> As<std::optional<Double>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsDouble( );
            }
            return {};
        }


        WideString AsWideString( ) const
        {
            WideString result;
            auto type = Type( );
            switch ( type )
            {
                case VariantType::Empty:
                {
                    
                }
                break;
                case VariantType::Null:
                {
                    result.Assign( L"<null>", 6 );
                }
                break;
                case VariantType::SByte:
                {
                    result = ToWideString( static_cast<SByte>( cVal ) );
                }
                break;
                case VariantType::Byte:
                {
                    result = ToWideString( static_cast< Byte >( bVal ) );
                }
                break;
                case VariantType::Int16:
                {
                    result = ToWideString( iVal );
                }
                break;
                case VariantType::UInt16:
                {
                    result = ToWideString( uiVal );
                }
                break;
                case VariantType::Int32:
                {
                    result = ToWideString( static_cast< Int32 >( lVal ) );
                }
                break;
                case VariantType::UInt32:
                {
                    result = ToWideString( static_cast<UInt32>( ulVal ) );
                }
                break;
                case VariantType::Int:
                {
                    result = ToWideString( intVal );
                }
                break;
                case VariantType::UInt:
                {
                    result = ToWideString( uintVal );
                }
                break;
                case VariantType::Int64:
                {
                    result = ToWideString( iVal );
                }
                break;
                case VariantType::UInt64:
                {
                    result = ToWideString( uiVal );
                }
                break;
                case VariantType::Single:
                {
                    result = ToWideStringInvariant( fltVal );
                }
                break;
                case VariantType::Double:
                {
                    result = ToWideString( dblVal );
                }
                break;
                case VariantType::Bool:
                {
                    result = ToWideString( boolVal != VARIANT_FALSE ? true : false );
                }
                break;
                case VariantType::Error:
                {
                    wchar_t* ptr = nullptr;
                    auto hr = PropVariantToStringAlloc( *this, &ptr );
                    if ( FAILED( hr ) )
                    {
                        CheckHRESULT( hr );
                    }
                    if ( ptr )
                    {
                        result = ptr;
                        CoTaskMemFree( ptr );
                    }
                }
                break;
                case VariantType::Currency:
                {
                    result = reinterpret_cast<const Currency&>(cyVal).ToWideString( );
                }
                break;
                case VariantType::DateTime:
                {
                    DateTime dateTime = DateTime::FromOADate( date );
                    result = dateTime.ToString( );
                }
                break;
                case VariantType::FileTime:
                {
                    DateTime dateTime = DateTime::FromFileTime( filetime );
                    result = dateTime.ToString( );
                }
                break;
                case VariantType::CLSID:
                {
                    if ( puuid )
                    {
                        Guid guid( *puuid );
                        result = guid.ToString( );
                    }
                }
                break;
                case VariantType::BStr:
                {
                    if ( bstrVal )
                    {
                        size_t length = SysStringLen( bstrVal );
                        result = WideString( bstrVal, length );
                    }
                }
                break;
                default:
                    wchar_t* ptr = nullptr;
                    auto hr = PropVariantToStringAlloc( *this, &ptr );
                    if ( FAILED( hr ) )
                    {
                        if ( hr != TYPE_E_TYPEMISMATCH )
                        {
                            CheckHRESULT( hr );
                        }
                    }
                    if ( ptr )
                    {
                        result = ptr;
                        CoTaskMemFree( ptr );
                    }
            }
            return result;
        }
        template<>
        WideString As<WideString>( ) const
        {
            return AsWideString( );
        }

        template<>
        std::optional<WideString> As<std::optional<WideString>>( ) const
        {
            return AsWideString( );
        }

        std::wstring AsStdWideString( ) const
        {
            if ( Type( ) == VariantType::BStr )
            {
                if ( Base::bstrVal )
                {
                    return std::wstring( Base::bstrVal );
                }
                else
                {
                    return {};
                }
            }
            else
            {
                wchar_t* ptr = nullptr;
                auto hr = PropVariantToStringAlloc( *this, &ptr );
                if ( FAILED( hr ) )
                {
                    CheckHRESULT( hr );
                }
                if ( ptr )
                {
                    std::wstring result(ptr);
                    CoTaskMemFree( ptr );
                    return result;
                }
                return {};
            }
        }

        template<>
        std::wstring As<std::wstring>( ) const
        {
            return AsStdWideString( );
        }

        template<>
        std::optional<std::wstring> As<std::optional<std::wstring>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsStdWideString( );
            }
            return {};
        }


        AnsiString AsAnsiString( ) const
        {
            return ToAnsiString( AsWideString( ) );
        }

        template<>
        AnsiString As<AnsiString>( ) const
        {
            return AsAnsiString( );
        }

        template<>
        std::optional<AnsiString> As<std::optional<AnsiString>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsAnsiString( );
            }
            return {};
        }

        std::string AsStdString( ) const
        {
            std::string result;
            ToAnsiString( AsWideString( ), result );
            return result;
        }

        template<>
        std::string As<std::string>( ) const
        {
            return AsStdString( );
        }

        template<>
        std::optional<std::string> As<std::optional<std::string>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsStdString( );
            }
            return {};
        }

        SysString AsSysString( ) const
        {
            if ( Type( ) == VariantType::BStr )
            {
                if ( Base::bstrVal )
                {
                    return SysString( Base::bstrVal );
                }
                else
                {
                    return SysString( );
                }
            }
            else
            {
                PropertyVariant result;
                auto hr = PropVariantChangeType( ( PROPVARIANT* )&result, *( PROPVARIANT* )this, 0, ( VARTYPE )VariantType::BStr );
                CheckHRESULT( hr );
                if ( result.bstrVal )
                {
                    return SysString( result.bstrVal );
                }
                else
                {
                    return SysString( );
                }
            }
        }

        template<>
        SysString As<SysString>( ) const
        {
            return AsSysString( );
        }

        template<>
        std::optional<SysString> As<std::optional<SysString>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsSysString( );
            }
            return {};
        }


        DateTime AsDateTime( LCID localeId = InvariantLocaleId ) const
        {
            auto type = Type( );
            if ( type == VariantType::DateTime )
            {
                return DateTime::FromOADate( Base::date );
            }
            else if ( type == VariantType::BStr )
            {
                DateTime dateTime;
                if ( DateTime::TryParse( static_cast< const wchar_t* >( Base::bstrVal ), dateTime ) )
                {
                    return dateTime;
                }
            }
            PropertyVariant result;
            auto hr = PropVariantChangeType( ( PROPVARIANT* )&result, *( const PROPVARIANT* )this, 0, ( VARTYPE )VariantType::DateTime );
            CheckHRESULT( hr );
            return DateTime::FromOADate( result.date );
        }
        template<>
        DateTime As<DateTime>( ) const
        {
            return AsDateTime( );
        }

        template<>
        std::optional<DateTime> As<std::optional<DateTime>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsDateTime( );
            }
            return {};
        }


        TimeSpan AsTimeSpan( ) const
        {
            auto type = Type( );
            if ( type == VariantType::Real8 || type == VariantType::DateTime )
            {
                return TimeSpan::FromDays( Base::dblVal );
            }
            else if ( type == VariantType::Real4 )
            {
                return TimeSpan::FromDays( Base::fltVal );
            }
            else if ( type == VariantType::BStr )
            {
                TimeSpan timeSpan;
                if ( TimeSpan::TryParse( Base::bstrVal, timeSpan ) )
                {
                    return timeSpan;
                }
            }
            PropertyVariant result;
            auto hr = PropVariantChangeType( ( PROPVARIANT* )&result, *( const PROPVARIANT* )this, 0, ( VARTYPE )VariantType::Real8 );
            CheckHRESULT( hr );
            return TimeSpan::FromDays( result.dblVal );
        }
        template<>
        TimeSpan As<TimeSpan>( ) const
        {
            return AsTimeSpan( );
        }

        template<>
        std::optional<TimeSpan> As<std::optional<TimeSpan>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsTimeSpan( );
            }
            return {};
        }

        Guid AsGuid( ) const
        {
            return Guid( AsWideString( ) );
        }
        template<>
        Guid As<Guid>( ) const
        {
            return AsGuid( );
        }

        template<>
        std::optional<Guid> As<std::optional<Guid>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsGuid( );
            }
            return {};
        }

        Currency AsCurrency( ) const
        {
            Currency result;
            switch ( Type( ) )
            {
                case VariantType::Bool:
                    result = Base::boolVal != VARIANT_FALSE ? 1 : 0;
                    break;
                case VariantType::Int1:
                    result = Base::cVal;
                    break;
                case VariantType::UInt1:
                    result = Base::bVal;
                    break;
                case VariantType::Int2:
                    result = Base::iVal;
                    break;
                case VariantType::UInt2:
                    result = Base::uiVal;
                    break;
                case VariantType::Int4:
                    result = Base::lVal;
                    break;
                case VariantType::UInt4:
                    result = Base::ulVal;
                    break;
                case VariantType::Int8:
                    result = Base::hVal.QuadPart;
                    break;
                case VariantType::UInt8:
                    result = Base::uhVal.QuadPart;
                    break;
                case VariantType::Real4:
                    result = Base::fltVal;
                    break;
                case VariantType::Real8:
                    result = Base::dblVal;
                    break;
                case VariantType::Currency:
                    result = Base::cyVal;
                    break;
                default:
                {
                    PropertyVariant variant;
                    auto hr = PropVariantChangeType( &variant, *( const PROPVARIANT* )this, 0, ( VARTYPE )VariantType::Currency );
                    CheckHRESULT( hr );
                    result = variant.cyVal;
                }
                break;
            }
            return result;
        }

        template<>
        Currency As<Currency>( ) const
        {
            return AsCurrency( );
        }

        template<>
        std::optional<Currency> As<std::optional<Currency>>( ) const
        {
            auto type = Type( );
            if ( type != VariantType::Empty && type != VariantType::Null )
            {
                return AsCurrency( );
            }
            return {};
        }

    };
}
#endif