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

                if (string.IsNullOrEmpty(value) == false)
                {
                    var previousShortName = _shortName;
                    _shortName = value;
                    if (!string.IsNullOrEmpty(previousShortName))
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
                    else
                    {
                        var project = Project;
                        if (project != null)
                        {
                            project.RowSourcesByAcronym[_shortName] = this;
                        }
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
                if (string.IsNullOrEmpty(schemaNamespace))
                {
                    schemaNamespace = Owner?.Name.FirstToUpper();
                }
                
                return $"{rootNamespace}.Types.{schemaNamespace}";

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


        


        
    }


}
