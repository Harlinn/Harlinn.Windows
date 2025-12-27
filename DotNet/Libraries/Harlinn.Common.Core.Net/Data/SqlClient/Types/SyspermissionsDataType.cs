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

public class SyspermissionsDataType
{
    readonly int _id = 0;
    readonly short? _grantee;
    readonly short? _grantor;
    readonly short? _actadd;
    readonly short? _actmod;
    readonly byte[]? _seladd;
    readonly byte[]? _selmod;
    readonly byte[]? _updadd;
    readonly byte[]? _updmod;
    readonly byte[]? _refadd;
    readonly byte[]? _refmod;

    public SyspermissionsDataType( )
    {
    }

    public SyspermissionsDataType(int id,
        short? grantee,
        short? grantor,
        short? actadd,
        short? actmod,
        byte[]? seladd,
        byte[]? selmod,
        byte[]? updadd,
        byte[]? updmod,
        byte[]? refadd,
        byte[]? refmod)
    {
        _id = id;
        _grantee = grantee;
        _grantor = grantor;
        _actadd = actadd;
        _actmod = actmod;
        _seladd = seladd;
        _selmod = selmod;
        _updadd = updadd;
        _updmod = updmod;
        _refadd = refadd;
        _refmod = refmod;
    }

    public int Id => _id;
    public short? Grantee => _grantee;
    public short? Grantor => _grantor;
    public short? Actadd => _actadd;
    public short? Actmod => _actmod;
    public byte[]? Seladd => _seladd;
    public byte[]? Selmod => _selmod;
    public byte[]? Updadd => _updadd;
    public byte[]? Updmod => _updmod;
    public byte[]? Refadd => _refadd;
    public byte[]? Refmod => _refmod;
}
