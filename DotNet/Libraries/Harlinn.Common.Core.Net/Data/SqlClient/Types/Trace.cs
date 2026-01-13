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

/// <summary>
/// Represents a row from the sys.traces catalog view.
/// </summary>
public class Trace
{
    readonly int _id = 0;
    readonly int _status = 0;
    readonly string? _path;
    readonly long? _maxSize;
    readonly DateTime? _stopTime;
    readonly int? _maxFiles;
    readonly bool? _isRowset;
    readonly bool? _isRollover;
    readonly bool? _isShutdown;
    readonly bool? _isDefault;
    readonly int? _bufferCount;
    readonly int? _bufferSize;
    readonly long? _filePosition;
    readonly int? _readerSpid;
    readonly DateTime? _startTime;
    readonly DateTime? _lastEventTime;
    readonly long? _eventCount;
    readonly int? _droppedEventCount;

    public Trace( )
    {
    }

    public Trace(int id,
        int status,
        string? path,
        long? maxSize,
        DateTime? stopTime,
        int? maxFiles,
        bool? isRowset,
        bool? isRollover,
        bool? isShutdown,
        bool? isDefault,
        int? bufferCount,
        int? bufferSize,
        long? filePosition,
        int? readerSpid,
        DateTime? startTime,
        DateTime? lastEventTime,
        long? eventCount,
        int? droppedEventCount)
    {
        _id = id;
        _status = status;
        _path = path;
        _maxSize = maxSize;
        _stopTime = stopTime;
        _maxFiles = maxFiles;
        _isRowset = isRowset;
        _isRollover = isRollover;
        _isShutdown = isShutdown;
        _isDefault = isDefault;
        _bufferCount = bufferCount;
        _bufferSize = bufferSize;
        _filePosition = filePosition;
        _readerSpid = readerSpid;
        _startTime = startTime;
        _lastEventTime = lastEventTime;
        _eventCount = eventCount;
        _droppedEventCount = droppedEventCount;
    }

    public int Id => _id;
    public int Status => _status;
    public string? Path => _path;
    public long? MaxSize => _maxSize;
    public DateTime? StopTime => _stopTime;
    public int? MaxFiles => _maxFiles;
    public bool? IsRowset => _isRowset;
    public bool? IsRollover => _isRollover;
    public bool? IsShutdown => _isShutdown;
    public bool? IsDefault => _isDefault;
    public int? BufferCount => _bufferCount;
    public int? BufferSize => _bufferSize;
    public long? FilePosition => _filePosition;
    public int? ReaderSpid => _readerSpid;
    public DateTime? StartTime => _startTime;
    public DateTime? LastEventTime => _lastEventTime;
    public long? EventCount => _eventCount;
    public int? DroppedEventCount => _droppedEventCount;
}
