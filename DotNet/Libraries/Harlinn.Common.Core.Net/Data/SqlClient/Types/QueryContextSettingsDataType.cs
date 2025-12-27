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

public class QueryContextSettingsDataType
{
    readonly long _contextSettingsId = 0;
    readonly byte[]? _setOptions;
    readonly short _languageId = 0;
    readonly short _dateFormat = 0;
    readonly byte _dateFirst = 0;
    readonly byte[]? _status;
    readonly int _requiredCursorOptions = 0;
    readonly int _acceptableCursorOptions = 0;
    readonly short _mergeActionType = 0;
    readonly int _defaultSchemaId = 0;
    readonly bool _isReplicationSpecific = false;
    readonly byte[]? _isContained;

    public QueryContextSettingsDataType( )
    {
    }

    public QueryContextSettingsDataType(long contextSettingsId,
        byte[]? setOptions,
        short languageId,
        short dateFormat,
        byte dateFirst,
        byte[]? status,
        int requiredCursorOptions,
        int acceptableCursorOptions,
        short mergeActionType,
        int defaultSchemaId,
        bool isReplicationSpecific,
        byte[]? isContained)
    {
        _contextSettingsId = contextSettingsId;
        _setOptions = setOptions;
        _languageId = languageId;
        _dateFormat = dateFormat;
        _dateFirst = dateFirst;
        _status = status;
        _requiredCursorOptions = requiredCursorOptions;
        _acceptableCursorOptions = acceptableCursorOptions;
        _mergeActionType = mergeActionType;
        _defaultSchemaId = defaultSchemaId;
        _isReplicationSpecific = isReplicationSpecific;
        _isContained = isContained;
    }

    public long ContextSettingsId => _contextSettingsId;
    public byte[]? SetOptions => _setOptions;
    public short LanguageId => _languageId;
    public short DateFormat => _dateFormat;
    public byte DateFirst => _dateFirst;
    public byte[]? Status => _status;
    public int RequiredCursorOptions => _requiredCursorOptions;
    public int AcceptableCursorOptions => _acceptableCursorOptions;
    public short MergeActionType => _mergeActionType;
    public int DefaultSchemaId => _defaultSchemaId;
    public bool IsReplicationSpecific => _isReplicationSpecific;
    public byte[]? IsContained => _isContained;
}
