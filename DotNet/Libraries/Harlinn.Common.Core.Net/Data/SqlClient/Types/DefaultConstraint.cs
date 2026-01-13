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
    public class DefaultConstraint : SchemaObject
    {
        readonly int _parentColumnId;
        readonly string _definition;
        readonly bool _isSystemNamed;
        public DefaultConstraint(string name, int objectId, int? principalId, int schemaId, int parentObjectId, string type, string typeDesc, DateTime createDate, DateTime modifyDate, bool isMsShipped, bool isPublished, bool isSchemaPublished, int parentColumnId, string definition, bool isSystemNamed)
            : base(name, objectId, principalId, schemaId, parentObjectId, type, typeDesc, createDate, modifyDate, isMsShipped, isPublished, isSchemaPublished)
        {
            _parentColumnId = parentColumnId;
            _definition = definition;
            _isSystemNamed = isSystemNamed;
        }
        public int ParentColumnId => _parentColumnId;
        public string Definition => _definition;

        public bool IsSystemNamed => _isSystemNamed;
    }

}
