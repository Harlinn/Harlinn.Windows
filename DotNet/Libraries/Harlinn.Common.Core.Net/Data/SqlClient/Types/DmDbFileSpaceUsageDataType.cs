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

public class DmDbFileSpaceUsageDataType
{
    readonly int? _databaseId;
    readonly short? _fileId;
    readonly short? _filegroupId;
    readonly long? _totalPageCount;
    readonly long? _allocatedExtentPageCount;
    readonly long? _unallocatedExtentPageCount;
    readonly long? _versionStoreReservedPageCount;
    readonly long? _userObjectReservedPageCount;
    readonly long? _internalObjectReservedPageCount;
    readonly long? _mixedExtentPageCount;
    readonly long? _modifiedExtentPageCount;

    public DmDbFileSpaceUsageDataType( )
    {
    }

    public DmDbFileSpaceUsageDataType(int? databaseId,
        short? fileId,
        short? filegroupId,
        long? totalPageCount,
        long? allocatedExtentPageCount,
        long? unallocatedExtentPageCount,
        long? versionStoreReservedPageCount,
        long? userObjectReservedPageCount,
        long? internalObjectReservedPageCount,
        long? mixedExtentPageCount,
        long? modifiedExtentPageCount)
    {
        _databaseId = databaseId;
        _fileId = fileId;
        _filegroupId = filegroupId;
        _totalPageCount = totalPageCount;
        _allocatedExtentPageCount = allocatedExtentPageCount;
        _unallocatedExtentPageCount = unallocatedExtentPageCount;
        _versionStoreReservedPageCount = versionStoreReservedPageCount;
        _userObjectReservedPageCount = userObjectReservedPageCount;
        _internalObjectReservedPageCount = internalObjectReservedPageCount;
        _mixedExtentPageCount = mixedExtentPageCount;
        _modifiedExtentPageCount = modifiedExtentPageCount;
    }

    public int? DatabaseId => _databaseId;
    public short? FileId => _fileId;
    public short? FilegroupId => _filegroupId;
    public long? TotalPageCount => _totalPageCount;
    public long? AllocatedExtentPageCount => _allocatedExtentPageCount;
    public long? UnallocatedExtentPageCount => _unallocatedExtentPageCount;
    public long? VersionStoreReservedPageCount => _versionStoreReservedPageCount;
    public long? UserObjectReservedPageCount => _userObjectReservedPageCount;
    public long? InternalObjectReservedPageCount => _internalObjectReservedPageCount;
    public long? MixedExtentPageCount => _mixedExtentPageCount;
    public long? ModifiedExtentPageCount => _modifiedExtentPageCount;
}
