/*
   Copyright 2024-2026 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{
    public static class SchemaObjectTypeExtensions
    {
        public static SchemaObjectType ToSchemaObjectType(this string type)
        {
            return type.Trim().ToUpper() switch
            {
                "AF" => SchemaObjectType.AggregateFunction,
                "C" => SchemaObjectType.CheckConstraint,
                "D" => SchemaObjectType.Default,
                "F" => SchemaObjectType.ForeignKeyConstraint,
                "FN" => SchemaObjectType.SqlScalarFunction,
                "FS" => SchemaObjectType.AssemblyScalarFunction,
                "FT" => SchemaObjectType.AssemblyTableValuedFunction,
                "IF" => SchemaObjectType.InlineTableValuedFunction,
                "IT" => SchemaObjectType.InternalTable,
                "P" => SchemaObjectType.StoredProcedure,
                "PC" => SchemaObjectType.AssemblyStoredProcedure,
                "PG" => SchemaObjectType.PlanGuide,
                "PK" => SchemaObjectType.PrimaryKey,
                "R" => SchemaObjectType.Rule,
                "RF" => SchemaObjectType.ReplicationFilter,
                "S" => SchemaObjectType.SystemTable,
                "SN" => SchemaObjectType.Synonym,
                "SO" => SchemaObjectType.Sequence,
                "U" => SchemaObjectType.Table,
                "V" => SchemaObjectType.View,
                "SQ" => SchemaObjectType.ServiceQueue,
                "TA" => SchemaObjectType.AssemblyDmlTrigger,
                "TF" => SchemaObjectType.TableValuedFunction,
                "TR" => SchemaObjectType.DmlTrigger,
                "TT" => SchemaObjectType.TableType,
                "UQ" => SchemaObjectType.UniqueConstraint,
                "X" => SchemaObjectType.ExtendedStoredProcedure,
                "ST" => SchemaObjectType.StatisticsTree,
                "ET" => SchemaObjectType.ExternalTable,
                "EC" =>  SchemaObjectType.EdgeConstraint,
                _ => SchemaObjectType.Unknown,
            };
        }

        public static string ToTypeString(this SchemaObjectType schemaObjectType)
        {
            return schemaObjectType switch
            {
                SchemaObjectType.AggregateFunction => "AF",
                SchemaObjectType.CheckConstraint => "C",
                SchemaObjectType.Default => "D",
                SchemaObjectType.ForeignKeyConstraint => "F",
                SchemaObjectType.SqlScalarFunction => "FN",
                SchemaObjectType.AssemblyScalarFunction => "FS",
                SchemaObjectType.AssemblyTableValuedFunction => "FT",
                SchemaObjectType.InlineTableValuedFunction => "IF",
                SchemaObjectType.InternalTable => "IT",
                SchemaObjectType.StoredProcedure => "P",
                SchemaObjectType.AssemblyStoredProcedure => "PC",
                SchemaObjectType.PlanGuide => "PG",
                SchemaObjectType.PrimaryKey => "PK",
                SchemaObjectType.Rule => "R",
                SchemaObjectType.ReplicationFilter => "RF",
                SchemaObjectType.SystemTable => "S",
                SchemaObjectType.Synonym => "SN",
                SchemaObjectType.Sequence => "SO",
                SchemaObjectType.Table => "U",
                SchemaObjectType.View => "V",
                SchemaObjectType.ServiceQueue => "SQ",
                SchemaObjectType.AssemblyDmlTrigger => "TA",
                SchemaObjectType.TableValuedFunction => "TF",
                SchemaObjectType.DmlTrigger => "TR",
                SchemaObjectType.TableType => "TT",
                SchemaObjectType.UniqueConstraint => "UQ",
                SchemaObjectType.ExtendedStoredProcedure => "X",
                SchemaObjectType.StatisticsTree => "ST",
                SchemaObjectType.ExternalTable => "ET",
                SchemaObjectType.EdgeConstraint => "EC",
                _ => string.Empty,
            };
        }

    }

}
