# `SqlConnectionExtensions` documentation

## Overview
`SqlConnectionExtensions` is a collection of convenience extension methods 
for `System.Data.SqlClient.SqlConnection` that simplify querying SQL Server 
catalog information. The methods execute pre-defined catalog queries (implemented 
by reader wrappers in `Harlinn.Common.Core.Net.Data.SqlClient.Readers`) and 
return strongly-typed domain objects from `Harlinn.Common.Core.Net.Data.SqlClient.Types`.

All methods are synchronous and use `using` to dispose commands/readers; callers do 
not need to dispose returned collections. 

## Key helpers
- `CreateCommand(this SqlConnection, string commandText, CommandType commandType = CommandType.Text)`  
  Creates and initializes a `SqlCommand` with text/type.

- Catalog readers → typed results (examples):
  - `GetSchemas()` / `GetSchema(int schemaId)` / `GetSchemaByName(string)` → returns `Types.Schema`
  - `GetSchemaObjects(...)` → returns `SchemaObject` / `Types.SchemaObject`
  - `GetTables(...)`, `GetViews(...)`, `GetProcedures(...)` → returns `Types.Table`, `Types.View`, `Types.Procedure`
  - `GetColumns(...)`, `GetSystemColumns(...)`, `GetComputedColumns(...)`, `GetIdentityColumns(...)` → returns `Column`, `Types.Column`, `ComputedColumn`, `IdentityColumn`
  - `GetIndexes(...)`, `GetIndexColumns(...)`, `GetForeignKeys(...)`, `GetCheckConstraints(...)`, `GetDefaultConstraint(...)` → index/constraint types
  - `GetSystemViews(...)` / `GetSystemView(...)` → returns `Types.SystemView`
  - `GetDatabaseType(...)`, `GetSystemDatabaseType(...)` → returns `Types.DatabaseType`

- Utility:
  - `GetSystemDataType(this SqlConnection, ITyped column)` — maps `ITyped.SystemType` to `SystemDataType`, performing schema/type lookups when needed.

## Describe first result set
- `DescribeFirstResultSet(this SqlConnection connection, string tsql, string? parameters, bool includeBrowseInformation = true)`  
  Calls `sys.sp_describe_first_result_set` and returns `IReadOnlyList<ResultSetColumn>` (reader: `ResultSetColumnReader`).  
  - `tsql` — the T-SQL batch to analyze (e.g. `SELECT ...` or `EXEC proc ...`).  
  - `parameters` — optional parameter definition string accepted by `sp_describe_first_result_set` (e.g. `'@p1 int, @p2 nvarchar(50)'`), or `null`.
  - `includeBrowseInformation` forwards to the stored-proc flag.

Example:
```csharp
// Example usage (not part of repository)
using var conn = new SqlConnection(connString);
conn.Open();

string tsql = "SELECT Id, Name FROM dbo.Orders WHERE Id = @id";
string parameters = "@id int";
var columns = conn.DescribeFirstResultSet(tsql, parameters);

foreach (var c in columns)
{
    Console.WriteLine($"{c.ColumnOrdinal}: {c.Name} ({c.SystemTypeName})");
}
```

## Return types and namespaces
Returned model types live in:
- `Harlinn.Common.Core.Net.Data.SqlClient.Types` (e.g. `Types.Table`, `Types.SchemaObject`, `Types.SystemView`, `ResultSetColumn`, etc.)
Readers live in:
- `Harlinn.Common.Core.Net.Data.SqlClient.Readers` and use `DataReaderWrapper` conveniences.

## Error handling and resource management
- Methods create `SqlCommand` and call `ExecuteReader()`; `SqlCommand` and `SqlDataReader` are disposed internally via `using`.
- SQL errors will surface as `SqlException` from the call site; callers should catch and handle accordingly.
- Many queries use `command.Parameters.AddWithValue(...)`. If precise parameter typing is required, prefer creating `SqlParameter` instances or the typed helpers in `SqlParameterCollectionExtensions`.

## Gotchas / notes
- Connection state: most methods assume the `SqlConnection` is open. If your environment requires explicit opening, call `Open()` first.
- `DescribeFirstResultSet` analyzes the batch without executing it — provide correct `@params` definitions for accurate results.
- `GetSystemDataType` may query the database for type/schema details; it caches the `sys` schema id in a static field. Consider potential threading implications if reused concurrently.
- Methods are synchronous only; use them on background threads or adapt for async if needed.
- For UDT/CLR types or spatial types (e.g. `geometry`, `geography`, `hierarchyid`) the readers and `DataReaderWrapper` expose specialized getters (e.g. `GetSqlGeometry`, `GetSqlGeography`, `GetSqlHierarchyId`) that return `Microsoft.SqlServer.Types` instances.

