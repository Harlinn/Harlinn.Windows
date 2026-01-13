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

public class EventNotificationsDataType
{
    readonly string _name = string.Empty;
    readonly int _objectId = 0;
    readonly byte _parentClass = 0;
    readonly string? _parentClassDesc;
    readonly int _parentId = 0;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;
    readonly string? _serviceName;
    readonly string? _brokerInstance;
    readonly byte[]? _creatorSid;
    readonly int? _principalId;

    public EventNotificationsDataType( )
    {
    }

    public EventNotificationsDataType(string name,
        int objectId,
        byte parentClass,
        string? parentClassDesc,
        int parentId,
        DateTime createDate,
        DateTime modifyDate,
        string? serviceName,
        string? brokerInstance,
        byte[]? creatorSid,
        int? principalId)
    {
        _name = name;
        _objectId = objectId;
        _parentClass = parentClass;
        _parentClassDesc = parentClassDesc;
        _parentId = parentId;
        _createDate = createDate;
        _modifyDate = modifyDate;
        _serviceName = serviceName;
        _brokerInstance = brokerInstance;
        _creatorSid = creatorSid;
        _principalId = principalId;
    }

    public string Name => _name;
    public int ObjectId => _objectId;
    public byte ParentClass => _parentClass;
    public string? ParentClassDesc => _parentClassDesc;
    public int ParentId => _parentId;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
    public string? ServiceName => _serviceName;
    public string? BrokerInstance => _brokerInstance;
    public byte[]? CreatorSid => _creatorSid;
    public int? PrincipalId => _principalId;
}
