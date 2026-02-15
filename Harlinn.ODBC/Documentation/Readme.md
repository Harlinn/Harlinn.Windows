# Using `HODBC.h` with Microsoft SQL Server — Table of Contents

This guide teaches practical use of `HODBC.h` (the Harlinn ODBC C++ wrapper) 
against Microsoft SQL Server. Each chapter contains a short summary and 
key takeaways.

---

## 1. Introduction and Scope
Summary
- Overview of the library: goals, design principles and how `HODBC.h` wraps ODBC semantics.
- Target audience and prerequisites (C++20, Visual Studio, SQL Server basics).
- How this book is organized and example projects included in the repository.

Key takeaways
- Understand the wrapper's intent: safer RAII handles, `DBValue` / `FixedDB*` containers, typed enums.
- Know prerequisites and repository layout for examples.

---

## 2. ODBC and SQL Server Primer
Summary
- Quick refresher on ODBC concepts: handles, return codes, indicators (`SQLLEN`), diagnostics.
- SQL Server-specific notes relevant to ODBC (driver behaviors, `Time2`, `TIMESTAMP`/`rowversion`, `SQL_SS_*` types).

Key takeaways
- Map between ODBC primitives and `HODBC` types like `Result`, `HandleType`, `SqlType`, `NativeType`.
- Recognize SQL Server-specific types and driver quirks.

---

## 3. Getting Started: Build, Link, and Driver Setup
Summary
- How to include `HODBC.h` in a Visual Studio project and set up the MS ODBC Driver for SQL Server.
- Linker, include and runtime requirements. Setting up connection strings and DSNs.

Key takeaways
- Build steps and common linkage issues.
- Correct MS ODBC driver selection and connection string patterns for SQL Server.

---

## 4. `Environment` and `Connection` - Lifecycle and Options
Summary
- Creating and configuring an ODBC `Environment` and `Connection` via the `HODBC` wrappers.
- Connection pooling, driver version selection and `ConnectionPooling` / `Version` enums.

Key takeaways
- Use RAII-style handles; prefer `Environment` → `Connection` lifetimes.
- Choose pooling strategy and ODBC version appropriate for the application.

---

## 5. `Statement` Basics: Preparing and Executing SQL
Summary
- Creating `Statement` objects, `SQLPrepare` / `SQLExecDirect` equivalents through the wrapper.
- Execution modes and how to check `Result` codes.

Key takeaways
- Prefer prepared statements for repeated queries.
- Always check `Result` with `Succeeded()` / `Failed()` and handle diagnostics.

---

## 6. Binding Parameters: `BindParameter` and DB-aware Containers
Summary
- Parameter binding patterns, `BindParameter` overloads and typed helpers (e.g., `BindBooleanParameter`, `BindGuidParameter`).
- Using `DBValue<T>` and `FixedDB*` containers for NULL semantics and indicator pointers.

Key takeaways
- Use `DBValue<T>` aliases and `FixedDBBinary/WideString/AnsiString` to preserve NULL and indicator semantics.
- Match `NativeType` and `SqlType` to the DB column type; supply correct buffer lengths.

---

## 7. Retrieving Results: `BindColumn`, `DataReader` and `Get*` Helpers
Summary
- Column binding with `BindColumn` and convenience `Bind*Column` helpers.
- Using `DataReader` and its `AfterFetch()` pattern; on-demand retrieval vs pre-binding.
- `GetDB*` and `Get*` helpers for converting column values to C++ types.

Key takeaways
- Prefer binding fixed-size columns ahead-of-time; use `DataReader::AfterFetch()` for LOBs or on-demand retrieval.
- Handle `SQL_NULL_DATA` via `Indicator()` on DB-aware containers or by checking `DBValue::IsNull()`.

---

## 8. Working with Strings and Binary Data
Summary
- `FixedDBWideString`, `FixedDBAnsiString`, `FixedDBBinary`, `AnsiString`, `WideString`, `std::string`, `std::vector<Byte>` usage patterns.
- Byte/count semantics: wide-character lengths are returned in bytes; ANSI in bytes.
- Streaming large columns and chunked `SQLGetData` patterns.

Key takeaways
- Allocate buffers carefully and pass correct byte-length values.
- For very large objects, stream in chunks and check for `SQL_NO_TOTAL` and `SQL_SUCCESS` loop patterns.

---

## 9. Date, Time and Numeric Types
Summary
- Mapping `DateTime`, `TimeSpan`, `Time`, `Time2`, `TimeStamp`, `TimeStampOffset`, `Numeric` and `Money` to SQL Server types.
- How `DBDateTime`, `DBTime`, `DBTime2`, `DBNumeric` wrappers are used and converted.

Key takeaways
- Use the provided structs and `DBValue` wrappers to avoid manual packing/unpacking.
- Understand precision/scale and `Time2` fraction handling specific to SQL Server.

---

