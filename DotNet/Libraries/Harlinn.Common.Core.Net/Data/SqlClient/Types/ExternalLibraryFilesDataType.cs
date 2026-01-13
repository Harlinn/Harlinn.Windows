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

public class ExternalLibraryFilesDataType
{
    readonly int _externalLibraryId = 0;
    readonly byte[]? _content;
    readonly byte? _platform;
    readonly string? _platformDesc;

    public ExternalLibraryFilesDataType( )
    {
    }

    public ExternalLibraryFilesDataType(int externalLibraryId,
        byte[]? content,
        byte? platform,
        string? platformDesc)
    {
        _externalLibraryId = externalLibraryId;
        _content = content;
        _platform = platform;
        _platformDesc = platformDesc;
    }

    public int ExternalLibraryId => _externalLibraryId;
    public byte[]? Content => _content;
    public byte? Platform => _platform;
    public string? PlatformDesc => _platformDesc;
}
