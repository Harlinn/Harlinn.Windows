# SyslockinfoReader

Reads rows from the `sys.syslockinfo` compatibility view. This view contains information about locks held or requested.

Columns and interpretation:

- `rsc_text` (string)
  - Description: Textual representation of the resource being locked.
  - Interpretation: Often a human-readable identifier of the resource.
- `rsc_bin` (binary)
  - Description: Binary representation of the resource.
  - Interpretation: Internal key or resource descriptor.
- `rsc_valblk` (binary)
  - Description: Binary value block associated with the resource.
  - Interpretation: Internal engine data.
- `rsc_dbid` (short)
  - Description: Database id the resource belongs to.
  - Interpretation: Correlate with `sysdatabases`.
- `rsc_indid` (short)
  - Description: Index id if the resource is index-related.
  - Interpretation: Identifies index within object.
- `rsc_objid` (int)
  - Description: Object id of the resource.
  - Interpretation: Table or object id.
- `rsc_type` (byte)
  - Description: Resource type (e.g., page, key, object).
  - Interpretation: Encoded resource type value.
- `rsc_flag` (byte)
  - Description: Resource flag providing extra information.
  - Interpretation: Encoded flags for the resource.
- `req_mode` (byte)
  - Description: Requested lock mode (shared, update, exclusive, etc.).
  - Interpretation: Encoded lock mode value.
- `req_status` (byte)
  - Description: Request status (granted, waiting, converting, etc.).
  - Interpretation: Encoded request state.
- `req_refcnt` (short)
  - Description: Reference count for request.
  - Interpretation: Number of references to the lock request.
- `req_cryrefcnt` (short)
  - Description: Probably/guesswork: cryptic reference count used internally.
  - Interpretation: Internal count.
- `req_lifetime` (int)
  - Description: Lifetime of the lock request.
  - Interpretation: Time or counter representing how long the request has existed.
- `req_spid` (int)
  - Description: Server process id (SPID) for the requesting process.
  - Interpretation: Correlate with `sysprocesses` or activity views.
- `req_ecid` (int)
  - Description: Execution context id.
  - Interpretation: For partitioned or parallel requests.
- `req_ownertype` (short)
  - Description: Owner type for the lock (transaction, request, session).
  - Interpretation: Encoded owner type value.
- `req_transactionID` (long?, nullable)
  - Description: Transaction id if lock is transaction-scoped.
  - Interpretation: Transaction sequence number.
- `req_transactionUOW` (GUID?, nullable)
  - Description: Transaction unit-of-work GUID.
  - Interpretation: GUID identifying the transaction UOW.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SyslockinfoReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SyslockinfoReader(reader);
while (r.Read())
{
    Console.WriteLine($"spid={r.ReqSpid} type={r.RscType} mode={r.ReqMode} status={r.ReqStatus} resource={r.RscText}");
}
```

See also:
- [sys.syslockinfo](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-syslockinfo-transact-sql)
