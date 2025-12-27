/*
   Copyright 2024-2025 Espen Harlinn

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

public class DmFilestreamFileIoRequestsDataType
{
    readonly byte[] _requestContextAddress = Array.Empty<byte>();
    readonly short _currentSpid = 0;
    readonly string _requestType = string.Empty;
    readonly string _requestState = string.Empty;
    readonly int _requestId = 0;
    readonly int _irpId = 0;
    readonly int _handleId = 0;
    readonly byte[]? _clientThreadId;
    readonly byte[]? _clientProcessId;
    readonly byte[]? _handleContextAddress;
    readonly byte[]? _filestreamTransactionId;

    public DmFilestreamFileIoRequestsDataType( )
    {
    }

    public DmFilestreamFileIoRequestsDataType(byte[] requestContextAddress,
        short currentSpid,
        string requestType,
        string requestState,
        int requestId,
        int irpId,
        int handleId,
        byte[]? clientThreadId,
        byte[]? clientProcessId,
        byte[]? handleContextAddress,
        byte[]? filestreamTransactionId)
    {
        _requestContextAddress = requestContextAddress;
        _currentSpid = currentSpid;
        _requestType = requestType;
        _requestState = requestState;
        _requestId = requestId;
        _irpId = irpId;
        _handleId = handleId;
        _clientThreadId = clientThreadId;
        _clientProcessId = clientProcessId;
        _handleContextAddress = handleContextAddress;
        _filestreamTransactionId = filestreamTransactionId;
    }

    public byte[] RequestContextAddress => _requestContextAddress;
    public short CurrentSpid => _currentSpid;
    public string RequestType => _requestType;
    public string RequestState => _requestState;
    public int RequestId => _requestId;
    public int IrpId => _irpId;
    public int HandleId => _handleId;
    public byte[]? ClientThreadId => _clientThreadId;
    public byte[]? ClientProcessId => _clientProcessId;
    public byte[]? HandleContextAddress => _handleContextAddress;
    public byte[]? FilestreamTransactionId => _filestreamTransactionId;
}
