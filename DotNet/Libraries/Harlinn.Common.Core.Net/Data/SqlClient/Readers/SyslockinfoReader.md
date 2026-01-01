# SyslockinfoReader

Overview

`SyslockinfoReader` wraps `sys.syslockinfo` (legacy) and exposes lock state and requests currently tracked by the server. This view returns a row per lock request with details about the resource and requester.

Reader SQL

```
SELECT
  s14.[rsc_text],
  s14.[rsc_bin],
  s14.[rsc_valblk],
  s14.[rsc_dbid],
  s14.[rsc_indid],
  s14.[rsc_objid],
  s14.[rsc_type],
  s14.[rsc_flag],
  s14.[req_mode],
  s14.[req_status],
  s14.[req_refcnt],
  s14.[req_cryrefcnt],
  s14.[req_lifetime],
  s14.[req_spid],
  s14.[req_ecid],
  s14.[req_ownertype],
  s14.[req_transactionID],
  s14.[req_transactionUOW]
FROM
  [sys].[syslockinfo] s14
```

Columns and interpretation

- `rsc_text` (string): Human-readable resource description (e.g., key text or page identifier).
- `rsc_bin` (binary): Binary representation of the resource identifier.
- `rsc_valblk` (binary): Resource value block (internal data about the resource value).
- `rsc_dbid` (smallint): Database id where the resource exists.
- `rsc_indid` (smallint): Index id related to the resource.
- `rsc_objid` (int): Object id of the object locked.
- `rsc_type` (byte): Resource type code (e.g., page, key, object).
- `rsc_flag` (byte): Resource attribute flags (internal meaning).
- `req_mode` (byte): Lock mode requested or held (encoded as numeric code, e.g., shared, exclusive).
- `req_status` (byte): Request status code (granted, waiting, converted, etc.).
- `req_refcnt` (smallint): Reference count for the request.
- `req_cryrefcnt` (smallint): Probably/guesswork: cryptic reference count for internal tracking.
- `req_lifetime` (int): Lifetime indicator for the request.
- `req_spid` (int): Server process id (SPID) of the requesting session.
- `req_ecid` (int): Execution context id within the session.
- `req_ownertype` (smallint): Owner type code for the request (internal categorization).
- `req_transactionID` (bigint?): Transaction id associated with the request.
- `req_transactionUOW` (uniqueidentifier?): Transaction UOW (unit of work) GUID if available.

How to interpret

- Use `req_spid` and `req_ecid` to correlate locks with sessions and execution contexts from process lists.
- Resource binary fields are internal but `rsc_text` is often useful to present a human-friendly description.
- `req_mode` and `req_status` can be mapped to known lock modes and statuses via SQL Server documentation or experimentation.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SyslockinfoReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SyslockinfoReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"SPID:{r.ReqSpid} Resource:{r.RscText} Mode:{r.ReqMode} Status:{r.ReqStatus} ObjId:{r.RscObjid}");
```

See also:

- [sys.syslockinfo](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-syslockinfo)
