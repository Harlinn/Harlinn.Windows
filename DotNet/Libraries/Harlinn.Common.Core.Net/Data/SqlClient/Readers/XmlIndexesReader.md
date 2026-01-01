# XmlIndexesReader

Overview

`XmlIndexesReader` wraps `sys.xml_indexes` and exposes metadata about XML indexes defined on XML-typed columns and their properties.

Reader SQL

```
SELECT
  xi.[object_id],
  xi.[Name],
  xi.[index_id],
  xi.[Type],
  xi.[type_desc],
  xi.[is_unique],
  xi.[data_space_id],
  xi.[ignore_dup_key],
  xi.[is_primary_key],
  xi.[is_unique_constraint],
  xi.[fill_factor],
  xi.[is_padded],
  xi.[is_disabled],
  xi.[is_hypothetical],
  xi.[is_ignored_in_optimization],
  xi.[allow_row_locks],
  xi.[allow_page_locks],
  xi.[using_xml_index_id],
  xi.[secondary_type],
  xi.[secondary_type_desc],
  xi.[has_filter],
  xi.[filter_definition],
  xi.[xml_index_type],
  xi.[xml_index_type_description],
  xi.[path_id],
  xi.[auto_created]
FROM
  [sys].[xml_indexes] xi
```

Columns and interpretation

- `object_id` (int): Object id (table) that owns the XML index.
- `Name` (nvarchar?): Index name.
- `index_id` (int): Index id within the object.
- `Type` (tinyint): Index type code.
- `type_desc` (nvarchar?): Index type description (PRIMARY XML INDEX, XML INDEX, PATH NAME INDEX etc.).
- `is_unique` (bit?): Whether the index enforces uniqueness.
- `data_space_id` (int): Filegroup or partition scheme id where index is stored.
- `ignore_dup_key` (bit?): Whether duplicate keys are ignored.
- `is_primary_key` (bit?): Whether this index is the primary XML index.
- `is_unique_constraint` (bit?): Whether index supports a unique constraint.
- `fill_factor` (tinyint): Fill factor setting for the index.
- `is_padded` (bit?): Padded flag for index pages.
- `is_disabled` (bit?): Whether the index is disabled.
- `is_hypothetical` (bit?): Whether the index is hypothetical (used in tuning advisor scenarios).
- `is_ignored_in_optimization` (bit?): Whether optimizer ignores the index.
- `allow_row_locks`/`allow_page_locks` (bit?): Locking options for the index.
- `using_xml_index_id` (int?): When this index is secondary, id of the primary XML index it uses.
- `secondary_type` (nvarchar?): Secondary index type.
- `secondary_type_desc` (nvarchar?): Secondary type description.
- `has_filter` (bit): Whether a filtered index definition exists.
- `filter_definition` (nvarchar?): Filter predicate definition.
- `xml_index_type` (tinyint?): XML index type code.
- `xml_index_type_description` (nvarchar?): XML index type description.
- `path_id` (int?): Path id for PATHNAME index entries.
- `auto_created` (bit?): Whether the index was auto-created by the engine.

How to interpret

- Primary XML indexes are required before creating secondary XML indexes. Use `using_xml_index_id` to find the relationship.
- `is_hypothetical` indicates indexes not physically present and used for tuning simulations.
- `filter_definition` applies when index is filtered; evaluate correctness for query coverage.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = XmlIndexesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new XmlIndexesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Table:{r.ObjectId} Index:{r.Name} Id:{r.IndexId} Type:{r.TypeDesc} Primary:{r.IsPrimaryKey} AutoCreated:{r.AutoCreated}");
```

See also:

- [sys.xml_indexes](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-xml-indexes)
