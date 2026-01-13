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

public class DmOsWorkerLocalStorageDataType
{
    readonly byte[] _workerAddress = Array.Empty<byte>();
    readonly byte[] _compExecCtxtAddress = Array.Empty<byte>();
    readonly byte[] _ecAddress = Array.Empty<byte>();
    readonly byte[] _brokerAddress = Array.Empty<byte>();
    readonly byte[] _taskProxyAddress = Array.Empty<byte>();
    readonly byte[] _msqlxactAddress = Array.Empty<byte>();
    readonly byte[] _sqlProfAddress = Array.Empty<byte>();
    readonly byte[] _stackCheckerAddress = Array.Empty<byte>();
    readonly byte[] _hostTaskAddress = Array.Empty<byte>();
    readonly byte[] _sniErrorAddress = Array.Empty<byte>();
    readonly byte[] _queryscanAddress = Array.Empty<byte>();
    readonly byte[] _diagAddress = Array.Empty<byte>();
    readonly byte[] _queryDriverAddress = Array.Empty<byte>();
    readonly byte[] _federatedxactAddress = Array.Empty<byte>();
    readonly byte[] _filestreamAddress = Array.Empty<byte>();
    readonly byte[] _qeCcAddress = Array.Empty<byte>();
    readonly byte[] _xtpAddress = Array.Empty<byte>();
    readonly byte[] _gqAddress = Array.Empty<byte>();
    readonly byte[] _extensibilityCtxtAddress = Array.Empty<byte>();

    public DmOsWorkerLocalStorageDataType( )
    {
    }

    public DmOsWorkerLocalStorageDataType(byte[] workerAddress,
        byte[] compExecCtxtAddress,
        byte[] ecAddress,
        byte[] brokerAddress,
        byte[] taskProxyAddress,
        byte[] msqlxactAddress,
        byte[] sqlProfAddress,
        byte[] stackCheckerAddress,
        byte[] hostTaskAddress,
        byte[] sniErrorAddress,
        byte[] queryscanAddress,
        byte[] diagAddress,
        byte[] queryDriverAddress,
        byte[] federatedxactAddress,
        byte[] filestreamAddress,
        byte[] qeCcAddress,
        byte[] xtpAddress,
        byte[] gqAddress,
        byte[] extensibilityCtxtAddress)
    {
        _workerAddress = workerAddress;
        _compExecCtxtAddress = compExecCtxtAddress;
        _ecAddress = ecAddress;
        _brokerAddress = brokerAddress;
        _taskProxyAddress = taskProxyAddress;
        _msqlxactAddress = msqlxactAddress;
        _sqlProfAddress = sqlProfAddress;
        _stackCheckerAddress = stackCheckerAddress;
        _hostTaskAddress = hostTaskAddress;
        _sniErrorAddress = sniErrorAddress;
        _queryscanAddress = queryscanAddress;
        _diagAddress = diagAddress;
        _queryDriverAddress = queryDriverAddress;
        _federatedxactAddress = federatedxactAddress;
        _filestreamAddress = filestreamAddress;
        _qeCcAddress = qeCcAddress;
        _xtpAddress = xtpAddress;
        _gqAddress = gqAddress;
        _extensibilityCtxtAddress = extensibilityCtxtAddress;
    }

    public byte[] WorkerAddress => _workerAddress;
    public byte[] CompExecCtxtAddress => _compExecCtxtAddress;
    public byte[] EcAddress => _ecAddress;
    public byte[] BrokerAddress => _brokerAddress;
    public byte[] TaskProxyAddress => _taskProxyAddress;
    public byte[] MsqlxactAddress => _msqlxactAddress;
    public byte[] SqlProfAddress => _sqlProfAddress;
    public byte[] StackCheckerAddress => _stackCheckerAddress;
    public byte[] HostTaskAddress => _hostTaskAddress;
    public byte[] SniErrorAddress => _sniErrorAddress;
    public byte[] QueryscanAddress => _queryscanAddress;
    public byte[] DiagAddress => _diagAddress;
    public byte[] QueryDriverAddress => _queryDriverAddress;
    public byte[] FederatedxactAddress => _federatedxactAddress;
    public byte[] FilestreamAddress => _filestreamAddress;
    public byte[] QeCcAddress => _qeCcAddress;
    public byte[] XtpAddress => _xtpAddress;
    public byte[] GqAddress => _gqAddress;
    public byte[] ExtensibilityCtxtAddress => _extensibilityCtxtAddress;
}