## Finding implementation
- Extension class source: `DotNet\Libraries\Harlinn.Common.Core.Net\Data\SqlClient\SqlConnectionExtensions.cs`
- Readers: `DotNet\Libraries\Harlinn.Common.Core.Net\Data\SqlClient\Readers\*Reader.cs`
- Model types: `DotNet\Libraries\Harlinn.Common.Core.Net\Data\SqlClient\Types\*.cs`
- Data reader helpers: `DotNet\Libraries\Harlinn.Common.Core.Net\Data\SqlClient\DataReaderWrapper.cs`

## Quick examples

Describe a SELECT:
```csharp
// Example
conn.Open();
var cols = conn.DescribeFirstResultSet("SELECT TOP(1) Id, Name FROM dbo.Customers", null);
```

Get all system views:
```csharp
var systemViews = conn.GetSystemViews();
foreach (var v in systemViews) Console.WriteLine(v.Name);
```

Get tables in schema:
```csharp
var tables = conn.GetTables(schemaId: 1);
```

# `SqlConnectionExtensions` 

- `SqlCommand CreateCommand(this SqlConnection connection, string commandText, CommandType commandType = CommandType.Text)`  
  - Returns: `SqlCommand`  
  - Source: (helper — not a catalog view)

- `IReadOnlyList<Schema> GetSchemas(this SqlConnection connection)`  
  - Returns: `IReadOnlyList<Schema>`  
  - View: `sys.schemas` (`SchemasReader.Sql`)

- `Schema? GetSchema(this SqlConnection connection, int schemaId)`  
  - Returns: `Schema?`  
  - View: `sys.schemas` (`SchemasReader.Sql`)

- `int GetSchemaId(this SqlConnection connection, string schemaName)`  
  - Returns: `int`  
  - View: `sys.schemas` (via `GetSchemaByName`)

- `Schema? GetSchemaByName(this SqlConnection connection, string schemaName)`  
  - Returns: `Schema?`  
  - View: `sys.schemas` (`SchemasReader.Sql`)

- `IReadOnlyList<SchemaObject> GetSchemaObjects(this SqlConnection connection)`  
  - Returns: `IReadOnlyList<SchemaObject>`  
  - View: `sys.objects` / schema-objects query (`SchemaObjectsReader.Sql`)

- `IReadOnlyList<SchemaObject> GetSchemaObjects(this SqlConnection connection, SchemaObjectType schemaObjectType)`  
  - Returns: `IReadOnlyList<SchemaObject>`  
  - View: `sys.objects` (`SchemaObjectsReader.Sql`)

- `IReadOnlyList<SchemaObject> GetSchemaObjects(this SqlConnection connection, int schemaId)`  
  - Returns: `IReadOnlyList<SchemaObject>`  
  - View: `sys.objects` (`SchemaObjectsReader.Sql`)

- `IReadOnlyList<SchemaObject> GetSchemaObjects(this SqlConnection connection, SchemaObjectType schemaObjectType, int schemaId)`  
  - Returns: `IReadOnlyList<SchemaObject>`  
  - View: `sys.objects` (`SchemaObjectsReader.Sql`)

- `IReadOnlyList<Types.SchemaObject> GetSchemaObjects(this SqlConnection connection, Schema schema)`  
  - Returns: `IReadOnlyList<Types.SchemaObject>`  
  - View: `sys.objects` (`SchemaObjectsReader.Sql`)

- `IReadOnlyList<Types.SchemaObject> GetSchemaObjects(this SqlConnection connection, SchemaObjectType schemaObjectType, Schema schema)`  
  - Returns: `IReadOnlyList<Types.SchemaObject>`  
  - View: `sys.objects` (`SchemaObjectsReader.Sql`)

- `SchemaObject? GetSchemaObject(this SqlConnection connection, int schemaId, int objectId)`  
  - Returns: `SchemaObject?`  
  - View: `sys.objects` (`SchemaObjectsReader.Sql`)

- `SchemaObject? GetSchemaObject(this SqlConnection connection, SchemaObjectType schemaObjectType, int schemaId, int objectId)`  
  - Returns: `SchemaObject?`  
  - View: `sys.objects` (`SchemaObjectsReader.Sql`)

