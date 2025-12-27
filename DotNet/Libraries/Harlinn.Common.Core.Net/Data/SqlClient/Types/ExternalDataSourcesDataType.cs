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

public class ExternalDataSourcesDataType
{
    readonly int _dataSourceId = 0;
    readonly string _name = string.Empty;
    readonly string _location = string.Empty;
    readonly string? _typeDesc;
    readonly byte _type = 0;
    readonly string? _resourceManagerLocation;
    readonly int _credentialId = 0;
    readonly string? _databaseName;
    readonly string? _shardMapName;
    readonly string? _connectionOptions;
    readonly string _pushdown = string.Empty;

    public ExternalDataSourcesDataType( )
    {
    }

    public ExternalDataSourcesDataType(int dataSourceId,
        string name,
        string location,
        string? typeDesc,
        byte type,
        string? resourceManagerLocation,
        int credentialId,
        string? databaseName,
        string? shardMapName,
        string? connectionOptions,
        string pushdown)
    {
        _dataSourceId = dataSourceId;
        _name = name;
        _location = location;
        _typeDesc = typeDesc;
        _type = type;
        _resourceManagerLocation = resourceManagerLocation;
        _credentialId = credentialId;
        _databaseName = databaseName;
        _shardMapName = shardMapName;
        _connectionOptions = connectionOptions;
        _pushdown = pushdown;
    }

    public int DataSourceId => _dataSourceId;
    public string Name => _name;
    public string Location => _location;
    public string? TypeDesc => _typeDesc;
    public byte Type => _type;
    public string? ResourceManagerLocation => _resourceManagerLocation;
    public int CredentialId => _credentialId;
    public string? DatabaseName => _databaseName;
    public string? ShardMapName => _shardMapName;
    public string? ConnectionOptions => _connectionOptions;
    public string Pushdown => _pushdown;
}
