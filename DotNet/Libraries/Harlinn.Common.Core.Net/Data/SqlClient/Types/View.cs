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

    public class View : ISchemaObject
    {
        readonly string _name;
        readonly int _objectId;
        readonly int? _principalId;
        readonly int _schemaId;
        readonly int? _parentObjectId;
        readonly SchemaObjectType _type;
        readonly string _typeDesc;
        readonly DateTime _createDate;
        readonly DateTime _modifyDate;
        readonly bool? _isMsShipped;
        readonly bool? _isPublished;
        readonly bool? _isSchemaPublished;
        readonly bool _isReplicated;
        readonly bool _hasReplicationFilter;
        readonly bool _hasOpaqueMetadata;
        readonly bool _hasUncheckedAssemblyData;
        readonly bool _withCheckOption;
        readonly bool _isDateCorrelationView;
        readonly bool _isTrackedByCdc;
        readonly bool _hasSnapshot;

        public View(string name, int objectId, int? principalId, int schemaId, int? parentObjectId, string type, string typeDesc, DateTime createDate, DateTime modifyDate, bool? isMsShipped, bool? isPublished, bool? isSchemaPublished, bool isReplicated, bool hasReplicationFilter, bool hasOpaqueMetadata, bool hasUncheckedAssemblyData, bool withCheckOption, bool isDateCorrelationView, bool isTrackedByCdc, bool hasSnapshot)
        {
            _name = name;
            _objectId = objectId;
            _principalId = principalId;
            _schemaId = schemaId;
            _parentObjectId = parentObjectId;
            _type = type.ToSchemaObjectType();
            _typeDesc = typeDesc;
            _createDate = createDate;
            _modifyDate = modifyDate;
            _isMsShipped = isMsShipped;
            _isPublished = isPublished;
            _isSchemaPublished = isSchemaPublished;
            _isReplicated = isReplicated;
            _hasReplicationFilter = hasReplicationFilter;
            _hasOpaqueMetadata = hasOpaqueMetadata;
            _hasUncheckedAssemblyData = hasUncheckedAssemblyData;
            _withCheckOption = withCheckOption;
            _isDateCorrelationView = isDateCorrelationView;
            _isTrackedByCdc = isTrackedByCdc;
            _hasSnapshot = hasSnapshot;
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

        public bool IsReplicated => _isReplicated;

        public bool HasReplicationFilter => _hasReplicationFilter;

        public bool HasOpaqueMetadata => _hasOpaqueMetadata;

        public bool HasUncheckedAssemblyData => _hasUncheckedAssemblyData;

        public bool WithCheckOption => _withCheckOption;

        public bool IsDateCorrelationView => _isDateCorrelationView;

        public bool IsTrackedByCdc => _isTrackedByCdc;

        public bool HasSnapshot => _hasSnapshot;
    }

}
