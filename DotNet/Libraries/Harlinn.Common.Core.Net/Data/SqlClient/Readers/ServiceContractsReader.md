# ServiceContractsReader

Overview

`ServiceContractsReader` wraps `sys.service_contracts` and exposes service contract metadata for Service Broker.

Reader SQL

```
SELECT
  sc1.[Name],
  sc1.[service_contract_id],
  sc1.[principal_id]
FROM
  [sys].[service_contracts] sc1
```

Columns and interpretation

- `Name` (string): Contract name.
- `service_contract_id` (int): Contract identifier.
- `principal_id` (int?): Principal id associated with the contract (owner/principal to enforce permissions).

How to interpret

- Contracts define permitted message flows between services; `principal_id` helps determine ownership and permissions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServiceContractsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServiceContractsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Contract:{r.Name} Id:{r.ServiceContractId} Principal:{r.PrincipalId}");
```

See also:

- [sys.service_contracts](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-service-contracts)
