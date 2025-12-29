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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{
    /// <summary>
    /// Represents a single column description returned by <c>sp_describe_first_result_set</c>.
    /// See: https://learn.microsoft.com/en-us/sql/relational-databases/system-stored-procedures/sp-describe-first-result-set-transact-sql
    /// </summary>
    public sealed class ResultSetColumn
    {
        readonly bool _isHidden;
        readonly int _columnOrdinal;
        readonly string? _name;
        readonly bool _isNullable;
        readonly int _systemTypeId;
        readonly string? _systemTypeName;
        readonly short? _maxLength;
        readonly byte? _precision;
        readonly byte? _scale;
        readonly string? _collationName;
        readonly int? _userTypeId;
        readonly string? _userTypeDatabase;
        readonly string? _userTypeSchema;
        readonly string? _userTypeName;
        readonly string? _assemblyQualifiedTypeName;
        readonly int? _xmlCollectionId;
        readonly string? _xmlCollectionDatabase;
        readonly string? _xmlCollectionSchema;
        readonly string? _xmlCollectionName;
        readonly bool _isXmlDocument;
        readonly bool _isCaseSensitive;
        readonly bool _isFixedLengthClrType;
        readonly string? _sourceServer;
        readonly string? _sourceDatabase;
        readonly string? _sourceSchema;
        readonly string? _sourceTable;
        readonly string? _sourceColumn;
        readonly bool _isIdentityColumn;
        readonly bool _isPartOfUniqueKey;
        readonly bool _isUpdateable;
        readonly bool _isComputedColumn;
        readonly bool _isSparseColumnSet;
        readonly int? _ordinalInOrderByList;
        readonly int? _orderByListLength;
        readonly short? _orderByIsDescending;
        readonly int? _tdsTypeId;
        readonly int? _tdsLength;
        readonly int? _tdsCollation;

        public ResultSetColumn(bool isHidden, int columnOrdinal, string? name, bool isNullable, int systemTypeId, string? systemTypeName, short? maxLength, byte? precision, byte? scale, string? collationName, int? userTypeId, string? userTypeDatabase, string? userTypeSchema, string? userTypeName, string? assemblyQualifiedTypeName, int? xmlCollectionId, string? xmlCollectionDatabase, string? xmlCollectionSchema, string? xmlCollectionName, bool isXmlDocument, bool isCaseSensitive, bool isFixedLengthClrType, string? sourceServer, string? sourceDatabase, string? sourceSchema, string? sourceTable, string? sourceColumn, bool isIdentityColumn, bool isPartOfUniqueKey, bool isUpdateable, bool isComputedColumn, bool isSparseColumnSet, int? ordinalInOrderByList, int? orderByListLength, short? orderByIsDescending, int? tdsTypeId, int? tdsLength, int? tdsCollation)
        {
            _isHidden = isHidden;
            _columnOrdinal = columnOrdinal;
            _name = name;
            _isNullable = isNullable;
            _systemTypeId = systemTypeId;
            _systemTypeName = systemTypeName;
            _maxLength = maxLength;
            _precision = precision;
            _scale = scale;
            _collationName = collationName;
            _userTypeId = userTypeId;
            _userTypeDatabase = userTypeDatabase;
            _userTypeSchema = userTypeSchema;
            _userTypeName = userTypeName;
            _assemblyQualifiedTypeName = assemblyQualifiedTypeName;
            _xmlCollectionId = xmlCollectionId;
            _xmlCollectionDatabase = xmlCollectionDatabase;
            _xmlCollectionSchema = xmlCollectionSchema;
            _xmlCollectionName = xmlCollectionName;
            _isXmlDocument = isXmlDocument;
            _isCaseSensitive = isCaseSensitive;
            _isFixedLengthClrType = isFixedLengthClrType;
            _sourceServer = sourceServer;
            _sourceDatabase = sourceDatabase;
            _sourceSchema = sourceSchema;
            _sourceTable = sourceTable;
            _sourceColumn = sourceColumn;
            _isIdentityColumn = isIdentityColumn;
            _isPartOfUniqueKey = isPartOfUniqueKey;
            _isUpdateable = isUpdateable;
            _isComputedColumn = isComputedColumn;
            _isSparseColumnSet = isSparseColumnSet;
            _ordinalInOrderByList = ordinalInOrderByList;
            _orderByListLength = orderByListLength;
            _orderByIsDescending = orderByIsDescending;
            _tdsTypeId = tdsTypeId;
            _tdsLength = tdsLength;
            _tdsCollation = tdsCollation;
        }

        public bool IsHidden => _isHidden;

        public int ColumnOrdinal => _columnOrdinal;

        public string? Name => _name;

        public bool IsNullable => _isNullable;

        public int SystemTypeId => _systemTypeId;

        public string? SystemTypeName => _systemTypeName;

        public short? MaxLength => _maxLength;

        public byte? Precision => _precision;

        public byte? Scale => _scale;

        public string? CollationName => _collationName;
                                     
        public int? UserTypeId => _userTypeId;

        public string? UserTypeDatabase => _userTypeDatabase;

        public string? UserTypeSchema => _userTypeSchema;

        public string? UserTypeName => _userTypeName;

        public string? AssemblyQualifiedTypeName => _assemblyQualifiedTypeName;

        public int? XmlCollectionId => _xmlCollectionId;

        public string? XmlCollectionDatabase => _xmlCollectionDatabase;

        public string? XmlCollectionSchema => _xmlCollectionSchema;

        public string? XmlCollectionName => _xmlCollectionName;

        public bool IsXmlDocument => _isXmlDocument;

        public bool IsCaseSensitive => _isCaseSensitive;

        public bool IsFixedLengthClrType => _isFixedLengthClrType;

        public string? SourceServer => _sourceServer;

        public string? SourceDatabase => _sourceDatabase;

        public string? SourceSchema => _sourceSchema;

        public string? SourceTable => _sourceTable;

        public string? SourceColumn => _sourceColumn;

        public bool IsIdentityColumn => _isIdentityColumn;

        public bool IsPartOfUniqueKey => _isPartOfUniqueKey;

        public bool IsUpdateable => _isUpdateable;

        public bool IsComputedColumn => _isComputedColumn;

        public bool IsSparseColumnSet => _isSparseColumnSet;

        public int? OrdinalInOrderByList => _ordinalInOrderByList;

        public int? OrderByListLength => _orderByListLength;

        public short? OrderByIsDescending => _orderByIsDescending;

        public int? TdsTypeId => _tdsTypeId;

        public int? TdsLength => _tdsLength;

        public int? TdsCollation => _tdsCollation;

        public override string ToString()
        {
            return $"{_columnOrdinal}: {_name} ({_systemTypeName})";
        }

    }
}