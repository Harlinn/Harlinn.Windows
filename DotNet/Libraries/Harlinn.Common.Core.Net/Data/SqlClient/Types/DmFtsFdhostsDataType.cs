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

public class DmFtsFdhostsDataType
{
    readonly int _fdhostId = 0;
    readonly string? _fdhostName;
    readonly int _fdhostProcessId = 0;
    readonly string? _fdhostType;
    readonly int _maxThread = 0;
    readonly int _batchCount = 0;

    public DmFtsFdhostsDataType( )
    {
    }

    public DmFtsFdhostsDataType(int fdhostId,
        string? fdhostName,
        int fdhostProcessId,
        string? fdhostType,
        int maxThread,
        int batchCount)
    {
        _fdhostId = fdhostId;
        _fdhostName = fdhostName;
        _fdhostProcessId = fdhostProcessId;
        _fdhostType = fdhostType;
        _maxThread = maxThread;
        _batchCount = batchCount;
    }

    public int FdhostId => _fdhostId;
    public string? FdhostName => _fdhostName;
    public int FdhostProcessId => _fdhostProcessId;
    public string? FdhostType => _fdhostType;
    public int MaxThread => _maxThread;
    public int BatchCount => _batchCount;
}
