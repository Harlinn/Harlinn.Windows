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

namespace Harlinn.MSSql.Tool.Input.Types
{

    [Serializable]
    public class EntityDefinition : SchemaObject
    {
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
        public List<FieldDefinition> Fields { get; set; } = new List<FieldDefinition>();

        [XmlArray("ForeignKeys")]
        [XmlArrayItem("ForeignKey")]
        public List<ForeignKeyDefinition> ForeignKeys { get; set; } = new List<ForeignKeyDefinition>();

        [XmlArray("Indexes")]
        [XmlArrayItem("Index")]
        public List<IndexDefinition> Indexes { get; set; } = new List<IndexDefinition>();

        [XmlElement("PrimaryKey")]
        public PrimaryKeyDefinition? PrimaryKey { get; set; }

        internal override void Initialize()
        {
            base.Initialize();
            foreach (var field in Fields)
            {
                field.Owner = this;
                field.Initialize();
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
