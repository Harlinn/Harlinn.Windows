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
﻿using System.ComponentModel.DataAnnotations;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net
{

    public static class StringTokenizerExtensions
    {
        private static bool IsIdentifierFirst(char c)
        {
            return c == '_' || char.IsLetter(c);
        }

        private static bool IsIdentifier(char c)
        {
            return c == '_' || char.IsLetterOrDigit(c);
        }

        private static bool TryGetIdentifier(this ReadOnlySpan<Char> self, int start, [NotNullWhen(true)] out string? token)
        {
            var index = start;
            var length = self.Length;
            if (index < length)
            {
                var c1 = self[index];
                if (IsIdentifierFirst(c1))
                {
                    index++;
                    while (index < length)
                    {
                        var c2 = self[index];
                        if (IsIdentifier(c2) == false)
                        {
                            break;
                        }
                        index++;
                    }
                }
            }
            if(index != start)
            {
                token = new string( self.Slice(start, index - start) );
            }
            else
            {
                token = null;
            }
            return index != start;
        }

        private static bool IsOtherTokenFirst(char c)
        {
            switch(c)
            {
                case '+': 
                    return true;
                case '-':
                    return true;
                case '*':
                    return true;
                case '/':
                    return true;
                case '%':
                    return true;
                case '^':
                    return true;
                case '.':
                    return true;
                case ',':
                    return true;
                case ':':
                    return true;
                case ';':
                    return true;
                case '!':
                    return true;
                case '~':
                    return true;
                case '|':
                    return true;
                case '&':
                    return true;
                case '=':
                    return true;
                case '"':
                    return true;
                case '\'':
                    return true;
                case '?':
                    return true;
                case '(':
                    return true;
                case ')':
                    return true;
                case '{':
                    return true;
                case '}':
                    return true;
                case '[':
                    return true;
                case ']':
                    return true;
                case '<':
                    return true;
                case '>':
                    return true;
                default:
                    return false;
            }
        }

        private static bool IsOtherTwoLetterToken(char first, char second)
        {
            switch (first)
            {
                case '+':
                    return second == '+' || second == '=';
                case '-':
                    return second == '-' || second == '=';
                case '*':
                    return second == '=';
                case '/':
                    return second == '=';
                case '%':
                    return second == '=';
                case '^':
                    return second == '=';
                case '!':
                    return second == '=';
                case '|':
                    return second == '|' || second == '=';
                case '&':
                    return second == '&' || second == '=';
                case '=':
                    return second == '=';
                case '<':
                    return second == '<' || second == '=';
                case '>':
                    return second == '>' || second == '=';
                default:
                    return false;
            }
        }

        private static bool IsOtherThreeLetterToken(char first, char second, char third)
        {
            switch (first)
            {
                case '|':
                    return second == '|' && third == '=';
                case '&':
                    return second == '&' && third == '=';
                case '<':
                    return second == '<' && third == '=';
                case '>':
                    return second == '>' && (third == '>' || third == '=');
                default:
                    return false;
            }
        }

        private static bool IsOtherFourLetterToken(char first, char second, char third, char fourth)
        {
            switch (first)
            {
                case '>':
                    return second == '>' && third == '>' && fourth == '=';
                default:
                    return false;
            }
        }



        private static bool TryGetOneLetterToken(this ReadOnlySpan<Char> self, int start, [NotNullWhen(true)] out string? token)
        {
            var index = start;
            var length = self.Length;
            if (length > index + 1)
            {
                var first = self[index];
                if (IsOtherTokenFirst(first))
                {
                    token = new string(self.Slice(index, 1));
                    return true;
                }
            }
            token = null;
            return false;
        }

        private static bool TryGetTwoLetterToken(this ReadOnlySpan<Char> self, int start, [NotNullWhen(true)] out string? token)
        {
            var index = start;
            var length = self.Length;
            if (length > index + 2)
            {
                var first = self[index];
                var second = self[index + 1];
                if (IsOtherTwoLetterToken(first, second))
                {
                    token = new string(self.Slice(index, 2));
                    return true;
                }
            }
            token = null;
            return false;
        }

        private static bool TryGetThreeLetterToken(this ReadOnlySpan<Char> self, int start, [NotNullWhen(true)] out string? token)
        {
            var index = start;
            var length = self.Length;
            if(length > index + 3)
            {
                var first = self[index];
                var second = self[index + 1];
                var third = self[index + 2];
                if(IsOtherThreeLetterToken(first, second, third))
                {
                    token = new string(self.Slice( index, 3 ));
                    return true;
                }
            }
            token = null;
            return false;
        }

        private static bool TryGetFourLetterToken(this ReadOnlySpan<Char> self, int start, [NotNullWhen(true)] out string? token)
        {
            var index = start;
            var length = self.Length;
            if (length > index + 4)
            {
                var first = self[index];
                var second = self[index + 1];
                var third = self[index + 2];
                var fourth = self[index + 3];
                if (IsOtherFourLetterToken(first, second, third, fourth))
                {
                    token = new string(self.Slice(index, 4));
                    return true;
                }
            }
            token = null;
            return false;
        }


        private static bool TryGetOtherToken(this ReadOnlySpan<Char> self, int start, [NotNullWhen(true)] out string? token)
        {
            if (TryGetFourLetterToken(self, start, out token))
            {
                return true;
            }
            else if (TryGetThreeLetterToken(self, start, out token))
            { 
                return true; 
            }
            else if (TryGetTwoLetterToken(self, start, out token))
            {
                return true;
            }
            else if (TryGetOneLetterToken(self, start, out token))
            {
                return true;
            }
            return false;
        }

        private static bool TryGetWhitespace(this ReadOnlySpan<Char> self, int start, out int whitespacelength)
        {
            var index = start;
            var length = self.Length;
            while (index < length)
            {
                var c = self[index];
                if (char.IsWhiteSpace(c))
                {
                    index++;
                }
            }
            whitespacelength = index - start;
            return whitespacelength != 0;
        }


        public static bool TryTokenize(this ReadOnlySpan<Char> self, out string[] tokens)
        {
            var list = new List<string>();
            var index = 0;
            var length = self.Length;
            while (index < length)
            {
                if(self.TryGetOtherToken(index, out var token))
                {
                    list.Add(token);
                    index += token.Length;
                }
                else if (self.TryGetIdentifier(index, out var identfier))
                {
                    list.Add(identfier);
                    index += identfier.Length;
                }
                else if (self.TryGetWhitespace(index, out var whitespacelength))
                {
                    index += whitespacelength;
                }
                else
                {
                    throw new Exception("Unexpected ");
                }
            }
            if (list.Count > 0)
            {
                tokens = list.ToArray();
                return true;
            }
            else
            {
                tokens =null;
                return false;
            }
        }

    }
}
