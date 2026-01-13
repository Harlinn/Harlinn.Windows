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

public class DmTranActiveSnapshotDatabaseTransactionsDataType
{
    readonly long? _transactionId;
    readonly long? _transactionSequenceNum;
    readonly long? _commitSequenceNum;
    readonly int? _sessionId;
    readonly bool? _isSnapshot;
    readonly long? _firstSnapshotSequenceNum;
    readonly int? _maxVersionChainTraversed;
    readonly double? _averageVersionChainTraversed;
    readonly long? _elapsedTimeSeconds;

    public DmTranActiveSnapshotDatabaseTransactionsDataType( )
    {
    }

    public DmTranActiveSnapshotDatabaseTransactionsDataType(long? transactionId,
        long? transactionSequenceNum,
        long? commitSequenceNum,
        int? sessionId,
        bool? isSnapshot,
        long? firstSnapshotSequenceNum,
        int? maxVersionChainTraversed,
        double? averageVersionChainTraversed,
        long? elapsedTimeSeconds)
    {
        _transactionId = transactionId;
        _transactionSequenceNum = transactionSequenceNum;
        _commitSequenceNum = commitSequenceNum;
        _sessionId = sessionId;
        _isSnapshot = isSnapshot;
        _firstSnapshotSequenceNum = firstSnapshotSequenceNum;
        _maxVersionChainTraversed = maxVersionChainTraversed;
        _averageVersionChainTraversed = averageVersionChainTraversed;
        _elapsedTimeSeconds = elapsedTimeSeconds;
    }

    public long? TransactionId => _transactionId;
    public long? TransactionSequenceNum => _transactionSequenceNum;
    public long? CommitSequenceNum => _commitSequenceNum;
    public int? SessionId => _sessionId;
    public bool? IsSnapshot => _isSnapshot;
    public long? FirstSnapshotSequenceNum => _firstSnapshotSequenceNum;
    public int? MaxVersionChainTraversed => _maxVersionChainTraversed;
    public double? AverageVersionChainTraversed => _averageVersionChainTraversed;
    public long? ElapsedTimeSeconds => _elapsedTimeSeconds;
}
