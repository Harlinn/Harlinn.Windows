/*
   Copyright 2024-2025 Espen Harlinn

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

using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.MSSql.Tool.Input.Types
{
    [Serializable]
    public class Int64FieldDefinition : IntegerFieldDefinition<long>
    {
        public Int64FieldDefinition()
            : base()
        {
        }

        public Int64FieldDefinition(SystemDataType systemColumnType, Column column, FieldDefaultConstraint? defaultConstraint, FieldComputed? computed, List<FieldCheckConstraint>? checks, string? description)
            : base(systemColumnType, column, defaultConstraint, computed, checks, description)
        {
        }

        public override FieldType FieldType => FieldType.Int64;
    }
}