# XmlSchemaComponentPlacementsReader

Overview

`XmlSchemaComponentPlacementsReader` wraps `sys.xml_schema_component_placements` and describes how XML schema components are placed (e.g., attribute or element placements within a complex type or model group).

Reader SQL

```
SELECT
  xscp.[xml_component_id],
  xscp.[placement_id],
  xscp.[placed_xml_component_id],
  xscp.[is_default_fixed],
  xscp.[min_occurences],
  xscp.[max_occurences],
  xscp.[default_value]
FROM
  [sys].[xml_schema_component_placements] xscp
```

Columns and interpretation

- `xml_component_id` (int): Id of the component that has placements (e.g., a complex type or model group).
- `placement_id` (int): Unique id for the placement entry.
- `placed_xml_component_id` (int): The xml component id that is placed (e.g., element or attribute id).
- `is_default_fixed` (bit): Whether the default value at this placement is fixed.
- `min_occurences` (int): Minimum occurrences allowed at this placement (minOccurs).
- `max_occurences` (int): Maximum occurrences allowed at this placement (maxOccurs); may be large sentinel for unbounded.
- `default_value` (nvarchar?): Default value at this placement, if any.

How to interpret

- Use placement rows to reconstruct content model definitions for types: which child elements/attributes appear, their multiplicity and defaulting behavior.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = XmlSchemaComponentPlacementsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new XmlSchemaComponentPlacementsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Component:{r.XmlComponentId} Placed:{r.PlacedXmlComponentId} Min:{r.MinOccurences} Max:{r.MaxOccurences} Default:{r.DefaultValue}");
```

See also:

- [sys.xml_schema_component_placements](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-xml-schema-component-placements)
