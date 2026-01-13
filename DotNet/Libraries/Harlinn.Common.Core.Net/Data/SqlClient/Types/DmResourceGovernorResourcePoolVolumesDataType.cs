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

public class DmResourceGovernorResourcePoolVolumesDataType
{
    readonly int _poolId = 0;
    readonly string _volumeName = string.Empty;
    readonly int _readIoQueuedTotal = 0;
    readonly int _readIoIssuedTotal = 0;
    readonly int _readIoCompletedTotal = 0;
    readonly int _readIoThrottledTotal = 0;
    readonly long _readBytesTotal = 0;
    readonly long _readIoStallTotalMs = 0;
    readonly long _readIoStallQueuedMs = 0;
    readonly int _writeIoQueuedTotal = 0;
    readonly int _writeIoIssuedTotal = 0;
    readonly int _writeIoCompletedTotal = 0;
    readonly int _writeIoThrottledTotal = 0;
    readonly long _writeBytesTotal = 0;
    readonly long _writeIoStallTotalMs = 0;
    readonly long _writeIoStallQueuedMs = 0;
    readonly int _ioIssueViolationsTotal = 0;
    readonly long _ioIssueDelayTotalMs = 0;
    readonly long _ioIssueAheadTotalMs = 0;
    readonly int _reservedIoLimitedByVolumeTotal = 0;
    readonly long? _ioIssueDelayNonThrottledTotalMs;

    public DmResourceGovernorResourcePoolVolumesDataType( )
    {
    }

    public DmResourceGovernorResourcePoolVolumesDataType(int poolId,
        string volumeName,
        int readIoQueuedTotal,
        int readIoIssuedTotal,
        int readIoCompletedTotal,
        int readIoThrottledTotal,
        long readBytesTotal,
        long readIoStallTotalMs,
        long readIoStallQueuedMs,
        int writeIoQueuedTotal,
        int writeIoIssuedTotal,
        int writeIoCompletedTotal,
        int writeIoThrottledTotal,
        long writeBytesTotal,
        long writeIoStallTotalMs,
        long writeIoStallQueuedMs,
        int ioIssueViolationsTotal,
        long ioIssueDelayTotalMs,
        long ioIssueAheadTotalMs,
        int reservedIoLimitedByVolumeTotal,
        long? ioIssueDelayNonThrottledTotalMs)
    {
        _poolId = poolId;
        _volumeName = volumeName;
        _readIoQueuedTotal = readIoQueuedTotal;
        _readIoIssuedTotal = readIoIssuedTotal;
        _readIoCompletedTotal = readIoCompletedTotal;
        _readIoThrottledTotal = readIoThrottledTotal;
        _readBytesTotal = readBytesTotal;
        _readIoStallTotalMs = readIoStallTotalMs;
        _readIoStallQueuedMs = readIoStallQueuedMs;
        _writeIoQueuedTotal = writeIoQueuedTotal;
        _writeIoIssuedTotal = writeIoIssuedTotal;
        _writeIoCompletedTotal = writeIoCompletedTotal;
        _writeIoThrottledTotal = writeIoThrottledTotal;
        _writeBytesTotal = writeBytesTotal;
        _writeIoStallTotalMs = writeIoStallTotalMs;
        _writeIoStallQueuedMs = writeIoStallQueuedMs;
        _ioIssueViolationsTotal = ioIssueViolationsTotal;
        _ioIssueDelayTotalMs = ioIssueDelayTotalMs;
        _ioIssueAheadTotalMs = ioIssueAheadTotalMs;
        _reservedIoLimitedByVolumeTotal = reservedIoLimitedByVolumeTotal;
        _ioIssueDelayNonThrottledTotalMs = ioIssueDelayNonThrottledTotalMs;
    }

    public int PoolId => _poolId;
    public string VolumeName => _volumeName;
    public int ReadIoQueuedTotal => _readIoQueuedTotal;
    public int ReadIoIssuedTotal => _readIoIssuedTotal;
    public int ReadIoCompletedTotal => _readIoCompletedTotal;
    public int ReadIoThrottledTotal => _readIoThrottledTotal;
    public long ReadBytesTotal => _readBytesTotal;
    public long ReadIoStallTotalMs => _readIoStallTotalMs;
    public long ReadIoStallQueuedMs => _readIoStallQueuedMs;
    public int WriteIoQueuedTotal => _writeIoQueuedTotal;
    public int WriteIoIssuedTotal => _writeIoIssuedTotal;
    public int WriteIoCompletedTotal => _writeIoCompletedTotal;
    public int WriteIoThrottledTotal => _writeIoThrottledTotal;
    public long WriteBytesTotal => _writeBytesTotal;
    public long WriteIoStallTotalMs => _writeIoStallTotalMs;
    public long WriteIoStallQueuedMs => _writeIoStallQueuedMs;
    public int IoIssueViolationsTotal => _ioIssueViolationsTotal;
    public long IoIssueDelayTotalMs => _ioIssueDelayTotalMs;
    public long IoIssueAheadTotalMs => _ioIssueAheadTotalMs;
    public int ReservedIoLimitedByVolumeTotal => _reservedIoLimitedByVolumeTotal;
    public long? IoIssueDelayNonThrottledTotalMs => _ioIssueDelayNonThrottledTotalMs;
}
