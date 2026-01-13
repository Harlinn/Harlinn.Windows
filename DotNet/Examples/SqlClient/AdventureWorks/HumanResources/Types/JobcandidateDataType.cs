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
