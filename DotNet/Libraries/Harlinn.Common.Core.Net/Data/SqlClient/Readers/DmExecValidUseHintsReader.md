# DmExecValidUseHintsReader — reference

Overview

`DmExecValidUseHintsReader` wraps `sys.dm_exec_valid_use_hints` and returns optimizer use-hints that are valid in the current server context. These are hints that can be supplied to queries to influence the optimizer's behavior.

Reader SQL

```
SELECT
  devuh.[Name]
FROM
  [sys].[dm_exec_valid_use_hints] devuh
```

Columns and interpretation

- `Name` ? `Name` (string)
  - Name of a valid use-hint (such as `USE HINT ('DISABLE_OPTIMIZER_ROWGOAL')`). Use these names when constructing `OPTION (USE HINT (...))` clauses.

How to interpret

- The set of valid hints may vary by SQL Server build and configuration. Query this DMV to determine which hints are supported on the current instance.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecValidUseHintsReader.Sql;
using var rdr = cmd.ExecuteReader();
var h = new DmExecValidUseHintsReader(rdr, ownsReader:false);
while (h.Read())
{
    Console.WriteLine($"Hint: {h.Name}");
}
```

See also:

- [sys.dm_exec_valid_use_hints](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-valid-use-hints)
