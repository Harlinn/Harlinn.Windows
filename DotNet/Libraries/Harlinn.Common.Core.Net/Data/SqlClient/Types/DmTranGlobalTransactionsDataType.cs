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

public class DmTranGlobalTransactionsDataType
{
    readonly Guid _transactionId;
    readonly int _databaseId = 0;
    readonly int _transactionState = 0;
    readonly Guid _resourceManagerId;
    readonly string? _resourceManagerServer;
    readonly string? _resourceManagerDatabase;
    readonly int _resourceManagerDbid = 0;
    readonly int _resourceManagerState = 0;
    readonly string? _resourcePrepareLsn;
    readonly long _resourcePhase1Time = 0;
    readonly long _resourcePhase2Time = 0;
    readonly long _transactionPhase1Time = 0;
    readonly long _transactionPhase2Time = 0;
    readonly long _transactionTotalTime = 0;
    readonly int _transactionDiagStatus = 0;
    readonly int _resourceManagerDiagStatus = 0;
    readonly long _maxCsn = 0;

    public DmTranGlobalTransactionsDataType( )
    {
    }

    public DmTranGlobalTransactionsDataType(Guid transactionId,
        int databaseId,
        int transactionState,
        Guid resourceManagerId,
        string? resourceManagerServer,
        string? resourceManagerDatabase,
        int resourceManagerDbid,
        int resourceManagerState,
        string? resourcePrepareLsn,
        long resourcePhase1Time,
        long resourcePhase2Time,
        long transactionPhase1Time,
        long transactionPhase2Time,
        long transactionTotalTime,
        int transactionDiagStatus,
        int resourceManagerDiagStatus,
        long maxCsn)
    {
        _transactionId = transactionId;
        _databaseId = databaseId;
        _transactionState = transactionState;
        _resourceManagerId = resourceManagerId;
        _resourceManagerServer = resourceManagerServer;
        _resourceManagerDatabase = resourceManagerDatabase;
        _resourceManagerDbid = resourceManagerDbid;
        _resourceManagerState = resourceManagerState;
        _resourcePrepareLsn = resourcePrepareLsn;
        _resourcePhase1Time = resourcePhase1Time;
        _resourcePhase2Time = resourcePhase2Time;
        _transactionPhase1Time = transactionPhase1Time;
        _transactionPhase2Time = transactionPhase2Time;
        _transactionTotalTime = transactionTotalTime;
        _transactionDiagStatus = transactionDiagStatus;
        _resourceManagerDiagStatus = resourceManagerDiagStatus;
        _maxCsn = maxCsn;
    }

    public Guid TransactionId => _transactionId;
    public int DatabaseId => _databaseId;
    public int TransactionState => _transactionState;
    public Guid ResourceManagerId => _resourceManagerId;
    public string? ResourceManagerServer => _resourceManagerServer;
    public string? ResourceManagerDatabase => _resourceManagerDatabase;
    public int ResourceManagerDbid => _resourceManagerDbid;
    public int ResourceManagerState => _resourceManagerState;
    public string? ResourcePrepareLsn => _resourcePrepareLsn;
    public long ResourcePhase1Time => _resourcePhase1Time;
    public long ResourcePhase2Time => _resourcePhase2Time;
    public long TransactionPhase1Time => _transactionPhase1Time;
    public long TransactionPhase2Time => _transactionPhase2Time;
    public long TransactionTotalTime => _transactionTotalTime;
    public int TransactionDiagStatus => _transactionDiagStatus;
    public int ResourceManagerDiagStatus => _resourceManagerDiagStatus;
    public long MaxCsn => _maxCsn;
}
