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
﻿using Harlinn.Common.Core.Net;
using Microsoft.SqlServer.Management.HadrData;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Harlinn.MSSql.Tool.CodeGenerators.CSharp
{
    public class CSharpGenerator
    {
        readonly Context _context;
        public CSharpGenerator(Context context)
        {
            _context = context;
        }
        public Context Context => _context;

        public BuildOptions BuildOptions => (BuildOptions)Context.Options;
        public bool UseWrappers => BuildOptions.UseWrappers;

        IReadOnlyList<Input.Types.Database> Databases => Context.Project.Databases;

        IReadOnlyList<Input.Types.Schema> Schemas
        {
            get
            {
                var result = new List<Input.Types.Schema>();
                foreach (var database in Databases)
                {
                    result.AddRange(database.Schemas);
                }
                return result;
            }
        }



        public void Run()
        {
            var schemas = Schemas;
            var entities = Context.Project.Entities;
            var rowSources = Context.Project.RowSources;
            foreach (var rowSource in rowSources)
            {
                CSharpDataTypeGenerator dataTypeGenerator = new CSharpDataTypeGenerator(Context, rowSource, rowSource.Type == Input.Types.SchemaObjectType.View);
                dataTypeGenerator.Run();

                var filename = Context.GetDataTypeFilename(rowSource);
                dataTypeGenerator.SaveToFile(filename);
            }


            foreach ( var schema in Schemas)
            {
                CSharpStoredProceduresGenerator storedProceduresGenerator = new CSharpStoredProceduresGenerator(Context, schema);
                storedProceduresGenerator.Run();
                var filename = Context.GetStoredProceduresFilename(schema);
                storedProceduresGenerator.SaveToFile(filename);
            }
            
            if (UseWrappers == false)
            {
                CSharpSqlDataReaderExtensionsGenerator sqlDataReaderExtensionsGenerator = new CSharpSqlDataReaderExtensionsGenerator(Context);
                sqlDataReaderExtensionsGenerator.Run();
                var filename = Context.GetSqlDataReaderExtensionsFilename();
                sqlDataReaderExtensionsGenerator.SaveToFile(filename);
            }
            

            if (UseWrappers == false)
            {
                CSharpSqlParameterCollectionExtensions sqlParameterCollectionExtensions = new CSharpSqlParameterCollectionExtensions(Context);
                sqlParameterCollectionExtensions.Run();
                var filename = Context.GetSqlParameterCollectionExtensionsFilename();
                sqlParameterCollectionExtensions.SaveToFile(filename);
            }
            

            foreach (var rowSource in rowSources)
            {
                CSharpReaderGenerator dataTypeGenerator = new CSharpReaderGenerator(Context, rowSource);
                dataTypeGenerator.Run();

                var filename = Context.GetReaderFilename(rowSource);
                dataTypeGenerator.SaveToFile(filename);
            }

            foreach (var entity in entities)
            {
                var generator = new CSharpBulkCopyGenerator(Context, entity);
                generator.Run();

                var filename = Context.GetBulkCopyFilename(entity);
                generator.SaveToFile(filename);
            }

            foreach (var entity in entities)
            {
                var generator = new CSharpDataTableGenerator(Context, entity);
                generator.Run();

                var filename = Context.GetDataTableFilename(entity);
                generator.SaveToFile(filename);
            }


            var typeDefinitions = Context.Project.TypeDefinitions;
            foreach (var entry in typeDefinitions)
            {
                var typeDefinition = entry.Value;

                var filename = Context.GetTypeFilename(typeDefinition);

                if (typeDefinition is Input.Types.EnumDefinition enumDefinition)
                {
                    CSharpEnumGenerator enumGenerator = new CSharpEnumGenerator(Context, enumDefinition);
                    enumGenerator.Run();
                    enumGenerator.SaveToFile(filename);
                }
                else if (typeDefinition is Input.Types.ObjectDefinition objectDefinition)
                {
                    CSharpObjectGenerator objectGenerator = new CSharpObjectGenerator(Context, objectDefinition);
                    objectGenerator.Run();
                    objectGenerator.SaveToFile(filename);
                }


            }

        }

    }


}
