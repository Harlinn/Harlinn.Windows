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

public class DmHadrDbThreadsDataType
{
    readonly Guid _groupId;
    readonly Guid _agDbId;
    readonly string _name = string.Empty;
    readonly int? _numCaptureThreads;
    readonly int? _numRedoThreads;
    readonly int? _numParallelRedoThreads;

    public DmHadrDbThreadsDataType( )
    {
    }

    public DmHadrDbThreadsDataType(Guid groupId,
        Guid agDbId,
        string name,
        int? numCaptureThreads,
        int? numRedoThreads,
        int? numParallelRedoThreads)
    {
        _groupId = groupId;
        _agDbId = agDbId;
        _name = name;
        _numCaptureThreads = numCaptureThreads;
        _numRedoThreads = numRedoThreads;
        _numParallelRedoThreads = numParallelRedoThreads;
    }

    public Guid GroupId => _groupId;
    public Guid AgDbId => _agDbId;
    public string Name => _name;
    public int? NumCaptureThreads => _numCaptureThreads;
    public int? NumRedoThreads => _numRedoThreads;
    public int? NumParallelRedoThreads => _numParallelRedoThreads;
}