- `SchemaObject? GetSchemaObject(this SqlConnection connection, int objectId)`  
  - Returns: `SchemaObject?`  
  - View: `sys.objects` (`SchemaObjectsReader.Sql`)

- `SchemaObject? GetSchemaObject(this SqlConnection connection, SchemaObjectType schemaObjectType, int objectId)`  
  - Returns: `SchemaObject?`  
  - View: `sys.objects` (`SchemaObjectsReader.Sql`)

- `SchemaObject? GetSchemaObject(this SqlConnection connection, int schemaId, string objectName)`  
  - Returns: `SchemaObject?`  
  - View: `sys.objects` (`SchemaObjectsReader.Sql`)

- `SchemaObject? GetSchemaObject(this SqlConnection connection, SchemaObjectType schemaObjectType, int schemaId, string objectName)`  
  - Returns: `SchemaObject?`  
  - View: `sys.objects` (`SchemaObjectsReader.Sql`)

- `IReadOnlyList<SchemaObject> GetSystemObjects(this SqlConnection connection)`  
  - Returns: `IReadOnlyList<SchemaObject>`  
  - View: `sys.system_objects` (or system-objects query via `SystemObjectsReader.Sql`)

- `IReadOnlyList<SchemaObject> GetSystemObjects(this SqlConnection connection, SchemaObjectType schemaObjectType)`  
  - Returns: `IReadOnlyList<SchemaObject>`  
  - View: `sys.system_objects` (`SystemObjectsReader.Sql`)

- `IReadOnlyList<SchemaObject> GetSystemObjects(this SqlConnection connection, int schemaId)`  
  - Returns: `IReadOnlyList<SchemaObject>`  
  - View: `sys.system_objects` (`SystemObjectsReader.Sql`)

- `IReadOnlyList<SchemaObject> GetSystemObjects(this SqlConnection connection, SchemaObjectType schemaObjectType, int schemaId)`  
  - Returns: `IReadOnlyList<SchemaObject>`  
  - View: `sys.system_objects` (`SystemObjectsReader.Sql`)

- `IReadOnlyList<Types.SchemaObject> GetSystemObjects(this SqlConnection connection, Schema schema)`  
  - Returns: `IReadOnlyList<Types.SchemaObject>`  
  - View: `sys.system_objects` (`SystemObjectsReader.Sql`)

- `IReadOnlyList<Types.SchemaObject> GetSystemObjects(this SqlConnection connection, SchemaObjectType schemaObjectType, Schema schema)`  
  - Returns: `IReadOnlyList<Types.SchemaObject>`  
  - View: `sys.system_objects` (`SystemObjectsReader.Sql`)

- `SchemaObject? GetSystemObject(this SqlConnection connection, int schemaId, int objectId)`  
  - Returns: `SchemaObject?`  
  - View: `sys.system_objects` (`SystemObjectsReader.Sql`)

- `SchemaObject? GetSystemObject(this SqlConnection connection, SchemaObjectType schemaObjectType, int schemaId, int objectId)`  
  - Returns: `SchemaObject?`  
  - View: `sys.system_objects` (`SystemObjectsReader.Sql`)

- `SchemaObject? GetSystemObject(this SqlConnection connection, int objectId)`  
  - Returns: `SchemaObject?`  
  - View: `sys.system_objects` (`SystemObjectsReader.Sql`)

- `SchemaObject? GetSystemObject(this SqlConnection connection, SchemaObjectType schemaObjectType, int objectId)`  
  - Returns: `SchemaObject?`  
  - View: `sys.system_objects` (`SystemObjectsReader.Sql`)

- `SchemaObject? GetSystemObject(this SqlConnection connection, int schemaId, string objectName)`  
  - Returns: `SchemaObject?`  
  - View: `sys.system_objects` (`SystemObjectsReader.Sql`)

- `SchemaObject? GetSystemObject(this SqlConnection connection, SchemaObjectType schemaObjectType, int schemaId, string objectName)`  
  - Returns: `SchemaObject?`  
  - View: `sys.system_objects` (`SystemObjectsReader.Sql`)

- `IReadOnlyList<Types.Table> GetTables(this SqlConnection connection)`  
  - Returns: `IReadOnlyList<Types.Table>`  
  - View: `sys.tables` (`TablesReader.Sql`)

