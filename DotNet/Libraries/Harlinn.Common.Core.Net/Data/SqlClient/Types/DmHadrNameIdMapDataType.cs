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

public class DmHadrNameIdMapDataType
{
    readonly string _agName = string.Empty;
    readonly Guid _agId;
    readonly string _agResourceId = string.Empty;
    readonly string _agGroupId = string.Empty;

    public DmHadrNameIdMapDataType( )
    {
    }

    public DmHadrNameIdMapDataType(string agName,
        Guid agId,
        string agResourceId,
        string agGroupId)
    {
        _agName = agName;
        _agId = agId;
        _agResourceId = agResourceId;
        _agGroupId = agGroupId;
    }

    public string AgName => _agName;
    public Guid AgId => _agId;
    public string AgResourceId => _agResourceId;
    public string AgGroupId => _agGroupId;
}
