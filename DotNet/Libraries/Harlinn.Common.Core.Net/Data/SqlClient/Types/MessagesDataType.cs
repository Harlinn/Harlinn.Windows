/*
   Copyright 2024-2025 Espen Harlinn

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
using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class MessagesDataType
{
    readonly int _messageId = 0;
    readonly short _languageId = 0;
    readonly byte? _severity;
    readonly bool _isEventLogged = false;
    readonly string _text = string.Empty;

    public MessagesDataType( )
    {
    }

    public MessagesDataType(int messageId,
        short languageId,
        byte? severity,
        bool isEventLogged,
        string text)
    {
        _messageId = messageId;
        _languageId = languageId;
        _severity = severity;
        _isEventLogged = isEventLogged;
        _text = text;
    }

    public int MessageId => _messageId;
    public short LanguageId => _languageId;
    public byte? Severity => _severity;
    public bool IsEventLogged => _isEventLogged;
    public string Text => _text;
}
