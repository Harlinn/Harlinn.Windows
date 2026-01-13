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

public class SqlFeatureRestrictionsDataType
{
    readonly string _class = string.Empty;
    readonly string? _object;
    readonly string _feature = string.Empty;

    public SqlFeatureRestrictionsDataType( )
    {
    }

    public SqlFeatureRestrictionsDataType(string class__,
        string? object__,
        string feature)
    {
        _class = class__;
        _object = object__;
        _feature = feature;
    }

    public string Class => _class;
    public string? Object => _object;
    public string Feature => _feature;
}
