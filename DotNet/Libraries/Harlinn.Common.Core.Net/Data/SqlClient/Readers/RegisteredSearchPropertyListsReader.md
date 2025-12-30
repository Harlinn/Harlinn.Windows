# RegisteredSearchPropertyListsReader

Overview

`RegisteredSearchPropertyListsReader` wraps `sys.registered_search_property_lists` and exposes registered property list definitions used by search features.

Reader SQL

```
SELECT
  rspl.[property_list_id],
  rspl.[Name],
  rspl.[create_date],
  rspl.[modify_date],
  rspl.[principal_id]
FROM
  [sys].[registered_search_property_lists] rspl
```

Columns and interpretation

- `property_list_id` (int): Unique identifier for the property list.
- `Name` (string): Name of the property list.
- `create_date` (DateTime): Creation timestamp for the list.
- `modify_date` (DateTime): Last modification timestamp for the list.
- `principal_id` (int?): Owner principal id of the object, if any.

How to interpret

- Property lists group multiple registered search properties. Use `property_list_id` when joining to the properties view.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = RegisteredSearchPropertyListsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new RegisteredSearchPropertyListsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"List:{r.PropertyListId} Name:{r.Name} Created:{r.CreateDate}");
}
```

See also:

- [sys.registered_search_property_lists](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-registered-search-property-lists)

