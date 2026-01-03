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
using Harlinn.Common.Core.Net.Data.SqlClient;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;
using Microsoft.Data.SqlClient;
using System.ComponentModel;
using System.Xml.Serialization;
using SchemaTypes = Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public class Schema
    {
        private Dictionary<string, SchemaObject> _objectsByName = new Dictionary<string, SchemaObject>(StringComparer.OrdinalIgnoreCase);
        private Dictionary<string, RowSourceDefinition> _rowSourcesByName = new Dictionary<string, RowSourceDefinition>(StringComparer.OrdinalIgnoreCase);
        private Dictionary<string, StoredProcedureDefinition> _storedProceduresByName = new Dictionary<string, StoredProcedureDefinition>(StringComparer.OrdinalIgnoreCase);
        private Dictionary<string, TypeDefinition> _typeDefinitions = new Dictionary<string, TypeDefinition>();
        private Database? _owner = null;
        private string _name = string.Empty;
        private string? _description;
        private string _namespace = string.Empty;
        private List<TypeDefinition> _types = new List<TypeDefinition>();
        private List<SchemaObject> _objects = new List<SchemaObject>();
        private string _storedProceduresWrapperClassName = "StoredProceduresWrapper";
        private string _storedProceduresWrapperNamespace = string.Empty;

        private List<QueryDefinition> _queries = new List<QueryDefinition>();
        private Dictionary<string, QueryDefinition> _queriesByName = new Dictionary<string, QueryDefinition>(StringComparer.OrdinalIgnoreCase);
        private string _dataTypesNamespace = "Types";
        private string _readersNamespace = "Readers";
        private string _databaseNamespace = "Database";

        [XmlIgnore]
        public Dictionary<string, SchemaObject> ObjectsByName { get => _objectsByName; set => _objectsByName = value; }
        [XmlIgnore]
        public Dictionary<string, RowSourceDefinition> RowSourcesByName { get => _rowSourcesByName; set => _rowSourcesByName = value; }

        [XmlIgnore]
        public Dictionary<string, StoredProcedureDefinition> StoredProceduresByName { get => _storedProceduresByName; set => _storedProceduresByName = value; }

        [XmlIgnore]
        public Dictionary<string, TypeDefinition> TypeDefinitions { get => _typeDefinitions; set => _typeDefinitions = value; }
        [XmlIgnore]
        public Database? Owner { get => _owner; set => _owner = value; }
        [XmlIgnore]
        public Project? Project => Owner?.Project;

        [XmlAttribute]
        public string Name { get => _name; set => _name = value; }
        [XmlAttribute, DefaultValue("")]
        public string Namespace { get => _namespace; set => _namespace = value; }

        [XmlAttribute, DefaultValue("Types")]
        public string DataTypesNamespace { get => _dataTypesNamespace; set => _dataTypesNamespace = value; }
        [XmlAttribute, DefaultValue("Readers")]
        public string ReadersNamespace { get => _readersNamespace; set => _readersNamespace = value; }

        [XmlAttribute, DefaultValue("Database")]
        public string DatabaseNamespace { get => _databaseNamespace; set => _databaseNamespace = value; }
        public string GetNamespace()
        {
            var ownerNamespace = Project?.GetNamespace() ?? string.Empty;
            if(string.IsNullOrEmpty(_namespace) == false)
            {
                return $"{ownerNamespace}.{_namespace}";
            }
            return $"{ownerNamespace}.{_name!.FirstToUpper()}";
        }


        [XmlAttribute, DefaultValue("DataType")]
        public string DataTypeSuffix { get; set; } = "DataType";

        [XmlAttribute, DefaultValue("")]
        public string DataTypePrefix { get; set; } = "";


        [XmlAttribute, DefaultValue("Reader")]
        public string ReaderSuffix { get; set; } = "Reader";

        [XmlAttribute, DefaultValue("")]
        public string ReaderPrefix { get; set; } = "";






        public string GetDataTypesNamespace()
        {
            var schemaNamespace = GetNamespace();
            return $"{schemaNamespace}.{DataTypesNamespace}";
        }

        public string GetDatabaseNamespace()
        {
            var schemaNamespace = GetNamespace();
            return $"{schemaNamespace}.{DatabaseNamespace}";
        }

        public string GetReadersNamespace()
        {
            var databaseNamespace = GetDatabaseNamespace();
            return $"{databaseNamespace}.{ReadersNamespace}";
        }


        [XmlArray("Types")]
        [XmlArrayItem(typeof(EnumDefinition), ElementName = "Enum")]
        [XmlArrayItem(typeof(ClassDefinition), ElementName = "Class")]
        [XmlArrayItem(typeof(StructDefinition), ElementName = "Struct")]
        public List<TypeDefinition> Types { get => _types; set => _types = value; }
        [XmlArray("Objects")]
        [XmlArrayItem(typeof(EntityDefinition), ElementName = "Entity")]
        [XmlArrayItem(typeof(ViewDefinition), ElementName = "View")]
        [XmlArrayItem(typeof(StoredProcedureDefinition), ElementName = "StoredProcedure")]
        [XmlArrayItem(typeof(FunctionDefinition), ElementName = "Function")]
        public List<SchemaObject> Objects { get => _objects; set => _objects = value; }

        public IReadOnlyList<EntityDefinition> GetEntities()
        {
            var result = new List<EntityDefinition>();
            foreach ( var obj in Objects)
            {
                if (obj is EntityDefinition entityDefinition)
                {
                    result.Add(entityDefinition);
                }
            }
            return result;
        }

        public IReadOnlyList<ViewDefinition> GetViews()
        {
            var result = new List<ViewDefinition>();
            foreach (var obj in Objects)
            {
                if (obj is ViewDefinition viewDefinition)
                {
                    result.Add(viewDefinition);
                }
            }
            return result;
        }

        public IReadOnlyList<StoredProcedureDefinition> GetStoredProcedures()
        {
            var result = new List<StoredProcedureDefinition>();
            foreach (var obj in Objects)
            {
                if (obj is StoredProcedureDefinition storedProcedureDefinition)
                {
                    result.Add(storedProcedureDefinition);
                }
            }
            return result;
        }


        [XmlArray("Queries"), DefaultValue(null)]
        public List<QueryDefinition>? QueriesOrNull
        {
            get
            {
                if (_queries.Count == 0)
                {
                    return null;
                }
                return _queries;
            }

            set
            {
                if (value == null)
                {
                    _queries.Clear();
                }
                else
                {
                    _queries = value;
                }
            }
        }

        [XmlIgnore]
        public List<QueryDefinition> Queries { get => _queries; set => _queries = value; }
        [XmlIgnore]
        public Dictionary<string, QueryDefinition> QueriesByName { get => _queriesByName; set => _queriesByName = value; }
        [XmlElement, DefaultValue(null)]
        public string? Description { get => _description; set => _description = value; }

        [XmlAttribute, DefaultValue("StoredProceduresWrapper")]
        public string StoredProceduresWrapperClassName { get => _storedProceduresWrapperClassName; set => _storedProceduresWrapperClassName = value; }
        [XmlAttribute, DefaultValue("")]
        public string StoredProceduresWrapperNamespace { get => _storedProceduresWrapperNamespace; set => _storedProceduresWrapperNamespace = value; }

        public string GetStoredProceduresWrapperNamespace()
        {
            var databaseNamespace = GetDatabaseNamespace();
            if (string.IsNullOrEmpty(StoredProceduresWrapperNamespace) == false)
            {
                return $"{databaseNamespace}.{StoredProceduresWrapperNamespace}";
            }
            return databaseNamespace;
        }

        internal void Initialize()
        {
            foreach (var typeDefinition in Types)
            {
                typeDefinition.Owner = this;
                TypeDefinitions[typeDefinition.Name] = typeDefinition;
                typeDefinition.Initialize();
            }

            foreach (var schemaObject in Objects)
            {
                schemaObject.Owner = this;
                schemaObject.Initialize();
                ObjectsByName[schemaObject.Name] = schemaObject;
                if (schemaObject is EntityDefinition entityDefinition)
                {
                    RowSourcesByName[string.IsNullOrEmpty(entityDefinition.Table) == false ? entityDefinition.Table : entityDefinition.Name] = entityDefinition;
                }
                else if (schemaObject is ViewDefinition viewDefinition && viewDefinition.View != null)
                {
                    RowSourcesByName[string.IsNullOrEmpty(viewDefinition.View) == false ? viewDefinition.View : viewDefinition.Name] = viewDefinition;
                }
            }
        }

        public EntityDefinition AddEntity(SchemaTypes.Table table) 
        {
            var tableName = table.Name;
            if (RowSourcesByName.TryGetValue(tableName, out var existingEntity))
            {
                return (EntityDefinition)existingEntity;
            }
            var entityDefinition = new EntityDefinition
            {
                Name = tableName.ToPascalCase(),
                Owner = this,
                Table = table.Name
            };
            Objects.Add(entityDefinition);
            ObjectsByName[entityDefinition.Name] = entityDefinition;
            RowSourcesByName[tableName] = entityDefinition;
            entityDefinition.AddToProject();
            return entityDefinition;
        }

        public ViewDefinition AddView(SchemaTypes.View view)
        {
            var viewName = view.Name;
            if (RowSourcesByName.TryGetValue(viewName, out var existingView))
            {
                return (ViewDefinition)existingView;
            }
            var viewDefinition = new ViewDefinition
            {
                Name = viewName.ToPascalCase(),
                Owner = this,
                View = view.Name
            };
            Objects.Add(viewDefinition);
            ObjectsByName[viewDefinition.Name] = viewDefinition;
            RowSourcesByName[viewName] = viewDefinition;
            viewDefinition.AddToProject();
            return viewDefinition;
        }


        public ViewDefinition AddView(SchemaTypes.SystemView view)
        {
            var viewName = view.Name;
            if (RowSourcesByName.TryGetValue(viewName, out var existingView))
            {
                return (ViewDefinition)existingView;
            }
            var viewDefinition = new ViewDefinition
            {
                Name = view.Name.ToPascalCase(),
                Owner = this,
                View = view.Name
            };
            Objects.Add(viewDefinition);
            ObjectsByName[viewDefinition.Name] = viewDefinition;
            RowSourcesByName[viewName] = viewDefinition;
            viewDefinition.AddToProject();
            return viewDefinition;
        }

        public StoredProcedureDefinition AddStoredProcedure(SchemaTypes.Procedure storedProcedure)
        {
            var procedureName = storedProcedure.Name;
            if (StoredProceduresByName.TryGetValue(procedureName, out var existingProcedure))
            {
                return existingProcedure;
            }
            var procedureDefinition = new StoredProcedureDefinition()
            {
                Name = procedureName,
                Owner = this
            };
            Objects.Add(procedureDefinition);
            ObjectsByName[procedureDefinition.Name] = procedureDefinition;
            StoredProceduresByName[procedureName] = procedureDefinition;
            procedureDefinition.AddToProject();
            return procedureDefinition;
        }

        internal void Initialize2()
        {
            foreach (var typeDefinition in Types)
            {
                typeDefinition.Initialize2();
            }

            foreach (var schemaObject in Objects)
            {
                schemaObject.Initialize2();
            }
        }

        internal void ImportTables(SqlConnection sqlConnection, IReadOnlyList<SchemaTypes.Table> tables)
        {
            foreach (var table in tables)
            {
                ImportTable(sqlConnection, table);
            }
        }

        internal void ImportTable(SqlConnection sqlConnection, SchemaTypes.Table table)
        {
            var schemaObject = AddEntity(table);

            if (schemaObject is EntityDefinition entity)
            {
                entity.ImportTable(sqlConnection, table);
            }
        }

        internal void ImportViews(SqlConnection sqlConnection, IReadOnlyList<SchemaTypes.View> views)
        {
            foreach (var view in views)
            {
                ImportView(sqlConnection, view);
            }
        }

        internal void ImportView(SqlConnection sqlConnection, SchemaTypes.View view)
        {
            var schemaObject = AddView(view);

            if (schemaObject is ViewDefinition viewDefinition)
            {
                viewDefinition.ImportView(sqlConnection, view);
            }
        }

        internal void ImportViews(SqlConnection sqlConnection, IReadOnlyList<SchemaTypes.SystemView> views)
        {
            foreach (var view in views)
            {
                ImportView(sqlConnection, view);
            }
        }

        internal void ImportView(SqlConnection sqlConnection, SchemaTypes.SystemView view)
        {
            var schemaObject = AddView(view);

            if (schemaObject is ViewDefinition viewDefinition)
            {
                viewDefinition.ImportView(sqlConnection, view);
            }
        }

        internal void ImportProcedures(SqlConnection sqlConnection, IReadOnlyList<SchemaTypes.Procedure> procedures)
        {
            foreach (var procedure in procedures)
            {
                ImportProcedure(sqlConnection, procedure);
            }
        }

        internal void ImportProcedure(SqlConnection sqlConnection, SchemaTypes.Procedure procedure)
        {
            var schemaObject = AddStoredProcedure(procedure);

            if (schemaObject is StoredProcedureDefinition procedureDefinition)
            {
                procedureDefinition.ImportProcedure(sqlConnection, procedure);
            }
        }




        public override string ToString()
        {
            return Name;
        }

    }


}
