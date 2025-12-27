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

public class DatabaseMirroringWitnessesDataType
{
    readonly string _databaseName = string.Empty;
    readonly string? _principalServerName;
    readonly string? _mirrorServerName;
    readonly byte _safetyLevel = 0;
    readonly string? _safetyLevelDesc;
    readonly int _safetySequenceNumber = 0;
    readonly int _roleSequenceNumber = 0;
    readonly Guid _mirroringGuid;
    readonly Guid _familyGuid;
    readonly bool? _isSuspended;
    readonly int _isSuspendedSequenceNumber = 0;
    readonly byte? _partnerSyncState;
    readonly string? _partnerSyncStateDesc;

    public DatabaseMirroringWitnessesDataType( )
    {
    }

    public DatabaseMirroringWitnessesDataType(string databaseName,
        string? principalServerName,
        string? mirrorServerName,
        byte safetyLevel,
        string? safetyLevelDesc,
        int safetySequenceNumber,
        int roleSequenceNumber,
        Guid mirroringGuid,
        Guid familyGuid,
        bool? isSuspended,
        int isSuspendedSequenceNumber,
        byte? partnerSyncState,
        string? partnerSyncStateDesc)
    {
        _databaseName = databaseName;
        _principalServerName = principalServerName;
        _mirrorServerName = mirrorServerName;
        _safetyLevel = safetyLevel;
        _safetyLevelDesc = safetyLevelDesc;
        _safetySequenceNumber = safetySequenceNumber;
        _roleSequenceNumber = roleSequenceNumber;
        _mirroringGuid = mirroringGuid;
        _familyGuid = familyGuid;
        _isSuspended = isSuspended;
        _isSuspendedSequenceNumber = isSuspendedSequenceNumber;
        _partnerSyncState = partnerSyncState;
        _partnerSyncStateDesc = partnerSyncStateDesc;
    }

    public string DatabaseName => _databaseName;
    public string? PrincipalServerName => _principalServerName;
    public string? MirrorServerName => _mirrorServerName;
    public byte SafetyLevel => _safetyLevel;
    public string? SafetyLevelDesc => _safetyLevelDesc;
    public int SafetySequenceNumber => _safetySequenceNumber;
    public int RoleSequenceNumber => _roleSequenceNumber;
    public Guid MirroringGuid => _mirroringGuid;
    public Guid FamilyGuid => _familyGuid;
    public bool? IsSuspended => _isSuspended;
    public int IsSuspendedSequenceNumber => _isSuspendedSequenceNumber;
    public byte? PartnerSyncState => _partnerSyncState;
    public string? PartnerSyncStateDesc => _partnerSyncStateDesc;
}
