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

public class DmDbScriptLevelDataType
{
    readonly int _databaseId = 0;
    readonly int _scriptId = 0;
    readonly string? _scriptName;
    readonly int _version = 0;
    readonly int _scriptLevel = 0;
    readonly int _downgradeStartLevel = 0;
    readonly int _downgradeTargetLevel = 0;
    readonly int? _upgradeStartLevel;
    readonly int? _upgradeTargetLevel;

    public DmDbScriptLevelDataType( )
    {
    }

    public DmDbScriptLevelDataType(int databaseId,
        int scriptId,
        string? scriptName,
        int version,
        int scriptLevel,
        int downgradeStartLevel,
        int downgradeTargetLevel,
        int? upgradeStartLevel,
        int? upgradeTargetLevel)
    {
        _databaseId = databaseId;
        _scriptId = scriptId;
        _scriptName = scriptName;
        _version = version;
        _scriptLevel = scriptLevel;
        _downgradeStartLevel = downgradeStartLevel;
        _downgradeTargetLevel = downgradeTargetLevel;
        _upgradeStartLevel = upgradeStartLevel;
        _upgradeTargetLevel = upgradeTargetLevel;
    }

    public int DatabaseId => _databaseId;
    public int ScriptId => _scriptId;
    public string? ScriptName => _scriptName;
    public int Version => _version;
    public int ScriptLevel => _scriptLevel;
    public int DowngradeStartLevel => _downgradeStartLevel;
    public int DowngradeTargetLevel => _downgradeTargetLevel;
    public int? UpgradeStartLevel => _upgradeStartLevel;
    public int? UpgradeTargetLevel => _upgradeTargetLevel;
}
