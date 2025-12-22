using System.Net;
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

    }
}
