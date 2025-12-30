# DmDbScriptLevelReader — reference

Overview

`DmDbScriptLevelReader` wraps `sys.dm_db_script_level` and exposes script versioning and upgrade/downgrade level metadata for the database.

Reader SQL

```
SELECT
  ddsl.[database_id],
  ddsl.[script_id],
  ddsl.[script_name],
  ddsl.[Version],
  ddsl.[script_level],
  ddsl.[downgrade_start_level],
  ddsl.[downgrade_target_level],
  ddsl.[upgrade_start_level],
  ddsl.[upgrade_target_level]
FROM
  [sys].[dm_db_script_level] ddsl
```

Columns (detailed)

- `database_id` ? `DatabaseId` (int)
  - Database identifier for which the script level information applies.

- `script_id` ? `ScriptId` (int)
  - Identifier for the script metadata record.

- `script_name` ? `ScriptName` (string?)
  - Name/title of the script or component.

- `Version` ? `Version` (int)
  - Numeric version of the script/component.

- `script_level` ? `ScriptLevel` (int)
  - Operational level value representing the applied level for the script.

- `downgrade_start_level` / `downgrade_target_level` ? (int)
  - Levels used when performing downgrades.

- `upgrade_start_level` / `upgrade_target_level` ? (int?)
  - Levels used for upgrades; may be null if not applicable.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbScriptLevelReader.Sql;
using var reader = cmd.ExecuteReader();
var sReader = new DmDbScriptLevelReader(reader, ownsReader: false);
while (sReader.Read())
{
    Console.WriteLine($"DB: {sReader.DatabaseId} Script: {sReader.ScriptName} v{sReader.Version} Level: {sReader.ScriptLevel}");
}
```

See also:

- [sys.dm_db_script_level](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-script-level)
