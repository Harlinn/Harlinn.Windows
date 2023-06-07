#pragma once
#ifndef __HCCSTRING_H__
#define __HCCSTRING_H__

#include <HCCDef.h>
#include <HCCTraits.h>
#include <HCCException.h>
#include <HCCLib.h>



namespace Harlinn::Common::Core
{
    HCC_EXPORT void ToWideString( const char* source, size_t length, unsigned codePage, unsigned flags, std::wstring& dest );
    inline void ToWideString( const char* source, size_t length, std::wstring& dest )
    {
        ToWideString( source, length, CP_ACP, 0, dest );
    }
    inline void ToWideString( const std::string& source, std::wstring& dest )
    {
        ToWideString( source.c_str( ), source.length( ), dest );
    }
    inline std::wstring ToWideString( const std::string& source )
    {
        std::wstring result;
        ToWideString( source, result );
        return result;
    }
    inline std::wstring ToWideString( const char* source )
    {
        if ( source && source[0] )
        {
            auto length = strlen( source );
            std::wstring result;
            ToWideString( source, length, CP_ACP, 0, result );
            return result;
        }
        else
        {
            return {};
        }
    }
    inline std::wstring ToWideString( const wchar_t* source )
    {
        if ( source && source[0] )
        {
            auto length = wcslen( source );
            std::wstring result( source, length );
            return result;
        }
        else
        {
            return {};
        }
    }

    HCC_EXPORT std::wstring ToWideString( bool value );
    HCC_EXPORT std::wstring ToWideString( SByte value, int base = 10 );
    HCC_EXPORT std::wstring ToWideString( Byte value, int base = 10 );
    HCC_EXPORT std::wstring ToWideString( Int16 value, int base = 10 );
    HCC_EXPORT std::wstring ToWideString( UInt16 value, int base = 10 );
    HCC_EXPORT std::wstring ToWideString( Int32 value, int base = 10 );
    HCC_EXPORT std::wstring ToWideString( UInt32 value, int base = 10 );
    HCC_EXPORT std::wstring ToWideString( Int64 value, int base = 10 );
    HCC_EXPORT std::wstring ToWideString( UInt64 value, int base = 10 );
    HCC_EXPORT std::wstring ToWideString( Single value );
    HCC_EXPORT std::wstring ToWideString( Single value, int width, int precission );
    HCC_EXPORT std::wstring ToWideString( Single value, const Locale& locale );
    HCC_EXPORT std::wstring ToWideString( Single value, int width, int precission, const Locale& locale );
    HCC_EXPORT std::wstring ToWideString( Double value );
    HCC_EXPORT std::wstring ToWideString( const DateTime& value );
    HCC_EXPORT std::wstring ToWideString( const TimeSpan& value );
    HCC_EXPORT std::wstring ToWideString( const Guid& value );
    HCC_EXPORT std::wstring ToWideString( const Currency& value );
    HCC_EXPORT std::wstring ToWideString( const Variant& value );


    HCC_EXPORT void ToAnsiString( const wchar_t* source, size_t length, unsigned codePage, unsigned flags, std::string& dest );
    inline void ToAnsiString( const wchar_t* source, size_t length, std::string& dest )
    {
        ToAnsiString( source, length, CP_ACP, 0, dest );
    }
    inline void ToAnsiString( const std::wstring& source, std::string& dest )
    {
        ToAnsiString( source.c_str(), source.length(), CP_ACP, 0, dest );
    }
    inline std::string ToAnsiString( const std::wstring& source )
    {
        std::string result;
        ToAnsiString( source, result );
        return result;
    }
    inline std::string ToAnsiString( const wchar_t* source )
    {
        if ( source && source[0] )
        {
            auto length = wcslen( source );
            std::string result;
            ToAnsiString( source, length, CP_ACP, 0, result );
            return result;
        }
        else
        {
            return {};
        }
    }
    inline std::string ToAnsiString( const char* source )
    {
        if ( source && source[0] )
        {
            auto length = strlen( source );
            std::string result(source, length);
            return result;
        }
        else
        {
            return {};
        }
    }

    HCC_EXPORT std::string ToAnsiString( bool value );
    HCC_EXPORT std::string ToAnsiString( SByte value, int base = 10 );
    HCC_EXPORT std::string ToAnsiString( Byte value, int base = 10 );
    HCC_EXPORT std::string ToAnsiString( Int16 value, int base = 10 );
    HCC_EXPORT std::string ToAnsiString( UInt16 value, int base = 10 );
    HCC_EXPORT std::string ToAnsiString( Int32 value, int base = 10 );
    HCC_EXPORT std::string ToAnsiString( UInt32 value, int base = 10 );
    HCC_EXPORT std::string ToAnsiString( Int64 value, int base = 10 );
    HCC_EXPORT std::string ToAnsiString( UInt64 value, int base = 10 );
    HCC_EXPORT std::string ToAnsiString( Single value );
    HCC_EXPORT std::string ToAnsiString( Single value, const Locale& locale );
    HCC_EXPORT std::string ToAnsiString( Single value, int width, int precission );
    HCC_EXPORT std::string ToAnsiString( Single value, int width, int precission, const Locale& locale );
    HCC_EXPORT std::string ToAnsiString( Double value );
    HCC_EXPORT std::string ToAnsiString( const DateTime& value );
    HCC_EXPORT std::string ToAnsiString( const TimeSpan& value );
    HCC_EXPORT std::string ToAnsiString( const Guid& value );
    HCC_EXPORT std::string ToAnsiString( const Currency& value );
    HCC_EXPORT std::string ToAnsiString( const Variant& value );


    inline std::wstring Format( const wchar_t* fmt, ... )
    {
        va_list args;
        va_start( args, fmt );
        auto requiredLength = _vscwprintf( fmt, args );
        if ( requiredLength > 0 )
        {
            std::wstring result;
            result.resize( requiredLength );
            vswprintf_s( result.data( ), requiredLength+1, fmt, args );
            va_end( args );
            return result;
        }
        else
        {
            va_end( args );
            return {};
        }
    }

    inline std::wstring Format( const Locale& locale, const wchar_t* fmt, ... )
    {
        va_list args;
        va_start( args, fmt );
        auto requiredLength = _vscwprintf_l( fmt, locale, args );
        if ( requiredLength > 0 )
        {
            std::wstring result;
            result.resize( requiredLength );
            _vswprintf_p_l( result.data( ), requiredLength + 1, fmt, locale, args );
            va_end( args );
            return result;
        }
        else
        {
            va_end( args );
            return {};
        }
    }


    inline std::string Format( const char* fmt, ... )
    {
        va_list args;
        va_start( args, fmt );
        auto requiredLength = _vscprintf( fmt, args );
        if ( requiredLength > 0 )
        {
            std::string result;
            result.resize( requiredLength );
            vsprintf_s( result.data( ), requiredLength+1, fmt, args );
            va_end( args );
            return result;
        }
        else
        {
            va_end( args );
            return {};
        }
    }

    inline std::string Format( const Locale& locale, const char* fmt, ... )
    {
        va_list args;
        va_start( args, fmt );
        auto requiredLength = _vscprintf_l( fmt, locale, args );
        if ( requiredLength > 0 )
        {
            std::string result;
            result.resize( requiredLength );
            _vsprintf_p_l( result.data( ), requiredLength + 1, fmt, locale, args );
            va_end( args );
            return result;
        }
        else
        {
            va_end( args );
            return {};
        }
    }


    HCC_EXPORT bool ToBoolean( const wchar_t* str ) noexcept;
    HCC_EXPORT bool ToBoolean( const char* str ) noexcept;

    inline bool ToBoolean( const std::wstring& str ) noexcept
    {
        return ToBoolean( str.c_str() );
    }
    inline bool ToBoolean( const std::string& str ) noexcept
    {
        return ToBoolean( str.c_str( ) );
    }

    HCC_EXPORT Byte ToByte( const wchar_t* str, int radix = 10 );
    HCC_EXPORT Byte ToByte( const char* str, int radix = 10 );

    inline Byte ToByte( const std::wstring& str, int radix = 10 )
    {
        return ToByte( str.c_str( ), radix );
    }
    inline Byte ToByte( const std::string& str, int radix = 10 )
    {
        return ToByte( str.c_str( ), radix );
    }


    HCC_EXPORT SByte ToSByte( const wchar_t* str, int radix = 10 );
    HCC_EXPORT SByte ToSByte( const char* str, int radix = 10 );

    inline SByte ToSByte( const std::wstring& str, int radix = 10 )
    {
        return ToSByte( str.c_str( ), radix );
    }
    inline SByte ToSByte( const std::string& str, int radix = 10 )
    {
        return ToSByte( str.c_str( ), radix );
    }

    HCC_EXPORT Int16 ToInt16( const wchar_t* str, int radix = 10 );
    HCC_EXPORT Int16 ToInt16( const char* str, int radix = 10 );

    inline Int16 ToInt16( const std::wstring& str, int radix = 10 )
    {
        return ToInt16( str.c_str( ), radix );
    }
    inline Int16 ToInt16( const std::string& str, int radix = 10 )
    {
        return ToInt16( str.c_str( ), radix );
    }

    HCC_EXPORT UInt16 ToUInt16( const wchar_t* str, int radix = 10 );
    HCC_EXPORT UInt16 ToUInt16( const char* str, int radix = 10 );

    inline UInt16 ToUInt16( const std::wstring& str, int radix = 10 )
    {
        return ToUInt16( str.c_str( ), radix );
    }
    inline UInt16 ToUInt16( const std::string& str, int radix = 10 )
    {
        return ToUInt16( str.c_str( ), radix );
    }

    HCC_EXPORT Int32 ToInt32( const wchar_t* str, int radix = 10 );
    HCC_EXPORT Int32 ToInt32( const char* str, int radix = 10 );

    inline Int32 ToInt32( const std::wstring& str, int radix = 10 )
    {
        return ToInt32( str.c_str( ), radix );
    }
    inline Int32 ToInt32( const std::string& str, int radix = 10 )
    {
        return ToInt32( str.c_str( ), radix );
    }

    HCC_EXPORT UInt32 ToUInt32( const wchar_t* str, int radix = 10 );
    HCC_EXPORT UInt32 ToUInt32( const char* str, int radix = 10 );

    inline UInt32 ToUInt32( const std::wstring& str, int radix = 10 )
    {
        return ToUInt32( str.c_str( ), radix );
    }
    inline UInt32 ToUInt32( const std::string& str, int radix = 10 )
    {
        return ToUInt32( str.c_str( ), radix );
    }

