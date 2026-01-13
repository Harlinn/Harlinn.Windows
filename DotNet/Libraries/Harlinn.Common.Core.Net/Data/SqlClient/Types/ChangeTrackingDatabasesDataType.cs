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

public class ChangeTrackingDatabasesDataType
{
    readonly int _databaseId = 0;
    readonly byte? _isAutoCleanupOn;
    readonly int? _retentionPeriod;
    readonly byte? _retentionPeriodUnits;
    readonly string? _retentionPeriodUnitsDesc;
    readonly long? _maxCleanupVersion;

    public ChangeTrackingDatabasesDataType( )
    {
    }

    public ChangeTrackingDatabasesDataType(int databaseId,
        byte? isAutoCleanupOn,
        int? retentionPeriod,
        byte? retentionPeriodUnits,
        string? retentionPeriodUnitsDesc,
        long? maxCleanupVersion)
    {
        _databaseId = databaseId;
        _isAutoCleanupOn = isAutoCleanupOn;
        _retentionPeriod = retentionPeriod;
        _retentionPeriodUnits = retentionPeriodUnits;
        _retentionPeriodUnitsDesc = retentionPeriodUnitsDesc;
        _maxCleanupVersion = maxCleanupVersion;
    }

    public int DatabaseId => _databaseId;
    public byte? IsAutoCleanupOn => _isAutoCleanupOn;
    public int? RetentionPeriod => _retentionPeriod;
    public byte? RetentionPeriodUnits => _retentionPeriodUnits;
    public string? RetentionPeriodUnitsDesc => _retentionPeriodUnitsDesc;
    public long? MaxCleanupVersion => _maxCleanupVersion;
}
