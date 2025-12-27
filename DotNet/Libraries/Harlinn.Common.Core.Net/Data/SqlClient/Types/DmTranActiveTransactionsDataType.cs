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

public class DmTranActiveTransactionsDataType
{
    readonly long _transactionId = 0;
    readonly string _name = string.Empty;
    readonly DateTime _transactionBeginTime;
    readonly int _transactionType = 0;
    readonly Guid? _transactionUow;
    readonly int _transactionState = 0;
    readonly int _transactionStatus = 0;
    readonly int _transactionStatus2 = 0;
    readonly int _dtcState = 0;
    readonly int _dtcStatus = 0;
    readonly int _dtcIsolationLevel = 0;
    readonly byte[]? _filestreamTransactionId;

    public DmTranActiveTransactionsDataType( )
    {
    }

    public DmTranActiveTransactionsDataType(long transactionId,
        string name,
        DateTime transactionBeginTime,
        int transactionType,
        Guid? transactionUow,
        int transactionState,
        int transactionStatus,
        int transactionStatus2,
        int dtcState,
        int dtcStatus,
        int dtcIsolationLevel,
        byte[]? filestreamTransactionId)
    {
        _transactionId = transactionId;
        _name = name;
        _transactionBeginTime = transactionBeginTime;
        _transactionType = transactionType;
        _transactionUow = transactionUow;
        _transactionState = transactionState;
        _transactionStatus = transactionStatus;
        _transactionStatus2 = transactionStatus2;
        _dtcState = dtcState;
        _dtcStatus = dtcStatus;
        _dtcIsolationLevel = dtcIsolationLevel;
        _filestreamTransactionId = filestreamTransactionId;
    }

    public long TransactionId => _transactionId;
    public string Name => _name;
    public DateTime TransactionBeginTime => _transactionBeginTime;
    public int TransactionType => _transactionType;
    public Guid? TransactionUow => _transactionUow;
    public int TransactionState => _transactionState;
    public int TransactionStatus => _transactionStatus;
    public int TransactionStatus2 => _transactionStatus2;
    public int DtcState => _dtcState;
    public int DtcStatus => _dtcStatus;
    public int DtcIsolationLevel => _dtcIsolationLevel;
    public byte[]? FilestreamTransactionId => _filestreamTransactionId;
}
