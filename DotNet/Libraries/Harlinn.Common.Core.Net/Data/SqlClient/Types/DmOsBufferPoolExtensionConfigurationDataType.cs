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

public class DmOsBufferPoolExtensionConfigurationDataType
{
    readonly string? _path;
    readonly int? _fileId;
    readonly int? _state;
    readonly string _stateDescription = string.Empty;
    readonly long? _currentSizeInKb;

    public DmOsBufferPoolExtensionConfigurationDataType( )
    {
    }

    public DmOsBufferPoolExtensionConfigurationDataType(string? path,
        int? fileId,
        int? state,
        string stateDescription,
        long? currentSizeInKb)
    {
        _path = path;
        _fileId = fileId;
        _state = state;
        _stateDescription = stateDescription;
        _currentSizeInKb = currentSizeInKb;
    }

    public string? Path => _path;
    public int? FileId => _fileId;
    public int? State => _state;
    public string StateDescription => _stateDescription;
    public long? CurrentSizeInKb => _currentSizeInKb;
}
