using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Dbo.Types;

public class ErrorlogDataType
{
    int _errorlogid = 0;
    DateTime _errortime;
    string _username = string.Empty;
    int _errornumber = 0;
    int? _errorseverity;
    int? _errorstate;
    string? _errorprocedure;
    int? _errorline;
    string _errormessage = string.Empty;

    public ErrorlogDataType( )
    {
    }

    public ErrorlogDataType(int errorlogid,
        DateTime errortime,
        string username,
        int errornumber,
        int? errorseverity,
        int? errorstate,
        string? errorprocedure,
        int? errorline,
        string errormessage)
    {
        _errorlogid = errorlogid;
        _errortime = errortime;
        _username = username;
        _errornumber = errornumber;
        _errorseverity = errorseverity;
        _errorstate = errorstate;
        _errorprocedure = errorprocedure;
        _errorline = errorline;
        _errormessage = errormessage;
    }

    public int Errorlogid
    {
        get => _errorlogid;
        set => _errorlogid = value;
    }
    public DateTime Errortime
    {
        get => _errortime;
        set => _errortime = value;
    }
    public string Username
    {
        get => _username;
        set => _username = value;
    }
    public int Errornumber
    {
        get => _errornumber;
        set => _errornumber = value;
    }
    public int? Errorseverity
    {
        get => _errorseverity;
        set => _errorseverity = value;
    }
    public int? Errorstate
    {
        get => _errorstate;
        set => _errorstate = value;
    }
    public string? Errorprocedure
    {
        get => _errorprocedure;
        set => _errorprocedure = value;
    }
    public int? Errorline
    {
        get => _errorline;
        set => _errorline = value;
    }
    public string Errormessage
    {
        get => _errormessage;
        set => _errormessage = value;
    }
}
