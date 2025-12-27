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

public class DmTranCurrentTransactionDataType
{
    readonly long? _transactionId;
    readonly long? _transactionSequenceNum;
    readonly bool? _transactionIsSnapshot;
    readonly long? _firstSnapshotSequenceNum;
    readonly long? _lastTransactionSequenceNum;
    readonly long? _firstUsefulSequenceNum;

    public DmTranCurrentTransactionDataType( )
    {
    }

    public DmTranCurrentTransactionDataType(long? transactionId,
        long? transactionSequenceNum,
        bool? transactionIsSnapshot,
        long? firstSnapshotSequenceNum,
        long? lastTransactionSequenceNum,
        long? firstUsefulSequenceNum)
    {
        _transactionId = transactionId;
        _transactionSequenceNum = transactionSequenceNum;
        _transactionIsSnapshot = transactionIsSnapshot;
        _firstSnapshotSequenceNum = firstSnapshotSequenceNum;
        _lastTransactionSequenceNum = lastTransactionSequenceNum;
        _firstUsefulSequenceNum = firstUsefulSequenceNum;
    }

    public long? TransactionId => _transactionId;
    public long? TransactionSequenceNum => _transactionSequenceNum;
    public bool? TransactionIsSnapshot => _transactionIsSnapshot;
    public long? FirstSnapshotSequenceNum => _firstSnapshotSequenceNum;
    public long? LastTransactionSequenceNum => _lastTransactionSequenceNum;
    public long? FirstUsefulSequenceNum => _firstUsefulSequenceNum;
}
