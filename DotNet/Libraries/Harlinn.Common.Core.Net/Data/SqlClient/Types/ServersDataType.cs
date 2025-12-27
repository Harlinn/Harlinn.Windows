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

public class ServersDataType
{
    readonly int _serverId = 0;
    readonly string _name = string.Empty;
    readonly string _product = string.Empty;
    readonly string _provider = string.Empty;
    readonly string? _dataSource;
    readonly string? _location;
    readonly string? _providerString;
    readonly string? _catalog;
    readonly int? _connectTimeout;
    readonly int? _queryTimeout;
    readonly bool _isLinked = false;
    readonly bool _isRemoteLoginEnabled = false;
    readonly bool _isRpcOutEnabled = false;
    readonly bool _isDataAccessEnabled = false;
    readonly bool _isCollationCompatible = false;
    readonly bool _usesRemoteCollation = false;
    readonly string? _collationName;
    readonly bool _lazySchemaValidation = false;
    readonly bool _isSystem = false;
    readonly bool _isPublisher = false;
    readonly bool? _isSubscriber;
    readonly bool? _isDistributor;
    readonly bool? _isNonsqlSubscriber;
    readonly bool? _isRemoteProcTransactionPromotionEnabled;
    readonly DateTime _modifyDate;
    readonly bool? _isRdaServer;

    public ServersDataType( )
    {
    }

    public ServersDataType(int serverId,
        string name,
        string product,
        string provider,
        string? dataSource,
        string? location,
        string? providerString,
        string? catalog,
        int? connectTimeout,
        int? queryTimeout,
        bool isLinked,
        bool isRemoteLoginEnabled,
        bool isRpcOutEnabled,
        bool isDataAccessEnabled,
        bool isCollationCompatible,
        bool usesRemoteCollation,
        string? collationName,
        bool lazySchemaValidation,
        bool isSystem,
        bool isPublisher,
        bool? isSubscriber,
        bool? isDistributor,
        bool? isNonsqlSubscriber,
        bool? isRemoteProcTransactionPromotionEnabled,
        DateTime modifyDate,
        bool? isRdaServer)
    {
        _serverId = serverId;
        _name = name;
        _product = product;
        _provider = provider;
        _dataSource = dataSource;
        _location = location;
        _providerString = providerString;
        _catalog = catalog;
        _connectTimeout = connectTimeout;
        _queryTimeout = queryTimeout;
        _isLinked = isLinked;
        _isRemoteLoginEnabled = isRemoteLoginEnabled;
        _isRpcOutEnabled = isRpcOutEnabled;
        _isDataAccessEnabled = isDataAccessEnabled;
        _isCollationCompatible = isCollationCompatible;
        _usesRemoteCollation = usesRemoteCollation;
        _collationName = collationName;
        _lazySchemaValidation = lazySchemaValidation;
        _isSystem = isSystem;
        _isPublisher = isPublisher;
        _isSubscriber = isSubscriber;
        _isDistributor = isDistributor;
        _isNonsqlSubscriber = isNonsqlSubscriber;
        _isRemoteProcTransactionPromotionEnabled = isRemoteProcTransactionPromotionEnabled;
        _modifyDate = modifyDate;
        _isRdaServer = isRdaServer;
    }

    public int ServerId => _serverId;
    public string Name => _name;
    public string Product => _product;
    public string Provider => _provider;
    public string? DataSource => _dataSource;
    public string? Location => _location;
    public string? ProviderString => _providerString;
    public string? Catalog => _catalog;
    public int? ConnectTimeout => _connectTimeout;
    public int? QueryTimeout => _queryTimeout;
    public bool IsLinked => _isLinked;
    public bool IsRemoteLoginEnabled => _isRemoteLoginEnabled;
    public bool IsRpcOutEnabled => _isRpcOutEnabled;
    public bool IsDataAccessEnabled => _isDataAccessEnabled;
    public bool IsCollationCompatible => _isCollationCompatible;
    public bool UsesRemoteCollation => _usesRemoteCollation;
    public string? CollationName => _collationName;
    public bool LazySchemaValidation => _lazySchemaValidation;
    public bool IsSystem => _isSystem;
    public bool IsPublisher => _isPublisher;
    public bool? IsSubscriber => _isSubscriber;
    public bool? IsDistributor => _isDistributor;
    public bool? IsNonsqlSubscriber => _isNonsqlSubscriber;
    public bool? IsRemoteProcTransactionPromotionEnabled => _isRemoteProcTransactionPromotionEnabled;
    public DateTime ModifyDate => _modifyDate;
    public bool? IsRdaServer => _isRdaServer;
}
