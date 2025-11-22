using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Net.Mime.MediaTypeNames;

namespace Harlinn.Common.Core.Net.Tokens
{

    public struct Token
    {
        readonly TokenType _tokenType;
        readonly int _lineNumber;
        readonly int _position;
        readonly string _text;

        public Token()
        {
            _tokenType = TokenType.Unknown;
            _lineNumber = 0;
            _position = 0;
            _text = string.Empty;
        }

        public Token(TokenType tokenType, int lineNumber, int position, string text)
        {
            _tokenType = tokenType;
            _lineNumber = lineNumber;
            _position = position;
            _text = text;
        }

        public TokenType TokenType => _tokenType;

        public int LineNumber => _lineNumber;

        public int Position => _position;

        public string Text => _text;
    }


}
