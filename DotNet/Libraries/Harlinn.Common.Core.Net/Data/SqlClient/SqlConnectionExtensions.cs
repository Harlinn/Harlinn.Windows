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

        /// <summary>
        /// Retrieves all schemas in the database.
        /// </summary>
        /// <param name="connection">The SQL connection.</param>
        /// <returns>A read-only list of schemas.</returns>
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

        /// <summary>
        /// Retrieves a schema by its schema ID.
        /// </summary>
        /// <param name="connection">The SQL connection.</param>
        /// <param name="schemaId">The schema ID.</param>
        /// <returns>The schema, or null if not found.</returns>
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

        /// <summary>
        /// Retrieves a schema by its name.
        /// </summary>
        /// <param name="connection">The SQL connection.</param>
        /// <param name="schemaName">The schema name.</param>
        /// <returns>The schema, or null if not found.</returns>
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

        /// <summary>
        /// Retrieves all schema objects in the database.
        /// </summary>
        /// <param name="connection">The SQL connection.</param>
        /// <returns>A read-only list of schema objects.</returns>
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

        /// <summary>
        /// Retrieves a read-only list of schema objects associated with the specified schema ID from the connected SQL
        /// Server database.
        /// </summary>
        /// <param name="connection">The open <see cref="SqlConnection"/> to use for querying schema objects. The connection must not be null and
        /// must be open.</param>
        /// <param name="schemaId">The identifier of the schema whose objects are to be retrieved.</param>
        /// <returns>A read-only list of <see cref="SchemaObject"/> instances representing the objects in the specified schema.
        /// The list is empty if no objects are found.</returns>
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

        /// <summary>
        /// Retrieves a schema object by its schema ID and object ID.
        /// </summary>
        /// <param name="connection">The SQL connection.</param>
        /// <param name="schemaId">The schema ID.</param>
        /// <param name="objectId">The object ID.</param>
        /// <returns>The schema object, or null if not found.</returns>
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

        /// <summary>
        /// Retrieves a schema object from the database by schema ID and object name.
        /// </summary>
        /// <remarks>The connection must be open before calling this method. The search is case-sensitive
        /// and limited to objects within the specified schema.</remarks>
        /// <param name="connection">The open <see cref="SqlConnection"/> to use for querying the database. Must not be null.</param>
        /// <param name="schemaId">The identifier of the schema containing the object to retrieve.</param>
        /// <param name="objectName">The name of the schema object to retrieve. Cannot be null.</param>
        /// <returns>A <see cref="SchemaObject"/> representing the requested schema object if found; otherwise, <see
        /// langword="null"/>.</returns>
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

        /// <summary>
        /// Retrieves all tables in the database.
        /// </summary>
        /// <param name="connection">The SQL connection.</param>
        /// <returns>A read-only list of tables in the database.</returns>
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

        /// <summary>
        /// Retrieves a read-only list of tables from the specified SQL connection that belong to the given schema.
        /// </summary>
        /// <param name="connection">The <see cref="SqlConnection"/> to use for querying the database. Must not be null and must be open.</param>
        /// <param name="schemaId">The identifier of the schema whose tables are to be retrieved.</param>
        /// <returns>A read-only list of <see cref="Types.Table"/> objects representing the tables in the specified schema. The
        /// list is empty if no tables are found.</returns>
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


        /// <summary>
        /// Retrieves a read-only list of tables associated with the specified schema from the connected SQL Server database.
        /// </summary>
        /// <param name="connection">The <see cref="SqlConnection"/> to use for querying the database. Must not be null and must be open.</param>
        /// <param name="schema">The <see cref="Schema"/> whose tables are to be retrieved.</param>
        /// <returns>A read-only list of <see cref="Types.Table"/> objects representing the tables in the specified schema. The
        /// list is empty if no tables are found.</returns>
        public static IReadOnlyList<Types.Table> GetTables(this SqlConnection connection, Schema schema)
        {
            return connection.GetTables(schema.SchemaId);
        }

        /// <summary>
        /// Retrieves a table by its schema ID and object ID.
        /// </summary>
        /// <param name="connection">The <see cref="SqlConnection"/> to use for querying the database. Must not be null and must be open.</param>
        /// <param name="schemaId">The identifier of the schema to which the table belongs.</param>
        /// <param name="objectId">The identifier of the table to retrieve.</param>
        /// <returns>A <see cref="Types.Table"/> object representing the table, or null if not found.</returns>
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

        /// <summary>
        /// Retrieves a table by its schema and object ID.
        /// </summary>
        /// <param name="connection">The <see cref="SqlConnection"/> to use for querying the database. Must not be null and must be open.</param>
        /// <param name="schema">The <see cref="Schema"/> to which the table belongs.</param>
        /// <param name="objectId">The identifier of the table to retrieve.</param>
        /// <returns>A <see cref="Types.Table"/> object representing the table, or null if not found.</returns>
        public static Types.Table? GetTable(this SqlConnection connection, Types.Schema schema, int objectId)
        {     
            return connection.GetTable(schema.SchemaId, objectId); 
        }

        /// <summary>
        /// Retrieves a table definition from the database by schema ID and object name.
        /// </summary>
        /// <remarks>The method searches for a table with the specified schema ID and name. The connection
        /// must be open before calling this method.</remarks>
        /// <param name="connection">The open <see cref="SqlConnection"/> to use for querying the database. The connection must not be null.</param>
        /// <param name="schemaId">The identifier of the schema that contains the table.</param>
        /// <param name="objectName">The name of the table to retrieve. Cannot be null.</param>
        /// <returns>A <see cref="Types.Table"/> object representing the table if found; otherwise, <see langword="null"/>.</returns>
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

        /// <summary>
        /// Retrieves a table definition from the specified schema by object name using the provided SQL connection.
        /// </summary>
        /// <param name="connection">The open <see cref="SqlConnection"/> to use for retrieving the table definition. Must not be null.</param>
        /// <param name="schema">The schema that contains the table to retrieve. Must not be null.</param>
        /// <param name="objectName">The name of the table to retrieve from the specified schema. Cannot be null or empty.</param>
        /// <returns>A <see cref="Types.Table"/> object representing the table if found; otherwise, <see langword="null"/>.</returns>
        public static Types.Table? GetTable(this SqlConnection connection, Types.Schema schema, string objectName)
        {
            return connection.GetTable(schema.SchemaId, objectName);
        }


        /// <summary>
        /// Retrieves all views in the database.
        /// </summary>
        /// <param name="connection">The open <see cref="SqlConnection"/> to use for querying the database. Must not be null.</param>
        /// <returns>A read-only list of <see cref="Types.View"/> objects representing the views in the database.</returns>
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

        /// <summary>
        /// Retrieves a read-only list of views defined in the specified schema from the connected SQL Server database.
        /// </summary>
        /// <param name="connection">The <see cref="SqlConnection"/> to use for querying the database. The connection must not be null and
        /// must be open.</param>
        /// <param name="schemaId">The identifier of the schema whose views are to be retrieved.</param>
        /// <returns>A read-only list of <see cref="Types.View"/> objects representing the views in the specified schema. The
        /// list is empty if no views are found.</returns>
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

        /// <summary>
        /// Retrieves a read-only list of views defined in the specified database schema.
        /// </summary>
        /// <param name="connection">The open <see cref="SqlConnection"/> to the database from which to retrieve views. Must not be null.</param>
        /// <param name="schema">The schema for which to retrieve views. Must not be null.</param>
        /// <returns>A read-only list of <see cref="Types.View"/> objects representing the views in the specified schema. The
        /// list is empty if no views are found.</returns>
        public static IReadOnlyList<Types.View> GetViews(this SqlConnection connection, Schema schema)
        {
            return connection.GetViews(schema.SchemaId);
        }

        /// <summary>
        /// Retrieves a view definition from the database by schema and view identifiers.
        /// </summary>
        /// <remarks>The connection must be open when this method is called. The method does not modify
        /// the state of the connection.</remarks>
        /// <param name="connection">The open <see cref="SqlConnection"/> to use for querying the database. Must not be null.</param>
        /// <param name="schemaId">The identifier of the schema that contains the view.</param>
        /// <param name="viewId">The object identifier of the view to retrieve.</param>
        /// <returns>A <see cref="Types.View"/> instance representing the view if found; otherwise, <see langword="null"/>.</returns>
        public static Types.View? GetView(this SqlConnection connection, int schemaId, int viewId)
        {
            var sql = $"{ViewsReader.Sql} WHERE [schema_id] = @SchemaId AND [object_id] = @ViewId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@SchemaId", schemaId);
                command.Parameters.AddWithValue("@ViewId", viewId);
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

        /// <summary>
        /// Retrieves a view definition from the database by schema ID and view name.
        /// </summary>
        /// <param name="connection">The open <see cref="SqlConnection"/> to use for querying the database. Must not be null.</param>
        /// <param name="schemaId">The identifier of the schema that contains the view.</param>
        /// <param name="viewName">The name of the view to retrieve.</param>
        /// <returns>A <see cref="Types.View"/> instance representing the view if found; otherwise, <see langword="null"/>.</returns>
        public static Types.View? GetView(this SqlConnection connection, int schemaId, string viewName)
        {
            var sql = $"{ViewsReader.Sql} WHERE [schema_id] = @SchemaId AND [name] = @ViewName";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@SchemaId", schemaId);
                command.Parameters.AddWithValue("@ViewName", viewName);
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

        /// <summary>
        /// Retrieves all foreign keys in the database.
        /// </summary>
        /// <param name="connection">The open <see cref="SqlConnection"/> to use for querying the database. Must not be null.</param>
        /// <returns>A read-only list of <see cref="Types.ForeignKey"/> instances representing the foreign keys in the database.</returns>
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

        /// <summary>
        /// Retrieves a read-only list of foreign keys associated with the specified table ID from the connected SQL Server database.
        /// </summary>
        /// <param name="connection">The open <see cref="SqlConnection"/> to use for querying the database. Must not be null.</param>
        /// <param name="tableId">The identifier of the parent object to retrieve foreign keys for.</param>
        /// <returns>A read-only list of <see cref="Types.ForeignKey"/> instances representing the foreign keys associated with the specified table ID.</returns>
        public static IReadOnlyList<Types.ForeignKey> GetForeignKeys(this SqlConnection connection, int tableId)
        {
            var sql = $"{ForeignKeyReader.Sql} WHERE fk.[parent_object_id] = @ParentObjectId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ParentObjectId", tableId);
                using (var reader = command.ExecuteReader())
                {
                    var foreignKeyReader = new ForeignKeyReader(reader, false);
                    return foreignKeyReader.GetForeignKeys();
                }
            } 
        }

        /// <summary>
        /// Retrieves a read-only list of foreign keys associated with the specified table from the connected SQL Server database.
        /// </summary>
        /// <param name="connection">The open <see cref="SqlConnection"/> to use for querying the database. Must not be null.</param>
        /// <param name="table">The table to retrieve foreign keys for.</param>
        /// <returns>A read-only list of <see cref="Types.ForeignKey"/> instances representing the foreign keys associated with the specified table.</returns>
        public static IReadOnlyList<Types.ForeignKey> GetForeignKeys(this SqlConnection connection, Types.Table table)
        {
            return connection.GetForeignKeys(table.ObjectId);
        }

        /// <summary>
        /// Retrieves the columns that participate in a specified foreign key constraint from the connected SQL Server
        /// database.
        /// </summary>
        /// <remarks>The connection must be open before calling this method. The returned columns are
        /// ordered by their ordinal position within the foreign key constraint.</remarks>
        /// <param name="connection">The open <see cref="SqlConnection"/> to the SQL Server database from which to retrieve foreign key column
        /// information.</param>
        /// <param name="parentObjectId">The object ID of the parent table that contains the foreign key constraint.</param>
        /// <param name="foreignKeyId">The object ID of the foreign key constraint whose columns are to be retrieved.</param>
        /// <returns>A read-only list of <see cref="Types.ForeignKeyColumn"/> objects representing the columns involved in the
        /// specified foreign key constraint. The list is empty if no matching columns are found.</returns>
        public static IReadOnlyList<Types.ForeignKeyColumn> GetForeignKeyColumns(this SqlConnection connection, int parentObjectId, int foreignKeyId)
        {
            var sql = $"{ForeignKeyColumnsReader.Sql} WHERE fkc.[parent_object_id] = @ParentObjectId AND fkc.[constraint_object_id] = @ForeignKeyId ORDER BY fkc.[constraint_column_id]";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ParentObjectId", parentObjectId);
                command.Parameters.AddWithValue("@ForeignKeyId", foreignKeyId);
                using (var reader = command.ExecuteReader())
                {
                    var foreignKeyColumnsReader = new ForeignKeyColumnsReader(reader, false);
                    return foreignKeyColumnsReader.GetForeignKeyColumns();
                }
            }
        }

        /// <summary>
        /// Retrieves the columns that participate in the specified foreign key constraint from the connected SQL Server
        /// database.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for retrieving foreign key column information.</param>
        /// <param name="foreignKey">The foreign key constraint for which to retrieve the participating columns. Cannot be null.</param>
        /// <returns>A read-only list of columns that are part of the specified foreign key constraint. The list is empty if the
        /// foreign key has no columns.</returns>
        public static IReadOnlyList<Types.ForeignKeyColumn> GetForeignKeyColumns(this SqlConnection connection, ForeignKey foreignKey)
        {
            return connection.GetForeignKeyColumns(foreignKey.ParentObjectId, foreignKey.ObjectId);
        }

        /// <summary>
        /// Retrieves all columns for a specified database object.
        /// </summary>
        /// <param name="connection">The open <see cref="SqlConnection"/> to the SQL Server database from which to retrieve column information.</param>
        /// <param name="objectId">The object ID of the database object for which to retrieve columns.</param>
        /// <returns>A read-only list of <see cref="Column"/> objects representing the columns of the specified database object. The list is empty if no columns are found.</returns>
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

        /// <summary>
        /// Retrieves metadata for a specific column in a database object by object and column identifiers.
        /// </summary>
        /// <remarks>The method queries the system catalog to locate the column by its object and column
        /// IDs. The connection must remain open for the duration of the call.</remarks>
        /// <param name="connection">The open <see cref="SqlConnection"/> to use for querying column metadata. Cannot be null and must be open.</param>
        /// <param name="objectId">The object ID of the database object (such as a table or view) containing the column.</param>
        /// <param name="columnId">The column ID within the specified object to retrieve metadata for.</param>
        /// <returns>A <see cref="Column"/> instance containing metadata for the specified column if found; otherwise, <see
        /// langword="null"/>.</returns>
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

        /// <summary>
        /// Retrieves all columns for the specified table.
        /// </summary>
        /// <param name="connection">The open <see cref="SqlConnection"/> to the SQL Server database from which to retrieve column information.</param>
        /// <param name="table">The <see cref="Table"/> object representing the table for which to retrieve columns.</param>
        /// <returns>A read-only list of <see cref="Column"/> objects representing the columns of the specified table. The list is empty if no columns are found.</returns>
        public static IReadOnlyList<Column> GetColumns(this SqlConnection connection, Table table)
        {
            return connection.GetColumns(table.ObjectId);
        }

        /// <summary>
        /// Retrieves a read-only list of columns defined in the specified database view.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for retrieving column metadata. Must not be null.</param>
        /// <param name="view">The view for which to retrieve column definitions. Must not be null.</param>
        /// <returns>A read-only list of <see cref="Column"/> objects representing the columns in the specified view. The list
        /// will be empty if the view contains no columns.</returns>
        public static IReadOnlyList<Column> GetColumns(this SqlConnection connection, View view)
        {
            return connection.GetColumns(view.ObjectId);
        }

        /// <summary>
        /// Retrieves all identity columns for a specified database object.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for retrieving identity column metadata. Must not be null.</param>
        /// <param name="objectId">The ID of the database object for which to retrieve identity columns.</param>
        /// <returns>A read-only list of <see cref="IdentityColumn"/> objects representing the identity columns of the specified database object. The list is empty if no identity columns are found.</returns>
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

        /// <summary>
        /// Retrieves the identity column information for the specified object and column from the connected SQL Server
        /// database.
        /// </summary>
        /// <param name="connection">The open <see cref="SqlConnection"/> to use for querying the database. Must not be null and must be open.</param>
        /// <param name="objectId">The object ID of the table or view containing the column.</param>
        /// <param name="columnId">The column ID of the identity column to retrieve.</param>
        /// <returns>An <see cref="IdentityColumn"/> object containing information about the identity column if found; otherwise,
        /// <see langword="null"/>.</returns>
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

        /// <summary>
        /// Retrieves the identity column information for the specified column in the database.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for retrieving identity column information.</param>
        /// <param name="column">The column for which to retrieve identity column details.</param>
        /// <returns>An <see cref="IdentityColumn"/> object containing identity information for the specified column, or <see
        /// langword="null"/> if the column is not an identity column.</returns>
        public static IdentityColumn? GetIdentityColumn(this SqlConnection connection, Column column)
        {
            return connection.GetIdentityColumn(column.ObjectId, column.ColumnId);
        }

        /// <summary>
        /// Retrieves all computed columns for a specified database object.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for retrieving computed column information.</param>
        /// <param name="objectId">The object ID of the table or view containing the computed columns.</param>
        /// <returns>A read-only list of <see cref="ComputedColumn"/> objects containing information about the computed columns.</returns>
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

        /// <summary>
        /// Retrieves the computed column information for the specified object and column from the connected SQL Server
        /// </summary>
        /// <param name="connection">The open SQL connection to use for retrieving computed column information.</param>
        /// <param name="objectId">The object ID of the table or view containing the computed column.</param>
        /// <param name="columnId">The column ID of the computed column.</param>
        /// <returns>A <see cref="ComputedColumn"/> object containing information about the computed column, or <see langword="null"/> if the column is not a computed column.</returns>
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

        /// <summary>
        /// Retrieves the computed column definition for the specified column in the connected SQL Server database.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for retrieving the computed column information.</param>
        /// <param name="column">The column for which to retrieve the computed column definition. Must not be null.</param>
        /// <returns>A <see cref="ComputedColumn"/> object representing the computed column definition if the specified column is
        /// computed; otherwise, <see langword="null"/>.</returns>
        public static ComputedColumn? GetComputedColumn(this SqlConnection connection, Column column)
        {
            return connection.GetComputedColumn(column.ObjectId, column.ColumnId);
        }

        /// <summary>
        /// Retrieves the default constraint for a specified column in a database object.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for retrieving the default constraint information.</param>
        /// <param name="parentObjectId">The object ID of the table or view containing the column.</param>
        /// <param name="columnId">The column ID of the column for which to retrieve the default constraint.</param>
        /// <returns>A <see cref="DefaultConstraint"/> object containing information about the default constraint, or <see langword="null"/> if the column has no default constraint.</returns>
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

        /// <summary>
        /// Retrieves the default constraint defined for the specified column in the connected SQL Server database.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for querying the database. Must not be null.</param>
        /// <param name="column">The column for which to retrieve the default constraint. Must not be null.</param>
        /// <returns>A <see cref="DefaultConstraint"/> object representing the default constraint for the specified column, or
        /// <see langword="null"/> if no default constraint is defined.</returns>
        public static DefaultConstraint? GetDefaultConstraint(this SqlConnection connection, Column column)
        {
            return connection.GetDefaultConstraint(column.ObjectId, column.ColumnId);
        }

        /// <summary>
        /// Retrieves all indexes for a specified database object.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for querying the database. Must not be null.</param>
        /// <param name="objectId">The object ID of the table or view for which to retrieve indexes.</param>
        /// <returns>A read-only list of <see cref="Types.Index"/> objects representing the indexes for the specified database object.</returns>
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
        /// <summary>
        /// Retrieves the collection of indexes defined on the specified table.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for retrieving indexes. Must not be null.</param>
        /// <param name="table">The table for which to retrieve indexes. Must not be null.</param>
        /// <returns>A read-only list of indexes defined on the specified table. The list is empty if the table has no indexes.</returns>
        public static IReadOnlyList<Types.Index> GetIndexes(this SqlConnection connection, Table table)
        {
            return connection.GetIndexes(table.ObjectId);
        }
        /// <summary>
        /// Retrieves all index columns for a specified index on a database object.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for querying the database. Must not be null.</param>
        /// <param name="objectId">The object ID of the table or view for which to retrieve index columns.</param>
        /// <param name="indexId">The index ID for which to retrieve columns.</param>
        /// <returns>A read-only list of <see cref="IndexColumn"/> objects representing the index columns for the specified index.</returns>
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

        /// <summary>
        /// Retrieves the columns that are part of the specified index in the connected SQL Server database.
        /// </summary>
        /// <param name="connection">The open <see cref="SqlConnection"/> to the SQL Server database from which to retrieve index column
        /// information.</param>
        /// <param name="index">The index for which to retrieve the associated columns. Must not be null.</param>
        /// <returns>A read-only list of <see cref="IndexColumn"/> objects representing the columns included in the specified
        /// index. The list is empty if the index has no columns.</returns>
        public static IReadOnlyList<IndexColumn> GetIndexColumns(this SqlConnection connection, Types.Index index)
        {
            return connection.GetIndexColumns(index.ObjectId, index.IndexId);
        }


        /// <summary>
        /// Retrieves all check constraints for a specified database object.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for querying the database. Must not be null.</param>
        /// <param name="objectId">The object ID of the table or view for which to retrieve check constraints.</param>
        /// <returns>A read-only list of <see cref="Types.CheckConstraint"/> objects representing the check constraints for the specified database object.</returns>
        public static IReadOnlyList<Types.CheckConstraint> GetCheckConstraints(this SqlConnection connection, int objectId)
        {
            var sql = $"{CheckConstraintsReader.Sql} WHERE cc.[parent_object_id] = @ObjectId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ObjectId", objectId);
                using (var reader = command.ExecuteReader())
                {
                    var checkConstraintsReader = new CheckConstraintsReader(reader, false);
                    return checkConstraintsReader.GetCheckConstraints();
                }
            }
        }

        /// <summary>
        /// Retrieves the collection of check constraints defined on the specified table.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for retrieving check constraints.</param>
        /// <param name="table">The table for which to retrieve check constraints. Cannot be null.</param>
        /// <returns>A read-only list of check constraints defined on the specified table. The list is empty if the table has no
        /// check constraints.</returns>
        public static IReadOnlyList<Types.CheckConstraint> GetCheckConstraints(this SqlConnection connection, Table table)
        {
            return connection.GetCheckConstraints(table.ObjectId);
        }

        /// <summary>
        /// Retrieves all check constraints defined directly on the specified table (excluding column-level constraints).
        /// </summary>
        /// <param name="connection">The open SQL connection to use for querying the database. Must not be null.</param>
        /// <param name="objectId">The object ID of the table for which to retrieve check constraints.</param>
        /// <returns>A read-only list of <see cref="Types.CheckConstraint"/> objects representing the check constraints defined directly on the specified table.</returns>
        public static IReadOnlyList<Types.CheckConstraint> GetTableCheckConstraints(this SqlConnection connection, int objectId)
        {
            var sql = $"{CheckConstraintsReader.Sql} WHERE cc.[parent_object_id] = @ObjectId AND cc.[parent_column_id] = 0";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ObjectId", objectId);
                using (var reader = command.ExecuteReader())
                {
                    var checkConstraintsReader = new CheckConstraintsReader(reader, false);
                    return checkConstraintsReader.GetCheckConstraints();
                }
            }
        }

        /// <summary>
        /// Retrieves the collection of check constraints defined on the specified table (excluding column-level constraints).
        /// </summary>
        /// <param name="connection">The open SQL connection to use for retrieving check constraints.</param>
        /// <param name="table">The table for which to retrieve check constraints.</param>
        /// <returns>A read-only list of check constraints associated with the specified table. The list is empty if the table
        /// has no check constraints.</returns>
        public static IReadOnlyList<Types.CheckConstraint> GetTableCheckConstraints(this SqlConnection connection, Table table)
        {
            return connection.GetTableCheckConstraints(table.ObjectId);
        }


        /// <summary>
        /// Retrieves the check constraints defined on a specific column of a database object.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for querying check constraints. Cannot be null.</param>
        /// <param name="objectId">The object ID of the parent database object (such as a table) containing the column.</param>
        /// <param name="columnId">The column ID within the specified object for which to retrieve check constraints.</param>
        /// <returns>A read-only list of check constraints associated with the specified column. The list is empty if no check
        /// constraints are defined for the column.</returns>
        public static IReadOnlyList<Types.CheckConstraint> GetCheckConstraints(this SqlConnection connection, int objectId, int columnId)
        {
            var sql = $"{CheckConstraintsReader.Sql} WHERE cc.[parent_object_id] = @ObjectId AND cc.[parent_column_id] = @ColumnId";
            using (var command = connection.CreateCommand(sql))
            {
                command.Parameters.AddWithValue("@ObjectId", objectId);
                command.Parameters.AddWithValue("@ColumnId", columnId);
                using (var reader = command.ExecuteReader())
                {
                    var checkConstraintsReader = new CheckConstraintsReader(reader, false);
                    return checkConstraintsReader.GetCheckConstraints();
                }
            }
        }

        /// <summary>
        /// Retrieves the collection of check constraints defined on the specified column in the database.
        /// </summary>
        /// <param name="connection">The open SQL connection to use for retrieving check constraints.</param>
        /// <param name="column">The column for which to retrieve associated check constraints. Must not be null.</param>
        /// <returns>A read-only list of check constraints associated with the specified column. The list is empty if no check
        /// constraints are defined.</returns>
        public static IReadOnlyList<Types.CheckConstraint> GetCheckConstraints(this SqlConnection connection, Column column)
        {
            return connection.GetCheckConstraints(column.ObjectId, column.ColumnId);
        }

        
        /// <summary>
        /// Retrieves the primary key index for the specified database object from the connected SQL Server instance.
        /// </summary>
        /// <param name="connection">The open <see cref="SqlConnection"/> to use for querying the database. Must not be null and must be open.</param>
        /// <param name="objectId">The object ID of the database object (such as a table) for which to retrieve the primary key index.</param>
        /// <returns>The <see cref="Types.Index"/> representing the primary key of the specified object.</returns>
        /// <exception cref="InvalidOperationException">Thrown if no primary key is found for the specified <paramref name="objectId"/>.</exception>
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

        /// <summary>
        /// Retrieves the primary key index for the specified table from the database connection.
        /// </summary>
        /// <param name="connection">The SQL connection to use when retrieving the primary key information. Must be an open and valid connection.</param>
        /// <param name="table">The table for which to retrieve the primary key index. Cannot be null.</param>
        /// <returns>An Index object representing the primary key of the specified table, or null if the table does not have a
        /// primary key.</returns>
        public static Types.Index GetPrimaryKey(this SqlConnection connection, Table table)
        {
            return connection.GetPrimaryKey(table.ObjectId);
        }


        

    }

}
