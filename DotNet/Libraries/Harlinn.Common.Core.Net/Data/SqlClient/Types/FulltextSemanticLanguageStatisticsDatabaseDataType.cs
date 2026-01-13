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

public class FulltextSemanticLanguageStatisticsDatabaseDataType
{
    readonly int _databaseId = 0;
    readonly DateTime _registerDate;
    readonly int _registeredBy = 0;
    readonly string _version = string.Empty;

    public FulltextSemanticLanguageStatisticsDatabaseDataType( )
    {
    }

    public FulltextSemanticLanguageStatisticsDatabaseDataType(int databaseId,
        DateTime registerDate,
        int registeredBy,
        string version)
    {
        _databaseId = databaseId;
        _registerDate = registerDate;
        _registeredBy = registeredBy;
        _version = version;
    }

    public int DatabaseId => _databaseId;
    public DateTime RegisterDate => _registerDate;
    public int RegisteredBy => _registeredBy;
    public string Version => _version;
}
