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

using Harlinn.Common.Core.Net.Data.SqlClient.Types;
using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{
    public class ForeignKeyColumnsReader : DataReaderWrapper
    {
        public const string Sql = """
        SELECT [constraint_object_id]
            ,[constraint_column_id]
            ,[parent_object_id]
            ,[parent_column_id]
            ,[referenced_object_id]
            ,[referenced_column_id]
        FROM [sys].[foreign_key_columns]
        """;

        public const int ConstraintObjectIdOrdinal = 0;
        public const int ConstraintColumnIdOrdinal = 1;
        public const int ParentObjectIdOrdinal = 2;
        public const int ParentColumnIdOrdinal = 3;
        public const int ReferencedObjectIdOrdinal = 4;
        public const int ReferencedColumnIdOrdinal = 5;


        public ForeignKeyColumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true) 
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public ForeignKeyColumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public ForeignKeyColumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        public int GetConstraintObjectId()
        {
            return base.GetInt32(ConstraintObjectIdOrdinal);
        }

        public int GetConstraintColumnId()
        {
            return base.GetInt32(ConstraintColumnIdOrdinal);
        }

        public int GetParentObjectId()
        {
            return base.GetInt32(ParentObjectIdOrdinal);
        }

        public int GetParentColumnId()
        {
            return base.GetInt32(ParentColumnIdOrdinal);
        }

        public int GetReferencedObjectId()
        {
            return base.GetInt32(ReferencedObjectIdOrdinal);
        }

        public int GetReferencedColumnId()
        {
            return base.GetInt32(ReferencedColumnIdOrdinal);
        }

        public ForeignKeyColumn GetForeignKeyColumn()
        {
            ForeignKeyColumn result = new ForeignKeyColumn(GetConstraintObjectId(),
                                        GetConstraintColumnId(),
                                        GetParentObjectId(),
                                        GetParentColumnId(),
                                        GetReferencedObjectId(),
                                        GetReferencedColumnId() );
            return result;
        }

        public IReadOnlyList<ForeignKeyColumn> GetForeignKeyColumns()
        {
            List<ForeignKeyColumn> result = new List<ForeignKeyColumn>();
            while (Read())
            {
                result.Add(GetForeignKeyColumn());
            }
            return result;
        }


    }
}
