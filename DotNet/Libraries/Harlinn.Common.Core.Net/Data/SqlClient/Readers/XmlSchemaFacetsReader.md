# XmlSchemaFacetsReader

Overview

`XmlSchemaFacetsReader` wraps `sys.xml_schema_facets` and exposes facets (restrictions) applied to simple types or elements in XML schema collections.

Reader SQL

```
SELECT
  xsf.[xml_component_id],
  xsf.[facet_id],
  xsf.[Kind],
  xsf.[kind_desc],
  xsf.[is_fixed],
  xsf.[Value]
FROM
  [sys].[xml_schema_facets] xsf
```

Columns and interpretation

- `xml_component_id` (int): Component id to which the facet applies (type or element).
- `facet_id` (int): Facet identifier.
- `Kind` (nvarchar): Facet kind code (e.g., length, minLength, pattern, enumeration).
- `kind_desc` (nvarchar?): Human readable facet description.
- `is_fixed` (bit): Whether the facet is fixed and cannot be changed in derivations.
- `Value` (nvarchar?): The facet value (e.g., numeric limit, pattern string, enumeration member).

How to interpret

- Use facets to understand constraints applied to simple types: value ranges, patterns, enumeration members, whiteSpace normalization, etc.
- `is_fixed` indicates whether derived types may change the facet.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = XmlSchemaFacetsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new XmlSchemaFacetsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Comp:{r.XmlComponentId} Facet:{r.Kind} Value:{r.Value} Fixed:{r.IsFixed}");
```

See also:

- [sys.xml_schema_facets](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-xml-schema-facets)
