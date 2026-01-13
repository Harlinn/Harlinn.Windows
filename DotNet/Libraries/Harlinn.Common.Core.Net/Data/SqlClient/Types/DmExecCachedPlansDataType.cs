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

public class DmExecCachedPlansDataType
{
    readonly int _bucketid = 0;
    readonly int _refcounts = 0;
    readonly int _usecounts = 0;
    readonly int _sizeInBytes = 0;
    readonly byte[] _memoryObjectAddress = Array.Empty<byte>();
    readonly string _cacheobjtype = string.Empty;
    readonly string _objtype = string.Empty;
    readonly byte[] _planHandle = Array.Empty<byte>();
    readonly int _poolId = 0;
    readonly byte[]? _parentPlanHandle;

    public DmExecCachedPlansDataType( )
    {
    }

    public DmExecCachedPlansDataType(int bucketid,
        int refcounts,
        int usecounts,
        int sizeInBytes,
        byte[] memoryObjectAddress,
        string cacheobjtype,
        string objtype,
        byte[] planHandle,
        int poolId,
        byte[]? parentPlanHandle)
    {
        _bucketid = bucketid;
        _refcounts = refcounts;
        _usecounts = usecounts;
        _sizeInBytes = sizeInBytes;
        _memoryObjectAddress = memoryObjectAddress;
        _cacheobjtype = cacheobjtype;
        _objtype = objtype;
        _planHandle = planHandle;
        _poolId = poolId;
        _parentPlanHandle = parentPlanHandle;
    }

    public int Bucketid => _bucketid;
    public int Refcounts => _refcounts;
    public int Usecounts => _usecounts;
    public int SizeInBytes => _sizeInBytes;
    public byte[] MemoryObjectAddress => _memoryObjectAddress;
    public string Cacheobjtype => _cacheobjtype;
    public string Objtype => _objtype;
    public byte[] PlanHandle => _planHandle;
    public int PoolId => _poolId;
    public byte[]? ParentPlanHandle => _parentPlanHandle;
}
