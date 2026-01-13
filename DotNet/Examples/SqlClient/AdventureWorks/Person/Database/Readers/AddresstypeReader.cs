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
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Person.Database.Readers;

public class AddresstypeReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[AddressType]";
    public const string TableName = "AddressType";
    public const string ShortName = "a1";
    public const string Sql = """
        SELECT
          a1.[Addresstypeid],
          a1.[Name],
          a1.[Rowguid],
          a1.[Modifieddate]
        FROM
          [Person].[AddressType] a1
        """;

    public const int ADDRESSTYPEID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int ROWGUID_FIELD_ID = 2;
    public const int MODIFIEDDATE_FIELD_ID = 3;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public AddresstypeReader(SqlDataReader reader, bool ownsReader = false)
    {
        _reader = reader;
        _ownsReader = ownsReader;
    }

    public SqlDataReader Reader => _reader;

    public void Dispose()
    {
        if (_ownsReader)
        {
            ((IDisposable)_reader).Dispose();
        }
    }

    public bool Read()
    {
        return _reader.Read();
    }

    public int Addresstypeid
    {
        get
        {
            return Reader.GetInt32(ADDRESSTYPEID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public Guid Rowguid
    {
        get
        {
            return Reader.GetGuid(ROWGUID_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Person.Types.AddresstypeDataType ToDataObject()
    {
        return new AdventureWorks.Person.Types.AddresstypeDataType(Addresstypeid,
            Name,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Person.Types.AddresstypeDataType> ToList()
    {
        var list = new List<AdventureWorks.Person.Types.AddresstypeDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
