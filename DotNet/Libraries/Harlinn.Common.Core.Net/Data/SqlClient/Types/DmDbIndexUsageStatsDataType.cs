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

public class DmDbIndexUsageStatsDataType
{
    readonly short _databaseId = 0;
    readonly int _objectId = 0;
    readonly int _indexId = 0;
    readonly long _userSeeks = 0;
    readonly long _userScans = 0;
    readonly long _userLookups = 0;
    readonly long _userUpdates = 0;
    readonly DateTime? _lastUserSeek;
    readonly DateTime? _lastUserScan;
    readonly DateTime? _lastUserLookup;
    readonly DateTime? _lastUserUpdate;
    readonly long _systemSeeks = 0;
    readonly long _systemScans = 0;
    readonly long _systemLookups = 0;
    readonly long _systemUpdates = 0;
    readonly DateTime? _lastSystemSeek;
    readonly DateTime? _lastSystemScan;
    readonly DateTime? _lastSystemLookup;
    readonly DateTime? _lastSystemUpdate;

    public DmDbIndexUsageStatsDataType( )
    {
    }

    public DmDbIndexUsageStatsDataType(short databaseId,
        int objectId,
        int indexId,
        long userSeeks,
        long userScans,
        long userLookups,
        long userUpdates,
        DateTime? lastUserSeek,
        DateTime? lastUserScan,
        DateTime? lastUserLookup,
        DateTime? lastUserUpdate,
        long systemSeeks,
        long systemScans,
        long systemLookups,
        long systemUpdates,
        DateTime? lastSystemSeek,
        DateTime? lastSystemScan,
        DateTime? lastSystemLookup,
        DateTime? lastSystemUpdate)
    {
        _databaseId = databaseId;
        _objectId = objectId;
        _indexId = indexId;
        _userSeeks = userSeeks;
        _userScans = userScans;
        _userLookups = userLookups;
        _userUpdates = userUpdates;
        _lastUserSeek = lastUserSeek;
        _lastUserScan = lastUserScan;
        _lastUserLookup = lastUserLookup;
        _lastUserUpdate = lastUserUpdate;
        _systemSeeks = systemSeeks;
        _systemScans = systemScans;
        _systemLookups = systemLookups;
        _systemUpdates = systemUpdates;
        _lastSystemSeek = lastSystemSeek;
        _lastSystemScan = lastSystemScan;
        _lastSystemLookup = lastSystemLookup;
        _lastSystemUpdate = lastSystemUpdate;
    }

    public short DatabaseId => _databaseId;
    public int ObjectId => _objectId;
    public int IndexId => _indexId;
    public long UserSeeks => _userSeeks;
    public long UserScans => _userScans;
    public long UserLookups => _userLookups;
    public long UserUpdates => _userUpdates;
    public DateTime? LastUserSeek => _lastUserSeek;
    public DateTime? LastUserScan => _lastUserScan;
    public DateTime? LastUserLookup => _lastUserLookup;
    public DateTime? LastUserUpdate => _lastUserUpdate;
    public long SystemSeeks => _systemSeeks;
    public long SystemScans => _systemScans;
    public long SystemLookups => _systemLookups;
    public long SystemUpdates => _systemUpdates;
    public DateTime? LastSystemSeek => _lastSystemSeek;
    public DateTime? LastSystemScan => _lastSystemScan;
    public DateTime? LastSystemLookup => _lastSystemLookup;
    public DateTime? LastSystemUpdate => _lastSystemUpdate;
}
