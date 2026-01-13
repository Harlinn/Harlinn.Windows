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

public class SysprocessesDataType
{
    readonly short _spid = 0;
    readonly short _kpid = 0;
    readonly short _blocked = 0;
    readonly byte[] _waittype = Array.Empty<byte>();
    readonly long _waittime = 0;
    readonly string _lastwaittype = string.Empty;
    readonly string _waitresource = string.Empty;
    readonly short _dbid = 0;
    readonly short? _uid;
    readonly int _cpu = 0;
    readonly long _physicalIo = 0;
    readonly int _memusage = 0;
    readonly DateTime _loginTime;
    readonly DateTime _lastBatch;
    readonly short _ecid = 0;
    readonly short _openTran = 0;
    readonly string _status = string.Empty;
    readonly byte[] _sid = Array.Empty<byte>();
    readonly string _hostname = string.Empty;
    readonly string _programName = string.Empty;
    readonly string _hostprocess = string.Empty;
    readonly string _cmd = string.Empty;
    readonly string _ntDomain = string.Empty;
    readonly string _ntUsername = string.Empty;
    readonly string _netAddress = string.Empty;
    readonly string _netLibrary = string.Empty;
    readonly string _loginame = string.Empty;
    readonly byte[] _contextInfo = Array.Empty<byte>();
    readonly byte[] _sqlHandle = Array.Empty<byte>();
    readonly int _stmtStart = 0;
    readonly int _stmtEnd = 0;
    readonly int _requestId = 0;
    readonly byte[]? _pageResource;

    public SysprocessesDataType( )
    {
    }

    public SysprocessesDataType(short spid,
        short kpid,
        short blocked,
        byte[] waittype,
        long waittime,
        string lastwaittype,
        string waitresource,
        short dbid,
        short? uid,
        int cpu,
        long physicalIo,
        int memusage,
        DateTime loginTime,
        DateTime lastBatch,
        short ecid,
        short openTran,
        string status,
        byte[] sid,
        string hostname,
        string programName,
        string hostprocess,
        string cmd,
        string ntDomain,
        string ntUsername,
        string netAddress,
        string netLibrary,
        string loginame,
        byte[] contextInfo,
        byte[] sqlHandle,
        int stmtStart,
        int stmtEnd,
        int requestId,
        byte[]? pageResource)
    {
        _spid = spid;
        _kpid = kpid;
        _blocked = blocked;
        _waittype = waittype;
        _waittime = waittime;
        _lastwaittype = lastwaittype;
        _waitresource = waitresource;
        _dbid = dbid;
        _uid = uid;
        _cpu = cpu;
        _physicalIo = physicalIo;
        _memusage = memusage;
        _loginTime = loginTime;
        _lastBatch = lastBatch;
        _ecid = ecid;
        _openTran = openTran;
        _status = status;
        _sid = sid;
        _hostname = hostname;
        _programName = programName;
        _hostprocess = hostprocess;
        _cmd = cmd;
        _ntDomain = ntDomain;
        _ntUsername = ntUsername;
        _netAddress = netAddress;
        _netLibrary = netLibrary;
        _loginame = loginame;
        _contextInfo = contextInfo;
        _sqlHandle = sqlHandle;
        _stmtStart = stmtStart;
        _stmtEnd = stmtEnd;
        _requestId = requestId;
        _pageResource = pageResource;
    }

    public short Spid => _spid;
    public short Kpid => _kpid;
    public short Blocked => _blocked;
    public byte[] Waittype => _waittype;
    public long Waittime => _waittime;
    public string Lastwaittype => _lastwaittype;
    public string Waitresource => _waitresource;
    public short Dbid => _dbid;
    public short? Uid => _uid;
    public int Cpu => _cpu;
    public long PhysicalIo => _physicalIo;
    public int Memusage => _memusage;
    public DateTime LoginTime => _loginTime;
    public DateTime LastBatch => _lastBatch;
    public short Ecid => _ecid;
    public short OpenTran => _openTran;
    public string Status => _status;
    public byte[] Sid => _sid;
    public string Hostname => _hostname;
    public string ProgramName => _programName;
    public string Hostprocess => _hostprocess;
    public string Cmd => _cmd;
    public string NtDomain => _ntDomain;
    public string NtUsername => _ntUsername;
    public string NetAddress => _netAddress;
    public string NetLibrary => _netLibrary;
    public string Loginame => _loginame;
    public byte[] ContextInfo => _contextInfo;
    public byte[] SqlHandle => _sqlHandle;
    public int StmtStart => _stmtStart;
    public int StmtEnd => _stmtEnd;
    public int RequestId => _requestId;
    public byte[]? PageResource => _pageResource;
}
