# ColumnStoreDictionariesReader — reference

Overview

`ColumnStoreDictionariesReader` wraps `sys.column_store_dictionaries` and exposes metadata about dictionaries used by columnstore indexes (per-partition).

Reader SQL

```
SELECT scsd.[partition_id]
      ,scsd.[hobt_id]
      ,scsd.[column_id]
      ,scsd.[dictionary_id]
      ,scsd.[version]
      ,scsd.[type]
      ,scsd.[last_id]
      ,scsd.[entry_count]
      ,scsd.[on_disk_size]
FROM [AdventureWorks2019].[sys].[column_store_dictionaries] scsd
```

Selected columns (method mapping and brief meaning)

- `partition_id` ? `GetPartitionId()` (int): Partition that contains the dictionary.
- `hobt_id` ? `GetHobtId()` (long): HOBT id for the columnstore object.
- `column_id` ? `GetColumnId()` (int): Column id the dictionary pertains to.
- `dictionary_id` ? `GetDictionaryId()` (long?): Dictionary identifier (may be NULL).
- `version` ? `GetVersion()` (int): Dictionary version number.
- `type` ? `GetDictionaryTypeCode()` (byte): Dictionary type code.
- `last_id` ? `GetLastId()` (long?): Last entry id in dictionary (may be NULL).
- `entry_count` ? `GetEntryCount()` (long): Number of distinct entries.
- `on_disk_size` ? `GetOnDiskSize()` (long): Space used on disk by the dictionary (bytes).

Helpers

- `GetColumnStoreDictionary()` returns a `ColumnStoreDictionary` instance for the current row.
- `GetColumnStoreDictionaries()` reads all rows and returns a list.
