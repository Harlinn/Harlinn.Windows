using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class DmXeSessionEventsDataType
{
    readonly byte[] _eventSessionAddress = Array.Empty<byte>();
    readonly string _eventName = string.Empty;
    readonly Guid _eventPackageGuid;
    readonly string? _eventPredicate;

    public DmXeSessionEventsDataType( )
    {
    }

    public DmXeSessionEventsDataType(byte[] eventSessionAddress,
        string eventName,
        Guid eventPackageGuid,
        string? eventPredicate)
    {
        _eventSessionAddress = eventSessionAddress;
        _eventName = eventName;
        _eventPackageGuid = eventPackageGuid;
        _eventPredicate = eventPredicate;
    }

    public byte[] EventSessionAddress => _eventSessionAddress;
    public string EventName => _eventName;
    public Guid EventPackageGuid => _eventPackageGuid;
    public string? EventPredicate => _eventPredicate;
}
