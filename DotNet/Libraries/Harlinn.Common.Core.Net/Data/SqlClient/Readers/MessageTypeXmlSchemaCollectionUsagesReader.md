# MessageTypeXmlSchemaCollectionUsagesReader — reference

Overview

`MessageTypeXmlSchemaCollectionUsagesReader` wraps `sys.message_type_xml_schema_collection_usages` and returns associations between service broker message types and XML schema collections.

Reader SQL

```
SELECT
  mtxscu.[message_type_id],
  mtxscu.[xml_collection_id]
FROM
  [sys].[message_type_xml_schema_collection_usages] mtxscu
```

Columns and interpretation

- `message_type_id` — id of the message type (Service Broker message type).
- `xml_collection_id` — id of the XML schema collection associated with the message type.

How to interpret

- Use to determine which XML schema collections are referenced by message types in Service Broker to validate message bodies.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = MessageTypeXmlSchemaCollectionUsagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new MessageTypeXmlSchemaCollectionUsagesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"MessageType:{r.MessageTypeId} XmlSchemaCollection:{r.XmlCollectionId}");
}
```

See also:

- [sys.message_type_xml_schema_collection_usages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-message-type-xml-schema-collection-usages)
