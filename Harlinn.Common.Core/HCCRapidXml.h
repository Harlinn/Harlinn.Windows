#pragma once
#ifndef HCCRAPIDXML_H_
#define HCCRAPIDXML_H_
/*
   Copyright 2024-2025 Espen Harlinn

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
#include <HCCDateTime.h>
#include <HCCGuid.h>
#include <HCCIO.h>
#include <boost/property_tree/detail/rapidxml.hpp>

namespace Harlinn::Common::Core::RapidXml
{

    namespace rapidxml
    {
        using namespace boost::property_tree::detail::rapidxml;
    }

    using XmlNodeType = rapidxml::node_type;

    ///////////////////////////////////////////////////////////////////////
    // Parsing flags
    enum class ParsingFlags : Int32
    { 
        //! Parse flags which represent default behaviour of the parser. 
        //! This is always equal to 0, so that all other flags can be simply ored together.
        //! Normally there is no need to inconveniently disable flags by anding with their negated (~) values.
        //! This also means that meaning of each flag is a <i>negation</i> of the default setting. 
        //! For example, if flag name is ParsingFlags::NoUtf8, it means that utf-8 is <i>enabled</i> by default,
        //! and using the flag will disable it.
        Default = 0,


        //! Parse flag instructing the parser to not create data nodes. 
        //! Text of first data node will still be placed in value of parent element, unless ParsingFlags::NoElementValues flag is also specified.
        //! Can be combined with other flags by use of | operator.
        NoDataNodes = 0x1,

        //! Parse flag instructing the parser to not use text of first data node as a value of parent element.
        //! Can be combined with other flags by use of | operator.
        //! Note that child data nodes of element node take precedence over its value when printing.
        //! That is, if element has one or more child data nodes <em>and</em> a value, the value will be ignored.
        //! Use ParsingFlags::NoDataNodes flag to prevent creation of data nodes if you want to manipulate data using values of elements.
        NoElementValues = 0x2,

        //! Parse flag instructing the parser to not place zero terminators after strings in the source text.
        //! By default zero terminators are placed, modifying source text.
        //! Can be combined with other flags by use of | operator.
        NoStringTerminators = 0x4,

        //! Parse flag instructing the parser to not translate entities in the source text.
        //! By default entities are translated, modifying source text.
        //! Can be combined with other flags by use of | operator.
        NoEntityTranslation = 0x8,

        //! Parse flag instructing the parser to disable UTF-8 handling and assume plain 8 bit characters.
        //! By default, UTF-8 handling is enabled.
        //! Can be combined with other flags by use of | operator.
        NoUtf8 = 0x10,

        //! Parse flag instructing the parser to create XML declaration node.
        //! By default, declaration node is not created.
        //! Can be combined with other flags by use of | operator.
        DeclarationNode = 0x20,

        //! Parse flag instructing the parser to create comments nodes.
        //! By default, comment nodes are not created.
        //! Can be combined with other flags by use of | operator.
        CommentNodes = 0x40,

        //! Parse flag instructing the parser to create DOCTYPE node.
        //! By default, doctype node is not created.
        //! Although W3C specification allows at most one DOCTYPE node, RapidXml will silently accept documents with more than one.
        //! Can be combined with other flags by use of | operator.
        DoctypeNode = 0x80,

        //! Parse flag instructing the parser to create PI nodes.
        //! By default, PI nodes are not created.
        //! Can be combined with other flags by use of | operator.
        PINodes = 0x100,

        //! Parse flag instructing the parser to validate closing tag names. 
        //! If not set, name inside closing tag is irrelevant to the parser.
        //! By default, closing tags are not validated.
        //! Can be combined with other flags by use of | operator.
        ValidateClosingTags = 0x200,

        //! Parse flag instructing the parser to trim all leading and trailing whitespace of data nodes.
        //! By default, whitespace is not trimmed. 
        //! This flag does not cause the parser to modify source text.
        //! Can be combined with other flags by use of | operator.
        TrimWhitespace = 0x400,

        //! Parse flag instructing the parser to condense all whitespace runs of data nodes to a single space character.
        //! Trimming of leading and trailing whitespace of data is controlled by rapidxml::parse_trim_whitespace flag.
        //! By default, whitespace is not normalized. 
        //! If this flag is specified, source text will be modified.
        //! Can be combined with other flags by use of | operator.
        NormalizeWhitespace = 0x800,

        // Compound flags


        //! A combination of parse flags that forbids any modifications of the source text. 
        //! This also results in faster parsing. However, note that the following will occur:
        //! <ul>
        //! <li>names and values of nodes will not be zero terminated, you have to use xml_base::name_size() and xml_base::value_size() functions to determine where name and value ends</li>
        //! <li>entities will not be translated</li>
        //! <li>whitespace will not be normalized</li>
        //! </ul>
        NonDestructive = NoStringTerminators | NoEntityTranslation,

        //! A combination of parse flags resulting in fastest possible parsing, without sacrificing important data.
        Fastest = NonDestructive | NoDataNodes,

        //! A combination of parse flags resulting in largest amount of data being extracted. 
        //! This usually results in slowest parsing.
        Full = DeclarationNode | CommentNodes | DoctypeNode | PINodes | ValidateClosingTags
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( ParsingFlags, Int32 );

#pragma warning(push)
#pragma warning(disable : 4348)
    template<typename Ch = char>
    class XmlAttribute;
    template<typename Ch = char>
    class XmlNode;
    template<typename Ch = char>
    class XmlDocument;
    template<typename Ch = char>
    class XmlParser;
#pragma warning(pop)
    template<typename Ch>
    class XmlBase
    {
    protected:
        rapidxml::xml_base<Ch>* data_ = nullptr;
    public:
        using StringView = std::basic_string_view<Ch>;
        using StringType = std::basic_string<Ch>;

        XmlBase( ) = default;
        explicit XmlBase( rapidxml::xml_base<Ch>* data )
            : data_( data )
        { }

        explicit operator bool( ) const
        {
            return data_ != nullptr;
        }

        size_t NameSize( ) const
        {
            if ( data_ )
            {
                return data_->name_size( );
            }
            return 0;
        }

        const Ch* NameText( ) const
        {
            if ( data_ )
            {
                return data_->name( );
            }
            return nullptr;
        }

        StringView Name( ) const
        {
            if ( data_ )
            {
                return StringView( data_->name( ), data_->name_size( ) );
            }
            return {};
        }


        size_t ValueSize( ) const
        {
            if ( data_ )
            {
                return data_->value_size( );
            }
            return 0;
        }

        const Ch* ValueText( ) const
        {
            if ( data_ )
            {
                return data_->value( );
            }
            return nullptr;
        }

        StringView Value( ) const
        {
            if ( data_ )
            {
                return StringView( data_->value( ), data_->value_size( ) );
            }
            return {};
        }

        inline XmlNode<Ch> Parent( ) const;

        template<WideStringLike StringT>
        StringT ToString( ) const
        {
            auto value = Value( );
            StringT result;
            ToWideString( value.data(), value.size(), result );
            return result;
        }
        template<AnsiStringLike StringT = std::string>
        StringT ToString( ) const
        {
            auto value = Value( );
            StringT result( value.data( ), value.size( ) );
            return result;
        }

    };


    template<typename Ch>
    class XmlAttribute : public XmlBase<Ch>
    {
    public:
        using Base = XmlBase<Ch>;
    private:
        using Base::data_;
        using Base::Value;
        using StringType = typename Base::StringType;
    public:
        
        XmlAttribute( ) = default;
        explicit XmlAttribute( rapidxml::xml_attribute<Ch>* data )
            : Base( data )
        {
        }

    private:
        rapidxml::xml_attribute<Ch>* Data( ) const
        {
            return static_cast< rapidxml::xml_attribute<Ch>* >( data_ );
        }
    public:
        template<BooleanType T>
        T Read( ) const
        {
            auto data = Data( );
            if ( data )
            {
                if constexpr ( std::is_same_v<Ch, wchar_t> )
                {
                    static constexpr std::wstring_view yesValue( L"yes" );
                    static constexpr std::wstring_view trueValue( L"true" );
                    static constexpr std::wstring_view noValue( L"no" );
                    static constexpr std::wstring_view falseValue( L"false" );
                    auto value = Value( );
                    switch ( value.size( ) )
                    {
                        case 2:
                        {
                            if ( value == noValue )
                            {
                                return false;
                            }
                        }
                        break;
                        case 3:
                        {
                            if ( value == yesValue )
                            {
                                return true;
                            }
                        }
                        break;
                        case 4:
                        {
                            if ( value == trueValue )
                            {
                                return true;
                            }
                        }
                        break;
                        case 5:
                        {
                            if ( value == falseValue )
                            {
                                return false;
                            }
                        }
                        break;
                    }
                }
                else
                {
                    static constexpr std::string_view yesValue( "yes" );
                    static constexpr std::string_view trueValue( "true" );
                    static constexpr std::string_view noValue( "no" );
                    static constexpr std::string_view falseValue( "false" );
                    auto value = Value( );
                    switch ( value.size( ) )
                    {
                        case 2:
                        {
                            if ( value == noValue )
                            {
                                return false;
                            }
                        }
                        break;
                        case 3:
                        {
                            if ( value == yesValue )
                            {
                                return true;
                            }
                        }
                        break;
                        case 4:
                        {
                            if ( value == trueValue )
                            {
                                return true;
                            }
                        }
                        break;
                        case 5:
                        {
                            if ( value == falseValue )
                            {
                                return false;
                            }
                        }
                        break;
                    }
                }
                StringType str( data_->value( ), data_->value_size( ) );
                return Parse<T>( str );
            }
            return {};
        }

        template<BooleanType T>
            requires std::is_same_v<T, std::optional<bool>>
        T Read( ) const
        {
            bool value = false;
            StringType str( data_->value( ), data_->value_size( ) );
            if ( TryParse( str, value ) )
            {
                return value;
            }
            return {};
        }


        template<IntegerType T>
        T Read( int radix = 10 ) const
        {
            StringType str( data_->value( ), data_->value_size( ) );
            return Parse<T>( str, radix );
        }


        template<FloatingPointType T>
            requires std::is_floating_point_v<T>
        T Read( ) const
        {
            StringType str( data_->value( ), data_->value_size( ) );
            return ParseInvariant( str );
        }

        template<typename T>
            requires std::is_enum_v<T>
        T Read( ) const
        {
            if constexpr ( std::is_same_v<wchar_t, Ch> )
            {
                StringType str( data_->value( ), data_->value_size( ) );
                return Parse<T>( str );
            }
            else
            {
                WideString str;
                ToWideString( data_->value( ), data_->value_size( ), str );
                return Parse<T>( str.c_str() );
            }
        }


        template<WideStringLike T>
        T Read( ) const
        {
            if constexpr ( std::is_same_v<wchar_t, Ch> )
            {
                return T( data_->value( ), data_->value_size( ) );
            }
            else
            {
                T result;
                ToWideString( data_->value( ), data_->value_size( ), result );
                return result;
            }
        }

        template<AnsiStringLike T>
        T Read( ) const
        {
            if constexpr ( std::is_same_v<char, Ch> )
            {
                return T( data_->value( ), data_->value_size( ) );
            }
            else
            {
                T result;
                ToAnsiString( data_->value( ), data_->value_size( ), result );
                return result;
            }
        }

        XmlAttribute<Ch> PreviousAttribute( const Ch* n = 0, std::size_t nsize = 0, bool case_sensitive = true ) const
        {
            rapidxml::xml_attribute<Ch>* data = Data( );
            if ( data )
            {
                auto node = data->previous_attribute( n, nsize, case_sensitive );
                return XmlNode<Ch>( node );
            }
            return {};
        }

        XmlAttribute<Ch> NextAttribute( const Ch* n = 0, std::size_t nsize = 0, bool case_sensitive = true ) const
        {
            rapidxml::xml_attribute<Ch>* data = Data( );
            if ( data )
            {
                auto node = data->next_attribute( n, nsize, case_sensitive );
                return XmlNode<Ch>( node );
            }
            return {};
        }

    };

    using NodeType = typename rapidxml::node_type;

    template<typename Ch>
    class XmlNode : public XmlBase<Ch>
    {
    public:
        using Base = XmlBase<Ch>;
        using StringType = typename Base::StringType;
        using StringView = typename Base::StringView;
    protected:
        using Base::data_;
    public:
        XmlNode( ) = default;
        explicit XmlNode( rapidxml::xml_node<Ch>* data )
            : Base( data )
        {
        }
    private:
        rapidxml::xml_node<Ch>* Data( ) const
        {
            return static_cast< rapidxml::xml_node<Ch>* >( Base::data_ );
        }
    public:
        XmlNodeType NodeType( ) const
        {
            rapidxml::xml_node<Ch>* data = Data( );
            return data->type( );
        }


        bool HasAttribute( const Ch* name ) const
        {
            rapidxml::xml_node<Ch>* data = Data( );
            auto attr = data->first_attribute( name );
            return attr != nullptr;
        }

        bool HasAttribute( const StringView& name ) const
        {
            rapidxml::xml_node<Ch>* data = Data( );
            auto attr = data->first_attribute( name.data( ), name.size( ) );
            return attr != nullptr;
        }

        XmlAttribute<Ch> Attribute( const Ch* name ) const
        {
            rapidxml::xml_node<Ch>* data = Data( );
            auto attr = data->first_attribute( name );
            return XmlAttribute<Ch>( attr );
        }

        XmlAttribute<Ch> Attribute( const StringView& name ) const
        {
            rapidxml::xml_node<Ch>* data = Data( );
            auto attr = data->first_attribute( name.data(), name.size() );
            return XmlAttribute<Ch>( attr );
        }

        template<typename T>
            requires (std::is_same_v<T, bool> || std::is_floating_point_v<T> || std::is_enum_v<T>)
        T Read( const Ch* name ) const
        {
            auto attr = Attribute( name );
            if ( attr )
            {
                return attr.Read<T>( );
            }
            return {};
        }

        template<typename T>
            requires ( std::is_same_v<T, bool> || std::is_floating_point_v<T> || std::is_enum_v<T> )
        T Read( const StringView& name ) const
        {
            auto attr = Attribute( name );
            if ( attr )
            {
                return attr.Read<T>( );
            }
            return {};
        }


        template<typename T>
            requires std::is_integral_v<T> && ( std::is_same_v<T, bool> == false )
        T Read( const Ch* name, int radix = 10 ) const
        {
            auto attr = Attribute( name );
            if ( attr )
            {
                return attr.Read<T>( radix );
            }
            return {};
        }

        template<typename T>
            requires std::is_integral_v<T> && ( std::is_same_v<T, bool> == false )
        T Read( const StringView& name, int radix = 10 ) const
        {
            auto attr = Attribute( name );
            if ( attr )
            {
                return attr.Read<T>( radix );
            }
            return {};
        }


        template<StringLike T>
        T Read( const Ch* name ) const
        {
            auto attr = Attribute( name );
            if ( attr )
            {
                return attr.Read<T>( );
            }
            return {};
        }

        template<StringLike T>
        T Read( const StringView& name ) const
        {
            auto attr = Attribute( name );
            if ( attr )
            {
                return attr.Read<T>( );
            }
            return {};
        }


        XmlNode<Ch> Child( const Ch* name ) const
        {
            return FirstNode( name );
        }

        XmlNode<Ch> Child( const StringView& name ) const
        {
            return FirstNode( name );
        }




        template<typename T>
            requires std::is_constructible_v<T, XmlNode<Ch> >
        std::shared_ptr<T> Child( const Ch* name ) const
        {
            XmlNode<Ch> child = FirstNode( name );
            if ( child )
            {
                auto result = std::make_shared<T>( child );
                return result;
            }
            return {};
        }

        template<typename T>
            requires std::is_constructible_v<T, XmlNode<Ch> >
        std::shared_ptr<T> Child( const StringView& name ) const
        {
            XmlNode<Ch> child = FirstNode( name );
            if ( child )
            {
                auto result = std::make_shared<T>( child );
                return result;
            }
            return {};
        }


        template<WideStringLike T>
        T Child( const Ch* name ) const
        {
            XmlNode<Ch> child = FirstNode( name );
            if ( child )
            {
                rapidxml::xml_node<Ch>* childData = static_cast< rapidxml::xml_node<Ch>* >( child.data_ );
                if constexpr ( std::is_same_v<wchar_t, Ch> )
                {
                    return T( childData->value( ), childData->value_size( ) );
                }
                else
                {
                    T result;
                    ToWideString( childData->value( ), childData->value_size( ), result );
                    return result;
                }
            }
            return {};
        }

        template<WideStringLike T>
        T Child( const StringView& name ) const
        {
            XmlNode<Ch> child = FirstNode( name );
            if ( child )
            {
                rapidxml::xml_node<Ch>* childData = static_cast< rapidxml::xml_node<Ch>* >( child.data_ );
                if constexpr ( std::is_same_v<wchar_t, Ch> )
                {
                    return T( childData->value( ), childData->value_size( ) );
                }
                else
                {
                    T result;
                    ToWideString( childData->value( ), childData->value_size( ), result );
                    return result;
                }
            }
            return {};
        }


        template<AnsiStringLike T>
        T Child( const Ch* name ) const
        {
            XmlNode<Ch> child = FirstNode( name );
            if ( child )
            {
                rapidxml::xml_node<Ch>* childData = static_cast< rapidxml::xml_node<Ch>* >( child.data_ );
                if constexpr ( std::is_same_v<char, Ch> )
                {
                    return T( childData->value( ), childData->value_size( ) );
                }
                else
                {
                    T result;
                    ToAnsiString( childData->value( ), childData->value_size( ), result );
                    return result;
                }
            }
            return {};
        }

        template<AnsiStringLike T>
        T Child( const StringView& name ) const
        {
            XmlNode<Ch> child = FirstNode( name );
            if ( child )
            {
                rapidxml::xml_node<Ch>* childData = static_cast< rapidxml::xml_node<Ch>* >( child.data_ );
                if constexpr ( std::is_same_v<char, Ch> )
                {
                    return T( childData->value( ), childData->value_size( ) );
                }
                else
                {
                    T result;
                    ToAnsiString( childData->value( ), childData->value_size( ), result );
                    return result;
                }
            }
            return {};
        }




        std::vector< XmlNode<Ch>> Children( const Ch* name ) const
        {
            std::vector<XmlNode<Ch>> result;
            auto childNode = FirstNode( name );
            if ( childNode )
            {
                do
                {
                    result.emplace_back( childNode );
                    childNode = childNode.NextSibling( name );
                } while ( childNode );
            }
            return result;
        }

        std::vector< XmlNode<Ch>> Children( const StringView& name ) const
        {
            std::vector<XmlNode<Ch>> result;
            auto childNode = FirstNode( name );
            if ( childNode )
            {
                do
                {
                    result.emplace_back( childNode );
                    childNode = childNode.NextSibling( name );
                } while ( childNode );
            }
            return result;
        }


        template<typename T>
            requires std::is_constructible_v<T, XmlNode<Ch> >
        std::vector<std::shared_ptr<T>> Children( const Ch* name ) const
        {
            std::vector<std::shared_ptr<T>> result;
            auto childNode = FirstNode( name );
            if ( childNode )
            {
                do
                {
                    auto element = std::make_shared<T>( childNode );
                    result.emplace_back( std::move( element ) );
                    childNode = childNode.NextSibling( name );
                } while ( childNode );
            }
            return result;
        }

        template<typename T>
            requires std::is_constructible_v<T, XmlNode<Ch> >
        std::vector<std::shared_ptr<T>> Children( const StringView& name ) const
        {
            std::vector<std::shared_ptr<T>> result;
            auto childNode = FirstNode( name );
            if ( childNode )
            {
                do
                {
                    auto element = std::make_shared<T>( childNode );
                    result.emplace_back( std::move( element ) );
                    childNode = childNode.NextSibling( name );
                } while ( childNode );
            }
            return result;
        }



        template<WideStringLike T>
        std::vector<T> Children( const Ch* name ) const
        {
            std::vector<T> result;
            XmlNode<Ch> child = FirstNode( name );
            if ( child )
            {
                do
                {
                    rapidxml::xml_node<Ch>* childData = static_cast< rapidxml::xml_node<Ch>* >( child.data_ );
                    if constexpr ( std::is_same_v<wchar_t, Ch> )
                    {
                        result.emplace_back( T( childData->value( ), childData->value_size( ) ) );
                    }
                    else
                    {
                        T s;
                        ToWideString( childData->value( ), childData->value_size( ), s );
                        result.emplace_back( std::move( s ) );
                    }
                    child = child.NextSibling( name );
                } while ( child );
            }
            return result;
        }

        template<WideStringLike T>
        std::vector<T> Children( const StringView& name ) const
        {
            std::vector<T> result;
            XmlNode<Ch> child = FirstNode( name );
            if ( child )
            {
                do
                {
                    rapidxml::xml_node<Ch>* childData = static_cast< rapidxml::xml_node<Ch>* >( child.data_ );
                    if constexpr ( std::is_same_v<wchar_t, Ch> )
                    {
                        result.emplace_back( T( childData->value( ), childData->value_size( ) ) );
                    }
                    else
                    {
                        T s;
                        ToWideString( childData->value( ), childData->value_size( ), s );
                        result.emplace_back( std::move( s ) );
                    }
                    child = child.NextSibling( name );
                } while ( child );
            }
            return result;
        }


        template<AnsiStringLike T>
        std::vector<T> Children( const StringView& name ) const
        {
            std::vector<T> result;
            XmlNode<Ch> child = FirstNode( name );
            if ( child )
            {
                do
                {
                    rapidxml::xml_node<Ch>* childData = static_cast< rapidxml::xml_node<Ch>* >( child.data_ );
                    if constexpr ( std::is_same_v<char, Ch> )
                    {
                        result.emplace_back( T( childData->value( ), childData->value_size( ) ) );
                    }
                    else
                    {
                        T s;
                        ToAnsiString( childData->value( ), childData->value_size( ), s );
                        result.emplace_back( std::move( s ) );
                    }
                    child = child.NextSibling( name );
                } while ( child );
            }
            return result;
        }

        template<AnsiStringLike T>
        std::vector<T> Children( const Ch* name ) const
        {
            std::vector<T> result;
            XmlNode<Ch> child = FirstNode( name );
            if ( child )
            {
                do
                {
                    rapidxml::xml_node<Ch>* childData = static_cast< rapidxml::xml_node<Ch>* >( child.data_ );
                    if constexpr ( std::is_same_v<char, Ch> )
                    {
                        result.emplace_back( T( childData->value( ), childData->value_size( ) ) );
                    }
                    else
                    {
                        T s;
                        ToAnsiString( childData->value( ), childData->value_size( ), s );
                        result.emplace_back( std::move( s ) );
                    }
                    child = child.NextSibling( name );
                } while ( child );
            }
            return result;
        }


        template<WideStringLike T>
        T Content( ) const
        {
            auto data = Data( );
            if ( data )
            {
                if constexpr ( std::is_same_v<wchar_t, Ch> )
                {
                    return T( data->value( ), data->value_size( ) );
                }
                else
                {
                    T result;
                    ToWideString( data->value( ), data->value_size( ), result );
                    return result;
                }
            }
            return {};
        }

        template<AnsiStringLike T>
        T Content( ) const
        {
            auto data = Data( );
            if ( data )
            {
                if constexpr ( std::is_same_v<char, Ch> )
                {
                    return T( data->value( ), data->value_size( ) );
                }
                else
                {
                    T result;
                    ToAnsiString( data->value( ), data->value_size( ), result );
                    return result;
                }
            }
            return {};
        }

        XmlDocument<Ch> Document( ) const;

        XmlNode<Ch> FirstNode( const Ch* n = 0, std::size_t nsize = 0, bool case_sensitive = true ) const
        {
            rapidxml::xml_node<Ch>* data = Data( );
            if ( data )
            {
                auto node = data->first_node( n, nsize, case_sensitive );
                return XmlNode<Ch>( node );
            }
            return {};
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, Ch>
        XmlNode<Ch> FirstNode( const SpanT& name, bool case_sensitive = true ) const
        {
            return FirstNode( name.data( ), name.size( ), case_sensitive );
        }

        XmlNode<Ch> LastNode( const Ch* n = 0, std::size_t nsize = 0, bool case_sensitive = true ) const
        {
            rapidxml::xml_node<Ch>* data = Data( );
            if ( data )
            {
                auto node = data->last_node( n, nsize, case_sensitive );
                return XmlNode<Ch>( node );
            }
            return {};
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, Ch>
        XmlNode<Ch> LastNode( const SpanT& name, bool case_sensitive = true ) const
        {
            return LastNode( name.data( ), name.size( ), case_sensitive );
        }

        XmlNode<Ch> PreviousSibling( const Ch* n = 0, std::size_t nsize = 0, bool case_sensitive = true ) const
        {
            rapidxml::xml_node<Ch>* data = Data( );
            if ( data )
            {
                auto node = data->previous_sibling( n, nsize, case_sensitive );
                return XmlNode<Ch>( node );
            }
            return {};
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, Ch>
        XmlNode<Ch> PreviousSibling( const SpanT& name, bool case_sensitive = true ) const
        {
            return PreviousSibling( name.data( ), name.size( ), case_sensitive );
        }


        XmlNode<Ch> NextSibling( const Ch* n = 0, std::size_t nsize = 0, bool case_sensitive = true ) const
        {
            rapidxml::xml_node<Ch>* data = Data( );
            if ( data )
            {
                auto node = data->next_sibling( n, nsize, case_sensitive );
                return XmlNode<Ch>( node );
            }
            return {};
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, Ch>
        XmlNode<Ch> NextSibling( const SpanT& name, bool case_sensitive = true ) const
        {
            return NextSibling( name.data( ), name.size( ), case_sensitive );
        }


        XmlAttribute<Ch> FirstAttribute( const Ch* n = 0, std::size_t nsize = 0, bool case_sensitive = true ) const
        {
            rapidxml::xml_attribute<Ch>* data = Data( );
            if ( data )
            {
                auto attr = data->first_attribute( n, nsize, case_sensitive );
                return XmlAttribute<Ch>( attr );
            }
            return {};
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, Ch>
        XmlNode<Ch> FirstAttribute( const SpanT& name, bool case_sensitive = true ) const
        {
            return FirstAttribute( name.data( ), name.size( ), case_sensitive );
        }

        XmlAttribute<Ch> LastAttribute( const Ch* n = 0, std::size_t nsize = 0, bool case_sensitive = true ) const
        {
            rapidxml::xml_attribute<Ch>* data = Data( );
            if ( data )
            {
                auto attr = data->last_attribute( n, nsize, case_sensitive );
                return XmlAttribute<Ch>( attr );
            }
            return {};
        }

        template<SimpleSpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, Ch>
        XmlNode<Ch> LastAttribute( const SpanT& name, bool case_sensitive = true ) const
        {
            return LastAttribute( name.data( ), name.size( ), case_sensitive );
        }


    };

    template<typename Ch>
    class XmlDocument : public XmlNode<Ch>
    {
    public:
        using Base = XmlNode<Ch>;
    private:
        using Base::data_;
    public:
        
    public:
        XmlDocument( ) = default;
        XmlDocument( rapidxml::xml_document<Ch>* document )
            : Base( document )
        {
        }
    private:
        rapidxml::xml_document<Ch>* Data( ) const
        {
            return static_cast< rapidxml::xml_document<Ch>* >( Base::data_ );
        }
    public:
        template<ParsingFlags flags>
        void Parse( Ch* str )
        {
            auto data = Data( );
            if ( data )
            {
                data->parse<static_cast< int >( flags )>( str );
            }
        }
        void Parse( Ch* str )
        {
            auto data = Data( );
            if ( data )
            {
                data->parse<0>( str );
            }
        }
    };

    template<typename Ch>
    inline XmlNode<Ch> XmlBase<Ch>::Parent( ) const
    {
        if ( data_ )
        {
            return XmlNode<Ch>( data_->parent( ) );
        }
        return {};
    }
    template<typename Ch>
    inline XmlDocument<Ch> XmlNode<Ch>::Document( ) const
    {
        auto data = Data( );
        if ( data_ )
        {
            return XmlDocument<Ch>( data->document( ) );
        }
        return {};
    }


    template<typename Ch>
    class XmlParser
    {
        mutable rapidxml::xml_document<Ch> document_;
    public:
        XmlParser( )
        { }
    private:
        rapidxml::xml_document<Ch>* Data( ) const
        {
            return &document_;
        }
    public:
        XmlDocument<Ch> Document( ) const
        {
            return XmlDocument<Ch>( Data( ) );
        }


        template<ParsingFlags flags>
        void Parse( Ch* str )
        {
            document_.parse<static_cast< int >( flags )>( str );
        }
        void Parse( Ch* str )
        {
            document_.parse<0>( str );
        }
    };


}

#endif
