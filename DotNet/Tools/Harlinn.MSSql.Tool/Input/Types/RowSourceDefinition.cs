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

using System.Xml.Serialization;
using Microsoft.Data.SqlClient;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Harlinn.MSSql.Tool.Import;
using SchemaTypes = Harlinn.Common.Core.Net.Data.SqlClient.Types;
using Harlinn.Common.Core.Net;
using System.ComponentModel;

namespace Harlinn.MSSql.Tool.Input.Types
{


    [Serializable]
    public abstract class RowSourceDefinition : SchemaObject
    {
        [XmlIgnore]
        public Dictionary<string, FieldDefinition> FieldsByName { get; set; } = new Dictionary<string, FieldDefinition>(StringComparer.OrdinalIgnoreCase);

        [XmlIgnore]
        List<FieldDefinition>? _persistentFields;

        [XmlIgnore]
        public Dictionary<string, IndexDefinition> IndexesByName { get; set; } = new Dictionary<string, IndexDefinition>(StringComparer.OrdinalIgnoreCase);

        [XmlIgnore]
        public Dictionary<string, ForeignKeyDefinition> ForeignKeysByName { get; set; } = new Dictionary<string, ForeignKeyDefinition>(StringComparer.OrdinalIgnoreCase);


        [XmlIgnore]
        List<FieldDefinition>? _primaryKeyFields;

        [XmlIgnore]
        List<FieldDefinition>? _nullableReferenceFields;

        [XmlIgnore]
        List<FieldDefinition>? _notReferenceAndNotNullableReferenceFields;

        [XmlIgnore]
        List<FieldDefinition>? _primaryKeyAndNullableReferenceFields;

        [XmlIgnore]
        List<FieldDefinition>? _nonPrimaryKeyFields;


        [XmlIgnore]
        string? _baseName;

        [XmlIgnore]
        string? _shortName;

        [XmlIgnore]
        public RowSourceDefinition? Base { get; set; }

        [XmlAttribute("Base")]
        public string? BaseName 
        { 
            get => _baseName; 
            set => _baseName = value; 
        }

        

        [XmlAttribute,DefaultValue(0)]
        public uint Id { get; set; }

        [XmlAttribute]
        public string? ShortName
        {
            get
            {
                if (string.IsNullOrEmpty(_shortName))
                {
                    if (!string.IsNullOrEmpty(Name))
                    {
                        var project = Project;
                        if (project != null)
                        {
                            var shortName = Name.ToAcronym();
                            if(!project.RowSourcesByAcronym.ContainsKey(shortName!))
                            {
                                project.RowSourcesByAcronym[shortName!] = this;
                                _shortName = shortName;
                            }
                            else
                            {
                                for (int i = 0; i < 100; i++)
                                {
                                    var newShortName = $"{shortName}{i}";
                                    if (!project.RowSourcesByAcronym.ContainsKey(newShortName!))
                                    {
                                        project.RowSourcesByAcronym[newShortName!] = this;
                                        _shortName = newShortName;
                                        break;
                                    }
                                }
                            }
                            
                            
                        }
                    }
                }
                return _shortName;
            }
            set
            {
                if (string.IsNullOrEmpty(value))
                {
                    throw new ArgumentException("ShortName cannot be null or empty.", nameof(value));
                }
                var previousShortName = _shortName;
                _shortName = value;
                if ( !string.IsNullOrEmpty(previousShortName))
                {
                    var project = Project;
                    if (project != null)
                    {
                        if (project.RowSourcesByAcronym.ContainsKey(previousShortName))
                        {
                            project.RowSourcesByAcronym.Remove(previousShortName);
                        }
                        project.RowSourcesByAcronym[_shortName] = this;
                    }
                }
            }
        }

