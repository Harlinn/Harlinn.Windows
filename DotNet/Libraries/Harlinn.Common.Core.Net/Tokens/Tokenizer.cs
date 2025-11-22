using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Tokens
{
    public class Tokenizer
    {
        List<Token> _tokens = [];
        int _lineNumber;

        private static bool IsIdentifierFirst(char c)
        {
            return c == '_' || char.IsLetter(c);
        }

        private static bool IsIdentifier(char c)
        {
            return c == '_' || char.IsLetterOrDigit(c);
        }

        private static bool TryGetIdentifier(ReadOnlySpan<Char> input, int start, out TokenType tokenType, [NotNullWhen(true)] out string? token)
        {
            var index = start;
            var length = input.Length;
            if (index < length)
            {
                var c1 = input[index];
                if (IsIdentifierFirst(c1))
                {
                    index++;
                    while (index < length)
                    {
                        var c2 = input[index];
                        if (IsIdentifier(c2) == false)
                        {
                            break;
                        }
                        index++;
                    }
                }
            }
            if (index != start)
            {
                tokenType = TokenType.Identifier;
                token = new string(input.Slice(start, index - start));
                return true;
            }
            else
            {
                tokenType = TokenType.Unknown;
                token = null;
                return false;
            }
        }

        private static TokenType GetSingleLetterTokenType(char c)
        {
            switch (c)
            {
                case '+':
                    return TokenType.Plus;
                case '-':
                    return TokenType.Minus;
                case '*':
                    return TokenType.Multiply;
                case '/':
                    return TokenType.Divide;
                case '%':
                    return TokenType.Modulus;
                case '^':
                    return TokenType.XOr;
                case '.':
                    return TokenType.Period;
                case ',':
                    return TokenType.Comma;
                case ':':
                    return TokenType.Colon;
                case ';':
                    return TokenType.SemiColon;
                case '!':
                    return TokenType.Exclamation;
                case '~':
                    return TokenType.Tilde;
                case '|':
                    return TokenType.BitwiseOr;
                case '&':
                    return TokenType.BitwiseAnd;
                case '=':
                    return TokenType.Assign;
                case '"':
                    return TokenType.QuestionMark;
                case '\'':
                    return TokenType.Apostrophe;
                case '?':
                    return TokenType.QuestionMark;
                case '(':
                    return TokenType.LParen;
                case ')':
                    return TokenType.RParen;
                case '{':
                    return TokenType.LBrace;
                case '}':
                    return TokenType.RBrace;
                case '[':
                    return TokenType.LBracket;
                case ']':
                    return TokenType.RBracket;
                case '<':
                    return TokenType.LessThan;
                case '>':
                    return TokenType.GreaterThan;
                default:
                    return TokenType.Unknown;
            }
        }

        private static TokenType GetTwoLetterTokenType(char first, char second)
        {
            switch (first)
            {
                case '+':
                    if(second == '+')
                    {
                        return TokenType.PlusPlus;
                    }
                    else if (second == '=')
                    {
                        return TokenType.PlusAssign;
                    }
                    return TokenType.Unknown;
                case '-':
                    if (second == '-')
                    {
                        return TokenType.MinusMinus;
                    }
                    else if (second == '=')
                    {
                        return TokenType.MinusAssign;
                    }
                    return TokenType.Unknown;
                case '*':
                    if (second == '=')
                    {
                        return TokenType.MultiplyAssign;
                    }
                    return TokenType.Unknown;
                case '/':
                    if (second == '=')
                    {
                        return TokenType.DivideAssign;
                    }
                    return TokenType.Unknown;
                case '%':
                    if (second == '=')
                    {
                        return TokenType.ModulusAssign;
                    }
                    return TokenType.Unknown;
                case '^':
                    if (second == '=')
                    {
                        return TokenType.XOrAssign;
                    }
                    return TokenType.Unknown;
                case '!':
                    if (second == '=')
                    {
                        return TokenType.NotEqual;
                    }
                    return TokenType.Unknown;
                case '|':
                    if (second == '|')
                    {
                        return TokenType.LogicalOr;
                    }
                    else if (second == '=')
                    {
                        return TokenType.BitwiseOrAssign;
                    }
                    return TokenType.Unknown;
                case '&':
                    if (second == '&')
                    {
                        return TokenType.LogicalAnd;
                    }
                    else if (second == '=')
                    {
                        return TokenType.BitwiseAndAssign;
                    }
                    return TokenType.Unknown;
                case '=':
                    if (second == '=')
                    {
                        return TokenType.Equal;
                    }
                    return TokenType.Unknown;
                case '<':
                    if(second == '<')
                    {
                        return TokenType.LeftShift;
                    }
                    if (second == '=')
                    {
                        return TokenType.LessOrEqual;
                    }
                    return TokenType.Unknown;
                case '>':
                    if (second == '>')
                    {
                        return TokenType.RightShift;
                    }
                    if (second == '=')
                    {
                        return TokenType.GreaterOrEqual;
                    }
                    return TokenType.Unknown;
                default:
                    return TokenType.Unknown;
            }
        }

        private static TokenType GetThreeLetterTokenType(char first, char second, char third)
        {
            switch (first)
            {
                case '|':
                    if(second == '|' && third == '=')
                    {
                        return TokenType.LogicalOrAssign;
                    }
                    return TokenType.Unknown;
                case '&':
                    if(second == '&' && third == '=')
                    {
                        return TokenType.LogicalAndAssign;
                    }
                    return TokenType.Unknown;
                case '<':
                    if(second == '<' && third == '=')
                    {
                        return TokenType.LeftShiftAssign;
                    }
                    return TokenType.Unknown;
                case '>':
                    if(second == '>')
                    {
                        if(third == '>')
                        {
                            return TokenType.UnsignedRightShift;
                        }
                        else if(third == '=')
                        {
                            return TokenType.RightShiftAssign;
                        }
                    }
                    return TokenType.Unknown;
                default:
                    return TokenType.Unknown;
            }
        }


        private static TokenType GetFourLetterTokenType(char first, char second, char third, char fourth)
        {
            switch (first)
            {
                case '>':
                    if( second == '>' && third == '>' && fourth == '=' )
                    {
                        return TokenType.UnsignedRightShiftAssign;
                    }
                    return TokenType.Unknown;
                default:
                    return TokenType.Unknown;
            }
        }


        private static bool TryGetOneLetterToken(ReadOnlySpan<Char> input, int start, out TokenType tokenType, [NotNullWhen(true)] out string? token)
        {
            var index = start;
            var length = input.Length;
            if (length > index + 1)
            {
                var first = input[index];
                tokenType = GetSingleLetterTokenType(first);
                if (tokenType != TokenType.Unknown)
                {
                    token = new string(input.Slice(index, 1));
                    return true;
                }
            }
            tokenType = TokenType.Unknown;
            token = null;
            return false;
        }

        private static bool TryGetTwoLetterToken(ReadOnlySpan<Char> input, int start, out TokenType tokenType, [NotNullWhen(true)] out string? token)
        {
            var index = start;
            var length = input.Length;
            if (length > index + 2)
            {
                var first = input[index];
                var second = input[index + 1];
                tokenType = GetTwoLetterTokenType(first, second);
                if (tokenType != TokenType.Unknown)
                {
                    token = new string(input.Slice(index, 2));
                    return true;
                }
            }
            tokenType = TokenType.Unknown;
            token = null;
            return false;
        }

        private static bool TryGetThreeLetterToken(ReadOnlySpan<Char> input, int start, out TokenType tokenType, [NotNullWhen(true)] out string? token)
        {
            var index = start;
            var length = input.Length;
            if (length > index + 3)
            {
                var first = input[index];
                var second = input[index + 1];
                var third = input[index + 2];
                tokenType = GetThreeLetterTokenType(first, second, third);
                if (tokenType != TokenType.Unknown)
                {
                    token = new string(input.Slice(index, 3));
                    return true;
                }
            }
            tokenType = TokenType.Unknown;
            token = null;
            return false;
        }

        private static bool TryGetFourLetterToken(ReadOnlySpan<Char> input, int start, out TokenType tokenType, [NotNullWhen(true)] out string? token)
        {
            var index = start;
            var length = input.Length;
            if (length > index + 4)
            {
                var first = input[index];
                var second = input[index + 1];
                var third = input[index + 2];
                var fourth = input[index + 3];
                tokenType = GetFourLetterTokenType(first, second, third, fourth);
                if (tokenType != TokenType.Unknown)
                {
                    token = new string(input.Slice(index, 4));
                    return true;
                }
            }
            tokenType = TokenType.Unknown;
            token = null;
            return false;
        }


        private static bool TryGetOtherToken(ReadOnlySpan<Char> input, int start, out TokenType tokenType, [NotNullWhen(true)] out string? token)
        {
            if (TryGetFourLetterToken(input, start, out tokenType, out token))
            {
                return true;
            }
            else if (TryGetThreeLetterToken(input, start, out tokenType, out token))
            {
                return true;
            }
            else if (TryGetTwoLetterToken(input, start, out tokenType, out token))
            {
                return true;
            }
            else if (TryGetOneLetterToken(input, start, out tokenType, out token))
            {
                return true;
            }
            return false;
        }

        private static bool TryGetWhitespace(ReadOnlySpan<Char> input, int start, out int whitespacelength)
        {
            var index = start;
            var length = input.Length;
            while (index < length)
            {
                var c = input[index];
                if (char.IsWhiteSpace(c))
                {
                    index++;
                }
            }
            whitespacelength = index - start;
            return whitespacelength != 0;
        }


        public void TryTokenize(ReadOnlySpan<Char> self)
        {
            TokenType tokenType;
            string? tokenText;
            var index = 0;
            var length = self.Length;
            while (index < length)
            {
                if (TryGetOtherToken(self, index, out tokenType, out tokenText))
                {
                    var token = new Token(tokenType, _lineNumber, index, tokenText);
                    _tokens.Add(token);
                    index += tokenText.Length;
                }
                else if (TryGetIdentifier(self, index, out tokenType, out tokenText))
                {
                    var token = new Token(tokenType, _lineNumber, index, tokenText);
                    _tokens.Add(token);
                    index += tokenText.Length;
                }
                else if (TryGetWhitespace(self, index, out var whitespacelength))
                {
                    var token = new Token(tokenType, _lineNumber, index, tokenText);
                    _tokens.Add(token);
                    index += whitespacelength;
                }
                else
                {
                    throw new Exception("Unexpected ");
                }
            }
        }
    }


}
