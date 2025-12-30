# `SqlParameterCollectionExtensions` documentation

## Overview
`SqlParameterCollectionExtensions` provides strongly-typed helper extension methods for `SqlParameterCollection` to simplify creating `SqlParameter` instances for common CLR types, enums, UDTs (spatial / hierarchyid), XML and `sql_variant`. The helpers avoid repeated `AddWithValue` calls and ensure correct `SqlDbType`, sizing and `ParameterDirection`.

All methods:
- Return the created `SqlParameter` (already added to the collection).
- Offer input and output overloads when applicable.
- Use `DBNull.Value` when passing `null` values.

## General usage pattern
1. Create a `SqlCommand` and set `CommandType` and `CommandText`.
2. Call extension methods on `command.Parameters` to add input or output parameters.
3. Execute the command (`ExecuteNonQuery`, `ExecuteReader`, `ExecuteScalar`).
4. Read output parameters from `command.Parameters[...]` and check for `DBNull.Value` before casting.

Example (pattern):
```
using var cmd = new SqlCommand("usp_DoWork", connection) { CommandType = CommandType.StoredProcedure };
cmd.Parameters.AddInt32("@id", 42);
cmd.Parameters.AddNVarChar("@name", "Alice");
cmd.Parameters.AddInt32("@result", ParameterDirection.Output);

cmd.ExecuteNonQuery();

var result = cmd.Parameters["@result"].Value == DBNull.Value ? (int?)null : (int)cmd.Parameters["@result"].Value;
```

## Supported types (high level)
- Boolean: `AddBoolean`
- Signed/unsigned integers: `AddSByte`, `AddByte`, `AddInt16`, `AddUInt16`, `AddInt32`, `AddUInt32`, `AddInt64`, `AddUInt64`
- Floating / decimal: `AddSingle`, `AddDouble`, `AddDecimal`
- Date/time: `AddDateTime`, `AddDateTimeAsInt64`, `AddDateTimeOffset`
- TimeSpan: `AddTimeSpan`, `AddTimeSpanAsInt64`
- Guid: `AddGuid`, `AddReference` (treats `Guid.Empty` as NULL for input)
- Enum: `AddEnum<T>` (chooses `SqlDbType` from enum underlying type)
- Character / string: `AddChar`, `AddNChar`, `AddVarChar`, `AddNVarChar`
- Binary: `AddBinary` (sized and varbinary overloads)
- Currency: `AddCurrency` (project-specific `Currency` → scaled `bigint`)
- Spatial / UDTs: `AddHierarchyId`, `AddSqlGeometry`, `AddSqlGeography` (use `SqlDbType.Udt` + `UdtTypeName`)
- XML: `AddSqlXml` (accepts `SqlXml` or `string`)
- Variant: `AddSqlVariant` (maps to `SqlDbType.Variant`)

## Examples — representative usages

Primitive input + output:
```
cmd.Parameters.AddInt32("@count", 5);
cmd.Parameters.AddInt32("@countOut", ParameterDirection.Output);

cmd.Parameters.AddBoolean("@flag", true);
cmd.Parameters.AddBoolean("@flagOut", ParameterDirection.Output);

cmd.ExecuteNonQuery();

int? countOut = cmd.Parameters["@countOut"].Value == DBNull.Value ? null : (int?)cmd.Parameters["@countOut"].Value;
bool? flagOut = cmd.Parameters["@flagOut"].Value == DBNull.Value ? null : (bool?)cmd.Parameters["@flagOut"].Value;
```

Enum:
```
enum Status : byte { Unknown = 0, Active = 1 }

cmd.Parameters.AddEnum<Status>("@status", Status.Active);
cmd.Parameters.AddEnum<Status>("@statusOut", ParameterDirection.Output);

cmd.ExecuteNonQuery();
object raw = cmd.Parameters["@statusOut"].Value;
Status? statusOut = raw == DBNull.Value ? (Status?)null : (Status)Convert.ToByte(raw);
```

String with sizing:
```
cmd.Parameters.AddNVarChar("@title", "Hello", 200);
cmd.Parameters.AddNVarChar("@titleOut", 200, ParameterDirection.Output);
```

