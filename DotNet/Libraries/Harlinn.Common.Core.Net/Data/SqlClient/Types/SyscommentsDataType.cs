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
using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class SyscommentsDataType
{
    readonly int _id = 0;
    readonly short? _number;
    readonly short _colid = 0;
    readonly short _status = 0;
    readonly byte[]? _ctext;
    readonly short? _texttype;
    readonly short? _language;
    readonly bool _encrypted = false;
    readonly bool _compressed = false;
    readonly string? _text;

    public SyscommentsDataType( )
    {
    }

    public SyscommentsDataType(int id,
        short? number,
        short colid,
        short status,
        byte[]? ctext,
        short? texttype,
        short? language,
        bool encrypted,
        bool compressed,
        string? text)
    {
        _id = id;
        _number = number;
        _colid = colid;
        _status = status;
        _ctext = ctext;
        _texttype = texttype;
        _language = language;
        _encrypted = encrypted;
        _compressed = compressed;
        _text = text;
    }

    public int Id => _id;
    public short? Number => _number;
    public short Colid => _colid;
    public short Status => _status;
    public byte[]? Ctext => _ctext;
    public short? Texttype => _texttype;
    public short? Language => _language;
    public bool Encrypted => _encrypted;
    public bool Compressed => _compressed;
    public string? Text => _text;
}
