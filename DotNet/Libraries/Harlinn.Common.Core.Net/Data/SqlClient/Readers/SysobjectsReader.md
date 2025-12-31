# SysobjectsReader

Reads rows from the `sys.sysobjects` compatibility view. This view lists objects (tables, views, procedures, etc.) and metadata.

Columns and interpretation:

- `Name` (string)
  - Description: Name of the object.
  - Interpretation: Object name within the database.
- `Id` (int)
  - Description: Object id.
  - Interpretation: Unique identifier for the object.
- `Xtype` (string)
  - Description: Object type code (e.g., 'U' = user table, 'V' = view, 'P' = stored procedure).
  - Interpretation: Short code describing object type.
- `Uid` (short?, nullable)
  - Description: Owner user id.
  - Interpretation: Maps to database principal id.
- `Info` (short?, nullable)
  - Description: Probably/guesswork: info flags about object.
  - Interpretation: Internal metadata.
- `Status` (int?, nullable)
  - Description: Status flags for the object.
  - Interpretation: Bitmask for object properties.
- `base_schema_ver` (int?, nullable)
  - Description: Probably/guesswork: schema base version.
  - Interpretation: Internal schema tracking.
- `Replinfo` (int?, nullable)
  - Description: Replication related info.
  - Interpretation: Flags or ids used by replication.
- `parent_obj` (int)
  - Description: Parent object id if applicable (e.g., constraint on table)
  - Interpretation: The id of the container object.
- `Crdate` (DateTime)
  - Description: Creation date of the object.
  - Interpretation: Timestamp when object was created.
- `Ftcatid` (short?, nullable)
  - Description: Full-text catalog id related to the object.
  - Interpretation: If object participates in full-text indexing.
- `schema_ver` (int?, nullable)
  - Description: Schema version for the object.
  - Interpretation: Internal versioning for schema changes.
- `stats_schema_ver` (int?, nullable)
  - Description: Statistics schema version.
  - Interpretation: Internal stats version.
- `Type` (string?, nullable)
  - Description: Possibly human-readable object type.
  - Interpretation: Longer type description.
- `Userstat` (short?, nullable)
  - Description: Probably/guesswork: user-level status flags.
- `Sysstat` (short?, nullable)
  - Description: Probably/guesswork: system-level status flags.
- `Indexdel` (short?, nullable)
  - Description: Probably/guesswork: index delete flag.
- `Refdate` (DateTime)
  - Description: Date reference updated or last referenced.
  - Interpretation: Internal timestamp.
- `Version` (int?, nullable)
  - Description: Object version.
  - Interpretation: Internal version number.
- Trigger fields: `Deltrig`, `Instrig`, `Updtrig`, `Seltrig` (int?, nullable)
  - Description: Counts or flags for triggers assigned to the object.
  - Interpretation: Non-zero indicates triggers are present.
- `Category` (int?, nullable)
  - Description: Category id used to group objects.
- `Cache` (short?, nullable)
  - Description: Probably/guesswork: caching flags for object.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysobjectsReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysobjectsReader(reader);
while (r.Read())
{
    Console.WriteLine($"{r.Name} (id={r.Id}) type={r.Xtype} owner={r.Uid} created={r.Crdate}");
}
```

See also:
- [sys.sysobjects](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysobjects-transact-sql)
