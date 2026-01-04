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

using Harlinn.Common.Core.Net;
using Harlinn.MSSql.Tool.Input.Types;
using Microsoft.SqlServer.Management.HadrData;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;



namespace Harlinn.MSSql.Tool.CodeGenerators.CSharp
{
    public static class CSharpFileHelper
    {

        public static string NamespaceToPath(this Context self, string @namespace)
        {
            var result = @namespace.Split('.')
                .Skip(1)
                .Join($"{System.IO.Path.DirectorySeparatorChar}");
            result = Path.Combine(self.Output.CSharp.Directory, result);
            return result;
        }

        public static string GetDataTypeFilename(this Context self, RowSourceDefinition rowSource)
        {
            var datatypeNamespace = rowSource.GetDataTypeNamespace();
            var relativeDirectory = self.NamespaceToPath(datatypeNamespace);
            relativeDirectory = Path.Combine(self.Output.CSharp.Directory, relativeDirectory);

            var className = CSharpHelper.GetDataType(rowSource);

            var filename = System.IO.Path.Combine(relativeDirectory, $"{className}.cs");
            return filename;
        }

        public static string GetReaderFilename(this Context self, RowSourceDefinition rowSource)
        {
            var readerNamespace = rowSource.GetReaderNamespace();
            var relativeDirectory = self.NamespaceToPath(readerNamespace);
            relativeDirectory = Path.Combine(self.Output.CSharp.Directory, relativeDirectory);

            var className = CSharpHelper.GetReaderClassName(rowSource);

            var filename = System.IO.Path.Combine(relativeDirectory, $"{className}.cs");
            return filename;
        }

        public static string GetBulkCopyFilename(this Context self, EntityDefinition entityDefinition)
        {
            var bulkCopyNamespace = entityDefinition.GetBulkCopyNamespace();
            var relativeDirectory = self.NamespaceToPath(bulkCopyNamespace);
            relativeDirectory = Path.Combine(self.Output.CSharp.Directory, relativeDirectory);

            var className = entityDefinition.GetBulkCopyClassName();

            var filename = System.IO.Path.Combine(relativeDirectory, $"{className}.cs");
            return filename;
        }


        public static string GetDataTableFilename(this Context self, EntityDefinition entityDefinition)
        {
            var dataTableNamespace = entityDefinition.GetDataTableNamespace();
            var relativeDirectory = self.NamespaceToPath(dataTableNamespace);
            relativeDirectory = Path.Combine(self.Output.CSharp.Directory, relativeDirectory);

            var className = entityDefinition.GetDataTableClassName();

            var filename = System.IO.Path.Combine(relativeDirectory, $"{className}.cs");
            return filename;
        }

        public static string GetStoredProceduresFilename(this Context self, Schema schema)
        {
            var storedProceduresNamespace = schema.GetStoredProceduresWrapperNamespace();
            var relativeDirectory = self.NamespaceToPath(storedProceduresNamespace);
            relativeDirectory = Path.Combine(self.Output.CSharp.Directory, relativeDirectory);

            var className = schema.StoredProceduresWrapperClassName;

            var filename = System.IO.Path.Combine(relativeDirectory, $"{className}.cs");
            return filename;
        }

        public static string GetSqlDataReaderExtensionsFilename(this Context self)
        {
            var result = Path.Combine(self.Output.CSharp.Directory, "SqlDataReaderExtensions.cs");
            return result;
        }

        public static string GetSqlParameterCollectionExtensionsFilename(this Context self)
        {
            var result = Path.Combine(self.Output.CSharp.Directory, "SqlParameterCollectionExtensions.cs");
            return result;
        }

        public static string GetTypeFilename(this Context self, TypeDefinition typeDefinition)
        {
            var typeNamespace = CSharpHelper.GetTypeNamespace( typeDefinition );
            var relativeDirectory = self.NamespaceToPath(typeNamespace);
            relativeDirectory = Path.Combine(self.Output.CSharp.Directory, relativeDirectory);

            var typeName = typeDefinition.Name;

            var filename = System.IO.Path.Combine(relativeDirectory, $"{typeName}.cs");
            return filename;
        }

    }
}