    HCC_EXPORT Int64 ToInt64( const wchar_t* str, int radix = 10 );
    HCC_EXPORT Int64 ToInt64( const char* str, int radix = 10 );

    inline Int64 ToInt64( const std::wstring& str, int radix = 10 )
    {
        return ToInt64( str.c_str( ), radix );
    }
    inline Int64 ToInt64( const std::string& str, int radix = 10 )
    {
        return ToInt64( str.c_str( ), radix );
    }

    HCC_EXPORT UInt64 ToUInt64( const wchar_t* str, int radix = 10 );
    HCC_EXPORT UInt64 ToUInt64( const char* str, int radix = 10 );

    inline UInt64 ToUInt64( const std::wstring& str, int radix = 10 )
    {
        return ToUInt64( str.c_str( ), radix );
    }
    inline UInt64 ToUInt64( const std::string& str, int radix = 10 )
    {
        return ToUInt64( str.c_str( ), radix );
    }


    HCC_EXPORT Single ToSingle( const wchar_t* str );
    HCC_EXPORT Single ToSingle( const char* str );

    inline Single ToSingle( const std::wstring& str )
    {
        return ToSingle( str.c_str( ) );
    }
    inline Single ToSingle( const std::string& str )
    {
        return ToSingle( str.c_str( ) );
    }


    HCC_EXPORT Double ToDouble( const wchar_t* str );
    HCC_EXPORT Double ToDouble( const char* str );

    inline Double ToDouble( const std::wstring& str )
    {
        return ToDouble( str.c_str( ) );
    }
    inline Double ToDouble( const std::string& str )
    {
        return ToDouble( str.c_str( ) );
    }

    inline bool IsAlnum( wchar_t c )
    {
        return std::iswalnum( c );
    }
    inline bool IsAlnum( char c )
    {
        return std::isalnum( c );
    }
    inline bool IsAlpha( wchar_t c )
    {
        return std::iswalpha( c );
    }
    inline bool IsAlpha( char c )
    {
        return std::isalpha( c );
    }
    inline bool IsBlank( wchar_t c )
    {
        return std::iswblank( c );
    }
    inline bool IsBlank( char c )
    {
        return std::isblank( c );
    }
    inline bool IsCntrl( wchar_t c )
    {
        return std::iswcntrl( c );
    }
    inline bool IsCntrl( char c )
    {
        return std::iscntrl( c );
    }
    inline bool IsDigit( wchar_t c )
    {
        return std::iswdigit( c );
    }
    inline bool IsDigit( char c )
    {
        return std::isdigit( c );
    }
    inline bool IsGraph( wchar_t c )
    {
        return std::iswgraph( c );
    }
    inline bool IsGraph( char c )
    {
        return std::isgraph( c );
    }
    inline bool IsLower( wchar_t c )
    {
        return std::iswlower( c );
    }
    inline bool IsLower( char c )
    {
        return std::islower( c );
    }
    inline bool IsPrint( wchar_t c )
    {
        return std::iswprint( c );
    }
    inline bool IsPrint( char c )
    {
        return std::isprint( c );
    }
    inline bool IsPunct( wchar_t c )
    {
        return std::iswpunct( c );
    }
    inline bool IsPunct( char c )
    {
        return std::ispunct( c );
    }
    inline bool IsSpace( wchar_t c )
    {
        return std::iswspace( c );
    }
    inline bool IsSpace( char c )
    {
        return std::isspace( c );
    }
    inline bool IsUpper( wchar_t c )
    {
        return std::iswupper( c );
    }
    inline bool IsUpper( char c )
    {
        return std::isupper( c );
    }
    inline bool IsXDigit( wchar_t c )
    {
        return std::iswxdigit( c );
    }
    inline bool IsXDigit( char c )
    {
        return std::isxdigit( c );
    }

    template<typename T>
        requires ( IsStdBasicString<T> || IsStdBasicStringView<T> )
    inline T TrimTrailing( const T& str, bool( testFunction )(typename T::value_type c)  )
    {
        using StringType = T;
        using CharType = StringType::value_type;
        auto begin = str.begin( );
        auto end = str.end( );
        while ( end > begin )
        {
            --end;
            CharType c = *end;
            if ( testFunction( c ) == false )
            {
                ++end;
                break;
            }
        }
        return StringType( begin, end );
    }

    template<typename T >
        requires ( IsStdBasicString<T> || IsStdBasicStringView<T> )
    inline T TrimTrailing( const T& str )
    {
        return TrimTrailing<T>( str, IsSpace );
    }

    template<typename T>
        requires ( IsStdBasicString<T> || IsStdBasicStringView<T> )
    inline T Trim( const T& str, bool( testFunction )(typename T::value_type c)  )
    {
        using StringType = T;
        using CharType = StringType::value_type;
        auto begin = str.begin( );
        auto end = str.end( );

        while ( begin < end )
        {
            CharType c = *begin;
            if ( testFunction( c ) == false )
            {
                break;
            }
            ++begin;
        }
        if ( begin < end )
        {
            while ( end > begin )
            {
                --end;
                CharType c = *end;
                if ( testFunction( c ) == false )
                {
                    ++end;
                    break;
                }
            }
        }
        return StringType( begin, end );
    }

    template<typename T >
        requires ( IsStdBasicString<T> || IsStdBasicStringView<T> )
    inline T Trim( const T& str )
    {
        return Trim<T>( str, IsSpace );
    }


    template<typename T>
        requires ( IsStdBasicString<T> || IsStdBasicStringView<T> )
    inline T TrimLeading( const T& str, bool( testFunction )(typename T::value_type c)  )
    {
        using StringType = T;
        using CharType = StringType::value_type;
        auto begin = str.begin( );
        auto end = str.end( );

        while ( begin < end )
        {
            CharType c = *begin;
            if ( testFunction( c ) == false )
            {
                break;
            }
            ++begin;
        }
        return StringType( begin, end );
    }

    template<typename T >
        requires ( IsStdBasicString<T> || IsStdBasicStringView<T> )
    inline T TrimLeading( const T& str )
    {
        return TrimLeading<T>( str, IsSpace );
    }

    template<typename T >
        requires IsStdBasicString<T> 
    inline T Strip( const T& str, bool( testFunction )( typename T::value_type c ) )
    {
        using StringType = T;
        using CharType = StringType::value_type;
        auto begin = str.begin( );
        auto end = str.end( );
        StringType result;
        result.reserve( str.size() );
        while ( begin < end )
        {
            CharType c = *begin;
            if ( testFunction( c ) == false )
            {
                result += c;
            }
            ++begin;
        }
        return result;
    }

    inline char ToLower( char c )
    {
        return static_cast<char>( std::tolower( c ) );
    }

    inline wchar_t ToLower( wchar_t c )
    {
        return static_cast<wchar_t>( std::towlower( c ) );
    }

    inline char ToUpper( char c )
    {
        return static_cast<char>( std::toupper( c ) );
    }

    inline wchar_t ToUpper( wchar_t c )
    {
        return static_cast<wchar_t>(std::towupper( c ));
    }


    template<typename T >
        requires IsStdBasicString<T> 
    inline T ToLower( const T& str )
    {
        using StringType = T;
        using CharType = StringType::value_type;
        auto begin = str.begin( );
        auto end = str.end( );
        StringType result;
        result.reserve( str.size() );
        while ( begin < end )
        {
            CharType c = *begin;
            if ( IsUpper( c ) == false )
            {
                result += c;
            }
            else
            {
                result += ToLower( c );
            }
            ++begin;
        }
        return result;
    }

    template<typename T >
        requires IsStdBasicString<T> 
    inline T ToUpper( const T& str )
    {
        using StringType = T;
        using CharType = StringType::value_type;
        auto begin = str.begin( );
        auto end = str.end( );
        StringType result;
        result.reserve( str.size() );
        while ( begin < end )
        {
            CharType c = *begin;
            if ( IsLower( c ) == false )
            {
                result += c;
            }
            else
            {
                result += ToUpper( c );
            }
            ++begin;
        }
        return result;
    }



#pragma pack(push,1)
    template <typename SizeT,typename CharT, size_t maxSize, bool zeroTerminated >
    class BasicFixedString
    {
    public:
        using SizeType = SizeT;
        using CharType = CharT;
        static constexpr size_t MaxSize = maxSize;
        static constexpr bool ZeroTerminated = zeroTerminated;
        static constexpr size_t ArraySize = maxSize + (ZeroTerminated ? 1 : 0);
        using ArrayType = std::array<CharType, ArraySize>;
        using ViewType = std::basic_string_view<CharType>;
        using SpanType = std::span<CharType>;

        using iterator = typename ArrayType::iterator;
        using const_iterator = typename ArrayType::const_iterator;
    private:
        SizeType size_;
        ArrayType data_;
    public:
        constexpr BasicFixedString() noexcept
            : size_( 0 ), data_{}
        {}

        constexpr BasicFixedString(const CharType* str, size_t strLength )
            : size_( static_cast<SizeType>(strLength) ), data_{}
        {
            std::copy( str, str + strLength, data_.begin( ) );
        }

        BasicFixedString( const CharType* str )
            : BasicFixedString( str, LengthOf( str ) )
        {
        }

        template<typename T>
            requires ( IsSpecializationOf<T, std::basic_string>&& std::is_same_v<typename T::value_type, CharType> )
        BasicFixedString( const T& str )
            : BasicFixedString( str.c_str(), str.length() )
        {
        }

        template<typename T>
            requires ( IsSpecializationOf<T, std::basic_string_view>&& std::is_same_v<typename T::value_type, CharType> )
        BasicFixedString( const T& str )
            : BasicFixedString( str.data(), str.length() )
        {
        }

        constexpr BasicFixedString( size_t count, CharType val )
            : size_( static_cast<SizeType>( count ) ), data_{}
        {
            std::fill( data_.begin( ), data_.begin( )+count, val );
        }

        constexpr const CharType* c_str( ) const noexcept
        {
            return data_.data( );
        }
        constexpr const CharType* data( ) const noexcept
        {
            return data_.data( );
        }
        constexpr CharType* data( ) noexcept
        {
            return data_.data( );
        }

        constexpr size_t length( ) const noexcept
        {
            return static_cast<size_t>(size_);
        }

        constexpr iterator begin( ) noexcept
        {
            data_.begin( );
        }
        constexpr iterator end( ) noexcept
        {
            data_.begin( ) + length( );
        }
        constexpr const_iterator begin( ) const noexcept
        {
            data_.begin( );
        }
        constexpr const_iterator end( ) const noexcept
        {
            data_.begin( ) + length( );
        }

