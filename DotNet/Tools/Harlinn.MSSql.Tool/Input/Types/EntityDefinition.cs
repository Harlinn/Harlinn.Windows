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
    public class EntityDefinition : RowSourceDefinition
    {
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

        public override SchemaObjectType Type => SchemaObjectType.Entity;

        [XmlAttribute]
        public string? Table { get; set; }

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
                if (string.IsNullOrEmpty(index.Name) == false)
                {
                    ImportIndex(sqlConnection, index);
                }
            }
        }

        internal void ImportForeignKey(SqlConnection sqlConnection, SchemaTypes.ForeignKey foreignKey)
        {
            string entityName = string.Empty;
            if (ForeignKeysByName.TryGetValue(foreignKey.Name, out var existingForeignKeyDefinition))
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
            if (checkConstraints != null && checkConstraints.Count > 0)
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
                        if (fieldDefinition.IsReference == false || (fieldDefinition.IsReference && !fieldDefinition.IsNullable))
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
