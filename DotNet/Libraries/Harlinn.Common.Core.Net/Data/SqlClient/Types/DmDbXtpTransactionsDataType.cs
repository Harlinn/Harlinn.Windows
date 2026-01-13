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

public class DmDbXtpTransactionsDataType
{
    readonly short _nodeId = 0;
    readonly long _xtpTransactionId = 0;
    readonly long _transactionId = 0;
    readonly short _sessionId = 0;
    readonly long _beginTsn = 0;
    readonly long _endTsn = 0;
    readonly int _state = 0;
    readonly string _stateDesc = string.Empty;
    readonly int _result = 0;
    readonly string _resultDesc = string.Empty;
    readonly short _xtpParentTransactionNodeId = 0;
    readonly long _xtpParentTransactionId = 0;
    readonly int _lastError = 0;
    readonly bool _isSpeculative = false;
    readonly bool _isPrepared = false;
    readonly bool _isDelayedDurability = false;
    readonly byte[] _memoryAddress = Array.Empty<byte>();
    readonly byte[] _databaseAddress = Array.Empty<byte>();
    readonly int _threadId = 0;
    readonly int _readSetRowCount = 0;
    readonly int _writeSetRowCount = 0;
    readonly int _scanSetCount = 0;
    readonly int _savepointGarbageCount = 0;
    readonly long _logBytesRequired = 0;
    readonly int _countOfAllocations = 0;
    readonly int _allocatedBytes = 0;
    readonly int _reservedBytes = 0;
    readonly int _commitDependencyCount = 0;
    readonly int _commitDependencyTotalAttemptCount = 0;
    readonly int _scanArea = 0;
    readonly string _scanAreaDesc = string.Empty;
    readonly int _scanLocation = 0;
    readonly byte[] _dependent1Address = Array.Empty<byte>();
    readonly byte[] _dependent2Address = Array.Empty<byte>();
    readonly byte[] _dependent3Address = Array.Empty<byte>();
    readonly byte[] _dependent4Address = Array.Empty<byte>();
    readonly byte[] _dependent5Address = Array.Empty<byte>();
    readonly byte[] _dependent6Address = Array.Empty<byte>();
    readonly byte[] _dependent7Address = Array.Empty<byte>();
    readonly byte[] _dependent8Address = Array.Empty<byte>();

    public DmDbXtpTransactionsDataType( )
    {
    }

    public DmDbXtpTransactionsDataType(short nodeId,
        long xtpTransactionId,
        long transactionId,
        short sessionId,
        long beginTsn,
        long endTsn,
        int state,
        string stateDesc,
        int result,
        string resultDesc,
        short xtpParentTransactionNodeId,
        long xtpParentTransactionId,
        int lastError,
        bool isSpeculative,
        bool isPrepared,
        bool isDelayedDurability,
        byte[] memoryAddress,
        byte[] databaseAddress,
        int threadId,
        int readSetRowCount,
        int writeSetRowCount,
        int scanSetCount,
        int savepointGarbageCount,
        long logBytesRequired,
        int countOfAllocations,
        int allocatedBytes,
        int reservedBytes,
        int commitDependencyCount,
        int commitDependencyTotalAttemptCount,
        int scanArea,
        string scanAreaDesc,
        int scanLocation,
        byte[] dependent1Address,
        byte[] dependent2Address,
        byte[] dependent3Address,
        byte[] dependent4Address,
        byte[] dependent5Address,
        byte[] dependent6Address,
        byte[] dependent7Address,
        byte[] dependent8Address)
    {
        _nodeId = nodeId;
        _xtpTransactionId = xtpTransactionId;
        _transactionId = transactionId;
        _sessionId = sessionId;
        _beginTsn = beginTsn;
        _endTsn = endTsn;
        _state = state;
        _stateDesc = stateDesc;
        _result = result;
        _resultDesc = resultDesc;
        _xtpParentTransactionNodeId = xtpParentTransactionNodeId;
        _xtpParentTransactionId = xtpParentTransactionId;
        _lastError = lastError;
        _isSpeculative = isSpeculative;
        _isPrepared = isPrepared;
        _isDelayedDurability = isDelayedDurability;
        _memoryAddress = memoryAddress;
        _databaseAddress = databaseAddress;
        _threadId = threadId;
        _readSetRowCount = readSetRowCount;
        _writeSetRowCount = writeSetRowCount;
        _scanSetCount = scanSetCount;
        _savepointGarbageCount = savepointGarbageCount;
        _logBytesRequired = logBytesRequired;
        _countOfAllocations = countOfAllocations;
        _allocatedBytes = allocatedBytes;
        _reservedBytes = reservedBytes;
        _commitDependencyCount = commitDependencyCount;
        _commitDependencyTotalAttemptCount = commitDependencyTotalAttemptCount;
        _scanArea = scanArea;
        _scanAreaDesc = scanAreaDesc;
        _scanLocation = scanLocation;
        _dependent1Address = dependent1Address;
        _dependent2Address = dependent2Address;
        _dependent3Address = dependent3Address;
        _dependent4Address = dependent4Address;
        _dependent5Address = dependent5Address;
        _dependent6Address = dependent6Address;
        _dependent7Address = dependent7Address;
        _dependent8Address = dependent8Address;
    }

    public short NodeId => _nodeId;
    public long XtpTransactionId => _xtpTransactionId;
    public long TransactionId => _transactionId;
    public short SessionId => _sessionId;
    public long BeginTsn => _beginTsn;
    public long EndTsn => _endTsn;
    public int State => _state;
    public string StateDesc => _stateDesc;
    public int Result => _result;
    public string ResultDesc => _resultDesc;
    public short XtpParentTransactionNodeId => _xtpParentTransactionNodeId;
    public long XtpParentTransactionId => _xtpParentTransactionId;
    public int LastError => _lastError;
    public bool IsSpeculative => _isSpeculative;
    public bool IsPrepared => _isPrepared;
    public bool IsDelayedDurability => _isDelayedDurability;
    public byte[] MemoryAddress => _memoryAddress;
    public byte[] DatabaseAddress => _databaseAddress;
    public int ThreadId => _threadId;
    public int ReadSetRowCount => _readSetRowCount;
    public int WriteSetRowCount => _writeSetRowCount;
    public int ScanSetCount => _scanSetCount;
    public int SavepointGarbageCount => _savepointGarbageCount;
    public long LogBytesRequired => _logBytesRequired;
    public int CountOfAllocations => _countOfAllocations;
    public int AllocatedBytes => _allocatedBytes;
    public int ReservedBytes => _reservedBytes;
    public int CommitDependencyCount => _commitDependencyCount;
    public int CommitDependencyTotalAttemptCount => _commitDependencyTotalAttemptCount;
    public int ScanArea => _scanArea;
    public string ScanAreaDesc => _scanAreaDesc;
    public int ScanLocation => _scanLocation;
    public byte[] Dependent1Address => _dependent1Address;
    public byte[] Dependent2Address => _dependent2Address;
    public byte[] Dependent3Address => _dependent3Address;
    public byte[] Dependent4Address => _dependent4Address;
    public byte[] Dependent5Address => _dependent5Address;
    public byte[] Dependent6Address => _dependent6Address;
    public byte[] Dependent7Address => _dependent7Address;
    public byte[] Dependent8Address => _dependent8Address;
}
