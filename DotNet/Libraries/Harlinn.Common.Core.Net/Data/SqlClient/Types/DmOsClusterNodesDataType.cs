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

public class DmOsClusterNodesDataType
{
    readonly string? _nodename;
    readonly int? _status;
    readonly string _statusDescription = string.Empty;
    readonly bool? _isCurrentOwner;

    public DmOsClusterNodesDataType( )
    {
    }

    public DmOsClusterNodesDataType(string? nodename,
        int? status,
        string statusDescription,
        bool? isCurrentOwner)
    {
        _nodename = nodename;
        _status = status;
        _statusDescription = statusDescription;
        _isCurrentOwner = isCurrentOwner;
    }

    public string? Nodename => _nodename;
    public int? Status => _status;
    public string StatusDescription => _statusDescription;
    public bool? IsCurrentOwner => _isCurrentOwner;
}
