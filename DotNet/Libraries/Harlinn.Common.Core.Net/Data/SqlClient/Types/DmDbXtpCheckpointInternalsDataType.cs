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

public class DmDbXtpCheckpointInternalsDataType
{
    readonly long _checkpointId = 0;
    readonly long? _checkpointTimestamp;
    readonly object? _lastSegmentLsn;
    readonly object? _recoveryLsn;
    readonly bool? _isSynchronized;

    public DmDbXtpCheckpointInternalsDataType( )
    {
    }

    public DmDbXtpCheckpointInternalsDataType(long checkpointId,
        long? checkpointTimestamp,
        object? lastSegmentLsn,
        object? recoveryLsn,
        bool? isSynchronized)
    {
        _checkpointId = checkpointId;
        _checkpointTimestamp = checkpointTimestamp;
        _lastSegmentLsn = lastSegmentLsn;
        _recoveryLsn = recoveryLsn;
        _isSynchronized = isSynchronized;
    }

    public long CheckpointId => _checkpointId;
    public long? CheckpointTimestamp => _checkpointTimestamp;
    public object? LastSegmentLsn => _lastSegmentLsn;
    public object? RecoveryLsn => _recoveryLsn;
    public bool? IsSynchronized => _isSynchronized;
}
