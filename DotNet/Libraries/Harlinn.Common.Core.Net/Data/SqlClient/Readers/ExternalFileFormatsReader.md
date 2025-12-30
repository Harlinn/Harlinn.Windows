# ExternalFileFormatsReader — reference

Overview

`ExternalFileFormatsReader` wraps `sys.external_file_formats` and returns definitions of file formats used by external tables and PolyBase, including delimiters, encoding and compression.

Reader SQL

```
SELECT
  eff.[file_format_id],
  eff.[Name],
  eff.[format_type],
  eff.[field_terminator],
  eff.[string_delimiter],
  eff.[date_format],
  eff.[use_type_default],
  eff.[serde_method],
  eff.[row_terminator],
  eff.[Encoding],
  eff.[data_compression],
  eff.[first_row]
FROM
  [sys].[external_file_formats] eff
```

Columns and interpretation

- `file_format_id` — id of the file format definition.
- `Name` — file format name.
- `format_type` — format type (for example DELIMITEDTEXT, ORC, PARQUET) as string.
- `field_terminator` — delimiter between fields for delimited formats (nullable).
- `string_delimiter` — optional string quoting delimiter (nullable).
- `date_format` — date format string configured (nullable).
- `use_type_default` — flag indicating whether type defaults are used for parsing.
- `serde_method` — serde serialization/deserialization method name when applicable (nullable).
- `row_terminator` — row terminator string (nullable).
- `Encoding` — encoding used (nullable string), e.g., UTF8.
- `data_compression` — compression algorithm (nullable).
- `first_row` — starting row index for data (nullable integer).

How to interpret

- Use `format_type` and terminator fields to understand how external files are parsed. Compression and encoding settings affect read performance and compatibility.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ExternalFileFormatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ExternalFileFormatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Format:{r.FileFormatId} Name:{r.Name} Type:{r.FormatType} Encoding:{r.Encoding} Compression:{r.DataCompression}");
}
```

See also:

- [sys.external_file_formats](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-external-file-formats)