        [XmlIgnore]
        public string DataTypeNamespace
        {
            get
            {
                var project = Project;
                var rootNamespace = project?.Namespace;
                var schemaNamespace = Owner?.Namespace;
                if (!string.IsNullOrEmpty(schemaNamespace))
                {
                    return $"{rootNamespace}.Types.{schemaNamespace}";
                }
                else
                {
                    return rootNamespace! + ".Types";
                }
            }
        }

        [XmlArray("Fields")]
        [XmlArrayItem(typeof(BooleanFieldDefinition),ElementName ="Boolean")]
        [XmlArrayItem(typeof(ByteFieldDefinition),ElementName ="Byte")]
        [XmlArrayItem(typeof(SByteFieldDefinition),ElementName ="SByte")]
        [XmlArrayItem(typeof(CharFieldDefinition),ElementName ="Char")]
        [XmlArrayItem(typeof(Int16FieldDefinition),ElementName ="Int16")]
        [XmlArrayItem(typeof(UInt16FieldDefinition),ElementName ="UInt16")]
        [XmlArrayItem(typeof(Int32FieldDefinition),ElementName ="Int32")]
        [XmlArrayItem(typeof(UInt32FieldDefinition),ElementName ="UInt32")]
        [XmlArrayItem(typeof(Int64FieldDefinition),ElementName ="Int64")]
        [XmlArrayItem(typeof(UInt64FieldDefinition),ElementName ="UInt64")]
        [XmlArrayItem(typeof(SingleFieldDefinition),ElementName ="Single")]
        [XmlArrayItem(typeof(DoubleFieldDefinition),ElementName ="Double")]
        [XmlArrayItem(typeof(DecimalFieldDefinition),ElementName ="Decimal")]
        [XmlArrayItem(typeof(DateTimeFieldDefinition),ElementName ="DateTime")]
        [XmlArrayItem(typeof(TimeSpanFieldDefinition),ElementName ="TimeSpan")]
        [XmlArrayItem(typeof(GuidFieldDefinition),ElementName ="Guid")]
        [XmlArrayItem(typeof(StringFieldDefinition),ElementName ="String")]
        [XmlArrayItem(typeof(BinaryFieldDefinition),ElementName ="Binary")]
        [XmlArrayItem(typeof(SqlVariantFieldDefinition),ElementName ="SqlVariant")]
        [XmlArrayItem(typeof(HierarchyIdFieldDefinition),ElementName ="HierarchyId")]
        [XmlArrayItem(typeof(GeometryFieldDefinition),ElementName ="Geometry")]
        [XmlArrayItem(typeof(GeographyFieldDefinition),ElementName ="Geography")]
        [XmlArrayItem(typeof(XmlFieldDefinition),ElementName ="Xml")]
        [XmlArrayItem(typeof(ObjectFieldDefinition), ElementName = "Object")]
        [XmlArrayItem(typeof(EnumFieldDefinition), ElementName = "Enum")]
        public List<FieldDefinition> Fields { get; set; } = new List<FieldDefinition>();

        [XmlIgnore]
        public List<FieldDefinition> PersistentFields
        {
            get
            {
                if(_persistentFields == null)
                {
                    _persistentFields = new List<FieldDefinition>();
                    foreach (var fieldDefinition in Fields)
                    {
                        if (fieldDefinition.IsComputed == false)
                        {
                            _persistentFields.Add(fieldDefinition);
                        }
                    }
                }
                return _persistentFields;
            }
        }

        [XmlArray("ForeignKeys")]
        [XmlArrayItem("ForeignKey")]
        public List<ForeignKeyDefinition> ForeignKeys { get; set; } = new List<ForeignKeyDefinition>();

        [XmlArray("Indexes")]
        [XmlArrayItem("Index")]
        public List<IndexDefinition> Indexes { get; set; } = new List<IndexDefinition>();

        [XmlElement("PrimaryKey")]
        public IndexDefinition? PrimaryKey { get; set; }

        [XmlArray("Checks"), XmlArrayItem(typeof(EntityCheckConstraint), ElementName = "Check"), DefaultValue(null)]
        public List<EntityCheckConstraint>? Checks { get; set; }