Binary (sized / varbinary):
```
cmd.Parameters.AddBinary("@data", bytes, 1024);     // fixed/var
cmd.Parameters.AddBinary("@dataOut", 8000, ParameterDirection.Output);

// read:
var binOut = cmd.Parameters["@dataOut"].Value == DBNull.Value ? null : (byte[])cmd.Parameters["@dataOut"].Value;
```

UDT / spatial / hierarchyid:
```
// requires Microsoft.SqlServer.Types and server-side type available
SqlHierarchyId hid = SqlHierarchyId.Parse("/1/2/");
cmd.Parameters.AddHierarchyId("@node", hid);
cmd.Parameters.AddHierarchyId("@nodeOut", ParameterDirection.Output);

SqlGeometry geom = SqlGeometry.Point(1,2,0);
cmd.Parameters.AddSqlGeometry("@geom", geom);
cmd.Parameters.AddSqlGeometry("@geomOut", ParameterDirection.Output);

cmd.ExecuteNonQuery();

var nodeOut = cmd.Parameters["@nodeOut"].Value == DBNull.Value ? null : (SqlHierarchyId)cmd.Parameters["@nodeOut"].Value;
var geomOut = cmd.Parameters["@geomOut"].Value == DBNull.Value ? null : (SqlGeometry)cmd.Parameters["@geomOut"].Value;
```

XML:
```
cmd.Parameters.AddSqlXml("@xmlIn", "<root/>");
cmd.Parameters.AddSqlXml("@xmlOut", ParameterDirection.Output);
cmd.ExecuteNonQuery();

var xmlOutRaw = cmd.Parameters["@xmlOut"].Value;
string? xmlText = xmlOutRaw == DBNull.Value ? null : (xmlOutRaw is System.Data.SqlTypes.SqlXml sx ? sx.Value : xmlOutRaw as string);
```

`sql_variant`:
```
cmd.Parameters.AddSqlVariant("@varIn", 123);
cmd.Parameters.AddSqlVariant("@varOut", ParameterDirection.Output);

cmd.ExecuteNonQuery();
object? variant = cmd.Parameters["@varOut"].Value == DBNull.Value ? null : cmd.Parameters["@varOut"].Value;
```

## Reading outputs — best practices
- Always check `Parameter.Value == DBNull.Value` before casting.
- UDTs and spatial types are returned as provider CLR types (e.g. `SqlGeometry`, `SqlGeography`, `SqlHierarchyId`) — cast accordingly.
- `AddReference` will store `Guid.Empty` as `DBNull.Value` for input overload that accepts `Guid`.
- Enum outputs are returned as integral CLR types — convert using `Convert`/`Enum.ToObject` or cast after converting to the underlying numeric type.

## Notes / gotchas
- These helpers choose `SqlDbType` based on the logical CLR type; when a more specific SQL type is required (precision/scale for `decimal`, `VarChar` vs `NVarChar`, etc.) prefer constructing a `SqlParameter` manually.
- For large binary/text values use the varbinary/nvarchar overloads (size = `-1` internally).
- UDT usage requires the server type (`hierarchyid`, `geometry`, `geography`) to be available and the `Microsoft.SqlServer.Types` provider on the client.
- `AddDateTimeAsInt64` and `AddTimeSpan` store ticks as `bigint` — convert back on read.

## Reference
- Source: `DotNet\Libraries\Harlinn.Common.Core.Net\Data\SqlClient\SqlParameterCollectionExtensions.cs`
- See also: `DataReaderWrapper` for typed readers that consume corresponding parameter/column types.


## `AddBoolean`

- Signatures:
  - `AddBoolean(this SqlParameterCollection self, string parameterName, bool? value, ParameterDirection parameterDirection = ParameterDirection.Input)`
  - `AddBoolean(this SqlParameterCollection self, string parameterName, bool value, ParameterDirection parameterDirection = ParameterDirection.Input)`
  - `AddBoolean(this SqlParameterCollection self, string parameterName, ParameterDirection parameterDirection = ParameterDirection.Output)`

Examples:

