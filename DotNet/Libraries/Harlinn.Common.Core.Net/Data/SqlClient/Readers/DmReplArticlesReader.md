# DmReplArticlesReader — reference

Overview

`DmReplArticlesReader` wraps `sys.dm_repl_articles` and exposes replication article metadata used by SQL Server replication (article definitions, generated commands and options).

Reader SQL

```
SELECT
  dra.[artcache_db_address],
  dra.[artcache_table_address],
  dra.[artcache_schema_address],
  dra.[artcache_article_address],
  dra.[Artid],
  dra.[Artfilter],
  dra.[Artobjid],
  dra.[Artpubid],
  dra.[Artstatus],
  dra.[Arttype],
  dra.[Wszartdesttable],
  dra.[Wszartdesttableowner],
  dra.[Wszartinscmd],
  dra.[Cmdtypeins],
  dra.[Wszartdelcmd],
  dra.[Cmdtypedel],
  dra.[Wszartupdcmd],
  dra.[Cmdtypeupd],
  dra.[Wszartpartialupdcmd],
  dra.[Cmdtypepartialupd],
  dra.[Numcol],
  dra.[Artcmdtype],
  dra.[Artgeninscmd],
  dra.[Artgendelcmd],
  dra.[Artgenupdcmd],
  dra.[Artpartialupdcmd],
  dra.[Artupdtxtcmd],
  dra.[Artgenins2cmd],
  dra.[Artgendel2cmd],
  dra.[Finreconcile],
  dra.[Fpuballowupdate],
  dra.[Intpublicationoptions]
FROM
  [sys].[dm_repl_articles] dra
```

Columns and interpretation

- `artcache_db_address` — Probably/guesswork: internal address of cached publication database info.
- `artcache_table_address` — Probably/guesswork: internal address of cached table metadata.
- `artcache_schema_address` — Probably/guesswork: internal address of cached schema metadata.
- `artcache_article_address` — Probably/guesswork: internal address for cached article metadata.
- `Artid` — article identifier within the publication.
- `Artfilter` — filter identifier applied to the article (if any).
- `Artobjid` — object id of the source object for the article.
- `Artpubid` — publication id that this article belongs to.
- `Artstatus` — status code for the article (enabled, disabled, etc.).
- `Arttype` — article type code (e.g., table, view).
- `Wszartdesttable` — destination table name used by the article.
- `Wszartdesttableowner` — owner/schema of the destination table.
- `Wszartinscmd` / `Cmdtypeins` — insert command template and type for the article.
- `Wszartdelcmd` / `Cmdtypedel` — delete command template and type.
- `Wszartupdcmd` / `Cmdtypeupd` — update command template and type.
- `Wszartpartialupdcmd` / `Cmdtypepartialupd` — partial update command and type.
- `Numcol` — number of columns in the article.
- `Artcmdtype` — command generation type for the article.
- `Artgeninscmd`, `Artgendelcmd`, `Artgenupdcmd` — generated statement templates for insert/delete/update.
- `Artpartialupdcmd` — generated partial update template.
- `Artupdtxtcmd` — update text command (for text/image types).
- `Artgenins2cmd`, `Artgendel2cmd` — alternative generated commands (replication internals).
- `Finreconcile` — flag indicating if final reconciliation is required.
- `Fpuballowupdate` — flag indicating whether publication allows updates at subscriber.
- `Intpublicationoptions` — internal bitmask of publication options.

How to interpret

- Use the article identifiers and `Artstatus`/`Arttype` to inspect replication configuration and diagnose missing or disabled articles.
- The generated command templates (`Artgen*`) and `Wszart*` fields show what statements replication will produce.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmReplArticlesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmReplArticlesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"ArticleId:{r.Artid} ObjId:{r.Artobjid} Dest:{r.Wszartdesttable} Status:{r.Artstatus} Type:{r.Arttype}");
}
```

See also:

- [sys.dm_repl_articles](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-repl-articles)
