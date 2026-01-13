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

public class DmDbXtpTableMemoryStatsDataType
{
    readonly int? _objectId;
    readonly long? _memoryAllocatedForTableKb;
    readonly long? _memoryUsedByTableKb;
    readonly long? _memoryAllocatedForIndexesKb;
    readonly long? _memoryUsedByIndexesKb;

    public DmDbXtpTableMemoryStatsDataType( )
    {
    }

    public DmDbXtpTableMemoryStatsDataType(int? objectId,
        long? memoryAllocatedForTableKb,
        long? memoryUsedByTableKb,
        long? memoryAllocatedForIndexesKb,
        long? memoryUsedByIndexesKb)
    {
        _objectId = objectId;
        _memoryAllocatedForTableKb = memoryAllocatedForTableKb;
        _memoryUsedByTableKb = memoryUsedByTableKb;
        _memoryAllocatedForIndexesKb = memoryAllocatedForIndexesKb;
        _memoryUsedByIndexesKb = memoryUsedByIndexesKb;
    }

    public int? ObjectId => _objectId;
    public long? MemoryAllocatedForTableKb => _memoryAllocatedForTableKb;
    public long? MemoryUsedByTableKb => _memoryUsedByTableKb;
    public long? MemoryAllocatedForIndexesKb => _memoryAllocatedForIndexesKb;
    public long? MemoryUsedByIndexesKb => _memoryUsedByIndexesKb;
}
