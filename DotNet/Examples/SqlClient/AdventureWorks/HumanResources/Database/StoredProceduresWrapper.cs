using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

using AdventureWorks.Dbo.Types;
using AdventureWorks.HumanResources.Types;
using AdventureWorks.Person.Types;
using AdventureWorks.Production.Types;
using AdventureWorks.Purchasing.Types;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.HumanResources.Database;

public class StoredProcedures
{
    public static bool InsertDepartment(SqlConnection sqlConnection, ref short departmentid,
        string name,
        string groupname,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[InsertDepartment]";

        var departmentidParameter = command.Parameters.AddInt16("@departmentid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@groupname", groupname, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            departmentid = (short)departmentidParameter.Value;
        }
        return result;
    }

    public static bool InsertDepartment(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.DepartmentDataType data )
    {
        var dataDepartmentid = data.Departmentid;
        var dataName = data.Name;
        var dataGroupname = data.Groupname;
        var dataModifieddate = data.Modifieddate;
        var result = InsertDepartment( sqlConnection, 
                        ref dataDepartmentid,
                        dataName,
                        dataGroupname,
                        dataModifieddate );
        data.Departmentid = dataDepartmentid;

        return result;
    }

    public static bool UpdateDepartment(SqlConnection sqlConnection, short departmentid,
        string name,
        string groupname,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[UpdateDepartment]";

        command.Parameters.AddInt16("@departmentid", departmentid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@groupname", groupname, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateDepartment(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.DepartmentDataType data )
    {
        var dataDepartmentid = data.Departmentid;
        var dataName = data.Name;
        var dataGroupname = data.Groupname;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateDepartment( sqlConnection, 
                        dataDepartmentid,
                        dataName,
                        dataGroupname,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteDepartment(SqlConnection sqlConnection, short departmentid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[DeleteDepartment]";

        command.Parameters.AddInt16("@departmentid", departmentid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteDepartment(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.DepartmentDataType data )
    {
        var dataDepartmentid = data.Departmentid;
        var result = DeleteDepartment( sqlConnection, 
                        dataDepartmentid );

        return result;
    }

    public static bool InsertEmployee(SqlConnection sqlConnection, int businessentityid,
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
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[InsertEmployee]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@nationalidnumber", nationalidnumber, 15);
        command.Parameters.AddNVarChar("@loginid", loginid, 256);
        command.Parameters.AddHierarchyId("@organizationnode", organizationnode);
        command.Parameters.AddInt16("@organizationlevel", organizationlevel);
        command.Parameters.AddNVarChar("@jobtitle", jobtitle, 50);
        command.Parameters.AddDateTime("@birthdate", birthdate);
        command.Parameters.AddNChar("@maritalstatus", maritalstatus, 1);
        command.Parameters.AddNChar("@gender", gender, 1);
        command.Parameters.AddDateTime("@hiredate", hiredate);
        command.Parameters.AddBoolean("@salariedflag", salariedflag);
        command.Parameters.AddInt16("@vacationhours", vacationhours);
        command.Parameters.AddInt16("@sickleavehours", sickleavehours);
        command.Parameters.AddBoolean("@currentflag", currentflag);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertEmployee(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.EmployeeDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataNationalidnumber = data.Nationalidnumber;
        var dataLoginid = data.Loginid;
        var dataOrganizationnode = data.Organizationnode;
        var dataOrganizationlevel = data.Organizationlevel;
        var dataJobtitle = data.Jobtitle;
        var dataBirthdate = data.Birthdate;
        var dataMaritalstatus = data.Maritalstatus;
        var dataGender = data.Gender;
        var dataHiredate = data.Hiredate;
        var dataSalariedflag = data.Salariedflag;
        var dataVacationhours = data.Vacationhours;
        var dataSickleavehours = data.Sickleavehours;
        var dataCurrentflag = data.Currentflag;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertEmployee( sqlConnection, 
                        dataBusinessentityid,
                        dataNationalidnumber,
                        dataLoginid,
                        dataOrganizationnode,
                        dataOrganizationlevel,
                        dataJobtitle,
                        dataBirthdate,
                        dataMaritalstatus,
                        dataGender,
                        dataHiredate,
                        dataSalariedflag,
                        dataVacationhours,
                        dataSickleavehours,
                        dataCurrentflag,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateEmployee(SqlConnection sqlConnection, int businessentityid,
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
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[UpdateEmployee]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@nationalidnumber", nationalidnumber, 15);
        command.Parameters.AddNVarChar("@loginid", loginid, 256);
        command.Parameters.AddHierarchyId("@organizationnode", organizationnode);
        command.Parameters.AddInt16("@organizationlevel", organizationlevel);
        command.Parameters.AddNVarChar("@jobtitle", jobtitle, 50);
        command.Parameters.AddDateTime("@birthdate", birthdate);
        command.Parameters.AddNChar("@maritalstatus", maritalstatus, 1);
        command.Parameters.AddNChar("@gender", gender, 1);
        command.Parameters.AddDateTime("@hiredate", hiredate);
        command.Parameters.AddBoolean("@salariedflag", salariedflag);
        command.Parameters.AddInt16("@vacationhours", vacationhours);
        command.Parameters.AddInt16("@sickleavehours", sickleavehours);
        command.Parameters.AddBoolean("@currentflag", currentflag);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateEmployee(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.EmployeeDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataNationalidnumber = data.Nationalidnumber;
        var dataLoginid = data.Loginid;
        var dataOrganizationnode = data.Organizationnode;
        var dataOrganizationlevel = data.Organizationlevel;
        var dataJobtitle = data.Jobtitle;
        var dataBirthdate = data.Birthdate;
        var dataMaritalstatus = data.Maritalstatus;
        var dataGender = data.Gender;
        var dataHiredate = data.Hiredate;
        var dataSalariedflag = data.Salariedflag;
        var dataVacationhours = data.Vacationhours;
        var dataSickleavehours = data.Sickleavehours;
        var dataCurrentflag = data.Currentflag;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateEmployee( sqlConnection, 
                        dataBusinessentityid,
                        dataNationalidnumber,
                        dataLoginid,
                        dataOrganizationnode,
                        dataOrganizationlevel,
                        dataJobtitle,
                        dataBirthdate,
                        dataMaritalstatus,
                        dataGender,
                        dataHiredate,
                        dataSalariedflag,
                        dataVacationhours,
                        dataSickleavehours,
                        dataCurrentflag,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteEmployee(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[DeleteEmployee]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteEmployee(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.EmployeeDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var result = DeleteEmployee( sqlConnection, 
                        dataBusinessentityid );

        return result;
    }

    public static bool InsertEmployeedepartmenthistory(SqlConnection sqlConnection, int businessentityid,
        short departmentid,
        byte shiftid,
        DateTime startdate,
        DateTime? enddate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[InsertEmployeeDepartmentHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt16("@departmentid", departmentid);
        command.Parameters.AddByte("@shiftid", shiftid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertEmployeedepartmenthistory(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.EmployeedepartmenthistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataDepartmentid = data.Departmentid;
        var dataShiftid = data.Shiftid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataModifieddate = data.Modifieddate;
        var result = InsertEmployeedepartmenthistory( sqlConnection, 
                        dataBusinessentityid,
                        dataDepartmentid,
                        dataShiftid,
                        dataStartdate,
                        dataEnddate,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateEmployeedepartmenthistory(SqlConnection sqlConnection, int businessentityid,
        short departmentid,
        byte shiftid,
        DateTime startdate,
        DateTime? enddate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[UpdateEmployeeDepartmentHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt16("@departmentid", departmentid);
        command.Parameters.AddByte("@shiftid", shiftid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateEmployeedepartmenthistory(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.EmployeedepartmenthistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataDepartmentid = data.Departmentid;
        var dataShiftid = data.Shiftid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateEmployeedepartmenthistory( sqlConnection, 
                        dataBusinessentityid,
                        dataDepartmentid,
                        dataShiftid,
                        dataStartdate,
                        dataEnddate,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteEmployeedepartmenthistory(SqlConnection sqlConnection, int businessentityid,
        DateTime startdate,
        short departmentid,
        byte shiftid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[DeleteEmployeeDepartmentHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddInt16("@departmentid", departmentid);
        command.Parameters.AddByte("@shiftid", shiftid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteEmployeedepartmenthistory(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.EmployeedepartmenthistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataStartdate = data.Startdate;
        var dataDepartmentid = data.Departmentid;
        var dataShiftid = data.Shiftid;
        var result = DeleteEmployeedepartmenthistory( sqlConnection, 
                        dataBusinessentityid,
                        dataStartdate,
                        dataDepartmentid,
                        dataShiftid );

        return result;
    }

    public static bool InsertEmployeepayhistory(SqlConnection sqlConnection, int businessentityid,
        DateTime ratechangedate,
        decimal rate,
        byte payfrequency,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[InsertEmployeePayHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDateTime("@ratechangedate", ratechangedate);
        command.Parameters.AddDecimal("@rate", rate);
        command.Parameters.AddByte("@payfrequency", payfrequency);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertEmployeepayhistory(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.EmployeepayhistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataRatechangedate = data.Ratechangedate;
        var dataRate = data.Rate;
        var dataPayfrequency = data.Payfrequency;
        var dataModifieddate = data.Modifieddate;
        var result = InsertEmployeepayhistory( sqlConnection, 
                        dataBusinessentityid,
                        dataRatechangedate,
                        dataRate,
                        dataPayfrequency,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateEmployeepayhistory(SqlConnection sqlConnection, int businessentityid,
        DateTime ratechangedate,
        decimal rate,
        byte payfrequency,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[UpdateEmployeePayHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDateTime("@ratechangedate", ratechangedate);
        command.Parameters.AddDecimal("@rate", rate);
        command.Parameters.AddByte("@payfrequency", payfrequency);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateEmployeepayhistory(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.EmployeepayhistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataRatechangedate = data.Ratechangedate;
        var dataRate = data.Rate;
        var dataPayfrequency = data.Payfrequency;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateEmployeepayhistory( sqlConnection, 
                        dataBusinessentityid,
                        dataRatechangedate,
                        dataRate,
                        dataPayfrequency,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteEmployeepayhistory(SqlConnection sqlConnection, int businessentityid,
        DateTime ratechangedate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[DeleteEmployeePayHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDateTime("@ratechangedate", ratechangedate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteEmployeepayhistory(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.EmployeepayhistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataRatechangedate = data.Ratechangedate;
        var result = DeleteEmployeepayhistory( sqlConnection, 
                        dataBusinessentityid,
                        dataRatechangedate );

        return result;
    }

    public static bool InsertJobcandidate(SqlConnection sqlConnection, ref int jobcandidateid,
        int? businessentityid,
        SqlXml? resume,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[InsertJobCandidate]";

        var jobcandidateidParameter = command.Parameters.AddInt32("@jobcandidateid");
        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddSqlXml("@resume", resume);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            jobcandidateid = (int)jobcandidateidParameter.Value;
        }
        return result;
    }

    public static bool InsertJobcandidate(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.JobcandidateDataType data )
    {
        var dataJobcandidateid = data.Jobcandidateid;
        var dataBusinessentityid = data.Businessentityid;
        var dataResume = data.Resume;
        var dataModifieddate = data.Modifieddate;
        var result = InsertJobcandidate( sqlConnection, 
                        ref dataJobcandidateid,
                        dataBusinessentityid,
                        dataResume,
                        dataModifieddate );
        data.Jobcandidateid = dataJobcandidateid;

        return result;
    }

    public static bool UpdateJobcandidate(SqlConnection sqlConnection, int jobcandidateid,
        int? businessentityid,
        SqlXml? resume,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[UpdateJobCandidate]";

        command.Parameters.AddInt32("@jobcandidateid", jobcandidateid);
        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddSqlXml("@resume", resume);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateJobcandidate(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.JobcandidateDataType data )
    {
        var dataJobcandidateid = data.Jobcandidateid;
        var dataBusinessentityid = data.Businessentityid;
        var dataResume = data.Resume;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateJobcandidate( sqlConnection, 
                        dataJobcandidateid,
                        dataBusinessentityid,
                        dataResume,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteJobcandidate(SqlConnection sqlConnection, int jobcandidateid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[DeleteJobCandidate]";

        command.Parameters.AddInt32("@jobcandidateid", jobcandidateid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteJobcandidate(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.JobcandidateDataType data )
    {
        var dataJobcandidateid = data.Jobcandidateid;
        var result = DeleteJobcandidate( sqlConnection, 
                        dataJobcandidateid );

        return result;
    }

    public static bool Insert1Jobcandidate(SqlConnection sqlConnection, ref int jobcandidateid,
        SqlXml? resume,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[Insert1JobCandidate]";

        var jobcandidateidParameter = command.Parameters.AddInt32("@jobcandidateid");
        command.Parameters.AddSqlXml("@resume", resume);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            jobcandidateid = (int)jobcandidateidParameter.Value;
        }
        return result;
    }

    public static bool Insert1Jobcandidate(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.JobcandidateDataType data )
    {
        var dataJobcandidateid = data.Jobcandidateid;
        var dataResume = data.Resume;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Jobcandidate( sqlConnection, 
                        ref dataJobcandidateid,
                        dataResume,
                        dataModifieddate );
        data.Jobcandidateid = dataJobcandidateid;

        return result;
    }

    public static bool Update1Jobcandidate(SqlConnection sqlConnection, int jobcandidateid,
        SqlXml? resume,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[Update1JobCandidate]";

        command.Parameters.AddInt32("@jobcandidateid", jobcandidateid);
        command.Parameters.AddSqlXml("@resume", resume);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update2Jobcandidate(SqlConnection sqlConnection, int jobcandidateid,
        int? businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[Update2JobCandidate]";

        command.Parameters.AddInt32("@jobcandidateid", jobcandidateid);
        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Jobcandidate(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.JobcandidateDataType data )
    {
        var dataJobcandidateid = data.Jobcandidateid;
        var dataResume = data.Resume;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Jobcandidate( sqlConnection, 
                        dataJobcandidateid,
                        dataResume,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Jobcandidate(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.JobcandidateDataType data )
    {
        var dataJobcandidateid = data.Jobcandidateid;
        var dataBusinessentityid = data.Businessentityid;
        var result = Update2Jobcandidate( sqlConnection, 
                        dataJobcandidateid,
                        dataBusinessentityid );

        return result;
    }

    public static bool InsertShift(SqlConnection sqlConnection, ref byte shiftid,
        string name,
        DateTime starttime,
        DateTime endtime,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[InsertShift]";

        var shiftidParameter = command.Parameters.AddByte("@shiftid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@starttime", starttime);
        command.Parameters.AddDateTime("@endtime", endtime);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            shiftid = (byte)shiftidParameter.Value;
        }
        return result;
    }

    public static bool InsertShift(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.ShiftDataType data )
    {
        var dataShiftid = data.Shiftid;
        var dataName = data.Name;
        var dataStarttime = data.Starttime;
        var dataEndtime = data.Endtime;
        var dataModifieddate = data.Modifieddate;
        var result = InsertShift( sqlConnection, 
                        ref dataShiftid,
                        dataName,
                        dataStarttime,
                        dataEndtime,
                        dataModifieddate );
        data.Shiftid = dataShiftid;

        return result;
    }

    public static bool UpdateShift(SqlConnection sqlConnection, byte shiftid,
        string name,
        DateTime starttime,
        DateTime endtime,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[UpdateShift]";

        command.Parameters.AddByte("@shiftid", shiftid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@starttime", starttime);
        command.Parameters.AddDateTime("@endtime", endtime);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateShift(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.ShiftDataType data )
    {
        var dataShiftid = data.Shiftid;
        var dataName = data.Name;
        var dataStarttime = data.Starttime;
        var dataEndtime = data.Endtime;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateShift( sqlConnection, 
                        dataShiftid,
                        dataName,
                        dataStarttime,
                        dataEndtime,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteShift(SqlConnection sqlConnection, byte shiftid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[DeleteShift]";

        command.Parameters.AddByte("@shiftid", shiftid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteShift(SqlConnection sqlConnection, AdventureWorks.HumanResources.Types.ShiftDataType data )
    {
        var dataShiftid = data.Shiftid;
        var result = DeleteShift( sqlConnection, 
                        dataShiftid );

        return result;
    }

}
