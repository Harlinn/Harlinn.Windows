# DatabasesReader — reference

Overview

`DatabasesReader` wraps `sys.databases` and exposes a comprehensive set of database properties, options, and state information.

Reader SQL

The reader selects many columns from `sys.databases` (see SQL in source). It joins no other views.

Selected columns (method mapping and brief meaning)

For brevity only a selection is shown; full column-to-method mapping exists in the class.

- `name` ? `GetName()` (string)
  - Database logical name.

- `database_id` ? `GetDatabaseId()` (int)
  - Database identifier.

- `source_database_id` ? `GetSourceDatabaseId()` (int?)
  - If database was created from a source, that source database id.

- `owner_sid` ? `GetOwnerSid()` (byte[])
  - Binary SID of database owner.

- `create_date` ? `GetCreateDate()` (DateTime)
  - Creation timestamp.

- `compatibility_level` ? `GetCompatibilityLevel()` (byte)
  - Database compatibility level.

- `collation_name` ? `GetCollationName()` (string?)
  - Default collation for database.

- `user_access` / `user_access_desc` ? `GetUserAccess()` / `GetUserAccessDesc()`
  - Access restriction for the database (SINGLE_USER/RESTRICTED_USER/MULTI_USER).

- `is_read_only` ? `GetIsReadOnly()` (bool)
  - Indicates if database is read-only.

- `state` / `state_desc` ? `GetState()` / `GetStateDesc()`
  - Operational state (ONLINE, RESTORING, RECOVERING etc.).

- `is_query_store_on` ? `GetIsQueryStoreOn()` (bool)
  - Whether Query Store is enabled.

- `service_broker_guid` ? `GetServiceBrokerGuid()` (Guid)
  - Service Broker GUID for the database.

- `is_encrypted` ? `GetIsEncrypted()` (bool)
  - Database encryption (TDE) flag.

- `replica_id`, `group_database_id` ? availability group related GUIDs.

- `physical_database_name` ? `GetPhysicalDatabaseName()` (string)
  - Physical file location or name for the database.

- Many additional options exposed: auto-create/update stats, ANSI settings, full-text, temporal, memory-optimized, etc.

Helpers

- `GetDatabase()` converts current row into a `Types.Database` object with all properties.
- `GetDatabases()` reads all rows and returns list of `Types.Database`.

Note: For exact SQL Server column semantics consult Microsoft Docs for `sys.databases`.
