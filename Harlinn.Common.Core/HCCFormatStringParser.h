#pragma once
#ifndef HARLINN_COMMON_CORE_HCCFORMATSTRINGPARSER_H_
#define HARLINN_COMMON_CORE_HCCFORMATSTRINGPARSER_H_

#include "HCCString.h"

namespace Harlinn::Common::Core::Formatting
{

    enum class FormatStringSectionType
    {
        Unknown,
        Text,
        Specification
    };



    template<typename CharT>
    class FormatStringSection : public std::basic_string<CharT>
    {
    public:
        using CharType = CharT;
        using Base = std::basic_string<CharT>;
    private:
        FormatStringSectionType sectionType_ = FormatStringSectionType::Unknown;
    public:
        FormatStringSection( ) = default;
        FormatStringSection( FormatStringSectionType sectionType, const CharType* text, size_t textLength )
            : Base( text, textLength ), sectionType_( sectionType )
        { }

        FormatStringSection( FormatStringSectionType sectionType, const CharType* text, const CharType* textEnd )
            : Base( text, textEnd ), sectionType_( sectionType )
        {
        }

        constexpr FormatStringSectionType SectionType( ) const noexcept
        {
            return sectionType_;
        }

    };

    /// <summary>
    /// Splits a format string into sections, a section will either hold
    /// text to be copied to the output, or a format specification.
    /// </summary>
    /// <typeparam name="CharT">The character type</typeparam>
    /// <typeparam name="expectedSectionCount">The number of sections to reserve space for</typeparam>
    /// <typeparam name="workBufferSize">The number of characters to reserve spece for in the work area/buffer</typeparam>
    template<typename CharT, size_t expectedSectionCount = 10, size_t workBufferSize = 256>
    class FormatStringParser
    {
    public:
        using CharType = CharT;
        using StringViewType = std::basic_string_view<const CharType>;
        using Section = FormatStringSection<CharType>;
        using Sections = boost::container::small_vector<Section, expectedSectionCount>;
        using Buffer = boost::container::small_vector<CharType, workBufferSize>;

        using value_type = typename Sections::value_type;
        using size_type = typename Sections::size_type;
        using const_iterator = typename Sections::const_iterator;
        using const_reference = typename Sections::const_reference;

        static constexpr CharType LeftBrace = static_cast< CharType >( '{' );
        static constexpr CharType RightBrace = static_cast< CharType >( '}' );
    private:
        StringViewType formatString_;
        Buffer buffer_;
        Sections sections_;
        bool isValid_ = false;
    public:
        explicit FormatStringParser( StringViewType formatString )
            : formatString_( formatString )
        {
            Parse( );
        }

        explicit FormatStringParser( const CharType* formatString )
            : FormatStringParser( StringViewType( formatString ) )
        { }

        constexpr explicit operator bool( ) const noexcept
        {
            return isValid_;
        }

        constexpr bool IsValid( ) const noexcept
        {
            return isValid_;
        }

        size_type size( ) const noexcept
        {
            return sections_.size( );
        }
        const_iterator begin( ) const noexcept
        {
            return sections_.begin( );
        }
        const_iterator end( ) const noexcept
        {
            return sections_.end( );
        }

        const_reference operator[]( size_type index ) const noexcept
        {
            return sections_[ index ];
        }

    private:
        void Parse( )
        {
            const CharType* ptr = formatString_.data( );
            const CharType* endPtr = formatString_.data( ) + formatString_.size();
            
            int unmatchedLeftBraces = 0;
            while ( ptr < endPtr )
            {
                CharType current = *ptr;
                switch ( current )
                {
                    case LeftBrace:
                    {
                        if ( ( ( ptr + 1 ) < endPtr ) && ( *( ptr + 1 ) ) == LeftBrace )
                        {
                            buffer_.emplace_back( current );
                            if ( unmatchedLeftBraces )
                            {
                                buffer_.emplace_back( current );
                            }
                            ptr += 2;
                        }
                        else
                        {
                            if ( unmatchedLeftBraces == 0 )
                            {
                                AddSection( FormatStringSectionType::Text );
                            }
                            buffer_.emplace_back( current );
                            ++unmatchedLeftBraces;
                            ++ptr;
                        }
                    }
                    break;
                    case RightBrace:
                    {
                        if ( ( ( ptr + 1 ) < endPtr ) && ( *( ptr + 1 ) ) == RightBrace )
                        {
                            buffer_.emplace_back( current );
                            if ( unmatchedLeftBraces )
                            {
                                buffer_.emplace_back( current );
                                unmatchedLeftBraces -= 2;
                                if ( unmatchedLeftBraces == 0 )
                                {
                                    AddSection( FormatStringSectionType::Specification );
                                }
                            }
                            ptr += 2;
                        }
                        else
                        {
                            buffer_.emplace_back( current );
                            if ( unmatchedLeftBraces == 1 )
                            {
                                AddSection( FormatStringSectionType::Specification );
                            }
                            --unmatchedLeftBraces;
                            ++ptr;
                        }
                    }
                    break;
                    default:
                    {
                        buffer_.emplace_back( current );
                        ++ptr;
                    }
                    break;
                }
            }
            if ( unmatchedLeftBraces == 0 )
            {
                AddSection( FormatStringSectionType::Text );
                isValid_ = true;
            }
        }

        void AddSection( FormatStringSectionType sectionType )
        {
            if ( !buffer_.empty( ) )
            {
                sections_.emplace_back( sectionType, buffer_.data( ), buffer_.size( ) );
                buffer_.clear( );
            }
        }

    };
}

#endif
