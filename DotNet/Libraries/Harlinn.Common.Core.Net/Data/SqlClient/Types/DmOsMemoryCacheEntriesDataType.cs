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

public class DmOsMemoryCacheEntriesDataType
{
    readonly byte[] _cacheAddress = Array.Empty<byte>();
    readonly string _name = string.Empty;
    readonly string _type = string.Empty;
    readonly byte[] _entryAddress = Array.Empty<byte>();
    readonly byte[] _entryDataAddress = Array.Empty<byte>();
    readonly int _inUseCount = 0;
    readonly bool _isDirty = false;
    readonly int _diskIosCount = 0;
    readonly int _contextSwitchesCount = 0;
    readonly int _originalCost = 0;
    readonly int _currentCost = 0;
    readonly byte[]? _memoryObjectAddress;
    readonly long _pagesKb = 0;
    readonly string? _entryData;
    readonly int? _poolId;
    readonly double? _timeToGenerate;
    readonly long? _useCount;
    readonly double? _averageTimeBetweenUses;
    readonly double? _timeSinceLastUse;
    readonly double? _probabilityOfReuse;
    readonly double? _value;

    public DmOsMemoryCacheEntriesDataType( )
    {
    }

    public DmOsMemoryCacheEntriesDataType(byte[] cacheAddress,
        string name,
        string type,
        byte[] entryAddress,
        byte[] entryDataAddress,
        int inUseCount,
        bool isDirty,
        int diskIosCount,
        int contextSwitchesCount,
        int originalCost,
        int currentCost,
        byte[]? memoryObjectAddress,
        long pagesKb,
        string? entryData,
        int? poolId,
        double? timeToGenerate,
        long? useCount,
        double? averageTimeBetweenUses,
        double? timeSinceLastUse,
        double? probabilityOfReuse,
        double? value)
    {
        _cacheAddress = cacheAddress;
        _name = name;
        _type = type;
        _entryAddress = entryAddress;
        _entryDataAddress = entryDataAddress;
        _inUseCount = inUseCount;
        _isDirty = isDirty;
        _diskIosCount = diskIosCount;
        _contextSwitchesCount = contextSwitchesCount;
        _originalCost = originalCost;
        _currentCost = currentCost;
        _memoryObjectAddress = memoryObjectAddress;
        _pagesKb = pagesKb;
        _entryData = entryData;
        _poolId = poolId;
        _timeToGenerate = timeToGenerate;
        _useCount = useCount;
        _averageTimeBetweenUses = averageTimeBetweenUses;
        _timeSinceLastUse = timeSinceLastUse;
        _probabilityOfReuse = probabilityOfReuse;
        _value = value;
    }

    public byte[] CacheAddress => _cacheAddress;
    public string Name => _name;
    public string Type => _type;
    public byte[] EntryAddress => _entryAddress;
    public byte[] EntryDataAddress => _entryDataAddress;
    public int InUseCount => _inUseCount;
    public bool IsDirty => _isDirty;
    public int DiskIosCount => _diskIosCount;
    public int ContextSwitchesCount => _contextSwitchesCount;
    public int OriginalCost => _originalCost;
    public int CurrentCost => _currentCost;
    public byte[]? MemoryObjectAddress => _memoryObjectAddress;
    public long PagesKb => _pagesKb;
    public string? EntryData => _entryData;
    public int? PoolId => _poolId;
    public double? TimeToGenerate => _timeToGenerate;
    public long? UseCount => _useCount;
    public double? AverageTimeBetweenUses => _averageTimeBetweenUses;
    public double? TimeSinceLastUse => _timeSinceLastUse;
    public double? ProbabilityOfReuse => _probabilityOfReuse;
    public double? Value => _value;
}
