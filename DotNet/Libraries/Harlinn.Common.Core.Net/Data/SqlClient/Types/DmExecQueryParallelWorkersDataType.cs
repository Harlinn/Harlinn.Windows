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

public class DmExecQueryParallelWorkersDataType
{
    readonly int _nodeId = 0;
    readonly int _schedulerCount = 0;
    readonly int _maxWorkerCount = 0;
    readonly int _reservedWorkerCount = 0;
    readonly int _freeWorkerCount = 0;
    readonly int _usedWorkerCount = 0;

    public DmExecQueryParallelWorkersDataType( )
    {
    }

    public DmExecQueryParallelWorkersDataType(int nodeId,
        int schedulerCount,
        int maxWorkerCount,
        int reservedWorkerCount,
        int freeWorkerCount,
        int usedWorkerCount)
    {
        _nodeId = nodeId;
        _schedulerCount = schedulerCount;
        _maxWorkerCount = maxWorkerCount;
        _reservedWorkerCount = reservedWorkerCount;
        _freeWorkerCount = freeWorkerCount;
        _usedWorkerCount = usedWorkerCount;
    }

    public int NodeId => _nodeId;
    public int SchedulerCount => _schedulerCount;
    public int MaxWorkerCount => _maxWorkerCount;
    public int ReservedWorkerCount => _reservedWorkerCount;
    public int FreeWorkerCount => _freeWorkerCount;
    public int UsedWorkerCount => _usedWorkerCount;
}