        internal int GetFieldIndex(string fieldName)
        {
            for (int i = 0; i < Fields.Count; i++)
            {
                if (string.Equals(Fields[i].Name, fieldName, StringComparison.OrdinalIgnoreCase))
                {
                    return i;
                }
            }
            return -1;
        }

        internal void AddField(FieldDefinition field)
        {
            var index = GetFieldIndex(field.Name);
            if (index >= 0)
            {
                Fields[index] = field;
            }
            else
            {
                Fields.Add(field);
            }
            FieldsByName[field.Name] = field;
        }


        internal int GetIndexIndex(string indexName)
        {
            for (int i = 0; i < Indexes.Count; i++)
            {
                if (string.Equals(Indexes[i].Name, indexName, StringComparison.OrdinalIgnoreCase))
                {
                    return i;
                }
            }
            return -1;
        }

        internal void AddIndex(IndexDefinition index)
        {
            var idx = GetIndexIndex(index.Name);
            if (idx >= 0)
            {
                Indexes[idx] = index;
            }
            else
            {
                Indexes.Add(index);
            }
            if (string.IsNullOrEmpty(index.Name) == false)
            {
                IndexesByName[index.Name] = index;
            }
        }


        internal int GetForeignKeyIndex(string foreignKeyName)
        {
            for (int i = 0; i < ForeignKeys.Count; i++)
            {
                if (string.Equals(ForeignKeys[i].Name, foreignKeyName, StringComparison.OrdinalIgnoreCase))
                {
                    return i;
                }
            }
            return -1;
        }

        internal void AddForeignKey(ForeignKeyDefinition foreignKey)
        {
            var idx = GetForeignKeyIndex(foreignKey.Name);
            if (idx >= 0)
            {
                ForeignKeys[idx] = foreignKey;
            }
            else
            {
                ForeignKeys.Add(foreignKey);
            }
            ForeignKeysByName[foreignKey.Name] = foreignKey;
        }


        internal void ImportColumn(SqlConnection sqlConnection, SchemaTypes.Column column)
        {
            var fieldDefinition = column.ToFieldDefinition(sqlConnection);
            fieldDefinition.Owner = this;
            AddField(fieldDefinition);
        }

        internal void ImportColumns(SqlConnection sqlConnection, IReadOnlyList<SchemaTypes.Column> columns)
        {
            foreach (var column in columns)
            {
                ImportColumn(sqlConnection, column);
            }
        }

        internal void ImportIndex(SqlConnection sqlConnection, SchemaTypes.Index index)
        {
            var indexDefinition = new IndexDefinition
            {
                Owner = this,
                Name = index.Name,
                IsUnique = index.IsUnique,
                IsPrimaryKey = index.IsPrimaryKey
            };
            if (index.IsPrimaryKey)
            {
                PrimaryKey = indexDefinition;
            }
            else
            {
                AddIndex(indexDefinition);
            }

            var indexColumns = sqlConnection.GetIndexColumns(index);
            foreach (var indexColumn in indexColumns)
            {
                var indexFieldDefinition = new IndexFieldDefinition
                {
                    Name = indexColumn.ColumnName,
                    IsDescending = indexColumn.IsDescendingKey
                };
                indexDefinition.AddField(indexFieldDefinition);
            }
        }

        internal void ImportIndexes(SqlConnection sqlConnection, IReadOnlyList<SchemaTypes.Index> indexes)
        {
            foreach (var index in indexes)
            {
                ImportIndex(sqlConnection, index);
            }
        }

