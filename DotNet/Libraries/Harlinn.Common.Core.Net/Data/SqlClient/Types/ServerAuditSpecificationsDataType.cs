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

public class ServerAuditSpecificationsDataType
{
    readonly int _serverSpecificationId = 0;
    readonly string _name = string.Empty;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;
    readonly Guid? _auditGuid;
    readonly bool? _isStateEnabled;

    public ServerAuditSpecificationsDataType( )
    {
    }

    public ServerAuditSpecificationsDataType(int serverSpecificationId,
        string name,
        DateTime createDate,
        DateTime modifyDate,
        Guid? auditGuid,
        bool? isStateEnabled)
    {
        _serverSpecificationId = serverSpecificationId;
        _name = name;
        _createDate = createDate;
        _modifyDate = modifyDate;
        _auditGuid = auditGuid;
        _isStateEnabled = isStateEnabled;
    }

    public int ServerSpecificationId => _serverSpecificationId;
    public string Name => _name;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
    public Guid? AuditGuid => _auditGuid;
    public bool? IsStateEnabled => _isStateEnabled;
}
