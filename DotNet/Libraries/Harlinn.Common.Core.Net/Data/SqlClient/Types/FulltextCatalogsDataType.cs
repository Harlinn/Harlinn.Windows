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

public class FulltextCatalogsDataType
{
    readonly int _fulltextCatalogId = 0;
    readonly string _name = string.Empty;
    readonly string? _path;
    readonly bool _isDefault = false;
    readonly bool _isAccentSensitivityOn = false;
    readonly int? _dataSpaceId;
    readonly int? _fileId;
    readonly int? _principalId;
    readonly bool _isImporting = false;

    public FulltextCatalogsDataType( )
    {
    }

    public FulltextCatalogsDataType(int fulltextCatalogId,
        string name,
        string? path,
        bool isDefault,
        bool isAccentSensitivityOn,
        int? dataSpaceId,
        int? fileId,
        int? principalId,
        bool isImporting)
    {
        _fulltextCatalogId = fulltextCatalogId;
        _name = name;
        _path = path;
        _isDefault = isDefault;
        _isAccentSensitivityOn = isAccentSensitivityOn;
        _dataSpaceId = dataSpaceId;
        _fileId = fileId;
        _principalId = principalId;
        _isImporting = isImporting;
    }

    public int FulltextCatalogId => _fulltextCatalogId;
    public string Name => _name;
    public string? Path => _path;
    public bool IsDefault => _isDefault;
    public bool IsAccentSensitivityOn => _isAccentSensitivityOn;
    public int? DataSpaceId => _dataSpaceId;
    public int? FileId => _fileId;
    public int? PrincipalId => _principalId;
    public bool IsImporting => _isImporting;
}
