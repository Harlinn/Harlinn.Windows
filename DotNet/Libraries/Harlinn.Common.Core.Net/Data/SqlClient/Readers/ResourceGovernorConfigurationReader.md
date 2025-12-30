# ResourceGovernorConfigurationReader

Overview

`ResourceGovernorConfigurationReader` wraps `sys.resource_governor_configuration` and exposes instance-level resource governor configuration.

Reader SQL

```
SELECT
  rgc.[classifier_function_id],
  rgc.[is_enabled],
  rgc.[max_outstanding_io_per_volume]
FROM
  [sys].[resource_governor_configuration] rgc
```

Columns and interpretation

- `classifier_function_id` (int): Identifier of the classifier function used by Resource Governor (object id of a scalar function).
- `is_enabled` (bool): Whether Resource Governor is currently enabled.
- `max_outstanding_io_per_volume` (int): Maximum outstanding I/O per volume setting.

How to interpret

- `classifier_function_id` links to a user defined function that assigns sessions to workload groups.
- `is_enabled` indicates whether resource governor policies are in effect.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ResourceGovernorConfigurationReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ResourceGovernorConfigurationReader(rdr, ownsReader:false);
if (r.Read())
{
    Console.WriteLine($"Enabled:{r.IsEnabled} ClassifierFn:{r.ClassifierFunctionId}");
}
```

See also:

- [sys.resource_governor_configuration](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-resource-governor-configuration)

