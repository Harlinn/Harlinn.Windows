# ServiceMessageTypesReader

Overview

`ServiceMessageTypesReader` wraps `sys.service_message_types` and exposes message type definitions used by Service Broker.

Reader SQL

```
SELECT
  smt.[Name],
  smt.[message_type_id],
  smt.[principal_id],
  smt.[Validation],
  smt.[validation_desc],
  smt.[xml_collection_id]
FROM
  [sys].[service_message_types] smt
```

Columns and interpretation

- `Name` (string): Message type name.
- `message_type_id` (int): Identifier for the message type.
- `principal_id` (int?): Principal id associated with the message type.
- `Validation` (string): Validation type code (NONE, EMPTY, WELL_FORMED_XML, VALID_XML_WITH_SCHEMA).
- `validation_desc` (string?): Description of validation behavior.
- `xml_collection_id` (int?): For XML validated messages, id of the XML schema collection used.

How to interpret

- `Validation` indicates whether messages of this type are validated as XML and, if so, which schema is used via `xml_collection_id`.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServiceMessageTypesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServiceMessageTypesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"MessageType:{r.Name} Validation:{r.Validation} XmlCollection:{r.XmlCollectionId}");
```

See also:

- [sys.service_message_types](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-service-message-types)