- `IReadOnlyList<Types.Table> GetTables(this SqlConnection connection, int schemaId)`  
  - Returns: `IReadOnlyList<Types.Table>`  
  - View: `sys.tables` (`TablesReader.Sql`)

- `IReadOnlyList<Types.Table> GetTables(this SqlConnection connection, Schema schema)`  
  - Returns: `IReadOnlyList<Types.Table>`  
  - View: `sys.tables` (`TablesReader.Sql`)

- `Types.Table? GetTable(this SqlConnection connection, int schemaId, int objectId)`  
  - Returns: `Types.Table?`  
  - View: `sys.tables` (`TablesReader.Sql`)

- `Types.Table? GetTable(this SqlConnection connection, Types.Schema schema, int objectId)`  
  - Returns: `Types.Table?`  
  - View: `sys.tables` (`TablesReader.Sql`)

- `Types.Table? GetTable(this SqlConnection connection, int schemaId, string objectName)`  
  - Returns: `Types.Table?`  
  - View: `sys.tables` (`TablesReader.Sql`)

- `Types.Table? GetTable(this SqlConnection connection, Types.Schema schema, string objectName)`  
  - Returns: `Types.Table?`  
  - View: `sys.tables` (`TablesReader.Sql`)

- `IReadOnlyList<Types.View> GetViews(this SqlConnection connection)`  
  - Returns: `IReadOnlyList<Types.View>`  
  - View: `sys.views` (`ViewsReader.Sql`)

- `IReadOnlyList<Types.View> GetViews(this SqlConnection connection, int schemaId)`  
  - Returns: `IReadOnlyList<Types.View>`  
  - View: `sys.views` (`ViewsReader.Sql`)

- `IReadOnlyList<Types.View> GetViews(this SqlConnection connection, Schema schema)`  
  - Returns: `IReadOnlyList<Types.View>`  
  - View: `sys.views` (`ViewsReader.Sql`)

- `Types.View? GetView(this SqlConnection connection, int schemaId, int viewId)`  
  - Returns: `Types.View?`  
  - View: `sys.views` (`ViewsReader.Sql`)

- `Types.View? GetView(this SqlConnection connection, int schemaId, string viewName)`  
  - Returns: `Types.View?`  
  - View: `sys.views` (`ViewsReader.Sql`)

- `IReadOnlyList<Types.SystemView> GetSystemViews(this SqlConnection connection)`  
  - Returns: `IReadOnlyList<Types.SystemView>`  
  - View: `sys.system_views` (`SystemViewsReader.Sql`)

- `IReadOnlyList<Types.SystemView> GetSystemViews(this SqlConnection connection, int schemaId)`  
  - Returns: `IReadOnlyList<Types.SystemView>`  
  - View: `sys.system_views` (`SystemViewsReader.Sql`)

- `IReadOnlyList<Types.SystemView> GetSystemViews(this SqlConnection connection, Schema schema)`  
  - Returns: `IReadOnlyList<Types.SystemView>`  
  - View: `sys.system_views` (`SystemViewsReader.Sql`)

- `Types.SystemView? GetSystemView(this SqlConnection connection, int schemaId, int viewId)`  
  - Returns: `Types.SystemView?`  
  - View: `sys.system_views` (`SystemViewsReader.Sql`)

- `IReadOnlyList<Types.Procedure> GetProcedures(this SqlConnection connection)`  
  - Returns: `IReadOnlyList<Types.Procedure>`  
  - View: `sys.procedures` (`ProceduresReader.Sql`)

- `IReadOnlyList<Types.Procedure> GetProcedures(this SqlConnection connection, int schemaId)`  
  - Returns: `IReadOnlyList<Types.Procedure>`  
  - View: `sys.procedures` (`ProceduresReader.Sql`)

- `IReadOnlyList<Types.Procedure> GetProcedures(this SqlConnection connection, Schema schema)`  
  - Returns: `IReadOnlyList<Types.Procedure>`  
  - View: `sys.procedures` (`ProceduresReader.Sql`)

- `IReadOnlyList<Parameter> GetParameters(this SqlConnection connection, int objectId)`  
  - Returns: `IReadOnlyList<Parameter>`  
  - View: `sys.parameters` (`ParametersReader.Sql`)

- `IReadOnlyList<Parameter> GetParameters(this SqlConnection connection, Procedure procedure)`  
  - Returns: `IReadOnlyList<Parameter>`  
  - View: `sys.parameters` (`ParametersReader.Sql`)

