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

public class DmDbExternalLanguageStatsDataType
{
    readonly int _externalLanguageId = 0;
    readonly bool _isInstalled = false;

    public DmDbExternalLanguageStatsDataType( )
    {
    }

    public DmDbExternalLanguageStatsDataType(int externalLanguageId,
        bool isInstalled)
    {
        _externalLanguageId = externalLanguageId;
        _isInstalled = isInstalled;
    }

    public int ExternalLanguageId => _externalLanguageId;
    public bool IsInstalled => _isInstalled;
}
