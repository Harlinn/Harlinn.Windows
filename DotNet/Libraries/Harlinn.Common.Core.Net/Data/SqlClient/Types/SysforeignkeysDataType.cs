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

public class SysforeignkeysDataType
{
    readonly int _constid = 0;
    readonly int _fkeyid = 0;
    readonly int _rkeyid = 0;
    readonly short? _fkey;
    readonly short? _rkey;
    readonly short? _keyno;

    public SysforeignkeysDataType( )
    {
    }

    public SysforeignkeysDataType(int constid,
        int fkeyid,
        int rkeyid,
        short? fkey,
        short? rkey,
        short? keyno)
    {
        _constid = constid;
        _fkeyid = fkeyid;
        _rkeyid = rkeyid;
        _fkey = fkey;
        _rkey = rkey;
        _keyno = keyno;
    }

    public int Constid => _constid;
    public int Fkeyid => _fkeyid;
    public int Rkeyid => _rkeyid;
    public short? Fkey => _fkey;
    public short? Rkey => _rkey;
    public short? Keyno => _keyno;
}
