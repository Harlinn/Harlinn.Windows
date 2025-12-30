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
    public static bool InsertAwbuildversion(SqlConnection sqlConnection, ref byte systeminformationid,
        string databaseVersion,
        DateTime versiondate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[InsertAWBuildVersion]";

        var systeminformationidParameter = command.Parameters.AddByte("@systeminformationid");
        command.Parameters.AddNVarChar("@databaseVersion", databaseVersion, 25);
        command.Parameters.AddDateTime("@versiondate", versiondate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            systeminformationid = (byte)systeminformationidParameter.Value;
        }
        return result;
    }

    public static bool InsertAwbuildversion(SqlConnection sqlConnection, Types.Dbo.AwbuildversionDataType data )
    {
        var dataSysteminformationid = data.Systeminformationid;
        var dataDatabaseVersion = data.DatabaseVersion;
        var dataVersiondate = data.Versiondate;
        var dataModifieddate = data.Modifieddate;
        var result = InsertAwbuildversion( sqlConnection, 
                        ref dataSysteminformationid,
                        dataDatabaseVersion,
                        dataVersiondate,
                        dataModifieddate );
        data.Systeminformationid = dataSysteminformationid;

        return result;
    }

    public static bool UpdateAwbuildversion(SqlConnection sqlConnection, byte systeminformationid,
        string databaseVersion,
        DateTime versiondate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[UpdateAWBuildVersion]";

        command.Parameters.AddByte("@systeminformationid", systeminformationid);
        command.Parameters.AddNVarChar("@databaseVersion", databaseVersion, 25);
        command.Parameters.AddDateTime("@versiondate", versiondate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateAwbuildversion(SqlConnection sqlConnection, Types.Dbo.AwbuildversionDataType data )
    {
        var dataSysteminformationid = data.Systeminformationid;
        var dataDatabaseVersion = data.DatabaseVersion;
        var dataVersiondate = data.Versiondate;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateAwbuildversion( sqlConnection, 
                        dataSysteminformationid,
                        dataDatabaseVersion,
                        dataVersiondate,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteAwbuildversion(SqlConnection sqlConnection, byte systeminformationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[DeleteAWBuildVersion]";

        command.Parameters.AddByte("@systeminformationid", systeminformationid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteAwbuildversion(SqlConnection sqlConnection, Types.Dbo.AwbuildversionDataType data )
    {
        var dataSysteminformationid = data.Systeminformationid;
        var result = DeleteAwbuildversion( sqlConnection, 
                        dataSysteminformationid );

        return result;
    }

    public static bool InsertDatabaselog(SqlConnection sqlConnection, ref int databaselogid,
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

        var databaselogidParameter = command.Parameters.AddInt32("@databaselogid");
        command.Parameters.AddDateTime("@posttime", posttime);
        command.Parameters.AddNVarChar("@databaseuser", databaseuser, 128);
        command.Parameters.AddNVarChar("@event", event__, 128);
        command.Parameters.AddNVarChar("@schema", schema, 128);
        command.Parameters.AddNVarChar("@object", object__, 128);
        command.Parameters.AddNVarChar("@tsql", tsql, -1);
        command.Parameters.AddSqlXml("@xmlevent", xmlevent);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            databaselogid = (int)databaselogidParameter.Value;
        }
        return result;
    }

    public static bool InsertDatabaselog(SqlConnection sqlConnection, Types.Dbo.DatabaselogDataType data )
    {
        var dataDatabaselogid = data.Databaselogid;
        var dataPosttime = data.Posttime;
        var dataDatabaseuser = data.Databaseuser;
        var dataEvent = data.Event;
        var dataSchema = data.Schema;
        var dataObject = data.Object;
        var dataTsql = data.Tsql;
        var dataXmlevent = data.Xmlevent;
        var result = InsertDatabaselog( sqlConnection, 
                        ref dataDatabaselogid,
                        dataPosttime,
                        dataDatabaseuser,
                        dataEvent,
                        dataSchema,
                        dataObject,
                        dataTsql,
                        dataXmlevent );
        data.Databaselogid = dataDatabaselogid;

        return result;
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

        command.Parameters.AddInt32("@databaselogid", databaselogid);
        command.Parameters.AddDateTime("@posttime", posttime);
        command.Parameters.AddNVarChar("@databaseuser", databaseuser, 128);
        command.Parameters.AddNVarChar("@event", event__, 128);
        command.Parameters.AddNVarChar("@schema", schema, 128);
        command.Parameters.AddNVarChar("@object", object__, 128);
        command.Parameters.AddNVarChar("@tsql", tsql, -1);
        command.Parameters.AddSqlXml("@xmlevent", xmlevent);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateDatabaselog(SqlConnection sqlConnection, Types.Dbo.DatabaselogDataType data )
    {
        var dataDatabaselogid = data.Databaselogid;
        var dataPosttime = data.Posttime;
        var dataDatabaseuser = data.Databaseuser;
        var dataEvent = data.Event;
        var dataSchema = data.Schema;
        var dataObject = data.Object;
        var dataTsql = data.Tsql;
        var dataXmlevent = data.Xmlevent;
        var result = UpdateDatabaselog( sqlConnection, 
                        dataDatabaselogid,
                        dataPosttime,
                        dataDatabaseuser,
                        dataEvent,
                        dataSchema,
                        dataObject,
                        dataTsql,
                        dataXmlevent );

        return result;
    }

    public static bool DeleteDatabaselog(SqlConnection sqlConnection, int databaselogid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[DeleteDatabaseLog]";

        command.Parameters.AddInt32("@databaselogid", databaselogid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteDatabaselog(SqlConnection sqlConnection, Types.Dbo.DatabaselogDataType data )
    {
        var dataDatabaselogid = data.Databaselogid;
        var result = DeleteDatabaselog( sqlConnection, 
                        dataDatabaselogid );

        return result;
    }

    public static bool InsertErrorlog(SqlConnection sqlConnection, ref int errorlogid,
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

        var errorlogidParameter = command.Parameters.AddInt32("@errorlogid");
        command.Parameters.AddDateTime("@errortime", errortime);
        command.Parameters.AddNVarChar("@username", username, 128);
        command.Parameters.AddInt32("@errornumber", errornumber);
        command.Parameters.AddInt32("@errorseverity", errorseverity);
        command.Parameters.AddInt32("@errorstate", errorstate);
        command.Parameters.AddNVarChar("@errorprocedure", errorprocedure, 126);
        command.Parameters.AddInt32("@errorline", errorline);
        command.Parameters.AddNVarChar("@errormessage", errormessage, 4000);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            errorlogid = (int)errorlogidParameter.Value;
        }
        return result;
    }

    public static bool InsertErrorlog(SqlConnection sqlConnection, Types.Dbo.ErrorlogDataType data )
    {
        var dataErrorlogid = data.Errorlogid;
        var dataErrortime = data.Errortime;
        var dataUsername = data.Username;
        var dataErrornumber = data.Errornumber;
        var dataErrorseverity = data.Errorseverity;
        var dataErrorstate = data.Errorstate;
        var dataErrorprocedure = data.Errorprocedure;
        var dataErrorline = data.Errorline;
        var dataErrormessage = data.Errormessage;
        var result = InsertErrorlog( sqlConnection, 
                        ref dataErrorlogid,
                        dataErrortime,
                        dataUsername,
                        dataErrornumber,
                        dataErrorseverity,
                        dataErrorstate,
                        dataErrorprocedure,
                        dataErrorline,
                        dataErrormessage );
        data.Errorlogid = dataErrorlogid;

        return result;
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

        command.Parameters.AddInt32("@errorlogid", errorlogid);
        command.Parameters.AddDateTime("@errortime", errortime);
        command.Parameters.AddNVarChar("@username", username, 128);
        command.Parameters.AddInt32("@errornumber", errornumber);
        command.Parameters.AddInt32("@errorseverity", errorseverity);
        command.Parameters.AddInt32("@errorstate", errorstate);
        command.Parameters.AddNVarChar("@errorprocedure", errorprocedure, 126);
        command.Parameters.AddInt32("@errorline", errorline);
        command.Parameters.AddNVarChar("@errormessage", errormessage, 4000);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateErrorlog(SqlConnection sqlConnection, Types.Dbo.ErrorlogDataType data )
    {
        var dataErrorlogid = data.Errorlogid;
        var dataErrortime = data.Errortime;
        var dataUsername = data.Username;
        var dataErrornumber = data.Errornumber;
        var dataErrorseverity = data.Errorseverity;
        var dataErrorstate = data.Errorstate;
        var dataErrorprocedure = data.Errorprocedure;
        var dataErrorline = data.Errorline;
        var dataErrormessage = data.Errormessage;
        var result = UpdateErrorlog( sqlConnection, 
                        dataErrorlogid,
                        dataErrortime,
                        dataUsername,
                        dataErrornumber,
                        dataErrorseverity,
                        dataErrorstate,
                        dataErrorprocedure,
                        dataErrorline,
                        dataErrormessage );

        return result;
    }

    public static bool DeleteErrorlog(SqlConnection sqlConnection, int errorlogid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[dbo].[DeleteErrorLog]";

        command.Parameters.AddInt32("@errorlogid", errorlogid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteErrorlog(SqlConnection sqlConnection, Types.Dbo.ErrorlogDataType data )
    {
        var dataErrorlogid = data.Errorlogid;
        var result = DeleteErrorlog( sqlConnection, 
                        dataErrorlogid );

        return result;
    }

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

    public static bool InsertDepartment(SqlConnection sqlConnection, Types.HumanResources.DepartmentDataType data )
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

    public static bool UpdateDepartment(SqlConnection sqlConnection, Types.HumanResources.DepartmentDataType data )
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

    public static bool DeleteDepartment(SqlConnection sqlConnection, Types.HumanResources.DepartmentDataType data )
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

    public static bool InsertEmployee(SqlConnection sqlConnection, Types.HumanResources.EmployeeDataType data )
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

    public static bool UpdateEmployee(SqlConnection sqlConnection, Types.HumanResources.EmployeeDataType data )
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

    public static bool DeleteEmployee(SqlConnection sqlConnection, Types.HumanResources.EmployeeDataType data )
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

    public static bool InsertEmployeedepartmenthistory(SqlConnection sqlConnection, Types.HumanResources.EmployeedepartmenthistoryDataType data )
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

    public static bool UpdateEmployeedepartmenthistory(SqlConnection sqlConnection, Types.HumanResources.EmployeedepartmenthistoryDataType data )
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

    public static bool DeleteEmployeedepartmenthistory(SqlConnection sqlConnection, Types.HumanResources.EmployeedepartmenthistoryDataType data )
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

    public static bool InsertEmployeepayhistory(SqlConnection sqlConnection, Types.HumanResources.EmployeepayhistoryDataType data )
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

    public static bool UpdateEmployeepayhistory(SqlConnection sqlConnection, Types.HumanResources.EmployeepayhistoryDataType data )
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

    public static bool DeleteEmployeepayhistory(SqlConnection sqlConnection, Types.HumanResources.EmployeepayhistoryDataType data )
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

    public static bool InsertJobcandidate(SqlConnection sqlConnection, Types.HumanResources.JobcandidateDataType data )
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

    public static bool UpdateJobcandidate(SqlConnection sqlConnection, Types.HumanResources.JobcandidateDataType data )
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

    public static bool DeleteJobcandidate(SqlConnection sqlConnection, Types.HumanResources.JobcandidateDataType data )
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

    public static bool Insert1Jobcandidate(SqlConnection sqlConnection, Types.HumanResources.JobcandidateDataType data )
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

    public static bool Update1Jobcandidate(SqlConnection sqlConnection, Types.HumanResources.JobcandidateDataType data )
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

    public static bool Update2Jobcandidate(SqlConnection sqlConnection, Types.HumanResources.JobcandidateDataType data )
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

    public static bool InsertShift(SqlConnection sqlConnection, Types.HumanResources.ShiftDataType data )
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

    public static bool UpdateShift(SqlConnection sqlConnection, Types.HumanResources.ShiftDataType data )
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

    public static bool DeleteShift(SqlConnection sqlConnection, Types.HumanResources.ShiftDataType data )
    {
        var dataShiftid = data.Shiftid;
        var result = DeleteShift( sqlConnection, 
                        dataShiftid );

        return result;
    }

    public static bool InsertAddress(SqlConnection sqlConnection, ref int addressid,
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

        var addressidParameter = command.Parameters.AddInt32("@addressid");
        command.Parameters.AddNVarChar("@addressline1", addressline1, 60);
        command.Parameters.AddNVarChar("@addressline2", addressline2, 60);
        command.Parameters.AddNVarChar("@city", city, 30);
        command.Parameters.AddInt32("@stateprovinceid", stateprovinceid);
        command.Parameters.AddNVarChar("@postalcode", postalcode, 15);
        command.Parameters.AddSqlGeography("@spatiallocation", spatiallocation);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            addressid = (int)addressidParameter.Value;
        }
        return result;
    }

    public static bool InsertAddress(SqlConnection sqlConnection, Types.Person.AddressDataType data )
    {
        var dataAddressid = data.Addressid;
        var dataAddressline1 = data.Addressline1;
        var dataAddressline2 = data.Addressline2;
        var dataCity = data.City;
        var dataStateprovinceid = data.Stateprovinceid;
        var dataPostalcode = data.Postalcode;
        var dataSpatiallocation = data.Spatiallocation;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertAddress( sqlConnection, 
                        ref dataAddressid,
                        dataAddressline1,
                        dataAddressline2,
                        dataCity,
                        dataStateprovinceid,
                        dataPostalcode,
                        dataSpatiallocation,
                        dataRowguid,
                        dataModifieddate );
        data.Addressid = dataAddressid;

        return result;
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

        command.Parameters.AddInt32("@addressid", addressid);
        command.Parameters.AddNVarChar("@addressline1", addressline1, 60);
        command.Parameters.AddNVarChar("@addressline2", addressline2, 60);
        command.Parameters.AddNVarChar("@city", city, 30);
        command.Parameters.AddInt32("@stateprovinceid", stateprovinceid);
        command.Parameters.AddNVarChar("@postalcode", postalcode, 15);
        command.Parameters.AddSqlGeography("@spatiallocation", spatiallocation);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateAddress(SqlConnection sqlConnection, Types.Person.AddressDataType data )
    {
        var dataAddressid = data.Addressid;
        var dataAddressline1 = data.Addressline1;
        var dataAddressline2 = data.Addressline2;
        var dataCity = data.City;
        var dataStateprovinceid = data.Stateprovinceid;
        var dataPostalcode = data.Postalcode;
        var dataSpatiallocation = data.Spatiallocation;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateAddress( sqlConnection, 
                        dataAddressid,
                        dataAddressline1,
                        dataAddressline2,
                        dataCity,
                        dataStateprovinceid,
                        dataPostalcode,
                        dataSpatiallocation,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteAddress(SqlConnection sqlConnection, int addressid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteAddress]";

        command.Parameters.AddInt32("@addressid", addressid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteAddress(SqlConnection sqlConnection, Types.Person.AddressDataType data )
    {
        var dataAddressid = data.Addressid;
        var result = DeleteAddress( sqlConnection, 
                        dataAddressid );

        return result;
    }

    public static bool InsertAddresstype(SqlConnection sqlConnection, ref int addresstypeid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertAddressType]";

        var addresstypeidParameter = command.Parameters.AddInt32("@addresstypeid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            addresstypeid = (int)addresstypeidParameter.Value;
        }
        return result;
    }

    public static bool InsertAddresstype(SqlConnection sqlConnection, Types.Person.AddresstypeDataType data )
    {
        var dataAddresstypeid = data.Addresstypeid;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertAddresstype( sqlConnection, 
                        ref dataAddresstypeid,
                        dataName,
                        dataRowguid,
                        dataModifieddate );
        data.Addresstypeid = dataAddresstypeid;

        return result;
    }

    public static bool UpdateAddresstype(SqlConnection sqlConnection, int addresstypeid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateAddressType]";

        command.Parameters.AddInt32("@addresstypeid", addresstypeid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateAddresstype(SqlConnection sqlConnection, Types.Person.AddresstypeDataType data )
    {
        var dataAddresstypeid = data.Addresstypeid;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateAddresstype( sqlConnection, 
                        dataAddresstypeid,
                        dataName,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteAddresstype(SqlConnection sqlConnection, int addresstypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteAddressType]";

        command.Parameters.AddInt32("@addresstypeid", addresstypeid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteAddresstype(SqlConnection sqlConnection, Types.Person.AddresstypeDataType data )
    {
        var dataAddresstypeid = data.Addresstypeid;
        var result = DeleteAddresstype( sqlConnection, 
                        dataAddresstypeid );

        return result;
    }

    public static bool InsertBusinessentity(SqlConnection sqlConnection, ref int businessentityid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertBusinessEntity]";

        var businessentityidParameter = command.Parameters.AddInt32("@businessentityid");
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            businessentityid = (int)businessentityidParameter.Value;
        }
        return result;
    }

    public static bool InsertBusinessentity(SqlConnection sqlConnection, Types.Person.BusinessentityDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertBusinessentity( sqlConnection, 
                        ref dataBusinessentityid,
                        dataRowguid,
                        dataModifieddate );
        data.Businessentityid = dataBusinessentityid;

        return result;
    }

    public static bool UpdateBusinessentity(SqlConnection sqlConnection, int businessentityid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateBusinessEntity]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateBusinessentity(SqlConnection sqlConnection, Types.Person.BusinessentityDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateBusinessentity( sqlConnection, 
                        dataBusinessentityid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteBusinessentity(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteBusinessEntity]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteBusinessentity(SqlConnection sqlConnection, Types.Person.BusinessentityDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var result = DeleteBusinessentity( sqlConnection, 
                        dataBusinessentityid );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@addressid", addressid);
        command.Parameters.AddInt32("@addresstypeid", addresstypeid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertBusinessentityaddress(SqlConnection sqlConnection, Types.Person.BusinessentityaddressDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataAddressid = data.Addressid;
        var dataAddresstypeid = data.Addresstypeid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertBusinessentityaddress( sqlConnection, 
                        dataBusinessentityid,
                        dataAddressid,
                        dataAddresstypeid,
                        dataRowguid,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@addressid", addressid);
        command.Parameters.AddInt32("@addresstypeid", addresstypeid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateBusinessentityaddress(SqlConnection sqlConnection, Types.Person.BusinessentityaddressDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataAddressid = data.Addressid;
        var dataAddresstypeid = data.Addresstypeid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateBusinessentityaddress( sqlConnection, 
                        dataBusinessentityid,
                        dataAddressid,
                        dataAddresstypeid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteBusinessentityaddress(SqlConnection sqlConnection, int businessentityid,
        int addressid,
        int addresstypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteBusinessEntityAddress]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@addressid", addressid);
        command.Parameters.AddInt32("@addresstypeid", addresstypeid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteBusinessentityaddress(SqlConnection sqlConnection, Types.Person.BusinessentityaddressDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataAddressid = data.Addressid;
        var dataAddresstypeid = data.Addresstypeid;
        var result = DeleteBusinessentityaddress( sqlConnection, 
                        dataBusinessentityid,
                        dataAddressid,
                        dataAddresstypeid );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@personid", personid);
        command.Parameters.AddInt32("@contacttypeid", contacttypeid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertBusinessentitycontact(SqlConnection sqlConnection, Types.Person.BusinessentitycontactDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPersonid = data.Personid;
        var dataContacttypeid = data.Contacttypeid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertBusinessentitycontact( sqlConnection, 
                        dataBusinessentityid,
                        dataPersonid,
                        dataContacttypeid,
                        dataRowguid,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@personid", personid);
        command.Parameters.AddInt32("@contacttypeid", contacttypeid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateBusinessentitycontact(SqlConnection sqlConnection, Types.Person.BusinessentitycontactDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPersonid = data.Personid;
        var dataContacttypeid = data.Contacttypeid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateBusinessentitycontact( sqlConnection, 
                        dataBusinessentityid,
                        dataPersonid,
                        dataContacttypeid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteBusinessentitycontact(SqlConnection sqlConnection, int businessentityid,
        int personid,
        int contacttypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteBusinessEntityContact]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@personid", personid);
        command.Parameters.AddInt32("@contacttypeid", contacttypeid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteBusinessentitycontact(SqlConnection sqlConnection, Types.Person.BusinessentitycontactDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPersonid = data.Personid;
        var dataContacttypeid = data.Contacttypeid;
        var result = DeleteBusinessentitycontact( sqlConnection, 
                        dataBusinessentityid,
                        dataPersonid,
                        dataContacttypeid );

        return result;
    }

    public static bool InsertContacttype(SqlConnection sqlConnection, ref int contacttypeid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertContactType]";

        var contacttypeidParameter = command.Parameters.AddInt32("@contacttypeid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            contacttypeid = (int)contacttypeidParameter.Value;
        }
        return result;
    }

    public static bool InsertContacttype(SqlConnection sqlConnection, Types.Person.ContacttypeDataType data )
    {
        var dataContacttypeid = data.Contacttypeid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertContacttype( sqlConnection, 
                        ref dataContacttypeid,
                        dataName,
                        dataModifieddate );
        data.Contacttypeid = dataContacttypeid;

        return result;
    }

    public static bool UpdateContacttype(SqlConnection sqlConnection, int contacttypeid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateContactType]";

        command.Parameters.AddInt32("@contacttypeid", contacttypeid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateContacttype(SqlConnection sqlConnection, Types.Person.ContacttypeDataType data )
    {
        var dataContacttypeid = data.Contacttypeid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateContacttype( sqlConnection, 
                        dataContacttypeid,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteContacttype(SqlConnection sqlConnection, int contacttypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteContactType]";

        command.Parameters.AddInt32("@contacttypeid", contacttypeid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteContacttype(SqlConnection sqlConnection, Types.Person.ContacttypeDataType data )
    {
        var dataContacttypeid = data.Contacttypeid;
        var result = DeleteContacttype( sqlConnection, 
                        dataContacttypeid );

        return result;
    }

    public static bool InsertCountryregion(SqlConnection sqlConnection, string countryregioncode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertCountryRegion]";

        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertCountryregion(SqlConnection sqlConnection, Types.Person.CountryregionDataType data )
    {
        var dataCountryregioncode = data.Countryregioncode;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCountryregion( sqlConnection, 
                        dataCountryregioncode,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateCountryregion(SqlConnection sqlConnection, string countryregioncode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateCountryRegion]";

        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCountryregion(SqlConnection sqlConnection, Types.Person.CountryregionDataType data )
    {
        var dataCountryregioncode = data.Countryregioncode;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCountryregion( sqlConnection, 
                        dataCountryregioncode,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCountryregion(SqlConnection sqlConnection, string countryregioncode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteCountryRegion]";

        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCountryregion(SqlConnection sqlConnection, Types.Person.CountryregionDataType data )
    {
        var dataCountryregioncode = data.Countryregioncode;
        var result = DeleteCountryregion( sqlConnection, 
                        dataCountryregioncode );

        return result;
    }

    public static bool InsertEmailaddress(SqlConnection sqlConnection, int businessentityid,
        ref int emailaddressid,
        string? emailaddress,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertEmailAddress]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        var emailaddressidParameter = command.Parameters.AddInt32("@emailaddressid");
        command.Parameters.AddNVarChar("@emailaddress", emailaddress, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            emailaddressid = (int)emailaddressidParameter.Value;
        }
        return result;
    }

    public static bool InsertEmailaddress(SqlConnection sqlConnection, Types.Person.EmailaddressDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataEmailaddressid = data.Emailaddressid;
        var dataEmailaddress = data.Emailaddress;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertEmailaddress( sqlConnection, 
                        dataBusinessentityid,
                        ref dataEmailaddressid,
                        dataEmailaddress,
                        dataRowguid,
                        dataModifieddate );
        data.Emailaddressid = dataEmailaddressid;

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@emailaddressid", emailaddressid);
        command.Parameters.AddNVarChar("@emailaddress", emailaddress, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateEmailaddress(SqlConnection sqlConnection, Types.Person.EmailaddressDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataEmailaddressid = data.Emailaddressid;
        var dataEmailaddress = data.Emailaddress;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateEmailaddress( sqlConnection, 
                        dataBusinessentityid,
                        dataEmailaddressid,
                        dataEmailaddress,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteEmailaddress(SqlConnection sqlConnection, int businessentityid,
        int emailaddressid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteEmailAddress]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@emailaddressid", emailaddressid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteEmailaddress(SqlConnection sqlConnection, Types.Person.EmailaddressDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataEmailaddressid = data.Emailaddressid;
        var result = DeleteEmailaddress( sqlConnection, 
                        dataBusinessentityid,
                        dataEmailaddressid );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddVarChar("@passwordhash", passwordhash, 128);
        command.Parameters.AddVarChar("@passwordsalt", passwordsalt, 10);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertPassword(SqlConnection sqlConnection, Types.Person.PasswordDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPasswordhash = data.Passwordhash;
        var dataPasswordsalt = data.Passwordsalt;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPassword( sqlConnection, 
                        dataBusinessentityid,
                        dataPasswordhash,
                        dataPasswordsalt,
                        dataRowguid,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddVarChar("@passwordhash", passwordhash, 128);
        command.Parameters.AddVarChar("@passwordsalt", passwordsalt, 10);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePassword(SqlConnection sqlConnection, Types.Person.PasswordDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPasswordhash = data.Passwordhash;
        var dataPasswordsalt = data.Passwordsalt;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePassword( sqlConnection, 
                        dataBusinessentityid,
                        dataPasswordhash,
                        dataPasswordsalt,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePassword(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeletePassword]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePassword(SqlConnection sqlConnection, Types.Person.PasswordDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var result = DeletePassword( sqlConnection, 
                        dataBusinessentityid );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNChar("@persontype", persontype, 2);
        command.Parameters.AddBoolean("@namestyle", namestyle);
        command.Parameters.AddNVarChar("@title", title, 8);
        command.Parameters.AddNVarChar("@firstname", firstname, 50);
        command.Parameters.AddNVarChar("@middlename", middlename, 50);
        command.Parameters.AddNVarChar("@lastname", lastname, 50);
        command.Parameters.AddNVarChar("@suffix", suffix, 10);
        command.Parameters.AddInt32("@emailpromotion", emailpromotion);
        command.Parameters.AddSqlXml("@additionalcontactinfo", additionalcontactinfo);
        command.Parameters.AddSqlXml("@demographics", demographics);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertPerson(SqlConnection sqlConnection, Types.Person.PersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPersontype = data.Persontype;
        var dataNamestyle = data.Namestyle;
        var dataTitle = data.Title;
        var dataFirstname = data.Firstname;
        var dataMiddlename = data.Middlename;
        var dataLastname = data.Lastname;
        var dataSuffix = data.Suffix;
        var dataEmailpromotion = data.Emailpromotion;
        var dataAdditionalcontactinfo = data.Additionalcontactinfo;
        var dataDemographics = data.Demographics;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPerson( sqlConnection, 
                        dataBusinessentityid,
                        dataPersontype,
                        dataNamestyle,
                        dataTitle,
                        dataFirstname,
                        dataMiddlename,
                        dataLastname,
                        dataSuffix,
                        dataEmailpromotion,
                        dataAdditionalcontactinfo,
                        dataDemographics,
                        dataRowguid,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNChar("@persontype", persontype, 2);
        command.Parameters.AddBoolean("@namestyle", namestyle);
        command.Parameters.AddNVarChar("@title", title, 8);
        command.Parameters.AddNVarChar("@firstname", firstname, 50);
        command.Parameters.AddNVarChar("@middlename", middlename, 50);
        command.Parameters.AddNVarChar("@lastname", lastname, 50);
        command.Parameters.AddNVarChar("@suffix", suffix, 10);
        command.Parameters.AddInt32("@emailpromotion", emailpromotion);
        command.Parameters.AddSqlXml("@additionalcontactinfo", additionalcontactinfo);
        command.Parameters.AddSqlXml("@demographics", demographics);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePerson(SqlConnection sqlConnection, Types.Person.PersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPersontype = data.Persontype;
        var dataNamestyle = data.Namestyle;
        var dataTitle = data.Title;
        var dataFirstname = data.Firstname;
        var dataMiddlename = data.Middlename;
        var dataLastname = data.Lastname;
        var dataSuffix = data.Suffix;
        var dataEmailpromotion = data.Emailpromotion;
        var dataAdditionalcontactinfo = data.Additionalcontactinfo;
        var dataDemographics = data.Demographics;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePerson( sqlConnection, 
                        dataBusinessentityid,
                        dataPersontype,
                        dataNamestyle,
                        dataTitle,
                        dataFirstname,
                        dataMiddlename,
                        dataLastname,
                        dataSuffix,
                        dataEmailpromotion,
                        dataAdditionalcontactinfo,
                        dataDemographics,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePerson(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeletePerson]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePerson(SqlConnection sqlConnection, Types.Person.PersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var result = DeletePerson( sqlConnection, 
                        dataBusinessentityid );

        return result;
    }

    public static bool InsertPersonphone(SqlConnection sqlConnection, int businessentityid,
        string phonenumber,
        int phonenumbertypeid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertPersonPhone]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@phonenumber", phonenumber, 25);
        command.Parameters.AddInt32("@phonenumbertypeid", phonenumbertypeid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertPersonphone(SqlConnection sqlConnection, Types.Person.PersonphoneDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPhonenumber = data.Phonenumber;
        var dataPhonenumbertypeid = data.Phonenumbertypeid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPersonphone( sqlConnection, 
                        dataBusinessentityid,
                        dataPhonenumber,
                        dataPhonenumbertypeid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdatePersonphone(SqlConnection sqlConnection, int businessentityid,
        string phonenumber,
        int phonenumbertypeid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdatePersonPhone]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@phonenumber", phonenumber, 25);
        command.Parameters.AddInt32("@phonenumbertypeid", phonenumbertypeid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePersonphone(SqlConnection sqlConnection, Types.Person.PersonphoneDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPhonenumber = data.Phonenumber;
        var dataPhonenumbertypeid = data.Phonenumbertypeid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePersonphone( sqlConnection, 
                        dataBusinessentityid,
                        dataPhonenumber,
                        dataPhonenumbertypeid,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePersonphone(SqlConnection sqlConnection, int businessentityid,
        string phonenumber,
        int phonenumbertypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeletePersonPhone]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@phonenumber", phonenumber, 25);
        command.Parameters.AddInt32("@phonenumbertypeid", phonenumbertypeid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePersonphone(SqlConnection sqlConnection, Types.Person.PersonphoneDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPhonenumber = data.Phonenumber;
        var dataPhonenumbertypeid = data.Phonenumbertypeid;
        var result = DeletePersonphone( sqlConnection, 
                        dataBusinessentityid,
                        dataPhonenumber,
                        dataPhonenumbertypeid );

        return result;
    }

    public static bool InsertPhonenumbertype(SqlConnection sqlConnection, ref int phonenumbertypeid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertPhoneNumberType]";

        var phonenumbertypeidParameter = command.Parameters.AddInt32("@phonenumbertypeid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            phonenumbertypeid = (int)phonenumbertypeidParameter.Value;
        }
        return result;
    }

    public static bool InsertPhonenumbertype(SqlConnection sqlConnection, Types.Person.PhonenumbertypeDataType data )
    {
        var dataPhonenumbertypeid = data.Phonenumbertypeid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPhonenumbertype( sqlConnection, 
                        ref dataPhonenumbertypeid,
                        dataName,
                        dataModifieddate );
        data.Phonenumbertypeid = dataPhonenumbertypeid;

        return result;
    }

    public static bool UpdatePhonenumbertype(SqlConnection sqlConnection, int phonenumbertypeid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdatePhoneNumberType]";

        command.Parameters.AddInt32("@phonenumbertypeid", phonenumbertypeid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePhonenumbertype(SqlConnection sqlConnection, Types.Person.PhonenumbertypeDataType data )
    {
        var dataPhonenumbertypeid = data.Phonenumbertypeid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePhonenumbertype( sqlConnection, 
                        dataPhonenumbertypeid,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePhonenumbertype(SqlConnection sqlConnection, int phonenumbertypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeletePhoneNumberType]";

        command.Parameters.AddInt32("@phonenumbertypeid", phonenumbertypeid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePhonenumbertype(SqlConnection sqlConnection, Types.Person.PhonenumbertypeDataType data )
    {
        var dataPhonenumbertypeid = data.Phonenumbertypeid;
        var result = DeletePhonenumbertype( sqlConnection, 
                        dataPhonenumbertypeid );

        return result;
    }

    public static bool InsertStateprovince(SqlConnection sqlConnection, ref int stateprovinceid,
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

        var stateprovinceidParameter = command.Parameters.AddInt32("@stateprovinceid");
        command.Parameters.AddNChar("@stateprovincecode", stateprovincecode, 3);
        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddBoolean("@isonlystateprovinceflag", isonlystateprovinceflag);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            stateprovinceid = (int)stateprovinceidParameter.Value;
        }
        return result;
    }

    public static bool InsertStateprovince(SqlConnection sqlConnection, Types.Person.StateprovinceDataType data )
    {
        var dataStateprovinceid = data.Stateprovinceid;
        var dataStateprovincecode = data.Stateprovincecode;
        var dataCountryregioncode = data.Countryregioncode;
        var dataIsonlystateprovinceflag = data.Isonlystateprovinceflag;
        var dataName = data.Name;
        var dataTerritoryid = data.Territoryid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertStateprovince( sqlConnection, 
                        ref dataStateprovinceid,
                        dataStateprovincecode,
                        dataCountryregioncode,
                        dataIsonlystateprovinceflag,
                        dataName,
                        dataTerritoryid,
                        dataRowguid,
                        dataModifieddate );
        data.Stateprovinceid = dataStateprovinceid;

        return result;
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

        command.Parameters.AddInt32("@stateprovinceid", stateprovinceid);
        command.Parameters.AddNChar("@stateprovincecode", stateprovincecode, 3);
        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddBoolean("@isonlystateprovinceflag", isonlystateprovinceflag);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateStateprovince(SqlConnection sqlConnection, Types.Person.StateprovinceDataType data )
    {
        var dataStateprovinceid = data.Stateprovinceid;
        var dataStateprovincecode = data.Stateprovincecode;
        var dataCountryregioncode = data.Countryregioncode;
        var dataIsonlystateprovinceflag = data.Isonlystateprovinceflag;
        var dataName = data.Name;
        var dataTerritoryid = data.Territoryid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateStateprovince( sqlConnection, 
                        dataStateprovinceid,
                        dataStateprovincecode,
                        dataCountryregioncode,
                        dataIsonlystateprovinceflag,
                        dataName,
                        dataTerritoryid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteStateprovince(SqlConnection sqlConnection, int stateprovinceid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteStateProvince]";

        command.Parameters.AddInt32("@stateprovinceid", stateprovinceid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteStateprovince(SqlConnection sqlConnection, Types.Person.StateprovinceDataType data )
    {
        var dataStateprovinceid = data.Stateprovinceid;
        var result = DeleteStateprovince( sqlConnection, 
                        dataStateprovinceid );

        return result;
    }

    public static bool InsertBillofmaterials(SqlConnection sqlConnection, ref int billofmaterialsid,
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

        var billofmaterialsidParameter = command.Parameters.AddInt32("@billofmaterialsid");
        command.Parameters.AddInt32("@productassemblyid", productassemblyid);
        command.Parameters.AddInt32("@componentid", componentid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddInt16("@bomlevel", bomlevel);
        command.Parameters.AddDecimal("@perassemblyqty", perassemblyqty);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            billofmaterialsid = (int)billofmaterialsidParameter.Value;
        }
        return result;
    }

    public static bool InsertBillofmaterials(SqlConnection sqlConnection, Types.Production.BillofmaterialsDataType data )
    {
        var dataBillofmaterialsid = data.Billofmaterialsid;
        var dataProductassemblyid = data.Productassemblyid;
        var dataComponentid = data.Componentid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataBomlevel = data.Bomlevel;
        var dataPerassemblyqty = data.Perassemblyqty;
        var dataModifieddate = data.Modifieddate;
        var result = InsertBillofmaterials( sqlConnection, 
                        ref dataBillofmaterialsid,
                        dataProductassemblyid,
                        dataComponentid,
                        dataStartdate,
                        dataEnddate,
                        dataUnitmeasurecode,
                        dataBomlevel,
                        dataPerassemblyqty,
                        dataModifieddate );
        data.Billofmaterialsid = dataBillofmaterialsid;

        return result;
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

        command.Parameters.AddInt32("@billofmaterialsid", billofmaterialsid);
        command.Parameters.AddInt32("@productassemblyid", productassemblyid);
        command.Parameters.AddInt32("@componentid", componentid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddInt16("@bomlevel", bomlevel);
        command.Parameters.AddDecimal("@perassemblyqty", perassemblyqty);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateBillofmaterials(SqlConnection sqlConnection, Types.Production.BillofmaterialsDataType data )
    {
        var dataBillofmaterialsid = data.Billofmaterialsid;
        var dataProductassemblyid = data.Productassemblyid;
        var dataComponentid = data.Componentid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataBomlevel = data.Bomlevel;
        var dataPerassemblyqty = data.Perassemblyqty;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateBillofmaterials( sqlConnection, 
                        dataBillofmaterialsid,
                        dataProductassemblyid,
                        dataComponentid,
                        dataStartdate,
                        dataEnddate,
                        dataUnitmeasurecode,
                        dataBomlevel,
                        dataPerassemblyqty,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteBillofmaterials(SqlConnection sqlConnection, int billofmaterialsid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteBillOfMaterials]";

        command.Parameters.AddInt32("@billofmaterialsid", billofmaterialsid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteBillofmaterials(SqlConnection sqlConnection, Types.Production.BillofmaterialsDataType data )
    {
        var dataBillofmaterialsid = data.Billofmaterialsid;
        var result = DeleteBillofmaterials( sqlConnection, 
                        dataBillofmaterialsid );

        return result;
    }

    public static bool Insert1Billofmaterials(SqlConnection sqlConnection, ref int billofmaterialsid,
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

        var billofmaterialsidParameter = command.Parameters.AddInt32("@billofmaterialsid");
        command.Parameters.AddInt32("@componentid", componentid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddInt16("@bomlevel", bomlevel);
        command.Parameters.AddDecimal("@perassemblyqty", perassemblyqty);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            billofmaterialsid = (int)billofmaterialsidParameter.Value;
        }
        return result;
    }

    public static bool Insert1Billofmaterials(SqlConnection sqlConnection, Types.Production.BillofmaterialsDataType data )
    {
        var dataBillofmaterialsid = data.Billofmaterialsid;
        var dataComponentid = data.Componentid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataBomlevel = data.Bomlevel;
        var dataPerassemblyqty = data.Perassemblyqty;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Billofmaterials( sqlConnection, 
                        ref dataBillofmaterialsid,
                        dataComponentid,
                        dataStartdate,
                        dataEnddate,
                        dataUnitmeasurecode,
                        dataBomlevel,
                        dataPerassemblyqty,
                        dataModifieddate );
        data.Billofmaterialsid = dataBillofmaterialsid;

        return result;
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

        command.Parameters.AddInt32("@billofmaterialsid", billofmaterialsid);
        command.Parameters.AddInt32("@componentid", componentid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddInt16("@bomlevel", bomlevel);
        command.Parameters.AddDecimal("@perassemblyqty", perassemblyqty);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update2Billofmaterials(SqlConnection sqlConnection, int billofmaterialsid,
        int? productassemblyid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update2BillOfMaterials]";

        command.Parameters.AddInt32("@billofmaterialsid", billofmaterialsid);
        command.Parameters.AddInt32("@productassemblyid", productassemblyid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Billofmaterials(SqlConnection sqlConnection, Types.Production.BillofmaterialsDataType data )
    {
        var dataBillofmaterialsid = data.Billofmaterialsid;
        var dataComponentid = data.Componentid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataBomlevel = data.Bomlevel;
        var dataPerassemblyqty = data.Perassemblyqty;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Billofmaterials( sqlConnection, 
                        dataBillofmaterialsid,
                        dataComponentid,
                        dataStartdate,
                        dataEnddate,
                        dataUnitmeasurecode,
                        dataBomlevel,
                        dataPerassemblyqty,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Billofmaterials(SqlConnection sqlConnection, Types.Production.BillofmaterialsDataType data )
    {
        var dataBillofmaterialsid = data.Billofmaterialsid;
        var dataProductassemblyid = data.Productassemblyid;
        var result = Update2Billofmaterials( sqlConnection, 
                        dataBillofmaterialsid,
                        dataProductassemblyid );

        return result;
    }

    public static bool InsertCulture(SqlConnection sqlConnection, string cultureid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertCulture]";

        command.Parameters.AddNChar("@cultureid", cultureid, 6);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertCulture(SqlConnection sqlConnection, Types.Production.CultureDataType data )
    {
        var dataCultureid = data.Cultureid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCulture( sqlConnection, 
                        dataCultureid,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateCulture(SqlConnection sqlConnection, string cultureid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateCulture]";

        command.Parameters.AddNChar("@cultureid", cultureid, 6);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCulture(SqlConnection sqlConnection, Types.Production.CultureDataType data )
    {
        var dataCultureid = data.Cultureid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCulture( sqlConnection, 
                        dataCultureid,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCulture(SqlConnection sqlConnection, string cultureid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteCulture]";

        command.Parameters.AddNChar("@cultureid", cultureid, 6);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCulture(SqlConnection sqlConnection, Types.Production.CultureDataType data )
    {
        var dataCultureid = data.Cultureid;
        var result = DeleteCulture( sqlConnection, 
                        dataCultureid );

        return result;
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

        command.Parameters.AddHierarchyId("@documentnode", documentnode);
        command.Parameters.AddInt16("@documentlevel", documentlevel);
        command.Parameters.AddNVarChar("@title", title, 50);
        command.Parameters.AddInt32("@owner", owner);
        command.Parameters.AddBoolean("@folderflag", folderflag);
        command.Parameters.AddNVarChar("@filename", filename, 400);
        command.Parameters.AddNVarChar("@fileextension", fileextension, 8);
        command.Parameters.AddNChar("@revision", revision, 5);
        command.Parameters.AddInt32("@changenumber", changenumber);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddNVarChar("@documentsummary", documentsummary, -1);
        command.Parameters.AddBinary("@document", document, -1);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertDocument(SqlConnection sqlConnection, Types.Production.DocumentDataType data )
    {
        var dataDocumentnode = data.Documentnode;
        var dataDocumentlevel = data.Documentlevel;
        var dataTitle = data.Title;
        var dataOwner = data.Owner;
        var dataFolderflag = data.Folderflag;
        var dataFilename = data.Filename;
        var dataFileextension = data.Fileextension;
        var dataRevision = data.Revision;
        var dataChangenumber = data.Changenumber;
        var dataStatus = data.Status;
        var dataDocumentsummary = data.Documentsummary;
        var dataDocument = data.Document;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertDocument( sqlConnection, 
                        dataDocumentnode,
                        dataDocumentlevel,
                        dataTitle,
                        dataOwner,
                        dataFolderflag,
                        dataFilename,
                        dataFileextension,
                        dataRevision,
                        dataChangenumber,
                        dataStatus,
                        dataDocumentsummary,
                        dataDocument,
                        dataRowguid,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddHierarchyId("@documentnode", documentnode);
        command.Parameters.AddInt16("@documentlevel", documentlevel);
        command.Parameters.AddNVarChar("@title", title, 50);
        command.Parameters.AddInt32("@owner", owner);
        command.Parameters.AddBoolean("@folderflag", folderflag);
        command.Parameters.AddNVarChar("@filename", filename, 400);
        command.Parameters.AddNVarChar("@fileextension", fileextension, 8);
        command.Parameters.AddNChar("@revision", revision, 5);
        command.Parameters.AddInt32("@changenumber", changenumber);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddNVarChar("@documentsummary", documentsummary, -1);
        command.Parameters.AddBinary("@document", document, -1);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateDocument(SqlConnection sqlConnection, Types.Production.DocumentDataType data )
    {
        var dataDocumentnode = data.Documentnode;
        var dataDocumentlevel = data.Documentlevel;
        var dataTitle = data.Title;
        var dataOwner = data.Owner;
        var dataFolderflag = data.Folderflag;
        var dataFilename = data.Filename;
        var dataFileextension = data.Fileextension;
        var dataRevision = data.Revision;
        var dataChangenumber = data.Changenumber;
        var dataStatus = data.Status;
        var dataDocumentsummary = data.Documentsummary;
        var dataDocument = data.Document;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateDocument( sqlConnection, 
                        dataDocumentnode,
                        dataDocumentlevel,
                        dataTitle,
                        dataOwner,
                        dataFolderflag,
                        dataFilename,
                        dataFileextension,
                        dataRevision,
                        dataChangenumber,
                        dataStatus,
                        dataDocumentsummary,
                        dataDocument,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteDocument(SqlConnection sqlConnection, SqlHierarchyId documentnode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteDocument]";

        command.Parameters.AddHierarchyId("@documentnode", documentnode);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteDocument(SqlConnection sqlConnection, Types.Production.DocumentDataType data )
    {
        var dataDocumentnode = data.Documentnode;
        var result = DeleteDocument( sqlConnection, 
                        dataDocumentnode );

        return result;
    }

    public static bool InsertIllustration(SqlConnection sqlConnection, ref int illustrationid,
        SqlXml? diagram,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertIllustration]";

        var illustrationidParameter = command.Parameters.AddInt32("@illustrationid");
        command.Parameters.AddSqlXml("@diagram", diagram);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            illustrationid = (int)illustrationidParameter.Value;
        }
        return result;
    }

    public static bool InsertIllustration(SqlConnection sqlConnection, Types.Production.IllustrationDataType data )
    {
        var dataIllustrationid = data.Illustrationid;
        var dataDiagram = data.Diagram;
        var dataModifieddate = data.Modifieddate;
        var result = InsertIllustration( sqlConnection, 
                        ref dataIllustrationid,
                        dataDiagram,
                        dataModifieddate );
        data.Illustrationid = dataIllustrationid;

        return result;
    }

    public static bool UpdateIllustration(SqlConnection sqlConnection, int illustrationid,
        SqlXml? diagram,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateIllustration]";

        command.Parameters.AddInt32("@illustrationid", illustrationid);
        command.Parameters.AddSqlXml("@diagram", diagram);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateIllustration(SqlConnection sqlConnection, Types.Production.IllustrationDataType data )
    {
        var dataIllustrationid = data.Illustrationid;
        var dataDiagram = data.Diagram;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateIllustration( sqlConnection, 
                        dataIllustrationid,
                        dataDiagram,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteIllustration(SqlConnection sqlConnection, int illustrationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteIllustration]";

        command.Parameters.AddInt32("@illustrationid", illustrationid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteIllustration(SqlConnection sqlConnection, Types.Production.IllustrationDataType data )
    {
        var dataIllustrationid = data.Illustrationid;
        var result = DeleteIllustration( sqlConnection, 
                        dataIllustrationid );

        return result;
    }

    public static bool InsertLocation(SqlConnection sqlConnection, ref short locationid,
        string name,
        decimal costrate,
        decimal availability,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertLocation]";

        var locationidParameter = command.Parameters.AddInt16("@locationid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDecimal("@costrate", costrate);
        command.Parameters.AddDecimal("@availability", availability);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            locationid = (short)locationidParameter.Value;
        }
        return result;
    }

    public static bool InsertLocation(SqlConnection sqlConnection, Types.Production.LocationDataType data )
    {
        var dataLocationid = data.Locationid;
        var dataName = data.Name;
        var dataCostrate = data.Costrate;
        var dataAvailability = data.Availability;
        var dataModifieddate = data.Modifieddate;
        var result = InsertLocation( sqlConnection, 
                        ref dataLocationid,
                        dataName,
                        dataCostrate,
                        dataAvailability,
                        dataModifieddate );
        data.Locationid = dataLocationid;

        return result;
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

        command.Parameters.AddInt16("@locationid", locationid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDecimal("@costrate", costrate);
        command.Parameters.AddDecimal("@availability", availability);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateLocation(SqlConnection sqlConnection, Types.Production.LocationDataType data )
    {
        var dataLocationid = data.Locationid;
        var dataName = data.Name;
        var dataCostrate = data.Costrate;
        var dataAvailability = data.Availability;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateLocation( sqlConnection, 
                        dataLocationid,
                        dataName,
                        dataCostrate,
                        dataAvailability,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteLocation(SqlConnection sqlConnection, short locationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteLocation]";

        command.Parameters.AddInt16("@locationid", locationid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteLocation(SqlConnection sqlConnection, Types.Production.LocationDataType data )
    {
        var dataLocationid = data.Locationid;
        var result = DeleteLocation( sqlConnection, 
                        dataLocationid );

        return result;
    }

    public static bool InsertProduct(SqlConnection sqlConnection, ref int productid,
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

        var productidParameter = command.Parameters.AddInt32("@productid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@productnumber", productnumber, 25);
        command.Parameters.AddBoolean("@makeflag", makeflag);
        command.Parameters.AddBoolean("@finishedgoodsflag", finishedgoodsflag);
        command.Parameters.AddNVarChar("@color", color, 15);
        command.Parameters.AddInt16("@safetystocklevel", safetystocklevel);
        command.Parameters.AddInt16("@reorderpoint", reorderpoint);
        command.Parameters.AddDecimal("@standardcost", standardcost);
        command.Parameters.AddDecimal("@listprice", listprice);
        command.Parameters.AddNVarChar("@size", size, 5);
        command.Parameters.AddNChar("@sizeunitmeasurecode", sizeunitmeasurecode, 3);
        command.Parameters.AddNChar("@weightunitmeasurecode", weightunitmeasurecode, 3);
        command.Parameters.AddDecimal("@weight", weight);
        command.Parameters.AddInt32("@daystomanufacture", daystomanufacture);
        command.Parameters.AddNChar("@productline", productline, 2);
        command.Parameters.AddNChar("@class", class__, 2);
        command.Parameters.AddNChar("@style", style, 2);
        command.Parameters.AddInt32("@productsubcategoryid", productsubcategoryid);
        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddDateTime("@sellstartdate", sellstartdate);
        command.Parameters.AddDateTime("@sellenddate", sellenddate);
        command.Parameters.AddDateTime("@discontinueddate", discontinueddate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productid = (int)productidParameter.Value;
        }
        return result;
    }

    public static bool InsertProduct(SqlConnection sqlConnection, Types.Production.ProductDataType data )
    {
        var dataProductid = data.Productid;
        var dataName = data.Name;
        var dataProductnumber = data.Productnumber;
        var dataMakeflag = data.Makeflag;
        var dataFinishedgoodsflag = data.Finishedgoodsflag;
        var dataColor = data.Color;
        var dataSafetystocklevel = data.Safetystocklevel;
        var dataReorderpoint = data.Reorderpoint;
        var dataStandardcost = data.Standardcost;
        var dataListprice = data.Listprice;
        var dataSize = data.Size;
        var dataSizeunitmeasurecode = data.Sizeunitmeasurecode;
        var dataWeightunitmeasurecode = data.Weightunitmeasurecode;
        var dataWeight = data.Weight;
        var dataDaystomanufacture = data.Daystomanufacture;
        var dataProductline = data.Productline;
        var dataClass = data.Class;
        var dataStyle = data.Style;
        var dataProductsubcategoryid = data.Productsubcategoryid;
        var dataProductmodelid = data.Productmodelid;
        var dataSellstartdate = data.Sellstartdate;
        var dataSellenddate = data.Sellenddate;
        var dataDiscontinueddate = data.Discontinueddate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProduct( sqlConnection, 
                        ref dataProductid,
                        dataName,
                        dataProductnumber,
                        dataMakeflag,
                        dataFinishedgoodsflag,
                        dataColor,
                        dataSafetystocklevel,
                        dataReorderpoint,
                        dataStandardcost,
                        dataListprice,
                        dataSize,
                        dataSizeunitmeasurecode,
                        dataWeightunitmeasurecode,
                        dataWeight,
                        dataDaystomanufacture,
                        dataProductline,
                        dataClass,
                        dataStyle,
                        dataProductsubcategoryid,
                        dataProductmodelid,
                        dataSellstartdate,
                        dataSellenddate,
                        dataDiscontinueddate,
                        dataRowguid,
                        dataModifieddate );
        data.Productid = dataProductid;

        return result;
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

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@productnumber", productnumber, 25);
        command.Parameters.AddBoolean("@makeflag", makeflag);
        command.Parameters.AddBoolean("@finishedgoodsflag", finishedgoodsflag);
        command.Parameters.AddNVarChar("@color", color, 15);
        command.Parameters.AddInt16("@safetystocklevel", safetystocklevel);
        command.Parameters.AddInt16("@reorderpoint", reorderpoint);
        command.Parameters.AddDecimal("@standardcost", standardcost);
        command.Parameters.AddDecimal("@listprice", listprice);
        command.Parameters.AddNVarChar("@size", size, 5);
        command.Parameters.AddNChar("@sizeunitmeasurecode", sizeunitmeasurecode, 3);
        command.Parameters.AddNChar("@weightunitmeasurecode", weightunitmeasurecode, 3);
        command.Parameters.AddDecimal("@weight", weight);
        command.Parameters.AddInt32("@daystomanufacture", daystomanufacture);
        command.Parameters.AddNChar("@productline", productline, 2);
        command.Parameters.AddNChar("@class", class__, 2);
        command.Parameters.AddNChar("@style", style, 2);
        command.Parameters.AddInt32("@productsubcategoryid", productsubcategoryid);
        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddDateTime("@sellstartdate", sellstartdate);
        command.Parameters.AddDateTime("@sellenddate", sellenddate);
        command.Parameters.AddDateTime("@discontinueddate", discontinueddate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProduct(SqlConnection sqlConnection, Types.Production.ProductDataType data )
    {
        var dataProductid = data.Productid;
        var dataName = data.Name;
        var dataProductnumber = data.Productnumber;
        var dataMakeflag = data.Makeflag;
        var dataFinishedgoodsflag = data.Finishedgoodsflag;
        var dataColor = data.Color;
        var dataSafetystocklevel = data.Safetystocklevel;
        var dataReorderpoint = data.Reorderpoint;
        var dataStandardcost = data.Standardcost;
        var dataListprice = data.Listprice;
        var dataSize = data.Size;
        var dataSizeunitmeasurecode = data.Sizeunitmeasurecode;
        var dataWeightunitmeasurecode = data.Weightunitmeasurecode;
        var dataWeight = data.Weight;
        var dataDaystomanufacture = data.Daystomanufacture;
        var dataProductline = data.Productline;
        var dataClass = data.Class;
        var dataStyle = data.Style;
        var dataProductsubcategoryid = data.Productsubcategoryid;
        var dataProductmodelid = data.Productmodelid;
        var dataSellstartdate = data.Sellstartdate;
        var dataSellenddate = data.Sellenddate;
        var dataDiscontinueddate = data.Discontinueddate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProduct( sqlConnection, 
                        dataProductid,
                        dataName,
                        dataProductnumber,
                        dataMakeflag,
                        dataFinishedgoodsflag,
                        dataColor,
                        dataSafetystocklevel,
                        dataReorderpoint,
                        dataStandardcost,
                        dataListprice,
                        dataSize,
                        dataSizeunitmeasurecode,
                        dataWeightunitmeasurecode,
                        dataWeight,
                        dataDaystomanufacture,
                        dataProductline,
                        dataClass,
                        dataStyle,
                        dataProductsubcategoryid,
                        dataProductmodelid,
                        dataSellstartdate,
                        dataSellenddate,
                        dataDiscontinueddate,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProduct(SqlConnection sqlConnection, int productid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProduct]";

        command.Parameters.AddInt32("@productid", productid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProduct(SqlConnection sqlConnection, Types.Production.ProductDataType data )
    {
        var dataProductid = data.Productid;
        var result = DeleteProduct( sqlConnection, 
                        dataProductid );

        return result;
    }

    public static bool Insert1Product(SqlConnection sqlConnection, ref int productid,
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

        var productidParameter = command.Parameters.AddInt32("@productid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@productnumber", productnumber, 25);
        command.Parameters.AddBoolean("@makeflag", makeflag);
        command.Parameters.AddBoolean("@finishedgoodsflag", finishedgoodsflag);
        command.Parameters.AddNVarChar("@color", color, 15);
        command.Parameters.AddInt16("@safetystocklevel", safetystocklevel);
        command.Parameters.AddInt16("@reorderpoint", reorderpoint);
        command.Parameters.AddDecimal("@standardcost", standardcost);
        command.Parameters.AddDecimal("@listprice", listprice);
        command.Parameters.AddNVarChar("@size", size, 5);
        command.Parameters.AddDecimal("@weight", weight);
        command.Parameters.AddInt32("@daystomanufacture", daystomanufacture);
        command.Parameters.AddNChar("@productline", productline, 2);
        command.Parameters.AddNChar("@class", class__, 2);
        command.Parameters.AddNChar("@style", style, 2);
        command.Parameters.AddDateTime("@sellstartdate", sellstartdate);
        command.Parameters.AddDateTime("@sellenddate", sellenddate);
        command.Parameters.AddDateTime("@discontinueddate", discontinueddate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productid = (int)productidParameter.Value;
        }
        return result;
    }

    public static bool Insert1Product(SqlConnection sqlConnection, Types.Production.ProductDataType data )
    {
        var dataProductid = data.Productid;
        var dataName = data.Name;
        var dataProductnumber = data.Productnumber;
        var dataMakeflag = data.Makeflag;
        var dataFinishedgoodsflag = data.Finishedgoodsflag;
        var dataColor = data.Color;
        var dataSafetystocklevel = data.Safetystocklevel;
        var dataReorderpoint = data.Reorderpoint;
        var dataStandardcost = data.Standardcost;
        var dataListprice = data.Listprice;
        var dataSize = data.Size;
        var dataWeight = data.Weight;
        var dataDaystomanufacture = data.Daystomanufacture;
        var dataProductline = data.Productline;
        var dataClass = data.Class;
        var dataStyle = data.Style;
        var dataSellstartdate = data.Sellstartdate;
        var dataSellenddate = data.Sellenddate;
        var dataDiscontinueddate = data.Discontinueddate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Product( sqlConnection, 
                        ref dataProductid,
                        dataName,
                        dataProductnumber,
                        dataMakeflag,
                        dataFinishedgoodsflag,
                        dataColor,
                        dataSafetystocklevel,
                        dataReorderpoint,
                        dataStandardcost,
                        dataListprice,
                        dataSize,
                        dataWeight,
                        dataDaystomanufacture,
                        dataProductline,
                        dataClass,
                        dataStyle,
                        dataSellstartdate,
                        dataSellenddate,
                        dataDiscontinueddate,
                        dataRowguid,
                        dataModifieddate );
        data.Productid = dataProductid;

        return result;
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

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@productnumber", productnumber, 25);
        command.Parameters.AddBoolean("@makeflag", makeflag);
        command.Parameters.AddBoolean("@finishedgoodsflag", finishedgoodsflag);
        command.Parameters.AddNVarChar("@color", color, 15);
        command.Parameters.AddInt16("@safetystocklevel", safetystocklevel);
        command.Parameters.AddInt16("@reorderpoint", reorderpoint);
        command.Parameters.AddDecimal("@standardcost", standardcost);
        command.Parameters.AddDecimal("@listprice", listprice);
        command.Parameters.AddNVarChar("@size", size, 5);
        command.Parameters.AddDecimal("@weight", weight);
        command.Parameters.AddInt32("@daystomanufacture", daystomanufacture);
        command.Parameters.AddNChar("@productline", productline, 2);
        command.Parameters.AddNChar("@class", class__, 2);
        command.Parameters.AddNChar("@style", style, 2);
        command.Parameters.AddDateTime("@sellstartdate", sellstartdate);
        command.Parameters.AddDateTime("@sellenddate", sellenddate);
        command.Parameters.AddDateTime("@discontinueddate", discontinueddate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
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

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddNChar("@sizeunitmeasurecode", sizeunitmeasurecode, 3);
        command.Parameters.AddNChar("@weightunitmeasurecode", weightunitmeasurecode, 3);
        command.Parameters.AddInt32("@productsubcategoryid", productsubcategoryid);
        command.Parameters.AddInt32("@productmodelid", productmodelid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Product(SqlConnection sqlConnection, Types.Production.ProductDataType data )
    {
        var dataProductid = data.Productid;
        var dataName = data.Name;
        var dataProductnumber = data.Productnumber;
        var dataMakeflag = data.Makeflag;
        var dataFinishedgoodsflag = data.Finishedgoodsflag;
        var dataColor = data.Color;
        var dataSafetystocklevel = data.Safetystocklevel;
        var dataReorderpoint = data.Reorderpoint;
        var dataStandardcost = data.Standardcost;
        var dataListprice = data.Listprice;
        var dataSize = data.Size;
        var dataWeight = data.Weight;
        var dataDaystomanufacture = data.Daystomanufacture;
        var dataProductline = data.Productline;
        var dataClass = data.Class;
        var dataStyle = data.Style;
        var dataSellstartdate = data.Sellstartdate;
        var dataSellenddate = data.Sellenddate;
        var dataDiscontinueddate = data.Discontinueddate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Product( sqlConnection, 
                        dataProductid,
                        dataName,
                        dataProductnumber,
                        dataMakeflag,
                        dataFinishedgoodsflag,
                        dataColor,
                        dataSafetystocklevel,
                        dataReorderpoint,
                        dataStandardcost,
                        dataListprice,
                        dataSize,
                        dataWeight,
                        dataDaystomanufacture,
                        dataProductline,
                        dataClass,
                        dataStyle,
                        dataSellstartdate,
                        dataSellenddate,
                        dataDiscontinueddate,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Product(SqlConnection sqlConnection, Types.Production.ProductDataType data )
    {
        var dataProductid = data.Productid;
        var dataSizeunitmeasurecode = data.Sizeunitmeasurecode;
        var dataWeightunitmeasurecode = data.Weightunitmeasurecode;
        var dataProductsubcategoryid = data.Productsubcategoryid;
        var dataProductmodelid = data.Productmodelid;
        var result = Update2Product( sqlConnection, 
                        dataProductid,
                        dataSizeunitmeasurecode,
                        dataWeightunitmeasurecode,
                        dataProductsubcategoryid,
                        dataProductmodelid );

        return result;
    }

    public static bool InsertProductcategory(SqlConnection sqlConnection, ref int productcategoryid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductCategory]";

        var productcategoryidParameter = command.Parameters.AddInt32("@productcategoryid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productcategoryid = (int)productcategoryidParameter.Value;
        }
        return result;
    }

    public static bool InsertProductcategory(SqlConnection sqlConnection, Types.Production.ProductcategoryDataType data )
    {
        var dataProductcategoryid = data.Productcategoryid;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductcategory( sqlConnection, 
                        ref dataProductcategoryid,
                        dataName,
                        dataRowguid,
                        dataModifieddate );
        data.Productcategoryid = dataProductcategoryid;

        return result;
    }

    public static bool UpdateProductcategory(SqlConnection sqlConnection, int productcategoryid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductCategory]";

        command.Parameters.AddInt32("@productcategoryid", productcategoryid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductcategory(SqlConnection sqlConnection, Types.Production.ProductcategoryDataType data )
    {
        var dataProductcategoryid = data.Productcategoryid;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductcategory( sqlConnection, 
                        dataProductcategoryid,
                        dataName,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductcategory(SqlConnection sqlConnection, int productcategoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductCategory]";

        command.Parameters.AddInt32("@productcategoryid", productcategoryid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductcategory(SqlConnection sqlConnection, Types.Production.ProductcategoryDataType data )
    {
        var dataProductcategoryid = data.Productcategoryid;
        var result = DeleteProductcategory( sqlConnection, 
                        dataProductcategoryid );

        return result;
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

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDecimal("@standardcost", standardcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertProductcosthistory(SqlConnection sqlConnection, Types.Production.ProductcosthistoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataStandardcost = data.Standardcost;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductcosthistory( sqlConnection, 
                        dataProductid,
                        dataStartdate,
                        dataEnddate,
                        dataStandardcost,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDecimal("@standardcost", standardcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductcosthistory(SqlConnection sqlConnection, Types.Production.ProductcosthistoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataStandardcost = data.Standardcost;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductcosthistory( sqlConnection, 
                        dataProductid,
                        dataStartdate,
                        dataEnddate,
                        dataStandardcost,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductcosthistory(SqlConnection sqlConnection, int productid,
        DateTime startdate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductCostHistory]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@startdate", startdate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductcosthistory(SqlConnection sqlConnection, Types.Production.ProductcosthistoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataStartdate = data.Startdate;
        var result = DeleteProductcosthistory( sqlConnection, 
                        dataProductid,
                        dataStartdate );

        return result;
    }

    public static bool InsertProductdescription(SqlConnection sqlConnection, ref int productdescriptionid,
        string description,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductDescription]";

        var productdescriptionidParameter = command.Parameters.AddInt32("@productdescriptionid");
        command.Parameters.AddNVarChar("@description", description, 400);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productdescriptionid = (int)productdescriptionidParameter.Value;
        }
        return result;
    }

    public static bool InsertProductdescription(SqlConnection sqlConnection, Types.Production.ProductdescriptionDataType data )
    {
        var dataProductdescriptionid = data.Productdescriptionid;
        var dataDescription = data.Description;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductdescription( sqlConnection, 
                        ref dataProductdescriptionid,
                        dataDescription,
                        dataRowguid,
                        dataModifieddate );
        data.Productdescriptionid = dataProductdescriptionid;

        return result;
    }

    public static bool UpdateProductdescription(SqlConnection sqlConnection, int productdescriptionid,
        string description,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductDescription]";

        command.Parameters.AddInt32("@productdescriptionid", productdescriptionid);
        command.Parameters.AddNVarChar("@description", description, 400);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductdescription(SqlConnection sqlConnection, Types.Production.ProductdescriptionDataType data )
    {
        var dataProductdescriptionid = data.Productdescriptionid;
        var dataDescription = data.Description;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductdescription( sqlConnection, 
                        dataProductdescriptionid,
                        dataDescription,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductdescription(SqlConnection sqlConnection, int productdescriptionid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductDescription]";

        command.Parameters.AddInt32("@productdescriptionid", productdescriptionid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductdescription(SqlConnection sqlConnection, Types.Production.ProductdescriptionDataType data )
    {
        var dataProductdescriptionid = data.Productdescriptionid;
        var result = DeleteProductdescription( sqlConnection, 
                        dataProductdescriptionid );

        return result;
    }

    public static bool InsertProductdocument(SqlConnection sqlConnection, int productid,
        SqlHierarchyId documentnode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductDocument]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddHierarchyId("@documentnode", documentnode);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertProductdocument(SqlConnection sqlConnection, Types.Production.ProductdocumentDataType data )
    {
        var dataProductid = data.Productid;
        var dataDocumentnode = data.Documentnode;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductdocument( sqlConnection, 
                        dataProductid,
                        dataDocumentnode,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateProductdocument(SqlConnection sqlConnection, int productid,
        SqlHierarchyId documentnode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductDocument]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddHierarchyId("@documentnode", documentnode);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductdocument(SqlConnection sqlConnection, Types.Production.ProductdocumentDataType data )
    {
        var dataProductid = data.Productid;
        var dataDocumentnode = data.Documentnode;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductdocument( sqlConnection, 
                        dataProductid,
                        dataDocumentnode,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductdocument(SqlConnection sqlConnection, int productid,
        SqlHierarchyId documentnode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductDocument]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddHierarchyId("@documentnode", documentnode);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductdocument(SqlConnection sqlConnection, Types.Production.ProductdocumentDataType data )
    {
        var dataProductid = data.Productid;
        var dataDocumentnode = data.Documentnode;
        var result = DeleteProductdocument( sqlConnection, 
                        dataProductid,
                        dataDocumentnode );

        return result;
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

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt16("@locationid", locationid);
        command.Parameters.AddNVarChar("@shelf", shelf, 10);
        command.Parameters.AddByte("@bin", bin);
        command.Parameters.AddInt16("@quantity", quantity);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertProductinventory(SqlConnection sqlConnection, Types.Production.ProductinventoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataLocationid = data.Locationid;
        var dataShelf = data.Shelf;
        var dataBin = data.Bin;
        var dataQuantity = data.Quantity;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductinventory( sqlConnection, 
                        dataProductid,
                        dataLocationid,
                        dataShelf,
                        dataBin,
                        dataQuantity,
                        dataRowguid,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt16("@locationid", locationid);
        command.Parameters.AddNVarChar("@shelf", shelf, 10);
        command.Parameters.AddByte("@bin", bin);
        command.Parameters.AddInt16("@quantity", quantity);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductinventory(SqlConnection sqlConnection, Types.Production.ProductinventoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataLocationid = data.Locationid;
        var dataShelf = data.Shelf;
        var dataBin = data.Bin;
        var dataQuantity = data.Quantity;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductinventory( sqlConnection, 
                        dataProductid,
                        dataLocationid,
                        dataShelf,
                        dataBin,
                        dataQuantity,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductinventory(SqlConnection sqlConnection, int productid,
        short locationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductInventory]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt16("@locationid", locationid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductinventory(SqlConnection sqlConnection, Types.Production.ProductinventoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataLocationid = data.Locationid;
        var result = DeleteProductinventory( sqlConnection, 
                        dataProductid,
                        dataLocationid );

        return result;
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

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDecimal("@listprice", listprice);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertProductlistpricehistory(SqlConnection sqlConnection, Types.Production.ProductlistpricehistoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataListprice = data.Listprice;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductlistpricehistory( sqlConnection, 
                        dataProductid,
                        dataStartdate,
                        dataEnddate,
                        dataListprice,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDecimal("@listprice", listprice);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductlistpricehistory(SqlConnection sqlConnection, Types.Production.ProductlistpricehistoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataListprice = data.Listprice;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductlistpricehistory( sqlConnection, 
                        dataProductid,
                        dataStartdate,
                        dataEnddate,
                        dataListprice,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductlistpricehistory(SqlConnection sqlConnection, int productid,
        DateTime startdate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductListPriceHistory]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@startdate", startdate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductlistpricehistory(SqlConnection sqlConnection, Types.Production.ProductlistpricehistoryDataType data )
    {
        var dataProductid = data.Productid;
        var dataStartdate = data.Startdate;
        var result = DeleteProductlistpricehistory( sqlConnection, 
                        dataProductid,
                        dataStartdate );

        return result;
    }

    public static bool InsertProductmodel(SqlConnection sqlConnection, ref int productmodelid,
        string name,
        SqlXml? catalogdescription,
        SqlXml? instructions,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductModel]";

        var productmodelidParameter = command.Parameters.AddInt32("@productmodelid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddSqlXml("@catalogdescription", catalogdescription);
        command.Parameters.AddSqlXml("@instructions", instructions);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productmodelid = (int)productmodelidParameter.Value;
        }
        return result;
    }

    public static bool InsertProductmodel(SqlConnection sqlConnection, Types.Production.ProductmodelDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataName = data.Name;
        var dataCatalogdescription = data.Catalogdescription;
        var dataInstructions = data.Instructions;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductmodel( sqlConnection, 
                        ref dataProductmodelid,
                        dataName,
                        dataCatalogdescription,
                        dataInstructions,
                        dataRowguid,
                        dataModifieddate );
        data.Productmodelid = dataProductmodelid;

        return result;
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

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddSqlXml("@catalogdescription", catalogdescription);
        command.Parameters.AddSqlXml("@instructions", instructions);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductmodel(SqlConnection sqlConnection, Types.Production.ProductmodelDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataName = data.Name;
        var dataCatalogdescription = data.Catalogdescription;
        var dataInstructions = data.Instructions;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductmodel( sqlConnection, 
                        dataProductmodelid,
                        dataName,
                        dataCatalogdescription,
                        dataInstructions,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductmodel(SqlConnection sqlConnection, int productmodelid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductModel]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductmodel(SqlConnection sqlConnection, Types.Production.ProductmodelDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var result = DeleteProductmodel( sqlConnection, 
                        dataProductmodelid );

        return result;
    }

    public static bool InsertProductmodelillustration(SqlConnection sqlConnection, int productmodelid,
        int illustrationid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductModelIllustration]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddInt32("@illustrationid", illustrationid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertProductmodelillustration(SqlConnection sqlConnection, Types.Production.ProductmodelillustrationDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataIllustrationid = data.Illustrationid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductmodelillustration( sqlConnection, 
                        dataProductmodelid,
                        dataIllustrationid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateProductmodelillustration(SqlConnection sqlConnection, int productmodelid,
        int illustrationid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductModelIllustration]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddInt32("@illustrationid", illustrationid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductmodelillustration(SqlConnection sqlConnection, Types.Production.ProductmodelillustrationDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataIllustrationid = data.Illustrationid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductmodelillustration( sqlConnection, 
                        dataProductmodelid,
                        dataIllustrationid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductmodelillustration(SqlConnection sqlConnection, int productmodelid,
        int illustrationid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductModelIllustration]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddInt32("@illustrationid", illustrationid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductmodelillustration(SqlConnection sqlConnection, Types.Production.ProductmodelillustrationDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataIllustrationid = data.Illustrationid;
        var result = DeleteProductmodelillustration( sqlConnection, 
                        dataProductmodelid,
                        dataIllustrationid );

        return result;
    }

    public static bool InsertProductmodelproductdescriptionculture(SqlConnection sqlConnection, int productmodelid,
        int productdescriptionid,
        string cultureid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductModelProductDescriptionCulture]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddInt32("@productdescriptionid", productdescriptionid);
        command.Parameters.AddNChar("@cultureid", cultureid, 6);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertProductmodelproductdescriptionculture(SqlConnection sqlConnection, Types.Production.ProductmodelproductdescriptioncultureDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataProductdescriptionid = data.Productdescriptionid;
        var dataCultureid = data.Cultureid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductmodelproductdescriptionculture( sqlConnection, 
                        dataProductmodelid,
                        dataProductdescriptionid,
                        dataCultureid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateProductmodelproductdescriptionculture(SqlConnection sqlConnection, int productmodelid,
        int productdescriptionid,
        string cultureid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductModelProductDescriptionCulture]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddInt32("@productdescriptionid", productdescriptionid);
        command.Parameters.AddNChar("@cultureid", cultureid, 6);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductmodelproductdescriptionculture(SqlConnection sqlConnection, Types.Production.ProductmodelproductdescriptioncultureDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataProductdescriptionid = data.Productdescriptionid;
        var dataCultureid = data.Cultureid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductmodelproductdescriptionculture( sqlConnection, 
                        dataProductmodelid,
                        dataProductdescriptionid,
                        dataCultureid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductmodelproductdescriptionculture(SqlConnection sqlConnection, int productmodelid,
        int productdescriptionid,
        string cultureid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductModelProductDescriptionCulture]";

        command.Parameters.AddInt32("@productmodelid", productmodelid);
        command.Parameters.AddInt32("@productdescriptionid", productdescriptionid);
        command.Parameters.AddNChar("@cultureid", cultureid, 6);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductmodelproductdescriptionculture(SqlConnection sqlConnection, Types.Production.ProductmodelproductdescriptioncultureDataType data )
    {
        var dataProductmodelid = data.Productmodelid;
        var dataProductdescriptionid = data.Productdescriptionid;
        var dataCultureid = data.Cultureid;
        var result = DeleteProductmodelproductdescriptionculture( sqlConnection, 
                        dataProductmodelid,
                        dataProductdescriptionid,
                        dataCultureid );

        return result;
    }

    public static bool InsertProductphoto(SqlConnection sqlConnection, ref int productphotoid,
        byte[]? thumbnailphoto,
        string? thumbnailphotofilename,
        byte[]? largephoto,
        string? largephotofilename,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductPhoto]";

        var productphotoidParameter = command.Parameters.AddInt32("@productphotoid");
        command.Parameters.AddBinary("@thumbnailphoto", thumbnailphoto, -1);
        command.Parameters.AddNVarChar("@thumbnailphotofilename", thumbnailphotofilename, 50);
        command.Parameters.AddBinary("@largephoto", largephoto, -1);
        command.Parameters.AddNVarChar("@largephotofilename", largephotofilename, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productphotoid = (int)productphotoidParameter.Value;
        }
        return result;
    }

    public static bool InsertProductphoto(SqlConnection sqlConnection, Types.Production.ProductphotoDataType data )
    {
        var dataProductphotoid = data.Productphotoid;
        var dataThumbnailphoto = data.Thumbnailphoto;
        var dataThumbnailphotofilename = data.Thumbnailphotofilename;
        var dataLargephoto = data.Largephoto;
        var dataLargephotofilename = data.Largephotofilename;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductphoto( sqlConnection, 
                        ref dataProductphotoid,
                        dataThumbnailphoto,
                        dataThumbnailphotofilename,
                        dataLargephoto,
                        dataLargephotofilename,
                        dataModifieddate );
        data.Productphotoid = dataProductphotoid;

        return result;
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

        command.Parameters.AddInt32("@productphotoid", productphotoid);
        command.Parameters.AddBinary("@thumbnailphoto", thumbnailphoto, -1);
        command.Parameters.AddNVarChar("@thumbnailphotofilename", thumbnailphotofilename, 50);
        command.Parameters.AddBinary("@largephoto", largephoto, -1);
        command.Parameters.AddNVarChar("@largephotofilename", largephotofilename, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductphoto(SqlConnection sqlConnection, Types.Production.ProductphotoDataType data )
    {
        var dataProductphotoid = data.Productphotoid;
        var dataThumbnailphoto = data.Thumbnailphoto;
        var dataThumbnailphotofilename = data.Thumbnailphotofilename;
        var dataLargephoto = data.Largephoto;
        var dataLargephotofilename = data.Largephotofilename;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductphoto( sqlConnection, 
                        dataProductphotoid,
                        dataThumbnailphoto,
                        dataThumbnailphotofilename,
                        dataLargephoto,
                        dataLargephotofilename,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductphoto(SqlConnection sqlConnection, int productphotoid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductPhoto]";

        command.Parameters.AddInt32("@productphotoid", productphotoid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductphoto(SqlConnection sqlConnection, Types.Production.ProductphotoDataType data )
    {
        var dataProductphotoid = data.Productphotoid;
        var result = DeleteProductphoto( sqlConnection, 
                        dataProductphotoid );

        return result;
    }

    public static bool InsertProductproductphoto(SqlConnection sqlConnection, int productid,
        int productphotoid,
        bool primary,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductProductPhoto]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@productphotoid", productphotoid);
        command.Parameters.AddBoolean("@primary", primary);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertProductproductphoto(SqlConnection sqlConnection, Types.Production.ProductproductphotoDataType data )
    {
        var dataProductid = data.Productid;
        var dataProductphotoid = data.Productphotoid;
        var dataPrimary = data.Primary;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductproductphoto( sqlConnection, 
                        dataProductid,
                        dataProductphotoid,
                        dataPrimary,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateProductproductphoto(SqlConnection sqlConnection, int productid,
        int productphotoid,
        bool primary,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateProductProductPhoto]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@productphotoid", productphotoid);
        command.Parameters.AddBoolean("@primary", primary);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductproductphoto(SqlConnection sqlConnection, Types.Production.ProductproductphotoDataType data )
    {
        var dataProductid = data.Productid;
        var dataProductphotoid = data.Productphotoid;
        var dataPrimary = data.Primary;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductproductphoto( sqlConnection, 
                        dataProductid,
                        dataProductphotoid,
                        dataPrimary,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductproductphoto(SqlConnection sqlConnection, int productid,
        int productphotoid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductProductPhoto]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@productphotoid", productphotoid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductproductphoto(SqlConnection sqlConnection, Types.Production.ProductproductphotoDataType data )
    {
        var dataProductid = data.Productid;
        var dataProductphotoid = data.Productphotoid;
        var result = DeleteProductproductphoto( sqlConnection, 
                        dataProductid,
                        dataProductphotoid );

        return result;
    }

    public static bool InsertProductreview(SqlConnection sqlConnection, ref int productreviewid,
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

        var productreviewidParameter = command.Parameters.AddInt32("@productreviewid");
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddNVarChar("@reviewername", reviewername, 50);
        command.Parameters.AddDateTime("@reviewdate", reviewdate);
        command.Parameters.AddNVarChar("@emailaddress", emailaddress, 50);
        command.Parameters.AddInt32("@rating", rating);
        command.Parameters.AddNVarChar("@comments", comments, 3850);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productreviewid = (int)productreviewidParameter.Value;
        }
        return result;
    }

    public static bool InsertProductreview(SqlConnection sqlConnection, Types.Production.ProductreviewDataType data )
    {
        var dataProductreviewid = data.Productreviewid;
        var dataProductid = data.Productid;
        var dataReviewername = data.Reviewername;
        var dataReviewdate = data.Reviewdate;
        var dataEmailaddress = data.Emailaddress;
        var dataRating = data.Rating;
        var dataComments = data.Comments;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductreview( sqlConnection, 
                        ref dataProductreviewid,
                        dataProductid,
                        dataReviewername,
                        dataReviewdate,
                        dataEmailaddress,
                        dataRating,
                        dataComments,
                        dataModifieddate );
        data.Productreviewid = dataProductreviewid;

        return result;
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

        command.Parameters.AddInt32("@productreviewid", productreviewid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddNVarChar("@reviewername", reviewername, 50);
        command.Parameters.AddDateTime("@reviewdate", reviewdate);
        command.Parameters.AddNVarChar("@emailaddress", emailaddress, 50);
        command.Parameters.AddInt32("@rating", rating);
        command.Parameters.AddNVarChar("@comments", comments, 3850);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductreview(SqlConnection sqlConnection, Types.Production.ProductreviewDataType data )
    {
        var dataProductreviewid = data.Productreviewid;
        var dataProductid = data.Productid;
        var dataReviewername = data.Reviewername;
        var dataReviewdate = data.Reviewdate;
        var dataEmailaddress = data.Emailaddress;
        var dataRating = data.Rating;
        var dataComments = data.Comments;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductreview( sqlConnection, 
                        dataProductreviewid,
                        dataProductid,
                        dataReviewername,
                        dataReviewdate,
                        dataEmailaddress,
                        dataRating,
                        dataComments,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductreview(SqlConnection sqlConnection, int productreviewid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductReview]";

        command.Parameters.AddInt32("@productreviewid", productreviewid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductreview(SqlConnection sqlConnection, Types.Production.ProductreviewDataType data )
    {
        var dataProductreviewid = data.Productreviewid;
        var result = DeleteProductreview( sqlConnection, 
                        dataProductreviewid );

        return result;
    }

    public static bool InsertProductsubcategory(SqlConnection sqlConnection, ref int productsubcategoryid,
        int productcategoryid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertProductSubcategory]";

        var productsubcategoryidParameter = command.Parameters.AddInt32("@productsubcategoryid");
        command.Parameters.AddInt32("@productcategoryid", productcategoryid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            productsubcategoryid = (int)productsubcategoryidParameter.Value;
        }
        return result;
    }

    public static bool InsertProductsubcategory(SqlConnection sqlConnection, Types.Production.ProductsubcategoryDataType data )
    {
        var dataProductsubcategoryid = data.Productsubcategoryid;
        var dataProductcategoryid = data.Productcategoryid;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductsubcategory( sqlConnection, 
                        ref dataProductsubcategoryid,
                        dataProductcategoryid,
                        dataName,
                        dataRowguid,
                        dataModifieddate );
        data.Productsubcategoryid = dataProductsubcategoryid;

        return result;
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

        command.Parameters.AddInt32("@productsubcategoryid", productsubcategoryid);
        command.Parameters.AddInt32("@productcategoryid", productcategoryid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductsubcategory(SqlConnection sqlConnection, Types.Production.ProductsubcategoryDataType data )
    {
        var dataProductsubcategoryid = data.Productsubcategoryid;
        var dataProductcategoryid = data.Productcategoryid;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductsubcategory( sqlConnection, 
                        dataProductsubcategoryid,
                        dataProductcategoryid,
                        dataName,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductsubcategory(SqlConnection sqlConnection, int productsubcategoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteProductSubcategory]";

        command.Parameters.AddInt32("@productsubcategoryid", productsubcategoryid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductsubcategory(SqlConnection sqlConnection, Types.Production.ProductsubcategoryDataType data )
    {
        var dataProductsubcategoryid = data.Productsubcategoryid;
        var result = DeleteProductsubcategory( sqlConnection, 
                        dataProductsubcategoryid );

        return result;
    }

    public static bool InsertScrapreason(SqlConnection sqlConnection, ref short scrapreasonid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertScrapReason]";

        var scrapreasonidParameter = command.Parameters.AddInt16("@scrapreasonid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            scrapreasonid = (short)scrapreasonidParameter.Value;
        }
        return result;
    }

    public static bool InsertScrapreason(SqlConnection sqlConnection, Types.Production.ScrapreasonDataType data )
    {
        var dataScrapreasonid = data.Scrapreasonid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertScrapreason( sqlConnection, 
                        ref dataScrapreasonid,
                        dataName,
                        dataModifieddate );
        data.Scrapreasonid = dataScrapreasonid;

        return result;
    }

    public static bool UpdateScrapreason(SqlConnection sqlConnection, short scrapreasonid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateScrapReason]";

        command.Parameters.AddInt16("@scrapreasonid", scrapreasonid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateScrapreason(SqlConnection sqlConnection, Types.Production.ScrapreasonDataType data )
    {
        var dataScrapreasonid = data.Scrapreasonid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateScrapreason( sqlConnection, 
                        dataScrapreasonid,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteScrapreason(SqlConnection sqlConnection, short scrapreasonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteScrapReason]";

        command.Parameters.AddInt16("@scrapreasonid", scrapreasonid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteScrapreason(SqlConnection sqlConnection, Types.Production.ScrapreasonDataType data )
    {
        var dataScrapreasonid = data.Scrapreasonid;
        var result = DeleteScrapreason( sqlConnection, 
                        dataScrapreasonid );

        return result;
    }

    public static bool InsertTransactionhistory(SqlConnection sqlConnection, ref int transactionid,
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

        var transactionidParameter = command.Parameters.AddInt32("@transactionid");
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@referenceorderid", referenceorderid);
        command.Parameters.AddInt32("@referenceorderlineid", referenceorderlineid);
        command.Parameters.AddDateTime("@transactiondate", transactiondate);
        command.Parameters.AddNChar("@transactiontype", transactiontype, 1);
        command.Parameters.AddInt32("@quantity", quantity);
        command.Parameters.AddDecimal("@actualcost", actualcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            transactionid = (int)transactionidParameter.Value;
        }
        return result;
    }

    public static bool InsertTransactionhistory(SqlConnection sqlConnection, Types.Production.TransactionhistoryDataType data )
    {
        var dataTransactionid = data.Transactionid;
        var dataProductid = data.Productid;
        var dataReferenceorderid = data.Referenceorderid;
        var dataReferenceorderlineid = data.Referenceorderlineid;
        var dataTransactiondate = data.Transactiondate;
        var dataTransactiontype = data.Transactiontype;
        var dataQuantity = data.Quantity;
        var dataActualcost = data.Actualcost;
        var dataModifieddate = data.Modifieddate;
        var result = InsertTransactionhistory( sqlConnection, 
                        ref dataTransactionid,
                        dataProductid,
                        dataReferenceorderid,
                        dataReferenceorderlineid,
                        dataTransactiondate,
                        dataTransactiontype,
                        dataQuantity,
                        dataActualcost,
                        dataModifieddate );
        data.Transactionid = dataTransactionid;

        return result;
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

        command.Parameters.AddInt32("@transactionid", transactionid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@referenceorderid", referenceorderid);
        command.Parameters.AddInt32("@referenceorderlineid", referenceorderlineid);
        command.Parameters.AddDateTime("@transactiondate", transactiondate);
        command.Parameters.AddNChar("@transactiontype", transactiontype, 1);
        command.Parameters.AddInt32("@quantity", quantity);
        command.Parameters.AddDecimal("@actualcost", actualcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateTransactionhistory(SqlConnection sqlConnection, Types.Production.TransactionhistoryDataType data )
    {
        var dataTransactionid = data.Transactionid;
        var dataProductid = data.Productid;
        var dataReferenceorderid = data.Referenceorderid;
        var dataReferenceorderlineid = data.Referenceorderlineid;
        var dataTransactiondate = data.Transactiondate;
        var dataTransactiontype = data.Transactiontype;
        var dataQuantity = data.Quantity;
        var dataActualcost = data.Actualcost;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateTransactionhistory( sqlConnection, 
                        dataTransactionid,
                        dataProductid,
                        dataReferenceorderid,
                        dataReferenceorderlineid,
                        dataTransactiondate,
                        dataTransactiontype,
                        dataQuantity,
                        dataActualcost,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteTransactionhistory(SqlConnection sqlConnection, int transactionid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteTransactionHistory]";

        command.Parameters.AddInt32("@transactionid", transactionid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteTransactionhistory(SqlConnection sqlConnection, Types.Production.TransactionhistoryDataType data )
    {
        var dataTransactionid = data.Transactionid;
        var result = DeleteTransactionhistory( sqlConnection, 
                        dataTransactionid );

        return result;
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

        command.Parameters.AddInt32("@transactionid", transactionid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@referenceorderid", referenceorderid);
        command.Parameters.AddInt32("@referenceorderlineid", referenceorderlineid);
        command.Parameters.AddDateTime("@transactiondate", transactiondate);
        command.Parameters.AddNChar("@transactiontype", transactiontype, 1);
        command.Parameters.AddInt32("@quantity", quantity);
        command.Parameters.AddDecimal("@actualcost", actualcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertTransactionhistoryarchive(SqlConnection sqlConnection, Types.Production.TransactionhistoryarchiveDataType data )
    {
        var dataTransactionid = data.Transactionid;
        var dataProductid = data.Productid;
        var dataReferenceorderid = data.Referenceorderid;
        var dataReferenceorderlineid = data.Referenceorderlineid;
        var dataTransactiondate = data.Transactiondate;
        var dataTransactiontype = data.Transactiontype;
        var dataQuantity = data.Quantity;
        var dataActualcost = data.Actualcost;
        var dataModifieddate = data.Modifieddate;
        var result = InsertTransactionhistoryarchive( sqlConnection, 
                        dataTransactionid,
                        dataProductid,
                        dataReferenceorderid,
                        dataReferenceorderlineid,
                        dataTransactiondate,
                        dataTransactiontype,
                        dataQuantity,
                        dataActualcost,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@transactionid", transactionid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@referenceorderid", referenceorderid);
        command.Parameters.AddInt32("@referenceorderlineid", referenceorderlineid);
        command.Parameters.AddDateTime("@transactiondate", transactiondate);
        command.Parameters.AddNChar("@transactiontype", transactiontype, 1);
        command.Parameters.AddInt32("@quantity", quantity);
        command.Parameters.AddDecimal("@actualcost", actualcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateTransactionhistoryarchive(SqlConnection sqlConnection, Types.Production.TransactionhistoryarchiveDataType data )
    {
        var dataTransactionid = data.Transactionid;
        var dataProductid = data.Productid;
        var dataReferenceorderid = data.Referenceorderid;
        var dataReferenceorderlineid = data.Referenceorderlineid;
        var dataTransactiondate = data.Transactiondate;
        var dataTransactiontype = data.Transactiontype;
        var dataQuantity = data.Quantity;
        var dataActualcost = data.Actualcost;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateTransactionhistoryarchive( sqlConnection, 
                        dataTransactionid,
                        dataProductid,
                        dataReferenceorderid,
                        dataReferenceorderlineid,
                        dataTransactiondate,
                        dataTransactiontype,
                        dataQuantity,
                        dataActualcost,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteTransactionhistoryarchive(SqlConnection sqlConnection, int transactionid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteTransactionHistoryArchive]";

        command.Parameters.AddInt32("@transactionid", transactionid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteTransactionhistoryarchive(SqlConnection sqlConnection, Types.Production.TransactionhistoryarchiveDataType data )
    {
        var dataTransactionid = data.Transactionid;
        var result = DeleteTransactionhistoryarchive( sqlConnection, 
                        dataTransactionid );

        return result;
    }

    public static bool InsertUnitmeasure(SqlConnection sqlConnection, string unitmeasurecode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[InsertUnitMeasure]";

        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertUnitmeasure(SqlConnection sqlConnection, Types.Production.UnitmeasureDataType data )
    {
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertUnitmeasure( sqlConnection, 
                        dataUnitmeasurecode,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateUnitmeasure(SqlConnection sqlConnection, string unitmeasurecode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[UpdateUnitMeasure]";

        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateUnitmeasure(SqlConnection sqlConnection, Types.Production.UnitmeasureDataType data )
    {
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateUnitmeasure( sqlConnection, 
                        dataUnitmeasurecode,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteUnitmeasure(SqlConnection sqlConnection, string unitmeasurecode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteUnitMeasure]";

        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteUnitmeasure(SqlConnection sqlConnection, Types.Production.UnitmeasureDataType data )
    {
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var result = DeleteUnitmeasure( sqlConnection, 
                        dataUnitmeasurecode );

        return result;
    }

    public static bool InsertWorkorder(SqlConnection sqlConnection, ref int workorderid,
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

        var workorderidParameter = command.Parameters.AddInt32("@workorderid");
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@orderqty", orderqty);
        command.Parameters.AddInt32("@stockedqty", stockedqty);
        command.Parameters.AddInt16("@scrappedqty", scrappedqty);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddInt16("@scrapreasonid", scrapreasonid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            workorderid = (int)workorderidParameter.Value;
        }
        return result;
    }

    public static bool InsertWorkorder(SqlConnection sqlConnection, Types.Production.WorkorderDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOrderqty = data.Orderqty;
        var dataStockedqty = data.Stockedqty;
        var dataScrappedqty = data.Scrappedqty;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataDuedate = data.Duedate;
        var dataScrapreasonid = data.Scrapreasonid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertWorkorder( sqlConnection, 
                        ref dataWorkorderid,
                        dataProductid,
                        dataOrderqty,
                        dataStockedqty,
                        dataScrappedqty,
                        dataStartdate,
                        dataEnddate,
                        dataDuedate,
                        dataScrapreasonid,
                        dataModifieddate );
        data.Workorderid = dataWorkorderid;

        return result;
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

        command.Parameters.AddInt32("@workorderid", workorderid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@orderqty", orderqty);
        command.Parameters.AddInt32("@stockedqty", stockedqty);
        command.Parameters.AddInt16("@scrappedqty", scrappedqty);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddInt16("@scrapreasonid", scrapreasonid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateWorkorder(SqlConnection sqlConnection, Types.Production.WorkorderDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOrderqty = data.Orderqty;
        var dataStockedqty = data.Stockedqty;
        var dataScrappedqty = data.Scrappedqty;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataDuedate = data.Duedate;
        var dataScrapreasonid = data.Scrapreasonid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateWorkorder( sqlConnection, 
                        dataWorkorderid,
                        dataProductid,
                        dataOrderqty,
                        dataStockedqty,
                        dataScrappedqty,
                        dataStartdate,
                        dataEnddate,
                        dataDuedate,
                        dataScrapreasonid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteWorkorder(SqlConnection sqlConnection, int workorderid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteWorkOrder]";

        command.Parameters.AddInt32("@workorderid", workorderid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteWorkorder(SqlConnection sqlConnection, Types.Production.WorkorderDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var result = DeleteWorkorder( sqlConnection, 
                        dataWorkorderid );

        return result;
    }

    public static bool Insert1Workorder(SqlConnection sqlConnection, ref int workorderid,
        int productid,
        int orderqty,
        short scrappedqty,
        DateTime startdate,
        DateTime? enddate,
        DateTime duedate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Insert1WorkOrder]";

        var workorderidParameter = command.Parameters.AddInt32("@workorderid");
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@orderqty", orderqty);
        command.Parameters.AddInt16("@scrappedqty", scrappedqty);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            workorderid = (int)workorderidParameter.Value;
        }
        return result;
    }

    public static bool Insert1Workorder(SqlConnection sqlConnection, Types.Production.WorkorderDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOrderqty = data.Orderqty;
        var dataScrappedqty = data.Scrappedqty;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataDuedate = data.Duedate;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Workorder( sqlConnection, 
                        ref dataWorkorderid,
                        dataProductid,
                        dataOrderqty,
                        dataScrappedqty,
                        dataStartdate,
                        dataEnddate,
                        dataDuedate,
                        dataModifieddate );
        data.Workorderid = dataWorkorderid;

        return result;
    }

    public static bool Update1Workorder(SqlConnection sqlConnection, int workorderid,
        int productid,
        int orderqty,
        short scrappedqty,
        DateTime startdate,
        DateTime? enddate,
        DateTime duedate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update1WorkOrder]";

        command.Parameters.AddInt32("@workorderid", workorderid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@orderqty", orderqty);
        command.Parameters.AddInt16("@scrappedqty", scrappedqty);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update2Workorder(SqlConnection sqlConnection, int workorderid,
        short? scrapreasonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[Update2WorkOrder]";

        command.Parameters.AddInt32("@workorderid", workorderid);
        command.Parameters.AddInt16("@scrapreasonid", scrapreasonid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Workorder(SqlConnection sqlConnection, Types.Production.WorkorderDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOrderqty = data.Orderqty;
        var dataScrappedqty = data.Scrappedqty;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataDuedate = data.Duedate;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Workorder( sqlConnection, 
                        dataWorkorderid,
                        dataProductid,
                        dataOrderqty,
                        dataScrappedqty,
                        dataStartdate,
                        dataEnddate,
                        dataDuedate,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Workorder(SqlConnection sqlConnection, Types.Production.WorkorderDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataScrapreasonid = data.Scrapreasonid;
        var result = Update2Workorder( sqlConnection, 
                        dataWorkorderid,
                        dataScrapreasonid );

        return result;
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

        command.Parameters.AddInt32("@workorderid", workorderid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt16("@operationsequence", operationsequence);
        command.Parameters.AddInt16("@locationid", locationid);
        command.Parameters.AddDateTime("@scheduledstartdate", scheduledstartdate);
        command.Parameters.AddDateTime("@scheduledenddate", scheduledenddate);
        command.Parameters.AddDateTime("@actualstartdate", actualstartdate);
        command.Parameters.AddDateTime("@actualenddate", actualenddate);
        command.Parameters.AddDecimal("@actualresourcehrs", actualresourcehrs);
        command.Parameters.AddDecimal("@plannedcost", plannedcost);
        command.Parameters.AddDecimal("@actualcost", actualcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertWorkorderrouting(SqlConnection sqlConnection, Types.Production.WorkorderroutingDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOperationsequence = data.Operationsequence;
        var dataLocationid = data.Locationid;
        var dataScheduledstartdate = data.Scheduledstartdate;
        var dataScheduledenddate = data.Scheduledenddate;
        var dataActualstartdate = data.Actualstartdate;
        var dataActualenddate = data.Actualenddate;
        var dataActualresourcehrs = data.Actualresourcehrs;
        var dataPlannedcost = data.Plannedcost;
        var dataActualcost = data.Actualcost;
        var dataModifieddate = data.Modifieddate;
        var result = InsertWorkorderrouting( sqlConnection, 
                        dataWorkorderid,
                        dataProductid,
                        dataOperationsequence,
                        dataLocationid,
                        dataScheduledstartdate,
                        dataScheduledenddate,
                        dataActualstartdate,
                        dataActualenddate,
                        dataActualresourcehrs,
                        dataPlannedcost,
                        dataActualcost,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@workorderid", workorderid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt16("@operationsequence", operationsequence);
        command.Parameters.AddInt16("@locationid", locationid);
        command.Parameters.AddDateTime("@scheduledstartdate", scheduledstartdate);
        command.Parameters.AddDateTime("@scheduledenddate", scheduledenddate);
        command.Parameters.AddDateTime("@actualstartdate", actualstartdate);
        command.Parameters.AddDateTime("@actualenddate", actualenddate);
        command.Parameters.AddDecimal("@actualresourcehrs", actualresourcehrs);
        command.Parameters.AddDecimal("@plannedcost", plannedcost);
        command.Parameters.AddDecimal("@actualcost", actualcost);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateWorkorderrouting(SqlConnection sqlConnection, Types.Production.WorkorderroutingDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOperationsequence = data.Operationsequence;
        var dataLocationid = data.Locationid;
        var dataScheduledstartdate = data.Scheduledstartdate;
        var dataScheduledenddate = data.Scheduledenddate;
        var dataActualstartdate = data.Actualstartdate;
        var dataActualenddate = data.Actualenddate;
        var dataActualresourcehrs = data.Actualresourcehrs;
        var dataPlannedcost = data.Plannedcost;
        var dataActualcost = data.Actualcost;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateWorkorderrouting( sqlConnection, 
                        dataWorkorderid,
                        dataProductid,
                        dataOperationsequence,
                        dataLocationid,
                        dataScheduledstartdate,
                        dataScheduledenddate,
                        dataActualstartdate,
                        dataActualenddate,
                        dataActualresourcehrs,
                        dataPlannedcost,
                        dataActualcost,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteWorkorderrouting(SqlConnection sqlConnection, int workorderid,
        int productid,
        short operationsequence)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Production].[DeleteWorkOrderRouting]";

        command.Parameters.AddInt32("@workorderid", workorderid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt16("@operationsequence", operationsequence);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteWorkorderrouting(SqlConnection sqlConnection, Types.Production.WorkorderroutingDataType data )
    {
        var dataWorkorderid = data.Workorderid;
        var dataProductid = data.Productid;
        var dataOperationsequence = data.Operationsequence;
        var result = DeleteWorkorderrouting( sqlConnection, 
                        dataWorkorderid,
                        dataProductid,
                        dataOperationsequence );

        return result;
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

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@averageleadtime", averageleadtime);
        command.Parameters.AddDecimal("@standardprice", standardprice);
        command.Parameters.AddDecimal("@lastreceiptcost", lastreceiptcost);
        command.Parameters.AddDateTime("@lastreceiptdate", lastreceiptdate);
        command.Parameters.AddInt32("@minorderqty", minorderqty);
        command.Parameters.AddInt32("@maxorderqty", maxorderqty);
        command.Parameters.AddInt32("@onorderqty", onorderqty);
        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertProductvendor(SqlConnection sqlConnection, Types.Purchasing.ProductvendorDataType data )
    {
        var dataProductid = data.Productid;
        var dataBusinessentityid = data.Businessentityid;
        var dataAverageleadtime = data.Averageleadtime;
        var dataStandardprice = data.Standardprice;
        var dataLastreceiptcost = data.Lastreceiptcost;
        var dataLastreceiptdate = data.Lastreceiptdate;
        var dataMinorderqty = data.Minorderqty;
        var dataMaxorderqty = data.Maxorderqty;
        var dataOnorderqty = data.Onorderqty;
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductvendor( sqlConnection, 
                        dataProductid,
                        dataBusinessentityid,
                        dataAverageleadtime,
                        dataStandardprice,
                        dataLastreceiptcost,
                        dataLastreceiptdate,
                        dataMinorderqty,
                        dataMaxorderqty,
                        dataOnorderqty,
                        dataUnitmeasurecode,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@averageleadtime", averageleadtime);
        command.Parameters.AddDecimal("@standardprice", standardprice);
        command.Parameters.AddDecimal("@lastreceiptcost", lastreceiptcost);
        command.Parameters.AddDateTime("@lastreceiptdate", lastreceiptdate);
        command.Parameters.AddInt32("@minorderqty", minorderqty);
        command.Parameters.AddInt32("@maxorderqty", maxorderqty);
        command.Parameters.AddInt32("@onorderqty", onorderqty);
        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductvendor(SqlConnection sqlConnection, Types.Purchasing.ProductvendorDataType data )
    {
        var dataProductid = data.Productid;
        var dataBusinessentityid = data.Businessentityid;
        var dataAverageleadtime = data.Averageleadtime;
        var dataStandardprice = data.Standardprice;
        var dataLastreceiptcost = data.Lastreceiptcost;
        var dataLastreceiptdate = data.Lastreceiptdate;
        var dataMinorderqty = data.Minorderqty;
        var dataMaxorderqty = data.Maxorderqty;
        var dataOnorderqty = data.Onorderqty;
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductvendor( sqlConnection, 
                        dataProductid,
                        dataBusinessentityid,
                        dataAverageleadtime,
                        dataStandardprice,
                        dataLastreceiptcost,
                        dataLastreceiptdate,
                        dataMinorderqty,
                        dataMaxorderqty,
                        dataOnorderqty,
                        dataUnitmeasurecode,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductvendor(SqlConnection sqlConnection, int productid,
        int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeleteProductVendor]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductvendor(SqlConnection sqlConnection, Types.Purchasing.ProductvendorDataType data )
    {
        var dataProductid = data.Productid;
        var dataBusinessentityid = data.Businessentityid;
        var result = DeleteProductvendor( sqlConnection, 
                        dataProductid,
                        dataBusinessentityid );

        return result;
    }

    public static bool InsertPurchaseorderdetail(SqlConnection sqlConnection, int purchaseorderid,
        ref int purchaseorderdetailid,
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

        command.Parameters.AddInt32("@purchaseorderid", purchaseorderid);
        var purchaseorderdetailidParameter = command.Parameters.AddInt32("@purchaseorderdetailid");
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddInt16("@orderqty", orderqty);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDecimal("@unitprice", unitprice);
        command.Parameters.AddDecimal("@linetotal", linetotal);
        command.Parameters.AddDecimal("@receivedqty", receivedqty);
        command.Parameters.AddDecimal("@rejectedqty", rejectedqty);
        command.Parameters.AddDecimal("@stockedqty", stockedqty);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            purchaseorderdetailid = (int)purchaseorderdetailidParameter.Value;
        }
        return result;
    }

    public static bool InsertPurchaseorderdetail(SqlConnection sqlConnection, Types.Purchasing.PurchaseorderdetailDataType data )
    {
        var dataPurchaseorderid = data.Purchaseorderid;
        var dataPurchaseorderdetailid = data.Purchaseorderdetailid;
        var dataDuedate = data.Duedate;
        var dataOrderqty = data.Orderqty;
        var dataProductid = data.Productid;
        var dataUnitprice = data.Unitprice;
        var dataLinetotal = data.Linetotal;
        var dataReceivedqty = data.Receivedqty;
        var dataRejectedqty = data.Rejectedqty;
        var dataStockedqty = data.Stockedqty;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPurchaseorderdetail( sqlConnection, 
                        dataPurchaseorderid,
                        ref dataPurchaseorderdetailid,
                        dataDuedate,
                        dataOrderqty,
                        dataProductid,
                        dataUnitprice,
                        dataLinetotal,
                        dataReceivedqty,
                        dataRejectedqty,
                        dataStockedqty,
                        dataModifieddate );
        data.Purchaseorderdetailid = dataPurchaseorderdetailid;

        return result;
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

        command.Parameters.AddInt32("@purchaseorderid", purchaseorderid);
        command.Parameters.AddInt32("@purchaseorderdetailid", purchaseorderdetailid);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddInt16("@orderqty", orderqty);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDecimal("@unitprice", unitprice);
        command.Parameters.AddDecimal("@linetotal", linetotal);
        command.Parameters.AddDecimal("@receivedqty", receivedqty);
        command.Parameters.AddDecimal("@rejectedqty", rejectedqty);
        command.Parameters.AddDecimal("@stockedqty", stockedqty);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePurchaseorderdetail(SqlConnection sqlConnection, Types.Purchasing.PurchaseorderdetailDataType data )
    {
        var dataPurchaseorderid = data.Purchaseorderid;
        var dataPurchaseorderdetailid = data.Purchaseorderdetailid;
        var dataDuedate = data.Duedate;
        var dataOrderqty = data.Orderqty;
        var dataProductid = data.Productid;
        var dataUnitprice = data.Unitprice;
        var dataLinetotal = data.Linetotal;
        var dataReceivedqty = data.Receivedqty;
        var dataRejectedqty = data.Rejectedqty;
        var dataStockedqty = data.Stockedqty;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePurchaseorderdetail( sqlConnection, 
                        dataPurchaseorderid,
                        dataPurchaseorderdetailid,
                        dataDuedate,
                        dataOrderqty,
                        dataProductid,
                        dataUnitprice,
                        dataLinetotal,
                        dataReceivedqty,
                        dataRejectedqty,
                        dataStockedqty,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePurchaseorderdetail(SqlConnection sqlConnection, int purchaseorderid,
        int purchaseorderdetailid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeletePurchaseOrderDetail]";

        command.Parameters.AddInt32("@purchaseorderid", purchaseorderid);
        command.Parameters.AddInt32("@purchaseorderdetailid", purchaseorderdetailid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePurchaseorderdetail(SqlConnection sqlConnection, Types.Purchasing.PurchaseorderdetailDataType data )
    {
        var dataPurchaseorderid = data.Purchaseorderid;
        var dataPurchaseorderdetailid = data.Purchaseorderdetailid;
        var result = DeletePurchaseorderdetail( sqlConnection, 
                        dataPurchaseorderid,
                        dataPurchaseorderdetailid );

        return result;
    }

    public static bool InsertPurchaseorderheader(SqlConnection sqlConnection, ref int purchaseorderid,
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

        var purchaseorderidParameter = command.Parameters.AddInt32("@purchaseorderid");
        command.Parameters.AddByte("@revisionnumber", revisionnumber);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddInt32("@employeeid", employeeid);
        command.Parameters.AddInt32("@vendorid", vendorid);
        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddDateTime("@orderdate", orderdate);
        command.Parameters.AddDateTime("@shipdate", shipdate);
        command.Parameters.AddDecimal("@subtotal", subtotal);
        command.Parameters.AddDecimal("@taxamt", taxamt);
        command.Parameters.AddDecimal("@freight", freight);
        command.Parameters.AddDecimal("@totaldue", totaldue);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            purchaseorderid = (int)purchaseorderidParameter.Value;
        }
        return result;
    }

    public static bool InsertPurchaseorderheader(SqlConnection sqlConnection, Types.Purchasing.PurchaseorderheaderDataType data )
    {
        var dataPurchaseorderid = data.Purchaseorderid;
        var dataRevisionnumber = data.Revisionnumber;
        var dataStatus = data.Status;
        var dataEmployeeid = data.Employeeid;
        var dataVendorid = data.Vendorid;
        var dataShipmethodid = data.Shipmethodid;
        var dataOrderdate = data.Orderdate;
        var dataShipdate = data.Shipdate;
        var dataSubtotal = data.Subtotal;
        var dataTaxamt = data.Taxamt;
        var dataFreight = data.Freight;
        var dataTotaldue = data.Totaldue;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPurchaseorderheader( sqlConnection, 
                        ref dataPurchaseorderid,
                        dataRevisionnumber,
                        dataStatus,
                        dataEmployeeid,
                        dataVendorid,
                        dataShipmethodid,
                        dataOrderdate,
                        dataShipdate,
                        dataSubtotal,
                        dataTaxamt,
                        dataFreight,
                        dataTotaldue,
                        dataModifieddate );
        data.Purchaseorderid = dataPurchaseorderid;

        return result;
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

        command.Parameters.AddInt32("@purchaseorderid", purchaseorderid);
        command.Parameters.AddByte("@revisionnumber", revisionnumber);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddInt32("@employeeid", employeeid);
        command.Parameters.AddInt32("@vendorid", vendorid);
        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddDateTime("@orderdate", orderdate);
        command.Parameters.AddDateTime("@shipdate", shipdate);
        command.Parameters.AddDecimal("@subtotal", subtotal);
        command.Parameters.AddDecimal("@taxamt", taxamt);
        command.Parameters.AddDecimal("@freight", freight);
        command.Parameters.AddDecimal("@totaldue", totaldue);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePurchaseorderheader(SqlConnection sqlConnection, Types.Purchasing.PurchaseorderheaderDataType data )
    {
        var dataPurchaseorderid = data.Purchaseorderid;
        var dataRevisionnumber = data.Revisionnumber;
        var dataStatus = data.Status;
        var dataEmployeeid = data.Employeeid;
        var dataVendorid = data.Vendorid;
        var dataShipmethodid = data.Shipmethodid;
        var dataOrderdate = data.Orderdate;
        var dataShipdate = data.Shipdate;
        var dataSubtotal = data.Subtotal;
        var dataTaxamt = data.Taxamt;
        var dataFreight = data.Freight;
        var dataTotaldue = data.Totaldue;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePurchaseorderheader( sqlConnection, 
                        dataPurchaseorderid,
                        dataRevisionnumber,
                        dataStatus,
                        dataEmployeeid,
                        dataVendorid,
                        dataShipmethodid,
                        dataOrderdate,
                        dataShipdate,
                        dataSubtotal,
                        dataTaxamt,
                        dataFreight,
                        dataTotaldue,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePurchaseorderheader(SqlConnection sqlConnection, int purchaseorderid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeletePurchaseOrderHeader]";

        command.Parameters.AddInt32("@purchaseorderid", purchaseorderid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePurchaseorderheader(SqlConnection sqlConnection, Types.Purchasing.PurchaseorderheaderDataType data )
    {
        var dataPurchaseorderid = data.Purchaseorderid;
        var result = DeletePurchaseorderheader( sqlConnection, 
                        dataPurchaseorderid );

        return result;
    }

    public static bool InsertShipmethod(SqlConnection sqlConnection, ref int shipmethodid,
        string name,
        decimal shipbase,
        decimal shiprate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[InsertShipMethod]";

        var shipmethodidParameter = command.Parameters.AddInt32("@shipmethodid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDecimal("@shipbase", shipbase);
        command.Parameters.AddDecimal("@shiprate", shiprate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            shipmethodid = (int)shipmethodidParameter.Value;
        }
        return result;
    }

    public static bool InsertShipmethod(SqlConnection sqlConnection, Types.Purchasing.ShipmethodDataType data )
    {
        var dataShipmethodid = data.Shipmethodid;
        var dataName = data.Name;
        var dataShipbase = data.Shipbase;
        var dataShiprate = data.Shiprate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertShipmethod( sqlConnection, 
                        ref dataShipmethodid,
                        dataName,
                        dataShipbase,
                        dataShiprate,
                        dataRowguid,
                        dataModifieddate );
        data.Shipmethodid = dataShipmethodid;

        return result;
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

        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDecimal("@shipbase", shipbase);
        command.Parameters.AddDecimal("@shiprate", shiprate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateShipmethod(SqlConnection sqlConnection, Types.Purchasing.ShipmethodDataType data )
    {
        var dataShipmethodid = data.Shipmethodid;
        var dataName = data.Name;
        var dataShipbase = data.Shipbase;
        var dataShiprate = data.Shiprate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateShipmethod( sqlConnection, 
                        dataShipmethodid,
                        dataName,
                        dataShipbase,
                        dataShiprate,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteShipmethod(SqlConnection sqlConnection, int shipmethodid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeleteShipMethod]";

        command.Parameters.AddInt32("@shipmethodid", shipmethodid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteShipmethod(SqlConnection sqlConnection, Types.Purchasing.ShipmethodDataType data )
    {
        var dataShipmethodid = data.Shipmethodid;
        var result = DeleteShipmethod( sqlConnection, 
                        dataShipmethodid );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@accountnumber", accountnumber, 15);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddByte("@creditrating", creditrating);
        command.Parameters.AddBoolean("@preferredvendorstatus", preferredvendorstatus);
        command.Parameters.AddBoolean("@activeflag", activeflag);
        command.Parameters.AddNVarChar("@purchasingwebserviceurl", purchasingwebserviceurl, 1024);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertVendor(SqlConnection sqlConnection, Types.Purchasing.VendorDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataAccountnumber = data.Accountnumber;
        var dataName = data.Name;
        var dataCreditrating = data.Creditrating;
        var dataPreferredvendorstatus = data.Preferredvendorstatus;
        var dataActiveflag = data.Activeflag;
        var dataPurchasingwebserviceurl = data.Purchasingwebserviceurl;
        var dataModifieddate = data.Modifieddate;
        var result = InsertVendor( sqlConnection, 
                        dataBusinessentityid,
                        dataAccountnumber,
                        dataName,
                        dataCreditrating,
                        dataPreferredvendorstatus,
                        dataActiveflag,
                        dataPurchasingwebserviceurl,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@accountnumber", accountnumber, 15);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddByte("@creditrating", creditrating);
        command.Parameters.AddBoolean("@preferredvendorstatus", preferredvendorstatus);
        command.Parameters.AddBoolean("@activeflag", activeflag);
        command.Parameters.AddNVarChar("@purchasingwebserviceurl", purchasingwebserviceurl, 1024);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateVendor(SqlConnection sqlConnection, Types.Purchasing.VendorDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataAccountnumber = data.Accountnumber;
        var dataName = data.Name;
        var dataCreditrating = data.Creditrating;
        var dataPreferredvendorstatus = data.Preferredvendorstatus;
        var dataActiveflag = data.Activeflag;
        var dataPurchasingwebserviceurl = data.Purchasingwebserviceurl;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateVendor( sqlConnection, 
                        dataBusinessentityid,
                        dataAccountnumber,
                        dataName,
                        dataCreditrating,
                        dataPreferredvendorstatus,
                        dataActiveflag,
                        dataPurchasingwebserviceurl,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteVendor(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeleteVendor]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteVendor(SqlConnection sqlConnection, Types.Purchasing.VendorDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var result = DeleteVendor( sqlConnection, 
                        dataBusinessentityid );

        return result;
    }

    public static bool InsertCountryregioncurrency(SqlConnection sqlConnection, string countryregioncode,
        string currencycode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertCountryRegionCurrency]";

        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNChar("@currencycode", currencycode, 3);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertCountryregioncurrency(SqlConnection sqlConnection, Types.Sales.CountryregioncurrencyDataType data )
    {
        var dataCountryregioncode = data.Countryregioncode;
        var dataCurrencycode = data.Currencycode;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCountryregioncurrency( sqlConnection, 
                        dataCountryregioncode,
                        dataCurrencycode,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateCountryregioncurrency(SqlConnection sqlConnection, string countryregioncode,
        string currencycode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateCountryRegionCurrency]";

        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNChar("@currencycode", currencycode, 3);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCountryregioncurrency(SqlConnection sqlConnection, Types.Sales.CountryregioncurrencyDataType data )
    {
        var dataCountryregioncode = data.Countryregioncode;
        var dataCurrencycode = data.Currencycode;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCountryregioncurrency( sqlConnection, 
                        dataCountryregioncode,
                        dataCurrencycode,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCountryregioncurrency(SqlConnection sqlConnection, string countryregioncode,
        string currencycode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCountryRegionCurrency]";

        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNChar("@currencycode", currencycode, 3);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCountryregioncurrency(SqlConnection sqlConnection, Types.Sales.CountryregioncurrencyDataType data )
    {
        var dataCountryregioncode = data.Countryregioncode;
        var dataCurrencycode = data.Currencycode;
        var result = DeleteCountryregioncurrency( sqlConnection, 
                        dataCountryregioncode,
                        dataCurrencycode );

        return result;
    }

    public static bool InsertCreditcard(SqlConnection sqlConnection, ref int creditcardid,
        string cardtype,
        string cardnumber,
        byte expmonth,
        short expyear,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertCreditCard]";

        var creditcardidParameter = command.Parameters.AddInt32("@creditcardid");
        command.Parameters.AddNVarChar("@cardtype", cardtype, 50);
        command.Parameters.AddNVarChar("@cardnumber", cardnumber, 25);
        command.Parameters.AddByte("@expmonth", expmonth);
        command.Parameters.AddInt16("@expyear", expyear);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            creditcardid = (int)creditcardidParameter.Value;
        }
        return result;
    }

    public static bool InsertCreditcard(SqlConnection sqlConnection, Types.Sales.CreditcardDataType data )
    {
        var dataCreditcardid = data.Creditcardid;
        var dataCardtype = data.Cardtype;
        var dataCardnumber = data.Cardnumber;
        var dataExpmonth = data.Expmonth;
        var dataExpyear = data.Expyear;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCreditcard( sqlConnection, 
                        ref dataCreditcardid,
                        dataCardtype,
                        dataCardnumber,
                        dataExpmonth,
                        dataExpyear,
                        dataModifieddate );
        data.Creditcardid = dataCreditcardid;

        return result;
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

        command.Parameters.AddInt32("@creditcardid", creditcardid);
        command.Parameters.AddNVarChar("@cardtype", cardtype, 50);
        command.Parameters.AddNVarChar("@cardnumber", cardnumber, 25);
        command.Parameters.AddByte("@expmonth", expmonth);
        command.Parameters.AddInt16("@expyear", expyear);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCreditcard(SqlConnection sqlConnection, Types.Sales.CreditcardDataType data )
    {
        var dataCreditcardid = data.Creditcardid;
        var dataCardtype = data.Cardtype;
        var dataCardnumber = data.Cardnumber;
        var dataExpmonth = data.Expmonth;
        var dataExpyear = data.Expyear;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCreditcard( sqlConnection, 
                        dataCreditcardid,
                        dataCardtype,
                        dataCardnumber,
                        dataExpmonth,
                        dataExpyear,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCreditcard(SqlConnection sqlConnection, int creditcardid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCreditCard]";

        command.Parameters.AddInt32("@creditcardid", creditcardid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCreditcard(SqlConnection sqlConnection, Types.Sales.CreditcardDataType data )
    {
        var dataCreditcardid = data.Creditcardid;
        var result = DeleteCreditcard( sqlConnection, 
                        dataCreditcardid );

        return result;
    }

    public static bool InsertCurrency(SqlConnection sqlConnection, string currencycode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertCurrency]";

        command.Parameters.AddNChar("@currencycode", currencycode, 3);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertCurrency(SqlConnection sqlConnection, Types.Sales.CurrencyDataType data )
    {
        var dataCurrencycode = data.Currencycode;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCurrency( sqlConnection, 
                        dataCurrencycode,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateCurrency(SqlConnection sqlConnection, string currencycode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateCurrency]";

        command.Parameters.AddNChar("@currencycode", currencycode, 3);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCurrency(SqlConnection sqlConnection, Types.Sales.CurrencyDataType data )
    {
        var dataCurrencycode = data.Currencycode;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCurrency( sqlConnection, 
                        dataCurrencycode,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCurrency(SqlConnection sqlConnection, string currencycode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCurrency]";

        command.Parameters.AddNChar("@currencycode", currencycode, 3);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCurrency(SqlConnection sqlConnection, Types.Sales.CurrencyDataType data )
    {
        var dataCurrencycode = data.Currencycode;
        var result = DeleteCurrency( sqlConnection, 
                        dataCurrencycode );

        return result;
    }

    public static bool InsertCurrencyrate(SqlConnection sqlConnection, ref int currencyrateid,
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

        var currencyrateidParameter = command.Parameters.AddInt32("@currencyrateid");
        command.Parameters.AddDateTime("@currencyratedate", currencyratedate);
        command.Parameters.AddNChar("@fromcurrencycode", fromcurrencycode, 3);
        command.Parameters.AddNChar("@tocurrencycode", tocurrencycode, 3);
        command.Parameters.AddDecimal("@averagerate", averagerate);
        command.Parameters.AddDecimal("@endofdayrate", endofdayrate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            currencyrateid = (int)currencyrateidParameter.Value;
        }
        return result;
    }

    public static bool InsertCurrencyrate(SqlConnection sqlConnection, Types.Sales.CurrencyrateDataType data )
    {
        var dataCurrencyrateid = data.Currencyrateid;
        var dataCurrencyratedate = data.Currencyratedate;
        var dataFromcurrencycode = data.Fromcurrencycode;
        var dataTocurrencycode = data.Tocurrencycode;
        var dataAveragerate = data.Averagerate;
        var dataEndofdayrate = data.Endofdayrate;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCurrencyrate( sqlConnection, 
                        ref dataCurrencyrateid,
                        dataCurrencyratedate,
                        dataFromcurrencycode,
                        dataTocurrencycode,
                        dataAveragerate,
                        dataEndofdayrate,
                        dataModifieddate );
        data.Currencyrateid = dataCurrencyrateid;

        return result;
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

        command.Parameters.AddInt32("@currencyrateid", currencyrateid);
        command.Parameters.AddDateTime("@currencyratedate", currencyratedate);
        command.Parameters.AddNChar("@fromcurrencycode", fromcurrencycode, 3);
        command.Parameters.AddNChar("@tocurrencycode", tocurrencycode, 3);
        command.Parameters.AddDecimal("@averagerate", averagerate);
        command.Parameters.AddDecimal("@endofdayrate", endofdayrate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCurrencyrate(SqlConnection sqlConnection, Types.Sales.CurrencyrateDataType data )
    {
        var dataCurrencyrateid = data.Currencyrateid;
        var dataCurrencyratedate = data.Currencyratedate;
        var dataFromcurrencycode = data.Fromcurrencycode;
        var dataTocurrencycode = data.Tocurrencycode;
        var dataAveragerate = data.Averagerate;
        var dataEndofdayrate = data.Endofdayrate;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCurrencyrate( sqlConnection, 
                        dataCurrencyrateid,
                        dataCurrencyratedate,
                        dataFromcurrencycode,
                        dataTocurrencycode,
                        dataAveragerate,
                        dataEndofdayrate,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCurrencyrate(SqlConnection sqlConnection, int currencyrateid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCurrencyRate]";

        command.Parameters.AddInt32("@currencyrateid", currencyrateid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCurrencyrate(SqlConnection sqlConnection, Types.Sales.CurrencyrateDataType data )
    {
        var dataCurrencyrateid = data.Currencyrateid;
        var result = DeleteCurrencyrate( sqlConnection, 
                        dataCurrencyrateid );

        return result;
    }

    public static bool InsertCustomer(SqlConnection sqlConnection, ref int customerid,
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

        var customeridParameter = command.Parameters.AddInt32("@customerid");
        command.Parameters.AddInt32("@personid", personid);
        command.Parameters.AddInt32("@storeid", storeid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddVarChar("@accountnumber", accountnumber, 10);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            customerid = (int)customeridParameter.Value;
        }
        return result;
    }

    public static bool InsertCustomer(SqlConnection sqlConnection, Types.Sales.CustomerDataType data )
    {
        var dataCustomerid = data.Customerid;
        var dataPersonid = data.Personid;
        var dataStoreid = data.Storeid;
        var dataTerritoryid = data.Territoryid;
        var dataAccountnumber = data.Accountnumber;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCustomer( sqlConnection, 
                        ref dataCustomerid,
                        dataPersonid,
                        dataStoreid,
                        dataTerritoryid,
                        dataAccountnumber,
                        dataRowguid,
                        dataModifieddate );
        data.Customerid = dataCustomerid;

        return result;
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

        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddInt32("@personid", personid);
        command.Parameters.AddInt32("@storeid", storeid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddVarChar("@accountnumber", accountnumber, 10);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCustomer(SqlConnection sqlConnection, Types.Sales.CustomerDataType data )
    {
        var dataCustomerid = data.Customerid;
        var dataPersonid = data.Personid;
        var dataStoreid = data.Storeid;
        var dataTerritoryid = data.Territoryid;
        var dataAccountnumber = data.Accountnumber;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCustomer( sqlConnection, 
                        dataCustomerid,
                        dataPersonid,
                        dataStoreid,
                        dataTerritoryid,
                        dataAccountnumber,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCustomer(SqlConnection sqlConnection, int customerid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCustomer]";

        command.Parameters.AddInt32("@customerid", customerid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCustomer(SqlConnection sqlConnection, Types.Sales.CustomerDataType data )
    {
        var dataCustomerid = data.Customerid;
        var result = DeleteCustomer( sqlConnection, 
                        dataCustomerid );

        return result;
    }

    public static bool Insert1Customer(SqlConnection sqlConnection, ref int customerid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Insert1Customer]";

        var customeridParameter = command.Parameters.AddInt32("@customerid");
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            customerid = (int)customeridParameter.Value;
        }
        return result;
    }

    public static bool Insert1Customer(SqlConnection sqlConnection, Types.Sales.CustomerDataType data )
    {
        var dataCustomerid = data.Customerid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Customer( sqlConnection, 
                        ref dataCustomerid,
                        dataRowguid,
                        dataModifieddate );
        data.Customerid = dataCustomerid;

        return result;
    }

    public static bool Update1Customer(SqlConnection sqlConnection, int customerid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update1Customer]";

        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update2Customer(SqlConnection sqlConnection, int customerid,
        int? personid,
        int? storeid,
        int? territoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update2Customer]";

        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddInt32("@personid", personid);
        command.Parameters.AddInt32("@storeid", storeid);
        command.Parameters.AddInt32("@territoryid", territoryid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Customer(SqlConnection sqlConnection, Types.Sales.CustomerDataType data )
    {
        var dataCustomerid = data.Customerid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Customer( sqlConnection, 
                        dataCustomerid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Customer(SqlConnection sqlConnection, Types.Sales.CustomerDataType data )
    {
        var dataCustomerid = data.Customerid;
        var dataPersonid = data.Personid;
        var dataStoreid = data.Storeid;
        var dataTerritoryid = data.Territoryid;
        var result = Update2Customer( sqlConnection, 
                        dataCustomerid,
                        dataPersonid,
                        dataStoreid,
                        dataTerritoryid );

        return result;
    }

    public static bool InsertPersoncreditcard(SqlConnection sqlConnection, int businessentityid,
        int creditcardid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertPersonCreditCard]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@creditcardid", creditcardid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertPersoncreditcard(SqlConnection sqlConnection, Types.Sales.PersoncreditcardDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataCreditcardid = data.Creditcardid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPersoncreditcard( sqlConnection, 
                        dataBusinessentityid,
                        dataCreditcardid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdatePersoncreditcard(SqlConnection sqlConnection, int businessentityid,
        int creditcardid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdatePersonCreditCard]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@creditcardid", creditcardid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePersoncreditcard(SqlConnection sqlConnection, Types.Sales.PersoncreditcardDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataCreditcardid = data.Creditcardid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePersoncreditcard( sqlConnection, 
                        dataBusinessentityid,
                        dataCreditcardid,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePersoncreditcard(SqlConnection sqlConnection, int businessentityid,
        int creditcardid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeletePersonCreditCard]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@creditcardid", creditcardid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePersoncreditcard(SqlConnection sqlConnection, Types.Sales.PersoncreditcardDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataCreditcardid = data.Creditcardid;
        var result = DeletePersoncreditcard( sqlConnection, 
                        dataBusinessentityid,
                        dataCreditcardid );

        return result;
    }

    public static bool InsertSalesorderdetail(SqlConnection sqlConnection, int salesorderid,
        ref int salesorderdetailid,
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

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        var salesorderdetailidParameter = command.Parameters.AddInt32("@salesorderdetailid");
        command.Parameters.AddNVarChar("@carriertrackingnumber", carriertrackingnumber, 25);
        command.Parameters.AddInt16("@orderqty", orderqty);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@specialofferid", specialofferid);
        command.Parameters.AddDecimal("@unitprice", unitprice);
        command.Parameters.AddDecimal("@unitpricediscount", unitpricediscount);
        command.Parameters.AddDecimal("@linetotal", linetotal);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            salesorderdetailid = (int)salesorderdetailidParameter.Value;
        }
        return result;
    }

    public static bool InsertSalesorderdetail(SqlConnection sqlConnection, Types.Sales.SalesorderdetailDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalesorderdetailid = data.Salesorderdetailid;
        var dataCarriertrackingnumber = data.Carriertrackingnumber;
        var dataOrderqty = data.Orderqty;
        var dataProductid = data.Productid;
        var dataSpecialofferid = data.Specialofferid;
        var dataUnitprice = data.Unitprice;
        var dataUnitpricediscount = data.Unitpricediscount;
        var dataLinetotal = data.Linetotal;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesorderdetail( sqlConnection, 
                        dataSalesorderid,
                        ref dataSalesorderdetailid,
                        dataCarriertrackingnumber,
                        dataOrderqty,
                        dataProductid,
                        dataSpecialofferid,
                        dataUnitprice,
                        dataUnitpricediscount,
                        dataLinetotal,
                        dataRowguid,
                        dataModifieddate );
        data.Salesorderdetailid = dataSalesorderdetailid;

        return result;
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

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddInt32("@salesorderdetailid", salesorderdetailid);
        command.Parameters.AddNVarChar("@carriertrackingnumber", carriertrackingnumber, 25);
        command.Parameters.AddInt16("@orderqty", orderqty);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@specialofferid", specialofferid);
        command.Parameters.AddDecimal("@unitprice", unitprice);
        command.Parameters.AddDecimal("@unitpricediscount", unitpricediscount);
        command.Parameters.AddDecimal("@linetotal", linetotal);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesorderdetail(SqlConnection sqlConnection, Types.Sales.SalesorderdetailDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalesorderdetailid = data.Salesorderdetailid;
        var dataCarriertrackingnumber = data.Carriertrackingnumber;
        var dataOrderqty = data.Orderqty;
        var dataProductid = data.Productid;
        var dataSpecialofferid = data.Specialofferid;
        var dataUnitprice = data.Unitprice;
        var dataUnitpricediscount = data.Unitpricediscount;
        var dataLinetotal = data.Linetotal;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesorderdetail( sqlConnection, 
                        dataSalesorderid,
                        dataSalesorderdetailid,
                        dataCarriertrackingnumber,
                        dataOrderqty,
                        dataProductid,
                        dataSpecialofferid,
                        dataUnitprice,
                        dataUnitpricediscount,
                        dataLinetotal,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesorderdetail(SqlConnection sqlConnection, int salesorderid,
        int salesorderdetailid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesOrderDetail]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddInt32("@salesorderdetailid", salesorderdetailid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesorderdetail(SqlConnection sqlConnection, Types.Sales.SalesorderdetailDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalesorderdetailid = data.Salesorderdetailid;
        var result = DeleteSalesorderdetail( sqlConnection, 
                        dataSalesorderid,
                        dataSalesorderdetailid );

        return result;
    }

    public static bool InsertSalesorderheader(SqlConnection sqlConnection, ref int salesorderid,
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

        var salesorderidParameter = command.Parameters.AddInt32("@salesorderid");
        command.Parameters.AddByte("@revisionnumber", revisionnumber);
        command.Parameters.AddDateTime("@orderdate", orderdate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddDateTime("@shipdate", shipdate);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddBoolean("@onlineorderflag", onlineorderflag);
        command.Parameters.AddNVarChar("@salesordernumber", salesordernumber, 25);
        command.Parameters.AddNVarChar("@purchaseordernumber", purchaseordernumber, 25);
        command.Parameters.AddNVarChar("@accountnumber", accountnumber, 15);
        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddInt32("@salespersonid", salespersonid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddInt32("@billtoaddressid", billtoaddressid);
        command.Parameters.AddInt32("@shiptoaddressid", shiptoaddressid);
        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddInt32("@creditcardid", creditcardid);
        command.Parameters.AddVarChar("@creditcardapprovalcode", creditcardapprovalcode, 15);
        command.Parameters.AddInt32("@currencyrateid", currencyrateid);
        command.Parameters.AddDecimal("@subtotal", subtotal);
        command.Parameters.AddDecimal("@taxamt", taxamt);
        command.Parameters.AddDecimal("@freight", freight);
        command.Parameters.AddDecimal("@totaldue", totaldue);
        command.Parameters.AddNVarChar("@comment", comment, 128);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            salesorderid = (int)salesorderidParameter.Value;
        }
        return result;
    }

    public static bool InsertSalesorderheader(SqlConnection sqlConnection, Types.Sales.SalesorderheaderDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataRevisionnumber = data.Revisionnumber;
        var dataOrderdate = data.Orderdate;
        var dataDuedate = data.Duedate;
        var dataShipdate = data.Shipdate;
        var dataStatus = data.Status;
        var dataOnlineorderflag = data.Onlineorderflag;
        var dataSalesordernumber = data.Salesordernumber;
        var dataPurchaseordernumber = data.Purchaseordernumber;
        var dataAccountnumber = data.Accountnumber;
        var dataCustomerid = data.Customerid;
        var dataSalespersonid = data.Salespersonid;
        var dataTerritoryid = data.Territoryid;
        var dataBilltoaddressid = data.Billtoaddressid;
        var dataShiptoaddressid = data.Shiptoaddressid;
        var dataShipmethodid = data.Shipmethodid;
        var dataCreditcardid = data.Creditcardid;
        var dataCreditcardapprovalcode = data.Creditcardapprovalcode;
        var dataCurrencyrateid = data.Currencyrateid;
        var dataSubtotal = data.Subtotal;
        var dataTaxamt = data.Taxamt;
        var dataFreight = data.Freight;
        var dataTotaldue = data.Totaldue;
        var dataComment = data.Comment;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesorderheader( sqlConnection, 
                        ref dataSalesorderid,
                        dataRevisionnumber,
                        dataOrderdate,
                        dataDuedate,
                        dataShipdate,
                        dataStatus,
                        dataOnlineorderflag,
                        dataSalesordernumber,
                        dataPurchaseordernumber,
                        dataAccountnumber,
                        dataCustomerid,
                        dataSalespersonid,
                        dataTerritoryid,
                        dataBilltoaddressid,
                        dataShiptoaddressid,
                        dataShipmethodid,
                        dataCreditcardid,
                        dataCreditcardapprovalcode,
                        dataCurrencyrateid,
                        dataSubtotal,
                        dataTaxamt,
                        dataFreight,
                        dataTotaldue,
                        dataComment,
                        dataRowguid,
                        dataModifieddate );
        data.Salesorderid = dataSalesorderid;

        return result;
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

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddByte("@revisionnumber", revisionnumber);
        command.Parameters.AddDateTime("@orderdate", orderdate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddDateTime("@shipdate", shipdate);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddBoolean("@onlineorderflag", onlineorderflag);
        command.Parameters.AddNVarChar("@salesordernumber", salesordernumber, 25);
        command.Parameters.AddNVarChar("@purchaseordernumber", purchaseordernumber, 25);
        command.Parameters.AddNVarChar("@accountnumber", accountnumber, 15);
        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddInt32("@salespersonid", salespersonid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddInt32("@billtoaddressid", billtoaddressid);
        command.Parameters.AddInt32("@shiptoaddressid", shiptoaddressid);
        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddInt32("@creditcardid", creditcardid);
        command.Parameters.AddVarChar("@creditcardapprovalcode", creditcardapprovalcode, 15);
        command.Parameters.AddInt32("@currencyrateid", currencyrateid);
        command.Parameters.AddDecimal("@subtotal", subtotal);
        command.Parameters.AddDecimal("@taxamt", taxamt);
        command.Parameters.AddDecimal("@freight", freight);
        command.Parameters.AddDecimal("@totaldue", totaldue);
        command.Parameters.AddNVarChar("@comment", comment, 128);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesorderheader(SqlConnection sqlConnection, Types.Sales.SalesorderheaderDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataRevisionnumber = data.Revisionnumber;
        var dataOrderdate = data.Orderdate;
        var dataDuedate = data.Duedate;
        var dataShipdate = data.Shipdate;
        var dataStatus = data.Status;
        var dataOnlineorderflag = data.Onlineorderflag;
        var dataSalesordernumber = data.Salesordernumber;
        var dataPurchaseordernumber = data.Purchaseordernumber;
        var dataAccountnumber = data.Accountnumber;
        var dataCustomerid = data.Customerid;
        var dataSalespersonid = data.Salespersonid;
        var dataTerritoryid = data.Territoryid;
        var dataBilltoaddressid = data.Billtoaddressid;
        var dataShiptoaddressid = data.Shiptoaddressid;
        var dataShipmethodid = data.Shipmethodid;
        var dataCreditcardid = data.Creditcardid;
        var dataCreditcardapprovalcode = data.Creditcardapprovalcode;
        var dataCurrencyrateid = data.Currencyrateid;
        var dataSubtotal = data.Subtotal;
        var dataTaxamt = data.Taxamt;
        var dataFreight = data.Freight;
        var dataTotaldue = data.Totaldue;
        var dataComment = data.Comment;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesorderheader( sqlConnection, 
                        dataSalesorderid,
                        dataRevisionnumber,
                        dataOrderdate,
                        dataDuedate,
                        dataShipdate,
                        dataStatus,
                        dataOnlineorderflag,
                        dataSalesordernumber,
                        dataPurchaseordernumber,
                        dataAccountnumber,
                        dataCustomerid,
                        dataSalespersonid,
                        dataTerritoryid,
                        dataBilltoaddressid,
                        dataShiptoaddressid,
                        dataShipmethodid,
                        dataCreditcardid,
                        dataCreditcardapprovalcode,
                        dataCurrencyrateid,
                        dataSubtotal,
                        dataTaxamt,
                        dataFreight,
                        dataTotaldue,
                        dataComment,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesorderheader(SqlConnection sqlConnection, int salesorderid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesOrderHeader]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesorderheader(SqlConnection sqlConnection, Types.Sales.SalesorderheaderDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var result = DeleteSalesorderheader( sqlConnection, 
                        dataSalesorderid );

        return result;
    }

    public static bool Insert1Salesorderheader(SqlConnection sqlConnection, ref int salesorderid,
        byte revisionnumber,
        DateTime orderdate,
        DateTime duedate,
        DateTime? shipdate,
        byte status,
        bool onlineorderflag,
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
        string? comment,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Insert1SalesOrderHeader]";

        var salesorderidParameter = command.Parameters.AddInt32("@salesorderid");
        command.Parameters.AddByte("@revisionnumber", revisionnumber);
        command.Parameters.AddDateTime("@orderdate", orderdate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddDateTime("@shipdate", shipdate);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddBoolean("@onlineorderflag", onlineorderflag);
        command.Parameters.AddNVarChar("@purchaseordernumber", purchaseordernumber, 25);
        command.Parameters.AddNVarChar("@accountnumber", accountnumber, 15);
        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddInt32("@billtoaddressid", billtoaddressid);
        command.Parameters.AddInt32("@shiptoaddressid", shiptoaddressid);
        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddVarChar("@creditcardapprovalcode", creditcardapprovalcode, 15);
        command.Parameters.AddDecimal("@subtotal", subtotal);
        command.Parameters.AddDecimal("@taxamt", taxamt);
        command.Parameters.AddDecimal("@freight", freight);
        command.Parameters.AddNVarChar("@comment", comment, 128);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            salesorderid = (int)salesorderidParameter.Value;
        }
        return result;
    }

    public static bool Insert1Salesorderheader(SqlConnection sqlConnection, Types.Sales.SalesorderheaderDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataRevisionnumber = data.Revisionnumber;
        var dataOrderdate = data.Orderdate;
        var dataDuedate = data.Duedate;
        var dataShipdate = data.Shipdate;
        var dataStatus = data.Status;
        var dataOnlineorderflag = data.Onlineorderflag;
        var dataPurchaseordernumber = data.Purchaseordernumber;
        var dataAccountnumber = data.Accountnumber;
        var dataCustomerid = data.Customerid;
        var dataBilltoaddressid = data.Billtoaddressid;
        var dataShiptoaddressid = data.Shiptoaddressid;
        var dataShipmethodid = data.Shipmethodid;
        var dataCreditcardapprovalcode = data.Creditcardapprovalcode;
        var dataSubtotal = data.Subtotal;
        var dataTaxamt = data.Taxamt;
        var dataFreight = data.Freight;
        var dataComment = data.Comment;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Salesorderheader( sqlConnection, 
                        ref dataSalesorderid,
                        dataRevisionnumber,
                        dataOrderdate,
                        dataDuedate,
                        dataShipdate,
                        dataStatus,
                        dataOnlineorderflag,
                        dataPurchaseordernumber,
                        dataAccountnumber,
                        dataCustomerid,
                        dataBilltoaddressid,
                        dataShiptoaddressid,
                        dataShipmethodid,
                        dataCreditcardapprovalcode,
                        dataSubtotal,
                        dataTaxamt,
                        dataFreight,
                        dataComment,
                        dataRowguid,
                        dataModifieddate );
        data.Salesorderid = dataSalesorderid;

        return result;
    }

    public static bool Update1Salesorderheader(SqlConnection sqlConnection, int salesorderid,
        byte revisionnumber,
        DateTime orderdate,
        DateTime duedate,
        DateTime? shipdate,
        byte status,
        bool onlineorderflag,
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
        string? comment,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update1SalesOrderHeader]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddByte("@revisionnumber", revisionnumber);
        command.Parameters.AddDateTime("@orderdate", orderdate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddDateTime("@shipdate", shipdate);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddBoolean("@onlineorderflag", onlineorderflag);
        command.Parameters.AddNVarChar("@purchaseordernumber", purchaseordernumber, 25);
        command.Parameters.AddNVarChar("@accountnumber", accountnumber, 15);
        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddInt32("@billtoaddressid", billtoaddressid);
        command.Parameters.AddInt32("@shiptoaddressid", shiptoaddressid);
        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddVarChar("@creditcardapprovalcode", creditcardapprovalcode, 15);
        command.Parameters.AddDecimal("@subtotal", subtotal);
        command.Parameters.AddDecimal("@taxamt", taxamt);
        command.Parameters.AddDecimal("@freight", freight);
        command.Parameters.AddNVarChar("@comment", comment, 128);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
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

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddInt32("@salespersonid", salespersonid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddInt32("@creditcardid", creditcardid);
        command.Parameters.AddInt32("@currencyrateid", currencyrateid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Salesorderheader(SqlConnection sqlConnection, Types.Sales.SalesorderheaderDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataRevisionnumber = data.Revisionnumber;
        var dataOrderdate = data.Orderdate;
        var dataDuedate = data.Duedate;
        var dataShipdate = data.Shipdate;
        var dataStatus = data.Status;
        var dataOnlineorderflag = data.Onlineorderflag;
        var dataPurchaseordernumber = data.Purchaseordernumber;
        var dataAccountnumber = data.Accountnumber;
        var dataCustomerid = data.Customerid;
        var dataBilltoaddressid = data.Billtoaddressid;
        var dataShiptoaddressid = data.Shiptoaddressid;
        var dataShipmethodid = data.Shipmethodid;
        var dataCreditcardapprovalcode = data.Creditcardapprovalcode;
        var dataSubtotal = data.Subtotal;
        var dataTaxamt = data.Taxamt;
        var dataFreight = data.Freight;
        var dataComment = data.Comment;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Salesorderheader( sqlConnection, 
                        dataSalesorderid,
                        dataRevisionnumber,
                        dataOrderdate,
                        dataDuedate,
                        dataShipdate,
                        dataStatus,
                        dataOnlineorderflag,
                        dataPurchaseordernumber,
                        dataAccountnumber,
                        dataCustomerid,
                        dataBilltoaddressid,
                        dataShiptoaddressid,
                        dataShipmethodid,
                        dataCreditcardapprovalcode,
                        dataSubtotal,
                        dataTaxamt,
                        dataFreight,
                        dataComment,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Salesorderheader(SqlConnection sqlConnection, Types.Sales.SalesorderheaderDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalespersonid = data.Salespersonid;
        var dataTerritoryid = data.Territoryid;
        var dataCreditcardid = data.Creditcardid;
        var dataCurrencyrateid = data.Currencyrateid;
        var result = Update2Salesorderheader( sqlConnection, 
                        dataSalesorderid,
                        dataSalespersonid,
                        dataTerritoryid,
                        dataCreditcardid,
                        dataCurrencyrateid );

        return result;
    }

    public static bool InsertSalesorderheadersalesreason(SqlConnection sqlConnection, int salesorderid,
        int salesreasonid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesOrderHeaderSalesReason]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddInt32("@salesreasonid", salesreasonid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertSalesorderheadersalesreason(SqlConnection sqlConnection, Types.Sales.SalesorderheadersalesreasonDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalesreasonid = data.Salesreasonid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesorderheadersalesreason( sqlConnection, 
                        dataSalesorderid,
                        dataSalesreasonid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateSalesorderheadersalesreason(SqlConnection sqlConnection, int salesorderid,
        int salesreasonid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesOrderHeaderSalesReason]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddInt32("@salesreasonid", salesreasonid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesorderheadersalesreason(SqlConnection sqlConnection, Types.Sales.SalesorderheadersalesreasonDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalesreasonid = data.Salesreasonid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesorderheadersalesreason( sqlConnection, 
                        dataSalesorderid,
                        dataSalesreasonid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesorderheadersalesreason(SqlConnection sqlConnection, int salesorderid,
        int salesreasonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesOrderHeaderSalesReason]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddInt32("@salesreasonid", salesreasonid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesorderheadersalesreason(SqlConnection sqlConnection, Types.Sales.SalesorderheadersalesreasonDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalesreasonid = data.Salesreasonid;
        var result = DeleteSalesorderheadersalesreason( sqlConnection, 
                        dataSalesorderid,
                        dataSalesreasonid );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddDecimal("@salesquota", salesquota);
        command.Parameters.AddDecimal("@bonus", bonus);
        command.Parameters.AddDecimal("@commissionpct", commissionpct);
        command.Parameters.AddDecimal("@salesytd", salesytd);
        command.Parameters.AddDecimal("@saleslastyear", saleslastyear);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertSalesperson(SqlConnection sqlConnection, Types.Sales.SalespersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataTerritoryid = data.Territoryid;
        var dataSalesquota = data.Salesquota;
        var dataBonus = data.Bonus;
        var dataCommissionpct = data.Commissionpct;
        var dataSalesytd = data.Salesytd;
        var dataSaleslastyear = data.Saleslastyear;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesperson( sqlConnection, 
                        dataBusinessentityid,
                        dataTerritoryid,
                        dataSalesquota,
                        dataBonus,
                        dataCommissionpct,
                        dataSalesytd,
                        dataSaleslastyear,
                        dataRowguid,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddDecimal("@salesquota", salesquota);
        command.Parameters.AddDecimal("@bonus", bonus);
        command.Parameters.AddDecimal("@commissionpct", commissionpct);
        command.Parameters.AddDecimal("@salesytd", salesytd);
        command.Parameters.AddDecimal("@saleslastyear", saleslastyear);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesperson(SqlConnection sqlConnection, Types.Sales.SalespersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataTerritoryid = data.Territoryid;
        var dataSalesquota = data.Salesquota;
        var dataBonus = data.Bonus;
        var dataCommissionpct = data.Commissionpct;
        var dataSalesytd = data.Salesytd;
        var dataSaleslastyear = data.Saleslastyear;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesperson( sqlConnection, 
                        dataBusinessentityid,
                        dataTerritoryid,
                        dataSalesquota,
                        dataBonus,
                        dataCommissionpct,
                        dataSalesytd,
                        dataSaleslastyear,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesperson(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesPerson]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesperson(SqlConnection sqlConnection, Types.Sales.SalespersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var result = DeleteSalesperson( sqlConnection, 
                        dataBusinessentityid );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDecimal("@salesquota", salesquota);
        command.Parameters.AddDecimal("@bonus", bonus);
        command.Parameters.AddDecimal("@commissionpct", commissionpct);
        command.Parameters.AddDecimal("@salesytd", salesytd);
        command.Parameters.AddDecimal("@saleslastyear", saleslastyear);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Insert1Salesperson(SqlConnection sqlConnection, Types.Sales.SalespersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataSalesquota = data.Salesquota;
        var dataBonus = data.Bonus;
        var dataCommissionpct = data.Commissionpct;
        var dataSalesytd = data.Salesytd;
        var dataSaleslastyear = data.Saleslastyear;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Salesperson( sqlConnection, 
                        dataBusinessentityid,
                        dataSalesquota,
                        dataBonus,
                        dataCommissionpct,
                        dataSalesytd,
                        dataSaleslastyear,
                        dataRowguid,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDecimal("@salesquota", salesquota);
        command.Parameters.AddDecimal("@bonus", bonus);
        command.Parameters.AddDecimal("@commissionpct", commissionpct);
        command.Parameters.AddDecimal("@salesytd", salesytd);
        command.Parameters.AddDecimal("@saleslastyear", saleslastyear);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update2Salesperson(SqlConnection sqlConnection, int businessentityid,
        int? territoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update2SalesPerson]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@territoryid", territoryid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Salesperson(SqlConnection sqlConnection, Types.Sales.SalespersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataSalesquota = data.Salesquota;
        var dataBonus = data.Bonus;
        var dataCommissionpct = data.Commissionpct;
        var dataSalesytd = data.Salesytd;
        var dataSaleslastyear = data.Saleslastyear;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Salesperson( sqlConnection, 
                        dataBusinessentityid,
                        dataSalesquota,
                        dataBonus,
                        dataCommissionpct,
                        dataSalesytd,
                        dataSaleslastyear,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Salesperson(SqlConnection sqlConnection, Types.Sales.SalespersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataTerritoryid = data.Territoryid;
        var result = Update2Salesperson( sqlConnection, 
                        dataBusinessentityid,
                        dataTerritoryid );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDateTime("@quotadate", quotadate);
        command.Parameters.AddDecimal("@salesquota", salesquota);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertSalespersonquotahistory(SqlConnection sqlConnection, Types.Sales.SalespersonquotahistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataQuotadate = data.Quotadate;
        var dataSalesquota = data.Salesquota;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalespersonquotahistory( sqlConnection, 
                        dataBusinessentityid,
                        dataQuotadate,
                        dataSalesquota,
                        dataRowguid,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDateTime("@quotadate", quotadate);
        command.Parameters.AddDecimal("@salesquota", salesquota);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalespersonquotahistory(SqlConnection sqlConnection, Types.Sales.SalespersonquotahistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataQuotadate = data.Quotadate;
        var dataSalesquota = data.Salesquota;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalespersonquotahistory( sqlConnection, 
                        dataBusinessentityid,
                        dataQuotadate,
                        dataSalesquota,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalespersonquotahistory(SqlConnection sqlConnection, int businessentityid,
        DateTime quotadate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesPersonQuotaHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDateTime("@quotadate", quotadate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalespersonquotahistory(SqlConnection sqlConnection, Types.Sales.SalespersonquotahistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataQuotadate = data.Quotadate;
        var result = DeleteSalespersonquotahistory( sqlConnection, 
                        dataBusinessentityid,
                        dataQuotadate );

        return result;
    }

    public static bool InsertSalesreason(SqlConnection sqlConnection, ref int salesreasonid,
        string name,
        string reasontype,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesReason]";

        var salesreasonidParameter = command.Parameters.AddInt32("@salesreasonid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@reasontype", reasontype, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            salesreasonid = (int)salesreasonidParameter.Value;
        }
        return result;
    }

    public static bool InsertSalesreason(SqlConnection sqlConnection, Types.Sales.SalesreasonDataType data )
    {
        var dataSalesreasonid = data.Salesreasonid;
        var dataName = data.Name;
        var dataReasontype = data.Reasontype;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesreason( sqlConnection, 
                        ref dataSalesreasonid,
                        dataName,
                        dataReasontype,
                        dataModifieddate );
        data.Salesreasonid = dataSalesreasonid;

        return result;
    }

    public static bool UpdateSalesreason(SqlConnection sqlConnection, int salesreasonid,
        string name,
        string reasontype,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesReason]";

        command.Parameters.AddInt32("@salesreasonid", salesreasonid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@reasontype", reasontype, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesreason(SqlConnection sqlConnection, Types.Sales.SalesreasonDataType data )
    {
        var dataSalesreasonid = data.Salesreasonid;
        var dataName = data.Name;
        var dataReasontype = data.Reasontype;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesreason( sqlConnection, 
                        dataSalesreasonid,
                        dataName,
                        dataReasontype,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesreason(SqlConnection sqlConnection, int salesreasonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesReason]";

        command.Parameters.AddInt32("@salesreasonid", salesreasonid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesreason(SqlConnection sqlConnection, Types.Sales.SalesreasonDataType data )
    {
        var dataSalesreasonid = data.Salesreasonid;
        var result = DeleteSalesreason( sqlConnection, 
                        dataSalesreasonid );

        return result;
    }

    public static bool InsertSalestaxrate(SqlConnection sqlConnection, ref int salestaxrateid,
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

        var salestaxrateidParameter = command.Parameters.AddInt32("@salestaxrateid");
        command.Parameters.AddInt32("@stateprovinceid", stateprovinceid);
        command.Parameters.AddByte("@taxtype", taxtype);
        command.Parameters.AddDecimal("@taxrate", taxrate);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            salestaxrateid = (int)salestaxrateidParameter.Value;
        }
        return result;
    }

    public static bool InsertSalestaxrate(SqlConnection sqlConnection, Types.Sales.SalestaxrateDataType data )
    {
        var dataSalestaxrateid = data.Salestaxrateid;
        var dataStateprovinceid = data.Stateprovinceid;
        var dataTaxtype = data.Taxtype;
        var dataTaxrate = data.Taxrate;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalestaxrate( sqlConnection, 
                        ref dataSalestaxrateid,
                        dataStateprovinceid,
                        dataTaxtype,
                        dataTaxrate,
                        dataName,
                        dataRowguid,
                        dataModifieddate );
        data.Salestaxrateid = dataSalestaxrateid;

        return result;
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

        command.Parameters.AddInt32("@salestaxrateid", salestaxrateid);
        command.Parameters.AddInt32("@stateprovinceid", stateprovinceid);
        command.Parameters.AddByte("@taxtype", taxtype);
        command.Parameters.AddDecimal("@taxrate", taxrate);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalestaxrate(SqlConnection sqlConnection, Types.Sales.SalestaxrateDataType data )
    {
        var dataSalestaxrateid = data.Salestaxrateid;
        var dataStateprovinceid = data.Stateprovinceid;
        var dataTaxtype = data.Taxtype;
        var dataTaxrate = data.Taxrate;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalestaxrate( sqlConnection, 
                        dataSalestaxrateid,
                        dataStateprovinceid,
                        dataTaxtype,
                        dataTaxrate,
                        dataName,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalestaxrate(SqlConnection sqlConnection, int salestaxrateid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesTaxRate]";

        command.Parameters.AddInt32("@salestaxrateid", salestaxrateid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalestaxrate(SqlConnection sqlConnection, Types.Sales.SalestaxrateDataType data )
    {
        var dataSalestaxrateid = data.Salestaxrateid;
        var result = DeleteSalestaxrate( sqlConnection, 
                        dataSalestaxrateid );

        return result;
    }

    public static bool InsertSalesterritory(SqlConnection sqlConnection, ref int territoryid,
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

        var territoryidParameter = command.Parameters.AddInt32("@territoryid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNVarChar("@group", group, 50);
        command.Parameters.AddDecimal("@salesytd", salesytd);
        command.Parameters.AddDecimal("@saleslastyear", saleslastyear);
        command.Parameters.AddDecimal("@costytd", costytd);
        command.Parameters.AddDecimal("@costlastyear", costlastyear);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            territoryid = (int)territoryidParameter.Value;
        }
        return result;
    }

    public static bool InsertSalesterritory(SqlConnection sqlConnection, Types.Sales.SalesterritoryDataType data )
    {
        var dataTerritoryid = data.Territoryid;
        var dataName = data.Name;
        var dataCountryregioncode = data.Countryregioncode;
        var dataGroup = data.Group;
        var dataSalesytd = data.Salesytd;
        var dataSaleslastyear = data.Saleslastyear;
        var dataCostytd = data.Costytd;
        var dataCostlastyear = data.Costlastyear;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesterritory( sqlConnection, 
                        ref dataTerritoryid,
                        dataName,
                        dataCountryregioncode,
                        dataGroup,
                        dataSalesytd,
                        dataSaleslastyear,
                        dataCostytd,
                        dataCostlastyear,
                        dataRowguid,
                        dataModifieddate );
        data.Territoryid = dataTerritoryid;

        return result;
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

        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNVarChar("@group", group, 50);
        command.Parameters.AddDecimal("@salesytd", salesytd);
        command.Parameters.AddDecimal("@saleslastyear", saleslastyear);
        command.Parameters.AddDecimal("@costytd", costytd);
        command.Parameters.AddDecimal("@costlastyear", costlastyear);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesterritory(SqlConnection sqlConnection, Types.Sales.SalesterritoryDataType data )
    {
        var dataTerritoryid = data.Territoryid;
        var dataName = data.Name;
        var dataCountryregioncode = data.Countryregioncode;
        var dataGroup = data.Group;
        var dataSalesytd = data.Salesytd;
        var dataSaleslastyear = data.Saleslastyear;
        var dataCostytd = data.Costytd;
        var dataCostlastyear = data.Costlastyear;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesterritory( sqlConnection, 
                        dataTerritoryid,
                        dataName,
                        dataCountryregioncode,
                        dataGroup,
                        dataSalesytd,
                        dataSaleslastyear,
                        dataCostytd,
                        dataCostlastyear,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesterritory(SqlConnection sqlConnection, int territoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesTerritory]";

        command.Parameters.AddInt32("@territoryid", territoryid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesterritory(SqlConnection sqlConnection, Types.Sales.SalesterritoryDataType data )
    {
        var dataTerritoryid = data.Territoryid;
        var result = DeleteSalesterritory( sqlConnection, 
                        dataTerritoryid );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertSalesterritoryhistory(SqlConnection sqlConnection, Types.Sales.SalesterritoryhistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataTerritoryid = data.Territoryid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesterritoryhistory( sqlConnection, 
                        dataBusinessentityid,
                        dataTerritoryid,
                        dataStartdate,
                        dataEnddate,
                        dataRowguid,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesterritoryhistory(SqlConnection sqlConnection, Types.Sales.SalesterritoryhistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataTerritoryid = data.Territoryid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesterritoryhistory( sqlConnection, 
                        dataBusinessentityid,
                        dataTerritoryid,
                        dataStartdate,
                        dataEnddate,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesterritoryhistory(SqlConnection sqlConnection, int businessentityid,
        DateTime startdate,
        int territoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesTerritoryHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddInt32("@territoryid", territoryid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesterritoryhistory(SqlConnection sqlConnection, Types.Sales.SalesterritoryhistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataStartdate = data.Startdate;
        var dataTerritoryid = data.Territoryid;
        var result = DeleteSalesterritoryhistory( sqlConnection, 
                        dataBusinessentityid,
                        dataStartdate,
                        dataTerritoryid );

        return result;
    }

    public static bool InsertShoppingcartitem(SqlConnection sqlConnection, ref int shoppingcartitemid,
        string shoppingcartid,
        int quantity,
        int productid,
        DateTime datecreated,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertShoppingCartItem]";

        var shoppingcartitemidParameter = command.Parameters.AddInt32("@shoppingcartitemid");
        command.Parameters.AddNVarChar("@shoppingcartid", shoppingcartid, 50);
        command.Parameters.AddInt32("@quantity", quantity);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@datecreated", datecreated);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            shoppingcartitemid = (int)shoppingcartitemidParameter.Value;
        }
        return result;
    }

    public static bool InsertShoppingcartitem(SqlConnection sqlConnection, Types.Sales.ShoppingcartitemDataType data )
    {
        var dataShoppingcartitemid = data.Shoppingcartitemid;
        var dataShoppingcartid = data.Shoppingcartid;
        var dataQuantity = data.Quantity;
        var dataProductid = data.Productid;
        var dataDatecreated = data.Datecreated;
        var dataModifieddate = data.Modifieddate;
        var result = InsertShoppingcartitem( sqlConnection, 
                        ref dataShoppingcartitemid,
                        dataShoppingcartid,
                        dataQuantity,
                        dataProductid,
                        dataDatecreated,
                        dataModifieddate );
        data.Shoppingcartitemid = dataShoppingcartitemid;

        return result;
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

        command.Parameters.AddInt32("@shoppingcartitemid", shoppingcartitemid);
        command.Parameters.AddNVarChar("@shoppingcartid", shoppingcartid, 50);
        command.Parameters.AddInt32("@quantity", quantity);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@datecreated", datecreated);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateShoppingcartitem(SqlConnection sqlConnection, Types.Sales.ShoppingcartitemDataType data )
    {
        var dataShoppingcartitemid = data.Shoppingcartitemid;
        var dataShoppingcartid = data.Shoppingcartid;
        var dataQuantity = data.Quantity;
        var dataProductid = data.Productid;
        var dataDatecreated = data.Datecreated;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateShoppingcartitem( sqlConnection, 
                        dataShoppingcartitemid,
                        dataShoppingcartid,
                        dataQuantity,
                        dataProductid,
                        dataDatecreated,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteShoppingcartitem(SqlConnection sqlConnection, int shoppingcartitemid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteShoppingCartItem]";

        command.Parameters.AddInt32("@shoppingcartitemid", shoppingcartitemid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteShoppingcartitem(SqlConnection sqlConnection, Types.Sales.ShoppingcartitemDataType data )
    {
        var dataShoppingcartitemid = data.Shoppingcartitemid;
        var result = DeleteShoppingcartitem( sqlConnection, 
                        dataShoppingcartitemid );

        return result;
    }

    public static bool InsertSpecialoffer(SqlConnection sqlConnection, ref int specialofferid,
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

        var specialofferidParameter = command.Parameters.AddInt32("@specialofferid");
        command.Parameters.AddNVarChar("@description", description, 255);
        command.Parameters.AddDecimal("@discountpct", discountpct);
        command.Parameters.AddNVarChar("@type", type, 50);
        command.Parameters.AddNVarChar("@category", category, 50);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddInt32("@minqty", minqty);
        command.Parameters.AddInt32("@maxqty", maxqty);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            specialofferid = (int)specialofferidParameter.Value;
        }
        return result;
    }

    public static bool InsertSpecialoffer(SqlConnection sqlConnection, Types.Sales.SpecialofferDataType data )
    {
        var dataSpecialofferid = data.Specialofferid;
        var dataDescription = data.Description;
        var dataDiscountpct = data.Discountpct;
        var dataType = data.Type;
        var dataCategory = data.Category;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataMinqty = data.Minqty;
        var dataMaxqty = data.Maxqty;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSpecialoffer( sqlConnection, 
                        ref dataSpecialofferid,
                        dataDescription,
                        dataDiscountpct,
                        dataType,
                        dataCategory,
                        dataStartdate,
                        dataEnddate,
                        dataMinqty,
                        dataMaxqty,
                        dataRowguid,
                        dataModifieddate );
        data.Specialofferid = dataSpecialofferid;

        return result;
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

        command.Parameters.AddInt32("@specialofferid", specialofferid);
        command.Parameters.AddNVarChar("@description", description, 255);
        command.Parameters.AddDecimal("@discountpct", discountpct);
        command.Parameters.AddNVarChar("@type", type, 50);
        command.Parameters.AddNVarChar("@category", category, 50);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddInt32("@minqty", minqty);
        command.Parameters.AddInt32("@maxqty", maxqty);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSpecialoffer(SqlConnection sqlConnection, Types.Sales.SpecialofferDataType data )
    {
        var dataSpecialofferid = data.Specialofferid;
        var dataDescription = data.Description;
        var dataDiscountpct = data.Discountpct;
        var dataType = data.Type;
        var dataCategory = data.Category;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataMinqty = data.Minqty;
        var dataMaxqty = data.Maxqty;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSpecialoffer( sqlConnection, 
                        dataSpecialofferid,
                        dataDescription,
                        dataDiscountpct,
                        dataType,
                        dataCategory,
                        dataStartdate,
                        dataEnddate,
                        dataMinqty,
                        dataMaxqty,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSpecialoffer(SqlConnection sqlConnection, int specialofferid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSpecialOffer]";

        command.Parameters.AddInt32("@specialofferid", specialofferid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSpecialoffer(SqlConnection sqlConnection, Types.Sales.SpecialofferDataType data )
    {
        var dataSpecialofferid = data.Specialofferid;
        var result = DeleteSpecialoffer( sqlConnection, 
                        dataSpecialofferid );

        return result;
    }

    public static bool InsertSpecialofferproduct(SqlConnection sqlConnection, int specialofferid,
        int productid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSpecialOfferProduct]";

        command.Parameters.AddInt32("@specialofferid", specialofferid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertSpecialofferproduct(SqlConnection sqlConnection, Types.Sales.SpecialofferproductDataType data )
    {
        var dataSpecialofferid = data.Specialofferid;
        var dataProductid = data.Productid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSpecialofferproduct( sqlConnection, 
                        dataSpecialofferid,
                        dataProductid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateSpecialofferproduct(SqlConnection sqlConnection, int specialofferid,
        int productid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSpecialOfferProduct]";

        command.Parameters.AddInt32("@specialofferid", specialofferid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSpecialofferproduct(SqlConnection sqlConnection, Types.Sales.SpecialofferproductDataType data )
    {
        var dataSpecialofferid = data.Specialofferid;
        var dataProductid = data.Productid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSpecialofferproduct( sqlConnection, 
                        dataSpecialofferid,
                        dataProductid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSpecialofferproduct(SqlConnection sqlConnection, int specialofferid,
        int productid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSpecialOfferProduct]";

        command.Parameters.AddInt32("@specialofferid", specialofferid);
        command.Parameters.AddInt32("@productid", productid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSpecialofferproduct(SqlConnection sqlConnection, Types.Sales.SpecialofferproductDataType data )
    {
        var dataSpecialofferid = data.Specialofferid;
        var dataProductid = data.Productid;
        var result = DeleteSpecialofferproduct( sqlConnection, 
                        dataSpecialofferid,
                        dataProductid );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddInt32("@salespersonid", salespersonid);
        command.Parameters.AddSqlXml("@demographics", demographics);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertStore(SqlConnection sqlConnection, Types.Sales.StoreDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataName = data.Name;
        var dataSalespersonid = data.Salespersonid;
        var dataDemographics = data.Demographics;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertStore( sqlConnection, 
                        dataBusinessentityid,
                        dataName,
                        dataSalespersonid,
                        dataDemographics,
                        dataRowguid,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddInt32("@salespersonid", salespersonid);
        command.Parameters.AddSqlXml("@demographics", demographics);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateStore(SqlConnection sqlConnection, Types.Sales.StoreDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataName = data.Name;
        var dataSalespersonid = data.Salespersonid;
        var dataDemographics = data.Demographics;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateStore( sqlConnection, 
                        dataBusinessentityid,
                        dataName,
                        dataSalespersonid,
                        dataDemographics,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteStore(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteStore]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteStore(SqlConnection sqlConnection, Types.Sales.StoreDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var result = DeleteStore( sqlConnection, 
                        dataBusinessentityid );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddSqlXml("@demographics", demographics);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Insert1Store(SqlConnection sqlConnection, Types.Sales.StoreDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataName = data.Name;
        var dataDemographics = data.Demographics;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Store( sqlConnection, 
                        dataBusinessentityid,
                        dataName,
                        dataDemographics,
                        dataRowguid,
                        dataModifieddate );

        return result;
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

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddSqlXml("@demographics", demographics);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update2Store(SqlConnection sqlConnection, int businessentityid,
        int? salespersonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update2Store]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@salespersonid", salespersonid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Store(SqlConnection sqlConnection, Types.Sales.StoreDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataName = data.Name;
        var dataDemographics = data.Demographics;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Store( sqlConnection, 
                        dataBusinessentityid,
                        dataName,
                        dataDemographics,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Store(SqlConnection sqlConnection, Types.Sales.StoreDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataSalespersonid = data.Salespersonid;
        var result = Update2Store( sqlConnection, 
                        dataBusinessentityid,
                        dataSalespersonid );

        return result;
    }

}