## 10. Transactions and Concurrency
Summary
- Transaction control via `Commit` and `Rollback` semantics; isolation and concurrency options in connection attributes.
- How to work with auto-commit vs explicit transactions using the wrapper.

Key takeaways
- Explicit transactions ensure consistent multi-statement operations.
- Handle driver-specific isolation-level behavior; always `Commit` or `Rollback` deterministically.

---

## 11. Diagnostics, Error Handling and Exceptions
Summary
- Using `Internal::GetSqlState`, `GetDiagnosticRecord` and wrapper exception helpers (`Internal::ThrowException`).
- Best practices for capturing and logging diagnostics from `SQLGetDiagRec`.

Key takeaways
- Use wrapper exception helpers for diagnostic-rich exceptions.
- Inspect `SqlState` and `DiagnosticRecord` for root causes and special cases (e.g., disconnected sessions).

---

## 12. Performance: Connection Pooling, Batch/Bulk Operations and Tuning
Summary
- Enabling connection pooling, using `BulkOperation` and array/bulk parameter binding patterns.
- Tips for tuning fetch size, cursor types, `SQL_ATTR_ROW_ARRAY_SIZE` and minimizing round-trips.

Key takeaways
- Use pooling for high-throughput apps; tune array sizes for bulk inserts/updates.
- Choose appropriate `CursorType` and `FetchOrientation` according to access patterns.

---

## 13. Advanced Topics: Descriptors, Asynchronous Operations and Bookmarks
Summary
- Using `Descriptor` for complex parameter/column metadata manipulations.
- Asynchronous execution (`CompleteAsync`) and `SQLBindParameter` advanced options.
- Bookmarks and positioned update/delete (driver dependent).

Key takeaways
- `Descriptor` gives fine-grained control for driver/statement-level metadata.
- Async and positioned operations require careful state and driver support checks.

---

## 14. Microsoft SQL Server Specific Patterns and Pitfalls
Summary
- MS SQL Server extensions: `Time2`, `TIMESTAMPOFFSET`, `GUID` treatment, `rowversion`, `SQL_SS_*` types.
- Driver behaviors: wide-vs-ANSI, NVARCHAR/NTEXT differences, and common pitfalls (e.g., `08003` disconnect state).

Key takeaways
- Use MS-specific `MsSql` types when needed and the `SqlType`/`NativeType` mappings exposed in `HODBC.h`.
- Validate driver version and test behavior for your SQL Server combination.

---

## 15. Security, Authentication and Encryption
Summary
- Authentication options (SQL auth, Windows Integrated). Configuring encrypted connections, TLS requirements.
- Secure handling of connection strings and secrets in code.

Key takeaways
- Prefer integrated auth where possible and never hard-code credentials.
- Enable encryption per company policy and confirm driver/SQL Server support.

---

## 16. Testing, Logging and Troubleshooting
Summary
- Unit-testing strategies for DB code (mocking vs integration tests), using transactions for test isolation.
- Logging patterns for SQL statements, parameters and diagnostic records.

Key takeaways
- Prefer integration tests against a disposable test DB; rollback or recreate state for repeatability.
- Log SQL and parameter values carefully (avoid secrets).

---

## 17. Example Walkthroughs
Summary
- End-to-end examples: simple query, parameterized insert, bulk insert, streaming LOB read, transaction example and async operation.
- Code snippets using the library wrappers and `DataReader` derived readers.

Key takeaways
- Concrete patterns to copy/adapt for common tasks.
- Reference implementations to validate behavior against SQL Server.

---

## 18. Migration and Interop: From Legacy ODBC and ADO.Net
Summary
- How to replace direct ODBC calls or ADO.NET patterns with `HODBC` idioms.
- Interop tips and type mapping pitfalls.

Key takeaways
- `HODBC` brings RAII and typed wrappers; map previous indicator handling to `DBValue` and `FixedDB*`.
- Test carefully when switching ownership/lifetimes of buffers.

---

## 19. Appendix: Type Maps, SQLSTATE references, and Common `HODBC` APIs
Summary
- Quick reference tables: `SqlType` ↔ SQL constants, `NativeType` mapping, `SqlState` common codes, `Result` meanings.
- Summary of frequently used `HODBC` APIs and helper patterns.

Key takeaways
- Keep the appendix handy for mapping types and diagnosing SQLSTATEs.
- Use it as a cheat-sheet while developing.

---

## 20. Troubleshooting Checklist and FAQ
Summary
- Common errors and fixes: driver not found, encoding/length mismatches, `SQL_NULL_DATA` surprises, disconnected sessions.
- FAQ for common development-time questions.

Key takeaways
- Step-by-step checklist to diagnose and resolve frequent issues.
- Practical fixes to save development time.

---

End of Table of Contents — each chapter includes examples, code snippets using `HODBC.h`, and 
recommended "gotchas" and best practices to avoid common pitfalls when working with Microsoft 
SQL Server.