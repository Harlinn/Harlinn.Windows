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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{
    public sealed class Sequence : ISchemaObject
    {
        private readonly string _name;
        private readonly int _objectId;
        private readonly int? _principalId;
        private readonly int _schemaId;
        private readonly int? _parentObjectId;
        private readonly SchemaObjectType _type;
        private readonly string _typeDesc;
        private readonly DateTime _createDate;
        private readonly DateTime _modifyDate;
        private readonly bool? _isMsShipped;
        private readonly bool? _isPublished;
        private readonly bool? _isSchemaPublished;
        private readonly decimal _startValue;
        private readonly decimal _increment;
        private readonly decimal _minimumValue;
        private readonly decimal _maximumValue;
        private readonly bool _isCycling;
        private readonly bool _isCached;
        private readonly int? _cacheSize;
        private readonly byte _systemTypeId;
        private readonly int _userTypeId;
        private readonly byte _precision;
        private readonly byte _scale;
        private readonly decimal? _currentValue;
        private readonly bool _isExhausted;
        private readonly decimal? _lastUsedValue;

        public Sequence(
            string name,
            int objectId,
            int? principalId,
            int schemaId,
            int? parentObjectId,
            string type,
            string typeDesc,
            DateTime createDate,
            DateTime modifyDate,
            bool? isMsShipped,
            bool? isPublished,
            bool? isSchemaPublished,
            decimal startValue,
            decimal increment,
            decimal minimumValue,
            decimal maximumValue,
            bool isCycling,
            bool isCached,
            int? cacheSize,
            byte systemTypeId,
            int userTypeId,
            byte precision,
            byte scale,
            decimal? currentValue,
            bool isExhausted,
            decimal? lastUsedValue)
        {
            _name = name ?? throw new ArgumentNullException(nameof(name));
            _objectId = objectId;
            _principalId = principalId;
            _schemaId = schemaId;
            _parentObjectId = parentObjectId;
            _type = type?.ToSchemaObjectType() ?? throw new ArgumentNullException(nameof(type));
            _typeDesc = typeDesc ?? throw new ArgumentNullException(nameof(typeDesc));
            _createDate = createDate;
            _modifyDate = modifyDate;
            _isMsShipped = isMsShipped;
            _isPublished = isPublished;
            _isSchemaPublished = isSchemaPublished;
            _startValue = startValue;
            _increment = increment;
            _minimumValue = minimumValue;
            _maximumValue = maximumValue;
            _isCycling = isCycling;
            _isCached = isCached;
            _cacheSize = cacheSize;
            _systemTypeId = systemTypeId;
            _userTypeId = userTypeId;
            _precision = precision;
            _scale = scale;
            _currentValue = currentValue;
            _isExhausted = isExhausted;
            _lastUsedValue = lastUsedValue;
        }

        public string Name => _name;
        public int ObjectId => _objectId;
        public int? PrincipalId => _principalId;
        public int SchemaId => _schemaId;
        public int? ParentObjectId => _parentObjectId;
        public SchemaObjectType Type => _type;
        public string TypeDesc => _typeDesc;
        public DateTime CreateDate => _createDate;
        public DateTime ModifyDate => _modifyDate;
        public bool? IsMsShipped => _isMsShipped;
        public bool? IsPublished => _isPublished;
        public bool? IsSchemaPublished => _isSchemaPublished;
        public decimal StartValue => _startValue;
        public decimal Increment => _increment;
        public decimal MinimumValue => _minimumValue;
        public decimal MaximumValue => _maximumValue;
        public bool IsCycling => _isCycling;
        public bool IsCached => _isCached;
        public int? CacheSize => _cacheSize;
        public byte SystemTypeId => _systemTypeId;
        public int UserTypeId => _userTypeId;
        public byte Precision => _precision;
        public byte Scale => _scale;
        public decimal? CurrentValue => _currentValue;
        public bool IsExhausted => _isExhausted;
        public decimal? LastUsedValue => _lastUsedValue;

    }
}