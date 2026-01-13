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

public class AvailabilityGroupsClusterDataType
{
    readonly Guid _groupId;
    readonly string? _name;
    readonly string? _resourceId;
    readonly string? _resourceGroupId;
    readonly int? _failureConditionLevel;
    readonly int? _healthCheckTimeout;
    readonly byte? _automatedBackupPreference;
    readonly string? _automatedBackupPreferenceDesc;

    public AvailabilityGroupsClusterDataType( )
    {
    }

    public AvailabilityGroupsClusterDataType(Guid groupId,
        string? name,
        string? resourceId,
        string? resourceGroupId,
        int? failureConditionLevel,
        int? healthCheckTimeout,
        byte? automatedBackupPreference,
        string? automatedBackupPreferenceDesc)
    {
        _groupId = groupId;
        _name = name;
        _resourceId = resourceId;
        _resourceGroupId = resourceGroupId;
        _failureConditionLevel = failureConditionLevel;
        _healthCheckTimeout = healthCheckTimeout;
        _automatedBackupPreference = automatedBackupPreference;
        _automatedBackupPreferenceDesc = automatedBackupPreferenceDesc;
    }

    public Guid GroupId => _groupId;
    public string? Name => _name;
    public string? ResourceId => _resourceId;
    public string? ResourceGroupId => _resourceGroupId;
    public int? FailureConditionLevel => _failureConditionLevel;
    public int? HealthCheckTimeout => _healthCheckTimeout;
    public byte? AutomatedBackupPreference => _automatedBackupPreference;
    public string? AutomatedBackupPreferenceDesc => _automatedBackupPreferenceDesc;
}
