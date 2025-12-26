using Harlinn.MSSql.Tool.Input.Types;
using Harlinn.MSSql.Tool.Output;

namespace Harlinn.MSSql.Tool.CodeGenerators.Database
{
    public class MsSqlTablesGenerator : CodeWriter
    {
        public MsSqlTablesGenerator(Context context) : base(context)
        {
        }

        public void Run()
        {
            var entities = Context.Project.Entities;
            var schemas = new HashSet<string>(StringComparer.OrdinalIgnoreCase);

            foreach (var entity in entities)
            {
                var schemaName = entity.Owner?.Name ?? "dbo";
                if (!schemas.Contains(schemaName))
                {
                    schemas.Add(schemaName);
                }
            }

            foreach (var schema in schemas)
            {
                if (schema.Equals("dbo", StringComparison.OrdinalIgnoreCase))
                {
                    continue;
                }
                WriteLine( "/*");
                WriteLine($" * Schema: [{schema}]");
                WriteLine( " */");
                WriteLine($"IF NOT EXISTS (SELECT * FROM sys.schemas WHERE name = '{schema}')");
                WriteLine("BEGIN");
                WriteLine($"    EXEC('CREATE SCHEMA [{schema}]');");
                WriteLine("END");
                WriteLine("go");
                WriteLine();
            }


            foreach (var entity in entities)
            {
                WriteCreateTable(entity);
            }
            foreach (var entity in entities)
            {
                WriteForeignKeys(entity);
            }
        }

        void WriteCreateTable(RowSourceDefinition entity)
        {
            var qualifiedTableName = MsSqlHelper.GetQualifiedTableOrViewName(entity);

            WriteLine( "/*");
            WriteLine($" * {qualifiedTableName}");
            WriteLine( " */");
            WriteLine($"CREATE TABLE {qualifiedTableName}");
            WriteLine("(");
            foreach (var field in entity.Fields)
            {
                WriteColumn(entity, field);
            }
            WritePrimaryKey(entity);
            WriteLine(")");
            WriteLine("go");
            WriteLine();
            WriteIndexes(entity);
            WriteLine();
        }

        void WriteColumn(RowSourceDefinition entity, FieldDefinition field)
        {
            var columnDefault = GetColumnDefault(field);
            var columnName = MsSqlHelper.GetColumnName(field);
            if (field.IsComputed)
            {
                var computedDefinition = field.Computed!.Definition;
                var computedIsPersisted = field.Computed.IsPersisted;
                if (computedIsPersisted)
                {
                    WriteLine($"    {columnName} AS ({computedDefinition}) PERSISTED,");
                }
                else
                {
                    WriteLine($"    {columnName} AS {computedDefinition},");
                }

                return;
            }
            else
            {
                var columnType = MsSqlHelper.GetRawColumnType(field);
                var columnIdentity = MsSqlHelper.GetColumnIdentity(field);
                if (string.IsNullOrEmpty(columnIdentity) == false)
                {
                    columnIdentity = " " + columnIdentity;
                }
                var columnNull = field.IsNullable ? "NULL" : "NOT NULL";
                WriteLine($"    {columnName} {columnType}{columnIdentity} {columnNull}{columnDefault},");
            }
        }

        static string GetColumnDefault(FieldDefinition field)
        {
            if (field.DefaultConstraint != null)
            {
                var defaultConstraint = field.DefaultConstraint;
                var definition = defaultConstraint.Definition;
                return $" DEFAULT {definition}";
            }
            else
            {
                return string.Empty;
            }
        }


        void WriteIndexes(RowSourceDefinition entity)
        {
            var indexes = entity.Indexes;
            foreach (var index in indexes)
            {
                WriteIndex(entity, index);
            }
        }

        void WriteIndex(RowSourceDefinition entity, IndexDefinition index)
        {
            var qualifiedTableName = MsSqlHelper.GetQualifiedTableOrViewName(entity);

            var indexColumnList = IndexColumnList(index);
            var indexName = index.Name;

            if (index.IsUnique)
            {
                WriteLine($"ALTER TABLE {qualifiedTableName}");
                WriteLine($"  ADD CONSTRAINT {indexName} UNIQUE({indexColumnList})");
                WriteLine("go");
            }
            else
            {
                WriteLine($"CREATE INDEX {indexName} ON {qualifiedTableName}({indexColumnList})");
                WriteLine("go");
            }
            WriteLine();
        }

        static string IndexColumnList(IndexDefinition index)
        {
            var columnNames = index.Fields.Select(f => MsSqlHelper.GetColumnName(f.Definition!));
            return string.Join(", ", columnNames);
        }

        void WritePrimaryKey(RowSourceDefinition entity)
        {
            var primaryKey = entity.PrimaryKey;
            var primaryKeyName = primaryKey?.Name;
            var primaryKeyColumnList = IndexColumnList(primaryKey!);

            WriteLine($"    CONSTRAINT [{primaryKeyName}] PRIMARY KEY({primaryKeyColumnList})");
        }


        static string ForeignKeyColumnList(ForeignKeyDefinition foreignKey)
        {
            var columnNames = foreignKey.References.Select(f => MsSqlHelper.GetColumnName(f.Definition!));
            return string.Join(", ", columnNames);
        }

        static string ForeignKeyReferencedColumnList(ForeignKeyDefinition foreignKey)
        {
            var columnNames = foreignKey.References.Select(f => MsSqlHelper.GetColumnName(f.ReferencesDefinition!));
            return string.Join(", ", columnNames);
        }

        void WriteForeignKeys(RowSourceDefinition entity)
        {
            var foreignKeys = entity.ForeignKeys;
            foreach (var foreignKey in foreignKeys)
            {
                WriteForeignKey(entity, foreignKey);
            }
        }

        void WriteForeignKey(RowSourceDefinition entity, ForeignKeyDefinition foreignKey)
        {
            var qualifiedTableName = MsSqlHelper.GetQualifiedTableOrViewName(entity);
            var qualifiedReferencedTableName = MsSqlHelper.GetQualifiedTableOrViewName(foreignKey.Entity!);

            var foreignKeyName = foreignKey.Name;
            var foreignKeyColumnList = ForeignKeyColumnList(foreignKey!);
            var foreignKeyReferencedColumnList = ForeignKeyReferencedColumnList(foreignKey!);

            WriteLine($"ALTER TABLE {qualifiedTableName}");
            WriteLine($"  ADD CONSTRAINT {foreignKeyName} FOREIGN KEY({foreignKeyColumnList})");
            WriteLine($"  REFERENCES {qualifiedReferencedTableName}({foreignKeyReferencedColumnList})");
            WriteLine("go");
            WriteLine();
        }
    }

}
