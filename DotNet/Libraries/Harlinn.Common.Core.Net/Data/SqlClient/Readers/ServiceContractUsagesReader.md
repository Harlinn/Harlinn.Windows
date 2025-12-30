# ServiceContractUsagesReader

Overview

`ServiceContractUsagesReader` wraps `sys.service_contract_usages` and exposes which services use which contracts.

Reader SQL

```
SELECT
  scu.[service_id],
  scu.[service_contract_id]
FROM
  [sys].[service_contract_usages] scu
```

Columns and interpretation

- `service_id` (int): Identifier of the service using the contract.
- `service_contract_id` (int): Identifier of the contract in use.

How to interpret

- Join `service_id` to `sys.services` to find the service names that participate in the contract.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServiceContractUsagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServiceContractUsagesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Service:{r.ServiceId} Contract:{r.ServiceContractId}");
```

See also:

- [sys.service_contract_usages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-service-contract-usages)
