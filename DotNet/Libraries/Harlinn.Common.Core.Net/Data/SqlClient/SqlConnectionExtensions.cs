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
using Microsoft.Data.SqlClient;
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

        public static IReadOnlyList<Schema> GetSchemas(this SqlConnection connection)
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

        public static Schema? GetSchema(this SqlConnection connection, int schemaId)
        {
            var sql = $"{SchemasReader.Sql} WHERE [schema_id] = @SchemaId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@SchemaId", schemaId);
                using (var reader = command.ExecuteReader())
                {
                    var schemasReader = new SchemasReader(reader, false);
                    if (schemasReader.Read())
                    {
                        return schemasReader.GetSchema();
                    }
                    return null;
                }
            }
        }

        public static Schema? GetSchemaByName(this SqlConnection connection, string schemaName)
        {
            var sql = $"{SchemasReader.Sql} WHERE [name] = @SchemaName";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@SchemaName", schemaName);
                using (var reader = command.ExecuteReader())
                {
                    var schemasReader = new SchemasReader(reader, false);
                    if (schemasReader.Read())
                    {
                        return schemasReader.GetSchema();
                    }
                    return null;
                }
            }
        }


        public static IReadOnlyList<SchemaObject> GetSchemaObjects(this SqlConnection connection)
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

        public static IReadOnlyList<SchemaObject> GetSchemaObjects(this SqlConnection connection, int schemaId)
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

        public static SchemaObject? GetSchemaObject(this SqlConnection connection, int schemaId, int objectId)
        {
            var sql = $"{SchemaObjectsReader.Sql} WHERE [schema_id] = @SchemaId AND [object_id] = @ObjectId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@SchemaId", schemaId);
                command.Parameters.AddWithValue("@ObjectId", objectId);
                using (var reader = command.ExecuteReader())
                {
                    var schemaObjectsReader = new SchemaObjectsReader(reader, false);
                    if (schemaObjectsReader.Read())
                    {
                        return schemaObjectsReader.GetSchemaObject();
                    }
                    return null;
                }
            }
        }

        public static SchemaObject? GetSchemaObject(this SqlConnection connection, int schemaId, string objectName)
        {
            var sql = $"{SchemaObjectsReader.Sql} WHERE [schema_id] = @SchemaId AND [name] = @ObjectName";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@SchemaId", schemaId);
                command.Parameters.AddWithValue("@ObjectName", objectName);
                using (var reader = command.ExecuteReader())
                {
                    var schemaObjectsReader = new SchemaObjectsReader(reader, false);
                    if (schemaObjectsReader.Read())
                    {
                        return schemaObjectsReader.GetSchemaObject();
                    }
                    return null;
                }
            }
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

        public static Types.Table? GetTable(this SqlConnection connection, int schemaId, int objectId)
        {
            var sql = $"{TablesReader.Sql} WHERE [schema_id] = @SchemaId AND [object_id] = @ObjectId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@SchemaId", schemaId);
                command.Parameters.AddWithValue("@ObjectId", objectId);
                using (var reader = command.ExecuteReader())
                {
                    var tablesReader = new TablesReader(reader, false);
                    if (tablesReader.Read())
                    {
                        return tablesReader.GetTable();
                    }
                    return null;
                }
            }
        }

        public static Types.Table? GetTable(this SqlConnection connection, Types.Schema schema, int objectId)
        {     
            return connection.GetTable(schema.SchemaId, objectId); 
        }

        public static Types.Table? GetTable(this SqlConnection connection, int schemaId, string objectName)
        {
            var sql = $"{TablesReader.Sql} WHERE [schema_id] = @SchemaId AND [name] = @ObjectName";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@SchemaId", schemaId);
                command.Parameters.AddWithValue("@ObjectName", objectName);
                using (var reader = command.ExecuteReader())
                {
                    var tablesReader = new TablesReader(reader, false);
                    if (tablesReader.Read())
                    {
                        return tablesReader.GetTable();
                    }
                    return null;
                }
            }
        }

        public static Types.Table? GetTable(this SqlConnection connection, Types.Schema schema, string objectName)
        {
            return connection.GetTable(schema.SchemaId, objectName);
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

        public static Types.View? GetView(this SqlConnection connection, int schemaId, int objectId)
        {
            var sql = $"{ViewsReader.Sql} WHERE [schema_id] = @SchemaId AND [object_id] = @ObjectId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@SchemaId", schemaId);
                command.Parameters.AddWithValue("@ObjectId", objectId);
                using (var reader = command.ExecuteReader())
                {
                    var viewsReader = new ViewsReader(reader, false);
                    if (viewsReader.Read())
                    {
                        return viewsReader.GetView();
                    }
                    return null;
                }
            }
        }

        public static Types.View? GetView(this SqlConnection connection, int schemaId, string objectName)
        {
            var sql = $"{ViewsReader.Sql} WHERE [schema_id] = @SchemaId AND [name] = @ObjectName";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@SchemaId", schemaId);
                command.Parameters.AddWithValue("@ObjectName", objectName);
                using (var reader = command.ExecuteReader())
                {
                    var viewsReader = new ViewsReader(reader, false);
                    if (viewsReader.Read())
                    {
                        return viewsReader.GetView();
                    }
                    return null;
                }
            }
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
            var sql = $"{ForeignKeyReader.Sql} WHERE fk.[parent_object_id] = @ParentObjectId";
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
            var sql = $"{ForeignKeyColumnsReader.Sql} WHERE fkc.[parent_object_id] = @ParentObjectId AND fkc.[constraint_object_id] = @ObjectId ORDER BY fkc.[constraint_column_id]";
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

        public static Column? GetColumn(this SqlConnection connection, int objectId, int columnId)
        {
            var sql = $"{ColumnsReader.Sql} WHERE [object_id] = @ObjectId AND [column_id] = @ColumnId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ObjectId", objectId);
                command.Parameters.AddWithValue("@ColumnId", columnId);
                using (var reader = command.ExecuteReader())
                {
                    if (reader.Read())
                    {
                        var columnsReader = new ColumnsReader(reader, false);
                        return columnsReader.GetColumn();
                    }
                    return null;
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

        public static IReadOnlyList<IdentityColumn> GetIdentityColumns(this SqlConnection connection, int objectId)
        {
            var sql = $"{IdentityColumnsReader.Sql} WHERE [object_id] = @ObjectId ORDER BY [column_id]";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ObjectId", objectId);
                using (var reader = command.ExecuteReader())
                {
                    var columnsReader = new IdentityColumnsReader(reader, false);
                    return columnsReader.GetIdentityColumns();
                }
            }
        }

        public static IdentityColumn? GetIdentityColumn(this SqlConnection connection, int objectId, int columnId)
        {
            var sql = $"{IdentityColumnsReader.Sql} WHERE [object_id] = @ObjectId AND [column_id] = @ColumnId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ObjectId", objectId);
                command.Parameters.AddWithValue("@ColumnId", columnId);
                using (var reader = command.ExecuteReader())
                {
                    if (reader.Read())
                    {
                        var columnsReader = new IdentityColumnsReader(reader, false);
                        return columnsReader.GetIdentityColumn();
                    }
                    return null;
                }
            }
        }

        public static IdentityColumn? GetIdentityColumn(this SqlConnection connection, Column column)
        {
            return connection.GetIdentityColumn(column.ObjectId, column.ColumnId);
        }

        public static IReadOnlyList<ComputedColumn> GetComputedColumns(this SqlConnection connection, int objectId)
        {
            var sql = $"{ComputedColumnsReader.Sql} WHERE [object_id] = @ObjectId ORDER BY [column_id]";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ObjectId", objectId);
                using (var reader = command.ExecuteReader())
                {
                    var columnsReader = new ComputedColumnsReader(reader, false);
                    return columnsReader.GetComputedColumns();
                }
            }
        }

        public static ComputedColumn? GetComputedColumn(this SqlConnection connection, int objectId, int columnId)
        {
            var sql = $"{ComputedColumnsReader.Sql} WHERE [object_id] = @ObjectId AND [column_id] = @ColumnId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ObjectId", objectId);
                command.Parameters.AddWithValue("@ColumnId", columnId);
                using (var reader = command.ExecuteReader())
                {
                    if (reader.Read())
                    {
                        var columnsReader = new ComputedColumnsReader(reader, false);
                        return columnsReader.GetComputedColumn();
                    }
                    return null;
                }
            }
        }

        public static ComputedColumn? GetComputedColumn(this SqlConnection connection, Column column)
        {
            return connection.GetComputedColumn(column.ObjectId, column.ColumnId);
        }

        public static DefaultConstraint? GetDefaultConstraint(this SqlConnection connection, int parentObjectId, int columnId)
        {
            var sql = $"{DefaultConstraintsReader.Sql} WHERE [parent_object_id] = @ParentObjectId AND [parent_column_id] = @ColumnId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ParentObjectId", parentObjectId);
                command.Parameters.AddWithValue("@ColumnId", columnId);
                using (var reader = command.ExecuteReader())
                {
                    if (reader.Read())
                    {
                        var columnsReader = new DefaultConstraintsReader(reader, false);
                        return columnsReader.GetDefaultConstraint();
                    }
                    return null;
                }
            }
        }

        public static DefaultConstraint? GetDefaultConstraint(this SqlConnection connection, Column column)
        {
            return connection.GetDefaultConstraint(column.ObjectId, column.ColumnId);
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


        public static IReadOnlyList<IndexColumn> GetIndexColumns(this SqlConnection connection, int objectId, int indexId)
        {
            var sql = $"{IndexColumnsReader.Sql} WHERE ic.[object_id] = @ObjectId AND ic.[index_id] = @IndexId ORDER BY [key_ordinal]";
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

       public static IReadOnlyList<IndexColumn> GetIndexColumns(this SqlConnection connection, Types.Index index)
       {
           return connection.GetIndexColumns(index.ObjectId, index.IndexId);
       }

    }

}
