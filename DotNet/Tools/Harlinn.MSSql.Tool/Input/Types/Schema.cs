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
        private Dictionary<string, TypeDefinition> _typeDefinitions = new Dictionary<string, TypeDefinition>();
        private Database? _owner = null;
        private string _name = string.Empty;
        private string _namespace = string.Empty;
        private List<TypeDefinition> _types = new List<TypeDefinition>();
        private List<SchemaObject> _objects = new List<SchemaObject>();

        [XmlIgnore]
        public Dictionary<string, SchemaObject> ObjectsByName { get => _objectsByName; set => _objectsByName = value; }
        [XmlIgnore]
        public Dictionary<string, RowSourceDefinition> RowSourcesByName { get => _rowSourcesByName; set => _rowSourcesByName = value; }
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



        public override string ToString()
        {
            return Name;
        }

    }


}
