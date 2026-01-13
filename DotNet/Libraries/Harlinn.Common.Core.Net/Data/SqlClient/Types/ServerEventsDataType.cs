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

public class ServerEventsDataType
{
    readonly int _objectId = 0;
    readonly int _type = 0;
    readonly string _typeDesc = string.Empty;
    readonly bool? _isTriggerEvent;
    readonly int? _eventGroupType;
    readonly string? _eventGroupTypeDesc;

    public ServerEventsDataType( )
    {
    }

    public ServerEventsDataType(int objectId,
        int type,
        string typeDesc,
        bool? isTriggerEvent,
        int? eventGroupType,
        string? eventGroupTypeDesc)
    {
        _objectId = objectId;
        _type = type;
        _typeDesc = typeDesc;
        _isTriggerEvent = isTriggerEvent;
        _eventGroupType = eventGroupType;
        _eventGroupTypeDesc = eventGroupTypeDesc;
    }

    public int ObjectId => _objectId;
    public int Type => _type;
    public string TypeDesc => _typeDesc;
    public bool? IsTriggerEvent => _isTriggerEvent;
    public int? EventGroupType => _eventGroupType;
    public string? EventGroupTypeDesc => _eventGroupTypeDesc;
}