- `IReadOnlyList<Types.ForeignKey> GetForeignKeys(this SqlConnection connection)`  
  - Returns: `IReadOnlyList<Types.ForeignKey>`  
  - View: `sys.foreign_keys` (`ForeignKeyReader.Sql`)

- `IReadOnlyList<Types.ForeignKey> GetForeignKeys(this SqlConnection connection, int tableId)`  
  - Returns: `IReadOnlyList<Types.ForeignKey>`  
  - View: `sys.foreign_keys` (`ForeignKeyReader.Sql`)

- `IReadOnlyList<Types.ForeignKey> GetForeignKeys(this SqlConnection connection, Types.Table table)`  
  - Returns: `IReadOnlyList<Types.ForeignKey>`  
  - View: `sys.foreign_keys` (`ForeignKeyReader.Sql`)

- `IReadOnlyList<Types.ForeignKeyColumn> GetForeignKeyColumns(this SqlConnection connection, int parentObjectId, int foreignKeyId)`  
  - Returns: `IReadOnlyList<Types.ForeignKeyColumn>`  
  - View: `sys.foreign_key_columns` (`ForeignKeyColumnsReader.Sql`)

- `IReadOnlyList<Types.ForeignKeyColumn> GetForeignKeyColumns(this SqlConnection connection, ForeignKey foreignKey)`  
  - Returns: `IReadOnlyList<Types.ForeignKeyColumn>`  
  - View: `sys.foreign_key_columns` (`ForeignKeyColumnsReader.Sql`)

- `IReadOnlyList<Column> GetColumns(this SqlConnection connection, int objectId)`  
  - Returns: `IReadOnlyList<Column>`  
  - View: `sys.columns` (`ColumnsReader.Sql`)

- `Column? GetColumn(this SqlConnection connection, int objectId, int columnId)`  
  - Returns: `Column?`  
  - View: `sys.columns` (`ColumnsReader.Sql`)

- `IReadOnlyList<Column> GetColumns(this SqlConnection connection, Table table)`  
  - Returns: `IReadOnlyList<Column>`  
  - View: `sys.columns` (`ColumnsReader.Sql`)

- `IReadOnlyList<Column> GetColumns(this SqlConnection connection, View view)`  
  - Returns: `IReadOnlyList<Column>`  
  - View: `sys.columns` (`ColumnsReader.Sql`)

- `IReadOnlyList<Column> GetSystemColumns(this SqlConnection connection, int objectId)`  
  - Returns: `IReadOnlyList<Column>`  
  - View: `sys.system_columns` (`SystemColumnsReader.Sql`)

- `Column? GetSystemColumn(this SqlConnection connection, int objectId, int columnId)`  
  - Returns: `Column?`  
  - View: `sys.system_columns` (`SystemColumnsReader.Sql`)

- `IReadOnlyList<Column> GetSystemColumns(this SqlConnection connection, SystemView view)`  
  - Returns: `IReadOnlyList<Column>`  
  - View: `sys.system_columns` (`SystemColumnsReader.Sql`)

- `IReadOnlyList<ResultSetColumn> DescribeFirstResultSet(this SqlConnection connection, string tsql, string? parameters, bool includeBrowseInformation = true)`  
  - Returns: `IReadOnlyList<ResultSetColumn>`  
  - Source: `sys.sp_describe_first_result_set` (stored procedure)

- `IReadOnlyList<IdentityColumn> GetIdentityColumns(this SqlConnection connection, int objectId)`  
  - Returns: `IReadOnlyList<IdentityColumn>`  
  - View: `sys.identity_columns` (`IdentityColumnsReader.Sql`)

- `IdentityColumn? GetIdentityColumn(this SqlConnection connection, int objectId, int columnId)`  
  - Returns: `IdentityColumn?`  
  - View: `sys.identity_columns` (`IdentityColumnsReader.Sql`)

- `IdentityColumn? GetIdentityColumn(this SqlConnection connection, Column column)`  
  - Returns: `IdentityColumn?`  
  - View: `sys.identity_columns` (`IdentityColumnsReader.Sql`)

- `IReadOnlyList<ComputedColumn> GetComputedColumns(this SqlConnection connection, int objectId)`  
  - Returns: `IReadOnlyList<ComputedColumn>`  
  - View: `sys.computed_columns` (`ComputedColumnsReader.Sql`)

