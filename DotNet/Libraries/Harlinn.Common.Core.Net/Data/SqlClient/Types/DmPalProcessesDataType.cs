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

public class DmPalProcessesDataType
{
    readonly long _processId = 0;
    readonly string _processName = string.Empty;
    readonly long _processorTime = 0;
    readonly long _userTime = 0;
    readonly long _privilegedTime = 0;
    readonly long _virtualBytesPeak = 0;
    readonly long _virtualBytes = 0;
    readonly long _workingSetPeak = 0;
    readonly long _workingSet = 0;
    readonly long _pageFileBytesPeak = 0;
    readonly long _pageFileBytes = 0;
    readonly long _privateBytes = 0;
    readonly long _threadCount = 0;
    readonly long _elapsedTime = 0;
    readonly long _poolPagedBytes = 0;
    readonly long _handleCount = 0;
    readonly long _ioReadOperations = 0;
    readonly long _ioWriteOperations = 0;
    readonly long _ioReadBytes = 0;
    readonly long _ioWriteBytes = 0;
    readonly long _workingSetPrivate = 0;

    public DmPalProcessesDataType( )
    {
    }

    public DmPalProcessesDataType(long processId,
        string processName,
        long processorTime,
        long userTime,
        long privilegedTime,
        long virtualBytesPeak,
        long virtualBytes,
        long workingSetPeak,
        long workingSet,
        long pageFileBytesPeak,
        long pageFileBytes,
        long privateBytes,
        long threadCount,
        long elapsedTime,
        long poolPagedBytes,
        long handleCount,
        long ioReadOperations,
        long ioWriteOperations,
        long ioReadBytes,
        long ioWriteBytes,
        long workingSetPrivate)
    {
        _processId = processId;
        _processName = processName;
        _processorTime = processorTime;
        _userTime = userTime;
        _privilegedTime = privilegedTime;
        _virtualBytesPeak = virtualBytesPeak;
        _virtualBytes = virtualBytes;
        _workingSetPeak = workingSetPeak;
        _workingSet = workingSet;
        _pageFileBytesPeak = pageFileBytesPeak;
        _pageFileBytes = pageFileBytes;
        _privateBytes = privateBytes;
        _threadCount = threadCount;
        _elapsedTime = elapsedTime;
        _poolPagedBytes = poolPagedBytes;
        _handleCount = handleCount;
        _ioReadOperations = ioReadOperations;
        _ioWriteOperations = ioWriteOperations;
        _ioReadBytes = ioReadBytes;
        _ioWriteBytes = ioWriteBytes;
        _workingSetPrivate = workingSetPrivate;
    }

    public long ProcessId => _processId;
    public string ProcessName => _processName;
    public long ProcessorTime => _processorTime;
    public long UserTime => _userTime;
    public long PrivilegedTime => _privilegedTime;
    public long VirtualBytesPeak => _virtualBytesPeak;
    public long VirtualBytes => _virtualBytes;
    public long WorkingSetPeak => _workingSetPeak;
    public long WorkingSet => _workingSet;
    public long PageFileBytesPeak => _pageFileBytesPeak;
    public long PageFileBytes => _pageFileBytes;
    public long PrivateBytes => _privateBytes;
    public long ThreadCount => _threadCount;
    public long ElapsedTime => _elapsedTime;
    public long PoolPagedBytes => _poolPagedBytes;
    public long HandleCount => _handleCount;
    public long IoReadOperations => _ioReadOperations;
    public long IoWriteOperations => _ioWriteOperations;
    public long IoReadBytes => _ioReadBytes;
    public long IoWriteBytes => _ioWriteBytes;
    public long WorkingSetPrivate => _workingSetPrivate;
}
