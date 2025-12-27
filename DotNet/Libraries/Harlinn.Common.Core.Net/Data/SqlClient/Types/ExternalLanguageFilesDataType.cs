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

public class ExternalLanguageFilesDataType
{
    readonly int _externalLanguageId = 0;
    readonly byte[]? _content;
    readonly string? _fileName;
    readonly byte? _platform;
    readonly string? _platformDesc;
    readonly string? _parameters;
    readonly string? _environmentVariables;

    public ExternalLanguageFilesDataType( )
    {
    }

    public ExternalLanguageFilesDataType(int externalLanguageId,
        byte[]? content,
        string? fileName,
        byte? platform,
        string? platformDesc,
        string? parameters,
        string? environmentVariables)
    {
        _externalLanguageId = externalLanguageId;
        _content = content;
        _fileName = fileName;
        _platform = platform;
        _platformDesc = platformDesc;
        _parameters = parameters;
        _environmentVariables = environmentVariables;
    }

    public int ExternalLanguageId => _externalLanguageId;
    public byte[]? Content => _content;
    public string? FileName => _fileName;
    public byte? Platform => _platform;
    public string? PlatformDesc => _platformDesc;
    public string? Parameters => _parameters;
    public string? EnvironmentVariables => _environmentVariables;
}
