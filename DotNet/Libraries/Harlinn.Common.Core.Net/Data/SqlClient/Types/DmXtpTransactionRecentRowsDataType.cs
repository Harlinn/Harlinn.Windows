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

public class DmXtpTransactionRecentRowsDataType
{
    readonly short _nodeId = 0;
    readonly long _xtpTransactionId = 0;
    readonly byte[] _rowAddress = Array.Empty<byte>();
    readonly byte[] _tableAddress = Array.Empty<byte>();
    readonly long _beforeBegin = 0;
    readonly long _beforeEnd = 0;
    readonly int _beforeLinks = 0;
    readonly long _beforeTime = 0;
    readonly long _afterBegin = 0;
    readonly long _afterEnd = 0;
    readonly int _afterLinks = 0;
    readonly long _afterTime = 0;
    readonly byte[] _outcome = Array.Empty<byte>();

    public DmXtpTransactionRecentRowsDataType( )
    {
    }

    public DmXtpTransactionRecentRowsDataType(short nodeId,
        long xtpTransactionId,
        byte[] rowAddress,
        byte[] tableAddress,
        long beforeBegin,
        long beforeEnd,
        int beforeLinks,
        long beforeTime,
        long afterBegin,
        long afterEnd,
        int afterLinks,
        long afterTime,
        byte[] outcome)
    {
        _nodeId = nodeId;
        _xtpTransactionId = xtpTransactionId;
        _rowAddress = rowAddress;
        _tableAddress = tableAddress;
        _beforeBegin = beforeBegin;
        _beforeEnd = beforeEnd;
        _beforeLinks = beforeLinks;
        _beforeTime = beforeTime;
        _afterBegin = afterBegin;
        _afterEnd = afterEnd;
        _afterLinks = afterLinks;
        _afterTime = afterTime;
        _outcome = outcome;
    }

    public short NodeId => _nodeId;
    public long XtpTransactionId => _xtpTransactionId;
    public byte[] RowAddress => _rowAddress;
    public byte[] TableAddress => _tableAddress;
    public long BeforeBegin => _beforeBegin;
    public long BeforeEnd => _beforeEnd;
    public int BeforeLinks => _beforeLinks;
    public long BeforeTime => _beforeTime;
    public long AfterBegin => _afterBegin;
    public long AfterEnd => _afterEnd;
    public int AfterLinks => _afterLinks;
    public long AfterTime => _afterTime;
    public byte[] Outcome => _outcome;
}
