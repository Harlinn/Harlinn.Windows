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


namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{
    public interface ISchemaObject
    {
        public string Name { get; }

        public int ObjectId { get; }

        public int? PrincipalId { get; }

        public int SchemaId { get; }

        public int? ParentObjectId { get; }

        public SchemaObjectType Type { get; }

        public string TypeDesc { get; }

        public DateTime CreateDate { get; }

        public DateTime ModifyDate { get; }

        public bool? IsMsShipped { get; }

        public bool? IsPublished { get; }

        public bool? IsSchemaPublished { get; }
    }
}