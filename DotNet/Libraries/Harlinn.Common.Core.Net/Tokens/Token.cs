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
﻿using System;
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
