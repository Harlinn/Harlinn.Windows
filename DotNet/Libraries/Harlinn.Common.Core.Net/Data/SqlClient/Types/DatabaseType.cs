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


namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{
    public class DatabaseType
    {
        readonly string _name;
        readonly byte _systemTypeId;
        readonly int _userTypeId;
        readonly int _schemaId;
        readonly int? _principalId;
        readonly short _maxLength;
        readonly byte _precision;
        readonly byte _scale;
        readonly string? _collationName;
        readonly bool _isNullable;
        readonly bool _isUserDefined;
        readonly bool _isAssemblyType;
        readonly int _defaultObjectId;
        readonly int _ruleObjectId;
        readonly bool _isTableType;

        public DatabaseType(string name, byte systemTypeId, int userTypeId, int schemaId, int? principalId, short maxLength, byte precision, byte scale, string? collationName, bool isNullable, bool isUserDefined, bool isAssemblyType, int defaultObjectId, int ruleObjectId, bool isTableType)
        {
            _name = name;
            _systemTypeId = systemTypeId;
            _userTypeId = userTypeId;
            _schemaId = schemaId;
            _principalId = principalId;
            _maxLength = maxLength;
            _precision = precision;
            _scale = scale;
            _collationName = collationName;
            _isNullable = isNullable;
            _isUserDefined = isUserDefined;
            _isAssemblyType = isAssemblyType;
            _defaultObjectId = defaultObjectId;
            _ruleObjectId = ruleObjectId;
            _isTableType = isTableType;
        }

        public string Name => _name;

        public byte SystemTypeId => _systemTypeId;

        public int UserTypeId => _userTypeId;

        public int SchemaId => _schemaId;

        public int? PrincipalId => _principalId;

        public short MaxLength => _maxLength;

        public byte Precision => _precision;

        public byte Scale => _scale;

        public string? CollationName => _collationName;

        public bool IsNullable => _isNullable;

        public bool IsUserDefined => _isUserDefined;

        public bool IsAssemblyType => _isAssemblyType;

        public int DefaultObjectId => _defaultObjectId;

        public int RuleObjectId => _ruleObjectId;

        public bool IsTableType => _isTableType;
    }


}
