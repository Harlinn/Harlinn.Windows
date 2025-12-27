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

public class DmCacheSizeDataType
{
    readonly short? _distributionId;
    readonly long? _cacheUsed;
    readonly long? _cacheAvailable;
    readonly long? _cacheCapacity;

    public DmCacheSizeDataType( )
    {
    }

    public DmCacheSizeDataType(short? distributionId,
        long? cacheUsed,
        long? cacheAvailable,
        long? cacheCapacity)
    {
        _distributionId = distributionId;
        _cacheUsed = cacheUsed;
        _cacheAvailable = cacheAvailable;
        _cacheCapacity = cacheCapacity;
    }

    public short? DistributionId => _distributionId;
    public long? CacheUsed => _cacheUsed;
    public long? CacheAvailable => _cacheAvailable;
    public long? CacheCapacity => _cacheCapacity;
}
