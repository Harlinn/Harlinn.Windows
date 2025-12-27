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

public class DmLogpoolHashentriesDataType
{
    readonly int _bucketNo = 0;
    readonly int _databaseId = 0;
    readonly int _recoveryUnitId = 0;
    readonly long _logBlockId = 0;
    readonly byte[] _cacheBuffer = Array.Empty<byte>();

    public DmLogpoolHashentriesDataType( )
    {
    }

    public DmLogpoolHashentriesDataType(int bucketNo,
        int databaseId,
        int recoveryUnitId,
        long logBlockId,
        byte[] cacheBuffer)
    {
        _bucketNo = bucketNo;
        _databaseId = databaseId;
        _recoveryUnitId = recoveryUnitId;
        _logBlockId = logBlockId;
        _cacheBuffer = cacheBuffer;
    }

    public int BucketNo => _bucketNo;
    public int DatabaseId => _databaseId;
    public int RecoveryUnitId => _recoveryUnitId;
    public long LogBlockId => _logBlockId;
    public byte[] CacheBuffer => _cacheBuffer;
}
