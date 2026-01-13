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
    /// <summary>
    /// Represents a row from the <c>sys.column_xml_schema_collection_usages</c> catalog view.
    /// Immutable type with private readonly backing fields prefixed with '_'.
    /// </summary>
    public sealed class ColumnXmlSchemaCollectionUsage
    {
        private readonly int _objectId;
        private readonly int _columnId;
        private readonly int? _xmlCollectionId;

        /// <summary>
        /// Initializes a new instance of <see cref="ColumnXmlSchemaCollectionUsage"/>.
        /// </summary>
        public ColumnXmlSchemaCollectionUsage(int objectId, int columnId, int? xmlCollectionId)
        {
            _objectId = objectId;
            _columnId = columnId;
            _xmlCollectionId = xmlCollectionId;
        }

        /// <summary>
        /// ID of the object that contains the column. (sys.column_xml_schema_collection_usages.object_id)
        /// References the object in sys.objects that owns the column.
        /// </summary>
        public int ObjectId => _objectId;

        /// <summary>
        /// ID of the column within the object. (sys.column_xml_schema_collection_usages.column_id)
        /// Identifies the specific column that uses an XML schema collection.
        /// </summary>
        public int ColumnId => _columnId;

        /// <summary>
        /// ID of the XML schema collection used by the column. (sys.column_xml_schema_collection_usages.xml_collection_id)
        /// References the xml_collection_id in sys.xml_schema_collections; may be NULL.
        /// </summary>
        public int? XmlCollectionId => _xmlCollectionId;
    }
}