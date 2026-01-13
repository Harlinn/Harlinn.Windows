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

public class DmTranTransactionsSnapshotDataType
{
    readonly long? _transactionSequenceNum;
    readonly int? _snapshotId;
    readonly long? _snapshotSequenceNum;

    public DmTranTransactionsSnapshotDataType( )
    {
    }

    public DmTranTransactionsSnapshotDataType(long? transactionSequenceNum,
        int? snapshotId,
        long? snapshotSequenceNum)
    {
        _transactionSequenceNum = transactionSequenceNum;
        _snapshotId = snapshotId;
        _snapshotSequenceNum = snapshotSequenceNum;
    }

    public long? TransactionSequenceNum => _transactionSequenceNum;
    public int? SnapshotId => _snapshotId;
    public long? SnapshotSequenceNum => _snapshotSequenceNum;
}
