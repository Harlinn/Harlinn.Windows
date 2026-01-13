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

public class DmDbXtpHashIndexStatsDataType
{
    readonly int _objectId = 0;
    readonly int _xtpObjectId = 0;
    readonly int _indexId = 0;
    readonly long _totalBucketCount = 0;
    readonly long? _emptyBucketCount;
    readonly long _avgChainLength = 0;
    readonly long _maxChainLength = 0;

    public DmDbXtpHashIndexStatsDataType( )
    {
    }

    public DmDbXtpHashIndexStatsDataType(int objectId,
        int xtpObjectId,
        int indexId,
        long totalBucketCount,
        long? emptyBucketCount,
        long avgChainLength,
        long maxChainLength)
    {
        _objectId = objectId;
        _xtpObjectId = xtpObjectId;
        _indexId = indexId;
        _totalBucketCount = totalBucketCount;
        _emptyBucketCount = emptyBucketCount;
        _avgChainLength = avgChainLength;
        _maxChainLength = maxChainLength;
    }

    public int ObjectId => _objectId;
    public int XtpObjectId => _xtpObjectId;
    public int IndexId => _indexId;
    public long TotalBucketCount => _totalBucketCount;
    public long? EmptyBucketCount => _emptyBucketCount;
    public long AvgChainLength => _avgChainLength;
    public long MaxChainLength => _maxChainLength;
}
