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

public class DmHadrAvailabilityGroupStatesDataType
{
    readonly Guid _groupId;
    readonly string? _primaryReplica;
    readonly byte? _primaryRecoveryHealth;
    readonly string? _primaryRecoveryHealthDesc;
    readonly byte? _secondaryRecoveryHealth;
    readonly string? _secondaryRecoveryHealthDesc;
    readonly byte? _synchronizationHealth;
    readonly string? _synchronizationHealthDesc;

    public DmHadrAvailabilityGroupStatesDataType( )
    {
    }

    public DmHadrAvailabilityGroupStatesDataType(Guid groupId,
        string? primaryReplica,
        byte? primaryRecoveryHealth,
        string? primaryRecoveryHealthDesc,
        byte? secondaryRecoveryHealth,
        string? secondaryRecoveryHealthDesc,
        byte? synchronizationHealth,
        string? synchronizationHealthDesc)
    {
        _groupId = groupId;
        _primaryReplica = primaryReplica;
        _primaryRecoveryHealth = primaryRecoveryHealth;
        _primaryRecoveryHealthDesc = primaryRecoveryHealthDesc;
        _secondaryRecoveryHealth = secondaryRecoveryHealth;
        _secondaryRecoveryHealthDesc = secondaryRecoveryHealthDesc;
        _synchronizationHealth = synchronizationHealth;
        _synchronizationHealthDesc = synchronizationHealthDesc;
    }

    public Guid GroupId => _groupId;
    public string? PrimaryReplica => _primaryReplica;
    public byte? PrimaryRecoveryHealth => _primaryRecoveryHealth;
    public string? PrimaryRecoveryHealthDesc => _primaryRecoveryHealthDesc;
    public byte? SecondaryRecoveryHealth => _secondaryRecoveryHealth;
    public string? SecondaryRecoveryHealthDesc => _secondaryRecoveryHealthDesc;
    public byte? SynchronizationHealth => _synchronizationHealth;
    public string? SynchronizationHealthDesc => _synchronizationHealthDesc;
}
