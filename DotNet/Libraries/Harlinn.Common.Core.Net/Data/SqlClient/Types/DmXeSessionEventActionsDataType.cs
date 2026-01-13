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

public class DmXeSessionEventActionsDataType
{
    readonly byte[] _eventSessionAddress = Array.Empty<byte>();
    readonly string _actionName = string.Empty;
    readonly Guid _actionPackageGuid;
    readonly string _eventName = string.Empty;
    readonly Guid _eventPackageGuid;

    public DmXeSessionEventActionsDataType( )
    {
    }

    public DmXeSessionEventActionsDataType(byte[] eventSessionAddress,
        string actionName,
        Guid actionPackageGuid,
        string eventName,
        Guid eventPackageGuid)
    {
        _eventSessionAddress = eventSessionAddress;
        _actionName = actionName;
        _actionPackageGuid = actionPackageGuid;
        _eventName = eventName;
        _eventPackageGuid = eventPackageGuid;
    }

    public byte[] EventSessionAddress => _eventSessionAddress;
    public string ActionName => _actionName;
    public Guid ActionPackageGuid => _actionPackageGuid;
    public string EventName => _eventName;
    public Guid EventPackageGuid => _eventPackageGuid;
}
