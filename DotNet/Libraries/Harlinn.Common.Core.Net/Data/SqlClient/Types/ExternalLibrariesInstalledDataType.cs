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

public class ExternalLibrariesInstalledDataType
{
    readonly int _dbId = 0;
    readonly int _principalId = 0;
    readonly int _languageId = 0;
    readonly int _externalLibraryId = 0;
    readonly string _name = string.Empty;
    readonly byte[] _mdversion = Array.Empty<byte>();

    public ExternalLibrariesInstalledDataType( )
    {
    }

    public ExternalLibrariesInstalledDataType(int dbId,
        int principalId,
        int languageId,
        int externalLibraryId,
        string name,
        byte[] mdversion)
    {
        _dbId = dbId;
        _principalId = principalId;
        _languageId = languageId;
        _externalLibraryId = externalLibraryId;
        _name = name;
        _mdversion = mdversion;
    }

    public int DbId => _dbId;
    public int PrincipalId => _principalId;
    public int LanguageId => _languageId;
    public int ExternalLibraryId => _externalLibraryId;
    public string Name => _name;
    public byte[] Mdversion => _mdversion;
}
