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

public class DmTranSessionTransactionsDataType
{
    readonly int _sessionId = 0;
    readonly long _transactionId = 0;
    readonly byte[] _transactionDescriptor = Array.Empty<byte>();
    readonly int _enlistCount = 0;
    readonly bool _isUserTransaction = false;
    readonly bool _isLocal = false;
    readonly bool _isEnlisted = false;
    readonly bool _isBound = false;
    readonly int _openTransactionCount = 0;

    public DmTranSessionTransactionsDataType( )
    {
    }

    public DmTranSessionTransactionsDataType(int sessionId,
        long transactionId,
        byte[] transactionDescriptor,
        int enlistCount,
        bool isUserTransaction,
        bool isLocal,
        bool isEnlisted,
        bool isBound,
        int openTransactionCount)
    {
        _sessionId = sessionId;
        _transactionId = transactionId;
        _transactionDescriptor = transactionDescriptor;
        _enlistCount = enlistCount;
        _isUserTransaction = isUserTransaction;
        _isLocal = isLocal;
        _isEnlisted = isEnlisted;
        _isBound = isBound;
        _openTransactionCount = openTransactionCount;
    }

    public int SessionId => _sessionId;
    public long TransactionId => _transactionId;
    public byte[] TransactionDescriptor => _transactionDescriptor;
    public int EnlistCount => _enlistCount;
    public bool IsUserTransaction => _isUserTransaction;
    public bool IsLocal => _isLocal;
    public bool IsEnlisted => _isEnlisted;
    public bool IsBound => _isBound;
    public int OpenTransactionCount => _openTransactionCount;
}
