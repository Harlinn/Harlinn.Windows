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

namespace Harlinn.MSSql.Tool.Input.Types
{

    [Serializable]
    public class EntityDefinition : SchemaObject
    {
        [XmlIgnore]
        public Dictionary<string, FieldDefinition> FieldsByName { get; set; } = new Dictionary<string, FieldDefinition>(StringComparer.OrdinalIgnoreCase);

        [XmlIgnore]
        public Dictionary<string, IndexDefinition> IndexesByName { get; set; } = new Dictionary<string, IndexDefinition>(StringComparer.OrdinalIgnoreCase);

        [XmlIgnore]
        public Dictionary<string, ForeignKeyDefinition> ForeignKeysByName { get; set; } = new Dictionary<string, ForeignKeyDefinition>(StringComparer.OrdinalIgnoreCase);


        [XmlIgnore]
        string? _baseName;

        [XmlIgnore]
        public EntityDefinition? Base { get; set; }

        [XmlAttribute("Base")]
        public string? BaseName 
        { 
            get => _baseName; 
            set => _baseName = value; 
        }

        public override SchemaObjectType Type => SchemaObjectType.Entity;

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
        public List<FieldDefinition> Fields { get; set; } = new List<FieldDefinition>();

        [XmlArray("ForeignKeys")]
        [XmlArrayItem("ForeignKey")]
        public List<ForeignKeyDefinition> ForeignKeys { get; set; } = new List<ForeignKeyDefinition>();

        [XmlArray("Indexes")]
        [XmlArrayItem("Index")]
        public List<IndexDefinition> Indexes { get; set; } = new List<IndexDefinition>();

        [XmlElement("PrimaryKey")]
        public IndexDefinition? PrimaryKey { get; set; }


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



        internal void ImportColumn(SchemaTypes.Column column)
        {
            var fieldDefinition = column.ToFieldDefinition();
            if (FieldsByName.ContainsKey(fieldDefinition.Name))
            {
                var index = GetFieldIndex(fieldDefinition.Name);
                if (index >= 0)
                {
                    Fields[index] = fieldDefinition;
                }
            }
            else
            {
                Fields.Add(fieldDefinition);
            }
            FieldsByName[fieldDefinition.Name] = fieldDefinition;

        }

        internal void ImportColumns(IReadOnlyList<SchemaTypes.Column> columns)
        {
            foreach (var column in columns)
            {
                ImportColumn(column);
            }
        }

        internal void ImportIndex(SqlConnection sqlConnection, SchemaTypes.Index index)
        {
            if (IndexesByName.TryGetValue(index.Name, out var indexDefinition))
            {
                var offset = GetIndexIndex(index.Name);
                if (offset >= 0)
                {
                    Indexes.RemoveAt(offset);
                }
            }

            indexDefinition = new IndexDefinition
            {
                Name = index.Name,
                IsUnique = index.IsUnique,
            };

            Indexes.Add(indexDefinition);
            IndexesByName[indexDefinition.Name] = indexDefinition;

            var indexColumns = sqlConnection.GetIndexColumns(index);
            foreach (var indexColumn in indexColumns)
            {
                var indexFieldDefinition = new IndexFieldDefinition
                {
                    Name = indexColumn.ColumnName,
                    IsDescending = indexColumn.IsDescendingKey
                };
                indexDefinition.Fields.Add(indexFieldDefinition);
            }
            if(index.IsPrimaryKey)
            {
                PrimaryKey = indexDefinition;
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
            if (ForeignKeysByName.TryGetValue(foreignKey.Name, out var foreignKeyDefinition))
            {
                var offset = GetForeignKeyIndex(foreignKey.Name);
                if (offset >= 0)
                {
                    ForeignKeys.RemoveAt(offset);
                }
            }

            foreignKeyDefinition = new ForeignKeyDefinition
            {
                Name = foreignKey.Name,
                ReferencedTableName = foreignKey.ReferencedTableName,
                ReferencedSchemaName = foreignKey.ReferencedSchemaName,

            };

            ForeignKeys.Add(foreignKeyDefinition);
            ForeignKeysByName[foreignKeyDefinition.Name] = foreignKeyDefinition;

            var foreignKeyColumns = sqlConnection.GetForeignKeyColumns(foreignKey);
            foreach (var foreignKeyColumn in foreignKeyColumns)
            {
                var foreignKeyFieldDefinition = new ForeignKeyReferenceDefinition
                {
                    Field = foreignKeyColumn.ColumnName,
                    References = foreignKeyColumn.ReferencedColumnName
                };
                foreignKeyDefinition.References.Add(foreignKeyFieldDefinition);
            }
        }

        internal void ImportForeignKeys(SqlConnection sqlConnection, IReadOnlyList<SchemaTypes.ForeignKey> foreignKeys)
        {
            foreach (var foreignKey in foreignKeys)
            {
                ImportForeignKey(sqlConnection, foreignKey);
            }
        }

        internal void ImportTable(SqlConnection sqlConnection, SchemaTypes.Table table)
        {
            var columns = sqlConnection.GetColumns(table);
            ImportColumns(columns);
            
            var indexes = sqlConnection.GetIndexes(table);
            ImportIndexes(sqlConnection, indexes);

            var foreignKeys = sqlConnection.GetForeignKeys(table);
            ImportForeignKeys(sqlConnection, foreignKeys);

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
            foreach (var foreignKey in ForeignKeys)
            {
                foreignKey.Owner = this;
            }
        }


    }


}