        constexpr CharType& operator[]( size_t index ) const noexcept
        {
            return data_[index];
        }
        constexpr CharType& operator[]( size_t index ) noexcept
        {
            return data_[index];
        }
        constexpr CharType& at( size_t index ) const noexcept
        {
            return data_[index];
        }
        constexpr CharType& at( size_t index ) noexcept
        {
            return data_[index];
        }

        constexpr CharType& front( ) const noexcept
        {
            return data_[0];
        }
        constexpr CharType& front( ) noexcept
        {
            return data_[0];
        }
        constexpr CharType& back( ) const noexcept
        {
            return data_[size_ - 1];
        }
        constexpr CharType& back( ) noexcept
        {
            return data_[size_ - 1];
        }

        template<typename T>
            requires (IsSpecializationOf<T, std::basic_string> && std::is_same_v<typename T::value_type,CharType> )
        BasicFixedString& operator = ( const T& other )
        {
            std::copy( other.begin(),other.end(), data_.data() );
            size_ = other.length( );
            data_[size_] = static_cast<CharType>( 0 );
            return *this;
        }

        template<typename T>
            requires (IsSpecializationOf<T, std::basic_string_view> && std::is_same_v<typename T::value_type,CharType> )
        BasicFixedString& operator = ( const T& other )
        {
            std::copy( other.begin(),other.end(), data_.data() );
            size_ = other.length( );
            data_[size_] = static_cast<CharType>( 0 );
            return *this;
        }

        BasicFixedString& operator = ( const CharType* str )
        {
            size_t len = LengthOf( str );
            std::copy( str, str + len, data_.data( ) );
            size_ = len;
            data_[size_] = static_cast<CharType>( 0 );
            return *this;
        }


        constexpr const ViewType View( ) const noexcept
        {
            return ViewType( data_.data( ), size_ );
        }
        constexpr ViewType View( ) noexcept
        {
            return ViewType( data_.data( ), size_ );
        }
        constexpr const SpanType Span( ) const noexcept
        {
            return SpanType( data_.data( ), size_ );
        }
        constexpr SpanType Span( ) noexcept
        {
            return SpanType( data_.data( ), size_ );
        }

        size_t Hash( ) const noexcept
        {
            if ( size_ )
            {
                return XXH3_64bits( data_.data( ), size_ * sizeof( CharType ) );
            }
            else
            {
                return 0;
            }
        }
    };

#pragma pack(pop)

    template <typename SizeT, size_t maxSize>
    using FixedWideString = BasicFixedString<SizeT, wchar_t, maxSize,false>;


    template <typename SizeT, size_t maxSize>
    using FixedString = BasicFixedString<SizeT, char, maxSize, false>;
    template <typename SizeT, size_t maxSize>
    using FixedWideZString = BasicFixedString<SizeT, wchar_t, maxSize, true>;
    template <typename SizeT, size_t maxSize>
    using FixedZString = BasicFixedString<SizeT, char, maxSize, true>;






#ifdef HCC_WITH_BASIC_STRING
    namespace Internal
    {
        HCC_EXPORT char* AllocateBytes( size_t count );
        HCC_EXPORT void FreeBytes( char* bytes, size_t size );
        HCC_EXPORT void ResetStringFixedSizeMemoryManager( );

        
        inline void Copy( char* dest, const char* source, size_t length ) noexcept
        {
            memcpy( dest, source, length );
        }
        inline void Copy( wchar_t* dest, const wchar_t* source, size_t length ) noexcept
        {
            wmemcpy( dest, source, length );
        }

        inline void Move( char* dest, const char* source, size_t length ) noexcept
        {
            memmove( dest, source, length );
        }
        inline void Move( wchar_t* dest, const wchar_t* source, size_t length ) noexcept
        {
            wmemmove( dest, source, length );
        }

        inline void Set( char* dest, char value, size_t length ) noexcept
        {
            memset( dest, value, length );
        }
        inline void Set( wchar_t* dest, wchar_t value, size_t length ) noexcept
        {
            wmemset( dest, value, length );
        }

        inline int Compare( DWORD compareFlags, const char* first, int firstLength, const char* second, int secondLength )
        {
            if ( first && second )
            {
                auto result = CompareStringA( LOCALE_USER_DEFAULT, compareFlags, first, firstLength, second, secondLength );
                if ( !result )
                {
                    ThrowLastOSError( );
                }
                return result - 2;
            }
            else if ( first )
            {
                return 1;
            }
            else if ( second )
            {
                return -1;
            }
            return 0;
        }

        inline int Compare( DWORD compareFlags, const wchar_t* first, int firstLength, const wchar_t* second, int secondLength )
        {
            if ( first && second )
            {
                auto result = CompareStringW( LOCALE_USER_DEFAULT, compareFlags, first, static_cast<int>( firstLength ), second, static_cast<int>( secondLength ) );
                if ( !result )
                {
                    ThrowLastOSError( );
                }
                return result - 2;
            }
            else if ( first )
            {
                return 1;
            }
            else if ( second )
            {
                return -1;
            }
            return 0;
        }


        inline int Compare( const char* first, size_t firstLength, const char* second, size_t secondLength )
        {
            return Compare( 0, first, static_cast<int>( firstLength ), second, static_cast<int>( secondLength ) );
        }

        inline int Compare( const wchar_t* first, size_t firstLength, const wchar_t* second, size_t secondLength )
        {
            return Compare( 0, first, static_cast<int>( firstLength ), second, static_cast<int>( secondLength ) );
        }

        inline int Compare( const char* first, size_t firstLength, const char* second )
        {
            return Compare( 0, first, static_cast<int>( firstLength ), second, -1 );
        }

        inline int Compare( const wchar_t* first, size_t firstLength, const wchar_t* second )
        {
            return Compare( 0, first, static_cast<int>( firstLength ), second, -1 );
        }

        inline int Compare( const char* first, const char* second, size_t secondLength )
        {
            return Compare( 0, first, -1, second, static_cast<int>( secondLength ) );
        }

        inline int Compare( const wchar_t* first, const wchar_t* second, size_t secondLength )
        {
            return Compare( 0, first, -1, second, static_cast<int>( secondLength ) );
        }


        inline int Compare( const char* first, const char* second )
        {
            return Compare( 0, first, -1, second, -1 );
        }
        inline int Compare( const wchar_t* first, const wchar_t* second )
        {
            return Compare( 0, first, -1, second, -1 );
        }

        inline int ICompare( const char* first, size_t firstLength, const char* second, size_t secondLength )
        {
            return Compare( NORM_IGNORECASE, first, static_cast<int>( firstLength ), second, static_cast<int>( secondLength ) );
        }

        inline int ICompare( const wchar_t* first, size_t firstLength, const wchar_t* second, size_t secondLength )
        {
            return Compare( NORM_IGNORECASE, first, static_cast<int>( firstLength ), second, static_cast<int>( secondLength ) );
        }

        inline int ICompare( const char* first, size_t firstLength, const char* second )
        {
            return Compare( NORM_IGNORECASE, first, static_cast<int>( firstLength ), second, -1 );
        }

        inline int ICompare( const wchar_t* first, size_t firstLength, const wchar_t* second )
        {
            return Compare( NORM_IGNORECASE, first, static_cast<int>( firstLength ), second, -1 );
        }

        inline int ICompare( const char* first, const char* second, size_t secondLength )
        {
            return Compare( NORM_IGNORECASE, first, -1, second, static_cast<int>( secondLength ) );
        }

        inline int ICompare( const wchar_t* first, const wchar_t* second, size_t secondLength )
        {
            return Compare( NORM_IGNORECASE, first, -1, second, static_cast<int>( secondLength ) );
        }


        inline int ICompare( const char* first, const char* second )
        {
            return Compare( NORM_IGNORECASE, first, -1, second, -1 );
        }
        inline int ICompare( const wchar_t* first, const wchar_t* second )
        {
            return Compare( NORM_IGNORECASE, first, -1, second, -1 );
        }


        inline char* MemChr( char* buffer, int value, size_t bufferSize ) noexcept
        {
            return (char*)memchr( buffer, value, bufferSize );
        }
        inline const char* MemChr( const char* buffer, int value, size_t bufferSize ) noexcept
        {
            return (const char*)memchr( buffer, value, bufferSize );
        }
        inline wchar_t* MemChr( wchar_t* buffer, int value, size_t bufferSize ) noexcept
        {
            return (wchar_t*)wmemchr( buffer, value, bufferSize );
        }
        inline const wchar_t* MemChr( const wchar_t* buffer, int value, size_t bufferSize ) noexcept
        {
            return (const wchar_t*)wmemchr( buffer, value, bufferSize );
        }




        inline char ToUpper( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:4302)
            return (char)CharUpperA( ( (LPSTR)( c ) ) );
#pragma warning(pop)
        }
        inline wchar_t ToUpper( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:4302)
            return (wchar_t)CharUpperW( ( (LPWSTR)( c ) ) );
#pragma warning(pop)
        }
        inline char ToLower( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:4302)
            return (char)CharLowerA( ( (LPSTR)( c ) ) );
#pragma warning(pop)
        }
        inline wchar_t ToLower( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:4302)
            return (wchar_t)CharLowerW( ( (LPWSTR)( c ) ) );
