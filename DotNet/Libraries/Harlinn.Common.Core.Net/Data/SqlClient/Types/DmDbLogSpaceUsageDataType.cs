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

public class DmDbLogSpaceUsageDataType
{
    readonly int? _databaseId;
    readonly long? _totalLogSizeInBytes;
    readonly long? _usedLogSpaceInBytes;
    readonly float? _usedLogSpaceInPercent;
    readonly long? _logSpaceInBytesSinceLastBackup;

    public DmDbLogSpaceUsageDataType( )
    {
    }

    public DmDbLogSpaceUsageDataType(int? databaseId,
        long? totalLogSizeInBytes,
        long? usedLogSpaceInBytes,
        float? usedLogSpaceInPercent,
        long? logSpaceInBytesSinceLastBackup)
    {
        _databaseId = databaseId;
        _totalLogSizeInBytes = totalLogSizeInBytes;
        _usedLogSpaceInBytes = usedLogSpaceInBytes;
        _usedLogSpaceInPercent = usedLogSpaceInPercent;
        _logSpaceInBytesSinceLastBackup = logSpaceInBytesSinceLastBackup;
    }

    public int? DatabaseId => _databaseId;
    public long? TotalLogSizeInBytes => _totalLogSizeInBytes;
    public long? UsedLogSpaceInBytes => _usedLogSpaceInBytes;
    public float? UsedLogSpaceInPercent => _usedLogSpaceInPercent;
    public long? LogSpaceInBytesSinceLastBackup => _logSpaceInBytesSinceLastBackup;
}
