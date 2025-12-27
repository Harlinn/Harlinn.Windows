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

public class DmDbXtpIndexStatsDataType
{
    readonly int _objectId = 0;
    readonly int _xtpObjectId = 0;
    readonly int _indexId = 0;
    readonly long _scansStarted = 0;
    readonly long _scansRetries = 0;
    readonly long _rowsReturned = 0;
    readonly long _rowsTouched = 0;
    readonly long _rowsExpiring = 0;
    readonly long _rowsExpired = 0;
    readonly long _rowsExpiredRemoved = 0;
    readonly long _phantomScansStarted = 0;
    readonly long _phantomScansRetries = 0;
    readonly long _phantomRowsTouched = 0;
    readonly long _phantomExpiringRowsEncountered = 0;
    readonly long _phantomExpiredRemovedRowsEncountered = 0;
    readonly long _phantomExpiredRowsRemoved = 0;
    readonly byte[] _objectAddress = Array.Empty<byte>();

    public DmDbXtpIndexStatsDataType( )
    {
    }

    public DmDbXtpIndexStatsDataType(int objectId,
        int xtpObjectId,
        int indexId,
        long scansStarted,
        long scansRetries,
        long rowsReturned,
        long rowsTouched,
        long rowsExpiring,
        long rowsExpired,
        long rowsExpiredRemoved,
        long phantomScansStarted,
        long phantomScansRetries,
        long phantomRowsTouched,
        long phantomExpiringRowsEncountered,
        long phantomExpiredRemovedRowsEncountered,
        long phantomExpiredRowsRemoved,
        byte[] objectAddress)
    {
        _objectId = objectId;
        _xtpObjectId = xtpObjectId;
        _indexId = indexId;
        _scansStarted = scansStarted;
        _scansRetries = scansRetries;
        _rowsReturned = rowsReturned;
        _rowsTouched = rowsTouched;
        _rowsExpiring = rowsExpiring;
        _rowsExpired = rowsExpired;
        _rowsExpiredRemoved = rowsExpiredRemoved;
        _phantomScansStarted = phantomScansStarted;
        _phantomScansRetries = phantomScansRetries;
        _phantomRowsTouched = phantomRowsTouched;
        _phantomExpiringRowsEncountered = phantomExpiringRowsEncountered;
        _phantomExpiredRemovedRowsEncountered = phantomExpiredRemovedRowsEncountered;
        _phantomExpiredRowsRemoved = phantomExpiredRowsRemoved;
        _objectAddress = objectAddress;
    }

    public int ObjectId => _objectId;
    public int XtpObjectId => _xtpObjectId;
    public int IndexId => _indexId;
    public long ScansStarted => _scansStarted;
    public long ScansRetries => _scansRetries;
    public long RowsReturned => _rowsReturned;
    public long RowsTouched => _rowsTouched;
    public long RowsExpiring => _rowsExpiring;
    public long RowsExpired => _rowsExpired;
    public long RowsExpiredRemoved => _rowsExpiredRemoved;
    public long PhantomScansStarted => _phantomScansStarted;
    public long PhantomScansRetries => _phantomScansRetries;
    public long PhantomRowsTouched => _phantomRowsTouched;
    public long PhantomExpiringRowsEncountered => _phantomExpiringRowsEncountered;
    public long PhantomExpiredRemovedRowsEncountered => _phantomExpiredRemovedRowsEncountered;
    public long PhantomExpiredRowsRemoved => _phantomExpiredRowsRemoved;
    public byte[] ObjectAddress => _objectAddress;
}
