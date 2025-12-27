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

public class FulltextIndexesDataType
{
    readonly int _objectId = 0;
    readonly int _uniqueIndexId = 0;
    readonly int? _fulltextCatalogId;
    readonly bool _isEnabled = false;
    readonly string? _changeTrackingState;
    readonly string? _changeTrackingStateDesc;
    readonly bool _hasCrawlCompleted = false;
    readonly string _crawlType = string.Empty;
    readonly string? _crawlTypeDesc;
    readonly DateTime? _crawlStartDate;
    readonly DateTime? _crawlEndDate;
    readonly byte[]? _incrementalTimestamp;
    readonly int? _stoplistId;
    readonly int? _propertyListId;
    readonly int _dataSpaceId = 0;

    public FulltextIndexesDataType( )
    {
    }

    public FulltextIndexesDataType(int objectId,
        int uniqueIndexId,
        int? fulltextCatalogId,
        bool isEnabled,
        string? changeTrackingState,
        string? changeTrackingStateDesc,
        bool hasCrawlCompleted,
        string crawlType,
        string? crawlTypeDesc,
        DateTime? crawlStartDate,
        DateTime? crawlEndDate,
        byte[]? incrementalTimestamp,
        int? stoplistId,
        int? propertyListId,
        int dataSpaceId)
    {
        _objectId = objectId;
        _uniqueIndexId = uniqueIndexId;
        _fulltextCatalogId = fulltextCatalogId;
        _isEnabled = isEnabled;
        _changeTrackingState = changeTrackingState;
        _changeTrackingStateDesc = changeTrackingStateDesc;
        _hasCrawlCompleted = hasCrawlCompleted;
        _crawlType = crawlType;
        _crawlTypeDesc = crawlTypeDesc;
        _crawlStartDate = crawlStartDate;
        _crawlEndDate = crawlEndDate;
        _incrementalTimestamp = incrementalTimestamp;
        _stoplistId = stoplistId;
        _propertyListId = propertyListId;
        _dataSpaceId = dataSpaceId;
    }

    public int ObjectId => _objectId;
    public int UniqueIndexId => _uniqueIndexId;
    public int? FulltextCatalogId => _fulltextCatalogId;
    public bool IsEnabled => _isEnabled;
    public string? ChangeTrackingState => _changeTrackingState;
    public string? ChangeTrackingStateDesc => _changeTrackingStateDesc;
    public bool HasCrawlCompleted => _hasCrawlCompleted;
    public string CrawlType => _crawlType;
    public string? CrawlTypeDesc => _crawlTypeDesc;
    public DateTime? CrawlStartDate => _crawlStartDate;
    public DateTime? CrawlEndDate => _crawlEndDate;
    public byte[]? IncrementalTimestamp => _incrementalTimestamp;
    public int? StoplistId => _stoplistId;
    public int? PropertyListId => _propertyListId;
    public int DataSpaceId => _dataSpaceId;
}
