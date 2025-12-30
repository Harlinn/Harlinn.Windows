# SyscacheobjectsReader

Overview

`SyscacheobjectsReader` wraps `sys.syscacheobjects` and exposes internal cache object statistics for the SQL Server engine (internal, legacy view).

Reader SQL

```
SELECT
  s25.[Bucketid],
  s25.[Cacheobjtype],
  s25.[Objtype],
  s25.[Objid],
  s25.[Dbid],
  s25.[Dbidexec],
  s25.[Uid],
  s25.[Refcounts],
  s25.[Usecounts],
  s25.[Pagesused],
  s25.[Setopts],
  s25.[Langid],
  s25.[Dateformat],
  s25.[Status],
  s25.[Lasttime],
  s25.[Maxexectime],
  s25.[Avgexectime],
  s25.[Lastreads],
  s25.[Lastwrites],
  s25.[Sqlbytes],
  s25.[Sql]
FROM
  [sys].[syscacheobjects] s25
```

Columns and interpretation

- `Bucketid` (int): Internal bucket id used by cache structures.
- `Cacheobjtype` (string): Cache object type (e.g., SQL, procedure).
- `Objtype` (string): Specific object type.
- `Objid`, `Dbid`, `Dbidexec`, `Uid` (int/short?): Identifiers for object, database, execution database, and user context.
- `Refcounts`, `Usecounts` (int): Reference and usage counters.
- `Pagesused` (int?): Number of pages used by the cached object.
- `Setopts` (int?): SET options used when creating the cached plan.
- `Langid`, `Dateformat` (short?): Language and dateformat context ids.
- `Status` (int?): Status flags for the cache entry.
- `Lasttime`, `Maxexectime`, `Avgexectime`, `Lastreads`, `Lastwrites` (long?): Performance metrics and timestamps.
- `Sqlbytes` (int?): Size of the SQL text in bytes.
- `Sql` (string?): The cached SQL text.

How to interpret

- This view provides engine-level cached plan information. `Refcounts` and `Usecounts` help identify frequently used cached objects. `Setopts` encodes session SET options that affect plan creation.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SyscacheobjectsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SyscacheobjectsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Obj:{r.Objtype} Id:{r.Objid} Uses:{r.Usecounts} LastExec:{r.Lasttime}");
```

See also:

- sys.syscacheobjects (internal/legacy) - no direct modern MSDN page; this is legacy diagnostic information
