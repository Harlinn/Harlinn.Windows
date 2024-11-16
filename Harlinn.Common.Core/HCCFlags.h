#pragma once
#ifndef HCCFLAGS_H_
#define HCCFLAGS_H_
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

namespace Harlinn::Common::Core
{
    template<typename DerivedT, typename ValueT>
    class EnumBase
    {
    public:
        using DerivedType = DerivedT;
        using StringType = WideString;
        using CharType = typename StringType::value_type;
        using ValueType = ValueT;
        using IntegerType = std::conditional_t<std::is_enum_v<ValueType>, std::underlying_type_t<ValueType>, ValueType>;
    protected:
        struct Entry
        {
            StringType Name;
            IntegerType Value;
        };
    protected:
        std::vector<Entry> entries_;
    public:
        EnumBase( ) = default;

        DerivedType& Add( const StringType& name, ValueType value )
        {
            entries_.emplace_back( name, static_cast< IntegerType >( value ) );
            return static_cast< DerivedType& >( *this );
        }
    protected:
        DerivedType& Add( const CharType* name, ValueType value )
        {
            return Add( StringType( name ), value );
        }
        const Entry* Find( const StringType& name ) const
        {
            size_t count = entries_.size( );
            for ( size_t i = 0; i < count; i++ )
            {
                const auto& entry = entries_[ i ];
                if ( entry.Name == name )
                {
                    return std::addressof( entry );
                }
            }
            return nullptr;
        }

        const Entry* Find( IntegerType value ) const
        {
            size_t count = entries_.size( );
            for ( size_t i = 0; i < count; i++ )
            {
                const auto& entry = entries_[ i ];
                if ( entry.Value == value )
                {
                    return std::addressof( entry );
                }
            }
            return nullptr;
        }
    };


    template<typename ValueT>
    class Flags : public EnumBase<Flags<ValueT>, ValueT>
    {
    public:
        using Base = EnumBase<Flags<ValueT>, ValueT>;
        using StringType = typename Base::StringType;
        using CharType = typename Base::CharType;
        using ValueType = typename Base::ValueType;
        using IntegerType = typename Base::IntegerType;
    private:
        using Entry = typename Base::Entry;
        CharType separator_ = static_cast< CharType >( '|' );
    public:
        Flags( ) = default;
        Flags( CharType separator )
            : separator_( separator )
        { }

    private:
        bool TryFind( IntegerType value, size_t& index, const Entry** entry ) const
        {
            size_t count = Base::entries_.size( );
            for ( size_t i = index; i < count; i++ )
            {
                const auto& currentEntry = Base::entries_[ i ];
                if ( value )
                {
                    if ( ( value & currentEntry.Value ) != 0 )
                    {
                        index = i;
                        *entry = &currentEntry;
                        return true;
                    }
                }
                else if( currentEntry.Value == 0)
                {
                    index = i;
                    *entry = &currentEntry;
                    return true;
                }
            }
            return false;
        }
    public:
        template<bool ThrowException>
        StringType ToString( ValueType value, const StringType& defaultResult ) const
        {
            if ( Base::entries_.size( ) )
            {
                size_t index = 0;
                const Entry* entry = nullptr;
                auto intValue = static_cast< IntegerType >( value );
                if ( intValue )
                {
                    IntegerType processedValue = 0;
                    StringType result;
                    bool isFirst = true;
                    while ( TryFind( intValue, index, &entry ) )
                    {
                        processedValue |= entry->Value;

                        if ( isFirst == false )
                        {
                            result.Append( separator_ );
                        }
                        result.Append( entry->Name );

                        if ( processedValue == intValue )
                        {
                            return result;
                        }

                        isFirst = false;
                        index++;
                    }
                }
                else
                {
                    if ( TryFind( intValue, index, &entry ) )
                    {
                        return entry->Name;
                    }
                }
            }
            if constexpr ( ThrowException )
            {
                if ( Base::entries_.size( ) == 0 )
                {
                    throw InvalidOperationException( );
                }
                throw ArgumentException( L"value" );
            }
            return defaultResult;
        }
    public:
        StringType ToString( ValueType value, const StringType& defaultResult ) const
        {
            return ToString<false>( value, defaultResult );
        }

        StringType ToString( ValueType value ) const
        {
            return ToString<true>( value, StringType() );
        }

    public:

        bool TryParse( const StringType& str, ValueType& value ) const
        {
            auto trimmedStr = Trim( str );
            auto trimmedStrLength = trimmedStr.Length( );
            if ( trimmedStrLength && Base::entries_.size( ) )
            {
                std::vector<StringType> parts;
                trimmedStr.Split( separator_, parts );
                auto partsCount = parts.size( );
                if ( partsCount )
                {
                    IntegerType intValue = 0;
                    for ( auto& part : parts )
                    {
                        auto entry = Base::Find( part );
                        if ( entry )
                        {
                            intValue |= entry->Value;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    value = static_cast< ValueType >( intValue );
                    return true;
                }
            }
            return false;
        }

        ValueType Parse( const StringType& str ) const
        {
            ValueType result{};
            if ( TryParse( str, result ) == false )
            {
                throw ArgumentException( L"str" );
            }
            return result;
        }

        ValueType Parse( const StringType& str, ValueType defaultValue ) const
        {
            ValueType result{};
            if ( TryParse( str, result ) == false )
            {
                return defaultValue;
            }
            return result;
        }
    };

    template<typename ValueT>
    class Enum : public EnumBase<Enum<ValueT>, ValueT>
    {
    public:
        using Base = EnumBase<Enum<ValueT>, ValueT>;
        using StringType = typename Base::StringType;
        using CharType = typename Base::CharType;
        using ValueType = typename Base::ValueType;
        using IntegerType = typename Base::IntegerType;
    private:
        using Entry = typename Base::Entry;
    public:
        Enum( ) = default;

    private:
    public:
        StringType ToString( ValueType value ) const
        {
            auto intValue = static_cast< IntegerType >( value );
            auto entry = Base::Find( intValue );
            if ( entry == nullptr)
            {
                throw ArgumentException( "value" );
            }
            return entry->Name;
        }

        StringType ToString( ValueType value, const StringType& defaultResult ) const
        {
            auto intValue = static_cast< IntegerType >( value );
            auto entry = Base::Find( intValue );
            if ( entry == nullptr )
            {
                return defaultResult;
            }
            return entry->Name;
        }

        bool TryParse( const StringType& str, ValueType& value ) const
        {
            auto trimmedStr = Trim( str );
            auto entry = Base::Find( trimmedStr );
            if ( entry )
            {
                value = static_cast< ValueType >(entry->Value);
                return true;
            }
            return false;
        }

        ValueType Parse( const StringType& str ) const
        {
            ValueType result{};
            if ( TryParse( str, result ) == false )
            {
                throw ArgumentException( L"str" );
            }
            return result;
        }

        ValueType Parse( const StringType& str, ValueType defaultValue ) const
        {
            ValueType result{};
            if ( TryParse( str, result ) == false )
            {
                return defaultValue;
            }
            return result;
        }

    };
}





#endif
