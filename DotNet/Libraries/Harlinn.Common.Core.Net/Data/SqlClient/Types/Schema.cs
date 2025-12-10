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

    public class Schema
    {
        readonly string name_;
        readonly int schemaId_;
        readonly int principalId_;

        public Schema(string name, int schemaId, int principalId)
        {
            name_ = name;
            schemaId_ = schemaId;
            principalId_ = principalId;
        }

        public string Name => name_;
        public int SchemaId => schemaId_;
        public int PrincipalId => principalId_;
    }

}
