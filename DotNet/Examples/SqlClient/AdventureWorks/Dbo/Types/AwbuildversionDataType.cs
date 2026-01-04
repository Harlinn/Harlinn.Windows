using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Dbo.Types;

public class AwbuildversionDataType
{
    byte _systeminformationid = 0;
    string _databaseVersion = string.Empty;
    DateTime _versiondate;
    DateTime _modifieddate;

    public AwbuildversionDataType( )
    {
    }

    public AwbuildversionDataType(byte systeminformationid,
        string databaseVersion,
        DateTime versiondate,
        DateTime modifieddate)
    {
        _systeminformationid = systeminformationid;
        _databaseVersion = databaseVersion;
        _versiondate = versiondate;
        _modifieddate = modifieddate;
    }

    public byte Systeminformationid
    {
        get => _systeminformationid;
        set => _systeminformationid = value;
    }
    public string DatabaseVersion
    {
        get => _databaseVersion;
        set => _databaseVersion = value;
    }
    public DateTime Versiondate
    {
        get => _versiondate;
        set => _versiondate = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
