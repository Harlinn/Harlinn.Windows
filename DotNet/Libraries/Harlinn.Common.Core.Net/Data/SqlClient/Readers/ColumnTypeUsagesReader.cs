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
    public class ColumnTypeUsagesReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT sctu.[object_id]
                  ,sctu.[column_id]
                  ,sctu.[user_type_id]
            FROM [sys].[column_type_usages] sctu
            """;

        public const int ObjectIdOrdinal = 0;
        public const int ColumnIdOrdinal = 1;
        public const int UserTypeIdOrdinal = 2;

        public ColumnTypeUsagesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public ColumnTypeUsagesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public ColumnTypeUsagesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        /// <summary>
        /// Reads the object_id column. (sys.column_type_usages.object_id)
        /// ID of the object that contains the column (references sys.objects.object_id).
        /// </summary>
        public int GetObjectId()
        {
            return GetInt32(ObjectIdOrdinal);
        }

        /// <summary>
        /// Reads the column_id column. (sys.column_type_usages.column_id)
        /// ID of the column within the object that uses the type.
        /// </summary>
        public int GetColumnId()
        {
            return GetInt32(ColumnIdOrdinal);
        }

        /// <summary>
        /// Reads the user_type_id column. (sys.column_type_usages.user_type_id)
        /// ID of the user-defined type used by the column (references sys.types.user_type_id).
        /// </summary>
        public int GetUserTypeId()
        {
            return GetInt32(UserTypeIdOrdinal);
        }

        /// <summary>
        /// Creates a <see cref="ColumnTypeUsage"/> instance populated from the current data record.
        /// </summary>
        public ColumnTypeUsage GetColumnTypeUsage()
        {
            var objectId = GetObjectId();
            var columnId = GetColumnId();
            var userTypeId = GetUserTypeId();
            return new ColumnTypeUsage(objectId, columnId, userTypeId);
        }

        /// <summary>
        /// Reads all rows from the reader and returns a list of <see cref="ColumnTypeUsage"/>.
        /// </summary>
        public IReadOnlyList<ColumnTypeUsage> GetColumnTypeUsages()
        {
            var list = new List<ColumnTypeUsage>();
            while (Read())
            {
                list.Add(GetColumnTypeUsage());
            }
            return list;
        }
    }
}