```
// input (nullable)
command.Parameters.AddBoolean("@isActive", (bool?)true);

// input (non-nullable)
command.Parameters.AddBoolean("@isActive", true);

// output
command.Parameters.AddBoolean("@isActiveOut", ParameterDirection.Output);
command.ExecuteNonQuery();
var isActiveOut = command.Parameters["@isActiveOut"].Value == DBNull.Value ? (bool?)null : (bool)command.Parameters["@isActiveOut"].Value;
```

## `AddSByte`

- Signatures:
  - `AddSByte(this SqlParameterCollection self, string parameterName, sbyte? value, ParameterDirection parameterDirection = ParameterDirection.Input)`
  - `AddSByte(this SqlParameterCollection self, string parameterName, sbyte value, ParameterDirection parameterDirection = ParameterDirection.Input)`
  - `AddSByte(this SqlParameterCollection self, string parameterName, ParameterDirection parameterDirection = ParameterDirection.Output)`

Examples:

```
// input (nullable)
command.Parameters.AddSByte("@smallSigned", (sbyte?)-5);

// input (non-nullable)
command.Parameters.AddSByte("@smallSigned", (sbyte)10);

// output
command.Parameters.AddSByte("@smallSignedOut", ParameterDirection.Output);
command.ExecuteNonQuery();
var smallSignedOut = command.Parameters["@smallSignedOut"].Value == DBNull.Value ? (sbyte?)null : unchecked((sbyte)(byte)command.Parameters["@smallSignedOut"].Value);
```
## `AddByte`

- Signatures analogous to `AddSByte` but for `byte`.

Examples:

```
// input
command.Parameters.AddByte("@tiny", (byte)200);

// output
command.Parameters.AddByte("@tinyOut", ParameterDirection.Output);
command.ExecuteNonQuery();
var tinyOut = command.Parameters["@tinyOut"].Value == DBNull.Value ? (byte?)null : (byte)command.Parameters["@tinyOut"].Value;
```
## `AddInt16` / `AddUInt16`

- `AddInt16` signatures for `short`
- `AddUInt16` signatures for `ushort` (mapped to `SmallInt` with cast)

Examples:

```
// Int16 input
command.Parameters.AddInt16("@s16", (short)123);

// Int16 output
command.Parameters.AddInt16("@s16Out", ParameterDirection.Output);

// UInt16 input
command.Parameters.AddUInt16("@u16", (ushort)456);

// UInt16 output
command.Parameters.AddUInt16("@u16Out", ParameterDirection.Output);
```

Read outputs similarly, checking `DBNull.Value` and unboxing to `short` or `ushort`.

## `AddInt32` / `AddUInt32`

- `AddInt32` for `int`
- `AddUInt32` stores `uint` as `int` (unchecked cast)

Examples:

```
// input
command.Parameters.AddInt32("@id", 42);

// output
command.Parameters.AddInt32("@idOut", ParameterDirection.Output);

// uint input
command.Parameters.AddUInt32("@uid", (uint)123);

// uint output
command.Parameters.AddUInt32("@uidOut", ParameterDirection.Output);
```

Read outputs by casting to `int` and converting if needed to `uint` with `unchecked`.

## `AddInt64` / `AddUInt64`

- `AddInt64` for `long`
- `AddUInt64` maps `ulong` to `bigint` with unchecked cast

Examples:

```
// input
command.Parameters.AddInt64("@big", 123456789L);

// output
command.Parameters.AddInt64("@bigOut", ParameterDirection.Output);

// ulong input (stored as BigInt)
command.Parameters.AddUInt64("@ubig", 9876543210UL);

// output
command.Parameters.AddUInt64("@ubigOut", ParameterDirection.Output);
```
## `AddSingle` / `AddDouble`

- `AddSingle` for `float`, `AddDouble` for `double`

Examples:

```
command.Parameters.AddSingle("@f", 1.23f);
command.Parameters.AddSingle("@fOut", ParameterDirection.Output);

command.Parameters.AddDouble("@d", 3.14159);
command.Parameters.AddDouble("@dOut", ParameterDirection.Output);
```
## `AddDecimal`

Examples:

