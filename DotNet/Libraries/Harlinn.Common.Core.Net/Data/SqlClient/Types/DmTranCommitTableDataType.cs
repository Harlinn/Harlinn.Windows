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

public class DmTranCommitTableDataType
{
    readonly long? _commitTs;
    readonly long? _xdesId;
    readonly long _commitLbn = 0;
    readonly long _commitCsn = 0;
    readonly DateTime _commitTime;

    public DmTranCommitTableDataType( )
    {
    }

    public DmTranCommitTableDataType(long? commitTs,
        long? xdesId,
        long commitLbn,
        long commitCsn,
        DateTime commitTime)
    {
        _commitTs = commitTs;
        _xdesId = xdesId;
        _commitLbn = commitLbn;
        _commitCsn = commitCsn;
        _commitTime = commitTime;
    }

    public long? CommitTs => _commitTs;
    public long? XdesId => _xdesId;
    public long CommitLbn => _commitLbn;
    public long CommitCsn => _commitCsn;
    public DateTime CommitTime => _commitTime;
}
