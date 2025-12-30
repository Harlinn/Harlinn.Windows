# QueryStoreQueryTextReader — reference

Overview

`QueryStoreQueryTextReader` wraps `sys.query_store_query_text` and returns SQL text captured by Query Store along with metadata about encryption and handles.

Reader SQL

```
SELECT
  qsqt.[query_text_id],
  qsqt.[query_sql_text],
  qsqt.[statement_sql_handle],
  qsqt.[is_part_of_encrypted_module],
  qsqt.[has_restricted_text]
FROM
  [sys].[query_store_query_text] qsqt
```

Columns and interpretation

- `query_text_id` — id for the stored SQL text.
- `query_sql_text` — the SQL text (nullable for restricted/encrypted content).
- `statement_sql_handle` — handle identifying the statement in the plan cache (nullable).
- `is_part_of_encrypted_module` — whether the text is part of an encrypted module (e.g., WITH ENCRYPTION on procedures).
- `has_restricted_text` — whether the text has restricted access (e.g., hidden due to permissions).

How to interpret

- Use `query_text_id` to correlate query text to queries in Query Store. Encrypted or restricted texts may hide actual SQL; `is_part_of_encrypted_module` helps explain missing text.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = QueryStoreQueryTextReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new QueryStoreQueryTextReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"TextId:{r.QueryTextId} HasText:{!string.IsNullOrEmpty(r.QuerySqlText)} Encrypted:{r.IsPartOfEncryptedModule}");
}
```

See also:

- [sys.query_store_query_text](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-query-store-query-text)
