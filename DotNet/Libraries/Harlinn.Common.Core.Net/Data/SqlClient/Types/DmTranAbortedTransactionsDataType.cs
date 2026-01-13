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

public class DmTranAbortedTransactionsDataType
{
    readonly long _transactionId = 0;
    readonly short _databaseId = 0;
    readonly object? _beginXactLsn;
    readonly object? _endXactLsn;
    readonly DateTime? _beginTime;
    readonly bool? _nestAborted;

    public DmTranAbortedTransactionsDataType( )
    {
    }

    public DmTranAbortedTransactionsDataType(long transactionId,
        short databaseId,
        object? beginXactLsn,
        object? endXactLsn,
        DateTime? beginTime,
        bool? nestAborted)
    {
        _transactionId = transactionId;
        _databaseId = databaseId;
        _beginXactLsn = beginXactLsn;
        _endXactLsn = endXactLsn;
        _beginTime = beginTime;
        _nestAborted = nestAborted;
    }

    public long TransactionId => _transactionId;
    public short DatabaseId => _databaseId;
    public object? BeginXactLsn => _beginXactLsn;
    public object? EndXactLsn => _endXactLsn;
    public DateTime? BeginTime => _beginTime;
    public bool? NestAborted => _nestAborted;
}