        internal void ImportForeignKey(SqlConnection sqlConnection, SchemaTypes.ForeignKey foreignKey)
        {
            string entityName = string.Empty;
            if(ForeignKeysByName.TryGetValue(foreignKey.Name, out var existingForeignKeyDefinition))
            {
                entityName = existingForeignKeyDefinition.EntityName;
            }
            var foreignKeyDefinition = new ForeignKeyDefinition
            {
                Owner = this,
                Name = foreignKey.Name,
                EntityName = entityName,
                ReferencedTableName = foreignKey.ReferencedTableName,
                ReferencedSchemaName = foreignKey.ReferencedSchemaName,
            };

            AddForeignKey(foreignKeyDefinition);

            var foreignKeyColumns = sqlConnection.GetForeignKeyColumns(foreignKey);
            foreach (var foreignKeyColumn in foreignKeyColumns)
            {
                var foreignKeyFieldDefinition = new ForeignKeyReferenceDefinition
                {
                    Field = foreignKeyColumn.ColumnName,
                    References = foreignKeyColumn.ReferencedColumnName
                };
                foreignKeyDefinition.AddReference(foreignKeyFieldDefinition);
            }
        }

        internal void ImportForeignKeys(SqlConnection sqlConnection, IReadOnlyList<SchemaTypes.ForeignKey> foreignKeys)
        {
            foreach (var foreignKey in foreignKeys)
            {
                ImportForeignKey(sqlConnection, foreignKey);
            }
        }

        internal void ImportTableCheckConstraints(SqlConnection sqlConnection, IReadOnlyList<SchemaTypes.CheckConstraint> checkConstraints)
        {
            if(checkConstraints != null && checkConstraints.Count > 0)
            {
                foreach (var checkConstraint in checkConstraints)
                {
                    var entityCheckConstraint = new EntityCheckConstraint
                    {
                        Name = checkConstraint.Name,
                        Definition = checkConstraint.Definition
                    };

                    AddCheckConstraint(entityCheckConstraint);
                }

            }
            
        }

        private void AddCheckConstraint(EntityCheckConstraint entityCheckConstraint)
        {
            if (Checks == null)
            {
                Checks = new List<EntityCheckConstraint>();
            }

            entityCheckConstraint.Owner = this;

            for (int i = 0; i < Checks.Count; i++)
            {
                var existingCheckConstraint = Checks[i];
                if (string.Equals(existingCheckConstraint.Name, entityCheckConstraint.Name, StringComparison.OrdinalIgnoreCase))
                {
                    // If a check constraint with the same name exists, replace it
                    existingCheckConstraint.Definition = entityCheckConstraint.Definition;
                    return;
                }
            }
            // If no existing check constraint was found, add a new one
            Checks.Add(entityCheckConstraint);
        }

        internal void ImportTable(SqlConnection sqlConnection, SchemaTypes.Table table)
        {
            var columns = sqlConnection.GetColumns(table);
            ImportColumns(sqlConnection, columns);
            
            var indexes = sqlConnection.GetIndexes(table);
            ImportIndexes(sqlConnection, indexes);

            var foreignKeys = sqlConnection.GetForeignKeys(table);
            ImportForeignKeys(sqlConnection, foreignKeys);

            var tableCheckConstraints = sqlConnection.GetTableCheckConstraints(table);
            ImportTableCheckConstraints(sqlConnection, tableCheckConstraints);

        }

        internal void ImportView(SqlConnection sqlConnection, SchemaTypes.View view)
        {
            var columns = sqlConnection.GetColumns(view);
            ImportColumns(sqlConnection, columns);
        }

        internal void ImportView(SqlConnection sqlConnection, SchemaTypes.SystemView view)
        {
            var columns = sqlConnection.GetSystemColumns(view);
            ImportColumns(sqlConnection, columns);
        }


        internal override void Initialize()
        {
            base.Initialize();
            foreach (var field in Fields)
            {
                field.Owner = this;
                field.Initialize();
                FieldsByName[field.Name] = field;
            }
            foreach (var foreignKey in ForeignKeys)
            {
                foreignKey.Owner = this;
                foreignKey.Initialize();
            }
            foreach (var index in Indexes)
            {
                index.Owner = this;
                index.Initialize();
            }
            if (PrimaryKey != null)
            {
                PrimaryKey.Owner = this;
                PrimaryKey.Initialize();
            }
        }

