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

public class SelectiveXmlIndexNamespacesDataType
{
    readonly int _objectId = 0;
    readonly int _indexId = 0;
    readonly bool? _isDefaultUri;
    readonly string? _uri;
    readonly string? _prefix;

    public SelectiveXmlIndexNamespacesDataType( )
    {
    }

    public SelectiveXmlIndexNamespacesDataType(int objectId,
        int indexId,
        bool? isDefaultUri,
        string? uri,
        string? prefix)
    {
        _objectId = objectId;
        _indexId = indexId;
        _isDefaultUri = isDefaultUri;
        _uri = uri;
        _prefix = prefix;
    }

    public int ObjectId => _objectId;
    public int IndexId => _indexId;
    public bool? IsDefaultUri => _isDefaultUri;
    public string? Uri => _uri;
    public string? Prefix => _prefix;
}
