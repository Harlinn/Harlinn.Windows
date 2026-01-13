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

public class SystemInternalsAllocationUnitsDataType
{
    readonly long _allocationUnitId = 0;
    readonly byte _type = 0;
    readonly string? _typeDesc;
    readonly long _containerId = 0;
    readonly short _filegroupId = 0;
    readonly long _totalPages = 0;
    readonly long _usedPages = 0;
    readonly long _dataPages = 0;
    readonly byte[] _firstPage = Array.Empty<byte>();
    readonly byte[] _rootPage = Array.Empty<byte>();
    readonly byte[] _firstIamPage = Array.Empty<byte>();

    public SystemInternalsAllocationUnitsDataType( )
    {
    }

    public SystemInternalsAllocationUnitsDataType(long allocationUnitId,
        byte type,
        string? typeDesc,
        long containerId,
        short filegroupId,
        long totalPages,
        long usedPages,
        long dataPages,
        byte[] firstPage,
        byte[] rootPage,
        byte[] firstIamPage)
    {
        _allocationUnitId = allocationUnitId;
        _type = type;
        _typeDesc = typeDesc;
        _containerId = containerId;
        _filegroupId = filegroupId;
        _totalPages = totalPages;
        _usedPages = usedPages;
        _dataPages = dataPages;
        _firstPage = firstPage;
        _rootPage = rootPage;
        _firstIamPage = firstIamPage;
    }

    public long AllocationUnitId => _allocationUnitId;
    public byte Type => _type;
    public string? TypeDesc => _typeDesc;
    public long ContainerId => _containerId;
    public short FilegroupId => _filegroupId;
    public long TotalPages => _totalPages;
    public long UsedPages => _usedPages;
    public long DataPages => _dataPages;
    public byte[] FirstPage => _firstPage;
    public byte[] RootPage => _rootPage;
    public byte[] FirstIamPage => _firstIamPage;
}
