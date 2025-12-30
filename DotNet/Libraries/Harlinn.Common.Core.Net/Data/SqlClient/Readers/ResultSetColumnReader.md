# ResultSetColumnReader

Overview

`ResultSetColumnReader` is a wrapper around the result set returned by `sys.sp_describe_first_result_set` (a stored procedure) and describes the metadata for the first result set of a T-SQL batch or query.

Reader SQL

```
EXEC sys.sp_describe_first_result_set @tsql = @tsql, @params = NULL, @include_browse_information = 1
```

Columns and interpretation

This reader exposes the full set of columns produced by `sp_describe_first_result_set`. Below are the columns and how to interpret them.

- `is_hidden` (bool): Whether the column is hidden (e.g., internal columns such as rowguid).
- `column_ordinal` (int): Column ordinal position in the result set (1-based).
- `name` (string?): Column name.
- `is_nullable` (bool): Whether the column allows NULL values.
- `system_type_id` (int): Internal system type id (map to SQL Server types).
- `system_type_name` (string?): Type name of the column (e.g., `int`, `nvarchar(50)`).
- `max_length` (short?): Maximum length in bytes for the type (or -1 for max types).
- `precision` (byte?): Precision for numeric types.
- `scale` (byte?): Scale for numeric types.
- `collation_name` (string?): Collation for character types.
- `user_type_id` (int?): User-defined type id if applicable.
- `user_type_database` (string?): Database containing the user type.
- `user_type_schema` (string?): Schema for the user type.
- `user_type_name` (string?): Name of the user-defined type.
- `assembly_qualified_type_name` (string?): For CLR types, the assembly-qualified .NET type name.
- `xml_collection_id` (int?): Id of associated xml collection, if xml typed.
- `xml_collection_database`/`xml_collection_schema`/`xml_collection_name` (string?): Location and name of the xml collection.
- `is_xml_document` (bool): Whether the xml type is documented as xml document type.
- `is_case_sensitive` (bool): Whether the type or column is case sensitive.
- `is_fixed_length_clr_type` (bool): Whether CLR type is fixed-length.
- `source_server`, `source_database`, `source_schema`, `source_table`, `source_column` (string?): Metadata indicating the original source of the column when the result set derives from a base table.
- `is_identity_column` (bool): Whether the column is an identity column.
- `is_part_of_unique_key` (bool): Whether the column is part of a unique key.
- `is_updateable` (bool): Whether the column is updateable.
- `is_computed_column` (bool): Whether the column is computed.
- `is_sparse_column_set` (bool): Whether the column is a sparse column set.
- `ordinal_in_order_by_list` (int?): If the column participates in an ORDER BY list, its ordinal in that list.
- `order_by_list_length` (int?): Total number of columns in the ORDER BY list.
- `order_by_is_descending` (short?): Whether the ORDER BY is descending for this column (non-zero means descending).
- `tds_type_id`, `tds_length`, `tds_collation`, `tds_collation_sort_id` (int?): TDS-specific type/collation information used by the client protocol.

How to interpret

- `sp_describe_first_result_set` provides column-level metadata without executing the query; use this reader to programmatically inspect expected result structure.
- `system_type_name`, `max_length`, `precision`, and `scale` are the most useful fields for mapping SQL types to application types.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ResultSetColumnReader.Sql;
cmd.Parameters.AddWithValue("@tsql", "SELECT Id, Name FROM dbo.Customers");
using var rdr = cmd.ExecuteReader();
var reader = new ResultSetColumnReader(rdr, ownsReader:false);
var cols = reader.GetColumns();
foreach (var col in cols)
{
    Console.WriteLine($"{col.ColumnOrdinal}: {col.Name} ({col.SystemTypeName}) Nullable:{col.IsNullable}");
}
```

See also:

- [sp_describe_first_result_set (Transact-SQL)](https://learn.microsoft.com/en-us/sql/relational-databases/system-stored-procedures/sp-describe-first-result-set-transact-sql)

