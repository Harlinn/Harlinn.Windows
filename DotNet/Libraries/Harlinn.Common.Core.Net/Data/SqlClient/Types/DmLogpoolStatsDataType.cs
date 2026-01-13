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

public class DmLogpoolStatsDataType
{
    readonly long _hashHitTotalSearchLength = 0;
    readonly long _hashMissTotalSearchLength = 0;
    readonly long _hashHits = 0;
    readonly long _hashMisses = 0;
    readonly int _hashBucketCount = 0;
    readonly long _memStatusStamp = 0;
    readonly int _memStatus = 0;
    readonly int _logpoolmgrCount = 0;
    readonly long _totalPages = 0;
    readonly long _privatePages = 0;

    public DmLogpoolStatsDataType( )
    {
    }

    public DmLogpoolStatsDataType(long hashHitTotalSearchLength,
        long hashMissTotalSearchLength,
        long hashHits,
        long hashMisses,
        int hashBucketCount,
        long memStatusStamp,
        int memStatus,
        int logpoolmgrCount,
        long totalPages,
        long privatePages)
    {
        _hashHitTotalSearchLength = hashHitTotalSearchLength;
        _hashMissTotalSearchLength = hashMissTotalSearchLength;
        _hashHits = hashHits;
        _hashMisses = hashMisses;
        _hashBucketCount = hashBucketCount;
        _memStatusStamp = memStatusStamp;
        _memStatus = memStatus;
        _logpoolmgrCount = logpoolmgrCount;
        _totalPages = totalPages;
        _privatePages = privatePages;
    }

    public long HashHitTotalSearchLength => _hashHitTotalSearchLength;
    public long HashMissTotalSearchLength => _hashMissTotalSearchLength;
    public long HashHits => _hashHits;
    public long HashMisses => _hashMisses;
    public int HashBucketCount => _hashBucketCount;
    public long MemStatusStamp => _memStatusStamp;
    public int MemStatus => _memStatus;
    public int LogpoolmgrCount => _logpoolmgrCount;
    public long TotalPages => _totalPages;
    public long PrivatePages => _privatePages;
}
