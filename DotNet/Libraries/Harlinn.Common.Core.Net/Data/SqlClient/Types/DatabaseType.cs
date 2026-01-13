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


namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{

    /// <summary>
    /// Represents a SQL Server database type, including both system and user-defined types.
    /// </summary>
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

        /// <summary>
        /// Name of the type. Is unique within the schema.
        /// </summary>
        public string Name => _name;

        /// <summary>
        /// ID of the internal system type.
        /// </summary>
        public byte SystemTypeId => _systemTypeId;

        /// <summary>
        /// ID of the internal system type.
        /// </summary>
        public SystemType SystemType => (SystemType)_systemTypeId;

        /// <summary>
        /// <para>ID of the type. Is unique within the database.</para>
        /// <para>
        /// CLR assembly types such as hierarchyid, geometry and geography, 
        /// will have a different system_type_id, and can be identified 
        /// using IsAssemblyType. The sysname data type is an internal 
        /// data type based on nvarchar.
        /// </para>
        /// </summary>
        public int UserTypeId => _userTypeId;

        /// <summary>
        /// ID of the schema to which the type belongs.
        /// </summary>
        public int SchemaId => _schemaId;

        /// <summary>
        /// <para>
        /// ID of the individual owner if different from schema owner. 
        /// By default, schema-contained objects are owned by the schema owner. 
        /// However, an alternate owner can be specified by using the 
        /// ALTER AUTHORIZATION statement to change ownership.
        /// </para>
        /// <para>
        /// null if there is no alternate individual owner.
        /// </para>
        /// </summary>
        public int? PrincipalId => _principalId;

        /// <summary>
        /// <para>
        /// Maximum length (in bytes) of the type.
        /// </para>
        /// <para>
        /// -1 = Column data type is varchar(max), nvarchar(max), varbinary(max), or xml.
        /// For text columns, the max_length value will be 16.
        /// </para>
        /// </summary>
        public short MaxLength => _maxLength;

        /// <summary>
        /// Max precision of the type if it is numeric-based; otherwise, 0.
        /// </summary>
        public byte Precision => _precision;

        /// <summary>
        /// Max scale of the type if it is numeric-based; otherwise, 0.
        /// </summary>
        public byte Scale => _scale;

        /// <summary>
        /// Name of the collation of the type if it is character-based; otherwise, null.
        /// </summary>
        public string? CollationName => _collationName;

        /// <summary>
        /// Type is nullable.
        /// </summary>
        public bool IsNullable => _isNullable;

        /// <summary>
        /// true if the type is user-defined; otherwise, false.
        /// </summary>
        public bool IsUserDefined => _isUserDefined;

        /// <summary>
        /// true if the type is defined in a CLR assembly; otherwise, false.
        /// </summary>
        public bool IsAssemblyType => _isAssemblyType;

        /// <summary>
        /// ID of the stand-alone default that is bound to the type by using sp_bindefault.
        /// </summary>
        public int DefaultObjectId => _defaultObjectId;

        /// <summary>
        /// ID of the stand-alone rule that is bound to the type by using sp_bindrule.
        /// </summary>
        public int RuleObjectId => _ruleObjectId;

        /// <summary>
        /// Indicates that the type is a table.
        /// </summary>
        public bool IsTableType => _isTableType;
    }


}