#pragma warning(pop)
        }

        inline void ToUpper( char* s )
        {
            CharUpperA( s );
        }

        inline void ToUpper( wchar_t* s )
        {
            CharUpperW( s );
        }

        inline void ToLower( char* s )
        {
            CharLowerA( s );
        }

        inline void ToLower( wchar_t* s )
        {
            CharLowerW( s );
        }

        inline void ToUpper( char* s, size_t size )
        {
            CharUpperBuffA( s, static_cast<DWORD>( size ) );
        }

        inline void ToUpper( wchar_t* s, size_t size )
        {
            CharUpperBuffW( s, static_cast<DWORD>( size ) );
        }

        inline void ToLower( char* s, size_t size )
        {
            CharLowerBuffA( s, static_cast<DWORD>( size ) );
        }

        inline void ToLower( wchar_t* s, size_t size )
        {
            CharLowerBuffW( s, static_cast<DWORD>( size ) );
        }




        inline char* MemIChr( char* buffer, int value, size_t bufferSize ) noexcept
        {
            auto lowerValue = ToLower( static_cast<char>( value ) );
            auto* result = (char*)memchr( buffer, lowerValue, bufferSize );
            if ( !result )
            {
                auto upperValue = ToUpper( static_cast<char>( value ) );
                result = (char*)memchr( buffer, upperValue, bufferSize );
            }
            return result;
        }
        inline const char* MemIChr( const char* buffer, int value, size_t bufferSize ) noexcept
        {
            auto lowerValue = ToLower( static_cast<char>( value ) );
            auto* result = (const char*)memchr( buffer, lowerValue, bufferSize );
            if ( !result )
            {
                auto upperValue = ToUpper( static_cast<char>( value ) );
                result = (const char*)memchr( buffer, upperValue, bufferSize );
            }
            return result;
        }
        inline wchar_t* MemIChr( wchar_t* buffer, int value, size_t bufferSize ) noexcept
        {
            auto lowerValue = ToLower( static_cast<wchar_t>( value ) );
            auto* result = (wchar_t*)wmemchr( buffer, lowerValue, bufferSize );
            if ( !result )
            {
                auto upperValue = ToUpper( static_cast<wchar_t>( value ) );
                result = (wchar_t*)wmemchr( buffer, upperValue, bufferSize );
            }
            return result;
        }
        inline const wchar_t* MemIChr( const wchar_t* buffer, int value, size_t bufferSize ) noexcept
        {
            auto lowerValue = ToLower( static_cast<wchar_t>( value ) );
            auto* result = (const wchar_t*)wmemchr( buffer, lowerValue, bufferSize );
            if ( !result )
            {
                auto upperValue = ToUpper( static_cast<wchar_t>( value ) );
                result = (const wchar_t*)wmemchr( buffer, upperValue, bufferSize );
            }
            return result;
        }



        inline int BufferSizeForFormat( const char* fmt, va_list argPtr ) noexcept
        {
            return _vscprintf( fmt, argPtr );
        }
        inline int BufferSizeForFormat( const wchar_t* fmt, va_list argPtr ) noexcept
        {
            return _vscwprintf( fmt, argPtr );
        }

        inline int Format( char* destination, size_t destinationSize, const char* fmt, va_list argPtr ) noexcept
        {
            return vsprintf_s( destination, destinationSize, fmt, argPtr );
        }
        inline int Format( wchar_t* destination, size_t destinationSize, const wchar_t* fmt, va_list argPtr ) noexcept
        {
            return vswprintf_s( destination, destinationSize, fmt, argPtr );
        }

        inline bool IsSpace( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return isspace( c );
#pragma warning(pop)
        }
        inline bool IsSpace( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswspace( c );
#pragma warning(pop)
        }


        inline bool IsControl( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iscntrl( c );
#pragma warning(pop)
        }
        inline bool IsControl( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswcntrl( c );
#pragma warning(pop)
        }

        inline bool IsDigit( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return isdigit( c );
#pragma warning(pop)
        }
        inline bool IsDigit( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswdigit( c );
#pragma warning(pop)
        }

        inline bool IsLetter( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return isalpha( c );
#pragma warning(pop)
        }
        inline bool IsLetter( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswalpha( c );
#pragma warning(pop)
        }

        inline bool IsLetterOrDigit( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return isalnum( c );
#pragma warning(pop)
        }
        inline bool IsLetterOrDigit( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswalnum( c );
#pragma warning(pop)
        }


        inline bool IsLower( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return islower( c );
#pragma warning(pop)
        }
        inline bool IsLower( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswlower( c );
#pragma warning(pop)
        }


        inline bool IsUpper( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return isupper( c );
#pragma warning(pop)
        }
        inline bool IsUpper( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswupper( c );
#pragma warning(pop)
        }

        inline bool IsPunctuation( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return ispunct( c );
#pragma warning(pop)
        }
        inline bool IsPunctuation( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return iswpunct( c );
#pragma warning(pop)
        }

        inline bool IsWhiteSpace( char c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return isspace( c );
#pragma warning(pop)
        }
        inline bool IsWhiteSpace( wchar_t c ) noexcept
        {
#pragma warning(push)
#pragma warning(disable:6330)
            return isspace( c );
#pragma warning(pop)
        }



        template< typename T >
        struct Data
        {
            using CharType = T;
            size_t referenceCount_;
            size_t size_;
            CharType buffer_[1024];

            size_t AddRef( )
            {
                return InterlockedIncrementSizeT( &referenceCount_ );
            }

            size_t DecRef( )
            {
                return InterlockedDecrementSizeT( &referenceCount_ );
            }

        };


        HCC_EXPORT WideString From( const char* text, size_t textLength, unsigned codePage = CP_ACP, unsigned flags = 0 );
        HCC_EXPORT AnsiString From( const wchar_t* text, size_t textLength, unsigned codePage = CP_ACP, unsigned flags = 0 );

    }

    template<typename T>
    class BasicString
    {
    public:
        using CharType = T;
        using iterator = CharType*;
        using const_iterator = const CharType*;
        using reference = CharType&;
        using const_reference = const CharType&;
        using size_type = size_t;
        using value_type = T;

        static constexpr size_type npos = MAXUINT64;
        static constexpr size_type AllocationGranularity = 64;
    private:
        using Data = Internal::Data<CharType>;

        Data* data_;

        static constexpr size_t BufferHeaderSize = offsetof( Data, buffer_ );
        static constexpr size_type NonTextBufferByteCount = BufferHeaderSize + sizeof( CharType );

        static constexpr size_type AllocationByteCount( size_type length ) noexcept
        {
            return length ? ( ( NonTextBufferByteCount + length * sizeof( CharType ) ) + ( AllocationGranularity - 1 ) ) & ~( AllocationGranularity - 1 ) : 0;
        }
        static constexpr size_type AllocationByteCountForLengthNotZero( size_type length ) noexcept
        {
            return ( ( NonTextBufferByteCount + length * sizeof( CharType ) ) + ( AllocationGranularity - 1 ) ) & ~( AllocationGranularity - 1 );
        }


        static Data* Allocate( size_t size )
        {
            size_t allocationByteCount = AllocationByteCount( size );
            Data* data = (Data*)Internal::AllocateBytes( allocationByteCount );
            data->referenceCount_ = 1;
            data->size_ = size;
            data->buffer_[size] = 0;
            return data;
        }

        static void Release( Data* data )
        {
            if ( data && data->DecRef( ) == 0 )
            {
                size_t allocationByteCount = AllocationByteCountForLengthNotZero( data->size_ );
                Internal::FreeBytes( (char*)data, allocationByteCount );
            }
        }


        CharType* ExpandIntoNewBuffer( size_t offset, size_t expandSize )
        {
            auto currentSize = data_->size_;
            auto newSize = currentSize + expandSize;
            auto newData = Allocate( newSize );
            Internal::Copy( newData->buffer_, data_->buffer_, offset );
            auto remaining = currentSize - offset;
            Internal::Copy( &newData->buffer_[offset + expandSize], &data_->buffer_[offset], remaining );
            auto* tmp = data_;
            data_ = newData;
            Release( tmp );
            return &newData->buffer_[offset];
        }

        CharType* ExpandCurrentBuffer( size_t offset, size_t expandSize )
        {
            auto currentSize = data_->size_;
            auto remaining = currentSize - offset;
            Internal::Move( &data_->buffer_[offset + expandSize], &data_->buffer_[offset], remaining );
            data_->size_ += expandSize;
            data_->buffer_[data_->size_] = 0;
            return &data_->buffer_[offset];
        }


        CharType* Expand( size_t offset, size_t expandSize )
        {
            if ( data_ )
            {
                if ( data_->referenceCount_ > 1 )
                {
                    return ExpandIntoNewBuffer( offset, expandSize );
                }
                else
                {
                    auto currentSize = data_->size_;
                    auto newSize = currentSize + expandSize;
                    auto currentBufferSize = AllocationByteCountForLengthNotZero( currentSize );
                    auto newBufferSize = AllocationByteCountForLengthNotZero( newSize );
                    if ( currentBufferSize == newBufferSize )
                    {
                        return ExpandCurrentBuffer( offset, expandSize );
                    }
                    else
                    {
                        return ExpandIntoNewBuffer( offset, expandSize );
                    }

                }
            }
            else
            {
                data_ = Allocate( expandSize );
                return data_->buffer_;
            }
        }

        CharType* ExtendIntoNewBuffer( size_t extendSize )
        {
            auto currentSize = data_->size_;
            auto newSize = currentSize + extendSize;
            auto newData = Allocate( newSize );
            Internal::Copy( newData->buffer_, data_->buffer_, currentSize );
            auto* tmp = data_;
            data_ = newData;
            Release( tmp );
            return &newData->buffer_[currentSize];
        }

        CharType* ExtendCurrentBuffer( size_t extendSize )
        {
            auto currentSize = data_->size_;
            data_->size_ += extendSize;
            data_->buffer_[data_->size_] = 0;
            return &data_->buffer_[currentSize];
        }

        CharType* Extend( size_t extendSize )
        {
            if ( data_ )
            {
                if ( data_->referenceCount_ > 1 )
                {
                    return ExtendIntoNewBuffer( extendSize );
                }
                else
                {
                    auto currentSize = data_->size_;
                    auto newSize = currentSize + extendSize;
                    auto currentBufferSize = AllocationByteCountForLengthNotZero( currentSize );
                    auto newBufferSize = AllocationByteCountForLengthNotZero( newSize );
                    if ( currentBufferSize == newBufferSize )
                    {
                        return ExtendCurrentBuffer( extendSize );
                    }
                    else
                    {
                        return ExtendIntoNewBuffer( extendSize );
                    }

                }
            }
            else
            {
                data_ = Allocate( extendSize );
                return data_->buffer_;
            }
        }



        CharType* Erase( size_t offset, size_t numberOfCharactersToErase )
        {
            if ( data_ )
            {
                auto currentSize = data_->size_;

                if ( offset < currentSize )
                {
                    if ( ( offset + numberOfCharactersToErase ) > currentSize )
                    {
                        numberOfCharactersToErase = currentSize - offset;
                    }
                    size_t newSize = currentSize - numberOfCharactersToErase;
                    if ( newSize )
                    {
                        auto currentBufferSize = AllocationByteCountForLengthNotZero( currentSize );
                        auto newBufferSize = AllocationByteCountForLengthNotZero( newSize );

                        if ( ( data_->referenceCount_ == 1 ) && ( currentBufferSize == newBufferSize ) )
                        {
                            size_t remainingSize = currentSize - ( offset + numberOfCharactersToErase );
                            if ( remainingSize )
                            {
                                auto* dest = &data_->buffer_[offset];
                                Internal::Copy( dest, dest + numberOfCharactersToErase, remainingSize );
                            }
                            data_->buffer_[newSize] = 0;
                            data_->size_ = newSize;
                        }
                        else
                        {
                            auto* newData = Allocate( newSize );
                            if ( offset )
                            {
                                Internal::Copy( newData->buffer_, data_->buffer_, offset );
                            }
                            size_t remainingSize = currentSize - ( offset + numberOfCharactersToErase );
                            if ( remainingSize )
                            {
                                Internal::Copy( &newData->buffer_[offset], &data_->buffer_[offset + numberOfCharactersToErase], remainingSize );
                            }
                            Release( data_ );
                            data_ = newData;
                        }
                        return &data_->buffer_[offset];

                    }
                    else
                    {
                        Release( data_ );
                        data_ = nullptr;
                    }
                }
            }
            return nullptr;
        }


        static Data* Initialize( const CharType* string, size_type size )
        {
            if ( size )
            {
                Data* data = Allocate( size );
                Internal::Copy( data->buffer_, string, size );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        static Data* Initialize( const CharType* string )
        {
            auto size = Internal::LengthOf( string );
            return Initialize( string, size );
        }

        static Data* Initialize( size_type count, CharType value )
        {
            if ( count )
            {
                Data* data = Allocate( count );
                Internal::Set( data->buffer_, value, count );
                return data;
            }
            else
            {
                return nullptr;
            }
        }

        BasicString( Data* data ) noexcept
            : data_( data )
        {
        }
    public:
        constexpr BasicString( ) noexcept
            : data_( nullptr )
        {
        }

        BasicString( const CharType* string )
            : data_( Initialize( string ) )
        {
        }

        BasicString( const CharType* string, size_type size )
            : data_( Initialize( string, size ) )
        {
        }

        BasicString( const BasicStringView<T>& v );


        BasicString( size_type count, CharType value )
            : data_( Initialize( count, value ) )
        {
        }


        BasicString( const BasicString& other )
            : data_( other.data_ )
        {
            if ( data_ )
            {
                data_->AddRef( );
            }
        }

        BasicString( BasicString&& other )
            : data_( other.data_ )
        {
            other.data_ = nullptr;
        }


        ~BasicString( )
        {
            if ( data_ )
            {
                Release( data_ );
            }
        }


        static BasicString From( const WideString& s )
            requires std::is_same_v<CharType, char>
        {
            return Internal::From( s.data( ), s.Length( ) );
        }
        static BasicString From( const std::wstring& s )
            requires std::is_same_v<CharType, char>
        {
            return Internal::From( s.data( ), s.size( ) );
        }
        static BasicString From( const wchar_t* s )
            requires std::is_same_v<CharType, char>
        {
            return Internal::From( s, Internal::LengthOf( s ) );
        }
        static BasicString From( const char* s )
            requires std::is_same_v<CharType, char>
        {
            return BasicString( s, Internal::LengthOf( s ) );
        }


        static BasicString From( const AnsiString& s )
            requires std::is_same_v<CharType, char>
        {
            return s;
        }
        static BasicString From( const std::string& s )
            requires std::is_same_v<CharType, char>
        {
            return BasicString( s.data( ), s.size( ) );
        }


        static BasicString From( const AnsiString& s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return Internal::From( s.data( ), s.Length( ) );
        }
        static BasicString From( const std::string& s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return Internal::From( s.data( ), s.size( ) );
        }

        static BasicString From( const WideString& s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return s;
        }
        static BasicString From( const std::wstring& s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return BasicString( s.data( ), s.size( ) );
        }

        static BasicString From( const wchar_t* s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return BasicString( s, Internal::LengthOf( s ) );
        }
        static BasicString From( const char* s )
            requires std::is_same_v<CharType, wchar_t>
        {
            return Internal::From( s, Internal::LengthOf( s ) );
        }




        BasicString& operator = ( const BasicString& other )
        {
            if ( other.data_ != data_ )
            {
                if ( data_ )
                {
                    Release( data_ );
                }
                data_ = other.data_;
                if ( data_ )
                {
                    data_->AddRef( );
                }
            }
            return *this;
        }

        BasicString& operator = ( BasicString&& other )
        {
            if ( other.data_ != data_ )
            {
                if ( data_ )
                {
                    Release( data_ );
                }
                data_ = other.data_;
                other.data_ = nullptr;
            }
            return *this;
        }


        static BasicString<CharType> Format( const CharType* fmt, ... )
        {
            va_list args;
            va_start( args, fmt );
            int length = Internal::BufferSizeForFormat( fmt, args );

            if ( length < 0 )
            {
                throw ArgumentException( L"fmt" );
            }

            BasicString<CharType> result( size_type( length ), '\x0' );
            Internal::Format( result.data( ), length + 1, fmt, args );
            va_end( args );
            return result;
        }

        static BasicString<CharType> FormatV( const CharType* fmt, va_list args )
        {
            int length = Internal::BufferSizeForFormat( fmt, args );

            if ( length < 0 )
            {
                throw ArgumentException( L"fmt" );
            }

            BasicString<CharType> result( size_type( length ), '\x0' );
            Internal::Format( result.data( ), length + 1, fmt, args );
            return result;
        }



        constexpr const CharType* c_str( ) const noexcept
        {
            if constexpr ( std::is_same_v<CharType, char> )
            {
                return data_ ? data_->buffer_ : "";
            }
            else
            {
                return data_ ? data_->buffer_ : L"";
            }
        }

        constexpr const CharType* data( ) const noexcept
        {
            return data_ ? data_->buffer_ : nullptr;
        }

        constexpr CharType* data( ) noexcept
        {
            return data_ ? data_->buffer_ : nullptr;
        }

        size_t Hash( ) const noexcept
        {
            if ( data_ )
            {
                return XXH3_64bits( data_->buffer_, data_->size_ * sizeof( CharType ) );
            }
            else
            {
                return 0;
            }
        }


        constexpr iterator begin( ) noexcept
        {
            return data_ ? data_->buffer_ : nullptr;
        }

        constexpr iterator end( ) noexcept
        {
            return data_ ? &data_->buffer_[data_->size_] : nullptr;
        }

        constexpr const_iterator begin( ) const noexcept
        {
            return data_ ? data_->buffer_ : nullptr;
        }

        constexpr const_iterator end( ) const noexcept
        {
            return data_ ? &data_->buffer_[data_->size_] : nullptr;
        }


        constexpr size_type size( ) const noexcept
        {
            return data_ ? data_->size_ : 0;
        }

        constexpr size_type length( ) const noexcept
        {
            return size( );
        }
        constexpr size_type Length( ) const noexcept
        {
            return size( );
        }

        void SetLength( size_type newLength )
        {
            if ( data_ )
            {
                if ( newLength )
                {
                    if ( data_->referenceCount_ > 1 )
                    {
                        auto tmp = data_;
                        data_ = Allocate( newLength );
                        auto copyLength = std::min( newLength, tmp->size_ );
                        Internal::Copy( data_->buffer_, tmp->buffer_, copyLength );
                        Release( tmp );
                    }
                    else
                    {
                        auto currentSize = data_->size_;
                        auto currentByteCount = AllocationByteCountForLengthNotZero( currentSize );
                        auto newByteCount = AllocationByteCountForLengthNotZero( newLength );
                        if ( currentByteCount == newByteCount )
                        {
                            data_->size_ = newLength;
                            data_->buffer_[newLength] = 0;
                        }
                        else
                        {
                            auto tmp = data_;
                            data_ = Allocate( newLength );
                            auto copyLength = std::min( newLength, tmp->size_ );
                            Internal::Copy( data_->buffer_, tmp->buffer_, copyLength );
                            Release( tmp );
                        }
                    }
                }
                else
                {
                    Release( data_ );
                    data_ = nullptr;
                }
            }
            else if ( newLength )
            {
                data_ = Allocate( newLength );
            }
        }


        constexpr bool empty( ) const noexcept
        {
            return data_ ? data_->size_ == 0 : true;
        }

        constexpr bool IsEmpty( ) const noexcept
        {
            return empty( );
        }


        constexpr explicit operator bool( ) const
        {
            return empty( ) == false;
        }


        reference operator[]( size_type offset ) noexcept
        {
            return data_->buffer_[offset];
        }
        const_reference operator[]( size_type offset ) const noexcept
        {
            return data_->buffer_[offset];
        }


        static BasicString<CharType> Combine( const CharType* first, size_t firstLength, const CharType* second, size_t secondLength )
        {
            auto sz = firstLength + secondLength;
            if ( sz )
            {
                auto* data = Allocate( sz );
                if ( firstLength )
                {
                    Internal::Copy( data->buffer_, first, firstLength );
                    if ( secondLength )
                    {
                        Internal::Copy( &data->buffer_[firstLength], second, secondLength );
                    }
                }
                else
                {
                    Internal::Copy( data->buffer_, second, secondLength );
                }
                return BasicString<CharType>( data );
            }
            else
            {
                return BasicString<CharType>( );
            }
        }


        friend BasicString<CharType> operator +( const BasicString<CharType>& first, const BasicString<CharType>& second )
        {
            auto firstSize = first.size( );
            auto* firstData = first.data( );

            auto secondSize = second.size( );
            auto* secondData = second.data( );

            return Combine( firstData, firstSize, secondData, secondSize );

        }

        friend BasicString<CharType> operator +( const CharType* first, const BasicString<CharType>& second )
        {
            auto firstSize = Internal::LengthOf( first );

            auto secondSize = second.size( );
            auto* secondData = second.data( );

            return Combine( first, firstSize, secondData, secondSize );
        }

        friend BasicString<CharType> operator +( const BasicString<CharType>& first, const CharType* second )
        {
            auto firstSize = first.size( );
            auto* firstData = first.data( );

            auto secondSize = Internal::LengthOf( second );

            return Combine( firstData, firstSize, second, secondSize );
        }


        void Append( const CharType* other )
        {
            auto otherLength = Internal::LengthOf( other );
            auto* dest = Extend( otherLength );
            Internal::Copy( dest, other, otherLength );
        }

        void Append( const CharType* other, size_t otherLength )
        {
            auto* dest = Extend( otherLength );
            Internal::Copy( dest, other, otherLength );
        }

        void Append( const BasicString<CharType>& other )
        {
            auto otherLength = other.size( );
            auto* dest = Extend( otherLength );
            Internal::Copy( dest, other.data( ), otherLength );
        }

        void Append( CharType c )
        {
            auto* dest = Extend( 1 );
            *dest = c;
        }

        BasicString<CharType>& operator += ( const CharType* other ) { Append( other ); return *this; }
        BasicString<CharType>& operator += ( const BasicString<CharType>& other ) { Append( other ); return *this; }
        BasicString<CharType>& operator += ( CharType c ) { Append( c ); return *this; }





    private:
        static int Compare( const Data* first, const Data* second )
        {
            if ( first != second )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::Compare( first->buffer_, first->size_, second->buffer_, second->size_ );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }
        }

        static int ICompare( const Data* first, const Data* second )
        {
            if ( first != second )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::ICompare( first->buffer_, first->size_, second->buffer_, second->size_ );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }
        }

        static bool IsNotSame( const CharType* first, const Data* second )
        {
            if ( second )
            {
                return first != second->buffer_;
            }
            else
            {
                return first ? false : true;
            }
        }
        static bool IsNotSame( const Data* first, const CharType* second )
        {
            if ( first )
            {
                return first->buffer_ != second;
            }
            else
            {
                return second ? false : true;
            }
        }


        static int Compare( const CharType* first, const Data* second )
        {
            if ( IsNotSame( first, second ) )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::Compare( first, second->buffer_, second->size_ );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }
        }

        static int ICompare( const CharType* first, const Data* second )
        {
            if ( IsNotSame( first, second ) )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::ICompare( first, second->buffer_, second->size_ );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }
        }

        static int Compare( const Data* first, const CharType* second )
        {
            if ( IsNotSame( first, second ) )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::Compare( first->buffer_, first->size_, second );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }
        }

        static int ICompare( const Data* first, const CharType* second )
        {
            if ( IsNotSame( first, second ) )
            {
                if ( first )
                {
                    if ( second )
                    {
                        return Internal::ICompare( first->buffer_, first->size_, second );
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return 0;
            }
        }

    public:
        static int Compare( const BasicString& first, const BasicString& second )
        {
            return Compare( first.data_, second.data_ );
        }
        static int Compare( const CharType* first, const BasicString& second )
        {
            return Compare( first, second.data_ );
        }
        static int Compare( const BasicString& first, const CharType* second )
        {
            return Compare( first.data_, second );
        }

        static int ICompare( const BasicString& first, const BasicString& second )
        {
            return ICompare( first.data_, second.data_ );
        }
        static int ICompare( const CharType* first, const BasicString& second )
        {
            return ICompare( first, second.data_ );
        }
        static int ICompare( const BasicString& first, const CharType* second )
        {
            return ICompare( first.data_, second );
        }

        friend bool operator == ( const BasicString& first, const BasicString& second )
        {
            return Compare( first, second ) == 0;
        }
        friend bool operator == ( const CharType* first, const BasicString& second )
        {
            return Compare( first, second ) == 0;
        }
        friend bool operator == ( const BasicString& first, const CharType* second )
        {
            return Compare( first, second ) == 0;
        }

        friend bool operator <= ( const BasicString& first, const BasicString& second )
        {
            return Compare( first, second ) <= 0;
        }
        friend bool operator <= ( const CharType* first, const BasicString& second )
        {
            return Compare( first, second ) <= 0;
        }
        friend bool operator <= ( const BasicString& first, const CharType* second )
        {
            return Compare( first, second ) <= 0;
        }

        friend bool operator >= ( const BasicString& first, const BasicString& second )
        {
            return Compare( first, second ) >= 0;
        }
        friend bool operator >= ( const CharType* first, const BasicString& second )
        {
            return Compare( first, second ) >= 0;
        }
        friend bool operator >= ( const BasicString& first, const CharType* second )
        {
            return Compare( first, second ) >= 0;
        }

        friend bool operator < ( const BasicString& first, const BasicString& second )
        {
            return Compare( first, second ) < 0;
        }
        friend bool operator < ( const CharType* first, const BasicString& second )
        {
            return Compare( first, second ) < 0;
        }
        friend bool operator < ( const BasicString& first, const CharType* second )
        {
            return Compare( first, second ) < 0;
        }
        friend bool operator > ( const BasicString& first, const BasicString& second )
        {
            return Compare( first, second ) > 0;
        }
        friend bool operator > ( const CharType* first, const BasicString& second )
        {
            return Compare( first, second ) > 0;
        }
        friend bool operator > ( const BasicString& first, const CharType* second )
        {
            return Compare( first, second ) > 0;
        }

        friend bool operator != ( const BasicString& first, const BasicString& second )
        {
            return Compare( first, second ) != 0;
        }
        friend bool operator != ( const CharType* first, const BasicString& second )
        {
            return Compare( first, second ) != 0;
        }
        friend bool operator != ( const BasicString& first, const CharType* second )
        {
            return Compare( first, second ) != 0;
        }








        size_type IndexOf( CharType c )
        {
            if ( data_ )
            {
                auto* foundAt = Internal::MemChr( data_->buffer_, c, data_->size_ );
                return foundAt ? foundAt - data_->buffer_ : npos;
            }
            else
            {
                return npos;
            }
        }

        size_type IndexOfAnyOf( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ && searchChars && numberOfSearchChars )
            {
                while ( start < data_->size_ )
                {
                    const auto* p = Internal::MemChr( searchChars, data_->buffer_[start], static_cast<size_t>( numberOfSearchChars ) );
                    if ( p )
                    {
                        return start;
                    }
                    start++;
                }
            }
            return npos;
        }


        size_type IIndexOfAnyOf( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ && searchChars && numberOfSearchChars )
            {
                while ( start < data_->size_ )
                {
                    auto c = Internal::ToUpper( data_->buffer_[start] );
                    for ( size_t i = 0; i < numberOfSearchChars; i++ )
                    {
                        auto sc = Internal::ToUpper( searchChars[i] );
                        if ( c == sc )
                        {
                            return start;
                        }
                    }
                    start++;
                }
            }
            return npos;
        }


        size_type IndexOfAnyOf( const BasicString<CharType>& searchChars, size_type start = 0 ) const
        {
            const auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return IndexOfAnyOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        size_type IIndexOfAnyOf( const AnsiString& searchChars, size_type start = 0 ) const
        {
            const auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return IIndexOfAnyOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        size_type IndexOfAnyOf( const CharType* searchChars, size_type start = 0 ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            if ( length )
            {
                return IndexOfAnyOf( searchChars, length, start );
            }
            return npos;
        }

        size_type IIndexOfAnyOf( const CharType* searchChars, size_type start = 0 ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            if ( length )
            {
                return IIndexOfAnyOf( searchChars, length, start );
            }
            return npos;
        }


        size_type IndexOfAnyBut( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ && searchChars && numberOfSearchChars )
            {
                while ( start < data_->size_ )
                {
                    const auto* p = Internal::MemChr( searchChars, data_->buffer_[start], static_cast<size_t>( numberOfSearchChars ) );
                    if ( !p )
                    {
                        return start;
                    }
                    start++;
                }
            }
            return npos;
        }

        size_type IIndexOfAnyBut( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ && searchChars && numberOfSearchChars )
            {
                while ( start < data_->size_ )
                {
                    auto c = Internal::ToUpper( data_->buffer_[start] );
                    size_t i = 0;
                    for ( ; i < numberOfSearchChars; i++ )
                    {
                        auto sc = Internal::ToUpper( searchChars[i] );
                        if ( c == sc )
                        {
                            break;
                        }
                    }
                    if ( i == numberOfSearchChars )
                    {
                        return start;
                    }
                    start++;
                }
            }
            return npos;
        }


        size_type IndexOfAnyBut( const BasicString& searchChars, size_type start = 0 ) const
        {
            auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return IndexOfAnyBut( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        size_type IIndexOfAnyBut( const BasicString& searchChars, size_type start = 0 ) const
        {
            auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return IIndexOfAnyBut( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        size_type IndexOfAnyBut( const CharType* searchChars, size_type start = 0 ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            return IndexOfAnyBut( searchChars, length, start );
        }

        size_type IIndexOfAnyBut( const CharType* searchChars, size_type start = 0 ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            return IIndexOfAnyBut( searchChars, length, start );
        }


        size_type LastIndexOfAnyOf( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ && searchChars && numberOfSearchChars )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }
                do
                {
                    const auto* p = Internal::MemChr( searchChars, data_->buffer_[start], static_cast<size_t>( numberOfSearchChars ) );
                    if ( p )
                    {
                        return start;
                    }
                } while ( start-- );
            }
            return npos;
        }

        size_type ILastIndexOfAnyOf( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ && searchChars && numberOfSearchChars )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }
                do
                {
                    auto c = Internal::ToUpper( data_->buffer_[start] );
                    for ( size_t i = 0; i < numberOfSearchChars; i++ )
                    {
                        auto sc = Internal::ToUpper( searchChars[i] );
                        if ( c == sc )
                        {
                            return start;
                        }
                    }
                } while ( start-- );
            }
            return npos;
        }


        size_type LastIndexOfAnyOf( const BasicString& searchChars, size_type start = npos ) const
        {
            auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return LastIndexOfAnyOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        size_type ILastIndexOfAnyOf( const BasicString& searchChars, size_type start = npos ) const
        {
            auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return ILastIndexOfAnyOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        size_type LastIndexOfAnyOf( const CharType* searchChars, size_type start = npos ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            if ( length )
            {
                return LastIndexOfAnyOf( searchChars, length, start );
            }
            return npos;
        }

        size_type ILastIndexOfAnyOf( const CharType* searchChars, size_type start = npos ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            if ( length )
            {
                return ILastIndexOfAnyOf( searchChars, length, start );
            }
            return npos;
        }


        size_type LastIndexOfAnyBut( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }
                do
                {
                    const auto* p = Internal::MemChr( searchChars, data_->buffer_[start], static_cast<size_t>( numberOfSearchChars ) );
                    if ( !p )
                    {
                        return start;
                    }
                } while ( start-- );
            }
            return npos;
        }

        size_type ILastIndexOfAnyBut( const CharType* searchChars, size_type numberOfSearchChars, size_type start ) const
        {
            if ( data_ )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }
                do
                {
                    auto c = Internal::ToUpper( data_->buffer_[start] );
                    size_t i = 0;
                    for ( ; i < numberOfSearchChars; i++ )
                    {
                        auto sc = Internal::ToUpper( searchChars[i] );
                        if ( c == sc )
                        {
                            break;
                        }
                    }
                    if ( i == numberOfSearchChars )
                    {
                        return start;
                    }
                } while ( start-- );
            }
            return npos;
        }




        size_type LastIndexOfAnyBut( const BasicString& searchChars, size_type start = npos ) const
        {
            auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return LastIndexOfAnyBut( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        size_type ILastIndexOfAnyBut( const BasicString& searchChars, size_type start = npos ) const
        {
            auto* searchData = searchChars.data_;
            if ( searchData )
            {
                return ILastIndexOfAnyBut( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        size_type LastIndexOfAnyBut( const CharType* searchChars, size_type start = npos ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            if ( length )
            {
                return LastIndexOfAnyBut( searchChars, length, start );
            }
            return npos;
        }

        size_type ILastIndexOfAnyBut( const CharType* searchChars, size_type start = npos ) const
        {
            size_type length = Internal::LengthOf( searchChars );
            if ( length )
            {
                return ILastIndexOfAnyBut( searchChars, length, start );
            }
            return npos;
        }


        size_type IndexOf( const CharType* searchString, size_type searchStringLength, size_type start ) const
        {
            if ( data_ && ( start < data_->size_ ) )
            {
                if ( searchStringLength == 1 )
                {
                    auto* p = Internal::MemChr( &data_->buffer_[start], *searchString, static_cast<size_t>( data_->size_ - start ) );
                    if ( p )
                    {
                        return p - data_->buffer_;
                    }
                }
                else if ( searchStringLength )
                {
                    while ( ( start + searchStringLength ) <= data_->size_ )
                    {
                        if ( Internal::Compare( &data_->buffer_[start], searchString, static_cast<size_t>( searchStringLength ) ) == 0 )
                        {
                            return start;
                        }
                        start++;
                    }
                }
            }
            return npos;
        }



        size_type IIndexOf( const CharType* searchString, size_type searchStringLength, size_type start ) const
        {
            if ( data_ && ( start < data_->size_ ) )
            {
                if ( searchStringLength == 1 )
                {
                    auto* p = Internal::MemIChr( &data_->buffer_[start], *searchString, static_cast<size_t>( data_->size_ - start ) );
                    if ( p )
                    {
                        return p - data_->buffer_;
                    }
                }
                else if ( searchStringLength )
                {
                    while ( ( start + searchStringLength ) <= data_->size_ )
                    {
                        if ( Internal::ICompare( &data_->buffer_[start], searchString, static_cast<size_t>( searchStringLength ) ) == 0 )
                        {
                            return start;
                        }
                        start++;
                    }
                }
            }
            return npos;
        }


        size_type IndexOf( const BasicString& searchString, size_type start = 0 ) const
        {
            auto* searchData = searchString.data_;
            if ( searchData )
            {
                return IndexOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        size_type IIndexOf( const BasicString& searchString, size_type start = 0 ) const
        {
            auto* searchData = searchString.data_;
            if ( searchData )
            {
                return IIndexOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        size_type IndexOf( const CharType* searchString, size_type start = 0 ) const
        {
            if ( searchString && searchString[0] && data_ && start < data_->size_ )
            {
                const char* pStart = &data_->buffer_[start];
                const char* pEnd = &data_->buffer_[data_->size_];
                while ( pStart < pEnd )
                {
                    auto* p = Internal::MemChr( pStart, *searchString, pEnd - pStart );
                    if ( p )
                    {
                        const char* pSearchChar = searchString + 1;
                        const char* pContent = p + 1;
                        while ( *pSearchChar )
                        {
                            if ( *pContent != *pSearchChar )
                            {
                                break;
                            }
                            pContent++;
                            pSearchChar++;
                        }
                        if ( !( *pSearchChar ) )
                        {
                            return p - data_->buffer_;
                        }
                        pStart = p + 1;
                    }
                    else
                    {
                        return npos;
                    }
                }
            }
            return npos;
        }

        size_type IIndexOf( const CharType* searchString, size_type start = 0 ) const
        {
            if ( searchString && searchString[0] && data_ && start < data_->size_ )
            {
                const char* pStart = &data_->buffer_[start];
                const char* pEnd = &data_->buffer_[data_->size_];
                while ( pStart < pEnd )
                {
                    auto* p = Internal::MemIChr( pStart, *searchString, pEnd - pStart );
                    if ( p )
                    {
                        const char* pSearchChar = searchString + 1;
                        const char* pContent = p + 1;
                        while ( *pSearchChar )
                        {
                            if ( toupper( *pContent ) != toupper( *pSearchChar ) )
                            {
                                break;
                            }
                            pContent++;
                            pSearchChar++;
                        }
                        if ( !( *pSearchChar ) )
                        {
                            return p - data_->buffer_;
                        }
                        pStart = p + 1;
                    }
                    else
                    {
                        return npos;
                    }
                }
            }
            return npos;
        }


        size_type IndexOf( const CharType c, size_type start = 0 ) const
        {
            if ( data_ && start < data_->size_ )
            {
                auto* p = Internal::MemChr( &data_->buffer_[start], c, static_cast<size_t>( data_->size_ - start ) );
                if ( p )
                {
                    return p - data_->buffer_;
                }
            }
            return npos;
        }


        size_type IndexOf( bool( *test )( CharType ), size_type start = 0 ) const
        {
            if ( data_ )
            {
                while ( start < data_->size_ )
                {
                    auto c = data_->buffer_[start];
                    if ( test( c ) )
                    {
                        return start;
                    }
                    start++;
                }
            }
            return npos;
        }

        size_type IndexOf( bool( *test )( const CharType*, size_type length ), size_type start = 0 ) const
        {
            if ( data_ && start < data_->size_ )
            {
                char* pStart = &data_->buffer_[start];
                size_type remainingLength = data_->size_ - start;
                while ( remainingLength )
                {
                    if ( test( pStart, remainingLength ) )
                    {
                        return start;
                    }
                    remainingLength--;
                    pStart++;
                }
            }
            return npos;
        }

        size_type IndexOf( bool( *test )( const CharType*, const CharType* ), size_type start = 0 ) const
        {
            if ( data_ && start < data_->size_ )
            {
                const char* pStart = &data_->buffer_[start];
                const char* pEnd = end( );
                while ( pStart < pEnd )
                {
                    if ( test( pStart, pEnd ) )
                    {
                        return start;
                    }
                    pStart++;
                }
            }
            return npos;
        }




        size_type LastIndexOf( const CharType* searchString, size_type searchStringLength, size_type start ) const
        {
            if ( data_ && ( searchStringLength <= data_->size_ ) )
            {
                if ( start > ( data_->size_ - searchStringLength ) )
                {
                    start = data_->size_ - searchStringLength;
                }

                if ( searchStringLength == 1 )
                {
                    do
                    {
                        if ( data_->buffer_[start] == *searchString )
                        {
                            return start;
                        }
                    } while ( start-- );
                }
                else if ( searchStringLength )
                {
                    do
                    {
                        if ( Compare( &data_->buffer_[start], searchString, static_cast<size_t>( searchStringLength ) ) == 0 )
                        {
                            return start;
                        }
                    } while ( start-- );
                }
            }
            return npos;
        }


        size_type ILastIndexOf( const CharType* searchString, size_type searchStringLength, size_type start ) const
        {
            if ( data_ && ( searchStringLength <= data_->size_ ) )
            {
                if ( start > ( data_->size_ - searchStringLength ) )
                {
                    start = data_->size_ - searchStringLength;
                }

                if ( searchStringLength == 1 )
                {
                    auto c = Internal::ToUpper( *searchString );
                    do
                    {
                        if ( Internal::ToUpper( data_->buffer_[start] ) == c )
                        {
                            return start;
                        }
                    } while ( start-- );
                }
                else if ( searchStringLength )
                {
                    do
                    {
                        if ( ICompare( &data_->buffer_[start], searchString, static_cast<size_t>( searchStringLength ) ) == 0 )
                        {
                            return start;
                        }
                    } while ( start-- );
                }
            }
            return npos;
        }

        size_type LastIndexOf( const BasicString& searchString, size_type start = npos ) const
        {
            auto* searchData = searchString.data_;
            if ( searchData )
            {
                return LastIndexOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        size_type ILastIndexOf( const BasicString& searchString, size_type start = npos ) const
        {
            auto* searchData = searchString.data_;
            if ( searchData )
            {
                return ILastIndexOf( searchData->buffer_, searchData->size_, start );
            }
            return npos;
        }

        size_type LastIndexOf( const CharType* searchString, size_type start = npos ) const
        {
            size_type length = Internal::LengthOf( searchString );
            if ( length )
            {

                return LastIndexOf( searchString, length, start );
            }
            return npos;
        }

        size_type ILastIndexOf( const CharType* searchString, size_type start = npos ) const
        {
            size_type length = Internal::LengthOf( searchString );
            if ( length )
            {

                return ILastIndexOf( searchString, length, start );
            }
            return npos;
        }

        size_type LastIndexOf( CharType c, size_type start = npos ) const
        {
            if ( data_ )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }

                do
                {
                    if ( data_->buffer_[start] == c )
                    {
                        return start;
                    }
                } while ( start-- );
            }
            return npos;
        }

        size_type ILastIndexOf( CharType c, size_type start = npos ) const
        {
            c = Internal::ToUpper( c );
            if ( data_ )
            {
                if ( start >= data_->size_ )
                {
                    start = data_->size_ - 1;
                }

                do
                {
                    if ( Internal::ToUpper( data_->buffer_[start] ) == c )
                    {
                        return start;
                    }
                } while ( start-- );
            }
            return npos;
        }


        size_type LastIndexOf( bool( *test )( CharType ), size_type start = npos ) const
        {
            if ( data_ )
            {
                if ( start >= ( data_->size_ ) )
                {
                    start = data_->size_ - 1;
                }

                do
                {
                    char c = data_->buffer_[start];
                    if ( test( c ) )
                    {
                        return start;
                    }
                } while ( start-- );

            }
            return npos;
        }


        size_type LastIndexOf( bool( *test )( const CharType*, size_type length ), size_type start = npos ) const
        {
            if ( ( data_ ) && ( start < data_->size_ ) )
            {
                if ( start >= ( data_->size_ ) )
                {
                    start = data_->size_ - 1;
                }

                const char* pStart = &data_->buffer_[start];
                size_type remainingLength = data_->size_ - start;

                do
                {
                    if ( test( pStart, remainingLength ) )
                    {
                        return start;
                    }
                    remainingLength++;
                } while ( data_ != pStart-- );
            }
            return npos;
        }


        size_type LastIndexOf( bool( *test )( const CharType*, const CharType* ), size_type start = npos ) const
        {
            if ( ( data_ ) && ( start < data_->size_ ) )
            {
                if ( start >= ( data_->size_ ) )
                {
                    start = data_->size_ - 1;
                }

                const char* pStart = &data_->buffer_[start];
                const char* pEnd = end( );
                do
                {
                    if ( test( pStart, pEnd ) )
                    {
                        return start;
                    }
                } while ( data_ != pStart-- );
            }
            return npos;
        }

        bool IsSpace( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsSpace( data_->buffer_[position] ) != 0;
            }
            return false;
        }

        bool IsControl( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsControl( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        bool IsDigit( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsDigit( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        bool IsLetter( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsLetter( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        bool IsLetterOrDigit( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsLetterOrDigit( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        bool IsLower( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsLower( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        bool IsUpper( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsUpper( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        bool IsPunctuation( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsPunctuation( data_->buffer_[position] ) != 0;
            }
            return false;
        }
        bool IsWhiteSpace( size_type position ) const
        {
            if ( ( data_ ) && ( position < data_->size_ ) )
            {
                return Internal::IsWhiteSpace( data_->buffer_[position] ) != 0;
            }
            return false;
        }

        bool StartsWith( const CharType* str ) const
        {
            if ( data_ && data_->buffer_[0] && str && str[0] )
            {
                const char* p = data_->buffer_;
                while ( *p && *str )
                {
                    if ( *p != *str )
                    {
                        break;
                    }
                    p++;
                    str++;
                }
                return *str == L'\x00';
            }
            return false;
        }

        bool StartsWith( const BasicString& str ) const
        {
            if ( str.data_ )
            {
                return StartsWith( str.data_->buffer_ );
            }
            else
            {
                return false;
            }
        }

        bool IStartsWith( const CharType* str ) const
        {
            if ( data_ && data_->buffer_[0] && str && str[0] )
            {
                const char* p = data_->buffer_;
                while ( *p && *str )
                {
                    if ( Internal::ToUpper( *p ) != Internal::ToUpper( *str ) )
                    {
                        break;
                    }
                    p++;
                    str++;
                }
                return *str == L'\x00';
            }
            return false;
        }

        bool IStartsWith( const BasicString& str ) const
        {
            if ( str.data_ )
            {
                return IStartsWith( str.data_->buffer_ );
            }
            else
            {
                return false;
            }
        }

        bool EndsWith( const CharType* str ) const
        {
            if ( data_ && data_->size_ && str && str[0] )
            {
                auto otherLength = Internal::LengthOf( str );
                if ( otherLength <= data_->size_ )
                {
                    return Internal::Compare( &data_->data[data_->size_ - otherLength], otherLength, str, otherLength ) == 0;
                }
            }
            return false;
        }
        bool EndsWith( const BasicString& str ) const
        {
            auto* other = str.data_;
            if ( data_ && data_->size_ && other && other->size_ )
            {
                if ( other->size_ <= data_->size_ )
                {
                    return Internal::Compare( &data_->data[data_->size_ - other->size_], other->size_, other->buffer_, other->size_ ) == 0;
                }
            }
            return false;
        }
        bool IEndsWith( const CharType* str ) const
        {
            if ( data_ && data_->size_ && str && str[0] )
            {
                auto otherLength = Internal::LengthOf( str );
                if ( otherLength <= data_->size_ )
                {
                    return Internal::ICompare( &data_->data[data_->size_ - otherLength], otherLength, str, otherLength ) == 0;
                }
            }
            return false;
        }
        bool IEndsWith( const BasicString& str ) const
        {
            auto* other = str.data_;
            if ( data_ && data_->size_ && other && other->size_ )
            {
                if ( other->size_ <= data_->size_ )
                {
                    return Internal::ICompare( &data_->data[data_->size_ - other->size_], other->size_, other->buffer_, other->size_ ) == 0;
                }
            }
            return false;
        }


        BasicString SubString( size_type start, size_type length = npos ) const
        {
            if ( data_ && ( start < data_->size_ ) )
            {
                if ( length > ( data_->size_ - start ) )
                {
                    length = data_->size_ - start;
                }
                if ( ( start == 0 ) && ( length == data_->size_ ) )
                {
                    return BasicString( data_ );
                }
                else
                {
                    return BasicString( data_->buffer_ + start, length );
                }
            }
            else
            {
                return BasicString( );
            }
        }

        BasicString& UpperCase( )
        {
            if ( data_ )
            {
                if ( data_->referenceCount_ > 1 )
                {
                    auto newData = Allocate( data_->size_ );
                    Internal::Copy( newData->buffer_, data_->buffer_, data_->size_ );
                    Release( data_ );
                    data_ = newData;
                }
                Internal::ToUpper( data_->buffer_, data_->size_ );
            }
            return *this;
        }

        BasicString& LowerCase( )
        {
            if ( data_ )
            {
                if ( data_->referenceCount_ > 1 )
                {
                    auto newData = Allocate( data_->size_ );
                    Internal::Copy( newData->buffer_, data_->buffer_, data_->size_ );
                    Release( data_ );
                    data_ = newData;
                }
                Internal::ToLower( data_->buffer_, data_->size_ );
            }
            return *this;
        }

        BasicString ToLower( ) const
        {
            if ( data_ )
            {
                auto newData = Allocate( data_->size_ );
                Internal::Copy( newData->buffer_, data_->buffer_, data_->size_ );
                Internal::ToLower( newData->buffer_, newData->size_ );
                return BasicString( newData );
            }
            else
            {
                return BasicString( );
            }
        }

        BasicString ToUpper( ) const
        {
            if ( data_ )
            {
                auto newData = Allocate( data_->size_ );
                Internal::Copy( newData->buffer_, data_->buffer_, data_->size_ );
                Internal::ToUpper( newData->buffer_, newData->size_ );
                return BasicString( newData );
            }
            else
            {
                return BasicString( );
            }
        }

        BasicString& erase( )
        {
            Release( data_ );
            data_ = nullptr;
            return *this;
        }

        BasicString& erase( size_type index, size_type count = npos )
        {
            Erase( index, count );
            return *this;
        }


        BasicString& Clear( )
        {
            Release( data_ );
            data_ = nullptr;
            return *this;
        }

        BasicString& Remove( size_type start, size_type length = npos )
        {
            if ( data_ && start < data_->size_ )
            {
                Erase( start, length );
            }
            return *this;
        }

        BasicString& RemoveRange( size_type start, size_type end )
        {
            if ( data_ && start < data_->size_ && start < end )
            {
                Erase( start, end - start );
            }
            return *this;
        }

        BasicString& Replace( CharType what, CharType with )
        {
            if ( data_ )
            {
                auto index = IndexOf( what );
                if ( index != npos )
                {
                    if ( data_->referenceCount_ > 1 )
                    {
                        auto currentSize = data_->size_;
                        auto* newData = Allocate( currentSize );
                        Internal::Copy( newData->buffer_, data_->buffer_, index );
                        auto endIt = data_->buffer_ + currentSize;
                        auto it = data_->buffer_ + index;
                        auto destIt = newData->buffer_ + index;
                        while ( it < endIt )
                        {
                            auto c = *it;
                            if ( c != what )
                            {
                                *destIt = c;
                            }
                            else
                            {
                                *destIt = with;
                            }
                            destIt++;
                            it++;
                        }
                        Release( data_ );
                        data_ = newData;
                    }
                    else
                    {
                        std::replace( begin( ) + index, end( ), what, with );
                    }
                }
            }
            return *this;
        }


        BasicString& TrimRight( const CharType* charactersToRemove, size_type numberOfCharactersToRemove )
        {
            if ( data_ )
            {
                auto index = LastIndexOfAnyBut( charactersToRemove, numberOfCharactersToRemove );
                erase( index );
            }
            return *this;
        }

        BasicString& TrimRight( BasicString& charactersToRemove )
        {
            if ( data_ )
            {
                auto index = LastIndexOfAnyBut( charactersToRemove.c_str( ), charactersToRemove.size( ) );
                erase( index );
            }
            return *this;
        }


    };



    template<typename T>
    class BasicStringView
    {
    public:
        using CharType = T;
        using const_iterator = const CharType*;
        using const_reference = const CharType&;
        using size_type = size_t;
        using value_type = T;

        static constexpr size_type npos = MAXUINT64;
    private:
        size_type size_;
        const CharType* buffer_;
    public:
        constexpr BasicStringView( ) noexcept
            : size_( 0 ), buffer_( nullptr )
        {
        }


        constexpr BasicStringView( const CharType* s, size_type count ) noexcept
            : size_( count ), buffer_( s )
        {
        }

        BasicStringView( const CharType* s ) noexcept
            : size_( Internal::LengthOf( s ) ), buffer_( s )
        {
        }

        BasicStringView( const BasicString<T>& s ) noexcept
            : size_( s.size( ) ), buffer_( s.data( ) )
        {

        }


        BasicStringView( const BasicStringView& other ) noexcept
            : size_( other.size_ ), buffer_( other.buffer_ )
        {
        }


        BasicStringView& operator = ( const BasicStringView& other )
        {
            size_ = other.size_;
            buffer_ = other.buffer_;
            return *this;
        }


        constexpr bool empty( ) const noexcept
        {
            return size_ != 0;
        }
        constexpr bool IsEmpty( ) const noexcept
        {
            return size_ != 0;
        }

        constexpr size_type size( ) const noexcept
        {
            return size_;
        }
        constexpr size_type length( ) const noexcept
        {
            return size_;
        }
        constexpr size_type Length( ) const noexcept
        {
            return size_;
        }

        constexpr const_iterator begin( ) const noexcept
        {
            return buffer_;
        }

        constexpr const_iterator end( ) const noexcept
        {
            return buffer_ + size_;
        }

        constexpr const_iterator cbegin( ) const noexcept
        {
            return buffer_;
        }

        constexpr const_iterator cend( ) const noexcept
        {
            return buffer_ + size_;
        }

        constexpr const_reference operator[]( size_type index ) const noexcept
        {
            return buffer_[index];
        }

        constexpr const CharType* data( ) const noexcept
        {
            return buffer_;
        }

        size_t Hash( ) const noexcept
        {
            if ( buffer_ )
            {
                return XXH3_64bits( buffer_, size_ * sizeof( CharType ) );
            }
            else
            {
                return 0;
            }
        }
    };

    template<typename T>
    inline BasicString<T>::BasicString( const BasicStringView<T>& v )
        : data_( Initialize( v.data( ), v.size( ) ) )
    {
    }
#endif
}

#ifdef HCC_WITH_BASIC_STRING
namespace std
{
    template<> struct hash<Harlinn::Common::Core::WideString>
    {
        std::size_t operator()( const Harlinn::Common::Core::WideString& s ) const noexcept
        {
            return s.Hash( );
        }
    };

    template<> struct hash<Harlinn::Common::Core::WideStringView>
    {
        std::size_t operator()( const Harlinn::Common::Core::WideStringView& s ) const noexcept
        {
            return s.Hash( );
        }
    };


    template<> struct hash<Harlinn::Common::Core::AnsiString>
    {
        std::size_t operator()( const Harlinn::Common::Core::AnsiString& s ) const noexcept
        {
            return s.Hash( );
        }
    };

    template<> struct hash<Harlinn::Common::Core::AnsiStringView>
    {
        std::size_t operator()( const Harlinn::Common::Core::AnsiStringView& s ) const noexcept
        {
            return s.Hash( );
        }
    };
}
#endif


#endif
