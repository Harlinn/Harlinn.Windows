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

public class ServerEventSessionTargetsDataType
{
    readonly int _eventSessionId = 0;
    readonly int _targetId = 0;
    readonly string? _name;
    readonly string? _package;
    readonly string? _module;

    public ServerEventSessionTargetsDataType( )
    {
    }

    public ServerEventSessionTargetsDataType(int eventSessionId,
        int targetId,
        string? name,
        string? package,
        string? module)
    {
        _eventSessionId = eventSessionId;
        _targetId = targetId;
        _name = name;
        _package = package;
        _module = module;
    }

    public int EventSessionId => _eventSessionId;
    public int TargetId => _targetId;
    public string? Name => _name;
    public string? Package => _package;
    public string? Module => _module;
}
