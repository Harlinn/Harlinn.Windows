# XmlSchemaCollectionsReader

Overview

`XmlSchemaCollectionsReader` wraps `sys.xml_schema_collections` and lists XML schema collections registered in the database.

Reader SQL

```
SELECT
  xsc.[xml_collection_id],
  xsc.[schema_id],
  xsc.[principal_id],
  xsc.[Name],
  xsc.[create_date],
  xsc.[modify_date]
FROM
  [sys].[xml_schema_collections] xsc
```

Columns and interpretation

- `xml_collection_id` (int): Identifier for the XML schema collection. Use to join to xml schema component views.
- `schema_id` (int): Schema id that contains the xml schema collection (owner schema).
- `principal_id` (int?): Principal id of the owner if different from schema owner.
- `Name` (sysname): Name of the XML schema collection.
- `create_date` (datetime): When the collection was created.
- `modify_date` (datetime): When the collection was last modified.

How to interpret

- XML schema collections group related XML schemas for validation. Use `xml_collection_id` to find components, types, elements, and namespaces belonging to the collection.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = XmlSchemaCollectionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new XmlSchemaCollectionsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Collection:{r.Name} Id:{r.XmlCollectionId} SchemaId:{r.SchemaId} Created:{r.CreateDate}");
```

See also:

- [sys.xml_schema_collections](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-xml-schema-collections)
