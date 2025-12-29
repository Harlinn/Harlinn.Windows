using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

using AdventureWorks.Types.Dbo;
using AdventureWorks.Types.HumanResources;
using AdventureWorks.Types.Person;
using AdventureWorks.Types.Production;
using AdventureWorks.Types.Purchasing;
using AdventureWorks.Types.Sales;

namespace AdventureWorks.Database;

public class StoredProcedures
{
    public static bool InsertAwbuildversion(SqlConnection sqlConnection, byte systeminformationid,
        string databaseVersion,
        DateTime versiondate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[InsertAWBuildVersion]";

        command.Parameters.AddWithValue("@systeminformationid", systeminformationid);
        command.Parameters.AddWithValue("@databaseVersion", databaseVersion);
        command.Parameters.AddWithValue("@versiondate", versiondate);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertAwbuildversion(SqlConnection sqlConnection, Types.Dbo.AwbuildversionDataType data )
    {
        return InsertAwbuildversion( sqlConnection, 
            data.Systeminformationid,
            data.DatabaseVersion,
            data.Versiondate,
            data.Modifieddate );
    }

    public static bool UpdateAwbuildversion(SqlConnection sqlConnection, byte systeminformationid,
        string databaseVersion,
        DateTime versiondate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[UpdateAWBuildVersion]";

        command.Parameters.AddWithValue("@systeminformationid", systeminformationid);
        command.Parameters.AddWithValue("@databaseVersion", databaseVersion);
        command.Parameters.AddWithValue("@versiondate", versiondate);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateAwbuildversion(SqlConnection sqlConnection, Types.Dbo.AwbuildversionDataType data )
    {
        return UpdateAwbuildversion( sqlConnection, 
            data.Systeminformationid,
            data.DatabaseVersion,
            data.Versiondate,
            data.Modifieddate );
    }

    public static bool DeleteAwbuildversion(SqlConnection sqlConnection, byte systeminformationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[DeleteAWBuildVersion]";

        command.Parameters.AddWithValue("@systeminformationid", systeminformationid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteAwbuildversion(SqlConnection sqlConnection, Types.Dbo.AwbuildversionDataType data )
    {
        return DeleteAwbuildversion( sqlConnection, 
            data.Systeminformationid );
    }

    public static bool InsertDatabaselog(SqlConnection sqlConnection, int databaselogid,
        DateTime posttime,
        string databaseuser,
        string event__,
        string? schema,
        string? object__,
        string tsql,
        SqlXml xmlevent)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[InsertDatabaseLog]";

        command.Parameters.AddWithValue("@databaselogid", databaselogid);
        command.Parameters.AddWithValue("@posttime", posttime);
        command.Parameters.AddWithValue("@databaseuser", databaseuser);
        command.Parameters.AddWithValue("@event", event__);
        command.Parameters.AddWithValue("@schema", (object?)schema ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@object", (object?)object__ ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@tsql", tsql);
        command.Parameters.AddWithValue("@xmlevent", xmlevent);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertDatabaselog(SqlConnection sqlConnection, Types.Dbo.DatabaselogDataType data )
    {
        return InsertDatabaselog( sqlConnection, 
            data.Databaselogid,
            data.Posttime,
            data.Databaseuser,
            data.Event,
            data.Schema,
            data.Object,
            data.Tsql,
            data.Xmlevent );
    }

    public static bool UpdateDatabaselog(SqlConnection sqlConnection, int databaselogid,
        DateTime posttime,
        string databaseuser,
        string event__,
        string? schema,
        string? object__,
        string tsql,
        SqlXml xmlevent)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[UpdateDatabaseLog]";

        command.Parameters.AddWithValue("@databaselogid", databaselogid);
        command.Parameters.AddWithValue("@posttime", posttime);
        command.Parameters.AddWithValue("@databaseuser", databaseuser);
        command.Parameters.AddWithValue("@event", event__);
        command.Parameters.AddWithValue("@schema", (object?)schema ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@object", (object?)object__ ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@tsql", tsql);
        command.Parameters.AddWithValue("@xmlevent", xmlevent);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateDatabaselog(SqlConnection sqlConnection, Types.Dbo.DatabaselogDataType data )
    {
        return UpdateDatabaselog( sqlConnection, 
            data.Databaselogid,
            data.Posttime,
            data.Databaseuser,
            data.Event,
            data.Schema,
            data.Object,
            data.Tsql,
            data.Xmlevent );
    }

    public static bool DeleteDatabaselog(SqlConnection sqlConnection, int databaselogid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[DeleteDatabaseLog]";

        command.Parameters.AddWithValue("@databaselogid", databaselogid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteDatabaselog(SqlConnection sqlConnection, Types.Dbo.DatabaselogDataType data )
    {
        return DeleteDatabaselog( sqlConnection, 
            data.Databaselogid );
    }

    public static bool InsertErrorlog(SqlConnection sqlConnection, int errorlogid,
        DateTime errortime,
        string username,
        int errornumber,
        int? errorseverity,
        int? errorstate,
        string? errorprocedure,
        int? errorline,
        string errormessage)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[InsertErrorLog]";

        command.Parameters.AddWithValue("@errorlogid", errorlogid);
        command.Parameters.AddWithValue("@errortime", errortime);
        command.Parameters.AddWithValue("@username", username);
        command.Parameters.AddWithValue("@errornumber", errornumber);
        command.Parameters.AddWithValue("@errorseverity", errorseverity.HasValue ? (object)errorseverity.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@errorstate", errorstate.HasValue ? (object)errorstate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@errorprocedure", (object?)errorprocedure ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@errorline", errorline.HasValue ? (object)errorline.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@errormessage", errormessage);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertErrorlog(SqlConnection sqlConnection, Types.Dbo.ErrorlogDataType data )
    {
        return InsertErrorlog( sqlConnection, 
            data.Errorlogid,
            data.Errortime,
            data.Username,
            data.Errornumber,
            data.Errorseverity,
            data.Errorstate,
            data.Errorprocedure,
            data.Errorline,
            data.Errormessage );
    }

    public static bool UpdateErrorlog(SqlConnection sqlConnection, int errorlogid,
        DateTime errortime,
        string username,
        int errornumber,
        int? errorseverity,
        int? errorstate,
        string? errorprocedure,
        int? errorline,
        string errormessage)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[UpdateErrorLog]";

        command.Parameters.AddWithValue("@errorlogid", errorlogid);
        command.Parameters.AddWithValue("@errortime", errortime);
        command.Parameters.AddWithValue("@username", username);
        command.Parameters.AddWithValue("@errornumber", errornumber);
        command.Parameters.AddWithValue("@errorseverity", errorseverity.HasValue ? (object)errorseverity.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@errorstate", errorstate.HasValue ? (object)errorstate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@errorprocedure", (object?)errorprocedure ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@errorline", errorline.HasValue ? (object)errorline.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@errormessage", errormessage);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateErrorlog(SqlConnection sqlConnection, Types.Dbo.ErrorlogDataType data )
    {
        return UpdateErrorlog( sqlConnection, 
            data.Errorlogid,
            data.Errortime,
            data.Username,
            data.Errornumber,
            data.Errorseverity,
            data.Errorstate,
            data.Errorprocedure,
            data.Errorline,
            data.Errormessage );
    }

    public static bool DeleteErrorlog(SqlConnection sqlConnection, int errorlogid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[DeleteErrorLog]";

        command.Parameters.AddWithValue("@errorlogid", errorlogid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteErrorlog(SqlConnection sqlConnection, Types.Dbo.ErrorlogDataType data )
    {
        return DeleteErrorlog( sqlConnection, 
            data.Errorlogid );
    }

    public static bool InsertDepartment(SqlConnection sqlConnection, short departmentid,
        string name,
        string groupname,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[InsertDepartment]";

        command.Parameters.AddWithValue("@departmentid", departmentid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@groupname", groupname);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertDepartment(SqlConnection sqlConnection, Types.HumanResources.DepartmentDataType data )
    {
        return InsertDepartment( sqlConnection, 
            data.Departmentid,
            data.Name,
            data.Groupname,
            data.Modifieddate );
    }

    public static bool UpdateDepartment(SqlConnection sqlConnection, short departmentid,
        string name,
        string groupname,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[UpdateDepartment]";

        command.Parameters.AddWithValue("@departmentid", departmentid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@groupname", groupname);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateDepartment(SqlConnection sqlConnection, Types.HumanResources.DepartmentDataType data )
    {
        return UpdateDepartment( sqlConnection, 
            data.Departmentid,
            data.Name,
            data.Groupname,
            data.Modifieddate );
    }

    public static bool DeleteDepartment(SqlConnection sqlConnection, short departmentid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[DeleteDepartment]";

        command.Parameters.AddWithValue("@departmentid", departmentid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteDepartment(SqlConnection sqlConnection, Types.HumanResources.DepartmentDataType data )
    {
        return DeleteDepartment( sqlConnection, 
            data.Departmentid );
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

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@nationalidnumber", nationalidnumber);
        command.Parameters.AddWithValue("@loginid", loginid);
        command.Parameters.AddWithValue("@organizationnode", (object?)organizationnode ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@organizationlevel", organizationlevel.HasValue ? (object)organizationlevel.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@jobtitle", jobtitle);
        command.Parameters.AddWithValue("@birthdate", birthdate);
        command.Parameters.AddWithValue("@maritalstatus", maritalstatus);
        command.Parameters.AddWithValue("@gender", gender);
        command.Parameters.AddWithValue("@hiredate", hiredate);
        command.Parameters.AddWithValue("@salariedflag", salariedflag);
        command.Parameters.AddWithValue("@vacationhours", vacationhours);
        command.Parameters.AddWithValue("@sickleavehours", sickleavehours);
        command.Parameters.AddWithValue("@currentflag", currentflag);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertEmployee(SqlConnection sqlConnection, Types.HumanResources.EmployeeDataType data )
    {
        return InsertEmployee( sqlConnection, 
            data.Businessentityid,
            data.Nationalidnumber,
            data.Loginid,
            data.Organizationnode,
            data.Organizationlevel,
            data.Jobtitle,
            data.Birthdate,
            data.Maritalstatus,
            data.Gender,
            data.Hiredate,
            data.Salariedflag,
            data.Vacationhours,
            data.Sickleavehours,
            data.Currentflag,
            data.Rowguid,
            data.Modifieddate );
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

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@nationalidnumber", nationalidnumber);
        command.Parameters.AddWithValue("@loginid", loginid);
        command.Parameters.AddWithValue("@organizationnode", (object?)organizationnode ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@organizationlevel", organizationlevel.HasValue ? (object)organizationlevel.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@jobtitle", jobtitle);
        command.Parameters.AddWithValue("@birthdate", birthdate);
        command.Parameters.AddWithValue("@maritalstatus", maritalstatus);
        command.Parameters.AddWithValue("@gender", gender);
        command.Parameters.AddWithValue("@hiredate", hiredate);
        command.Parameters.AddWithValue("@salariedflag", salariedflag);
        command.Parameters.AddWithValue("@vacationhours", vacationhours);
        command.Parameters.AddWithValue("@sickleavehours", sickleavehours);
        command.Parameters.AddWithValue("@currentflag", currentflag);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateEmployee(SqlConnection sqlConnection, Types.HumanResources.EmployeeDataType data )
    {
        return UpdateEmployee( sqlConnection, 
            data.Businessentityid,
            data.Nationalidnumber,
            data.Loginid,
            data.Organizationnode,
            data.Organizationlevel,
            data.Jobtitle,
            data.Birthdate,
            data.Maritalstatus,
            data.Gender,
            data.Hiredate,
            data.Salariedflag,
            data.Vacationhours,
            data.Sickleavehours,
            data.Currentflag,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteEmployee(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[DeleteEmployee]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteEmployee(SqlConnection sqlConnection, Types.HumanResources.EmployeeDataType data )
    {
        return DeleteEmployee( sqlConnection, 
            data.Businessentityid );
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

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@departmentid", departmentid);
        command.Parameters.AddWithValue("@shiftid", shiftid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertEmployeedepartmenthistory(SqlConnection sqlConnection, Types.HumanResources.EmployeedepartmenthistoryDataType data )
    {
        return InsertEmployeedepartmenthistory( sqlConnection, 
            data.Businessentityid,
            data.Departmentid,
            data.Shiftid,
            data.Startdate,
            data.Enddate,
            data.Modifieddate );
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

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@departmentid", departmentid);
        command.Parameters.AddWithValue("@shiftid", shiftid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateEmployeedepartmenthistory(SqlConnection sqlConnection, Types.HumanResources.EmployeedepartmenthistoryDataType data )
    {
        return UpdateEmployeedepartmenthistory( sqlConnection, 
            data.Businessentityid,
            data.Departmentid,
            data.Shiftid,
            data.Startdate,
            data.Enddate,
            data.Modifieddate );
    }

    public static bool DeleteEmployeedepartmenthistory(SqlConnection sqlConnection, int businessentityid,
        DateTime startdate,
        short departmentid,
        byte shiftid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[DeleteEmployeeDepartmentHistory]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@departmentid", departmentid);
        command.Parameters.AddWithValue("@shiftid", shiftid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteEmployeedepartmenthistory(SqlConnection sqlConnection, Types.HumanResources.EmployeedepartmenthistoryDataType data )
    {
        return DeleteEmployeedepartmenthistory( sqlConnection, 
            data.Businessentityid,
            data.Startdate,
            data.Departmentid,
            data.Shiftid );
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

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@ratechangedate", ratechangedate);
        command.Parameters.AddWithValue("@rate", rate);
        command.Parameters.AddWithValue("@payfrequency", payfrequency);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertEmployeepayhistory(SqlConnection sqlConnection, Types.HumanResources.EmployeepayhistoryDataType data )
    {
        return InsertEmployeepayhistory( sqlConnection, 
            data.Businessentityid,
            data.Ratechangedate,
            data.Rate,
            data.Payfrequency,
            data.Modifieddate );
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

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@ratechangedate", ratechangedate);
        command.Parameters.AddWithValue("@rate", rate);
        command.Parameters.AddWithValue("@payfrequency", payfrequency);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateEmployeepayhistory(SqlConnection sqlConnection, Types.HumanResources.EmployeepayhistoryDataType data )
    {
        return UpdateEmployeepayhistory( sqlConnection, 
            data.Businessentityid,
            data.Ratechangedate,
            data.Rate,
            data.Payfrequency,
            data.Modifieddate );
    }

    public static bool DeleteEmployeepayhistory(SqlConnection sqlConnection, int businessentityid,
        DateTime ratechangedate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[DeleteEmployeePayHistory]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@ratechangedate", ratechangedate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteEmployeepayhistory(SqlConnection sqlConnection, Types.HumanResources.EmployeepayhistoryDataType data )
    {
        return DeleteEmployeepayhistory( sqlConnection, 
            data.Businessentityid,
            data.Ratechangedate );
    }

    public static bool InsertJobcandidate(SqlConnection sqlConnection, int jobcandidateid,
        int? businessentityid,
        SqlXml? resume,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[InsertJobCandidate]";

        command.Parameters.AddWithValue("@jobcandidateid", jobcandidateid);
        command.Parameters.AddWithValue("@businessentityid", businessentityid.HasValue ? (object)businessentityid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@resume", (object?)resume ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertJobcandidate(SqlConnection sqlConnection, Types.HumanResources.JobcandidateDataType data )
    {
        return InsertJobcandidate( sqlConnection, 
            data.Jobcandidateid,
            data.Businessentityid,
            data.Resume,
            data.Modifieddate );
    }

    public static bool UpdateJobcandidate(SqlConnection sqlConnection, int jobcandidateid,
        int? businessentityid,
        SqlXml? resume,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[UpdateJobCandidate]";

        command.Parameters.AddWithValue("@jobcandidateid", jobcandidateid);
        command.Parameters.AddWithValue("@businessentityid", businessentityid.HasValue ? (object)businessentityid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@resume", (object?)resume ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateJobcandidate(SqlConnection sqlConnection, Types.HumanResources.JobcandidateDataType data )
    {
        return UpdateJobcandidate( sqlConnection, 
            data.Jobcandidateid,
            data.Businessentityid,
            data.Resume,
            data.Modifieddate );
    }

    public static bool DeleteJobcandidate(SqlConnection sqlConnection, int jobcandidateid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[DeleteJobCandidate]";

        command.Parameters.AddWithValue("@jobcandidateid", jobcandidateid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteJobcandidate(SqlConnection sqlConnection, Types.HumanResources.JobcandidateDataType data )
    {
        return DeleteJobcandidate( sqlConnection, 
            data.Jobcandidateid );
    }

    public static bool Insert1Jobcandidate(SqlConnection sqlConnection, int jobcandidateid,
        SqlXml? resume,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[Insert1JobCandidate]";

        command.Parameters.AddWithValue("@jobcandidateid", jobcandidateid);
        command.Parameters.AddWithValue("@resume", (object?)resume ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Insert1Jobcandidate(SqlConnection sqlConnection, Types.HumanResources.JobcandidateDataType data )
    {
        return Insert1Jobcandidate( sqlConnection, 
            data.Jobcandidateid,
            data.Resume,
            data.Modifieddate );
    }

    public static bool Update1Jobcandidate(SqlConnection sqlConnection, int jobcandidateid,
        SqlXml? resume,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[Update1JobCandidate]";

        command.Parameters.AddWithValue("@jobcandidateid", jobcandidateid);
        command.Parameters.AddWithValue("@resume", (object?)resume ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update2Jobcandidate(SqlConnection sqlConnection, int jobcandidateid,
        int? businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[Update2JobCandidate]";

        command.Parameters.AddWithValue("@jobcandidateid", jobcandidateid);
        command.Parameters.AddWithValue("@businessentityid", businessentityid.HasValue ? (object)businessentityid.Value : (object)DBNull.Value);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update1Jobcandidate(SqlConnection sqlConnection, Types.HumanResources.JobcandidateDataType data )
    {
        return Update1Jobcandidate( sqlConnection, 
            data.Jobcandidateid,
            data.Resume,
            data.Modifieddate );
    }

    public static bool Update2Jobcandidate(SqlConnection sqlConnection, Types.HumanResources.JobcandidateDataType data )
    {
        return Update2Jobcandidate( sqlConnection, 
            data.Jobcandidateid,
            data.Businessentityid );
    }

    public static bool InsertShift(SqlConnection sqlConnection, byte shiftid,
        string name,
        DateTime starttime,
        DateTime endtime,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[InsertShift]";

        command.Parameters.AddWithValue("@shiftid", shiftid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@starttime", starttime);
        command.Parameters.AddWithValue("@endtime", endtime);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertShift(SqlConnection sqlConnection, Types.HumanResources.ShiftDataType data )
    {
        return InsertShift( sqlConnection, 
            data.Shiftid,
            data.Name,
            data.Starttime,
            data.Endtime,
            data.Modifieddate );
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

        command.Parameters.AddWithValue("@shiftid", shiftid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@starttime", starttime);
        command.Parameters.AddWithValue("@endtime", endtime);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateShift(SqlConnection sqlConnection, Types.HumanResources.ShiftDataType data )
    {
        return UpdateShift( sqlConnection, 
            data.Shiftid,
            data.Name,
            data.Starttime,
            data.Endtime,
            data.Modifieddate );
    }

    public static bool DeleteShift(SqlConnection sqlConnection, byte shiftid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[HumanResources].[DeleteShift]";

        command.Parameters.AddWithValue("@shiftid", shiftid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteShift(SqlConnection sqlConnection, Types.HumanResources.ShiftDataType data )
    {
        return DeleteShift( sqlConnection, 
            data.Shiftid );
    }

    public static bool InsertAddress(SqlConnection sqlConnection, int addressid,
        string addressline1,
        string? addressline2,
        string city,
        int stateprovinceid,
        string postalcode,
        SqlGeography? spatiallocation,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertAddress]";

        command.Parameters.AddWithValue("@addressid", addressid);
        command.Parameters.AddWithValue("@addressline1", addressline1);
        command.Parameters.AddWithValue("@addressline2", (object?)addressline2 ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@city", city);
        command.Parameters.AddWithValue("@stateprovinceid", stateprovinceid);
        command.Parameters.AddWithValue("@postalcode", postalcode);
        command.Parameters.AddWithValue("@spatiallocation", (object?)spatiallocation ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertAddress(SqlConnection sqlConnection, Types.Person.AddressDataType data )
    {
        return InsertAddress( sqlConnection, 
            data.Addressid,
            data.Addressline1,
            data.Addressline2,
            data.City,
            data.Stateprovinceid,
            data.Postalcode,
            data.Spatiallocation,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateAddress(SqlConnection sqlConnection, int addressid,
        string addressline1,
        string? addressline2,
        string city,
        int stateprovinceid,
        string postalcode,
        SqlGeography? spatiallocation,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateAddress]";

        command.Parameters.AddWithValue("@addressid", addressid);
        command.Parameters.AddWithValue("@addressline1", addressline1);
        command.Parameters.AddWithValue("@addressline2", (object?)addressline2 ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@city", city);
        command.Parameters.AddWithValue("@stateprovinceid", stateprovinceid);
        command.Parameters.AddWithValue("@postalcode", postalcode);
        command.Parameters.AddWithValue("@spatiallocation", (object?)spatiallocation ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateAddress(SqlConnection sqlConnection, Types.Person.AddressDataType data )
    {
        return UpdateAddress( sqlConnection, 
            data.Addressid,
            data.Addressline1,
            data.Addressline2,
            data.City,
            data.Stateprovinceid,
            data.Postalcode,
            data.Spatiallocation,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteAddress(SqlConnection sqlConnection, int addressid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteAddress]";

        command.Parameters.AddWithValue("@addressid", addressid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteAddress(SqlConnection sqlConnection, Types.Person.AddressDataType data )
    {
        return DeleteAddress( sqlConnection, 
            data.Addressid );
    }

    public static bool InsertAddresstype(SqlConnection sqlConnection, int addresstypeid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertAddressType]";

        command.Parameters.AddWithValue("@addresstypeid", addresstypeid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertAddresstype(SqlConnection sqlConnection, Types.Person.AddresstypeDataType data )
    {
        return InsertAddresstype( sqlConnection, 
            data.Addresstypeid,
            data.Name,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateAddresstype(SqlConnection sqlConnection, int addresstypeid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateAddressType]";

        command.Parameters.AddWithValue("@addresstypeid", addresstypeid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateAddresstype(SqlConnection sqlConnection, Types.Person.AddresstypeDataType data )
    {
        return UpdateAddresstype( sqlConnection, 
            data.Addresstypeid,
            data.Name,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteAddresstype(SqlConnection sqlConnection, int addresstypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteAddressType]";

        command.Parameters.AddWithValue("@addresstypeid", addresstypeid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteAddresstype(SqlConnection sqlConnection, Types.Person.AddresstypeDataType data )
    {
        return DeleteAddresstype( sqlConnection, 
            data.Addresstypeid );
    }

    public static bool InsertBusinessentity(SqlConnection sqlConnection, int businessentityid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertBusinessEntity]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertBusinessentity(SqlConnection sqlConnection, Types.Person.BusinessentityDataType data )
    {
        return InsertBusinessentity( sqlConnection, 
            data.Businessentityid,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateBusinessentity(SqlConnection sqlConnection, int businessentityid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateBusinessEntity]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateBusinessentity(SqlConnection sqlConnection, Types.Person.BusinessentityDataType data )
    {
        return UpdateBusinessentity( sqlConnection, 
            data.Businessentityid,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteBusinessentity(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteBusinessEntity]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteBusinessentity(SqlConnection sqlConnection, Types.Person.BusinessentityDataType data )
    {
        return DeleteBusinessentity( sqlConnection, 
            data.Businessentityid );
    }

    public static bool InsertBusinessentityaddress(SqlConnection sqlConnection, int businessentityid,
        int addressid,
        int addresstypeid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertBusinessEntityAddress]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@addressid", addressid);
        command.Parameters.AddWithValue("@addresstypeid", addresstypeid);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertBusinessentityaddress(SqlConnection sqlConnection, Types.Person.BusinessentityaddressDataType data )
    {
        return InsertBusinessentityaddress( sqlConnection, 
            data.Businessentityid,
            data.Addressid,
            data.Addresstypeid,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateBusinessentityaddress(SqlConnection sqlConnection, int businessentityid,
        int addressid,
        int addresstypeid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateBusinessEntityAddress]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@addressid", addressid);
        command.Parameters.AddWithValue("@addresstypeid", addresstypeid);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateBusinessentityaddress(SqlConnection sqlConnection, Types.Person.BusinessentityaddressDataType data )
    {
        return UpdateBusinessentityaddress( sqlConnection, 
            data.Businessentityid,
            data.Addressid,
            data.Addresstypeid,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteBusinessentityaddress(SqlConnection sqlConnection, int businessentityid,
        int addressid,
        int addresstypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteBusinessEntityAddress]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@addressid", addressid);
        command.Parameters.AddWithValue("@addresstypeid", addresstypeid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteBusinessentityaddress(SqlConnection sqlConnection, Types.Person.BusinessentityaddressDataType data )
    {
        return DeleteBusinessentityaddress( sqlConnection, 
            data.Businessentityid,
            data.Addressid,
            data.Addresstypeid );
    }

    public static bool InsertBusinessentitycontact(SqlConnection sqlConnection, int businessentityid,
        int personid,
        int contacttypeid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertBusinessEntityContact]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@personid", personid);
        command.Parameters.AddWithValue("@contacttypeid", contacttypeid);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertBusinessentitycontact(SqlConnection sqlConnection, Types.Person.BusinessentitycontactDataType data )
    {
        return InsertBusinessentitycontact( sqlConnection, 
            data.Businessentityid,
            data.Personid,
            data.Contacttypeid,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateBusinessentitycontact(SqlConnection sqlConnection, int businessentityid,
        int personid,
        int contacttypeid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateBusinessEntityContact]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@personid", personid);
        command.Parameters.AddWithValue("@contacttypeid", contacttypeid);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateBusinessentitycontact(SqlConnection sqlConnection, Types.Person.BusinessentitycontactDataType data )
    {
        return UpdateBusinessentitycontact( sqlConnection, 
            data.Businessentityid,
            data.Personid,
            data.Contacttypeid,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteBusinessentitycontact(SqlConnection sqlConnection, int businessentityid,
        int personid,
        int contacttypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteBusinessEntityContact]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@personid", personid);
        command.Parameters.AddWithValue("@contacttypeid", contacttypeid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteBusinessentitycontact(SqlConnection sqlConnection, Types.Person.BusinessentitycontactDataType data )
    {
        return DeleteBusinessentitycontact( sqlConnection, 
            data.Businessentityid,
            data.Personid,
            data.Contacttypeid );
    }

    public static bool InsertContacttype(SqlConnection sqlConnection, int contacttypeid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertContactType]";

        command.Parameters.AddWithValue("@contacttypeid", contacttypeid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertContacttype(SqlConnection sqlConnection, Types.Person.ContacttypeDataType data )
    {
        return InsertContacttype( sqlConnection, 
            data.Contacttypeid,
            data.Name,
            data.Modifieddate );
    }

    public static bool UpdateContacttype(SqlConnection sqlConnection, int contacttypeid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateContactType]";

        command.Parameters.AddWithValue("@contacttypeid", contacttypeid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateContacttype(SqlConnection sqlConnection, Types.Person.ContacttypeDataType data )
    {
        return UpdateContacttype( sqlConnection, 
            data.Contacttypeid,
            data.Name,
            data.Modifieddate );
    }

    public static bool DeleteContacttype(SqlConnection sqlConnection, int contacttypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteContactType]";

        command.Parameters.AddWithValue("@contacttypeid", contacttypeid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteContacttype(SqlConnection sqlConnection, Types.Person.ContacttypeDataType data )
    {
        return DeleteContacttype( sqlConnection, 
            data.Contacttypeid );
    }

    public static bool InsertCountryregion(SqlConnection sqlConnection, string countryregioncode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertCountryRegion]";

        command.Parameters.AddWithValue("@countryregioncode", countryregioncode);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertCountryregion(SqlConnection sqlConnection, Types.Person.CountryregionDataType data )
    {
        return InsertCountryregion( sqlConnection, 
            data.Countryregioncode,
            data.Name,
            data.Modifieddate );
    }

    public static bool UpdateCountryregion(SqlConnection sqlConnection, string countryregioncode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateCountryRegion]";

        command.Parameters.AddWithValue("@countryregioncode", countryregioncode);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateCountryregion(SqlConnection sqlConnection, Types.Person.CountryregionDataType data )
    {
        return UpdateCountryregion( sqlConnection, 
            data.Countryregioncode,
            data.Name,
            data.Modifieddate );
    }

    public static bool DeleteCountryregion(SqlConnection sqlConnection, string countryregioncode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteCountryRegion]";

        command.Parameters.AddWithValue("@countryregioncode", countryregioncode);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteCountryregion(SqlConnection sqlConnection, Types.Person.CountryregionDataType data )
    {
        return DeleteCountryregion( sqlConnection, 
            data.Countryregioncode );
    }

    public static bool InsertEmailaddress(SqlConnection sqlConnection, int businessentityid,
        int emailaddressid,
        string? emailaddress,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertEmailAddress]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@emailaddressid", emailaddressid);
        command.Parameters.AddWithValue("@emailaddress", (object?)emailaddress ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertEmailaddress(SqlConnection sqlConnection, Types.Person.EmailaddressDataType data )
    {
        return InsertEmailaddress( sqlConnection, 
            data.Businessentityid,
            data.Emailaddressid,
            data.Emailaddress,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateEmailaddress(SqlConnection sqlConnection, int businessentityid,
        int emailaddressid,
        string? emailaddress,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateEmailAddress]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@emailaddressid", emailaddressid);
        command.Parameters.AddWithValue("@emailaddress", (object?)emailaddress ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateEmailaddress(SqlConnection sqlConnection, Types.Person.EmailaddressDataType data )
    {
        return UpdateEmailaddress( sqlConnection, 
            data.Businessentityid,
            data.Emailaddressid,
            data.Emailaddress,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteEmailaddress(SqlConnection sqlConnection, int businessentityid,
        int emailaddressid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteEmailAddress]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@emailaddressid", emailaddressid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteEmailaddress(SqlConnection sqlConnection, Types.Person.EmailaddressDataType data )
    {
        return DeleteEmailaddress( sqlConnection, 
            data.Businessentityid,
            data.Emailaddressid );
    }

    public static bool InsertPassword(SqlConnection sqlConnection, int businessentityid,
        string passwordhash,
        string passwordsalt,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertPassword]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@passwordhash", passwordhash);
        command.Parameters.AddWithValue("@passwordsalt", passwordsalt);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertPassword(SqlConnection sqlConnection, Types.Person.PasswordDataType data )
    {
        return InsertPassword( sqlConnection, 
            data.Businessentityid,
            data.Passwordhash,
            data.Passwordsalt,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdatePassword(SqlConnection sqlConnection, int businessentityid,
        string passwordhash,
        string passwordsalt,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdatePassword]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@passwordhash", passwordhash);
        command.Parameters.AddWithValue("@passwordsalt", passwordsalt);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdatePassword(SqlConnection sqlConnection, Types.Person.PasswordDataType data )
    {
        return UpdatePassword( sqlConnection, 
            data.Businessentityid,
            data.Passwordhash,
            data.Passwordsalt,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeletePassword(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeletePassword]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeletePassword(SqlConnection sqlConnection, Types.Person.PasswordDataType data )
    {
        return DeletePassword( sqlConnection, 
            data.Businessentityid );
    }

    public static bool InsertPerson(SqlConnection sqlConnection, int businessentityid,
        string persontype,
        bool namestyle,
        string? title,
        string firstname,
        string? middlename,
        string lastname,
        string? suffix,
        int emailpromotion,
        SqlXml? additionalcontactinfo,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertPerson]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@persontype", persontype);
        command.Parameters.AddWithValue("@namestyle", namestyle);
        command.Parameters.AddWithValue("@title", (object?)title ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@firstname", firstname);
        command.Parameters.AddWithValue("@middlename", (object?)middlename ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@lastname", lastname);
        command.Parameters.AddWithValue("@suffix", (object?)suffix ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@emailpromotion", emailpromotion);
        command.Parameters.AddWithValue("@additionalcontactinfo", (object?)additionalcontactinfo ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@demographics", (object?)demographics ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertPerson(SqlConnection sqlConnection, Types.Person.PersonDataType data )
    {
        return InsertPerson( sqlConnection, 
            data.Businessentityid,
            data.Persontype,
            data.Namestyle,
            data.Title,
            data.Firstname,
            data.Middlename,
            data.Lastname,
            data.Suffix,
            data.Emailpromotion,
            data.Additionalcontactinfo,
            data.Demographics,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdatePerson(SqlConnection sqlConnection, int businessentityid,
        string persontype,
        bool namestyle,
        string? title,
        string firstname,
        string? middlename,
        string lastname,
        string? suffix,
        int emailpromotion,
        SqlXml? additionalcontactinfo,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdatePerson]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@persontype", persontype);
        command.Parameters.AddWithValue("@namestyle", namestyle);
        command.Parameters.AddWithValue("@title", (object?)title ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@firstname", firstname);
        command.Parameters.AddWithValue("@middlename", (object?)middlename ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@lastname", lastname);
        command.Parameters.AddWithValue("@suffix", (object?)suffix ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@emailpromotion", emailpromotion);
        command.Parameters.AddWithValue("@additionalcontactinfo", (object?)additionalcontactinfo ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@demographics", (object?)demographics ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdatePerson(SqlConnection sqlConnection, Types.Person.PersonDataType data )
    {
        return UpdatePerson( sqlConnection, 
            data.Businessentityid,
            data.Persontype,
            data.Namestyle,
            data.Title,
            data.Firstname,
            data.Middlename,
            data.Lastname,
            data.Suffix,
            data.Emailpromotion,
            data.Additionalcontactinfo,
            data.Demographics,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeletePerson(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeletePerson]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeletePerson(SqlConnection sqlConnection, Types.Person.PersonDataType data )
    {
        return DeletePerson( sqlConnection, 
            data.Businessentityid );
    }

    public static bool InsertPersonphone(SqlConnection sqlConnection, int businessentityid,
        string phonenumber,
        int phonenumbertypeid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertPersonPhone]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@phonenumber", phonenumber);
        command.Parameters.AddWithValue("@phonenumbertypeid", phonenumbertypeid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertPersonphone(SqlConnection sqlConnection, Types.Person.PersonphoneDataType data )
    {
        return InsertPersonphone( sqlConnection, 
            data.Businessentityid,
            data.Phonenumber,
            data.Phonenumbertypeid,
            data.Modifieddate );
    }

    public static bool UpdatePersonphone(SqlConnection sqlConnection, int businessentityid,
        string phonenumber,
        int phonenumbertypeid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdatePersonPhone]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@phonenumber", phonenumber);
        command.Parameters.AddWithValue("@phonenumbertypeid", phonenumbertypeid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdatePersonphone(SqlConnection sqlConnection, Types.Person.PersonphoneDataType data )
    {
        return UpdatePersonphone( sqlConnection, 
            data.Businessentityid,
            data.Phonenumber,
            data.Phonenumbertypeid,
            data.Modifieddate );
    }

    public static bool DeletePersonphone(SqlConnection sqlConnection, int businessentityid,
        string phonenumber,
        int phonenumbertypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeletePersonPhone]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@phonenumber", phonenumber);
        command.Parameters.AddWithValue("@phonenumbertypeid", phonenumbertypeid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeletePersonphone(SqlConnection sqlConnection, Types.Person.PersonphoneDataType data )
    {
        return DeletePersonphone( sqlConnection, 
            data.Businessentityid,
            data.Phonenumber,
            data.Phonenumbertypeid );
    }

    public static bool InsertPhonenumbertype(SqlConnection sqlConnection, int phonenumbertypeid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertPhoneNumberType]";

        command.Parameters.AddWithValue("@phonenumbertypeid", phonenumbertypeid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertPhonenumbertype(SqlConnection sqlConnection, Types.Person.PhonenumbertypeDataType data )
    {
        return InsertPhonenumbertype( sqlConnection, 
            data.Phonenumbertypeid,
            data.Name,
            data.Modifieddate );
    }

    public static bool UpdatePhonenumbertype(SqlConnection sqlConnection, int phonenumbertypeid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdatePhoneNumberType]";

        command.Parameters.AddWithValue("@phonenumbertypeid", phonenumbertypeid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdatePhonenumbertype(SqlConnection sqlConnection, Types.Person.PhonenumbertypeDataType data )
    {
        return UpdatePhonenumbertype( sqlConnection, 
            data.Phonenumbertypeid,
            data.Name,
            data.Modifieddate );
    }

    public static bool DeletePhonenumbertype(SqlConnection sqlConnection, int phonenumbertypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeletePhoneNumberType]";

        command.Parameters.AddWithValue("@phonenumbertypeid", phonenumbertypeid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeletePhonenumbertype(SqlConnection sqlConnection, Types.Person.PhonenumbertypeDataType data )
    {
        return DeletePhonenumbertype( sqlConnection, 
            data.Phonenumbertypeid );
    }

    public static bool InsertStateprovince(SqlConnection sqlConnection, int stateprovinceid,
        string stateprovincecode,
        string countryregioncode,
        bool isonlystateprovinceflag,
        string name,
        int territoryid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertStateProvince]";

        command.Parameters.AddWithValue("@stateprovinceid", stateprovinceid);
        command.Parameters.AddWithValue("@stateprovincecode", stateprovincecode);
        command.Parameters.AddWithValue("@countryregioncode", countryregioncode);
        command.Parameters.AddWithValue("@isonlystateprovinceflag", isonlystateprovinceflag);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@territoryid", territoryid);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertStateprovince(SqlConnection sqlConnection, Types.Person.StateprovinceDataType data )
    {
        return InsertStateprovince( sqlConnection, 
            data.Stateprovinceid,
            data.Stateprovincecode,
            data.Countryregioncode,
            data.Isonlystateprovinceflag,
            data.Name,
            data.Territoryid,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateStateprovince(SqlConnection sqlConnection, int stateprovinceid,
        string stateprovincecode,
        string countryregioncode,
        bool isonlystateprovinceflag,
        string name,
        int territoryid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateStateProvince]";

        command.Parameters.AddWithValue("@stateprovinceid", stateprovinceid);
        command.Parameters.AddWithValue("@stateprovincecode", stateprovincecode);
        command.Parameters.AddWithValue("@countryregioncode", countryregioncode);
        command.Parameters.AddWithValue("@isonlystateprovinceflag", isonlystateprovinceflag);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@territoryid", territoryid);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateStateprovince(SqlConnection sqlConnection, Types.Person.StateprovinceDataType data )
    {
        return UpdateStateprovince( sqlConnection, 
            data.Stateprovinceid,
            data.Stateprovincecode,
            data.Countryregioncode,
            data.Isonlystateprovinceflag,
            data.Name,
            data.Territoryid,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteStateprovince(SqlConnection sqlConnection, int stateprovinceid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteStateProvince]";

        command.Parameters.AddWithValue("@stateprovinceid", stateprovinceid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteStateprovince(SqlConnection sqlConnection, Types.Person.StateprovinceDataType data )
    {
        return DeleteStateprovince( sqlConnection, 
            data.Stateprovinceid );
    }

    public static bool InsertBillofmaterials(SqlConnection sqlConnection, int billofmaterialsid,
        int? productassemblyid,
        int componentid,
        DateTime startdate,
        DateTime? enddate,
        string unitmeasurecode,
        short bomlevel,
        decimal perassemblyqty,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertBillOfMaterials]";

        command.Parameters.AddWithValue("@billofmaterialsid", billofmaterialsid);
        command.Parameters.AddWithValue("@productassemblyid", productassemblyid.HasValue ? (object)productassemblyid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@componentid", componentid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@unitmeasurecode", unitmeasurecode);
        command.Parameters.AddWithValue("@bomlevel", bomlevel);
        command.Parameters.AddWithValue("@perassemblyqty", perassemblyqty);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertBillofmaterials(SqlConnection sqlConnection, Types.Production.BillofmaterialsDataType data )
    {
        return InsertBillofmaterials( sqlConnection, 
            data.Billofmaterialsid,
            data.Productassemblyid,
            data.Componentid,
            data.Startdate,
            data.Enddate,
            data.Unitmeasurecode,
            data.Bomlevel,
            data.Perassemblyqty,
            data.Modifieddate );
    }

    public static bool UpdateBillofmaterials(SqlConnection sqlConnection, int billofmaterialsid,
        int? productassemblyid,
        int componentid,
        DateTime startdate,
        DateTime? enddate,
        string unitmeasurecode,
        short bomlevel,
        decimal perassemblyqty,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateBillOfMaterials]";

        command.Parameters.AddWithValue("@billofmaterialsid", billofmaterialsid);
        command.Parameters.AddWithValue("@productassemblyid", productassemblyid.HasValue ? (object)productassemblyid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@componentid", componentid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@unitmeasurecode", unitmeasurecode);
        command.Parameters.AddWithValue("@bomlevel", bomlevel);
        command.Parameters.AddWithValue("@perassemblyqty", perassemblyqty);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateBillofmaterials(SqlConnection sqlConnection, Types.Production.BillofmaterialsDataType data )
    {
        return UpdateBillofmaterials( sqlConnection, 
            data.Billofmaterialsid,
            data.Productassemblyid,
            data.Componentid,
            data.Startdate,
            data.Enddate,
            data.Unitmeasurecode,
            data.Bomlevel,
            data.Perassemblyqty,
            data.Modifieddate );
    }

    public static bool DeleteBillofmaterials(SqlConnection sqlConnection, int billofmaterialsid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteBillOfMaterials]";

        command.Parameters.AddWithValue("@billofmaterialsid", billofmaterialsid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteBillofmaterials(SqlConnection sqlConnection, Types.Production.BillofmaterialsDataType data )
    {
        return DeleteBillofmaterials( sqlConnection, 
            data.Billofmaterialsid );
    }

    public static bool Insert1Billofmaterials(SqlConnection sqlConnection, int billofmaterialsid,
        int componentid,
        DateTime startdate,
        DateTime? enddate,
        string unitmeasurecode,
        short bomlevel,
        decimal perassemblyqty,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Insert1BillOfMaterials]";

        command.Parameters.AddWithValue("@billofmaterialsid", billofmaterialsid);
        command.Parameters.AddWithValue("@componentid", componentid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@unitmeasurecode", unitmeasurecode);
        command.Parameters.AddWithValue("@bomlevel", bomlevel);
        command.Parameters.AddWithValue("@perassemblyqty", perassemblyqty);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Insert1Billofmaterials(SqlConnection sqlConnection, Types.Production.BillofmaterialsDataType data )
    {
        return Insert1Billofmaterials( sqlConnection, 
            data.Billofmaterialsid,
            data.Componentid,
            data.Startdate,
            data.Enddate,
            data.Unitmeasurecode,
            data.Bomlevel,
            data.Perassemblyqty,
            data.Modifieddate );
    }

    public static bool Update1Billofmaterials(SqlConnection sqlConnection, int billofmaterialsid,
        int componentid,
        DateTime startdate,
        DateTime? enddate,
        string unitmeasurecode,
        short bomlevel,
        decimal perassemblyqty,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update1BillOfMaterials]";

        command.Parameters.AddWithValue("@billofmaterialsid", billofmaterialsid);
        command.Parameters.AddWithValue("@componentid", componentid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@unitmeasurecode", unitmeasurecode);
        command.Parameters.AddWithValue("@bomlevel", bomlevel);
        command.Parameters.AddWithValue("@perassemblyqty", perassemblyqty);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update2Billofmaterials(SqlConnection sqlConnection, int billofmaterialsid,
        int? productassemblyid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update2BillOfMaterials]";

        command.Parameters.AddWithValue("@billofmaterialsid", billofmaterialsid);
        command.Parameters.AddWithValue("@productassemblyid", productassemblyid.HasValue ? (object)productassemblyid.Value : (object)DBNull.Value);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update1Billofmaterials(SqlConnection sqlConnection, Types.Production.BillofmaterialsDataType data )
    {
        return Update1Billofmaterials( sqlConnection, 
            data.Billofmaterialsid,
            data.Componentid,
            data.Startdate,
            data.Enddate,
            data.Unitmeasurecode,
            data.Bomlevel,
            data.Perassemblyqty,
            data.Modifieddate );
    }

    public static bool Update2Billofmaterials(SqlConnection sqlConnection, Types.Production.BillofmaterialsDataType data )
    {
        return Update2Billofmaterials( sqlConnection, 
            data.Billofmaterialsid,
            data.Productassemblyid );
    }

    public static bool InsertCulture(SqlConnection sqlConnection, string cultureid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertCulture]";

        command.Parameters.AddWithValue("@cultureid", cultureid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertCulture(SqlConnection sqlConnection, Types.Production.CultureDataType data )
    {
        return InsertCulture( sqlConnection, 
            data.Cultureid,
            data.Name,
            data.Modifieddate );
    }

    public static bool UpdateCulture(SqlConnection sqlConnection, string cultureid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateCulture]";

        command.Parameters.AddWithValue("@cultureid", cultureid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateCulture(SqlConnection sqlConnection, Types.Production.CultureDataType data )
    {
        return UpdateCulture( sqlConnection, 
            data.Cultureid,
            data.Name,
            data.Modifieddate );
    }

    public static bool DeleteCulture(SqlConnection sqlConnection, string cultureid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteCulture]";

        command.Parameters.AddWithValue("@cultureid", cultureid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteCulture(SqlConnection sqlConnection, Types.Production.CultureDataType data )
    {
        return DeleteCulture( sqlConnection, 
            data.Cultureid );
    }

    public static bool InsertDocument(SqlConnection sqlConnection, SqlHierarchyId documentnode,
        short? documentlevel,
        string title,
        int owner,
        bool folderflag,
        string filename,
        string fileextension,
        string revision,
        int changenumber,
        byte status,
        string? documentsummary,
        byte[]? document,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertDocument]";

        command.Parameters.AddWithValue("@documentnode", documentnode);
        command.Parameters.AddWithValue("@documentlevel", documentlevel.HasValue ? (object)documentlevel.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@title", title);
        command.Parameters.AddWithValue("@owner", owner);
        command.Parameters.AddWithValue("@folderflag", folderflag);
        command.Parameters.AddWithValue("@filename", filename);
        command.Parameters.AddWithValue("@fileextension", fileextension);
        command.Parameters.AddWithValue("@revision", revision);
        command.Parameters.AddWithValue("@changenumber", changenumber);
        command.Parameters.AddWithValue("@status", status);
        command.Parameters.AddWithValue("@documentsummary", (object?)documentsummary ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@document", (object?)document ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertDocument(SqlConnection sqlConnection, Types.Production.DocumentDataType data )
    {
        return InsertDocument( sqlConnection, 
            data.Documentnode,
            data.Documentlevel,
            data.Title,
            data.Owner,
            data.Folderflag,
            data.Filename,
            data.Fileextension,
            data.Revision,
            data.Changenumber,
            data.Status,
            data.Documentsummary,
            data.Document,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateDocument(SqlConnection sqlConnection, SqlHierarchyId documentnode,
        short? documentlevel,
        string title,
        int owner,
        bool folderflag,
        string filename,
        string fileextension,
        string revision,
        int changenumber,
        byte status,
        string? documentsummary,
        byte[]? document,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateDocument]";

        command.Parameters.AddWithValue("@documentnode", documentnode);
        command.Parameters.AddWithValue("@documentlevel", documentlevel.HasValue ? (object)documentlevel.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@title", title);
        command.Parameters.AddWithValue("@owner", owner);
        command.Parameters.AddWithValue("@folderflag", folderflag);
        command.Parameters.AddWithValue("@filename", filename);
        command.Parameters.AddWithValue("@fileextension", fileextension);
        command.Parameters.AddWithValue("@revision", revision);
        command.Parameters.AddWithValue("@changenumber", changenumber);
        command.Parameters.AddWithValue("@status", status);
        command.Parameters.AddWithValue("@documentsummary", (object?)documentsummary ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@document", (object?)document ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateDocument(SqlConnection sqlConnection, Types.Production.DocumentDataType data )
    {
        return UpdateDocument( sqlConnection, 
            data.Documentnode,
            data.Documentlevel,
            data.Title,
            data.Owner,
            data.Folderflag,
            data.Filename,
            data.Fileextension,
            data.Revision,
            data.Changenumber,
            data.Status,
            data.Documentsummary,
            data.Document,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteDocument(SqlConnection sqlConnection, SqlHierarchyId documentnode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteDocument]";

        command.Parameters.AddWithValue("@documentnode", documentnode);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteDocument(SqlConnection sqlConnection, Types.Production.DocumentDataType data )
    {
        return DeleteDocument( sqlConnection, 
            data.Documentnode );
    }

    public static bool InsertIllustration(SqlConnection sqlConnection, int illustrationid,
        SqlXml? diagram,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertIllustration]";

        command.Parameters.AddWithValue("@illustrationid", illustrationid);
        command.Parameters.AddWithValue("@diagram", (object?)diagram ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertIllustration(SqlConnection sqlConnection, Types.Production.IllustrationDataType data )
    {
        return InsertIllustration( sqlConnection, 
            data.Illustrationid,
            data.Diagram,
            data.Modifieddate );
    }

    public static bool UpdateIllustration(SqlConnection sqlConnection, int illustrationid,
        SqlXml? diagram,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateIllustration]";

        command.Parameters.AddWithValue("@illustrationid", illustrationid);
        command.Parameters.AddWithValue("@diagram", (object?)diagram ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateIllustration(SqlConnection sqlConnection, Types.Production.IllustrationDataType data )
    {
        return UpdateIllustration( sqlConnection, 
            data.Illustrationid,
            data.Diagram,
            data.Modifieddate );
    }

    public static bool DeleteIllustration(SqlConnection sqlConnection, int illustrationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteIllustration]";

        command.Parameters.AddWithValue("@illustrationid", illustrationid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteIllustration(SqlConnection sqlConnection, Types.Production.IllustrationDataType data )
    {
        return DeleteIllustration( sqlConnection, 
            data.Illustrationid );
    }

    public static bool InsertLocation(SqlConnection sqlConnection, short locationid,
        string name,
        decimal costrate,
        decimal availability,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertLocation]";

        command.Parameters.AddWithValue("@locationid", locationid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@costrate", costrate);
        command.Parameters.AddWithValue("@availability", availability);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertLocation(SqlConnection sqlConnection, Types.Production.LocationDataType data )
    {
        return InsertLocation( sqlConnection, 
            data.Locationid,
            data.Name,
            data.Costrate,
            data.Availability,
            data.Modifieddate );
    }

    public static bool UpdateLocation(SqlConnection sqlConnection, short locationid,
        string name,
        decimal costrate,
        decimal availability,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateLocation]";

        command.Parameters.AddWithValue("@locationid", locationid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@costrate", costrate);
        command.Parameters.AddWithValue("@availability", availability);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateLocation(SqlConnection sqlConnection, Types.Production.LocationDataType data )
    {
        return UpdateLocation( sqlConnection, 
            data.Locationid,
            data.Name,
            data.Costrate,
            data.Availability,
            data.Modifieddate );
    }

    public static bool DeleteLocation(SqlConnection sqlConnection, short locationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteLocation]";

        command.Parameters.AddWithValue("@locationid", locationid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteLocation(SqlConnection sqlConnection, Types.Production.LocationDataType data )
    {
        return DeleteLocation( sqlConnection, 
            data.Locationid );
    }

    public static bool InsertProduct(SqlConnection sqlConnection, int productid,
        string name,
        string productnumber,
        bool makeflag,
        bool finishedgoodsflag,
        string? color,
        short safetystocklevel,
        short reorderpoint,
        decimal standardcost,
        decimal listprice,
        string? size,
        string? sizeunitmeasurecode,
        string? weightunitmeasurecode,
        decimal? weight,
        int daystomanufacture,
        string? productline,
        string? class__,
        string? style,
        int? productsubcategoryid,
        int? productmodelid,
        DateTime sellstartdate,
        DateTime? sellenddate,
        DateTime? discontinueddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProduct]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@productnumber", productnumber);
        command.Parameters.AddWithValue("@makeflag", makeflag);
        command.Parameters.AddWithValue("@finishedgoodsflag", finishedgoodsflag);
        command.Parameters.AddWithValue("@color", (object?)color ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@safetystocklevel", safetystocklevel);
        command.Parameters.AddWithValue("@reorderpoint", reorderpoint);
        command.Parameters.AddWithValue("@standardcost", standardcost);
        command.Parameters.AddWithValue("@listprice", listprice);
        command.Parameters.AddWithValue("@size", (object?)size ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@sizeunitmeasurecode", (object?)sizeunitmeasurecode ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@weightunitmeasurecode", (object?)weightunitmeasurecode ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@weight", weight.HasValue ? (object)weight.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@daystomanufacture", daystomanufacture);
        command.Parameters.AddWithValue("@productline", (object?)productline ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@class", (object?)class__ ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@style", (object?)style ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@productsubcategoryid", productsubcategoryid.HasValue ? (object)productsubcategoryid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@productmodelid", productmodelid.HasValue ? (object)productmodelid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@sellstartdate", sellstartdate);
        command.Parameters.AddWithValue("@sellenddate", sellenddate.HasValue ? (object)sellenddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@discontinueddate", discontinueddate.HasValue ? (object)discontinueddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProduct(SqlConnection sqlConnection, Types.Production.ProductDataType data )
    {
        return InsertProduct( sqlConnection, 
            data.Productid,
            data.Name,
            data.Productnumber,
            data.Makeflag,
            data.Finishedgoodsflag,
            data.Color,
            data.Safetystocklevel,
            data.Reorderpoint,
            data.Standardcost,
            data.Listprice,
            data.Size,
            data.Sizeunitmeasurecode,
            data.Weightunitmeasurecode,
            data.Weight,
            data.Daystomanufacture,
            data.Productline,
            data.Class,
            data.Style,
            data.Productsubcategoryid,
            data.Productmodelid,
            data.Sellstartdate,
            data.Sellenddate,
            data.Discontinueddate,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateProduct(SqlConnection sqlConnection, int productid,
        string name,
        string productnumber,
        bool makeflag,
        bool finishedgoodsflag,
        string? color,
        short safetystocklevel,
        short reorderpoint,
        decimal standardcost,
        decimal listprice,
        string? size,
        string? sizeunitmeasurecode,
        string? weightunitmeasurecode,
        decimal? weight,
        int daystomanufacture,
        string? productline,
        string? class__,
        string? style,
        int? productsubcategoryid,
        int? productmodelid,
        DateTime sellstartdate,
        DateTime? sellenddate,
        DateTime? discontinueddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProduct]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@productnumber", productnumber);
        command.Parameters.AddWithValue("@makeflag", makeflag);
        command.Parameters.AddWithValue("@finishedgoodsflag", finishedgoodsflag);
        command.Parameters.AddWithValue("@color", (object?)color ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@safetystocklevel", safetystocklevel);
        command.Parameters.AddWithValue("@reorderpoint", reorderpoint);
        command.Parameters.AddWithValue("@standardcost", standardcost);
        command.Parameters.AddWithValue("@listprice", listprice);
        command.Parameters.AddWithValue("@size", (object?)size ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@sizeunitmeasurecode", (object?)sizeunitmeasurecode ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@weightunitmeasurecode", (object?)weightunitmeasurecode ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@weight", weight.HasValue ? (object)weight.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@daystomanufacture", daystomanufacture);
        command.Parameters.AddWithValue("@productline", (object?)productline ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@class", (object?)class__ ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@style", (object?)style ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@productsubcategoryid", productsubcategoryid.HasValue ? (object)productsubcategoryid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@productmodelid", productmodelid.HasValue ? (object)productmodelid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@sellstartdate", sellstartdate);
        command.Parameters.AddWithValue("@sellenddate", sellenddate.HasValue ? (object)sellenddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@discontinueddate", discontinueddate.HasValue ? (object)discontinueddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProduct(SqlConnection sqlConnection, Types.Production.ProductDataType data )
    {
        return UpdateProduct( sqlConnection, 
            data.Productid,
            data.Name,
            data.Productnumber,
            data.Makeflag,
            data.Finishedgoodsflag,
            data.Color,
            data.Safetystocklevel,
            data.Reorderpoint,
            data.Standardcost,
            data.Listprice,
            data.Size,
            data.Sizeunitmeasurecode,
            data.Weightunitmeasurecode,
            data.Weight,
            data.Daystomanufacture,
            data.Productline,
            data.Class,
            data.Style,
            data.Productsubcategoryid,
            data.Productmodelid,
            data.Sellstartdate,
            data.Sellenddate,
            data.Discontinueddate,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteProduct(SqlConnection sqlConnection, int productid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProduct]";

        command.Parameters.AddWithValue("@productid", productid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProduct(SqlConnection sqlConnection, Types.Production.ProductDataType data )
    {
        return DeleteProduct( sqlConnection, 
            data.Productid );
    }

    public static bool Insert1Product(SqlConnection sqlConnection, int productid,
        string name,
        string productnumber,
        bool makeflag,
        bool finishedgoodsflag,
        string? color,
        short safetystocklevel,
        short reorderpoint,
        decimal standardcost,
        decimal listprice,
        string? size,
        decimal? weight,
        int daystomanufacture,
        string? productline,
        string? class__,
        string? style,
        DateTime sellstartdate,
        DateTime? sellenddate,
        DateTime? discontinueddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Insert1Product]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@productnumber", productnumber);
        command.Parameters.AddWithValue("@makeflag", makeflag);
        command.Parameters.AddWithValue("@finishedgoodsflag", finishedgoodsflag);
        command.Parameters.AddWithValue("@color", (object?)color ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@safetystocklevel", safetystocklevel);
        command.Parameters.AddWithValue("@reorderpoint", reorderpoint);
        command.Parameters.AddWithValue("@standardcost", standardcost);
        command.Parameters.AddWithValue("@listprice", listprice);
        command.Parameters.AddWithValue("@size", (object?)size ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@weight", weight.HasValue ? (object)weight.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@daystomanufacture", daystomanufacture);
        command.Parameters.AddWithValue("@productline", (object?)productline ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@class", (object?)class__ ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@style", (object?)style ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@sellstartdate", sellstartdate);
        command.Parameters.AddWithValue("@sellenddate", sellenddate.HasValue ? (object)sellenddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@discontinueddate", discontinueddate.HasValue ? (object)discontinueddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Insert1Product(SqlConnection sqlConnection, Types.Production.ProductDataType data )
    {
        return Insert1Product( sqlConnection, 
            data.Productid,
            data.Name,
            data.Productnumber,
            data.Makeflag,
            data.Finishedgoodsflag,
            data.Color,
            data.Safetystocklevel,
            data.Reorderpoint,
            data.Standardcost,
            data.Listprice,
            data.Size,
            data.Weight,
            data.Daystomanufacture,
            data.Productline,
            data.Class,
            data.Style,
            data.Sellstartdate,
            data.Sellenddate,
            data.Discontinueddate,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool Update1Product(SqlConnection sqlConnection, int productid,
        string name,
        string productnumber,
        bool makeflag,
        bool finishedgoodsflag,
        string? color,
        short safetystocklevel,
        short reorderpoint,
        decimal standardcost,
        decimal listprice,
        string? size,
        decimal? weight,
        int daystomanufacture,
        string? productline,
        string? class__,
        string? style,
        DateTime sellstartdate,
        DateTime? sellenddate,
        DateTime? discontinueddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update1Product]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@productnumber", productnumber);
        command.Parameters.AddWithValue("@makeflag", makeflag);
        command.Parameters.AddWithValue("@finishedgoodsflag", finishedgoodsflag);
        command.Parameters.AddWithValue("@color", (object?)color ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@safetystocklevel", safetystocklevel);
        command.Parameters.AddWithValue("@reorderpoint", reorderpoint);
        command.Parameters.AddWithValue("@standardcost", standardcost);
        command.Parameters.AddWithValue("@listprice", listprice);
        command.Parameters.AddWithValue("@size", (object?)size ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@weight", weight.HasValue ? (object)weight.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@daystomanufacture", daystomanufacture);
        command.Parameters.AddWithValue("@productline", (object?)productline ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@class", (object?)class__ ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@style", (object?)style ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@sellstartdate", sellstartdate);
        command.Parameters.AddWithValue("@sellenddate", sellenddate.HasValue ? (object)sellenddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@discontinueddate", discontinueddate.HasValue ? (object)discontinueddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update2Product(SqlConnection sqlConnection, int productid,
        string? sizeunitmeasurecode,
        string? weightunitmeasurecode,
        int? productsubcategoryid,
        int? productmodelid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update2Product]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@sizeunitmeasurecode", (object?)sizeunitmeasurecode ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@weightunitmeasurecode", (object?)weightunitmeasurecode ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@productsubcategoryid", productsubcategoryid.HasValue ? (object)productsubcategoryid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@productmodelid", productmodelid.HasValue ? (object)productmodelid.Value : (object)DBNull.Value);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update1Product(SqlConnection sqlConnection, Types.Production.ProductDataType data )
    {
        return Update1Product( sqlConnection, 
            data.Productid,
            data.Name,
            data.Productnumber,
            data.Makeflag,
            data.Finishedgoodsflag,
            data.Color,
            data.Safetystocklevel,
            data.Reorderpoint,
            data.Standardcost,
            data.Listprice,
            data.Size,
            data.Weight,
            data.Daystomanufacture,
            data.Productline,
            data.Class,
            data.Style,
            data.Sellstartdate,
            data.Sellenddate,
            data.Discontinueddate,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool Update2Product(SqlConnection sqlConnection, Types.Production.ProductDataType data )
    {
        return Update2Product( sqlConnection, 
            data.Productid,
            data.Sizeunitmeasurecode,
            data.Weightunitmeasurecode,
            data.Productsubcategoryid,
            data.Productmodelid );
    }

    public static bool InsertProductcategory(SqlConnection sqlConnection, int productcategoryid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductCategory]";

        command.Parameters.AddWithValue("@productcategoryid", productcategoryid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductcategory(SqlConnection sqlConnection, Types.Production.ProductcategoryDataType data )
    {
        return InsertProductcategory( sqlConnection, 
            data.Productcategoryid,
            data.Name,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateProductcategory(SqlConnection sqlConnection, int productcategoryid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductCategory]";

        command.Parameters.AddWithValue("@productcategoryid", productcategoryid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductcategory(SqlConnection sqlConnection, Types.Production.ProductcategoryDataType data )
    {
        return UpdateProductcategory( sqlConnection, 
            data.Productcategoryid,
            data.Name,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteProductcategory(SqlConnection sqlConnection, int productcategoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductCategory]";

        command.Parameters.AddWithValue("@productcategoryid", productcategoryid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductcategory(SqlConnection sqlConnection, Types.Production.ProductcategoryDataType data )
    {
        return DeleteProductcategory( sqlConnection, 
            data.Productcategoryid );
    }

    public static bool InsertProductcosthistory(SqlConnection sqlConnection, int productid,
        DateTime startdate,
        DateTime? enddate,
        decimal standardcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductCostHistory]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@standardcost", standardcost);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductcosthistory(SqlConnection sqlConnection, Types.Production.ProductcosthistoryDataType data )
    {
        return InsertProductcosthistory( sqlConnection, 
            data.Productid,
            data.Startdate,
            data.Enddate,
            data.Standardcost,
            data.Modifieddate );
    }

    public static bool UpdateProductcosthistory(SqlConnection sqlConnection, int productid,
        DateTime startdate,
        DateTime? enddate,
        decimal standardcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductCostHistory]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@standardcost", standardcost);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductcosthistory(SqlConnection sqlConnection, Types.Production.ProductcosthistoryDataType data )
    {
        return UpdateProductcosthistory( sqlConnection, 
            data.Productid,
            data.Startdate,
            data.Enddate,
            data.Standardcost,
            data.Modifieddate );
    }

    public static bool DeleteProductcosthistory(SqlConnection sqlConnection, int productid,
        DateTime startdate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductCostHistory]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@startdate", startdate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductcosthistory(SqlConnection sqlConnection, Types.Production.ProductcosthistoryDataType data )
    {
        return DeleteProductcosthistory( sqlConnection, 
            data.Productid,
            data.Startdate );
    }

    public static bool InsertProductdescription(SqlConnection sqlConnection, int productdescriptionid,
        string description,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductDescription]";

        command.Parameters.AddWithValue("@productdescriptionid", productdescriptionid);
        command.Parameters.AddWithValue("@description", description);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductdescription(SqlConnection sqlConnection, Types.Production.ProductdescriptionDataType data )
    {
        return InsertProductdescription( sqlConnection, 
            data.Productdescriptionid,
            data.Description,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateProductdescription(SqlConnection sqlConnection, int productdescriptionid,
        string description,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductDescription]";

        command.Parameters.AddWithValue("@productdescriptionid", productdescriptionid);
        command.Parameters.AddWithValue("@description", description);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductdescription(SqlConnection sqlConnection, Types.Production.ProductdescriptionDataType data )
    {
        return UpdateProductdescription( sqlConnection, 
            data.Productdescriptionid,
            data.Description,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteProductdescription(SqlConnection sqlConnection, int productdescriptionid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductDescription]";

        command.Parameters.AddWithValue("@productdescriptionid", productdescriptionid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductdescription(SqlConnection sqlConnection, Types.Production.ProductdescriptionDataType data )
    {
        return DeleteProductdescription( sqlConnection, 
            data.Productdescriptionid );
    }

    public static bool InsertProductdocument(SqlConnection sqlConnection, int productid,
        SqlHierarchyId documentnode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductDocument]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@documentnode", documentnode);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductdocument(SqlConnection sqlConnection, Types.Production.ProductdocumentDataType data )
    {
        return InsertProductdocument( sqlConnection, 
            data.Productid,
            data.Documentnode,
            data.Modifieddate );
    }

    public static bool UpdateProductdocument(SqlConnection sqlConnection, int productid,
        SqlHierarchyId documentnode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductDocument]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@documentnode", documentnode);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductdocument(SqlConnection sqlConnection, Types.Production.ProductdocumentDataType data )
    {
        return UpdateProductdocument( sqlConnection, 
            data.Productid,
            data.Documentnode,
            data.Modifieddate );
    }

    public static bool DeleteProductdocument(SqlConnection sqlConnection, int productid,
        SqlHierarchyId documentnode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductDocument]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@documentnode", documentnode);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductdocument(SqlConnection sqlConnection, Types.Production.ProductdocumentDataType data )
    {
        return DeleteProductdocument( sqlConnection, 
            data.Productid,
            data.Documentnode );
    }

    public static bool InsertProductinventory(SqlConnection sqlConnection, int productid,
        short locationid,
        string shelf,
        byte bin,
        short quantity,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductInventory]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@locationid", locationid);
        command.Parameters.AddWithValue("@shelf", shelf);
        command.Parameters.AddWithValue("@bin", bin);
        command.Parameters.AddWithValue("@quantity", quantity);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductinventory(SqlConnection sqlConnection, Types.Production.ProductinventoryDataType data )
    {
        return InsertProductinventory( sqlConnection, 
            data.Productid,
            data.Locationid,
            data.Shelf,
            data.Bin,
            data.Quantity,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateProductinventory(SqlConnection sqlConnection, int productid,
        short locationid,
        string shelf,
        byte bin,
        short quantity,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductInventory]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@locationid", locationid);
        command.Parameters.AddWithValue("@shelf", shelf);
        command.Parameters.AddWithValue("@bin", bin);
        command.Parameters.AddWithValue("@quantity", quantity);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductinventory(SqlConnection sqlConnection, Types.Production.ProductinventoryDataType data )
    {
        return UpdateProductinventory( sqlConnection, 
            data.Productid,
            data.Locationid,
            data.Shelf,
            data.Bin,
            data.Quantity,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteProductinventory(SqlConnection sqlConnection, int productid,
        short locationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductInventory]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@locationid", locationid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductinventory(SqlConnection sqlConnection, Types.Production.ProductinventoryDataType data )
    {
        return DeleteProductinventory( sqlConnection, 
            data.Productid,
            data.Locationid );
    }

    public static bool InsertProductlistpricehistory(SqlConnection sqlConnection, int productid,
        DateTime startdate,
        DateTime? enddate,
        decimal listprice,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductListPriceHistory]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@listprice", listprice);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductlistpricehistory(SqlConnection sqlConnection, Types.Production.ProductlistpricehistoryDataType data )
    {
        return InsertProductlistpricehistory( sqlConnection, 
            data.Productid,
            data.Startdate,
            data.Enddate,
            data.Listprice,
            data.Modifieddate );
    }

    public static bool UpdateProductlistpricehistory(SqlConnection sqlConnection, int productid,
        DateTime startdate,
        DateTime? enddate,
        decimal listprice,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductListPriceHistory]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@listprice", listprice);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductlistpricehistory(SqlConnection sqlConnection, Types.Production.ProductlistpricehistoryDataType data )
    {
        return UpdateProductlistpricehistory( sqlConnection, 
            data.Productid,
            data.Startdate,
            data.Enddate,
            data.Listprice,
            data.Modifieddate );
    }

    public static bool DeleteProductlistpricehistory(SqlConnection sqlConnection, int productid,
        DateTime startdate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductListPriceHistory]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@startdate", startdate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductlistpricehistory(SqlConnection sqlConnection, Types.Production.ProductlistpricehistoryDataType data )
    {
        return DeleteProductlistpricehistory( sqlConnection, 
            data.Productid,
            data.Startdate );
    }

    public static bool InsertProductmodel(SqlConnection sqlConnection, int productmodelid,
        string name,
        SqlXml? catalogdescription,
        SqlXml? instructions,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductModel]";

        command.Parameters.AddWithValue("@productmodelid", productmodelid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@catalogdescription", (object?)catalogdescription ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@instructions", (object?)instructions ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductmodel(SqlConnection sqlConnection, Types.Production.ProductmodelDataType data )
    {
        return InsertProductmodel( sqlConnection, 
            data.Productmodelid,
            data.Name,
            data.Catalogdescription,
            data.Instructions,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateProductmodel(SqlConnection sqlConnection, int productmodelid,
        string name,
        SqlXml? catalogdescription,
        SqlXml? instructions,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductModel]";

        command.Parameters.AddWithValue("@productmodelid", productmodelid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@catalogdescription", (object?)catalogdescription ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@instructions", (object?)instructions ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductmodel(SqlConnection sqlConnection, Types.Production.ProductmodelDataType data )
    {
        return UpdateProductmodel( sqlConnection, 
            data.Productmodelid,
            data.Name,
            data.Catalogdescription,
            data.Instructions,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteProductmodel(SqlConnection sqlConnection, int productmodelid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductModel]";

        command.Parameters.AddWithValue("@productmodelid", productmodelid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductmodel(SqlConnection sqlConnection, Types.Production.ProductmodelDataType data )
    {
        return DeleteProductmodel( sqlConnection, 
            data.Productmodelid );
    }

    public static bool InsertProductmodelillustration(SqlConnection sqlConnection, int productmodelid,
        int illustrationid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductModelIllustration]";

        command.Parameters.AddWithValue("@productmodelid", productmodelid);
        command.Parameters.AddWithValue("@illustrationid", illustrationid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductmodelillustration(SqlConnection sqlConnection, Types.Production.ProductmodelillustrationDataType data )
    {
        return InsertProductmodelillustration( sqlConnection, 
            data.Productmodelid,
            data.Illustrationid,
            data.Modifieddate );
    }

    public static bool UpdateProductmodelillustration(SqlConnection sqlConnection, int productmodelid,
        int illustrationid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductModelIllustration]";

        command.Parameters.AddWithValue("@productmodelid", productmodelid);
        command.Parameters.AddWithValue("@illustrationid", illustrationid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductmodelillustration(SqlConnection sqlConnection, Types.Production.ProductmodelillustrationDataType data )
    {
        return UpdateProductmodelillustration( sqlConnection, 
            data.Productmodelid,
            data.Illustrationid,
            data.Modifieddate );
    }

    public static bool DeleteProductmodelillustration(SqlConnection sqlConnection, int productmodelid,
        int illustrationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductModelIllustration]";

        command.Parameters.AddWithValue("@productmodelid", productmodelid);
        command.Parameters.AddWithValue("@illustrationid", illustrationid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductmodelillustration(SqlConnection sqlConnection, Types.Production.ProductmodelillustrationDataType data )
    {
        return DeleteProductmodelillustration( sqlConnection, 
            data.Productmodelid,
            data.Illustrationid );
    }

    public static bool InsertProductmodelproductdescriptionculture(SqlConnection sqlConnection, int productmodelid,
        int productdescriptionid,
        string cultureid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductModelProductDescriptionCulture]";

        command.Parameters.AddWithValue("@productmodelid", productmodelid);
        command.Parameters.AddWithValue("@productdescriptionid", productdescriptionid);
        command.Parameters.AddWithValue("@cultureid", cultureid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductmodelproductdescriptionculture(SqlConnection sqlConnection, Types.Production.ProductmodelproductdescriptioncultureDataType data )
    {
        return InsertProductmodelproductdescriptionculture( sqlConnection, 
            data.Productmodelid,
            data.Productdescriptionid,
            data.Cultureid,
            data.Modifieddate );
    }

    public static bool UpdateProductmodelproductdescriptionculture(SqlConnection sqlConnection, int productmodelid,
        int productdescriptionid,
        string cultureid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductModelProductDescriptionCulture]";

        command.Parameters.AddWithValue("@productmodelid", productmodelid);
        command.Parameters.AddWithValue("@productdescriptionid", productdescriptionid);
        command.Parameters.AddWithValue("@cultureid", cultureid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductmodelproductdescriptionculture(SqlConnection sqlConnection, Types.Production.ProductmodelproductdescriptioncultureDataType data )
    {
        return UpdateProductmodelproductdescriptionculture( sqlConnection, 
            data.Productmodelid,
            data.Productdescriptionid,
            data.Cultureid,
            data.Modifieddate );
    }

    public static bool DeleteProductmodelproductdescriptionculture(SqlConnection sqlConnection, int productmodelid,
        int productdescriptionid,
        string cultureid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductModelProductDescriptionCulture]";

        command.Parameters.AddWithValue("@productmodelid", productmodelid);
        command.Parameters.AddWithValue("@productdescriptionid", productdescriptionid);
        command.Parameters.AddWithValue("@cultureid", cultureid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductmodelproductdescriptionculture(SqlConnection sqlConnection, Types.Production.ProductmodelproductdescriptioncultureDataType data )
    {
        return DeleteProductmodelproductdescriptionculture( sqlConnection, 
            data.Productmodelid,
            data.Productdescriptionid,
            data.Cultureid );
    }

    public static bool InsertProductphoto(SqlConnection sqlConnection, int productphotoid,
        byte[]? thumbnailphoto,
        string? thumbnailphotofilename,
        byte[]? largephoto,
        string? largephotofilename,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductPhoto]";

        command.Parameters.AddWithValue("@productphotoid", productphotoid);
        command.Parameters.AddWithValue("@thumbnailphoto", (object?)thumbnailphoto ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@thumbnailphotofilename", (object?)thumbnailphotofilename ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@largephoto", (object?)largephoto ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@largephotofilename", (object?)largephotofilename ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductphoto(SqlConnection sqlConnection, Types.Production.ProductphotoDataType data )
    {
        return InsertProductphoto( sqlConnection, 
            data.Productphotoid,
            data.Thumbnailphoto,
            data.Thumbnailphotofilename,
            data.Largephoto,
            data.Largephotofilename,
            data.Modifieddate );
    }

    public static bool UpdateProductphoto(SqlConnection sqlConnection, int productphotoid,
        byte[]? thumbnailphoto,
        string? thumbnailphotofilename,
        byte[]? largephoto,
        string? largephotofilename,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductPhoto]";

        command.Parameters.AddWithValue("@productphotoid", productphotoid);
        command.Parameters.AddWithValue("@thumbnailphoto", (object?)thumbnailphoto ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@thumbnailphotofilename", (object?)thumbnailphotofilename ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@largephoto", (object?)largephoto ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@largephotofilename", (object?)largephotofilename ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductphoto(SqlConnection sqlConnection, Types.Production.ProductphotoDataType data )
    {
        return UpdateProductphoto( sqlConnection, 
            data.Productphotoid,
            data.Thumbnailphoto,
            data.Thumbnailphotofilename,
            data.Largephoto,
            data.Largephotofilename,
            data.Modifieddate );
    }

    public static bool DeleteProductphoto(SqlConnection sqlConnection, int productphotoid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductPhoto]";

        command.Parameters.AddWithValue("@productphotoid", productphotoid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductphoto(SqlConnection sqlConnection, Types.Production.ProductphotoDataType data )
    {
        return DeleteProductphoto( sqlConnection, 
            data.Productphotoid );
    }

    public static bool InsertProductproductphoto(SqlConnection sqlConnection, int productid,
        int productphotoid,
        bool primary,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductProductPhoto]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@productphotoid", productphotoid);
        command.Parameters.AddWithValue("@primary", primary);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductproductphoto(SqlConnection sqlConnection, Types.Production.ProductproductphotoDataType data )
    {
        return InsertProductproductphoto( sqlConnection, 
            data.Productid,
            data.Productphotoid,
            data.Primary,
            data.Modifieddate );
    }

    public static bool UpdateProductproductphoto(SqlConnection sqlConnection, int productid,
        int productphotoid,
        bool primary,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductProductPhoto]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@productphotoid", productphotoid);
        command.Parameters.AddWithValue("@primary", primary);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductproductphoto(SqlConnection sqlConnection, Types.Production.ProductproductphotoDataType data )
    {
        return UpdateProductproductphoto( sqlConnection, 
            data.Productid,
            data.Productphotoid,
            data.Primary,
            data.Modifieddate );
    }

    public static bool DeleteProductproductphoto(SqlConnection sqlConnection, int productid,
        int productphotoid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductProductPhoto]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@productphotoid", productphotoid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductproductphoto(SqlConnection sqlConnection, Types.Production.ProductproductphotoDataType data )
    {
        return DeleteProductproductphoto( sqlConnection, 
            data.Productid,
            data.Productphotoid );
    }

    public static bool InsertProductreview(SqlConnection sqlConnection, int productreviewid,
        int productid,
        string reviewername,
        DateTime reviewdate,
        string emailaddress,
        int rating,
        string? comments,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductReview]";

        command.Parameters.AddWithValue("@productreviewid", productreviewid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@reviewername", reviewername);
        command.Parameters.AddWithValue("@reviewdate", reviewdate);
        command.Parameters.AddWithValue("@emailaddress", emailaddress);
        command.Parameters.AddWithValue("@rating", rating);
        command.Parameters.AddWithValue("@comments", (object?)comments ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductreview(SqlConnection sqlConnection, Types.Production.ProductreviewDataType data )
    {
        return InsertProductreview( sqlConnection, 
            data.Productreviewid,
            data.Productid,
            data.Reviewername,
            data.Reviewdate,
            data.Emailaddress,
            data.Rating,
            data.Comments,
            data.Modifieddate );
    }

    public static bool UpdateProductreview(SqlConnection sqlConnection, int productreviewid,
        int productid,
        string reviewername,
        DateTime reviewdate,
        string emailaddress,
        int rating,
        string? comments,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductReview]";

        command.Parameters.AddWithValue("@productreviewid", productreviewid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@reviewername", reviewername);
        command.Parameters.AddWithValue("@reviewdate", reviewdate);
        command.Parameters.AddWithValue("@emailaddress", emailaddress);
        command.Parameters.AddWithValue("@rating", rating);
        command.Parameters.AddWithValue("@comments", (object?)comments ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductreview(SqlConnection sqlConnection, Types.Production.ProductreviewDataType data )
    {
        return UpdateProductreview( sqlConnection, 
            data.Productreviewid,
            data.Productid,
            data.Reviewername,
            data.Reviewdate,
            data.Emailaddress,
            data.Rating,
            data.Comments,
            data.Modifieddate );
    }

    public static bool DeleteProductreview(SqlConnection sqlConnection, int productreviewid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductReview]";

        command.Parameters.AddWithValue("@productreviewid", productreviewid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductreview(SqlConnection sqlConnection, Types.Production.ProductreviewDataType data )
    {
        return DeleteProductreview( sqlConnection, 
            data.Productreviewid );
    }

    public static bool InsertProductsubcategory(SqlConnection sqlConnection, int productsubcategoryid,
        int productcategoryid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductSubcategory]";

        command.Parameters.AddWithValue("@productsubcategoryid", productsubcategoryid);
        command.Parameters.AddWithValue("@productcategoryid", productcategoryid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductsubcategory(SqlConnection sqlConnection, Types.Production.ProductsubcategoryDataType data )
    {
        return InsertProductsubcategory( sqlConnection, 
            data.Productsubcategoryid,
            data.Productcategoryid,
            data.Name,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateProductsubcategory(SqlConnection sqlConnection, int productsubcategoryid,
        int productcategoryid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductSubcategory]";

        command.Parameters.AddWithValue("@productsubcategoryid", productsubcategoryid);
        command.Parameters.AddWithValue("@productcategoryid", productcategoryid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductsubcategory(SqlConnection sqlConnection, Types.Production.ProductsubcategoryDataType data )
    {
        return UpdateProductsubcategory( sqlConnection, 
            data.Productsubcategoryid,
            data.Productcategoryid,
            data.Name,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteProductsubcategory(SqlConnection sqlConnection, int productsubcategoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductSubcategory]";

        command.Parameters.AddWithValue("@productsubcategoryid", productsubcategoryid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductsubcategory(SqlConnection sqlConnection, Types.Production.ProductsubcategoryDataType data )
    {
        return DeleteProductsubcategory( sqlConnection, 
            data.Productsubcategoryid );
    }

    public static bool InsertScrapreason(SqlConnection sqlConnection, short scrapreasonid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertScrapReason]";

        command.Parameters.AddWithValue("@scrapreasonid", scrapreasonid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertScrapreason(SqlConnection sqlConnection, Types.Production.ScrapreasonDataType data )
    {
        return InsertScrapreason( sqlConnection, 
            data.Scrapreasonid,
            data.Name,
            data.Modifieddate );
    }

    public static bool UpdateScrapreason(SqlConnection sqlConnection, short scrapreasonid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateScrapReason]";

        command.Parameters.AddWithValue("@scrapreasonid", scrapreasonid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateScrapreason(SqlConnection sqlConnection, Types.Production.ScrapreasonDataType data )
    {
        return UpdateScrapreason( sqlConnection, 
            data.Scrapreasonid,
            data.Name,
            data.Modifieddate );
    }

    public static bool DeleteScrapreason(SqlConnection sqlConnection, short scrapreasonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteScrapReason]";

        command.Parameters.AddWithValue("@scrapreasonid", scrapreasonid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteScrapreason(SqlConnection sqlConnection, Types.Production.ScrapreasonDataType data )
    {
        return DeleteScrapreason( sqlConnection, 
            data.Scrapreasonid );
    }

    public static bool InsertTransactionhistory(SqlConnection sqlConnection, int transactionid,
        int productid,
        int referenceorderid,
        int referenceorderlineid,
        DateTime transactiondate,
        string transactiontype,
        int quantity,
        decimal actualcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertTransactionHistory]";

        command.Parameters.AddWithValue("@transactionid", transactionid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@referenceorderid", referenceorderid);
        command.Parameters.AddWithValue("@referenceorderlineid", referenceorderlineid);
        command.Parameters.AddWithValue("@transactiondate", transactiondate);
        command.Parameters.AddWithValue("@transactiontype", transactiontype);
        command.Parameters.AddWithValue("@quantity", quantity);
        command.Parameters.AddWithValue("@actualcost", actualcost);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertTransactionhistory(SqlConnection sqlConnection, Types.Production.TransactionhistoryDataType data )
    {
        return InsertTransactionhistory( sqlConnection, 
            data.Transactionid,
            data.Productid,
            data.Referenceorderid,
            data.Referenceorderlineid,
            data.Transactiondate,
            data.Transactiontype,
            data.Quantity,
            data.Actualcost,
            data.Modifieddate );
    }

    public static bool UpdateTransactionhistory(SqlConnection sqlConnection, int transactionid,
        int productid,
        int referenceorderid,
        int referenceorderlineid,
        DateTime transactiondate,
        string transactiontype,
        int quantity,
        decimal actualcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateTransactionHistory]";

        command.Parameters.AddWithValue("@transactionid", transactionid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@referenceorderid", referenceorderid);
        command.Parameters.AddWithValue("@referenceorderlineid", referenceorderlineid);
        command.Parameters.AddWithValue("@transactiondate", transactiondate);
        command.Parameters.AddWithValue("@transactiontype", transactiontype);
        command.Parameters.AddWithValue("@quantity", quantity);
        command.Parameters.AddWithValue("@actualcost", actualcost);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateTransactionhistory(SqlConnection sqlConnection, Types.Production.TransactionhistoryDataType data )
    {
        return UpdateTransactionhistory( sqlConnection, 
            data.Transactionid,
            data.Productid,
            data.Referenceorderid,
            data.Referenceorderlineid,
            data.Transactiondate,
            data.Transactiontype,
            data.Quantity,
            data.Actualcost,
            data.Modifieddate );
    }

    public static bool DeleteTransactionhistory(SqlConnection sqlConnection, int transactionid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteTransactionHistory]";

        command.Parameters.AddWithValue("@transactionid", transactionid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteTransactionhistory(SqlConnection sqlConnection, Types.Production.TransactionhistoryDataType data )
    {
        return DeleteTransactionhistory( sqlConnection, 
            data.Transactionid );
    }

    public static bool InsertTransactionhistoryarchive(SqlConnection sqlConnection, int transactionid,
        int productid,
        int referenceorderid,
        int referenceorderlineid,
        DateTime transactiondate,
        string transactiontype,
        int quantity,
        decimal actualcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertTransactionHistoryArchive]";

        command.Parameters.AddWithValue("@transactionid", transactionid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@referenceorderid", referenceorderid);
        command.Parameters.AddWithValue("@referenceorderlineid", referenceorderlineid);
        command.Parameters.AddWithValue("@transactiondate", transactiondate);
        command.Parameters.AddWithValue("@transactiontype", transactiontype);
        command.Parameters.AddWithValue("@quantity", quantity);
        command.Parameters.AddWithValue("@actualcost", actualcost);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertTransactionhistoryarchive(SqlConnection sqlConnection, Types.Production.TransactionhistoryarchiveDataType data )
    {
        return InsertTransactionhistoryarchive( sqlConnection, 
            data.Transactionid,
            data.Productid,
            data.Referenceorderid,
            data.Referenceorderlineid,
            data.Transactiondate,
            data.Transactiontype,
            data.Quantity,
            data.Actualcost,
            data.Modifieddate );
    }

    public static bool UpdateTransactionhistoryarchive(SqlConnection sqlConnection, int transactionid,
        int productid,
        int referenceorderid,
        int referenceorderlineid,
        DateTime transactiondate,
        string transactiontype,
        int quantity,
        decimal actualcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateTransactionHistoryArchive]";

        command.Parameters.AddWithValue("@transactionid", transactionid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@referenceorderid", referenceorderid);
        command.Parameters.AddWithValue("@referenceorderlineid", referenceorderlineid);
        command.Parameters.AddWithValue("@transactiondate", transactiondate);
        command.Parameters.AddWithValue("@transactiontype", transactiontype);
        command.Parameters.AddWithValue("@quantity", quantity);
        command.Parameters.AddWithValue("@actualcost", actualcost);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateTransactionhistoryarchive(SqlConnection sqlConnection, Types.Production.TransactionhistoryarchiveDataType data )
    {
        return UpdateTransactionhistoryarchive( sqlConnection, 
            data.Transactionid,
            data.Productid,
            data.Referenceorderid,
            data.Referenceorderlineid,
            data.Transactiondate,
            data.Transactiontype,
            data.Quantity,
            data.Actualcost,
            data.Modifieddate );
    }

    public static bool DeleteTransactionhistoryarchive(SqlConnection sqlConnection, int transactionid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteTransactionHistoryArchive]";

        command.Parameters.AddWithValue("@transactionid", transactionid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteTransactionhistoryarchive(SqlConnection sqlConnection, Types.Production.TransactionhistoryarchiveDataType data )
    {
        return DeleteTransactionhistoryarchive( sqlConnection, 
            data.Transactionid );
    }

    public static bool InsertUnitmeasure(SqlConnection sqlConnection, string unitmeasurecode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertUnitMeasure]";

        command.Parameters.AddWithValue("@unitmeasurecode", unitmeasurecode);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertUnitmeasure(SqlConnection sqlConnection, Types.Production.UnitmeasureDataType data )
    {
        return InsertUnitmeasure( sqlConnection, 
            data.Unitmeasurecode,
            data.Name,
            data.Modifieddate );
    }

    public static bool UpdateUnitmeasure(SqlConnection sqlConnection, string unitmeasurecode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateUnitMeasure]";

        command.Parameters.AddWithValue("@unitmeasurecode", unitmeasurecode);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateUnitmeasure(SqlConnection sqlConnection, Types.Production.UnitmeasureDataType data )
    {
        return UpdateUnitmeasure( sqlConnection, 
            data.Unitmeasurecode,
            data.Name,
            data.Modifieddate );
    }

    public static bool DeleteUnitmeasure(SqlConnection sqlConnection, string unitmeasurecode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteUnitMeasure]";

        command.Parameters.AddWithValue("@unitmeasurecode", unitmeasurecode);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteUnitmeasure(SqlConnection sqlConnection, Types.Production.UnitmeasureDataType data )
    {
        return DeleteUnitmeasure( sqlConnection, 
            data.Unitmeasurecode );
    }

    public static bool InsertWorkorder(SqlConnection sqlConnection, int workorderid,
        int productid,
        int orderqty,
        int stockedqty,
        short scrappedqty,
        DateTime startdate,
        DateTime? enddate,
        DateTime duedate,
        short? scrapreasonid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertWorkOrder]";

        command.Parameters.AddWithValue("@workorderid", workorderid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@orderqty", orderqty);
        command.Parameters.AddWithValue("@stockedqty", stockedqty);
        command.Parameters.AddWithValue("@scrappedqty", scrappedqty);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@duedate", duedate);
        command.Parameters.AddWithValue("@scrapreasonid", scrapreasonid.HasValue ? (object)scrapreasonid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertWorkorder(SqlConnection sqlConnection, Types.Production.WorkorderDataType data )
    {
        return InsertWorkorder( sqlConnection, 
            data.Workorderid,
            data.Productid,
            data.Orderqty,
            data.Stockedqty,
            data.Scrappedqty,
            data.Startdate,
            data.Enddate,
            data.Duedate,
            data.Scrapreasonid,
            data.Modifieddate );
    }

    public static bool UpdateWorkorder(SqlConnection sqlConnection, int workorderid,
        int productid,
        int orderqty,
        int stockedqty,
        short scrappedqty,
        DateTime startdate,
        DateTime? enddate,
        DateTime duedate,
        short? scrapreasonid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateWorkOrder]";

        command.Parameters.AddWithValue("@workorderid", workorderid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@orderqty", orderqty);
        command.Parameters.AddWithValue("@stockedqty", stockedqty);
        command.Parameters.AddWithValue("@scrappedqty", scrappedqty);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@duedate", duedate);
        command.Parameters.AddWithValue("@scrapreasonid", scrapreasonid.HasValue ? (object)scrapreasonid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateWorkorder(SqlConnection sqlConnection, Types.Production.WorkorderDataType data )
    {
        return UpdateWorkorder( sqlConnection, 
            data.Workorderid,
            data.Productid,
            data.Orderqty,
            data.Stockedqty,
            data.Scrappedqty,
            data.Startdate,
            data.Enddate,
            data.Duedate,
            data.Scrapreasonid,
            data.Modifieddate );
    }

    public static bool DeleteWorkorder(SqlConnection sqlConnection, int workorderid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteWorkOrder]";

        command.Parameters.AddWithValue("@workorderid", workorderid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteWorkorder(SqlConnection sqlConnection, Types.Production.WorkorderDataType data )
    {
        return DeleteWorkorder( sqlConnection, 
            data.Workorderid );
    }

    public static bool Insert1Workorder(SqlConnection sqlConnection, int workorderid,
        int productid,
        int orderqty,
        int stockedqty,
        short scrappedqty,
        DateTime startdate,
        DateTime? enddate,
        DateTime duedate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Insert1WorkOrder]";

        command.Parameters.AddWithValue("@workorderid", workorderid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@orderqty", orderqty);
        command.Parameters.AddWithValue("@stockedqty", stockedqty);
        command.Parameters.AddWithValue("@scrappedqty", scrappedqty);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@duedate", duedate);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Insert1Workorder(SqlConnection sqlConnection, Types.Production.WorkorderDataType data )
    {
        return Insert1Workorder( sqlConnection, 
            data.Workorderid,
            data.Productid,
            data.Orderqty,
            data.Stockedqty,
            data.Scrappedqty,
            data.Startdate,
            data.Enddate,
            data.Duedate,
            data.Modifieddate );
    }

    public static bool Update1Workorder(SqlConnection sqlConnection, int workorderid,
        int productid,
        int orderqty,
        int stockedqty,
        short scrappedqty,
        DateTime startdate,
        DateTime? enddate,
        DateTime duedate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update1WorkOrder]";

        command.Parameters.AddWithValue("@workorderid", workorderid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@orderqty", orderqty);
        command.Parameters.AddWithValue("@stockedqty", stockedqty);
        command.Parameters.AddWithValue("@scrappedqty", scrappedqty);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@duedate", duedate);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update2Workorder(SqlConnection sqlConnection, int workorderid,
        short? scrapreasonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update2WorkOrder]";

        command.Parameters.AddWithValue("@workorderid", workorderid);
        command.Parameters.AddWithValue("@scrapreasonid", scrapreasonid.HasValue ? (object)scrapreasonid.Value : (object)DBNull.Value);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update1Workorder(SqlConnection sqlConnection, Types.Production.WorkorderDataType data )
    {
        return Update1Workorder( sqlConnection, 
            data.Workorderid,
            data.Productid,
            data.Orderqty,
            data.Stockedqty,
            data.Scrappedqty,
            data.Startdate,
            data.Enddate,
            data.Duedate,
            data.Modifieddate );
    }

    public static bool Update2Workorder(SqlConnection sqlConnection, Types.Production.WorkorderDataType data )
    {
        return Update2Workorder( sqlConnection, 
            data.Workorderid,
            data.Scrapreasonid );
    }

    public static bool InsertWorkorderrouting(SqlConnection sqlConnection, int workorderid,
        int productid,
        short operationsequence,
        short locationid,
        DateTime scheduledstartdate,
        DateTime scheduledenddate,
        DateTime? actualstartdate,
        DateTime? actualenddate,
        decimal? actualresourcehrs,
        decimal plannedcost,
        decimal? actualcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertWorkOrderRouting]";

        command.Parameters.AddWithValue("@workorderid", workorderid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@operationsequence", operationsequence);
        command.Parameters.AddWithValue("@locationid", locationid);
        command.Parameters.AddWithValue("@scheduledstartdate", scheduledstartdate);
        command.Parameters.AddWithValue("@scheduledenddate", scheduledenddate);
        command.Parameters.AddWithValue("@actualstartdate", actualstartdate.HasValue ? (object)actualstartdate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@actualenddate", actualenddate.HasValue ? (object)actualenddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@actualresourcehrs", actualresourcehrs.HasValue ? (object)actualresourcehrs.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@plannedcost", plannedcost);
        command.Parameters.AddWithValue("@actualcost", actualcost.HasValue ? (object)actualcost.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertWorkorderrouting(SqlConnection sqlConnection, Types.Production.WorkorderroutingDataType data )
    {
        return InsertWorkorderrouting( sqlConnection, 
            data.Workorderid,
            data.Productid,
            data.Operationsequence,
            data.Locationid,
            data.Scheduledstartdate,
            data.Scheduledenddate,
            data.Actualstartdate,
            data.Actualenddate,
            data.Actualresourcehrs,
            data.Plannedcost,
            data.Actualcost,
            data.Modifieddate );
    }

    public static bool UpdateWorkorderrouting(SqlConnection sqlConnection, int workorderid,
        int productid,
        short operationsequence,
        short locationid,
        DateTime scheduledstartdate,
        DateTime scheduledenddate,
        DateTime? actualstartdate,
        DateTime? actualenddate,
        decimal? actualresourcehrs,
        decimal plannedcost,
        decimal? actualcost,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateWorkOrderRouting]";

        command.Parameters.AddWithValue("@workorderid", workorderid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@operationsequence", operationsequence);
        command.Parameters.AddWithValue("@locationid", locationid);
        command.Parameters.AddWithValue("@scheduledstartdate", scheduledstartdate);
        command.Parameters.AddWithValue("@scheduledenddate", scheduledenddate);
        command.Parameters.AddWithValue("@actualstartdate", actualstartdate.HasValue ? (object)actualstartdate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@actualenddate", actualenddate.HasValue ? (object)actualenddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@actualresourcehrs", actualresourcehrs.HasValue ? (object)actualresourcehrs.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@plannedcost", plannedcost);
        command.Parameters.AddWithValue("@actualcost", actualcost.HasValue ? (object)actualcost.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateWorkorderrouting(SqlConnection sqlConnection, Types.Production.WorkorderroutingDataType data )
    {
        return UpdateWorkorderrouting( sqlConnection, 
            data.Workorderid,
            data.Productid,
            data.Operationsequence,
            data.Locationid,
            data.Scheduledstartdate,
            data.Scheduledenddate,
            data.Actualstartdate,
            data.Actualenddate,
            data.Actualresourcehrs,
            data.Plannedcost,
            data.Actualcost,
            data.Modifieddate );
    }

    public static bool DeleteWorkorderrouting(SqlConnection sqlConnection, int workorderid,
        int productid,
        short operationsequence)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteWorkOrderRouting]";

        command.Parameters.AddWithValue("@workorderid", workorderid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@operationsequence", operationsequence);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteWorkorderrouting(SqlConnection sqlConnection, Types.Production.WorkorderroutingDataType data )
    {
        return DeleteWorkorderrouting( sqlConnection, 
            data.Workorderid,
            data.Productid,
            data.Operationsequence );
    }

    public static bool InsertProductvendor(SqlConnection sqlConnection, int productid,
        int businessentityid,
        int averageleadtime,
        decimal standardprice,
        decimal? lastreceiptcost,
        DateTime? lastreceiptdate,
        int minorderqty,
        int maxorderqty,
        int? onorderqty,
        string unitmeasurecode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[InsertProductVendor]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@averageleadtime", averageleadtime);
        command.Parameters.AddWithValue("@standardprice", standardprice);
        command.Parameters.AddWithValue("@lastreceiptcost", lastreceiptcost.HasValue ? (object)lastreceiptcost.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@lastreceiptdate", lastreceiptdate.HasValue ? (object)lastreceiptdate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@minorderqty", minorderqty);
        command.Parameters.AddWithValue("@maxorderqty", maxorderqty);
        command.Parameters.AddWithValue("@onorderqty", onorderqty.HasValue ? (object)onorderqty.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@unitmeasurecode", unitmeasurecode);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertProductvendor(SqlConnection sqlConnection, Types.Purchasing.ProductvendorDataType data )
    {
        return InsertProductvendor( sqlConnection, 
            data.Productid,
            data.Businessentityid,
            data.Averageleadtime,
            data.Standardprice,
            data.Lastreceiptcost,
            data.Lastreceiptdate,
            data.Minorderqty,
            data.Maxorderqty,
            data.Onorderqty,
            data.Unitmeasurecode,
            data.Modifieddate );
    }

    public static bool UpdateProductvendor(SqlConnection sqlConnection, int productid,
        int businessentityid,
        int averageleadtime,
        decimal standardprice,
        decimal? lastreceiptcost,
        DateTime? lastreceiptdate,
        int minorderqty,
        int maxorderqty,
        int? onorderqty,
        string unitmeasurecode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[UpdateProductVendor]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@averageleadtime", averageleadtime);
        command.Parameters.AddWithValue("@standardprice", standardprice);
        command.Parameters.AddWithValue("@lastreceiptcost", lastreceiptcost.HasValue ? (object)lastreceiptcost.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@lastreceiptdate", lastreceiptdate.HasValue ? (object)lastreceiptdate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@minorderqty", minorderqty);
        command.Parameters.AddWithValue("@maxorderqty", maxorderqty);
        command.Parameters.AddWithValue("@onorderqty", onorderqty.HasValue ? (object)onorderqty.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@unitmeasurecode", unitmeasurecode);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateProductvendor(SqlConnection sqlConnection, Types.Purchasing.ProductvendorDataType data )
    {
        return UpdateProductvendor( sqlConnection, 
            data.Productid,
            data.Businessentityid,
            data.Averageleadtime,
            data.Standardprice,
            data.Lastreceiptcost,
            data.Lastreceiptdate,
            data.Minorderqty,
            data.Maxorderqty,
            data.Onorderqty,
            data.Unitmeasurecode,
            data.Modifieddate );
    }

    public static bool DeleteProductvendor(SqlConnection sqlConnection, int productid,
        int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeleteProductVendor]";

        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@businessentityid", businessentityid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteProductvendor(SqlConnection sqlConnection, Types.Purchasing.ProductvendorDataType data )
    {
        return DeleteProductvendor( sqlConnection, 
            data.Productid,
            data.Businessentityid );
    }

    public static bool InsertPurchaseorderdetail(SqlConnection sqlConnection, int purchaseorderid,
        int purchaseorderdetailid,
        DateTime duedate,
        short orderqty,
        int productid,
        decimal unitprice,
        decimal linetotal,
        decimal receivedqty,
        decimal rejectedqty,
        decimal stockedqty,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[InsertPurchaseOrderDetail]";

        command.Parameters.AddWithValue("@purchaseorderid", purchaseorderid);
        command.Parameters.AddWithValue("@purchaseorderdetailid", purchaseorderdetailid);
        command.Parameters.AddWithValue("@duedate", duedate);
        command.Parameters.AddWithValue("@orderqty", orderqty);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@unitprice", unitprice);
        command.Parameters.AddWithValue("@linetotal", linetotal);
        command.Parameters.AddWithValue("@receivedqty", receivedqty);
        command.Parameters.AddWithValue("@rejectedqty", rejectedqty);
        command.Parameters.AddWithValue("@stockedqty", stockedqty);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertPurchaseorderdetail(SqlConnection sqlConnection, Types.Purchasing.PurchaseorderdetailDataType data )
    {
        return InsertPurchaseorderdetail( sqlConnection, 
            data.Purchaseorderid,
            data.Purchaseorderdetailid,
            data.Duedate,
            data.Orderqty,
            data.Productid,
            data.Unitprice,
            data.Linetotal,
            data.Receivedqty,
            data.Rejectedqty,
            data.Stockedqty,
            data.Modifieddate );
    }

    public static bool UpdatePurchaseorderdetail(SqlConnection sqlConnection, int purchaseorderid,
        int purchaseorderdetailid,
        DateTime duedate,
        short orderqty,
        int productid,
        decimal unitprice,
        decimal linetotal,
        decimal receivedqty,
        decimal rejectedqty,
        decimal stockedqty,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[UpdatePurchaseOrderDetail]";

        command.Parameters.AddWithValue("@purchaseorderid", purchaseorderid);
        command.Parameters.AddWithValue("@purchaseorderdetailid", purchaseorderdetailid);
        command.Parameters.AddWithValue("@duedate", duedate);
        command.Parameters.AddWithValue("@orderqty", orderqty);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@unitprice", unitprice);
        command.Parameters.AddWithValue("@linetotal", linetotal);
        command.Parameters.AddWithValue("@receivedqty", receivedqty);
        command.Parameters.AddWithValue("@rejectedqty", rejectedqty);
        command.Parameters.AddWithValue("@stockedqty", stockedqty);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdatePurchaseorderdetail(SqlConnection sqlConnection, Types.Purchasing.PurchaseorderdetailDataType data )
    {
        return UpdatePurchaseorderdetail( sqlConnection, 
            data.Purchaseorderid,
            data.Purchaseorderdetailid,
            data.Duedate,
            data.Orderqty,
            data.Productid,
            data.Unitprice,
            data.Linetotal,
            data.Receivedqty,
            data.Rejectedqty,
            data.Stockedqty,
            data.Modifieddate );
    }

    public static bool DeletePurchaseorderdetail(SqlConnection sqlConnection, int purchaseorderid,
        int purchaseorderdetailid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeletePurchaseOrderDetail]";

        command.Parameters.AddWithValue("@purchaseorderid", purchaseorderid);
        command.Parameters.AddWithValue("@purchaseorderdetailid", purchaseorderdetailid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeletePurchaseorderdetail(SqlConnection sqlConnection, Types.Purchasing.PurchaseorderdetailDataType data )
    {
        return DeletePurchaseorderdetail( sqlConnection, 
            data.Purchaseorderid,
            data.Purchaseorderdetailid );
    }

    public static bool InsertPurchaseorderheader(SqlConnection sqlConnection, int purchaseorderid,
        byte revisionnumber,
        byte status,
        int employeeid,
        int vendorid,
        int shipmethodid,
        DateTime orderdate,
        DateTime? shipdate,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        decimal totaldue,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[InsertPurchaseOrderHeader]";

        command.Parameters.AddWithValue("@purchaseorderid", purchaseorderid);
        command.Parameters.AddWithValue("@revisionnumber", revisionnumber);
        command.Parameters.AddWithValue("@status", status);
        command.Parameters.AddWithValue("@employeeid", employeeid);
        command.Parameters.AddWithValue("@vendorid", vendorid);
        command.Parameters.AddWithValue("@shipmethodid", shipmethodid);
        command.Parameters.AddWithValue("@orderdate", orderdate);
        command.Parameters.AddWithValue("@shipdate", shipdate.HasValue ? (object)shipdate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@subtotal", subtotal);
        command.Parameters.AddWithValue("@taxamt", taxamt);
        command.Parameters.AddWithValue("@freight", freight);
        command.Parameters.AddWithValue("@totaldue", totaldue);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertPurchaseorderheader(SqlConnection sqlConnection, Types.Purchasing.PurchaseorderheaderDataType data )
    {
        return InsertPurchaseorderheader( sqlConnection, 
            data.Purchaseorderid,
            data.Revisionnumber,
            data.Status,
            data.Employeeid,
            data.Vendorid,
            data.Shipmethodid,
            data.Orderdate,
            data.Shipdate,
            data.Subtotal,
            data.Taxamt,
            data.Freight,
            data.Totaldue,
            data.Modifieddate );
    }

    public static bool UpdatePurchaseorderheader(SqlConnection sqlConnection, int purchaseorderid,
        byte revisionnumber,
        byte status,
        int employeeid,
        int vendorid,
        int shipmethodid,
        DateTime orderdate,
        DateTime? shipdate,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        decimal totaldue,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[UpdatePurchaseOrderHeader]";

        command.Parameters.AddWithValue("@purchaseorderid", purchaseorderid);
        command.Parameters.AddWithValue("@revisionnumber", revisionnumber);
        command.Parameters.AddWithValue("@status", status);
        command.Parameters.AddWithValue("@employeeid", employeeid);
        command.Parameters.AddWithValue("@vendorid", vendorid);
        command.Parameters.AddWithValue("@shipmethodid", shipmethodid);
        command.Parameters.AddWithValue("@orderdate", orderdate);
        command.Parameters.AddWithValue("@shipdate", shipdate.HasValue ? (object)shipdate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@subtotal", subtotal);
        command.Parameters.AddWithValue("@taxamt", taxamt);
        command.Parameters.AddWithValue("@freight", freight);
        command.Parameters.AddWithValue("@totaldue", totaldue);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdatePurchaseorderheader(SqlConnection sqlConnection, Types.Purchasing.PurchaseorderheaderDataType data )
    {
        return UpdatePurchaseorderheader( sqlConnection, 
            data.Purchaseorderid,
            data.Revisionnumber,
            data.Status,
            data.Employeeid,
            data.Vendorid,
            data.Shipmethodid,
            data.Orderdate,
            data.Shipdate,
            data.Subtotal,
            data.Taxamt,
            data.Freight,
            data.Totaldue,
            data.Modifieddate );
    }

    public static bool DeletePurchaseorderheader(SqlConnection sqlConnection, int purchaseorderid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeletePurchaseOrderHeader]";

        command.Parameters.AddWithValue("@purchaseorderid", purchaseorderid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeletePurchaseorderheader(SqlConnection sqlConnection, Types.Purchasing.PurchaseorderheaderDataType data )
    {
        return DeletePurchaseorderheader( sqlConnection, 
            data.Purchaseorderid );
    }

    public static bool InsertShipmethod(SqlConnection sqlConnection, int shipmethodid,
        string name,
        decimal shipbase,
        decimal shiprate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[InsertShipMethod]";

        command.Parameters.AddWithValue("@shipmethodid", shipmethodid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@shipbase", shipbase);
        command.Parameters.AddWithValue("@shiprate", shiprate);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertShipmethod(SqlConnection sqlConnection, Types.Purchasing.ShipmethodDataType data )
    {
        return InsertShipmethod( sqlConnection, 
            data.Shipmethodid,
            data.Name,
            data.Shipbase,
            data.Shiprate,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateShipmethod(SqlConnection sqlConnection, int shipmethodid,
        string name,
        decimal shipbase,
        decimal shiprate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[UpdateShipMethod]";

        command.Parameters.AddWithValue("@shipmethodid", shipmethodid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@shipbase", shipbase);
        command.Parameters.AddWithValue("@shiprate", shiprate);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateShipmethod(SqlConnection sqlConnection, Types.Purchasing.ShipmethodDataType data )
    {
        return UpdateShipmethod( sqlConnection, 
            data.Shipmethodid,
            data.Name,
            data.Shipbase,
            data.Shiprate,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteShipmethod(SqlConnection sqlConnection, int shipmethodid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeleteShipMethod]";

        command.Parameters.AddWithValue("@shipmethodid", shipmethodid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteShipmethod(SqlConnection sqlConnection, Types.Purchasing.ShipmethodDataType data )
    {
        return DeleteShipmethod( sqlConnection, 
            data.Shipmethodid );
    }

    public static bool InsertVendor(SqlConnection sqlConnection, int businessentityid,
        string accountnumber,
        string name,
        byte creditrating,
        bool preferredvendorstatus,
        bool activeflag,
        string? purchasingwebserviceurl,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[InsertVendor]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@accountnumber", accountnumber);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@creditrating", creditrating);
        command.Parameters.AddWithValue("@preferredvendorstatus", preferredvendorstatus);
        command.Parameters.AddWithValue("@activeflag", activeflag);
        command.Parameters.AddWithValue("@purchasingwebserviceurl", (object?)purchasingwebserviceurl ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertVendor(SqlConnection sqlConnection, Types.Purchasing.VendorDataType data )
    {
        return InsertVendor( sqlConnection, 
            data.Businessentityid,
            data.Accountnumber,
            data.Name,
            data.Creditrating,
            data.Preferredvendorstatus,
            data.Activeflag,
            data.Purchasingwebserviceurl,
            data.Modifieddate );
    }

    public static bool UpdateVendor(SqlConnection sqlConnection, int businessentityid,
        string accountnumber,
        string name,
        byte creditrating,
        bool preferredvendorstatus,
        bool activeflag,
        string? purchasingwebserviceurl,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[UpdateVendor]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@accountnumber", accountnumber);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@creditrating", creditrating);
        command.Parameters.AddWithValue("@preferredvendorstatus", preferredvendorstatus);
        command.Parameters.AddWithValue("@activeflag", activeflag);
        command.Parameters.AddWithValue("@purchasingwebserviceurl", (object?)purchasingwebserviceurl ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateVendor(SqlConnection sqlConnection, Types.Purchasing.VendorDataType data )
    {
        return UpdateVendor( sqlConnection, 
            data.Businessentityid,
            data.Accountnumber,
            data.Name,
            data.Creditrating,
            data.Preferredvendorstatus,
            data.Activeflag,
            data.Purchasingwebserviceurl,
            data.Modifieddate );
    }

    public static bool DeleteVendor(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeleteVendor]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteVendor(SqlConnection sqlConnection, Types.Purchasing.VendorDataType data )
    {
        return DeleteVendor( sqlConnection, 
            data.Businessentityid );
    }

    public static bool InsertCountryregioncurrency(SqlConnection sqlConnection, string countryregioncode,
        string currencycode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertCountryRegionCurrency]";

        command.Parameters.AddWithValue("@countryregioncode", countryregioncode);
        command.Parameters.AddWithValue("@currencycode", currencycode);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertCountryregioncurrency(SqlConnection sqlConnection, Types.Sales.CountryregioncurrencyDataType data )
    {
        return InsertCountryregioncurrency( sqlConnection, 
            data.Countryregioncode,
            data.Currencycode,
            data.Modifieddate );
    }

    public static bool UpdateCountryregioncurrency(SqlConnection sqlConnection, string countryregioncode,
        string currencycode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateCountryRegionCurrency]";

        command.Parameters.AddWithValue("@countryregioncode", countryregioncode);
        command.Parameters.AddWithValue("@currencycode", currencycode);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateCountryregioncurrency(SqlConnection sqlConnection, Types.Sales.CountryregioncurrencyDataType data )
    {
        return UpdateCountryregioncurrency( sqlConnection, 
            data.Countryregioncode,
            data.Currencycode,
            data.Modifieddate );
    }

    public static bool DeleteCountryregioncurrency(SqlConnection sqlConnection, string countryregioncode,
        string currencycode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCountryRegionCurrency]";

        command.Parameters.AddWithValue("@countryregioncode", countryregioncode);
        command.Parameters.AddWithValue("@currencycode", currencycode);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteCountryregioncurrency(SqlConnection sqlConnection, Types.Sales.CountryregioncurrencyDataType data )
    {
        return DeleteCountryregioncurrency( sqlConnection, 
            data.Countryregioncode,
            data.Currencycode );
    }

    public static bool InsertCreditcard(SqlConnection sqlConnection, int creditcardid,
        string cardtype,
        string cardnumber,
        byte expmonth,
        short expyear,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertCreditCard]";

        command.Parameters.AddWithValue("@creditcardid", creditcardid);
        command.Parameters.AddWithValue("@cardtype", cardtype);
        command.Parameters.AddWithValue("@cardnumber", cardnumber);
        command.Parameters.AddWithValue("@expmonth", expmonth);
        command.Parameters.AddWithValue("@expyear", expyear);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertCreditcard(SqlConnection sqlConnection, Types.Sales.CreditcardDataType data )
    {
        return InsertCreditcard( sqlConnection, 
            data.Creditcardid,
            data.Cardtype,
            data.Cardnumber,
            data.Expmonth,
            data.Expyear,
            data.Modifieddate );
    }

    public static bool UpdateCreditcard(SqlConnection sqlConnection, int creditcardid,
        string cardtype,
        string cardnumber,
        byte expmonth,
        short expyear,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateCreditCard]";

        command.Parameters.AddWithValue("@creditcardid", creditcardid);
        command.Parameters.AddWithValue("@cardtype", cardtype);
        command.Parameters.AddWithValue("@cardnumber", cardnumber);
        command.Parameters.AddWithValue("@expmonth", expmonth);
        command.Parameters.AddWithValue("@expyear", expyear);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateCreditcard(SqlConnection sqlConnection, Types.Sales.CreditcardDataType data )
    {
        return UpdateCreditcard( sqlConnection, 
            data.Creditcardid,
            data.Cardtype,
            data.Cardnumber,
            data.Expmonth,
            data.Expyear,
            data.Modifieddate );
    }

    public static bool DeleteCreditcard(SqlConnection sqlConnection, int creditcardid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCreditCard]";

        command.Parameters.AddWithValue("@creditcardid", creditcardid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteCreditcard(SqlConnection sqlConnection, Types.Sales.CreditcardDataType data )
    {
        return DeleteCreditcard( sqlConnection, 
            data.Creditcardid );
    }

    public static bool InsertCurrency(SqlConnection sqlConnection, string currencycode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertCurrency]";

        command.Parameters.AddWithValue("@currencycode", currencycode);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertCurrency(SqlConnection sqlConnection, Types.Sales.CurrencyDataType data )
    {
        return InsertCurrency( sqlConnection, 
            data.Currencycode,
            data.Name,
            data.Modifieddate );
    }

    public static bool UpdateCurrency(SqlConnection sqlConnection, string currencycode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateCurrency]";

        command.Parameters.AddWithValue("@currencycode", currencycode);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateCurrency(SqlConnection sqlConnection, Types.Sales.CurrencyDataType data )
    {
        return UpdateCurrency( sqlConnection, 
            data.Currencycode,
            data.Name,
            data.Modifieddate );
    }

    public static bool DeleteCurrency(SqlConnection sqlConnection, string currencycode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCurrency]";

        command.Parameters.AddWithValue("@currencycode", currencycode);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteCurrency(SqlConnection sqlConnection, Types.Sales.CurrencyDataType data )
    {
        return DeleteCurrency( sqlConnection, 
            data.Currencycode );
    }

    public static bool InsertCurrencyrate(SqlConnection sqlConnection, int currencyrateid,
        DateTime currencyratedate,
        string fromcurrencycode,
        string tocurrencycode,
        decimal averagerate,
        decimal endofdayrate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertCurrencyRate]";

        command.Parameters.AddWithValue("@currencyrateid", currencyrateid);
        command.Parameters.AddWithValue("@currencyratedate", currencyratedate);
        command.Parameters.AddWithValue("@fromcurrencycode", fromcurrencycode);
        command.Parameters.AddWithValue("@tocurrencycode", tocurrencycode);
        command.Parameters.AddWithValue("@averagerate", averagerate);
        command.Parameters.AddWithValue("@endofdayrate", endofdayrate);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertCurrencyrate(SqlConnection sqlConnection, Types.Sales.CurrencyrateDataType data )
    {
        return InsertCurrencyrate( sqlConnection, 
            data.Currencyrateid,
            data.Currencyratedate,
            data.Fromcurrencycode,
            data.Tocurrencycode,
            data.Averagerate,
            data.Endofdayrate,
            data.Modifieddate );
    }

    public static bool UpdateCurrencyrate(SqlConnection sqlConnection, int currencyrateid,
        DateTime currencyratedate,
        string fromcurrencycode,
        string tocurrencycode,
        decimal averagerate,
        decimal endofdayrate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateCurrencyRate]";

        command.Parameters.AddWithValue("@currencyrateid", currencyrateid);
        command.Parameters.AddWithValue("@currencyratedate", currencyratedate);
        command.Parameters.AddWithValue("@fromcurrencycode", fromcurrencycode);
        command.Parameters.AddWithValue("@tocurrencycode", tocurrencycode);
        command.Parameters.AddWithValue("@averagerate", averagerate);
        command.Parameters.AddWithValue("@endofdayrate", endofdayrate);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateCurrencyrate(SqlConnection sqlConnection, Types.Sales.CurrencyrateDataType data )
    {
        return UpdateCurrencyrate( sqlConnection, 
            data.Currencyrateid,
            data.Currencyratedate,
            data.Fromcurrencycode,
            data.Tocurrencycode,
            data.Averagerate,
            data.Endofdayrate,
            data.Modifieddate );
    }

    public static bool DeleteCurrencyrate(SqlConnection sqlConnection, int currencyrateid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCurrencyRate]";

        command.Parameters.AddWithValue("@currencyrateid", currencyrateid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteCurrencyrate(SqlConnection sqlConnection, Types.Sales.CurrencyrateDataType data )
    {
        return DeleteCurrencyrate( sqlConnection, 
            data.Currencyrateid );
    }

    public static bool InsertCustomer(SqlConnection sqlConnection, int customerid,
        int? personid,
        int? storeid,
        int? territoryid,
        string accountnumber,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertCustomer]";

        command.Parameters.AddWithValue("@customerid", customerid);
        command.Parameters.AddWithValue("@personid", personid.HasValue ? (object)personid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@storeid", storeid.HasValue ? (object)storeid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@territoryid", territoryid.HasValue ? (object)territoryid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@accountnumber", accountnumber);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertCustomer(SqlConnection sqlConnection, Types.Sales.CustomerDataType data )
    {
        return InsertCustomer( sqlConnection, 
            data.Customerid,
            data.Personid,
            data.Storeid,
            data.Territoryid,
            data.Accountnumber,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateCustomer(SqlConnection sqlConnection, int customerid,
        int? personid,
        int? storeid,
        int? territoryid,
        string accountnumber,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateCustomer]";

        command.Parameters.AddWithValue("@customerid", customerid);
        command.Parameters.AddWithValue("@personid", personid.HasValue ? (object)personid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@storeid", storeid.HasValue ? (object)storeid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@territoryid", territoryid.HasValue ? (object)territoryid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@accountnumber", accountnumber);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateCustomer(SqlConnection sqlConnection, Types.Sales.CustomerDataType data )
    {
        return UpdateCustomer( sqlConnection, 
            data.Customerid,
            data.Personid,
            data.Storeid,
            data.Territoryid,
            data.Accountnumber,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteCustomer(SqlConnection sqlConnection, int customerid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCustomer]";

        command.Parameters.AddWithValue("@customerid", customerid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteCustomer(SqlConnection sqlConnection, Types.Sales.CustomerDataType data )
    {
        return DeleteCustomer( sqlConnection, 
            data.Customerid );
    }

    public static bool Insert1Customer(SqlConnection sqlConnection, int customerid,
        string accountnumber,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Insert1Customer]";

        command.Parameters.AddWithValue("@customerid", customerid);
        command.Parameters.AddWithValue("@accountnumber", accountnumber);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Insert1Customer(SqlConnection sqlConnection, Types.Sales.CustomerDataType data )
    {
        return Insert1Customer( sqlConnection, 
            data.Customerid,
            data.Accountnumber,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool Update1Customer(SqlConnection sqlConnection, int customerid,
        string accountnumber,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update1Customer]";

        command.Parameters.AddWithValue("@customerid", customerid);
        command.Parameters.AddWithValue("@accountnumber", accountnumber);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update2Customer(SqlConnection sqlConnection, int customerid,
        int? personid,
        int? storeid,
        int? territoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update2Customer]";

        command.Parameters.AddWithValue("@customerid", customerid);
        command.Parameters.AddWithValue("@personid", personid.HasValue ? (object)personid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@storeid", storeid.HasValue ? (object)storeid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@territoryid", territoryid.HasValue ? (object)territoryid.Value : (object)DBNull.Value);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update1Customer(SqlConnection sqlConnection, Types.Sales.CustomerDataType data )
    {
        return Update1Customer( sqlConnection, 
            data.Customerid,
            data.Accountnumber,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool Update2Customer(SqlConnection sqlConnection, Types.Sales.CustomerDataType data )
    {
        return Update2Customer( sqlConnection, 
            data.Customerid,
            data.Personid,
            data.Storeid,
            data.Territoryid );
    }

    public static bool InsertPersoncreditcard(SqlConnection sqlConnection, int businessentityid,
        int creditcardid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertPersonCreditCard]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@creditcardid", creditcardid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertPersoncreditcard(SqlConnection sqlConnection, Types.Sales.PersoncreditcardDataType data )
    {
        return InsertPersoncreditcard( sqlConnection, 
            data.Businessentityid,
            data.Creditcardid,
            data.Modifieddate );
    }

    public static bool UpdatePersoncreditcard(SqlConnection sqlConnection, int businessentityid,
        int creditcardid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdatePersonCreditCard]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@creditcardid", creditcardid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdatePersoncreditcard(SqlConnection sqlConnection, Types.Sales.PersoncreditcardDataType data )
    {
        return UpdatePersoncreditcard( sqlConnection, 
            data.Businessentityid,
            data.Creditcardid,
            data.Modifieddate );
    }

    public static bool DeletePersoncreditcard(SqlConnection sqlConnection, int businessentityid,
        int creditcardid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeletePersonCreditCard]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@creditcardid", creditcardid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeletePersoncreditcard(SqlConnection sqlConnection, Types.Sales.PersoncreditcardDataType data )
    {
        return DeletePersoncreditcard( sqlConnection, 
            data.Businessentityid,
            data.Creditcardid );
    }

    public static bool InsertSalesorderdetail(SqlConnection sqlConnection, int salesorderid,
        int salesorderdetailid,
        string? carriertrackingnumber,
        short orderqty,
        int productid,
        int specialofferid,
        decimal unitprice,
        decimal unitpricediscount,
        decimal linetotal,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesOrderDetail]";

        command.Parameters.AddWithValue("@salesorderid", salesorderid);
        command.Parameters.AddWithValue("@salesorderdetailid", salesorderdetailid);
        command.Parameters.AddWithValue("@carriertrackingnumber", (object?)carriertrackingnumber ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@orderqty", orderqty);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@specialofferid", specialofferid);
        command.Parameters.AddWithValue("@unitprice", unitprice);
        command.Parameters.AddWithValue("@unitpricediscount", unitpricediscount);
        command.Parameters.AddWithValue("@linetotal", linetotal);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertSalesorderdetail(SqlConnection sqlConnection, Types.Sales.SalesorderdetailDataType data )
    {
        return InsertSalesorderdetail( sqlConnection, 
            data.Salesorderid,
            data.Salesorderdetailid,
            data.Carriertrackingnumber,
            data.Orderqty,
            data.Productid,
            data.Specialofferid,
            data.Unitprice,
            data.Unitpricediscount,
            data.Linetotal,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateSalesorderdetail(SqlConnection sqlConnection, int salesorderid,
        int salesorderdetailid,
        string? carriertrackingnumber,
        short orderqty,
        int productid,
        int specialofferid,
        decimal unitprice,
        decimal unitpricediscount,
        decimal linetotal,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesOrderDetail]";

        command.Parameters.AddWithValue("@salesorderid", salesorderid);
        command.Parameters.AddWithValue("@salesorderdetailid", salesorderdetailid);
        command.Parameters.AddWithValue("@carriertrackingnumber", (object?)carriertrackingnumber ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@orderqty", orderqty);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@specialofferid", specialofferid);
        command.Parameters.AddWithValue("@unitprice", unitprice);
        command.Parameters.AddWithValue("@unitpricediscount", unitpricediscount);
        command.Parameters.AddWithValue("@linetotal", linetotal);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateSalesorderdetail(SqlConnection sqlConnection, Types.Sales.SalesorderdetailDataType data )
    {
        return UpdateSalesorderdetail( sqlConnection, 
            data.Salesorderid,
            data.Salesorderdetailid,
            data.Carriertrackingnumber,
            data.Orderqty,
            data.Productid,
            data.Specialofferid,
            data.Unitprice,
            data.Unitpricediscount,
            data.Linetotal,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteSalesorderdetail(SqlConnection sqlConnection, int salesorderid,
        int salesorderdetailid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesOrderDetail]";

        command.Parameters.AddWithValue("@salesorderid", salesorderid);
        command.Parameters.AddWithValue("@salesorderdetailid", salesorderdetailid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteSalesorderdetail(SqlConnection sqlConnection, Types.Sales.SalesorderdetailDataType data )
    {
        return DeleteSalesorderdetail( sqlConnection, 
            data.Salesorderid,
            data.Salesorderdetailid );
    }

    public static bool InsertSalesorderheader(SqlConnection sqlConnection, int salesorderid,
        byte revisionnumber,
        DateTime orderdate,
        DateTime duedate,
        DateTime? shipdate,
        byte status,
        bool onlineorderflag,
        string salesordernumber,
        string? purchaseordernumber,
        string? accountnumber,
        int customerid,
        int? salespersonid,
        int? territoryid,
        int billtoaddressid,
        int shiptoaddressid,
        int shipmethodid,
        int? creditcardid,
        string? creditcardapprovalcode,
        int? currencyrateid,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        decimal totaldue,
        string? comment,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesOrderHeader]";

        command.Parameters.AddWithValue("@salesorderid", salesorderid);
        command.Parameters.AddWithValue("@revisionnumber", revisionnumber);
        command.Parameters.AddWithValue("@orderdate", orderdate);
        command.Parameters.AddWithValue("@duedate", duedate);
        command.Parameters.AddWithValue("@shipdate", shipdate.HasValue ? (object)shipdate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@status", status);
        command.Parameters.AddWithValue("@onlineorderflag", onlineorderflag);
        command.Parameters.AddWithValue("@salesordernumber", salesordernumber);
        command.Parameters.AddWithValue("@purchaseordernumber", (object?)purchaseordernumber ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@accountnumber", (object?)accountnumber ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@customerid", customerid);
        command.Parameters.AddWithValue("@salespersonid", salespersonid.HasValue ? (object)salespersonid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@territoryid", territoryid.HasValue ? (object)territoryid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@billtoaddressid", billtoaddressid);
        command.Parameters.AddWithValue("@shiptoaddressid", shiptoaddressid);
        command.Parameters.AddWithValue("@shipmethodid", shipmethodid);
        command.Parameters.AddWithValue("@creditcardid", creditcardid.HasValue ? (object)creditcardid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@creditcardapprovalcode", (object?)creditcardapprovalcode ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@currencyrateid", currencyrateid.HasValue ? (object)currencyrateid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@subtotal", subtotal);
        command.Parameters.AddWithValue("@taxamt", taxamt);
        command.Parameters.AddWithValue("@freight", freight);
        command.Parameters.AddWithValue("@totaldue", totaldue);
        command.Parameters.AddWithValue("@comment", (object?)comment ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertSalesorderheader(SqlConnection sqlConnection, Types.Sales.SalesorderheaderDataType data )
    {
        return InsertSalesorderheader( sqlConnection, 
            data.Salesorderid,
            data.Revisionnumber,
            data.Orderdate,
            data.Duedate,
            data.Shipdate,
            data.Status,
            data.Onlineorderflag,
            data.Salesordernumber,
            data.Purchaseordernumber,
            data.Accountnumber,
            data.Customerid,
            data.Salespersonid,
            data.Territoryid,
            data.Billtoaddressid,
            data.Shiptoaddressid,
            data.Shipmethodid,
            data.Creditcardid,
            data.Creditcardapprovalcode,
            data.Currencyrateid,
            data.Subtotal,
            data.Taxamt,
            data.Freight,
            data.Totaldue,
            data.Comment,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateSalesorderheader(SqlConnection sqlConnection, int salesorderid,
        byte revisionnumber,
        DateTime orderdate,
        DateTime duedate,
        DateTime? shipdate,
        byte status,
        bool onlineorderflag,
        string salesordernumber,
        string? purchaseordernumber,
        string? accountnumber,
        int customerid,
        int? salespersonid,
        int? territoryid,
        int billtoaddressid,
        int shiptoaddressid,
        int shipmethodid,
        int? creditcardid,
        string? creditcardapprovalcode,
        int? currencyrateid,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        decimal totaldue,
        string? comment,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesOrderHeader]";

        command.Parameters.AddWithValue("@salesorderid", salesorderid);
        command.Parameters.AddWithValue("@revisionnumber", revisionnumber);
        command.Parameters.AddWithValue("@orderdate", orderdate);
        command.Parameters.AddWithValue("@duedate", duedate);
        command.Parameters.AddWithValue("@shipdate", shipdate.HasValue ? (object)shipdate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@status", status);
        command.Parameters.AddWithValue("@onlineorderflag", onlineorderflag);
        command.Parameters.AddWithValue("@salesordernumber", salesordernumber);
        command.Parameters.AddWithValue("@purchaseordernumber", (object?)purchaseordernumber ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@accountnumber", (object?)accountnumber ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@customerid", customerid);
        command.Parameters.AddWithValue("@salespersonid", salespersonid.HasValue ? (object)salespersonid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@territoryid", territoryid.HasValue ? (object)territoryid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@billtoaddressid", billtoaddressid);
        command.Parameters.AddWithValue("@shiptoaddressid", shiptoaddressid);
        command.Parameters.AddWithValue("@shipmethodid", shipmethodid);
        command.Parameters.AddWithValue("@creditcardid", creditcardid.HasValue ? (object)creditcardid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@creditcardapprovalcode", (object?)creditcardapprovalcode ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@currencyrateid", currencyrateid.HasValue ? (object)currencyrateid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@subtotal", subtotal);
        command.Parameters.AddWithValue("@taxamt", taxamt);
        command.Parameters.AddWithValue("@freight", freight);
        command.Parameters.AddWithValue("@totaldue", totaldue);
        command.Parameters.AddWithValue("@comment", (object?)comment ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateSalesorderheader(SqlConnection sqlConnection, Types.Sales.SalesorderheaderDataType data )
    {
        return UpdateSalesorderheader( sqlConnection, 
            data.Salesorderid,
            data.Revisionnumber,
            data.Orderdate,
            data.Duedate,
            data.Shipdate,
            data.Status,
            data.Onlineorderflag,
            data.Salesordernumber,
            data.Purchaseordernumber,
            data.Accountnumber,
            data.Customerid,
            data.Salespersonid,
            data.Territoryid,
            data.Billtoaddressid,
            data.Shiptoaddressid,
            data.Shipmethodid,
            data.Creditcardid,
            data.Creditcardapprovalcode,
            data.Currencyrateid,
            data.Subtotal,
            data.Taxamt,
            data.Freight,
            data.Totaldue,
            data.Comment,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteSalesorderheader(SqlConnection sqlConnection, int salesorderid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesOrderHeader]";

        command.Parameters.AddWithValue("@salesorderid", salesorderid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteSalesorderheader(SqlConnection sqlConnection, Types.Sales.SalesorderheaderDataType data )
    {
        return DeleteSalesorderheader( sqlConnection, 
            data.Salesorderid );
    }

    public static bool Insert1Salesorderheader(SqlConnection sqlConnection, int salesorderid,
        byte revisionnumber,
        DateTime orderdate,
        DateTime duedate,
        DateTime? shipdate,
        byte status,
        bool onlineorderflag,
        string salesordernumber,
        string? purchaseordernumber,
        string? accountnumber,
        int customerid,
        int billtoaddressid,
        int shiptoaddressid,
        int shipmethodid,
        string? creditcardapprovalcode,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        decimal totaldue,
        string? comment,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Insert1SalesOrderHeader]";

        command.Parameters.AddWithValue("@salesorderid", salesorderid);
        command.Parameters.AddWithValue("@revisionnumber", revisionnumber);
        command.Parameters.AddWithValue("@orderdate", orderdate);
        command.Parameters.AddWithValue("@duedate", duedate);
        command.Parameters.AddWithValue("@shipdate", shipdate.HasValue ? (object)shipdate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@status", status);
        command.Parameters.AddWithValue("@onlineorderflag", onlineorderflag);
        command.Parameters.AddWithValue("@salesordernumber", salesordernumber);
        command.Parameters.AddWithValue("@purchaseordernumber", (object?)purchaseordernumber ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@accountnumber", (object?)accountnumber ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@customerid", customerid);
        command.Parameters.AddWithValue("@billtoaddressid", billtoaddressid);
        command.Parameters.AddWithValue("@shiptoaddressid", shiptoaddressid);
        command.Parameters.AddWithValue("@shipmethodid", shipmethodid);
        command.Parameters.AddWithValue("@creditcardapprovalcode", (object?)creditcardapprovalcode ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@subtotal", subtotal);
        command.Parameters.AddWithValue("@taxamt", taxamt);
        command.Parameters.AddWithValue("@freight", freight);
        command.Parameters.AddWithValue("@totaldue", totaldue);
        command.Parameters.AddWithValue("@comment", (object?)comment ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Insert1Salesorderheader(SqlConnection sqlConnection, Types.Sales.SalesorderheaderDataType data )
    {
        return Insert1Salesorderheader( sqlConnection, 
            data.Salesorderid,
            data.Revisionnumber,
            data.Orderdate,
            data.Duedate,
            data.Shipdate,
            data.Status,
            data.Onlineorderflag,
            data.Salesordernumber,
            data.Purchaseordernumber,
            data.Accountnumber,
            data.Customerid,
            data.Billtoaddressid,
            data.Shiptoaddressid,
            data.Shipmethodid,
            data.Creditcardapprovalcode,
            data.Subtotal,
            data.Taxamt,
            data.Freight,
            data.Totaldue,
            data.Comment,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool Update1Salesorderheader(SqlConnection sqlConnection, int salesorderid,
        byte revisionnumber,
        DateTime orderdate,
        DateTime duedate,
        DateTime? shipdate,
        byte status,
        bool onlineorderflag,
        string salesordernumber,
        string? purchaseordernumber,
        string? accountnumber,
        int customerid,
        int billtoaddressid,
        int shiptoaddressid,
        int shipmethodid,
        string? creditcardapprovalcode,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        decimal totaldue,
        string? comment,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update1SalesOrderHeader]";

        command.Parameters.AddWithValue("@salesorderid", salesorderid);
        command.Parameters.AddWithValue("@revisionnumber", revisionnumber);
        command.Parameters.AddWithValue("@orderdate", orderdate);
        command.Parameters.AddWithValue("@duedate", duedate);
        command.Parameters.AddWithValue("@shipdate", shipdate.HasValue ? (object)shipdate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@status", status);
        command.Parameters.AddWithValue("@onlineorderflag", onlineorderflag);
        command.Parameters.AddWithValue("@salesordernumber", salesordernumber);
        command.Parameters.AddWithValue("@purchaseordernumber", (object?)purchaseordernumber ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@accountnumber", (object?)accountnumber ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@customerid", customerid);
        command.Parameters.AddWithValue("@billtoaddressid", billtoaddressid);
        command.Parameters.AddWithValue("@shiptoaddressid", shiptoaddressid);
        command.Parameters.AddWithValue("@shipmethodid", shipmethodid);
        command.Parameters.AddWithValue("@creditcardapprovalcode", (object?)creditcardapprovalcode ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@subtotal", subtotal);
        command.Parameters.AddWithValue("@taxamt", taxamt);
        command.Parameters.AddWithValue("@freight", freight);
        command.Parameters.AddWithValue("@totaldue", totaldue);
        command.Parameters.AddWithValue("@comment", (object?)comment ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update2Salesorderheader(SqlConnection sqlConnection, int salesorderid,
        int? salespersonid,
        int? territoryid,
        int? creditcardid,
        int? currencyrateid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update2SalesOrderHeader]";

        command.Parameters.AddWithValue("@salesorderid", salesorderid);
        command.Parameters.AddWithValue("@salespersonid", salespersonid.HasValue ? (object)salespersonid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@territoryid", territoryid.HasValue ? (object)territoryid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@creditcardid", creditcardid.HasValue ? (object)creditcardid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@currencyrateid", currencyrateid.HasValue ? (object)currencyrateid.Value : (object)DBNull.Value);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update1Salesorderheader(SqlConnection sqlConnection, Types.Sales.SalesorderheaderDataType data )
    {
        return Update1Salesorderheader( sqlConnection, 
            data.Salesorderid,
            data.Revisionnumber,
            data.Orderdate,
            data.Duedate,
            data.Shipdate,
            data.Status,
            data.Onlineorderflag,
            data.Salesordernumber,
            data.Purchaseordernumber,
            data.Accountnumber,
            data.Customerid,
            data.Billtoaddressid,
            data.Shiptoaddressid,
            data.Shipmethodid,
            data.Creditcardapprovalcode,
            data.Subtotal,
            data.Taxamt,
            data.Freight,
            data.Totaldue,
            data.Comment,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool Update2Salesorderheader(SqlConnection sqlConnection, Types.Sales.SalesorderheaderDataType data )
    {
        return Update2Salesorderheader( sqlConnection, 
            data.Salesorderid,
            data.Salespersonid,
            data.Territoryid,
            data.Creditcardid,
            data.Currencyrateid );
    }

    public static bool InsertSalesorderheadersalesreason(SqlConnection sqlConnection, int salesorderid,
        int salesreasonid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesOrderHeaderSalesReason]";

        command.Parameters.AddWithValue("@salesorderid", salesorderid);
        command.Parameters.AddWithValue("@salesreasonid", salesreasonid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertSalesorderheadersalesreason(SqlConnection sqlConnection, Types.Sales.SalesorderheadersalesreasonDataType data )
    {
        return InsertSalesorderheadersalesreason( sqlConnection, 
            data.Salesorderid,
            data.Salesreasonid,
            data.Modifieddate );
    }

    public static bool UpdateSalesorderheadersalesreason(SqlConnection sqlConnection, int salesorderid,
        int salesreasonid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesOrderHeaderSalesReason]";

        command.Parameters.AddWithValue("@salesorderid", salesorderid);
        command.Parameters.AddWithValue("@salesreasonid", salesreasonid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateSalesorderheadersalesreason(SqlConnection sqlConnection, Types.Sales.SalesorderheadersalesreasonDataType data )
    {
        return UpdateSalesorderheadersalesreason( sqlConnection, 
            data.Salesorderid,
            data.Salesreasonid,
            data.Modifieddate );
    }

    public static bool DeleteSalesorderheadersalesreason(SqlConnection sqlConnection, int salesorderid,
        int salesreasonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesOrderHeaderSalesReason]";

        command.Parameters.AddWithValue("@salesorderid", salesorderid);
        command.Parameters.AddWithValue("@salesreasonid", salesreasonid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteSalesorderheadersalesreason(SqlConnection sqlConnection, Types.Sales.SalesorderheadersalesreasonDataType data )
    {
        return DeleteSalesorderheadersalesreason( sqlConnection, 
            data.Salesorderid,
            data.Salesreasonid );
    }

    public static bool InsertSalesperson(SqlConnection sqlConnection, int businessentityid,
        int? territoryid,
        decimal? salesquota,
        decimal bonus,
        decimal commissionpct,
        decimal salesytd,
        decimal saleslastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesPerson]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@territoryid", territoryid.HasValue ? (object)territoryid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@salesquota", salesquota.HasValue ? (object)salesquota.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@bonus", bonus);
        command.Parameters.AddWithValue("@commissionpct", commissionpct);
        command.Parameters.AddWithValue("@salesytd", salesytd);
        command.Parameters.AddWithValue("@saleslastyear", saleslastyear);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertSalesperson(SqlConnection sqlConnection, Types.Sales.SalespersonDataType data )
    {
        return InsertSalesperson( sqlConnection, 
            data.Businessentityid,
            data.Territoryid,
            data.Salesquota,
            data.Bonus,
            data.Commissionpct,
            data.Salesytd,
            data.Saleslastyear,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateSalesperson(SqlConnection sqlConnection, int businessentityid,
        int? territoryid,
        decimal? salesquota,
        decimal bonus,
        decimal commissionpct,
        decimal salesytd,
        decimal saleslastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesPerson]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@territoryid", territoryid.HasValue ? (object)territoryid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@salesquota", salesquota.HasValue ? (object)salesquota.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@bonus", bonus);
        command.Parameters.AddWithValue("@commissionpct", commissionpct);
        command.Parameters.AddWithValue("@salesytd", salesytd);
        command.Parameters.AddWithValue("@saleslastyear", saleslastyear);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateSalesperson(SqlConnection sqlConnection, Types.Sales.SalespersonDataType data )
    {
        return UpdateSalesperson( sqlConnection, 
            data.Businessentityid,
            data.Territoryid,
            data.Salesquota,
            data.Bonus,
            data.Commissionpct,
            data.Salesytd,
            data.Saleslastyear,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteSalesperson(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesPerson]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteSalesperson(SqlConnection sqlConnection, Types.Sales.SalespersonDataType data )
    {
        return DeleteSalesperson( sqlConnection, 
            data.Businessentityid );
    }

    public static bool Insert1Salesperson(SqlConnection sqlConnection, int businessentityid,
        decimal? salesquota,
        decimal bonus,
        decimal commissionpct,
        decimal salesytd,
        decimal saleslastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Insert1SalesPerson]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@salesquota", salesquota.HasValue ? (object)salesquota.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@bonus", bonus);
        command.Parameters.AddWithValue("@commissionpct", commissionpct);
        command.Parameters.AddWithValue("@salesytd", salesytd);
        command.Parameters.AddWithValue("@saleslastyear", saleslastyear);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Insert1Salesperson(SqlConnection sqlConnection, Types.Sales.SalespersonDataType data )
    {
        return Insert1Salesperson( sqlConnection, 
            data.Businessentityid,
            data.Salesquota,
            data.Bonus,
            data.Commissionpct,
            data.Salesytd,
            data.Saleslastyear,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool Update1Salesperson(SqlConnection sqlConnection, int businessentityid,
        decimal? salesquota,
        decimal bonus,
        decimal commissionpct,
        decimal salesytd,
        decimal saleslastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update1SalesPerson]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@salesquota", salesquota.HasValue ? (object)salesquota.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@bonus", bonus);
        command.Parameters.AddWithValue("@commissionpct", commissionpct);
        command.Parameters.AddWithValue("@salesytd", salesytd);
        command.Parameters.AddWithValue("@saleslastyear", saleslastyear);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update2Salesperson(SqlConnection sqlConnection, int businessentityid,
        int? territoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update2SalesPerson]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@territoryid", territoryid.HasValue ? (object)territoryid.Value : (object)DBNull.Value);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update1Salesperson(SqlConnection sqlConnection, Types.Sales.SalespersonDataType data )
    {
        return Update1Salesperson( sqlConnection, 
            data.Businessentityid,
            data.Salesquota,
            data.Bonus,
            data.Commissionpct,
            data.Salesytd,
            data.Saleslastyear,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool Update2Salesperson(SqlConnection sqlConnection, Types.Sales.SalespersonDataType data )
    {
        return Update2Salesperson( sqlConnection, 
            data.Businessentityid,
            data.Territoryid );
    }

    public static bool InsertSalespersonquotahistory(SqlConnection sqlConnection, int businessentityid,
        DateTime quotadate,
        decimal salesquota,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesPersonQuotaHistory]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@quotadate", quotadate);
        command.Parameters.AddWithValue("@salesquota", salesquota);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertSalespersonquotahistory(SqlConnection sqlConnection, Types.Sales.SalespersonquotahistoryDataType data )
    {
        return InsertSalespersonquotahistory( sqlConnection, 
            data.Businessentityid,
            data.Quotadate,
            data.Salesquota,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateSalespersonquotahistory(SqlConnection sqlConnection, int businessentityid,
        DateTime quotadate,
        decimal salesquota,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesPersonQuotaHistory]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@quotadate", quotadate);
        command.Parameters.AddWithValue("@salesquota", salesquota);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateSalespersonquotahistory(SqlConnection sqlConnection, Types.Sales.SalespersonquotahistoryDataType data )
    {
        return UpdateSalespersonquotahistory( sqlConnection, 
            data.Businessentityid,
            data.Quotadate,
            data.Salesquota,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteSalespersonquotahistory(SqlConnection sqlConnection, int businessentityid,
        DateTime quotadate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesPersonQuotaHistory]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@quotadate", quotadate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteSalespersonquotahistory(SqlConnection sqlConnection, Types.Sales.SalespersonquotahistoryDataType data )
    {
        return DeleteSalespersonquotahistory( sqlConnection, 
            data.Businessentityid,
            data.Quotadate );
    }

    public static bool InsertSalesreason(SqlConnection sqlConnection, int salesreasonid,
        string name,
        string reasontype,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesReason]";

        command.Parameters.AddWithValue("@salesreasonid", salesreasonid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@reasontype", reasontype);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertSalesreason(SqlConnection sqlConnection, Types.Sales.SalesreasonDataType data )
    {
        return InsertSalesreason( sqlConnection, 
            data.Salesreasonid,
            data.Name,
            data.Reasontype,
            data.Modifieddate );
    }

    public static bool UpdateSalesreason(SqlConnection sqlConnection, int salesreasonid,
        string name,
        string reasontype,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesReason]";

        command.Parameters.AddWithValue("@salesreasonid", salesreasonid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@reasontype", reasontype);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateSalesreason(SqlConnection sqlConnection, Types.Sales.SalesreasonDataType data )
    {
        return UpdateSalesreason( sqlConnection, 
            data.Salesreasonid,
            data.Name,
            data.Reasontype,
            data.Modifieddate );
    }

    public static bool DeleteSalesreason(SqlConnection sqlConnection, int salesreasonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesReason]";

        command.Parameters.AddWithValue("@salesreasonid", salesreasonid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteSalesreason(SqlConnection sqlConnection, Types.Sales.SalesreasonDataType data )
    {
        return DeleteSalesreason( sqlConnection, 
            data.Salesreasonid );
    }

    public static bool InsertSalestaxrate(SqlConnection sqlConnection, int salestaxrateid,
        int stateprovinceid,
        byte taxtype,
        decimal taxrate,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesTaxRate]";

        command.Parameters.AddWithValue("@salestaxrateid", salestaxrateid);
        command.Parameters.AddWithValue("@stateprovinceid", stateprovinceid);
        command.Parameters.AddWithValue("@taxtype", taxtype);
        command.Parameters.AddWithValue("@taxrate", taxrate);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertSalestaxrate(SqlConnection sqlConnection, Types.Sales.SalestaxrateDataType data )
    {
        return InsertSalestaxrate( sqlConnection, 
            data.Salestaxrateid,
            data.Stateprovinceid,
            data.Taxtype,
            data.Taxrate,
            data.Name,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateSalestaxrate(SqlConnection sqlConnection, int salestaxrateid,
        int stateprovinceid,
        byte taxtype,
        decimal taxrate,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesTaxRate]";

        command.Parameters.AddWithValue("@salestaxrateid", salestaxrateid);
        command.Parameters.AddWithValue("@stateprovinceid", stateprovinceid);
        command.Parameters.AddWithValue("@taxtype", taxtype);
        command.Parameters.AddWithValue("@taxrate", taxrate);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateSalestaxrate(SqlConnection sqlConnection, Types.Sales.SalestaxrateDataType data )
    {
        return UpdateSalestaxrate( sqlConnection, 
            data.Salestaxrateid,
            data.Stateprovinceid,
            data.Taxtype,
            data.Taxrate,
            data.Name,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteSalestaxrate(SqlConnection sqlConnection, int salestaxrateid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesTaxRate]";

        command.Parameters.AddWithValue("@salestaxrateid", salestaxrateid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteSalestaxrate(SqlConnection sqlConnection, Types.Sales.SalestaxrateDataType data )
    {
        return DeleteSalestaxrate( sqlConnection, 
            data.Salestaxrateid );
    }

    public static bool InsertSalesterritory(SqlConnection sqlConnection, int territoryid,
        string name,
        string countryregioncode,
        string group,
        decimal salesytd,
        decimal saleslastyear,
        decimal costytd,
        decimal costlastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesTerritory]";

        command.Parameters.AddWithValue("@territoryid", territoryid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@countryregioncode", countryregioncode);
        command.Parameters.AddWithValue("@group", group);
        command.Parameters.AddWithValue("@salesytd", salesytd);
        command.Parameters.AddWithValue("@saleslastyear", saleslastyear);
        command.Parameters.AddWithValue("@costytd", costytd);
        command.Parameters.AddWithValue("@costlastyear", costlastyear);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertSalesterritory(SqlConnection sqlConnection, Types.Sales.SalesterritoryDataType data )
    {
        return InsertSalesterritory( sqlConnection, 
            data.Territoryid,
            data.Name,
            data.Countryregioncode,
            data.Group,
            data.Salesytd,
            data.Saleslastyear,
            data.Costytd,
            data.Costlastyear,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateSalesterritory(SqlConnection sqlConnection, int territoryid,
        string name,
        string countryregioncode,
        string group,
        decimal salesytd,
        decimal saleslastyear,
        decimal costytd,
        decimal costlastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesTerritory]";

        command.Parameters.AddWithValue("@territoryid", territoryid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@countryregioncode", countryregioncode);
        command.Parameters.AddWithValue("@group", group);
        command.Parameters.AddWithValue("@salesytd", salesytd);
        command.Parameters.AddWithValue("@saleslastyear", saleslastyear);
        command.Parameters.AddWithValue("@costytd", costytd);
        command.Parameters.AddWithValue("@costlastyear", costlastyear);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateSalesterritory(SqlConnection sqlConnection, Types.Sales.SalesterritoryDataType data )
    {
        return UpdateSalesterritory( sqlConnection, 
            data.Territoryid,
            data.Name,
            data.Countryregioncode,
            data.Group,
            data.Salesytd,
            data.Saleslastyear,
            data.Costytd,
            data.Costlastyear,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteSalesterritory(SqlConnection sqlConnection, int territoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesTerritory]";

        command.Parameters.AddWithValue("@territoryid", territoryid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteSalesterritory(SqlConnection sqlConnection, Types.Sales.SalesterritoryDataType data )
    {
        return DeleteSalesterritory( sqlConnection, 
            data.Territoryid );
    }

    public static bool InsertSalesterritoryhistory(SqlConnection sqlConnection, int businessentityid,
        int territoryid,
        DateTime startdate,
        DateTime? enddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesTerritoryHistory]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@territoryid", territoryid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertSalesterritoryhistory(SqlConnection sqlConnection, Types.Sales.SalesterritoryhistoryDataType data )
    {
        return InsertSalesterritoryhistory( sqlConnection, 
            data.Businessentityid,
            data.Territoryid,
            data.Startdate,
            data.Enddate,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateSalesterritoryhistory(SqlConnection sqlConnection, int businessentityid,
        int territoryid,
        DateTime startdate,
        DateTime? enddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesTerritoryHistory]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@territoryid", territoryid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate.HasValue ? (object)enddate.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateSalesterritoryhistory(SqlConnection sqlConnection, Types.Sales.SalesterritoryhistoryDataType data )
    {
        return UpdateSalesterritoryhistory( sqlConnection, 
            data.Businessentityid,
            data.Territoryid,
            data.Startdate,
            data.Enddate,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteSalesterritoryhistory(SqlConnection sqlConnection, int businessentityid,
        DateTime startdate,
        int territoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesTerritoryHistory]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@territoryid", territoryid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteSalesterritoryhistory(SqlConnection sqlConnection, Types.Sales.SalesterritoryhistoryDataType data )
    {
        return DeleteSalesterritoryhistory( sqlConnection, 
            data.Businessentityid,
            data.Startdate,
            data.Territoryid );
    }

    public static bool InsertShoppingcartitem(SqlConnection sqlConnection, int shoppingcartitemid,
        string shoppingcartid,
        int quantity,
        int productid,
        DateTime datecreated,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertShoppingCartItem]";

        command.Parameters.AddWithValue("@shoppingcartitemid", shoppingcartitemid);
        command.Parameters.AddWithValue("@shoppingcartid", shoppingcartid);
        command.Parameters.AddWithValue("@quantity", quantity);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@datecreated", datecreated);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertShoppingcartitem(SqlConnection sqlConnection, Types.Sales.ShoppingcartitemDataType data )
    {
        return InsertShoppingcartitem( sqlConnection, 
            data.Shoppingcartitemid,
            data.Shoppingcartid,
            data.Quantity,
            data.Productid,
            data.Datecreated,
            data.Modifieddate );
    }

    public static bool UpdateShoppingcartitem(SqlConnection sqlConnection, int shoppingcartitemid,
        string shoppingcartid,
        int quantity,
        int productid,
        DateTime datecreated,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateShoppingCartItem]";

        command.Parameters.AddWithValue("@shoppingcartitemid", shoppingcartitemid);
        command.Parameters.AddWithValue("@shoppingcartid", shoppingcartid);
        command.Parameters.AddWithValue("@quantity", quantity);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@datecreated", datecreated);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateShoppingcartitem(SqlConnection sqlConnection, Types.Sales.ShoppingcartitemDataType data )
    {
        return UpdateShoppingcartitem( sqlConnection, 
            data.Shoppingcartitemid,
            data.Shoppingcartid,
            data.Quantity,
            data.Productid,
            data.Datecreated,
            data.Modifieddate );
    }

    public static bool DeleteShoppingcartitem(SqlConnection sqlConnection, int shoppingcartitemid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteShoppingCartItem]";

        command.Parameters.AddWithValue("@shoppingcartitemid", shoppingcartitemid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteShoppingcartitem(SqlConnection sqlConnection, Types.Sales.ShoppingcartitemDataType data )
    {
        return DeleteShoppingcartitem( sqlConnection, 
            data.Shoppingcartitemid );
    }

    public static bool InsertSpecialoffer(SqlConnection sqlConnection, int specialofferid,
        string description,
        decimal discountpct,
        string type,
        string category,
        DateTime startdate,
        DateTime enddate,
        int minqty,
        int? maxqty,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSpecialOffer]";

        command.Parameters.AddWithValue("@specialofferid", specialofferid);
        command.Parameters.AddWithValue("@description", description);
        command.Parameters.AddWithValue("@discountpct", discountpct);
        command.Parameters.AddWithValue("@type", type);
        command.Parameters.AddWithValue("@category", category);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate);
        command.Parameters.AddWithValue("@minqty", minqty);
        command.Parameters.AddWithValue("@maxqty", maxqty.HasValue ? (object)maxqty.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertSpecialoffer(SqlConnection sqlConnection, Types.Sales.SpecialofferDataType data )
    {
        return InsertSpecialoffer( sqlConnection, 
            data.Specialofferid,
            data.Description,
            data.Discountpct,
            data.Type,
            data.Category,
            data.Startdate,
            data.Enddate,
            data.Minqty,
            data.Maxqty,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateSpecialoffer(SqlConnection sqlConnection, int specialofferid,
        string description,
        decimal discountpct,
        string type,
        string category,
        DateTime startdate,
        DateTime enddate,
        int minqty,
        int? maxqty,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSpecialOffer]";

        command.Parameters.AddWithValue("@specialofferid", specialofferid);
        command.Parameters.AddWithValue("@description", description);
        command.Parameters.AddWithValue("@discountpct", discountpct);
        command.Parameters.AddWithValue("@type", type);
        command.Parameters.AddWithValue("@category", category);
        command.Parameters.AddWithValue("@startdate", startdate);
        command.Parameters.AddWithValue("@enddate", enddate);
        command.Parameters.AddWithValue("@minqty", minqty);
        command.Parameters.AddWithValue("@maxqty", maxqty.HasValue ? (object)maxqty.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateSpecialoffer(SqlConnection sqlConnection, Types.Sales.SpecialofferDataType data )
    {
        return UpdateSpecialoffer( sqlConnection, 
            data.Specialofferid,
            data.Description,
            data.Discountpct,
            data.Type,
            data.Category,
            data.Startdate,
            data.Enddate,
            data.Minqty,
            data.Maxqty,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteSpecialoffer(SqlConnection sqlConnection, int specialofferid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSpecialOffer]";

        command.Parameters.AddWithValue("@specialofferid", specialofferid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteSpecialoffer(SqlConnection sqlConnection, Types.Sales.SpecialofferDataType data )
    {
        return DeleteSpecialoffer( sqlConnection, 
            data.Specialofferid );
    }

    public static bool InsertSpecialofferproduct(SqlConnection sqlConnection, int specialofferid,
        int productid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSpecialOfferProduct]";

        command.Parameters.AddWithValue("@specialofferid", specialofferid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertSpecialofferproduct(SqlConnection sqlConnection, Types.Sales.SpecialofferproductDataType data )
    {
        return InsertSpecialofferproduct( sqlConnection, 
            data.Specialofferid,
            data.Productid,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateSpecialofferproduct(SqlConnection sqlConnection, int specialofferid,
        int productid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSpecialOfferProduct]";

        command.Parameters.AddWithValue("@specialofferid", specialofferid);
        command.Parameters.AddWithValue("@productid", productid);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateSpecialofferproduct(SqlConnection sqlConnection, Types.Sales.SpecialofferproductDataType data )
    {
        return UpdateSpecialofferproduct( sqlConnection, 
            data.Specialofferid,
            data.Productid,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteSpecialofferproduct(SqlConnection sqlConnection, int specialofferid,
        int productid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSpecialOfferProduct]";

        command.Parameters.AddWithValue("@specialofferid", specialofferid);
        command.Parameters.AddWithValue("@productid", productid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteSpecialofferproduct(SqlConnection sqlConnection, Types.Sales.SpecialofferproductDataType data )
    {
        return DeleteSpecialofferproduct( sqlConnection, 
            data.Specialofferid,
            data.Productid );
    }

    public static bool InsertStore(SqlConnection sqlConnection, int businessentityid,
        string name,
        int? salespersonid,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertStore]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@salespersonid", salespersonid.HasValue ? (object)salespersonid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@demographics", (object?)demographics ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool InsertStore(SqlConnection sqlConnection, Types.Sales.StoreDataType data )
    {
        return InsertStore( sqlConnection, 
            data.Businessentityid,
            data.Name,
            data.Salespersonid,
            data.Demographics,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool UpdateStore(SqlConnection sqlConnection, int businessentityid,
        string name,
        int? salespersonid,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateStore]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@salespersonid", salespersonid.HasValue ? (object)salespersonid.Value : (object)DBNull.Value);
        command.Parameters.AddWithValue("@demographics", (object?)demographics ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool UpdateStore(SqlConnection sqlConnection, Types.Sales.StoreDataType data )
    {
        return UpdateStore( sqlConnection, 
            data.Businessentityid,
            data.Name,
            data.Salespersonid,
            data.Demographics,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool DeleteStore(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteStore]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool DeleteStore(SqlConnection sqlConnection, Types.Sales.StoreDataType data )
    {
        return DeleteStore( sqlConnection, 
            data.Businessentityid );
    }

    public static bool Insert1Store(SqlConnection sqlConnection, int businessentityid,
        string name,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Insert1Store]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@demographics", (object?)demographics ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Insert1Store(SqlConnection sqlConnection, Types.Sales.StoreDataType data )
    {
        return Insert1Store( sqlConnection, 
            data.Businessentityid,
            data.Name,
            data.Demographics,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool Update1Store(SqlConnection sqlConnection, int businessentityid,
        string name,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update1Store]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@name", name);
        command.Parameters.AddWithValue("@demographics", (object?)demographics ?? (object)DBNull.Value);
        command.Parameters.AddWithValue("@rowguid", rowguid);
        command.Parameters.AddWithValue("@modifieddate", modifieddate);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update2Store(SqlConnection sqlConnection, int businessentityid,
        int? salespersonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update2Store]";

        command.Parameters.AddWithValue("@businessentityid", businessentityid);
        command.Parameters.AddWithValue("@salespersonid", salespersonid.HasValue ? (object)salespersonid.Value : (object)DBNull.Value);

        return command.ExecuteNonQuery() > 0;
    }

    public static bool Update1Store(SqlConnection sqlConnection, Types.Sales.StoreDataType data )
    {
        return Update1Store( sqlConnection, 
            data.Businessentityid,
            data.Name,
            data.Demographics,
            data.Rowguid,
            data.Modifieddate );
    }

    public static bool Update2Store(SqlConnection sqlConnection, Types.Sales.StoreDataType data )
    {
        return Update2Store( sqlConnection, 
            data.Businessentityid,
            data.Salespersonid );
    }

}
