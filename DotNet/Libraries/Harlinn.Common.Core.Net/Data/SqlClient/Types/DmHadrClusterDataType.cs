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

public class DmHadrClusterDataType
{
    readonly string _clusterName = string.Empty;
    readonly byte _quorumType = 0;
    readonly string _quorumTypeDesc = string.Empty;
    readonly byte _quorumState = 0;
    readonly string _quorumStateDesc = string.Empty;

    public DmHadrClusterDataType( )
    {
    }

    public DmHadrClusterDataType(string clusterName,
        byte quorumType,
        string quorumTypeDesc,
        byte quorumState,
        string quorumStateDesc)
    {
        _clusterName = clusterName;
        _quorumType = quorumType;
        _quorumTypeDesc = quorumTypeDesc;
        _quorumState = quorumState;
        _quorumStateDesc = quorumStateDesc;
    }

    public string ClusterName => _clusterName;
    public byte QuorumType => _quorumType;
    public string QuorumTypeDesc => _quorumTypeDesc;
    public byte QuorumState => _quorumState;
    public string QuorumStateDesc => _quorumStateDesc;
}
