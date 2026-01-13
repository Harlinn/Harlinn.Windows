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

public class AssemblyModulesDataType
{
    readonly int _objectId = 0;
    readonly int _assemblyId = 0;
    readonly string? _assemblyClass;
    readonly string? _assemblyMethod;
    readonly bool? _nullOnNullInput;
    readonly int? _executeAsPrincipalId;

    public AssemblyModulesDataType( )
    {
    }

    public AssemblyModulesDataType(int objectId,
        int assemblyId,
        string? assemblyClass,
        string? assemblyMethod,
        bool? nullOnNullInput,
        int? executeAsPrincipalId)
    {
        _objectId = objectId;
        _assemblyId = assemblyId;
        _assemblyClass = assemblyClass;
        _assemblyMethod = assemblyMethod;
        _nullOnNullInput = nullOnNullInput;
        _executeAsPrincipalId = executeAsPrincipalId;
    }

    public int ObjectId => _objectId;
    public int AssemblyId => _assemblyId;
    public string? AssemblyClass => _assemblyClass;
    public string? AssemblyMethod => _assemblyMethod;
    public bool? NullOnNullInput => _nullOnNullInput;
    public int? ExecuteAsPrincipalId => _executeAsPrincipalId;
}