```
command.Parameters.AddDecimal("@amount", 123.45m);
command.Parameters.AddDecimal("@amountOut", ParameterDirection.Output);
```

## `AddCurrency`

`Currency` is a project-specific type that is converted with `.ToScaled()` to `bigint` before sending.

Examples:

```
Currency c = new Currency(12.34m);
command.Parameters.AddCurrency("@cur", c);
command.Parameters.AddCurrency("@curOut", ParameterDirection.Output);
```
## `AddDateTime` / `AddDateTimeAsInt64` / `AddDateTimeOffset`

- `AddDateTime` maps to `DateTime2`
- `AddDateTimeAsInt64` stores `DateTime.Ticks` as `bigint`
- `AddDateTimeOffset` maps to `DateTimeOffset`

Examples:

```
var now = DateTime.UtcNow;
command.Parameters.AddDateTime("@dt", now);
command.Parameters.AddDateTime("@dtOut", ParameterDirection.Output);

command.Parameters.AddDateTimeAsInt64("@dtTicks", now);
command.Parameters.AddDateTimeAsInt64("@dtTicksOut", ParameterDirection.Output);

var dto = DateTimeOffset.Now;
command.Parameters.AddDateTimeOffset("@dto", dto);
command.Parameters.AddDateTimeOffset("@dtoOut", ParameterDirection.Output);
```

Reading `DateTimeAsInt64` outputs requires converting ticks back: `new DateTime((long)p.Value, DateTimeKind.Utc)`.

## `AddTimeSpan` / `AddTimeSpanAsInt64`

- `AddTimeSpan` stores TimeSpan as `bigint` (raw ticks)
- `AddTimeSpanAsInt64` same explicit name

Examples:

```
TimeSpan ts = TimeSpan.FromHours(2);
command.Parameters.AddTimeSpan("@ts", ts);
command.Parameters.AddTimeSpan("@tsOut", ParameterDirection.Output);

command.Parameters.AddTimeSpanAsInt64("@tsTicks", ts);
command.Parameters.AddTimeSpanAsInt64("@tsTicksOut", ParameterDirection.Output);
```

Read output ticks and create `TimeSpan` with `TimeSpan.FromTicks(...)`.

## `AddGuid` / `AddReference`

- `AddGuid` persists `Guid` as `UniqueIdentifier`.
- `AddReference` treats `Guid.Empty` as null when adding as input.

Examples:

```csharp
Guid id = Guid.NewGuid();
command.Parameters.AddGuid("@id", id);
command.Parameters.AddGuid("@idOut", ParameterDirection.Output);

command.Parameters.AddReference("@ref", (Guid?)null); // Nullable input
command.Parameters.AddReference("@refOut", ParameterDirection.Output);
```
## `AddEnum<T>`

Three overloads: nullable input, non-nullable input, and output. The method picks 
`SqlDbType` based on enum underlying type.

Examples:

```csharp
enum Status : byte { None = 0, Active = 1 }

// nullable input
command.Parameters.AddEnum<Status>("@status", (Status?)Status.Active);

// non-nullable input
command.Parameters.AddEnum<Status>("@status2", Status.Active);

// output
command.Parameters.AddEnum<Status>("@statusOut", ParameterDirection.Output);

// read output:
var raw = command.Parameters["@statusOut"].Value;
Status? statusOut = raw == DBNull.Value ? (Status?)null : (Status)(Convert.ToByte(raw));
```
## `AddChar` / `AddNChar` / `AddVarChar` / `AddNVarChar`

Character/string parameter helpers with sizing.

Examples:

```csharp
command.Parameters.AddChar("@c", "A", 1);
command.Parameters.AddChar("@cOut", 1, ParameterDirection.Output);

command.Parameters.AddNChar("@nc", "Ö", 2);
command.Parameters.AddVarChar("@v", "hello", 50);
command.Parameters.AddNVarChar("@nv", "hello nv", 100);
command.Parameters.AddNVarChar("@nvOut", 100, ParameterDirection.Output);
```

Reading string outputs:

```csharp
var s = command.Parameters["@nvOut"].Value == DBNull.Value ? null : (string)command.Parameters["@nvOut"].Value;
```

