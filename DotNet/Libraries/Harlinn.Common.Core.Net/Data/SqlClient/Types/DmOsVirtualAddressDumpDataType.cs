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

public class DmOsVirtualAddressDumpDataType
{
    readonly byte[] _regionBaseAddress = Array.Empty<byte>();
    readonly byte[] _regionAllocationBaseAddress = Array.Empty<byte>();
    readonly byte[] _regionAllocationProtection = Array.Empty<byte>();
    readonly long _regionSizeInBytes = 0;
    readonly byte[] _regionState = Array.Empty<byte>();
    readonly byte[] _regionCurrentProtection = Array.Empty<byte>();
    readonly byte[] _regionType = Array.Empty<byte>();

    public DmOsVirtualAddressDumpDataType( )
    {
    }

    public DmOsVirtualAddressDumpDataType(byte[] regionBaseAddress,
        byte[] regionAllocationBaseAddress,
        byte[] regionAllocationProtection,
        long regionSizeInBytes,
        byte[] regionState,
        byte[] regionCurrentProtection,
        byte[] regionType)
    {
        _regionBaseAddress = regionBaseAddress;
        _regionAllocationBaseAddress = regionAllocationBaseAddress;
        _regionAllocationProtection = regionAllocationProtection;
        _regionSizeInBytes = regionSizeInBytes;
        _regionState = regionState;
        _regionCurrentProtection = regionCurrentProtection;
        _regionType = regionType;
    }

    public byte[] RegionBaseAddress => _regionBaseAddress;
    public byte[] RegionAllocationBaseAddress => _regionAllocationBaseAddress;
    public byte[] RegionAllocationProtection => _regionAllocationProtection;
    public long RegionSizeInBytes => _regionSizeInBytes;
    public byte[] RegionState => _regionState;
    public byte[] RegionCurrentProtection => _regionCurrentProtection;
    public byte[] RegionType => _regionType;
}
