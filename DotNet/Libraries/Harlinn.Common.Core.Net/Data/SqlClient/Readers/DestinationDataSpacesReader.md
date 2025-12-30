# DestinationDataSpacesReader — reference

Overview

`DestinationDataSpacesReader` wraps `sys.destination_data_spaces` and exposes mapping of partition scheme destinations to data spaces.

Reader SQL

```
SELECT
  dds.[partition_scheme_id],
  dds.[destination_id],
  dds.[data_space_id]
FROM
  [sys].[destination_data_spaces] dds
```

Selected columns (property mapping and brief meaning)

- `partition_scheme_id` ? `PartitionSchemeId` (int): Identifier of the partition scheme.
- `destination_id` ? `DestinationId` (int): Destination ordinal within the partition scheme.
- `data_space_id` ? `DataSpaceId` (int): Data space id (filegroup or partition scheme) assigned to the destination.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DestinationDataSpacesDataType` objects.
