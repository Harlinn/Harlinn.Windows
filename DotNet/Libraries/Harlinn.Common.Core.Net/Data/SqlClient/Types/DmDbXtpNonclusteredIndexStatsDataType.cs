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

public class DmDbXtpNonclusteredIndexStatsDataType
{
    readonly int _objectId = 0;
    readonly int _xtpObjectId = 0;
    readonly int _indexId = 0;
    readonly long _deltaPages = 0;
    readonly long _internalPages = 0;
    readonly long _leafPages = 0;
    readonly long _outstandingRetiredNodes = 0;
    readonly long _pageUpdateCount = 0;
    readonly long _pageUpdateRetryCount = 0;
    readonly long _pageConsolidationCount = 0;
    readonly long _pageConsolidationRetryCount = 0;
    readonly long _pageSplitCount = 0;
    readonly long _pageSplitRetryCount = 0;
    readonly long _keySplitCount = 0;
    readonly long _keySplitRetryCount = 0;
    readonly long _pageMergeCount = 0;
    readonly long _pageMergeRetryCount = 0;
    readonly long _keyMergeCount = 0;
    readonly long _keyMergeRetryCount = 0;
    readonly bool _usesKeyNormalization = false;

    public DmDbXtpNonclusteredIndexStatsDataType( )
    {
    }

    public DmDbXtpNonclusteredIndexStatsDataType(int objectId,
        int xtpObjectId,
        int indexId,
        long deltaPages,
        long internalPages,
        long leafPages,
        long outstandingRetiredNodes,
        long pageUpdateCount,
        long pageUpdateRetryCount,
        long pageConsolidationCount,
        long pageConsolidationRetryCount,
        long pageSplitCount,
        long pageSplitRetryCount,
        long keySplitCount,
        long keySplitRetryCount,
        long pageMergeCount,
        long pageMergeRetryCount,
        long keyMergeCount,
        long keyMergeRetryCount,
        bool usesKeyNormalization)
    {
        _objectId = objectId;
        _xtpObjectId = xtpObjectId;
        _indexId = indexId;
        _deltaPages = deltaPages;
        _internalPages = internalPages;
        _leafPages = leafPages;
        _outstandingRetiredNodes = outstandingRetiredNodes;
        _pageUpdateCount = pageUpdateCount;
        _pageUpdateRetryCount = pageUpdateRetryCount;
        _pageConsolidationCount = pageConsolidationCount;
        _pageConsolidationRetryCount = pageConsolidationRetryCount;
        _pageSplitCount = pageSplitCount;
        _pageSplitRetryCount = pageSplitRetryCount;
        _keySplitCount = keySplitCount;
        _keySplitRetryCount = keySplitRetryCount;
        _pageMergeCount = pageMergeCount;
        _pageMergeRetryCount = pageMergeRetryCount;
        _keyMergeCount = keyMergeCount;
        _keyMergeRetryCount = keyMergeRetryCount;
        _usesKeyNormalization = usesKeyNormalization;
    }

    public int ObjectId => _objectId;
    public int XtpObjectId => _xtpObjectId;
    public int IndexId => _indexId;
    public long DeltaPages => _deltaPages;
    public long InternalPages => _internalPages;
    public long LeafPages => _leafPages;
    public long OutstandingRetiredNodes => _outstandingRetiredNodes;
    public long PageUpdateCount => _pageUpdateCount;
    public long PageUpdateRetryCount => _pageUpdateRetryCount;
    public long PageConsolidationCount => _pageConsolidationCount;
    public long PageConsolidationRetryCount => _pageConsolidationRetryCount;
    public long PageSplitCount => _pageSplitCount;
    public long PageSplitRetryCount => _pageSplitRetryCount;
    public long KeySplitCount => _keySplitCount;
    public long KeySplitRetryCount => _keySplitRetryCount;
    public long PageMergeCount => _pageMergeCount;
    public long PageMergeRetryCount => _pageMergeRetryCount;
    public long KeyMergeCount => _keyMergeCount;
    public long KeyMergeRetryCount => _keyMergeRetryCount;
    public bool UsesKeyNormalization => _usesKeyNormalization;
}
