using Harlinn.MSSql.Tool.Input.Types;
using Harlinn.MSSql.Tool.Output;
using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;
using System.Reflection.PortableExecutable;
using MsSqlHelper = Harlinn.MSSql.Tool.CodeGenerators.Database.MsSqlHelper;

namespace Harlinn.MSSql.Tool.CodeGenerators.CSharp
{
    public class CSharpReaderGenerator : CodeWriter
    {
        readonly RowSourceDefinition _rowSourceDefinition;
        public CSharpReaderGenerator(Context context, RowSourceDefinition rowSourceDefinition)
            : base(context)
        {
            _rowSourceDefinition = rowSourceDefinition;
        }

        public RowSourceDefinition RowSource => _rowSourceDefinition;

        public void Run()
        {
            WriteLine("using System;");
            WriteLine("using System.Data;");
            WriteLine("using System.Data.Common;");
            WriteLine("using System.Collections.Generic;");
            WriteLine("using Microsoft.Data.SqlClient;");
            if (UseWrappers)
            {
                WriteLine("using Harlinn.Common.Core.Net.Data.SqlClient;");
            }
            WriteLine();

            string baseClassName = UseWrappers ? "DataReaderWrapper, " : "";

            var readerNamespace = CSharpHelper.GetDatabaseReaderNamespace(RowSource);
            WriteLine($"namespace {readerNamespace};");
            WriteLine();
            var readerClassName = CSharpHelper.GetReaderClassName(RowSource);
            WriteLine($"public class {readerClassName} : {baseClassName}IDisposable");
            WriteLine("{");
            WriteLine($"    public const string QualifiedTableName = \"{MsSqlHelper.GetQualifiedTableOrViewName(RowSource)}\";");
            WriteLine($"    public const string TableName = \"{MsSqlHelper.GetTableOrViewName(RowSource)}\";");
            var shortName = MsSqlHelper.GetShortName(RowSource).ToLower();
            WriteLine($"    public const string ShortName = \"{shortName}\";");
            WriteLine($"    public const string Sql = \"\"\"");
            WriteLine($"        SELECT");
            var fieldDefinitions = RowSource.Fields;
            var fieldDefinitionsCount = fieldDefinitions.Count;
            var columnNamesList = new List<string>();
            for (int i = 0; i < fieldDefinitionsCount; i++)
            {
                var fieldDefinition = fieldDefinitions[i];
                var columnName = MsSqlHelper.GetColumnName(fieldDefinition);
                columnNamesList.Add(shortName + "." + columnName);
            }
            var columnNames = string.Join($",{Environment.NewLine}          ", columnNamesList);
            WriteLine($"          {columnNames}");
            WriteLine($"        FROM");
            WriteLine($"          {MsSqlHelper.GetQualifiedTableOrViewName(RowSource)} {shortName}");
            WriteLine("        \"\"\";");
            WriteLine();
            for (int i = 0; i < fieldDefinitionsCount; i++)
            {
                var fieldDefinition = fieldDefinitions[i];
                var propertyName = CSharpHelper.GetMemberPropertyName(fieldDefinition);
                WriteLine($"    public const int {propertyName.ToUpper()}_FIELD_ID = {i};");
            }
            WriteLine();


            WriteLine($"    readonly SqlDataReader _reader;");
            WriteLine($"    readonly bool _ownsReader;");
            WriteLine();
            if (UseWrappers)
            {
                WriteLine($"    public {readerClassName}([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)");
                WriteLine("        : base(loggerFactory, sqlDataReader, ownsReader)");
                WriteLine("    {");
                WriteLine("    }");
                WriteLine();
                WriteLine($"    public {readerClassName}([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)");
                WriteLine("        : base(sqlDataReader, ownsReader)");
                WriteLine("    {");
                WriteLine("    }");
                WriteLine();
                WriteLine($"    public {readerClassName}([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)");
                WriteLine("        : base(logger, sqlDataReader, ownsReader)");
                WriteLine("    {");
                WriteLine("    }");
            }
            else
            {
                WriteLine($"    public {readerClassName}(SqlDataReader reader, bool ownsReader = false)");
                WriteLine("    {");
                WriteLine($"        _reader = reader;");
                WriteLine($"        _ownsReader = ownsReader;");
                WriteLine("    }");
            }
            WriteLine();
            WriteLine("    public SqlDataReader Reader => _reader;");
            WriteLine();
            WriteLine("    public void Dispose()");
            WriteLine("    {");
            WriteLine("        if (_ownsReader)");
            WriteLine("        {");
            WriteLine("            ((IDisposable)_reader).Dispose();");
            WriteLine("        }");
            WriteLine("    }");
            WriteLine();
            WriteLine("    public bool Read()");
            WriteLine("    {");
            WriteLine("        return _reader.Read();");
            WriteLine("    }");
            WriteLine();

            for (int i = 0; i < fieldDefinitionsCount; i++)
            {
                var fieldDefinition = fieldDefinitions[i];
                var propertyName = CSharpHelper.GetMemberPropertyName(fieldDefinition);
                var propertyType = CSharpHelper.GetMemberFieldType(fieldDefinition);
                var fieldId = $"{propertyName.ToUpper()}_FIELD_ID";
                var funtion = CSharpHelper.GetDataReaderFunction(fieldDefinition);

                WriteLine($"    public {propertyType} {propertyName}");
                WriteLine("    {");
                WriteLine("        get");
                WriteLine("        {");
                WriteLine($"            return Reader.{funtion}({fieldId});");
                WriteLine("        }");
                WriteLine("    }");
                WriteLine();

            }
            WriteLine();
            var dataTypeName = CSharpHelper.GetDataType(RowSource);
            var qualifiedDataTypeNamespace = CSharpHelper.GetQualifiedDataTypeNamespace(RowSource);
            WriteLine($"    public {qualifiedDataTypeNamespace}.{dataTypeName} ToDataObject()");
            WriteLine("    {");
            var propertyNameList = new List<string>();
            for (int i = 0; i < fieldDefinitionsCount; i++)
            {
                var fieldDefinition = fieldDefinitions[i];
                var propertyName = CSharpHelper.GetMemberPropertyName(fieldDefinition);
                propertyNameList.Add(propertyName);
            }
            var propertyNames = string.Join($",{Environment.NewLine}            ", propertyNameList);

            WriteLine($"        return new {qualifiedDataTypeNamespace}.{dataTypeName}({propertyNames});");
            
            WriteLine("    }");
            WriteLine();

            WriteLine($"    public List<{qualifiedDataTypeNamespace}.{dataTypeName}> ToList()");
            WriteLine("    {");
            WriteLine($"        var list = new List<{qualifiedDataTypeNamespace}.{dataTypeName}>();");
            WriteLine("        while (Read())");
            WriteLine("        {");
            WriteLine("            list.Add(ToDataObject());");
            WriteLine("        }");
            WriteLine("        return list;");
            WriteLine("    }");
            WriteLine();


            WriteLine("}");

        }

    }


}
