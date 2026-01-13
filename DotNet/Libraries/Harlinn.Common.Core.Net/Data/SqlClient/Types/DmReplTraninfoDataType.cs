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

public class DmReplTraninfoDataType
{
    readonly byte? _fp2pPubExists;
    readonly int? _dbVer;
    readonly byte[]? _compRangeAddress;
    readonly byte[]? _textinfoAddress;
    readonly byte[]? _fsinfoAddress;
    readonly string? _beginLsn;
    readonly string? _commitLsn;
    readonly short? _dbid;
    readonly int? _rows;
    readonly string? _xdesid;
    readonly byte[]? _artcacheTableAddress;
    readonly string? _server;
    readonly int? _serverLenInBytes;
    readonly string? _database;
    readonly int? _dbLenInBytes;
    readonly string? _originator;
    readonly int? _originatorLenInBytes;
    readonly string? _origDb;
    readonly int? _origDbLenInBytes;
    readonly int? _cmdsInTran;
    readonly byte? _isBoundedupdateSingleton;
    readonly string? _beginUpdateLsn;
    readonly string? _deleteLsn;
    readonly string? _lastEndLsn;
    readonly byte? _fcomplete;
    readonly byte? _fcompensated;
    readonly byte? _fprocessingtext;
    readonly int? _maxCmdsInTran;
    readonly DateTime? _beginTime;
    readonly DateTime? _commitTime;
    readonly int? _sessionId;
    readonly string? _sessionPhase;
    readonly byte? _isKnownCdcTran;
    readonly int? _errorCount;

    public DmReplTraninfoDataType( )
    {
    }

    public DmReplTraninfoDataType(byte? fp2pPubExists,
        int? dbVer,
        byte[]? compRangeAddress,
        byte[]? textinfoAddress,
        byte[]? fsinfoAddress,
        string? beginLsn,
        string? commitLsn,
        short? dbid,
        int? rows,
        string? xdesid,
        byte[]? artcacheTableAddress,
        string? server,
        int? serverLenInBytes,
        string? database,
        int? dbLenInBytes,
        string? originator,
        int? originatorLenInBytes,
        string? origDb,
        int? origDbLenInBytes,
        int? cmdsInTran,
        byte? isBoundedupdateSingleton,
        string? beginUpdateLsn,
        string? deleteLsn,
        string? lastEndLsn,
        byte? fcomplete,
        byte? fcompensated,
        byte? fprocessingtext,
        int? maxCmdsInTran,
        DateTime? beginTime,
        DateTime? commitTime,
        int? sessionId,
        string? sessionPhase,
        byte? isKnownCdcTran,
        int? errorCount)
    {
        _fp2pPubExists = fp2pPubExists;
        _dbVer = dbVer;
        _compRangeAddress = compRangeAddress;
        _textinfoAddress = textinfoAddress;
        _fsinfoAddress = fsinfoAddress;
        _beginLsn = beginLsn;
        _commitLsn = commitLsn;
        _dbid = dbid;
        _rows = rows;
        _xdesid = xdesid;
        _artcacheTableAddress = artcacheTableAddress;
        _server = server;
        _serverLenInBytes = serverLenInBytes;
        _database = database;
        _dbLenInBytes = dbLenInBytes;
        _originator = originator;
        _originatorLenInBytes = originatorLenInBytes;
        _origDb = origDb;
        _origDbLenInBytes = origDbLenInBytes;
        _cmdsInTran = cmdsInTran;
        _isBoundedupdateSingleton = isBoundedupdateSingleton;
        _beginUpdateLsn = beginUpdateLsn;
        _deleteLsn = deleteLsn;
        _lastEndLsn = lastEndLsn;
        _fcomplete = fcomplete;
        _fcompensated = fcompensated;
        _fprocessingtext = fprocessingtext;
        _maxCmdsInTran = maxCmdsInTran;
        _beginTime = beginTime;
        _commitTime = commitTime;
        _sessionId = sessionId;
        _sessionPhase = sessionPhase;
        _isKnownCdcTran = isKnownCdcTran;
        _errorCount = errorCount;
    }

    public byte? Fp2pPubExists => _fp2pPubExists;
    public int? DbVer => _dbVer;
    public byte[]? CompRangeAddress => _compRangeAddress;
    public byte[]? TextinfoAddress => _textinfoAddress;
    public byte[]? FsinfoAddress => _fsinfoAddress;
    public string? BeginLsn => _beginLsn;
    public string? CommitLsn => _commitLsn;
    public short? Dbid => _dbid;
    public int? Rows => _rows;
    public string? Xdesid => _xdesid;
    public byte[]? ArtcacheTableAddress => _artcacheTableAddress;
    public string? Server => _server;
    public int? ServerLenInBytes => _serverLenInBytes;
    public string? Database => _database;
    public int? DbLenInBytes => _dbLenInBytes;
    public string? Originator => _originator;
    public int? OriginatorLenInBytes => _originatorLenInBytes;
    public string? OrigDb => _origDb;
    public int? OrigDbLenInBytes => _origDbLenInBytes;
    public int? CmdsInTran => _cmdsInTran;
    public byte? IsBoundedupdateSingleton => _isBoundedupdateSingleton;
    public string? BeginUpdateLsn => _beginUpdateLsn;
    public string? DeleteLsn => _deleteLsn;
    public string? LastEndLsn => _lastEndLsn;
    public byte? Fcomplete => _fcomplete;
    public byte? Fcompensated => _fcompensated;
    public byte? Fprocessingtext => _fprocessingtext;
    public int? MaxCmdsInTran => _maxCmdsInTran;
    public DateTime? BeginTime => _beginTime;
    public DateTime? CommitTime => _commitTime;
    public int? SessionId => _sessionId;
    public string? SessionPhase => _sessionPhase;
    public byte? IsKnownCdcTran => _isKnownCdcTran;
    public int? ErrorCount => _errorCount;
}
