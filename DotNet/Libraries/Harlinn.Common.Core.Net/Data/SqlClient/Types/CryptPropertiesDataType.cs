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

public class CryptPropertiesDataType
{
    readonly byte _class = 0;
    readonly string? _classDesc;
    readonly int _majorId = 0;
    readonly byte[] _thumbprint = Array.Empty<byte>();
    readonly string _cryptType = string.Empty;
    readonly string? _cryptTypeDesc;
    readonly byte[] _cryptProperty = Array.Empty<byte>();

    public CryptPropertiesDataType( )
    {
    }

    public CryptPropertiesDataType(byte class__,
        string? classDesc,
        int majorId,
        byte[] thumbprint,
        string cryptType,
        string? cryptTypeDesc,
        byte[] cryptProperty)
    {
        _class = class__;
        _classDesc = classDesc;
        _majorId = majorId;
        _thumbprint = thumbprint;
        _cryptType = cryptType;
        _cryptTypeDesc = cryptTypeDesc;
        _cryptProperty = cryptProperty;
    }

    public byte Class => _class;
    public string? ClassDesc => _classDesc;
    public int MajorId => _majorId;
    public byte[] Thumbprint => _thumbprint;
    public string CryptType => _cryptType;
    public string? CryptTypeDesc => _cryptTypeDesc;
    public byte[] CryptProperty => _cryptProperty;
}
