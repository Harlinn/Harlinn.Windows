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

public class SysreferencesDataType
{
    readonly int _constid = 0;
    readonly int _fkeyid = 0;
    readonly int? _rkeyid;
    readonly short? _rkeyindid;
    readonly short? _keycnt;
    readonly byte[]? _forkeys;
    readonly byte[]? _refkeys;
    readonly short? _fkeydbid;
    readonly short? _rkeydbid;
    readonly short? _fkey1;
    readonly short? _fkey2;
    readonly short? _fkey3;
    readonly short? _fkey4;
    readonly short? _fkey5;
    readonly short? _fkey6;
    readonly short? _fkey7;
    readonly short? _fkey8;
    readonly short? _fkey9;
    readonly short? _fkey10;
    readonly short? _fkey11;
    readonly short? _fkey12;
    readonly short? _fkey13;
    readonly short? _fkey14;
    readonly short? _fkey15;
    readonly short? _fkey16;
    readonly short? _rkey1;
    readonly short? _rkey2;
    readonly short? _rkey3;
    readonly short? _rkey4;
    readonly short? _rkey5;
    readonly short? _rkey6;
    readonly short? _rkey7;
    readonly short? _rkey8;
    readonly short? _rkey9;
    readonly short? _rkey10;
    readonly short? _rkey11;
    readonly short? _rkey12;
    readonly short? _rkey13;
    readonly short? _rkey14;
    readonly short? _rkey15;
    readonly short? _rkey16;

    public SysreferencesDataType( )
    {
    }

    public SysreferencesDataType(int constid,
        int fkeyid,
        int? rkeyid,
        short? rkeyindid,
        short? keycnt,
        byte[]? forkeys,
        byte[]? refkeys,
        short? fkeydbid,
        short? rkeydbid,
        short? fkey1,
        short? fkey2,
        short? fkey3,
        short? fkey4,
        short? fkey5,
        short? fkey6,
        short? fkey7,
        short? fkey8,
        short? fkey9,
        short? fkey10,
        short? fkey11,
        short? fkey12,
        short? fkey13,
        short? fkey14,
        short? fkey15,
        short? fkey16,
        short? rkey1,
        short? rkey2,
        short? rkey3,
        short? rkey4,
        short? rkey5,
        short? rkey6,
        short? rkey7,
        short? rkey8,
        short? rkey9,
        short? rkey10,
        short? rkey11,
        short? rkey12,
        short? rkey13,
        short? rkey14,
        short? rkey15,
        short? rkey16)
    {
        _constid = constid;
        _fkeyid = fkeyid;
        _rkeyid = rkeyid;
        _rkeyindid = rkeyindid;
        _keycnt = keycnt;
        _forkeys = forkeys;
        _refkeys = refkeys;
        _fkeydbid = fkeydbid;
        _rkeydbid = rkeydbid;
        _fkey1 = fkey1;
        _fkey2 = fkey2;
        _fkey3 = fkey3;
        _fkey4 = fkey4;
        _fkey5 = fkey5;
        _fkey6 = fkey6;
        _fkey7 = fkey7;
        _fkey8 = fkey8;
        _fkey9 = fkey9;
        _fkey10 = fkey10;
        _fkey11 = fkey11;
        _fkey12 = fkey12;
        _fkey13 = fkey13;
        _fkey14 = fkey14;
        _fkey15 = fkey15;
        _fkey16 = fkey16;
        _rkey1 = rkey1;
        _rkey2 = rkey2;
        _rkey3 = rkey3;
        _rkey4 = rkey4;
        _rkey5 = rkey5;
        _rkey6 = rkey6;
        _rkey7 = rkey7;
        _rkey8 = rkey8;
        _rkey9 = rkey9;
        _rkey10 = rkey10;
        _rkey11 = rkey11;
        _rkey12 = rkey12;
        _rkey13 = rkey13;
        _rkey14 = rkey14;
        _rkey15 = rkey15;
        _rkey16 = rkey16;
    }

    public int Constid => _constid;
    public int Fkeyid => _fkeyid;
    public int? Rkeyid => _rkeyid;
    public short? Rkeyindid => _rkeyindid;
    public short? Keycnt => _keycnt;
    public byte[]? Forkeys => _forkeys;
    public byte[]? Refkeys => _refkeys;
    public short? Fkeydbid => _fkeydbid;
    public short? Rkeydbid => _rkeydbid;
    public short? Fkey1 => _fkey1;
    public short? Fkey2 => _fkey2;
    public short? Fkey3 => _fkey3;
    public short? Fkey4 => _fkey4;
    public short? Fkey5 => _fkey5;
    public short? Fkey6 => _fkey6;
    public short? Fkey7 => _fkey7;
    public short? Fkey8 => _fkey8;
    public short? Fkey9 => _fkey9;
    public short? Fkey10 => _fkey10;
    public short? Fkey11 => _fkey11;
    public short? Fkey12 => _fkey12;
    public short? Fkey13 => _fkey13;
    public short? Fkey14 => _fkey14;
    public short? Fkey15 => _fkey15;
    public short? Fkey16 => _fkey16;
    public short? Rkey1 => _rkey1;
    public short? Rkey2 => _rkey2;
    public short? Rkey3 => _rkey3;
    public short? Rkey4 => _rkey4;
    public short? Rkey5 => _rkey5;
    public short? Rkey6 => _rkey6;
    public short? Rkey7 => _rkey7;
    public short? Rkey8 => _rkey8;
    public short? Rkey9 => _rkey9;
    public short? Rkey10 => _rkey10;
    public short? Rkey11 => _rkey11;
    public short? Rkey12 => _rkey12;
    public short? Rkey13 => _rkey13;
    public short? Rkey14 => _rkey14;
    public short? Rkey15 => _rkey15;
    public short? Rkey16 => _rkey16;
}
