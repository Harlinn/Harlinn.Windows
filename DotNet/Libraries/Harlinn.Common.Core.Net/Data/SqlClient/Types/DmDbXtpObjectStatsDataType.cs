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

public class DmDbXtpObjectStatsDataType
{
    readonly int _objectId = 0;
    readonly int _xtpObjectId = 0;
    readonly long _rowInsertAttempts = 0;
    readonly long _rowUpdateAttempts = 0;
    readonly long _rowDeleteAttempts = 0;
    readonly long _writeConflicts = 0;
    readonly long _uniqueConstraintViolations = 0;
    readonly byte[] _objectAddress = Array.Empty<byte>();

    public DmDbXtpObjectStatsDataType( )
    {
    }

    public DmDbXtpObjectStatsDataType(int objectId,
        int xtpObjectId,
        long rowInsertAttempts,
        long rowUpdateAttempts,
        long rowDeleteAttempts,
        long writeConflicts,
        long uniqueConstraintViolations,
        byte[] objectAddress)
    {
        _objectId = objectId;
        _xtpObjectId = xtpObjectId;
        _rowInsertAttempts = rowInsertAttempts;
        _rowUpdateAttempts = rowUpdateAttempts;
        _rowDeleteAttempts = rowDeleteAttempts;
        _writeConflicts = writeConflicts;
        _uniqueConstraintViolations = uniqueConstraintViolations;
        _objectAddress = objectAddress;
    }

    public int ObjectId => _objectId;
    public int XtpObjectId => _xtpObjectId;
    public long RowInsertAttempts => _rowInsertAttempts;
    public long RowUpdateAttempts => _rowUpdateAttempts;
    public long RowDeleteAttempts => _rowDeleteAttempts;
    public long WriteConflicts => _writeConflicts;
    public long UniqueConstraintViolations => _uniqueConstraintViolations;
    public byte[] ObjectAddress => _objectAddress;
}
