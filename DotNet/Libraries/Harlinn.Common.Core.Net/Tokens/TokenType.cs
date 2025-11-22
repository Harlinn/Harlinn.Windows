namespace Harlinn.Common.Core.Net.Tokens
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
