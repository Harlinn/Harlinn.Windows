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

public class DmOsServerDiagnosticsLogConfigurationsDataType
{
    readonly int? _isEnabled;
    readonly string _path = string.Empty;
    readonly int? _maxSize;
    readonly int? _maxFiles;

    public DmOsServerDiagnosticsLogConfigurationsDataType( )
    {
    }

    public DmOsServerDiagnosticsLogConfigurationsDataType(int? isEnabled,
        string path,
        int? maxSize,
        int? maxFiles)
    {
        _isEnabled = isEnabled;
        _path = path;
        _maxSize = maxSize;
        _maxFiles = maxFiles;
    }

    public int? IsEnabled => _isEnabled;
    public string Path => _path;
    public int? MaxSize => _maxSize;
    public int? MaxFiles => _maxFiles;
}
