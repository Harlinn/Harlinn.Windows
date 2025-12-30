# ServiceContractMessageUsagesReader

Overview

`ServiceContractMessageUsagesReader` wraps `sys.service_contract_message_usages` and exposes which message types are used by service contracts and the direction (initiator/target).

Reader SQL

```
SELECT
  scmu.[service_contract_id],
  scmu.[message_type_id],
  scmu.[is_sent_by_initiator],
  scmu.[is_sent_by_target]
FROM
  [sys].[service_contract_message_usages] scmu
```

Columns and interpretation

- `service_contract_id` (int): Identifier of the service contract.
- `message_type_id` (int): Identifier of the message type used by the contract.
- `is_sent_by_initiator` (bool): True when messages of this type are sent by the initiator role.
- `is_sent_by_target` (bool): True when messages of this type are sent by the target role.

How to interpret

- These rows define which messages are permitted under a contract and who can send them. Use to validate service choreography.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServiceContractMessageUsagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServiceContractMessageUsagesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Contract:{r.ServiceContractId} MessageType:{r.MessageTypeId} Initiator:{r.IsSentByInitiator} Target:{r.IsSentByTarget}");
```

See also:

- [sys.service_contract_message_usages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-service-contract-message-usages)
