# XmlSchemaModelGroupsReader

Overview

`XmlSchemaModelGroupsReader` wraps `sys.xml_schema_model_groups` and exposes model group components (sequence/choice/all) used to compose complex content models.

Reader SQL

```
SELECT
  xsmg.[xml_component_id],
  xsmg.[xml_collection_id],
  xsmg.[xml_namespace_id],
  xsmg.[is_qualified],
  xsmg.[Name],
  xsmg.[symbol_space],
  xsmg.[symbol_space_desc],
  xsmg.[Kind],
  xsmg.[kind_desc],
  xsmg.[Derivation],
  xsmg.[derivation_desc],
  xsmg.[base_xml_component_id],
  xsmg.[scoping_xml_component_id],
  xsmg.[Compositor],
  xsmg.[compositor_desc]
FROM
  [sys].[xml_schema_model_groups] xsmg
```

Columns and interpretation

- `xml_component_id` (int): Component id for the model group.
- `xml_collection_id` (int): Collection id.
- `xml_namespace_id` (int): Namespace id.
- `is_qualified` (bit): Namespace qualification flag.
- `Name` (nvarchar?): Name of the model group (if named).
- `symbol_space` (nvarchar): Internal symbol space classification.
- `symbol_space_desc` (nvarchar?): Description of symbol space.
- `Kind`/`kind_desc` (nvarchar): Kind codes and descriptions.
- `Derivation`/`derivation_desc` (nvarchar): Derivation information for types.
- `base_xml_component_id` (int?): Base component id where applicable.
- `scoping_xml_component_id` (int?): Component id that scopes the model group.
- `Compositor` (nvarchar): Compositor used by the model group (Sequence, Choice, All).
- `compositor_desc` (nvarchar?): Description of the compositor.

How to interpret

- Model groups define the ordering and occurrence rules for child elements. Use placements to see which elements are placed into model groups.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = XmlSchemaModelGroupsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new XmlSchemaModelGroupsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"ModelGroup:{r.XmlComponentId} Name:{r.Name} Compositor:{r.Compositor}");
```

See also:

- [sys.xml_schema_model_groups](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-xml-schema-model-groups)
