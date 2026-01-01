# XmlSchemaComponentsReader

Overview

`XmlSchemaComponentsReader` wraps `sys.xml_schema_components` and lists components (types, elements, attributes, model groups, etc.) defined in xml schema collections.

Reader SQL

```
SELECT
  xsc0.[xml_component_id],
  xsc0.[xml_collection_id],
  xsc0.[xml_namespace_id],
  xsc0.[is_qualified],
  xsc0.[Name],
  xsc0.[symbol_space],
  xsc0.[symbol_space_desc],
  xsc0.[Kind],
  xsc0.[kind_desc],
  xsc0.[Derivation],
  xsc0.[derivation_desc],
  xsc0.[base_xml_component_id],
  xsc0.[scoping_xml_component_id]
FROM
  [sys].[xml_schema_components] xsc0
```

Columns and interpretation

- `xml_component_id` (int): Unique id of the schema component.
- `xml_collection_id` (int): Collection id that owns the component.
- `xml_namespace_id` (int): Namespace id for component.
- `is_qualified` (bit): Whether component is namespace-qualified.
- `Name` (nvarchar?): Local name of the component; may be NULL for anonymous components.
- `symbol_space` (nvarchar): Internal symbol space classification.
- `symbol_space_desc` (nvarchar?): Readable description of the symbol space.
- `Kind` (nvarchar): Component kind code (element, attribute, type, etc.).
- `kind_desc` (nvarchar?): Human readable kind description.
- `Derivation` (nvarchar): Derivation code for type components.
- `derivation_desc` (nvarchar?): Human readable derivation description.
- `base_xml_component_id` (int?): Base component id for derived types.
- `scoping_xml_component_id` (int?): Component id that scopes this component (e.g., the complex type or element that contains it).

How to interpret

- Use `xml_component_id` to relate rows across the various xml_schema_* catalog views.
- The combination of `xml_collection_id`, `xml_namespace_id`, and `Name` identifies a named component within the database.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = XmlSchemaComponentsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new XmlSchemaComponentsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"CompId:{r.XmlComponentId} Coll:{r.XmlCollectionId} Name:{r.Name} Kind:{r.Kind}");
```

See also:

- [sys.xml_schema_components](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-xml-schema-components)
