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

public class SyslockinfoDataType
{
    readonly string _rscText = string.Empty;
    readonly byte[] _rscBin = Array.Empty<byte>();
    readonly byte[] _rscValblk = Array.Empty<byte>();
    readonly short _rscDbid = 0;
    readonly short _rscIndid = 0;
    readonly int _rscObjid = 0;
    readonly byte _rscType = 0;
    readonly byte _rscFlag = 0;
    readonly byte _reqMode = 0;
    readonly byte _reqStatus = 0;
    readonly short _reqRefcnt = 0;
    readonly short _reqCryrefcnt = 0;
    readonly int _reqLifetime = 0;
    readonly int _reqSpid = 0;
    readonly int _reqEcid = 0;
    readonly short _reqOwnertype = 0;
    readonly long? _reqTransactionid;
    readonly Guid? _reqTransactionuow;

    public SyslockinfoDataType( )
    {
    }

    public SyslockinfoDataType(string rscText,
        byte[] rscBin,
        byte[] rscValblk,
        short rscDbid,
        short rscIndid,
        int rscObjid,
        byte rscType,
        byte rscFlag,
        byte reqMode,
        byte reqStatus,
        short reqRefcnt,
        short reqCryrefcnt,
        int reqLifetime,
        int reqSpid,
        int reqEcid,
        short reqOwnertype,
        long? reqTransactionid,
        Guid? reqTransactionuow)
    {
        _rscText = rscText;
        _rscBin = rscBin;
        _rscValblk = rscValblk;
        _rscDbid = rscDbid;
        _rscIndid = rscIndid;
        _rscObjid = rscObjid;
        _rscType = rscType;
        _rscFlag = rscFlag;
        _reqMode = reqMode;
        _reqStatus = reqStatus;
        _reqRefcnt = reqRefcnt;
        _reqCryrefcnt = reqCryrefcnt;
        _reqLifetime = reqLifetime;
        _reqSpid = reqSpid;
        _reqEcid = reqEcid;
        _reqOwnertype = reqOwnertype;
        _reqTransactionid = reqTransactionid;
        _reqTransactionuow = reqTransactionuow;
    }

    public string RscText => _rscText;
    public byte[] RscBin => _rscBin;
    public byte[] RscValblk => _rscValblk;
    public short RscDbid => _rscDbid;
    public short RscIndid => _rscIndid;
    public int RscObjid => _rscObjid;
    public byte RscType => _rscType;
    public byte RscFlag => _rscFlag;
    public byte ReqMode => _reqMode;
    public byte ReqStatus => _reqStatus;
    public short ReqRefcnt => _reqRefcnt;
    public short ReqCryrefcnt => _reqCryrefcnt;
    public int ReqLifetime => _reqLifetime;
    public int ReqSpid => _reqSpid;
    public int ReqEcid => _reqEcid;
    public short ReqOwnertype => _reqOwnertype;
    public long? ReqTransactionid => _reqTransactionid;
    public Guid? ReqTransactionuow => _reqTransactionuow;
}
