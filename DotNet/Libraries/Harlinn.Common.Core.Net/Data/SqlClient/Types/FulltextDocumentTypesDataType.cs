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

public class FulltextDocumentTypesDataType
{
    readonly string _documentType = string.Empty;
    readonly Guid _classId;
    readonly string? _path;
    readonly string _version = string.Empty;
    readonly string? _manufacturer;

    public FulltextDocumentTypesDataType( )
    {
    }

    public FulltextDocumentTypesDataType(string documentType,
        Guid classId,
        string? path,
        string version,
        string? manufacturer)
    {
        _documentType = documentType;
        _classId = classId;
        _path = path;
        _version = version;
        _manufacturer = manufacturer;
    }

    public string DocumentType => _documentType;
    public Guid ClassId => _classId;
    public string? Path => _path;
    public string Version => _version;
    public string? Manufacturer => _manufacturer;
}
