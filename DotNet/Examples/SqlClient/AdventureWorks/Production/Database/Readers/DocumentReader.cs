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

namespace AdventureWorks.Production.Database.Readers;

public class DocumentReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[Document]";
    public const string TableName = "Document";
    public const string ShortName = "d1";
    public const string Sql = """
        SELECT
          d1.[Documentnode],
          d1.[Documentlevel],
          d1.[Title],
          d1.[Owner],
          d1.[Folderflag],
          d1.[Filename],
          d1.[Fileextension],
          d1.[Revision],
          d1.[Changenumber],
          d1.[Status],
          d1.[Documentsummary],
          d1.[Document],
          d1.[Rowguid],
          d1.[Modifieddate]
        FROM
          [Production].[Document] d1
        """;

    public const int DOCUMENTNODE_FIELD_ID = 0;
    public const int DOCUMENTLEVEL_FIELD_ID = 1;
    public const int TITLE_FIELD_ID = 2;
    public const int OWNER_FIELD_ID = 3;
    public const int FOLDERFLAG_FIELD_ID = 4;
    public const int FILENAME_FIELD_ID = 5;
    public const int FILEEXTENSION_FIELD_ID = 6;
    public const int REVISION_FIELD_ID = 7;
    public const int CHANGENUMBER_FIELD_ID = 8;
    public const int STATUS_FIELD_ID = 9;
    public const int DOCUMENTSUMMARY_FIELD_ID = 10;
    public const int DOCUMENT_FIELD_ID = 11;
    public const int ROWGUID_FIELD_ID = 12;
    public const int MODIFIEDDATE_FIELD_ID = 13;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public DocumentReader(SqlDataReader reader, bool ownsReader = false)
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

    public SqlHierarchyId Documentnode
    {
        get
        {
            return Reader.GetSqlHierarchyId(DOCUMENTNODE_FIELD_ID);
        }
    }

    public short? Documentlevel
    {
        get
        {
            return Reader.GetNullableInt16(DOCUMENTLEVEL_FIELD_ID);
        }
    }

    public string Title
    {
        get
        {
            return Reader.GetString(TITLE_FIELD_ID);
        }
    }

    public int Owner
    {
        get
        {
            return Reader.GetInt32(OWNER_FIELD_ID);
        }
    }

    public bool Folderflag
    {
        get
        {
            return Reader.GetBoolean(FOLDERFLAG_FIELD_ID);
        }
    }

    public string Filename
    {
        get
        {
            return Reader.GetString(FILENAME_FIELD_ID);
        }
    }

    public string Fileextension
    {
        get
        {
            return Reader.GetString(FILEEXTENSION_FIELD_ID);
        }
    }

    public string Revision
    {
        get
        {
            return Reader.GetString(REVISION_FIELD_ID);
        }
    }

    public int Changenumber
    {
        get
        {
            return Reader.GetInt32(CHANGENUMBER_FIELD_ID);
        }
    }

    public byte Status
    {
        get
        {
            return Reader.GetByte(STATUS_FIELD_ID);
        }
    }

    public string? Documentsummary
    {
        get
        {
            return Reader.GetNullableString(DOCUMENTSUMMARY_FIELD_ID);
        }
    }

    public byte[]? Document
    {
        get
        {
            return Reader.GetNullableBinary(DOCUMENT_FIELD_ID);
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


    public AdventureWorks.Production.Types.DocumentDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.DocumentDataType(Documentnode,
            Documentlevel,
            Title,
            Owner,
            Folderflag,
            Filename,
            Fileextension,
            Revision,
            Changenumber,
            Status,
            Documentsummary,
            Document,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.DocumentDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.DocumentDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
