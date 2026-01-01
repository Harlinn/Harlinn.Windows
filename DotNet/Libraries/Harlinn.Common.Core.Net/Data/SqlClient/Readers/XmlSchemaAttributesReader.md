# XmlSchemaAttributesReader

Overview

`XmlSchemaAttributesReader` wraps `sys.xml_schema_attributes` and exposes metadata about attribute components defined in XML schema collections registered in the database.

Reader SQL

```
SELECT
  xsa.[xml_component_id],
  xsa.[xml_collection_id],
  xsa.[xml_namespace_id],
  xsa.[is_qualified],
  xsa.[Name],
  xsa.[symbol_space],
  xsa.[symbol_space_desc],
  xsa.[Kind],
  xsa.[kind_desc],
  xsa.[Derivation],
  xsa.[derivation_desc],
  xsa.[base_xml_component_id],
  xsa.[scoping_xml_component_id],
  xsa.[is_default_fixed],
  xsa.[must_be_qualified],
  xsa.[default_value]
FROM
  [sys].[xml_schema_attributes] xsa
```

Columns and interpretation

- `xml_component_id` (int): Unique identifier for this XML schema component (attribute) within the database.
- `xml_collection_id` (int): Identifier of the xml schema collection that contains this component. Join to `sys.xml_schema_collections`.
- `xml_namespace_id` (int): Identifier of the namespace in which the attribute is defined. Join to `sys.xml_schema_namespaces`.
- `is_qualified` (bit): Whether this component is namespace-qualified (true) or unqualified (false).
- `Name` (nvarchar): Local name of the attribute (may be NULL for anonymous or wildcard components).
- `symbol_space` (nvarchar): Symbol space name/type used by SQL Server to classify the component (internal grouping).
- `symbol_space_desc` (nvarchar?): Human readable description of the symbol space.
- `Kind` (nvarchar): Component kind code (e.g., attribute). Use `kind_desc` for readable form.
- `kind_desc` (nvarchar?): Readable description of the kind.
- `Derivation` (nvarchar): Derivation method code for type derivation (e.g., restriction, extension).
- `derivation_desc` (nvarchar?): Human readable description of the derivation method.
- `base_xml_component_id` (int?): If the attribute type is derived from another component, this is the base component id.
- `scoping_xml_component_id` (int?): Component id that scopes this attribute (e.g., complex type or element where this attribute applies).
- `is_default_fixed` (bit): Whether a default value is fixed (true for fixed defaults).
- `must_be_qualified` (bit): Whether the attribute must be namespace-qualified when used.
- `default_value` (nvarchar?): Default value for the attribute, if specified.

How to interpret

- Use `xml_component_id` to correlate other xml schema catalog views (types, elements, wildcards) that reference the same component.
- `xml_collection_id` and `xml_namespace_id` identify the collection and namespace context for the attribute.
- `is_qualified` and `must_be_qualified` describe namespace qualification rules relevant when validating XML instances.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = XmlSchemaAttributesReader.Sql;
using var rdr = cmd.ExecuteReader();
var reader = new XmlSchemaAttributesReader(rdr, ownsReader: false);
while (reader.Read())
    Console.WriteLine($"Id:{reader.XmlComponentId} Coll:{reader.XmlCollectionId} Name:{reader.Name} Qualified:{reader.IsQualified} Default:{reader.DefaultValue}");
```

See also:

- [sys.xml_schema_attributes](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-xml-schema-attributes)
