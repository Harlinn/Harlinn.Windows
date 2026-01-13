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

public class EmployeeDataType
{
    int _businessentityid = 0;
    string _nationalidnumber = string.Empty;
    string _loginid = string.Empty;
    SqlHierarchyId? _organizationnode;
    short? _organizationlevel;
    string _jobtitle = string.Empty;
    DateTime _birthdate;
    string _maritalstatus = string.Empty;
    string _gender = string.Empty;
    DateTime _hiredate;
    bool _salariedflag = false;
    short _vacationhours = 0;
    short _sickleavehours = 0;
    bool _currentflag = false;
    Guid _rowguid;
    DateTime _modifieddate;

    public EmployeeDataType( )
    {
    }

    public EmployeeDataType(int businessentityid,
        string nationalidnumber,
        string loginid,
        SqlHierarchyId? organizationnode,
        short? organizationlevel,
        string jobtitle,
        DateTime birthdate,
        string maritalstatus,
        string gender,
        DateTime hiredate,
        bool salariedflag,
        short vacationhours,
        short sickleavehours,
        bool currentflag,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _nationalidnumber = nationalidnumber;
        _loginid = loginid;
        _organizationnode = organizationnode;
        _organizationlevel = organizationlevel;
        _jobtitle = jobtitle;
        _birthdate = birthdate;
        _maritalstatus = maritalstatus;
        _gender = gender;
        _hiredate = hiredate;
        _salariedflag = salariedflag;
        _vacationhours = vacationhours;
        _sickleavehours = sickleavehours;
        _currentflag = currentflag;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public string Nationalidnumber
    {
        get => _nationalidnumber;
        set => _nationalidnumber = value;
    }
    public string Loginid
    {
        get => _loginid;
        set => _loginid = value;
    }
    public SqlHierarchyId? Organizationnode
    {
        get => _organizationnode;
        set => _organizationnode = value;
    }
    public short? Organizationlevel
    {
        get => _organizationlevel;
        set => _organizationlevel = value;
    }
    public string Jobtitle
    {
        get => _jobtitle;
        set => _jobtitle = value;
    }
    public DateTime Birthdate
    {
        get => _birthdate;
        set => _birthdate = value;
    }
    public string Maritalstatus
    {
        get => _maritalstatus;
        set => _maritalstatus = value;
    }
    public string Gender
    {
        get => _gender;
        set => _gender = value;
    }
    public DateTime Hiredate
    {
        get => _hiredate;
        set => _hiredate = value;
    }
    public bool Salariedflag
    {
        get => _salariedflag;
        set => _salariedflag = value;
    }
    public short Vacationhours
    {
        get => _vacationhours;
        set => _vacationhours = value;
    }
    public short Sickleavehours
    {
        get => _sickleavehours;
        set => _sickleavehours = value;
    }
    public bool Currentflag
    {
        get => _currentflag;
        set => _currentflag = value;
    }
    public Guid Rowguid
    {
        get => _rowguid;
        set => _rowguid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
