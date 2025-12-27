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

public class KeyEncryptionsDataType
{
    readonly int _keyId = 0;
    readonly byte[]? _thumbprint;
    readonly string _cryptType = string.Empty;
    readonly string? _cryptTypeDesc;
    readonly byte[]? _cryptProperty;

    public KeyEncryptionsDataType( )
    {
    }

    public KeyEncryptionsDataType(int keyId,
        byte[]? thumbprint,
        string cryptType,
        string? cryptTypeDesc,
        byte[]? cryptProperty)
    {
        _keyId = keyId;
        _thumbprint = thumbprint;
        _cryptType = cryptType;
        _cryptTypeDesc = cryptTypeDesc;
        _cryptProperty = cryptProperty;
    }

    public int KeyId => _keyId;
    public byte[]? Thumbprint => _thumbprint;
    public string CryptType => _cryptType;
    public string? CryptTypeDesc => _cryptTypeDesc;
    public byte[]? CryptProperty => _cryptProperty;
}
