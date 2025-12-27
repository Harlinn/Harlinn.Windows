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

public class DmReplTranhashDataType
{
    readonly int? _buckets;
    readonly int? _hashedTrans;
    readonly int? _completedTrans;
    readonly int? _compensatedTrans;
    readonly string? _firstBeginLsn;
    readonly string? _lastCommitLsn;

    public DmReplTranhashDataType( )
    {
    }

    public DmReplTranhashDataType(int? buckets,
        int? hashedTrans,
        int? completedTrans,
        int? compensatedTrans,
        string? firstBeginLsn,
        string? lastCommitLsn)
    {
        _buckets = buckets;
        _hashedTrans = hashedTrans;
        _completedTrans = completedTrans;
        _compensatedTrans = compensatedTrans;
        _firstBeginLsn = firstBeginLsn;
        _lastCommitLsn = lastCommitLsn;
    }

    public int? Buckets => _buckets;
    public int? HashedTrans => _hashedTrans;
    public int? CompletedTrans => _completedTrans;
    public int? CompensatedTrans => _compensatedTrans;
    public string? FirstBeginLsn => _firstBeginLsn;
    public string? LastCommitLsn => _lastCommitLsn;
}
