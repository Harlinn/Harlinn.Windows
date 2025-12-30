# RegisteredSearchPropertiesReader

Overview

`RegisteredSearchPropertiesReader` wraps `sys.registered_search_properties`, containing metadata about registered search properties for full-text or semantic search.

Reader SQL

```
SELECT
  rsp.[property_list_id],
  rsp.[property_id],
  rsp.[property_name],
  rsp.[property_set_guid],
  rsp.[property_int_id],
  rsp.[property_description]
FROM
  [sys].[registered_search_properties] rsp
```

Columns and interpretation

- `property_list_id` (int): Identifier of the property list this property belongs to (links to `sys.registered_search_property_lists`).
- `property_id` (int): Internal id of the registered property.
- `property_name` (string): Name of the property used in search metadata.
- `property_set_guid` (Guid): GUID identifying the property set.
- `property_int_id` (int): Integer identifier for the property within the set.
- `property_description` (string?): Optional description of the property.

How to interpret

- Use the `property_list_id` to group properties belonging to the same logical collection.
- `property_set_guid` and `property_int_id` are often used externally to reference the property in client code.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = RegisteredSearchPropertiesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new RegisteredSearchPropertiesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"List:{r.PropertyListId} Name:{r.PropertyName} GUID:{r.PropertySetGuid}");
}
```

See also:

- [sys.registered_search_properties](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-registered-search-properties)

