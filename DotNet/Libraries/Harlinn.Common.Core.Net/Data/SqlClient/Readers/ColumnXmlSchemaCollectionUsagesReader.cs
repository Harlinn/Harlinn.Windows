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

using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{
    public class ColumnXmlSchemaCollectionUsagesReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT scxscu.[object_id]
                  ,scxscu.[column_id]
                  ,scxscu.[xml_collection_id]
            FROM [sys].[column_xml_schema_collection_usages] scxscu
            """;

        public const int ObjectIdOrdinal = 0;
        public const int ColumnIdOrdinal = 1;
        public const int XmlCollectionIdOrdinal = 2;

        public ColumnXmlSchemaCollectionUsagesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public ColumnXmlSchemaCollectionUsagesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public ColumnXmlSchemaCollectionUsagesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        /// <summary>
        /// Reads the object_id column. (sys.column_xml_schema_collection_usages.object_id)
        /// ID of the object that contains the column (references sys.objects.object_id).
        /// </summary>
        public int GetObjectId()
        {
            return GetInt32(ObjectIdOrdinal);
        }

        /// <summary>
        /// Reads the column_id column. (sys.column_xml_schema_collection_usages.column_id)
        /// ID of the column within the object that uses the XML schema collection.
        /// </summary>
        public int GetColumnId()
        {
            return GetInt32(ColumnIdOrdinal);
        }

        /// <summary>
        /// Reads the xml_collection_id column. (sys.column_xml_schema_collection_usages.xml_collection_id)
        /// ID of the XML schema collection used by the column (references sys.xml_schema_collections.xml_collection_id). May be NULL.
        /// </summary>
        public int? GetXmlCollectionId()
        {
            return GetNullableInt32(XmlCollectionIdOrdinal);
        }

        /// <summary>
        /// Creates a <see cref="ColumnXmlSchemaCollectionUsage"/> instance populated from the current data record.
        /// </summary>
        public ColumnXmlSchemaCollectionUsage GetColumnXmlSchemaCollectionUsage()
        {
            var objectId = GetObjectId();
            var columnId = GetColumnId();
            var xmlCollectionId = GetXmlCollectionId();
            return new ColumnXmlSchemaCollectionUsage(objectId, columnId, xmlCollectionId);
        }

        /// <summary>
        /// Reads all rows from the reader and returns a list of <see cref="ColumnXmlSchemaCollectionUsage"/>.
        /// </summary>
        public IReadOnlyList<ColumnXmlSchemaCollectionUsage> GetColumnXmlSchemaCollectionUsages()
        {
            var list = new List<ColumnXmlSchemaCollectionUsage>();
            while (Read())
            {
                list.Add(GetColumnXmlSchemaCollectionUsage());
            }
            return list;
        }
    }
}