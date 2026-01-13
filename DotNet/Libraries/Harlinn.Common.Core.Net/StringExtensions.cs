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
﻿using System.Net;
using System.Text;
namespace Harlinn.Common.Core.Net
{
    public static class StringExtensions
    {
        /// <summary>
        /// Creates an acronym from the given string.
        /// </summary>
        /// <param name="self"></param>
        /// <returns></returns>
        public static string? ToAcronym(this string? self)
        {
            if (string.IsNullOrEmpty(self))
            {
                return null;
            }

            var sb = new System.Text.StringBuilder();
            var count = self.Length;
            int i = 0;
            bool nextToUpper = false;
            while (i < count)
            {
                var ch = self[i];
                if (nextToUpper)
                {
                    ch = char.ToUpper(ch);
                    nextToUpper = false;
                }
                if (char.IsUpper(ch))
                {
                    sb.Append(ch);
                }
                else if (ch == '_' || ch == ' ')
                {
                    nextToUpper = true;
                }
                i++;
            }
            return sb.ToString();
        }

        /// <summary>
        /// Returns a copy of the input string with the first character converted to uppercase.
        /// </summary>
        /// <param name="self">The string to convert. Can be null or empty.</param>
        /// <returns>A new string with the first character in uppercase; or null if the input string is null or empty.</returns>
        public static string? FirstToUpper(this string? self)
        {
            if (string.IsNullOrEmpty(self))
            {
                return null;
            }

            var chars = self.ToCharArray();
            chars[0] = char.ToUpper(chars[0]);
            return new string(chars);
        }

        /// <summary>
        /// Returns a copy of the input string with the first character converted to lowercase.
        /// </summary>
        /// <param name="self">The string to convert. Can be null or empty.</param>
        /// <returns>A new string with the first character in lowercase; or null if the input string is null or empty.</returns>
        public static string? FirstToLower(this string? self)
        {
            if (string.IsNullOrEmpty(self))
            {
                return null;
            }

            var chars = self.ToCharArray();
            chars[0] = char.ToLower(chars[0]);
            return new string(chars);
        }

        /// <summary>
        /// Encodes a string to be safely displayed in HTML by replacing special characters with their corresponding
        /// HTML entities.
        /// </summary>
        /// <param name="self">The string to encode. Can be null.</param>
        /// <returns>A string containing the HTML-encoded representation of the input, or null if the input is null or empty.</returns>
        public static string? HtmlEncode(this string? self)
        {
            if (string.IsNullOrEmpty(self))
            {
                return null;
            }
            return WebUtility.HtmlEncode(self);
        }

        /// <summary>
        /// Decodes a string that contains HTML-encoded characters into a decoded string.   
        /// </summary>
        /// <param name="self">The HTML-encoded string to decode. Can be null.</param>
        /// <returns>A decoded string with HTML entities converted to their corresponding characters, or null if the input is
        /// null or empty.</returns>
        public static string? HtmlDecode(this string? self)
        {
            if (string.IsNullOrEmpty(self))
            {
                return null;
            }
            return WebUtility.HtmlDecode(self);
        }

        public static string ToPascalCase(this string? self)
        {
            if (string.IsNullOrWhiteSpace(self))
            {
                return string.Empty;
            }

            // Treat common separators as word boundaries
            var separators = new[] { '_', '-', ' ', '\t' };
            var parts = self.Split(separators, StringSplitOptions.RemoveEmptyEntries);

            var sb = new StringBuilder(parts.Length * 8);
            foreach (var part in parts)
            {
                if (part.Length == 0) continue;

                // Normalize to lower for predictable casing, but preserve non-letter leading characters
                var lower = part.ToLowerInvariant();

                // If first character is a letter, uppercase it; otherwise leave as-is
                var firstChar = lower[0];
                if (char.IsLetter(firstChar))
                {
                    sb.Append(char.ToUpperInvariant(firstChar));
                    if (lower.Length > 1)
                    {
                        sb.Append(lower.AsSpan(1));
                    }
                }
                else
                {
                    // If first char is not a letter (digit, underscore etc.), append the part trimmed of leading non-alphanumerics
                    sb.Append(lower.TrimStart(c => !char.IsLetterOrDigit(c)));
                }
            }

            return sb.ToString();
        }

        // Helper for trimming with predicate using Span when available
        private static string TrimStart(this string s, Func<char, bool> predicate)
        {
            int i = 0;
            while (i < s.Length && predicate(s[i])) i++;
            return i == 0 ? s : s.Substring(i);
        }


    }
}
