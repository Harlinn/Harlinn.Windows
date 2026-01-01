# SysobjectsReader

Overview

`SysobjectsReader` wraps `sys.sysobjects` (legacy) and exposes information about objects in the database (tables, views, procedures, etc.).

Reader SQL

```
SELECT
  s43.[Name],
  s43.[Id],
  s43.[Xtype],
  s43.[Uid],
  s43.[Info],
  s43.[Status],
  s43.[base_schema_ver],
  s43.[Replinfo],
  s43.[parent_obj],
  s43.[Crdate],
  s43.[Ftcatid],
  s43.[schema_ver],
  s43.[stats_schema_ver],
  s43.[Type],
  s43.[Userstat],
  s43.[Sysstat],
  s43.[Indexdel],
  s43.[Refdate],
  s43.[Version],
  s43.[Deltrig],
  s43.[Instrig],
  s43.[Updtrig],
  s43.[Seltrig],
  s43.[Category],
  s43.[Cache]
FROM
  [sys].[sysobjects] s43
```

Columns and interpretation

- `Name` (string): Object name.
- `Id` (int): Object id.
- `Xtype` (string): Extended type or object type code (single-character code in legacy systems indicating table, view, procedure, etc.).
- `Uid` (smallint?): Owner user id.
- `Info` (smallint?): Internal info bits about the object.
- `Status` (int?): Status bitmask describing object properties.
- `base_schema_ver` (int?): Base schema version for the object (internal versioning).
- `Replinfo` (int?): Replication-related information.
- `parent_obj` (int): Parent object id (used for objects like constraints referencing a parent object).
- `Crdate` (datetime): Object creation date.
- `Ftcatid` (smallint?): Full-text catalog id associated with object.
- `schema_ver` (int?): Schema version for the object.
- `stats_schema_ver` (int?): Statistics schema version.
- `Type` (string?): Object type description or code.
- `Userstat` (smallint?): User status bits.
- `Sysstat` (smallint?): System status bits.
- `Indexdel` (smallint?): Index delete flag or count.
- `Refdate` (datetime): Reference date (internal use).
- `Version` (int?): Object version number.
- `Deltrig` (int?): Number of delete triggers or flag.
- `Instrig` (int?): Number of insert triggers or flag.
- `Updtrig` (int?): Number of update triggers or flag.
- `Seltrig` (int?): Number of select triggers or flag.
- `Category` (int?): Category code.
- `Cache` (smallint?): Cache-related flag or small counter.

How to interpret

- Prefer modern catalog views like `sys.objects`, `sys.schemas`, `sys.triggers`, and `sys.indexes` for clearer semantics; `sys.sysobjects` is a legacy compatibility view.
- `Xtype` and `Type` can be used to distinguish object kinds (e.g., 'U' = user table, 'V' = view, 'P' = stored procedure).

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysobjectsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysobjectsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Object:{r.Name} Id:{r.Id} Type:{r.Xtype} Created:{r.Crdate}");
```

See also:

- [sys.sysobjects](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysobjects)
