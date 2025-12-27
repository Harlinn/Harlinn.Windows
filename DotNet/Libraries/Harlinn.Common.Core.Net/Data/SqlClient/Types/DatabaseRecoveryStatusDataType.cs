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

public class DatabaseRecoveryStatusDataType
{
    readonly int _databaseId = 0;
    readonly Guid? _databaseGuid;
    readonly Guid? _familyGuid;
    readonly object? _lastLogBackupLsn;
    readonly Guid? _recoveryForkGuid;
    readonly Guid? _firstRecoveryForkGuid;
    readonly object? _forkPointLsn;

    public DatabaseRecoveryStatusDataType( )
    {
    }

    public DatabaseRecoveryStatusDataType(int databaseId,
        Guid? databaseGuid,
        Guid? familyGuid,
        object? lastLogBackupLsn,
        Guid? recoveryForkGuid,
        Guid? firstRecoveryForkGuid,
        object? forkPointLsn)
    {
        _databaseId = databaseId;
        _databaseGuid = databaseGuid;
        _familyGuid = familyGuid;
        _lastLogBackupLsn = lastLogBackupLsn;
        _recoveryForkGuid = recoveryForkGuid;
        _firstRecoveryForkGuid = firstRecoveryForkGuid;
        _forkPointLsn = forkPointLsn;
    }

    public int DatabaseId => _databaseId;
    public Guid? DatabaseGuid => _databaseGuid;
    public Guid? FamilyGuid => _familyGuid;
    public object? LastLogBackupLsn => _lastLogBackupLsn;
    public Guid? RecoveryForkGuid => _recoveryForkGuid;
    public Guid? FirstRecoveryForkGuid => _firstRecoveryForkGuid;
    public object? ForkPointLsn => _forkPointLsn;
}
