# ColumnXmlSchemaCollectionUsagesReader — reference

Overview

`ColumnXmlSchemaCollectionUsagesReader` wraps `sys.column_xml_schema_collection_usages` and exposes the XML schema collection associations for columns.

Reader SQL

```
SELECT scxscu.[object_id]
      ,scxscu.[column_id]
      ,scxscu.[xml_collection_id]
FROM [sys].[column_xml_schema_collection_usages] scxscu
```

Selected columns (method mapping and brief meaning)

- `object_id` ? `GetObjectId()` (int): Object id containing the column.
- `column_id` ? `GetColumnId()` (int): Column id within the object.
- `xml_collection_id` ? `GetXmlCollectionId()` (int?): Xml schema collection id used by the column (may be NULL).

Helpers

- `GetColumnXmlSchemaCollectionUsage()` returns a `ColumnXmlSchemaCollectionUsage` instance for the current row.
- `GetColumnXmlSchemaCollectionUsages()` reads all rows and returns a list.
