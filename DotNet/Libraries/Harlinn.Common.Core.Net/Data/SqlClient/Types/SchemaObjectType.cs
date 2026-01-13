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
    public enum SchemaObjectType
    {
        None,
        Unknown,
        // AF = Aggregate function (CLR)
        AggregateFunction,
        // C = Check constraint
        CheckConstraint,
        // D = Default(constraint or stand - alone)
        Default,
        // F = Foreign key constraint
        ForeignKeyConstraint,
        // FN = SQL scalar function
        SqlScalarFunction,
        // FS = Assembly(CLR) scalar-function
        AssemblyScalarFunction,
        // FT = Assembly(CLR) table-valued function
        AssemblyTableValuedFunction,
        // IF = SQL inline table-valued function (TVF)
        InlineTableValuedFunction,
        // IT = Internal table
        InternalTable,
        // P = SQL stored procedure
        StoredProcedure,
        // PC = Assembly(CLR) stored-procedure
        AssemblyStoredProcedure,
        // PG = Plan guide
        PlanGuide,
        // PK = Primary key constraint
        PrimaryKey,
        // R = Rule(old - style, stand - alone)
        Rule,
        // RF = Replication - filter - procedure
        ReplicationFilter,
        // S = System base table
        SystemTable,
        // SN = Synonym
        Synonym,
        // SO = Sequence object
        Sequence,
        // U = Table(user - defined)
        Table,
        // V = View
        View,
        // SQ = Service queue
        ServiceQueue,
        // TA = Assembly(CLR) DML trigger
        AssemblyDmlTrigger,
        // TF = SQL table-valued-function (TVF)
        TableValuedFunction,
        // TR = SQL DML trigger
        DmlTrigger,
        // TT = Table type
        TableType,
        // UQ = unique constraint
        UniqueConstraint,
        // X = Extended stored procedure
        ExtendedStoredProcedure,
        // ST = Statistics tree
        StatisticsTree,
        // ET = External table
        ExternalTable,
        // EC = Edge constraint
        EdgeConstraint
    }

}
