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

public class DmQnSubscriptionsDataType
{
    readonly int _id = 0;
    readonly int _databaseId = 0;
    readonly byte[] _sid = Array.Empty<byte>();
    readonly int _objectId = 0;
    readonly DateTime _created;
    readonly int _timeout = 0;
    readonly int _status = 0;

    public DmQnSubscriptionsDataType( )
    {
    }

    public DmQnSubscriptionsDataType(int id,
        int databaseId,
        byte[] sid,
        int objectId,
        DateTime created,
        int timeout,
        int status)
    {
        _id = id;
        _databaseId = databaseId;
        _sid = sid;
        _objectId = objectId;
        _created = created;
        _timeout = timeout;
        _status = status;
    }

    public int Id => _id;
    public int DatabaseId => _databaseId;
    public byte[] Sid => _sid;
    public int ObjectId => _objectId;
    public DateTime Created => _created;
    public int Timeout => _timeout;
    public int Status => _status;
}
