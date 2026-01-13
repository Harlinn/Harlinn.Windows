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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class DmTranLocksDataType
{
    readonly string _resourceType = string.Empty;
    readonly string _resourceSubtype = string.Empty;
    readonly int _resourceDatabaseId = 0;
    readonly string _resourceDescription = string.Empty;
    readonly long? _resourceAssociatedEntityId;
    readonly int? _resourceLockPartition;
    readonly string _requestMode = string.Empty;
    readonly string _requestType = string.Empty;
    readonly string _requestStatus = string.Empty;
    readonly short _requestReferenceCount = 0;
    readonly int _requestLifetime = 0;
    readonly int _requestSessionId = 0;
    readonly int _requestExecContextId = 0;
    readonly int _requestRequestId = 0;
    readonly string _requestOwnerType = string.Empty;
    readonly long? _requestOwnerId;
    readonly Guid? _requestOwnerGuid;
    readonly string _requestOwnerLockspaceId = string.Empty;
    readonly byte[] _lockOwnerAddress = Array.Empty<byte>();

    public DmTranLocksDataType( )
    {
    }

    public DmTranLocksDataType(string resourceType,
        string resourceSubtype,
        int resourceDatabaseId,
        string resourceDescription,
        long? resourceAssociatedEntityId,
        int? resourceLockPartition,
        string requestMode,
        string requestType,
        string requestStatus,
        short requestReferenceCount,
        int requestLifetime,
        int requestSessionId,
        int requestExecContextId,
        int requestRequestId,
        string requestOwnerType,
        long? requestOwnerId,
        Guid? requestOwnerGuid,
        string requestOwnerLockspaceId,
        byte[] lockOwnerAddress)
    {
        _resourceType = resourceType;
        _resourceSubtype = resourceSubtype;
        _resourceDatabaseId = resourceDatabaseId;
        _resourceDescription = resourceDescription;
        _resourceAssociatedEntityId = resourceAssociatedEntityId;
        _resourceLockPartition = resourceLockPartition;
        _requestMode = requestMode;
        _requestType = requestType;
        _requestStatus = requestStatus;
        _requestReferenceCount = requestReferenceCount;
        _requestLifetime = requestLifetime;
        _requestSessionId = requestSessionId;
        _requestExecContextId = requestExecContextId;
        _requestRequestId = requestRequestId;
        _requestOwnerType = requestOwnerType;
        _requestOwnerId = requestOwnerId;
        _requestOwnerGuid = requestOwnerGuid;
        _requestOwnerLockspaceId = requestOwnerLockspaceId;
        _lockOwnerAddress = lockOwnerAddress;
    }

    public string ResourceType => _resourceType;
    public string ResourceSubtype => _resourceSubtype;
    public int ResourceDatabaseId => _resourceDatabaseId;
    public string ResourceDescription => _resourceDescription;
    public long? ResourceAssociatedEntityId => _resourceAssociatedEntityId;
    public int? ResourceLockPartition => _resourceLockPartition;
    public string RequestMode => _requestMode;
    public string RequestType => _requestType;
    public string RequestStatus => _requestStatus;
    public short RequestReferenceCount => _requestReferenceCount;
    public int RequestLifetime => _requestLifetime;
    public int RequestSessionId => _requestSessionId;
    public int RequestExecContextId => _requestExecContextId;
    public int RequestRequestId => _requestRequestId;
    public string RequestOwnerType => _requestOwnerType;
    public long? RequestOwnerId => _requestOwnerId;
    public Guid? RequestOwnerGuid => _requestOwnerGuid;
    public string RequestOwnerLockspaceId => _requestOwnerLockspaceId;
    public byte[] LockOwnerAddress => _lockOwnerAddress;
}
