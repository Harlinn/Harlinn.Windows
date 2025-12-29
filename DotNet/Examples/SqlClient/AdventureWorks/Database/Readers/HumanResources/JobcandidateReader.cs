using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.HumanResources;

public class JobcandidateReader : IDisposable
{
    public const string QualifiedTableName = "[HumanResources].[JobCandidate]";
    public const string TableName = "JobCandidate";
    public const string ShortName = "j";
    public const string Sql = """
        SELECT
          j.[Jobcandidateid],
          j.[Businessentityid],
          j.[Resume],
          j.[Modifieddate]
        FROM
          [HumanResources].[JobCandidate] j
        """;

    public const int JOBCANDIDATEID_FIELD_ID = 0;
    public const int BUSINESSENTITYID_FIELD_ID = 1;
    public const int RESUME_FIELD_ID = 2;
    public const int MODIFIEDDATE_FIELD_ID = 3;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public JobcandidateReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Jobcandidateid
    {
        get
        {
            return Reader.GetInt32(JOBCANDIDATEID_FIELD_ID);
        }
    }

    public int? Businessentityid
    {
        get
        {
            return Reader.GetNullableInt32(BUSINESSENTITYID_FIELD_ID);
        }
    }

    public SqlXml? Resume
    {
        get
        {
            return Reader.GetNullableSqlXml(RESUME_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.HumanResources.JobcandidateDataType ToDataObject()
    {
        return new Types.HumanResources.JobcandidateDataType(Jobcandidateid,
            Businessentityid,
            Resume,
            Modifieddate);
    }

    public List<Types.HumanResources.JobcandidateDataType> ToList()
    {
        var list = new List<Types.HumanResources.JobcandidateDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
