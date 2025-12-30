# AllocationUnitsReader — reference

Overview

`AllocationUnitsReader` wraps a query on `sys.allocation_units` and exposes storage allocation metrics for allocation units (an internal allocation granularity in SQL Server representing parts of index/storage structures).

Reader SQL

```
SELECT sau.[allocation_unit_id]
    ,sau.[type]
    ,sau.[type_desc]
    ,sau.[container_id]
    ,sau.[data_space_id]
    ,sau.[total_pages]
    ,sau.[used_pages]
    ,sau.[data_pages]
FROM [sys].[allocation_units] sau
```

Selected columns (property mapping and brief meaning)

- `allocation_unit_id` ? method: `GetAllocationUnitId()` (int)
  - Unique id for the allocation unit.

- `type` ? method: `GetAllocationUnitType()` (byte)
  - Allocation unit type (internal code).

- `type_desc` ? method: `GetAllocationUnitTypeDesc()` (string)
  - Text description of the allocation unit type (e.g. IN_ROW_DATA, LOB_DATA, ROW_OVERFLOW_DATA).

- `container_id` ? method: `GetContainerId()` (long)
  - Container id grouping pages belonging to the allocation unit.

- `data_space_id` ? method: `GetDataSpaceId()` (int)
  - Data space id (partition scheme or filegroup id) where pages are allocated.

- `total_pages` ? method: `GetTotalPages()` (long)
  - Total pages allocated for the allocation unit.

- `used_pages` ? method: `GetUsedPages()` (long)
  - Pages currently used.

- `data_pages` ? method: `GetDataPages()` (long)
  - Data pages count (excluding index overhead pages etc.).

Helpers

- `GetAllocationUnit()` converts the current row into a `Types.AllocationUnit` domain object.
- `GetAllocationUnits()` iterates and collects allocation units.

---
