/*
    Copyright 2024-2026 Espen Harlinn
 
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
﻿namespace Harlinn.Common.Core.Net.Tokens
{
    public enum TokenType
    {
        Unknown,
        Whitespace,
        Comment,
        Identifier,

        // Four letter tokens

        // >>>=
        UnsignedRightShiftAssign,
        
        // Three letter tokens
        
        // ||=
        LogicalOrAssign,
        // &&=
        LogicalAndAssign,
        // <<=
        LeftShiftAssign,
        // >>=
        RightShiftAssign,
        // >>>
        UnsignedRightShift,
        
        // Two letter tokens

        // ++
        PlusPlus,
        // +=
        PlusAssign,
        // --
        MinusMinus,
        // -=
        MinusAssign,
        // *=
        MultiplyAssign,
        // /=
        DivideAssign,
        // %=
        ModulusAssign,
        // ^=
        XOrAssign,
        // !=
        NotEqual,
        // ||
        LogicalOr,
        // |=
        BitwiseOrAssign,
        // &&
        LogicalAnd, 
        // &=
        BitwiseAndAssign,
        // ==
        Equal,
        // <<
        LeftShift,
        // >>
        RightShift,
        // <=
        LessOrEqual,
        // >=
        GreaterOrEqual,

        // single letter tokens

        // +
        Plus,
        // -
        Minus,
        // *
        Multiply,
        // /
        Divide,
        // %
        Modulus,
        // ^
        XOr,
        // .
        Period,
        // ,
        Comma,
        // :
        Colon,
        // ;
        SemiColon,
        // !
        Exclamation,
        // ~
        Tilde,
        // &
        BitwiseAnd,
        // |
        BitwiseOr,
        // =
        Assign,
        // "
        QuotationMark,
        // '
        Apostrophe,
        // ?
        QuestionMark,
        // (
        LParen,
        // )
        RParen,

        // [
        LBracket,
        // ]
        RBracket,

        // {
        LBrace,
        // }
        RBrace,

        // <
        LessThan,
        // >
        GreaterThan


    }


}
