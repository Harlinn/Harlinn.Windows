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

public class DmOsLoadedModulesDataType
{
    readonly byte[] _baseAddress = Array.Empty<byte>();
    readonly string? _fileVersion;
    readonly string? _productVersion;
    readonly bool? _debug;
    readonly bool? _patched;
    readonly bool? _prerelease;
    readonly bool? _privateBuild;
    readonly bool? _specialBuild;
    readonly int? _language;
    readonly string? _company;
    readonly string? _description;
    readonly string? _name;

    public DmOsLoadedModulesDataType( )
    {
    }

    public DmOsLoadedModulesDataType(byte[] baseAddress,
        string? fileVersion,
        string? productVersion,
        bool? debug,
        bool? patched,
        bool? prerelease,
        bool? privateBuild,
        bool? specialBuild,
        int? language,
        string? company,
        string? description,
        string? name)
    {
        _baseAddress = baseAddress;
        _fileVersion = fileVersion;
        _productVersion = productVersion;
        _debug = debug;
        _patched = patched;
        _prerelease = prerelease;
        _privateBuild = privateBuild;
        _specialBuild = specialBuild;
        _language = language;
        _company = company;
        _description = description;
        _name = name;
    }

    public byte[] BaseAddress => _baseAddress;
    public string? FileVersion => _fileVersion;
    public string? ProductVersion => _productVersion;
    public bool? Debug => _debug;
    public bool? Patched => _patched;
    public bool? Prerelease => _prerelease;
    public bool? PrivateBuild => _privateBuild;
    public bool? SpecialBuild => _specialBuild;
    public int? Language => _language;
    public string? Company => _company;
    public string? Description => _description;
    public string? Name => _name;
}
