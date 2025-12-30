# ParameterXmlSchemaCollectionUsagesReader — reference

Overview

`ParameterXmlSchemaCollectionUsagesReader` wraps `sys.parameter_xml_schema_collection_usages` and returns associations between parameters and XML schema collections used for xml validation.

Reader SQL

```
SELECT
  pxscu.[object_id],
  pxscu.[parameter_id],
  pxscu.[xml_collection_id]
FROM
  [sys].[parameter_xml_schema_collection_usages] pxscu
```

Columns and interpretation

- `object_id` — object id of the parent object (procedure/function).
- `parameter_id` — parameter ordinal id.
- `xml_collection_id` — id of the XML schema collection used for validation.

How to interpret

- When a parameter is of XML type and validated by an XML schema collection, this view links the parameter to the schema collection to allow inspection or troubleshooting of validation rules.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ParameterXmlSchemaCollectionUsagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ParameterXmlSchemaCollectionUsagesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Obj:{r.ObjectId} Param:{r.ParameterId} XmlCollectionId:{r.XmlCollectionId}");
}
```

See also:

- [sys.parameter_xml_schema_collection_usages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-parameter-xml-schema-collection-usages)
