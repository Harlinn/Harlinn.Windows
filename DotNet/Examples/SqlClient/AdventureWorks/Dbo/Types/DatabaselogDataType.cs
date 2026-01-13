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
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Dbo.Types;

public class DatabaselogDataType
{
    int _databaselogid = 0;
    DateTime _posttime;
    string _databaseuser = string.Empty;
    string _event = string.Empty;
    string? _schema;
    string? _object;
    string _tsql = string.Empty;
    SqlXml _xmlevent;

    public DatabaselogDataType( )
    {
    }

    public DatabaselogDataType(int databaselogid,
        DateTime posttime,
        string databaseuser,
        string event__,
        string? schema,
        string? object__,
        string tsql,
        SqlXml xmlevent)
    {
        _databaselogid = databaselogid;
        _posttime = posttime;
        _databaseuser = databaseuser;
        _event = event__;
        _schema = schema;
        _object = object__;
        _tsql = tsql;
        _xmlevent = xmlevent;
    }

    public int Databaselogid
    {
        get => _databaselogid;
        set => _databaselogid = value;
    }
    public DateTime Posttime
    {
        get => _posttime;
        set => _posttime = value;
    }
    public string Databaseuser
    {
        get => _databaseuser;
        set => _databaseuser = value;
    }
    public string Event
    {
        get => _event;
        set => _event = value;
    }
    public string? Schema
    {
        get => _schema;
        set => _schema = value;
    }
    public string? Object
    {
        get => _object;
        set => _object = value;
    }
    public string Tsql
    {
        get => _tsql;
        set => _tsql = value;
    }
    public SqlXml Xmlevent
    {
        get => _xmlevent;
        set => _xmlevent = value;
    }
}
