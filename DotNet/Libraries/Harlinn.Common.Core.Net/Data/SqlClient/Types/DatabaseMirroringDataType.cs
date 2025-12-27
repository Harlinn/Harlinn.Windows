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

public class DatabaseMirroringDataType
{
    readonly int _databaseId = 0;
    readonly Guid? _mirroringGuid;
    readonly byte? _mirroringState;
    readonly string? _mirroringStateDesc;
    readonly byte? _mirroringRole;
    readonly string? _mirroringRoleDesc;
    readonly int? _mirroringRoleSequence;
    readonly byte? _mirroringSafetyLevel;
    readonly string? _mirroringSafetyLevelDesc;
    readonly int? _mirroringSafetySequence;
    readonly string? _mirroringPartnerName;
    readonly string? _mirroringPartnerInstance;
    readonly string? _mirroringWitnessName;
    readonly byte? _mirroringWitnessState;
    readonly string? _mirroringWitnessStateDesc;
    readonly object? _mirroringFailoverLsn;
    readonly int? _mirroringConnectionTimeout;
    readonly int? _mirroringRedoQueue;
    readonly string? _mirroringRedoQueueType;
    readonly object? _mirroringEndOfLogLsn;
    readonly object? _mirroringReplicationLsn;

    public DatabaseMirroringDataType( )
    {
    }

    public DatabaseMirroringDataType(int databaseId,
        Guid? mirroringGuid,
        byte? mirroringState,
        string? mirroringStateDesc,
        byte? mirroringRole,
        string? mirroringRoleDesc,
        int? mirroringRoleSequence,
        byte? mirroringSafetyLevel,
        string? mirroringSafetyLevelDesc,
        int? mirroringSafetySequence,
        string? mirroringPartnerName,
        string? mirroringPartnerInstance,
        string? mirroringWitnessName,
        byte? mirroringWitnessState,
        string? mirroringWitnessStateDesc,
        object? mirroringFailoverLsn,
        int? mirroringConnectionTimeout,
        int? mirroringRedoQueue,
        string? mirroringRedoQueueType,
        object? mirroringEndOfLogLsn,
        object? mirroringReplicationLsn)
    {
        _databaseId = databaseId;
        _mirroringGuid = mirroringGuid;
        _mirroringState = mirroringState;
        _mirroringStateDesc = mirroringStateDesc;
        _mirroringRole = mirroringRole;
        _mirroringRoleDesc = mirroringRoleDesc;
        _mirroringRoleSequence = mirroringRoleSequence;
        _mirroringSafetyLevel = mirroringSafetyLevel;
        _mirroringSafetyLevelDesc = mirroringSafetyLevelDesc;
        _mirroringSafetySequence = mirroringSafetySequence;
        _mirroringPartnerName = mirroringPartnerName;
        _mirroringPartnerInstance = mirroringPartnerInstance;
        _mirroringWitnessName = mirroringWitnessName;
        _mirroringWitnessState = mirroringWitnessState;
        _mirroringWitnessStateDesc = mirroringWitnessStateDesc;
        _mirroringFailoverLsn = mirroringFailoverLsn;
        _mirroringConnectionTimeout = mirroringConnectionTimeout;
        _mirroringRedoQueue = mirroringRedoQueue;
        _mirroringRedoQueueType = mirroringRedoQueueType;
        _mirroringEndOfLogLsn = mirroringEndOfLogLsn;
        _mirroringReplicationLsn = mirroringReplicationLsn;
    }

    public int DatabaseId => _databaseId;
    public Guid? MirroringGuid => _mirroringGuid;
    public byte? MirroringState => _mirroringState;
    public string? MirroringStateDesc => _mirroringStateDesc;
    public byte? MirroringRole => _mirroringRole;
    public string? MirroringRoleDesc => _mirroringRoleDesc;
    public int? MirroringRoleSequence => _mirroringRoleSequence;
    public byte? MirroringSafetyLevel => _mirroringSafetyLevel;
    public string? MirroringSafetyLevelDesc => _mirroringSafetyLevelDesc;
    public int? MirroringSafetySequence => _mirroringSafetySequence;
    public string? MirroringPartnerName => _mirroringPartnerName;
    public string? MirroringPartnerInstance => _mirroringPartnerInstance;
    public string? MirroringWitnessName => _mirroringWitnessName;
    public byte? MirroringWitnessState => _mirroringWitnessState;
    public string? MirroringWitnessStateDesc => _mirroringWitnessStateDesc;
    public object? MirroringFailoverLsn => _mirroringFailoverLsn;
    public int? MirroringConnectionTimeout => _mirroringConnectionTimeout;
    public int? MirroringRedoQueue => _mirroringRedoQueue;
    public string? MirroringRedoQueueType => _mirroringRedoQueueType;
    public object? MirroringEndOfLogLsn => _mirroringEndOfLogLsn;
    public object? MirroringReplicationLsn => _mirroringReplicationLsn;
}
