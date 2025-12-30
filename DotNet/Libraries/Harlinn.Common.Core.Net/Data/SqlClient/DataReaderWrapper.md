# `DataReaderWrapper` documentation

## Overview
`DataReaderWrapper` is a thin, robust wrapper around `Microsoft.Data.SqlClient.SqlDataReader` that implements `System.Data.IDataReader`. It centralizes safe access to a `SqlDataReader` by:

- catching and logging exceptions from underlying reader calls,
- exposing many typed `Get` helpers and nullable variants,
- providing convenience conversions (e.g. enums, CLR spatial/SQL types),
- controlling disposal of the wrapped reader via an `ownsReader` flag.

The class is intended as a base for typed "Reader" wrappers (e.g. `ComputedColumnsReader`, `FirstResultSetReader`) that map resultset columns to domain types.

## Key constructors
- `DataReaderWrapper(ILoggerFactory loggerFactory, SqlDataReader sqlDataReader, bool ownsReader = true)`  
  Creates wrapper and obtains a logger from `loggerFactory`.
- `DataReaderWrapper(SqlDataReader sqlDataReader, bool ownsReader = true)`  
  Creates wrapper with a `NullLogger` (no logging).
- `DataReaderWrapper(ILogger logger, SqlDataReader sqlDataReader, bool ownsReader = true)`  
  Creates wrapper using explicit `ILogger`.

Parameter `ownsReader` controls whether the wrapper will close/dispose the underlying `SqlDataReader` when the wrapper is disposed.

## Disposal behavior
- Implements `IDisposable`. Calling `Dispose()` invokes `OnDispose()` which calls `DisposeDataReader()` when `_ownsReader` is true.
- `DisposeDataReader()` closes and disposes the underlying `SqlDataReader` (safely guarded).
- Exceptions during disposal are logged and rethrown.

## Logging and error handling
- Exceptions from any reader operation are caught, passed to `LogException(Exception, callerMethodName)` and rethrown.
- Logging uses the provided `ILogger` (or `NullLogger` if none).
- In DEBUG with a debugger attached, `LogException` will break into the debugger.

## Important protected members / extensibility
- `protected bool OwnsReader { get; set; }` — indicates whether wrapper owns the reader.
- `protected void SetDataReader(SqlDataReader reader, bool ownsReader = true)` — replace underlying reader and ownership flag.

Derived typed readers typically call the wrapper's typed `GetX` helpers to read column values by ordinal.

## Implemented `IDataReader` / `IDataRecord` surface
Implements common members and forwards to `_reader` with logging:
- Cursor/control: `Read()`, `NextResult()`, `Close()`, `IsClosed`, `RecordsAffected`, `Depth`.
- Schema: `GetSchemaTable()`, `FieldCount`, `GetName(int)`, `GetOrdinal(string)`, `GetDataTypeName(int)`, `GetFieldType(int)`.
- Indexers: `this[int]`, `this[string]`.
- Generic value access: `GetValue(int)`, `GetValues(object[])`, `IsDBNull(int)`.

## Typed helper getters (not exhaustive)
Use these to read columns by ordinal safely:
- Primitive / CLR types: `GetBoolean`, `GetSByte`, `GetByte`, `GetInt16`, `GetInt32`, `GetInt64`, `GetSingle` / `GetFloat`, `GetDouble`, `GetDecimal`, `GetDateTime`, `GetString`, `GetGuid`, `GetTimeSpan` (stored as ticks).
- Nullable variants: `GetNullableBoolean`, `GetNullableSByte`, `GetNullableByte`, `GetNullableInt16`, `GetNullableInt32`, `GetNullableInt64`, `GetNullableSingle`, `GetNullableDouble`, `GetNullableDecimal`, `GetNullableDateTime`, `GetNullableString`, `GetNullableGuid`, `GetNullableTimeSpan`, etc.
- Binary helpers: `GetBytes(int)` (returns full byte[]), `GetBytes(...)` overload, `GetNullableBytes(int)`, `GetBinary(int)`, `GetNullableBinary(int)`.
- Enum helper: `GetEnum<T>(int)` and `GetNullableEnum<T>(int)` — maps underlying numeric DB value to enum type with correct underlying integer sizes.
- SQL CLR / specialized types:
  - `GetSqlHierarchyId(int)` / `GetNullableSqlHierarchyId(int)`
  - `GetSqlGeometry(int)` / `GetNullableSqlGeometry(int)`
  - `GetSqlGeography(int)` / `GetNullableSqlGeography(int)`
  - `GetSqlXml(int)` / `GetNullableSqlXml(int)`
- Other helpers: `GetData(int)`, `GetDataTypeName(int)`, `GetFieldType(int)`, `GetTimestamp(int)` (alias for `GetInt64`), `GetNullableTimestamp(int)`.

All helpers check `IsDBNull` where appropriate and log & rethrow any exceptions.

## Notable behaviors / gotchas
- `GetTimeSpan(int)` expects the stored value to be an `Int64` tick count and constructs a `TimeSpan` from it.
- `GetUInt32` / `GetUInt64` use `GetDecimal` conversions and `unchecked` casts — be careful with large unsigned values.
- Spatial/UDT getters rely on provider returning the correct SQL CLR types via `GetSqlValue`.
- `GetEnum<T>` uses the enum's underlying integral type to select the correct reader method; if mapping is unexpected, validate DB column type and ordinal.
- All methods rethrow exceptions after logging; callers should handle exceptions as needed.

## Typical usage examples

Create wrapper and read rows (commonly used by generated typed readers):

```csharp
// C# example (not a file target)
using var cmd = connection.CreateCommand("SELECT ...");
using var rdr = cmd.ExecuteReader();
var wrapper = new DataReaderWrapper(rdr, ownsReader: true);
while (wrapper.Read())
{
    int id = wrapper.GetInt32(0);
    string? name = wrapper.GetNullableString(1);
    // ...
}
```

In derived reader:

```csharp
public int GetObjectId() => GetInt32(ObjectIdOrdinal);
public string? GetCollationName() => GetNullableString(CollationNameOrdinal);
```

## When to extend / override
- Override `LogException` or provide a logger in constructor to customize logging behavior.
- Use `SetDataReader` to rebind to a different `SqlDataReader` instance.
- Override disposal semantics by deriving and overriding `OnDispose` / `DisposeDataReader`.

## Summary
`DataReaderWrapper` centralizes safe, logged access to `SqlDataReader` and provides many typed 
helpers and nullable variants that make implementing typed resultset readers straightforward and 
consistent. It is designed for defensive use: exceptions are logged and rethrown, disposal is 
controlled by `ownsReader`, and the class exposes convenient helpers for SQL CLR and 
specialized SQL types.
