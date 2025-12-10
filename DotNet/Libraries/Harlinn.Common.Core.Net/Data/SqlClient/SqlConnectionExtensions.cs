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

using System.Data;
using System.Diagnostics.CodeAnalysis;
using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using Microsoft.Identity.Client;
using Harlinn.Common.Core.Net.Data.SqlClient.Readers;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.Common.Core.Net.Data.SqlClient
{
    public static class SqlConnectionExtensions
    {

        public static SqlCommand CreateCommand(this SqlConnection connection, string commandText, CommandType commandType = CommandType.Text)
        {
            SqlCommand command = connection.CreateCommand();
            command.CommandText = commandText;
            command.CommandType = commandType;
            return command;
        }

        public static IReadOnlyList<Types.Schema> GetSchemas(this SqlConnection connection)
        {
            using (var command = connection.CreateCommand(SchemasReader.Sql))
            {
                using (var reader = command.ExecuteReader())
                {
                    var schemasReader = new SchemasReader(reader, false);
                    return schemasReader.GetSchemas();
                }
            }
        }

        public static IReadOnlyList<Types.SchemaObject> GetSchemaObjects(this SqlConnection connection)
        {
            using (var command = connection.CreateCommand(SchemaObjectsReader.Sql))
            {
                using (var reader = command.ExecuteReader())
                {
                    var schemaObjectsReader = new SchemaObjectsReader(reader, false);
                    return schemaObjectsReader.GetSchemaObjects();
                }
            }
        }

        public static IReadOnlyList<Types.SchemaObject> GetSchemaObjects(this SqlConnection connection, int schemaId)
        {
            var sql = $"{SchemaObjectsReader.Sql} WHERE [schema_id] = @SchemaId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@SchemaId", schemaId);
                using (var reader = command.ExecuteReader())
                {
                    var schemaObjectsReader = new SchemaObjectsReader(reader, false);
                    return schemaObjectsReader.GetSchemaObjects();
                }
            }
        }

        public static IReadOnlyList<Types.SchemaObject> GetSchemaObjects(this SqlConnection connection, Schema schema)
        {
            return connection.GetSchemaObjects(schema.SchemaId);
        }

        public static IReadOnlyList<Types.Table> GetTables(this SqlConnection connection)
        {
            using (var command = connection.CreateCommand(TablesReader.Sql))
            {
                using (var reader = command.ExecuteReader())
                {
                    var tablesReader = new TablesReader(reader, false);
                    return tablesReader.GetTables();
                }
            }
        }

        public static IReadOnlyList<Types.Table> GetTables(this SqlConnection connection, int schemaId)
        {
            var sql = $"{TablesReader.Sql} WHERE [schema_id] = @SchemaId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@SchemaId", schemaId);
                using (var reader = command.ExecuteReader())
                {
                    var tablesReader = new TablesReader(reader, false);
                    return tablesReader.GetTables();
                }
            }
        }

        public static IReadOnlyList<Types.Table> GetTables(this SqlConnection connection, Schema schema)
        {
            return connection.GetTables(schema.SchemaId);
        }

        public static IReadOnlyList<Types.View> GetViews(this SqlConnection connection)
        {
            using (var command = connection.CreateCommand(ViewsReader.Sql))
            {
                using (var reader = command.ExecuteReader())
                {
                    var viewsReader = new ViewsReader(reader, false);
                    return viewsReader.GetViews();
                }
            }
        }

        public static IReadOnlyList<Types.View> GetViews(this SqlConnection connection, int schemaId)
        {
            var sql = $"{ViewsReader.Sql} WHERE [schema_id] = @SchemaId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@SchemaId", schemaId);
                using (var reader = command.ExecuteReader())
                {
                    var viewsReader = new ViewsReader(reader, false);
                    return viewsReader.GetViews();
                }
            }
        }

        public static IReadOnlyList<Types.View> GetViews(this SqlConnection connection, Schema schema)
        {
            return connection.GetViews(schema.SchemaId);
        }

        public static IReadOnlyList<Types.ForeignKey> GetForeignKeys(this SqlConnection connection)
        {
            using (var command = connection.CreateCommand(ForeignKeyReader.Sql))
            {
                using (var reader = command.ExecuteReader())
                {
                    var foreignKeyReader = new ForeignKeyReader(reader, false);
                    return foreignKeyReader.GetForeignKeys();
                }
            }
        }

        public static IReadOnlyList<Types.ForeignKey> GetForeignKeys(this SqlConnection connection, int parentObjectId)
        {
            var sql = $"{ForeignKeyReader.Sql} WHERE [parent_object_id] = @ParentObjectId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ParentObjectId", parentObjectId);
                using (var reader = command.ExecuteReader())
                {
                    var foreignKeyReader = new ForeignKeyReader(reader, false);
                    return foreignKeyReader.GetForeignKeys();
                }
            } 
        }


        public static IReadOnlyList<Types.ForeignKey> GetForeignKeys(this SqlConnection connection, Types.Table table)
        {
            return connection.GetForeignKeys(table.ObjectId);
        }

        public static IReadOnlyList<Types.ForeignKeyColumn> GetForeignKeyColumns(this SqlConnection connection, int parentObjectId, int objectId)
        {
            var sql = $"{ForeignKeyColumnsReader.Sql} WHERE [parent_object_id] = @ParentObjectId AND [constraint_object_id] = @ObjectId ORDER BY [constraint_column_id]";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ParentObjectId", parentObjectId);
                command.Parameters.AddWithValue("@ObjectId", objectId);
                using (var reader = command.ExecuteReader())
                {
                    var foreignKeyColumnsReader = new ForeignKeyColumnsReader(reader, false);
                    return foreignKeyColumnsReader.GetForeignKeyColumns();
                }
            }
        }

        public static IReadOnlyList<Types.ForeignKeyColumn> GetForeignKeyColumns(this SqlConnection connection, ForeignKey foreignKey)
        {
            return connection.GetForeignKeyColumns(foreignKey.ParentObjectId, foreignKey.ObjectId);
        }

        public static IReadOnlyList<Column> GetColumns(this SqlConnection connection, int objectId)
        {
            var sql = $"{ColumnsReader.Sql} WHERE [object_id] = @ObjectId ORDER BY [column_id]";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ObjectId", objectId);
                using (var reader = command.ExecuteReader())
                {
                    var columnsReader = new ColumnsReader(reader, false);
                    return columnsReader.GetColumns();
                }
            }
        }

        public static IReadOnlyList<Column> GetColumns(this SqlConnection connection, Table table)
        {
            return connection.GetColumns(table.ObjectId);
        }

        public static IReadOnlyList<Column> GetColumns(this SqlConnection connection, View view)
        {
            return connection.GetColumns(view.ObjectId);
        }

        public static IReadOnlyList<Types.Index> GetIndexes(this SqlConnection connection, int objectId)
        {
            var sql = $"{IndexesReader.Sql} WHERE [object_id] = @ObjectId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ObjectId", objectId);
                using (var reader = command.ExecuteReader())
                {
                    var indexesReader = new IndexesReader(reader, false);
                    return indexesReader.GetIndexes();
                }
            }
        }

        public static IReadOnlyList<Types.Index> GetIndexes(this SqlConnection connection, Table table)
        {
            return connection.GetIndexes(table.ObjectId);
        }

        public static Types.Index GetPrimaryKey(this SqlConnection connection, int objectId)
        {
            var sql = $"{IndexesReader.Sql} WHERE [object_id] = @ObjectId AND [is_primary_key] = 1";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ObjectId", objectId);
                using (var reader = command.ExecuteReader())
                {
                    var indexesReader = new IndexesReader(reader, false);
                    if (indexesReader.Read())
                    {
                        return indexesReader.GetIndex();
                    }
                    else
                    {
                        throw new InvalidOperationException($"No primary key found for object id {objectId}");
                    }
                }
            }
        }

        public static Types.Index GetPrimaryKey(this SqlConnection connection, Table table)
        {
            return connection.GetPrimaryKey(table.ObjectId);
        }


        public static IReadOnlyList<Types.IndexColumn> GetIndexColumns(this SqlConnection connection, int objectId, int indexId)
        {
            var sql = $"{IndexColumnsReader.Sql} WHERE [object_id] = @ObjectId AND [index_id] = @IndexId ORDER BY [key_ordinal]";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ObjectId", objectId);
                command.Parameters.AddWithValue("@IndexId", indexId);
                using (var reader = command.ExecuteReader())
                {
                    var indexColumnsReader = new IndexColumnsReader(reader, false);
                    return indexColumnsReader.GetIndexColumns();
                }
            }
        }

       public static IReadOnlyList<Types.IndexColumn> GetIndexColumns(this SqlConnection connection, Types.Index index)
       {
           return connection.GetIndexColumns(index.ObjectId, index.IndexId);
       }

    }

}
