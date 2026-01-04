using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.HumanResources.Types;

public class JobcandidateDataType
{
    int _jobcandidateid = 0;
    int? _businessentityid;
    SqlXml? _resume;
    DateTime _modifieddate;

    public JobcandidateDataType( )
    {
    }

    public JobcandidateDataType(int jobcandidateid,
        int? businessentityid,
        SqlXml? resume,
        DateTime modifieddate)
    {
        _jobcandidateid = jobcandidateid;
        _businessentityid = businessentityid;
        _resume = resume;
        _modifieddate = modifieddate;
    }

    public int Jobcandidateid
    {
        get => _jobcandidateid;
        set => _jobcandidateid = value;
    }
    public int? Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public SqlXml? Resume
    {
        get => _resume;
        set => _resume = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
