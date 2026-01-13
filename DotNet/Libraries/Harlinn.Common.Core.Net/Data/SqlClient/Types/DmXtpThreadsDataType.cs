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

public class DmXtpThreadsDataType
{
    readonly byte[] _threadAddress = Array.Empty<byte>();
    readonly int _threadType = 0;
    readonly string _threadTypeDesc = string.Empty;
    readonly int _retiredRowCount = 0;
    readonly int _retiredTransactionCount = 0;

    public DmXtpThreadsDataType( )
    {
    }

    public DmXtpThreadsDataType(byte[] threadAddress,
        int threadType,
        string threadTypeDesc,
        int retiredRowCount,
        int retiredTransactionCount)
    {
        _threadAddress = threadAddress;
        _threadType = threadType;
        _threadTypeDesc = threadTypeDesc;
        _retiredRowCount = retiredRowCount;
        _retiredTransactionCount = retiredTransactionCount;
    }

    public byte[] ThreadAddress => _threadAddress;
    public int ThreadType => _threadType;
    public string ThreadTypeDesc => _threadTypeDesc;
    public int RetiredRowCount => _retiredRowCount;
    public int RetiredTransactionCount => _retiredTransactionCount;
}
