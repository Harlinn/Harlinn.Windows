# XmlSchemaWildcardNamespacesReader

Overview

`XmlSchemaWildcardNamespacesReader` wraps `sys.xml_schema_wildcard_namespaces` and lists namespace URIs permitted or used by wildcard components in XML schema collections.

Reader SQL

```
SELECT
  xswn.[xml_component_id],
  xswn.[Namespace]
FROM
  [sys].[xml_schema_wildcard_namespaces] xswn
```

Columns and interpretation

- `xml_component_id` (int): The wildcard component id to which the namespace entry belongs.
- `Namespace` (nvarchar): The namespace URI or wildcard token representing allowed namespaces for the wildcard (e.g., ##any, ##local, ##other, or explicit namespace URI).

How to interpret

- These entries enumerate namespaces allowed by wildcard components; use to reconstruct namespace matching rules for <any> or <anyAttribute> wildcards in schemas.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = XmlSchemaWildcardNamespacesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new XmlSchemaWildcardNamespacesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"WildcardComp:{r.XmlComponentId} Namespace:{r.Namespace}");
```

See also:

- [sys.xml_schema_wildcard_namespaces](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-xml-schema-wildcard-namespaces)
