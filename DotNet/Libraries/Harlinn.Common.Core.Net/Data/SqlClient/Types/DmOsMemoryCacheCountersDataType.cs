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

public class DmOsMemoryCacheCountersDataType
{
    readonly byte[] _cacheAddress = Array.Empty<byte>();
    readonly string _name = string.Empty;
    readonly string _type = string.Empty;
    readonly long _pagesKb = 0;
    readonly long? _pagesInUseKb;
    readonly long _entriesCount = 0;
    readonly long _entriesInUseCount = 0;

    public DmOsMemoryCacheCountersDataType( )
    {
    }

    public DmOsMemoryCacheCountersDataType(byte[] cacheAddress,
        string name,
        string type,
        long pagesKb,
        long? pagesInUseKb,
        long entriesCount,
        long entriesInUseCount)
    {
        _cacheAddress = cacheAddress;
        _name = name;
        _type = type;
        _pagesKb = pagesKb;
        _pagesInUseKb = pagesInUseKb;
        _entriesCount = entriesCount;
        _entriesInUseCount = entriesInUseCount;
    }

    public byte[] CacheAddress => _cacheAddress;
    public string Name => _name;
    public string Type => _type;
    public long PagesKb => _pagesKb;
    public long? PagesInUseKb => _pagesInUseKb;
    public long EntriesCount => _entriesCount;
    public long EntriesInUseCount => _entriesInUseCount;
}
