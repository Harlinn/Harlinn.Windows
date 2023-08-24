#pragma once
#ifndef HCCTOKENIZER_H_
#define HCCTOKENIZER_H_

#include "HCCDef.h"

namespace Harlinn::Common::Core
{
    enum class TokenType : Byte
    {
        Unknown,
        Symbol,
        // (
        LParen = static_cast< Byte >('('),
        // )
        RParen = static_cast< Byte >( ')' ),
        // {
        LBrace = static_cast< Byte >( '{' ),
        // }
        RBrace = static_cast< Byte >( '}' ),
        // [ 
        LBracket = static_cast< Byte >( '[' ),
        // ]
        RBracket = static_cast< Byte >( ']' ),
        // +
        Plus = static_cast< Byte >( '+' ),
        // -
        Minus = static_cast< Byte >( '-' ),
        // *
        Asterisk = static_cast< Byte >( '*' ),
        Multiply = Asterisk,
        // /
        Slash = static_cast< Byte >( '/' ),
        Divide = Slash,
        Solidus = Slash,
        Virgule = Slash,

        // %
        Percent = static_cast< Byte >( '%' ),
        Remainder = Percent,

        // |
        VerticalBar = static_cast< Byte >( '|' ),
        Pipe = VerticalBar,
        BitwiseOr = VerticalBar,

        // ^
        Caret = static_cast< Byte >( '^' ),
        BitwiseXor = Caret,
        // ~
        Tilde = static_cast< Byte >( '~' ),
        BitwiseNot = Tilde,
        // &
        Ampersand = static_cast< Byte >( '&' ),
        BitwiseAnd = Ampersand,
        AddressOf = Ampersand,

        // <
        Less = static_cast< Byte >( '<' ),

        // >
        Greater = static_cast< Byte >( '>' ),

        // .
        Period = static_cast< Byte >( '.' ),
        Dot = Period,

        // =
        EqualsSign = static_cast< Byte >( '=' ),
        Assign = EqualsSign,




        

    };

    template<typename CharT> 
    class Tokenizer
    {

    };
}


#endif