- `ComputedColumn? GetComputedColumn(this SqlConnection connection, int objectId, int columnId)`  
  - Returns: `ComputedColumn?`  
  - View: `sys.computed_columns` (`ComputedColumnsReader.Sql`)

- `ComputedColumn? GetComputedColumn(this SqlConnection connection, Column column)`  
  - Returns: `ComputedColumn?`  
  - View: `sys.computed_columns` (`ComputedColumnsReader.Sql`)

- `DefaultConstraint? GetDefaultConstraint(this SqlConnection connection, int parentObjectId, int columnId)`  
  - Returns: `DefaultConstraint?`  
  - View: `sys.default_constraints` (`DefaultConstraintsReader.Sql`)

- `DefaultConstraint? GetDefaultConstraint(this SqlConnection connection, Column column)`  
  - Returns: `DefaultConstraint?`  
  - View: `sys.default_constraints` (`DefaultConstraintsReader.Sql`)

- `IReadOnlyList<Types.Index> GetIndexes(this SqlConnection connection, int objectId)`  
  - Returns: `IReadOnlyList<Types.Index>`  
  - View: `sys.indexes` (`IndexesReader.Sql`)

- `IReadOnlyList<Types.Index> GetIndexes(this SqlConnection connection, Table table)`  
  - Returns: `IReadOnlyList<Types.Index>`  
  - View: `sys.indexes` (`IndexesReader.Sql`)

- `IReadOnlyList<IndexColumn> GetIndexColumns(this SqlConnection connection, int objectId, int indexId)`  
  - Returns: `IReadOnlyList<IndexColumn>`  
  - View: `sys.index_columns` (`IndexColumnsReader.Sql`)

- `IReadOnlyList<IndexColumn> GetIndexColumns(this SqlConnection connection, Types.Index index)`  
  - Returns: `IReadOnlyList<IndexColumn>`  
  - View: `sys.index_columns` (`IndexColumnsReader.Sql`)

- `IReadOnlyList<Types.CheckConstraint> GetCheckConstraints(this SqlConnection connection, int objectId)`  
  - Returns: `IReadOnlyList<Types.CheckConstraint>`  
  - View: `sys.check_constraints` (`CheckConstraintsReader.Sql`)

- `IReadOnlyList<Types.CheckConstraint> GetTableCheckConstraints(this SqlConnection connection, int objectId)`  
  - Returns: `IReadOnlyList<Types.CheckConstraint>`  
  - View: `sys.check_constraints` (`CheckConstraintsReader.Sql` - filtered for parent_column_id = 0)

- `IReadOnlyList<Types.CheckConstraint> GetCheckConstraints(this SqlConnection connection, int objectId, int columnId)`  
  - Returns: `IReadOnlyList<Types.CheckConstraint>`  
  - View: `sys.check_constraints` (`CheckConstraintsReader.Sql`)

- `IReadOnlyList<Types.CheckConstraint> GetCheckConstraints(this SqlConnection connection, Column column)`  
  - Returns: `IReadOnlyList<Types.CheckConstraint>`  
  - View: `sys.check_constraints` (`CheckConstraintsReader.Sql`)

- `Types.Index GetPrimaryKey(this SqlConnection connection, int objectId)`  
  - Returns: `Types.Index`  
  - View: `sys.indexes` (`IndexesReader.Sql` — filtered `is_primary_key = 1`)

- `Types.Index GetPrimaryKey(this SqlConnection connection, Table table)`  
  - Returns: `Types.Index`  
  - View: `sys.indexes` (`IndexesReader.Sql`)

- `Types.DatabaseType? GetDatabaseType(this SqlConnection connection, int schemaId, string typeName)`  
  - Returns: `Types.DatabaseType?`  
  - View: `sys.types` (`TypesReader.Sql`)

- `Types.DatabaseType? GetDatabaseType(this SqlConnection connection, string typeName)`  
  - Returns: `Types.DatabaseType?`  
  - View: `sys.types` (`TypesReader.Sql`)

- `Types.DatabaseType? GetSystemDatabaseType(this SqlConnection connection, byte systemTypeId)`  
  - Returns: `Types.DatabaseType?`  
  - View: `sys.types` (`TypesReader.Sql`)

- `SystemDataType GetSystemDataType(this SqlConnection connection, ITyped column)`  
  - Returns: `SystemDataType` (enum)  
  - Uses: `sys.types`, `sys.schemas` and other lookups (via `TypesReader.Sql`, `SchemasReader.Sql`) — performs mapping logic