## `AddBinary`

Overloads for `byte[]` with size control and output.

Examples:

```csharp
byte[] data = new byte[] { 1, 2, 3 };
command.Parameters.AddBinary("@bin", data, 1024);      // sized
command.Parameters.AddBinary("@binVar", data);         // varbinary(-1)
command.Parameters.AddBinary("@binOut", 8000, ParameterDirection.Output);
```

Read output as `byte[]` after `ExecuteNonQuery()`:

```csharp
var pv = command.Parameters["@binOut"].Value;
var binOut = pv == DBNull.Value ? null : (byte[])pv;
```

## `AddHierarchyId`

Adds `SqlHierarchyId` UDT (`hierarchyid`) using `SqlDbType.Udt` and `UdtTypeName = "hierarchyid"`.

Examples:

```csharp
SqlHierarchyId? hid = SqlHierarchyId.Parse("/1/3/");
command.Parameters.AddHierarchyId("@node", hid);
command.Parameters.AddHierarchyId("@nodeOut", ParameterDirection.Output);

// read
var hv = command.Parameters["@nodeOut"].Value;
SqlHierarchyId? nodeOut = hv == DBNull.Value ? null : (SqlHierarchyId)hv;
```
## `AddSqlGeometry` / `AddSqlGeography`

UDT parameters for spatial types `geometry` and `geography`.

Examples:

```csharp
SqlGeometry? geom = SqlGeometry.Point(1.0, 2.0, 0);
command.Parameters.AddSqlGeometry("@geom", geom);
command.Parameters.AddSqlGeometry("@geomOut", ParameterDirection.Output);

SqlGeography? geog = SqlGeography.Point(1.0, 2.0, 4326);
command.Parameters.AddSqlGeography("@geog", geog);
command.Parameters.AddSqlGeography("@geogOut", ParameterDirection.Output);
```

Read outputs with null-check and cast to `SqlGeometry` / `SqlGeography`.

## `AddSqlXml`

XML typed parameter using `SqlDbType.Xml`. Accepts `SqlXml` or `string` overload.

Examples:

```csharp
// input with string
command.Parameters.AddSqlXml("@x", "<root />");

// input with SqlXml
var sqlXml = new System.Data.SqlTypes.SqlXml(new System.IO.StringReader("<root/>"));
command.Parameters.AddSqlXml("@x2", sqlXml);

// output
command.Parameters.AddSqlXml("@xmlOut", ParameterDirection.Output);

// read
var xmlOutRaw = command.Parameters["@xmlOut"].Value;
string? xmlOut = xmlOutRaw == DBNull.Value ? null : xmlOutRaw as string;
```

Note: provider may return `SqlXml` or `string` — handle both.

---

## `AddSqlVariant`

Adds `sql_variant` parameter (flexible typed container).

Examples:

```csharp
// input with int
command.Parameters.AddSqlVariant("@v", 123);

// input with string
command.Parameters.AddSqlVariant("@v2", "hello");

// output
command.Parameters.AddSqlVariant("@vOut", ParameterDirection.Output);

// read
object? vOut = command.Parameters["@vOut"].Value == DBNull.Value ? null : command.Parameters["@vOut"].Value;
```

`sql_variant` values may arrive as CLR primitives or `Sql*` provider types; inspect and convert accordingly.

---

## Notes and best practices

- Always call `ExecuteNonQuery`, `ExecuteReader`, or `ExecuteScalar` before reading output parameters.
- When reading outputs, always test for `DBNull.Value` to detect NULL.
- For UDT/UDT-like results (`SqlGeometry`, `SqlGeography`, `SqlHierarchyId`, `SqlXml`) cast the `Parameter.Value` to the corresponding provider type; provider behavior may differ (sometimes a `byte[]` or `string` may be returned for XML).
- Use the strongly-typed `Add*` overloads to avoid `AddWithValue` pitfalls and to ensure correct `SqlDbType` is used.
- For `AddEnum<T>` outputs, the returned `Value` will be an integral CLR type — convert to the enum using `Enum.ToObject` or `Convert` and `unchecked` when necessary.
