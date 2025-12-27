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

public class DmTranGlobalTransactionsLogDataType
{
    readonly Guid _transactionId;
    readonly DateTime _timeUtc;
    readonly byte _dropped = 0;
    readonly Guid _resourceManagerId;
    readonly string? _resourceManagerPrepareLsn;
    readonly byte _resourceManagerAckReceived = 0;
    readonly long _commitTimestamp = 0;

    public DmTranGlobalTransactionsLogDataType( )
    {
    }

    public DmTranGlobalTransactionsLogDataType(Guid transactionId,
        DateTime timeUtc,
        byte dropped,
        Guid resourceManagerId,
        string? resourceManagerPrepareLsn,
        byte resourceManagerAckReceived,
        long commitTimestamp)
    {
        _transactionId = transactionId;
        _timeUtc = timeUtc;
        _dropped = dropped;
        _resourceManagerId = resourceManagerId;
        _resourceManagerPrepareLsn = resourceManagerPrepareLsn;
        _resourceManagerAckReceived = resourceManagerAckReceived;
        _commitTimestamp = commitTimestamp;
    }

    public Guid TransactionId => _transactionId;
    public DateTime TimeUtc => _timeUtc;
    public byte Dropped => _dropped;
    public Guid ResourceManagerId => _resourceManagerId;
    public string? ResourceManagerPrepareLsn => _resourceManagerPrepareLsn;
    public byte ResourceManagerAckReceived => _resourceManagerAckReceived;
    public long CommitTimestamp => _commitTimestamp;
}
