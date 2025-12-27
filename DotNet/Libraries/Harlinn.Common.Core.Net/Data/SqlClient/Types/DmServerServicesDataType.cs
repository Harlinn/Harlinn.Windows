using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class DmServerServicesDataType
{
    readonly string _servicename = string.Empty;
    readonly int? _startupType;
    readonly string _startupTypeDesc = string.Empty;
    readonly int? _status;
    readonly string _statusDesc = string.Empty;
    readonly int? _processId;
    readonly DateTime? _lastStartupTime;
    readonly string _serviceAccount = string.Empty;
    readonly string _filename = string.Empty;
    readonly string _isClustered = string.Empty;
    readonly string? _clusterNodename;
    readonly string _instantFileInitializationEnabled = string.Empty;

    public DmServerServicesDataType( )
    {
    }

    public DmServerServicesDataType(string servicename,
        int? startupType,
        string startupTypeDesc,
        int? status,
        string statusDesc,
        int? processId,
        DateTime? lastStartupTime,
        string serviceAccount,
        string filename,
        string isClustered,
        string? clusterNodename,
        string instantFileInitializationEnabled)
    {
        _servicename = servicename;
        _startupType = startupType;
        _startupTypeDesc = startupTypeDesc;
        _status = status;
        _statusDesc = statusDesc;
        _processId = processId;
        _lastStartupTime = lastStartupTime;
        _serviceAccount = serviceAccount;
        _filename = filename;
        _isClustered = isClustered;
        _clusterNodename = clusterNodename;
        _instantFileInitializationEnabled = instantFileInitializationEnabled;
    }

    public string Servicename => _servicename;
    public int? StartupType => _startupType;
    public string StartupTypeDesc => _startupTypeDesc;
    public int? Status => _status;
    public string StatusDesc => _statusDesc;
    public int? ProcessId => _processId;
    public DateTime? LastStartupTime => _lastStartupTime;
    public string ServiceAccount => _serviceAccount;
    public string Filename => _filename;
    public string IsClustered => _isClustered;
    public string? ClusterNodename => _clusterNodename;
    public string InstantFileInitializationEnabled => _instantFileInitializationEnabled;
}
