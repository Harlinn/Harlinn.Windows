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

public class CryptographicProvidersDataType
{
    readonly int _providerId = 0;
    readonly string _name = string.Empty;
    readonly Guid? _guid;
    readonly string? _version;
    readonly string? _dllPath;
    readonly bool _isEnabled = false;

    public CryptographicProvidersDataType( )
    {
    }

    public CryptographicProvidersDataType(int providerId,
        string name,
        Guid? guid,
        string? version,
        string? dllPath,
        bool isEnabled)
    {
        _providerId = providerId;
        _name = name;
        _guid = guid;
        _version = version;
        _dllPath = dllPath;
        _isEnabled = isEnabled;
    }

    public int ProviderId => _providerId;
    public string Name => _name;
    public Guid? Guid => _guid;
    public string? Version => _version;
    public string? DllPath => _dllPath;
    public bool IsEnabled => _isEnabled;
}
