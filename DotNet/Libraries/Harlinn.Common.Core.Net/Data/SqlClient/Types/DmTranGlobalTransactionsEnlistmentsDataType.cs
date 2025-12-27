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

public class DmTranGlobalTransactionsEnlistmentsDataType
{
    readonly Guid _transactionId;
    readonly int _databaseId = 0;
    readonly int _isoLevel = 0;
    readonly int _canCommit = 0;
    readonly int _enlistmentState = 0;
    readonly Guid _resourceManagerId;
    readonly string? _serverName;
    readonly string? _databaseName;
    readonly string? _transactionManagerServerName;
    readonly string? _transactionManagerDatabaseName;
    readonly int _transactionManagerDatabaseId = 0;
    readonly Guid _transactionManagerRmid;
    readonly string? _prepareLsn;
    readonly long _snapshotTimestamp = 0;
    readonly string? _oldestActiveLsn;
    readonly long _prepareElapsedTime = 0;
    readonly int _objectRefCount = 0;
    readonly int _transactionTimeout = 0;
    readonly int _diagStatus = 0;

    public DmTranGlobalTransactionsEnlistmentsDataType( )
    {
    }

    public DmTranGlobalTransactionsEnlistmentsDataType(Guid transactionId,
        int databaseId,
        int isoLevel,
        int canCommit,
        int enlistmentState,
        Guid resourceManagerId,
        string? serverName,
        string? databaseName,
        string? transactionManagerServerName,
        string? transactionManagerDatabaseName,
        int transactionManagerDatabaseId,
        Guid transactionManagerRmid,
        string? prepareLsn,
        long snapshotTimestamp,
        string? oldestActiveLsn,
        long prepareElapsedTime,
        int objectRefCount,
        int transactionTimeout,
        int diagStatus)
    {
        _transactionId = transactionId;
        _databaseId = databaseId;
        _isoLevel = isoLevel;
        _canCommit = canCommit;
        _enlistmentState = enlistmentState;
        _resourceManagerId = resourceManagerId;
        _serverName = serverName;
        _databaseName = databaseName;
        _transactionManagerServerName = transactionManagerServerName;
        _transactionManagerDatabaseName = transactionManagerDatabaseName;
        _transactionManagerDatabaseId = transactionManagerDatabaseId;
        _transactionManagerRmid = transactionManagerRmid;
        _prepareLsn = prepareLsn;
        _snapshotTimestamp = snapshotTimestamp;
        _oldestActiveLsn = oldestActiveLsn;
        _prepareElapsedTime = prepareElapsedTime;
        _objectRefCount = objectRefCount;
        _transactionTimeout = transactionTimeout;
        _diagStatus = diagStatus;
    }

    public Guid TransactionId => _transactionId;
    public int DatabaseId => _databaseId;
    public int IsoLevel => _isoLevel;
    public int CanCommit => _canCommit;
    public int EnlistmentState => _enlistmentState;
    public Guid ResourceManagerId => _resourceManagerId;
    public string? ServerName => _serverName;
    public string? DatabaseName => _databaseName;
    public string? TransactionManagerServerName => _transactionManagerServerName;
    public string? TransactionManagerDatabaseName => _transactionManagerDatabaseName;
    public int TransactionManagerDatabaseId => _transactionManagerDatabaseId;
    public Guid TransactionManagerRmid => _transactionManagerRmid;
    public string? PrepareLsn => _prepareLsn;
    public long SnapshotTimestamp => _snapshotTimestamp;
    public string? OldestActiveLsn => _oldestActiveLsn;
    public long PrepareElapsedTime => _prepareElapsedTime;
    public int ObjectRefCount => _objectRefCount;
    public int TransactionTimeout => _transactionTimeout;
    public int DiagStatus => _diagStatus;
}
