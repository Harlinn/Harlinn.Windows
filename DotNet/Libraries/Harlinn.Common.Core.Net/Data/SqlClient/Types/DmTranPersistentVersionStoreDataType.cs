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

public class DmTranPersistentVersionStoreDataType
{
    readonly long _xdesTsPush = 0;
    readonly long _xdesTsTran = 0;
    readonly int? _subidPush;
    readonly int? _subidTran;
    readonly long _rowsetId = 0;
    readonly byte[] _secVersionRid = Array.Empty<byte>();
    readonly short? _minLen;
    readonly long? _seqNum;
    readonly byte[] _prevRowInChain = Array.Empty<byte>();
    readonly byte[] _rowVersion = Array.Empty<byte>();

    public DmTranPersistentVersionStoreDataType( )
    {
    }

    public DmTranPersistentVersionStoreDataType(long xdesTsPush,
        long xdesTsTran,
        int? subidPush,
        int? subidTran,
        long rowsetId,
        byte[] secVersionRid,
        short? minLen,
        long? seqNum,
        byte[] prevRowInChain,
        byte[] rowVersion)
    {
        _xdesTsPush = xdesTsPush;
        _xdesTsTran = xdesTsTran;
        _subidPush = subidPush;
        _subidTran = subidTran;
        _rowsetId = rowsetId;
        _secVersionRid = secVersionRid;
        _minLen = minLen;
        _seqNum = seqNum;
        _prevRowInChain = prevRowInChain;
        _rowVersion = rowVersion;
    }

    public long XdesTsPush => _xdesTsPush;
    public long XdesTsTran => _xdesTsTran;
    public int? SubidPush => _subidPush;
    public int? SubidTran => _subidTran;
    public long RowsetId => _rowsetId;
    public byte[] SecVersionRid => _secVersionRid;
    public short? MinLen => _minLen;
    public long? SeqNum => _seqNum;
    public byte[] PrevRowInChain => _prevRowInChain;
    public byte[] RowVersion => _rowVersion;
}
