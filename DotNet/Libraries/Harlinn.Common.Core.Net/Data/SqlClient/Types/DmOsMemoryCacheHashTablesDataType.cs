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

public class DmOsMemoryCacheHashTablesDataType
{
    readonly byte[] _cacheAddress = Array.Empty<byte>();
    readonly string _name = string.Empty;
    readonly string _type = string.Empty;
    readonly int _tableLevel = 0;
    readonly int _bucketsCount = 0;
    readonly int _bucketsInUseCount = 0;
    readonly int _bucketsMinLength = 0;
    readonly int _bucketsMaxLength = 0;
    readonly int _bucketsAvgLength = 0;
    readonly int _bucketsMaxLengthEver = 0;
    readonly long _hitsCount = 0;
    readonly long _missesCount = 0;
    readonly int _bucketsAvgScanHitLength = 0;
    readonly int _bucketsAvgScanMissLength = 0;

    public DmOsMemoryCacheHashTablesDataType( )
    {
    }

    public DmOsMemoryCacheHashTablesDataType(byte[] cacheAddress,
        string name,
        string type,
        int tableLevel,
        int bucketsCount,
        int bucketsInUseCount,
        int bucketsMinLength,
        int bucketsMaxLength,
        int bucketsAvgLength,
        int bucketsMaxLengthEver,
        long hitsCount,
        long missesCount,
        int bucketsAvgScanHitLength,
        int bucketsAvgScanMissLength)
    {
        _cacheAddress = cacheAddress;
        _name = name;
        _type = type;
        _tableLevel = tableLevel;
        _bucketsCount = bucketsCount;
        _bucketsInUseCount = bucketsInUseCount;
        _bucketsMinLength = bucketsMinLength;
        _bucketsMaxLength = bucketsMaxLength;
        _bucketsAvgLength = bucketsAvgLength;
        _bucketsMaxLengthEver = bucketsMaxLengthEver;
        _hitsCount = hitsCount;
        _missesCount = missesCount;
        _bucketsAvgScanHitLength = bucketsAvgScanHitLength;
        _bucketsAvgScanMissLength = bucketsAvgScanMissLength;
    }

    public byte[] CacheAddress => _cacheAddress;
    public string Name => _name;
    public string Type => _type;
    public int TableLevel => _tableLevel;
    public int BucketsCount => _bucketsCount;
    public int BucketsInUseCount => _bucketsInUseCount;
    public int BucketsMinLength => _bucketsMinLength;
    public int BucketsMaxLength => _bucketsMaxLength;
    public int BucketsAvgLength => _bucketsAvgLength;
    public int BucketsMaxLengthEver => _bucketsMaxLengthEver;
    public long HitsCount => _hitsCount;
    public long MissesCount => _missesCount;
    public int BucketsAvgScanHitLength => _bucketsAvgScanHitLength;
    public int BucketsAvgScanMissLength => _bucketsAvgScanMissLength;
}