        internal override void Initialize2()
        {
            base.Initialize2();
            foreach (var field in Fields)
            {
                field.Initialize2();
            }
            foreach (var foreignKey in ForeignKeys)
            {
                foreignKey.Initialize2();
            }
        }


        [XmlIgnore]
        public List<FieldDefinition> PrimaryKeyFields
        {
            get
            {
                if (_primaryKeyFields == null)
                {
                    _primaryKeyFields = new List<FieldDefinition>();
                    if (PrimaryKey != null)
                    {
                        foreach (var indexField in PrimaryKey.Fields)
                        {
                            if (FieldsByName.TryGetValue(indexField.Name, out var fieldDefinition))
                            {
                                _primaryKeyFields.Add(fieldDefinition);
                            }
                        }
                    }
                }
                return _primaryKeyFields;
            }
        }

        internal bool GetIsReference(FieldDefinition fieldDefinition)
        {
            foreach (var foreignKey in ForeignKeys)
            {
                foreach (var reference in foreignKey.References)
                {
                    if (string.Equals(reference.Field, fieldDefinition.Name, StringComparison.OrdinalIgnoreCase))
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        [XmlIgnore]
        public List<FieldDefinition> NullableReferenceFields
        {
            get
            {
                if (_nullableReferenceFields == null)
                {
                    _nullableReferenceFields = new List<FieldDefinition>();
                    foreach (var fieldDefinition in Fields)
                    {
                        if (fieldDefinition.IsReference && fieldDefinition.IsNullable)
                        {
                            _nullableReferenceFields.Add(fieldDefinition);
                        }
                    }
                }
                return _nullableReferenceFields;
            }
        }
        

        [XmlIgnore]
        public List<FieldDefinition> NotReferenceAndNotNullableReferenceFields
        {             
            get
            {
                if (_notReferenceAndNotNullableReferenceFields == null)
                {
                    _notReferenceAndNotNullableReferenceFields = new List<FieldDefinition>();
                    foreach (var fieldDefinition in Fields)
                    {
                        if (fieldDefinition.IsReference == false ||( fieldDefinition.IsReference && !fieldDefinition.IsNullable ))
                        {
                            _notReferenceAndNotNullableReferenceFields.Add(fieldDefinition);
                        }
                    }
                }
                return _notReferenceAndNotNullableReferenceFields;
            }
        }

        [XmlIgnore]
        public List<FieldDefinition> PrimaryKeyAndNullableReferenceFields
        {
            get
            {
                if (_primaryKeyAndNullableReferenceFields == null)
                {
                    _primaryKeyAndNullableReferenceFields = new List<FieldDefinition>();
                    _primaryKeyAndNullableReferenceFields.AddRange(PrimaryKeyFields);
                    _primaryKeyAndNullableReferenceFields.AddRange(NullableReferenceFields);
                }
                return _primaryKeyAndNullableReferenceFields;
            }
        }

        [XmlIgnore]
        public List<FieldDefinition> NonPrimaryKeyFields
        {
            get
            {
                if (_nonPrimaryKeyFields == null)
                {
                    _nonPrimaryKeyFields = new List<FieldDefinition>();
                    var primaryKeyFieldNames = new HashSet<string>(StringComparer.OrdinalIgnoreCase);
                    foreach (var primaryKeyField in PrimaryKeyFields)
                    {
                        primaryKeyFieldNames.Add(primaryKeyField.Name);
                    }
                    foreach (var fieldDefinition in Fields)
                    {
                        if (!primaryKeyFieldNames.Contains(fieldDefinition.Name))
                        {
                            _nonPrimaryKeyFields.Add(fieldDefinition);
                        }
                    }
                }
                return _nonPrimaryKeyFields;
            }
        }
    }


}
