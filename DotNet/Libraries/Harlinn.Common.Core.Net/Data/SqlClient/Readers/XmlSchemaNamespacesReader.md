# XmlSchemaNamespacesReader

Overview

`XmlSchemaNamespacesReader` wraps `sys.xml_schema_namespaces` and lists namespaces registered for XML schema collections.

Reader SQL

```
SELECT
  xsn.[xml_collection_id],
  xsn.[Name],
  xsn.[xml_namespace_id]
FROM
  [sys].[xml_schema_namespaces] xsn
```

Columns and interpretation

- `xml_collection_id` (int): The xml schema collection id that includes the namespace.
- `Name` (nvarchar?): Namespace URI or a prefix/name used to identify the namespace.
- `xml_namespace_id` (int): Identifier for the namespace within the collection.

How to interpret

- Use these rows to resolve namespace ids used in other xml schema catalog views and to map component names to their namespace URIs.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = XmlSchemaNamespacesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new XmlSchemaNamespacesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Collection:{r.XmlCollectionId} NamespaceId:{r.XmlNamespaceId} Name:{r.Name}");
```

See also:

- [sys.xml_schema_namespaces](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-xml-schema-namespaces)
