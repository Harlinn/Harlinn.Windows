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

public class SystemParametersDataType
{
    readonly int _objectId = 0;
    readonly string? _name;
    readonly int _parameterId = 0;
    readonly byte _systemTypeId = 0;
    readonly int _userTypeId = 0;
    readonly short _maxLength = 0;
    readonly byte _precision = 0;
    readonly byte _scale = 0;
    readonly bool _isOutput = false;
    readonly bool _isCursorRef = false;
    readonly bool _hasDefaultValue = false;
    readonly bool _isXmlDocument = false;
    readonly object? _defaultValue;
    readonly int _xmlCollectionId = 0;
    readonly bool _isReadonly = false;
    readonly bool? _isNullable;
    readonly int? _encryptionType;
    readonly string? _encryptionTypeDesc;
    readonly string? _encryptionAlgorithmName;
    readonly int? _columnEncryptionKeyId;
    readonly string? _columnEncryptionKeyDatabaseName;

    public SystemParametersDataType( )
    {
    }

    public SystemParametersDataType(int objectId,
        string? name,
        int parameterId,
        byte systemTypeId,
        int userTypeId,
        short maxLength,
        byte precision,
        byte scale,
        bool isOutput,
        bool isCursorRef,
        bool hasDefaultValue,
        bool isXmlDocument,
        object? defaultValue,
        int xmlCollectionId,
        bool isReadonly,
        bool? isNullable,
        int? encryptionType,
        string? encryptionTypeDesc,
        string? encryptionAlgorithmName,
        int? columnEncryptionKeyId,
        string? columnEncryptionKeyDatabaseName)
    {
        _objectId = objectId;
        _name = name;
        _parameterId = parameterId;
        _systemTypeId = systemTypeId;
        _userTypeId = userTypeId;
        _maxLength = maxLength;
        _precision = precision;
        _scale = scale;
        _isOutput = isOutput;
        _isCursorRef = isCursorRef;
        _hasDefaultValue = hasDefaultValue;
        _isXmlDocument = isXmlDocument;
        _defaultValue = defaultValue;
        _xmlCollectionId = xmlCollectionId;
        _isReadonly = isReadonly;
        _isNullable = isNullable;
        _encryptionType = encryptionType;
        _encryptionTypeDesc = encryptionTypeDesc;
        _encryptionAlgorithmName = encryptionAlgorithmName;
        _columnEncryptionKeyId = columnEncryptionKeyId;
        _columnEncryptionKeyDatabaseName = columnEncryptionKeyDatabaseName;
    }

    public int ObjectId => _objectId;
    public string? Name => _name;
    public int ParameterId => _parameterId;
    public byte SystemTypeId => _systemTypeId;
    public int UserTypeId => _userTypeId;
    public short MaxLength => _maxLength;
    public byte Precision => _precision;
    public byte Scale => _scale;
    public bool IsOutput => _isOutput;
    public bool IsCursorRef => _isCursorRef;
    public bool HasDefaultValue => _hasDefaultValue;
    public bool IsXmlDocument => _isXmlDocument;
    public object? DefaultValue => _defaultValue;
    public int XmlCollectionId => _xmlCollectionId;
    public bool IsReadonly => _isReadonly;
    public bool? IsNullable => _isNullable;
    public int? EncryptionType => _encryptionType;
    public string? EncryptionTypeDesc => _encryptionTypeDesc;
    public string? EncryptionAlgorithmName => _encryptionAlgorithmName;
    public int? ColumnEncryptionKeyId => _columnEncryptionKeyId;
    public string? ColumnEncryptionKeyDatabaseName => _columnEncryptionKeyDatabaseName;
}
