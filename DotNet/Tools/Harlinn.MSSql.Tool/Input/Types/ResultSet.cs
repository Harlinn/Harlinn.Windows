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
    public class ResultSet
    {
        private List<FieldDefinition> _fields = new List<FieldDefinition>();

        [XmlArray("Fields")]
        [XmlArrayItem(typeof(BooleanFieldDefinition), ElementName = "Boolean")]
        [XmlArrayItem(typeof(ByteFieldDefinition), ElementName = "Byte")]
        [XmlArrayItem(typeof(SByteFieldDefinition), ElementName = "SByte")]
        [XmlArrayItem(typeof(CharFieldDefinition), ElementName = "Char")]
        [XmlArrayItem(typeof(Int16FieldDefinition), ElementName = "Int16")]
        [XmlArrayItem(typeof(UInt16FieldDefinition), ElementName = "UInt16")]
        [XmlArrayItem(typeof(Int32FieldDefinition), ElementName = "Int32")]
        [XmlArrayItem(typeof(UInt32FieldDefinition), ElementName = "UInt32")]
        [XmlArrayItem(typeof(Int64FieldDefinition), ElementName = "Int64")]
        [XmlArrayItem(typeof(UInt64FieldDefinition), ElementName = "UInt64")]
        [XmlArrayItem(typeof(SingleFieldDefinition), ElementName = "Single")]
        [XmlArrayItem(typeof(DoubleFieldDefinition), ElementName = "Double")]
        [XmlArrayItem(typeof(DecimalFieldDefinition), ElementName = "Decimal")]
        [XmlArrayItem(typeof(DateTimeFieldDefinition), ElementName = "DateTime")]
        [XmlArrayItem(typeof(TimeSpanFieldDefinition), ElementName = "TimeSpan")]
        [XmlArrayItem(typeof(GuidFieldDefinition), ElementName = "Guid")]
        [XmlArrayItem(typeof(StringFieldDefinition), ElementName = "String")]
        [XmlArrayItem(typeof(BinaryFieldDefinition), ElementName = "Binary")]
        [XmlArrayItem(typeof(SqlVariantFieldDefinition), ElementName = "SqlVariant")]
        [XmlArrayItem(typeof(HierarchyIdFieldDefinition), ElementName = "HierarchyId")]
        [XmlArrayItem(typeof(GeometryFieldDefinition), ElementName = "Geometry")]
        [XmlArrayItem(typeof(GeographyFieldDefinition), ElementName = "Geography")]
        [XmlArrayItem(typeof(XmlFieldDefinition), ElementName = "Xml")]
        [XmlArrayItem(typeof(ObjectFieldDefinition), ElementName = "Object")]
        [XmlArrayItem(typeof(EnumFieldDefinition), ElementName = "Enum")]
        public List<FieldDefinition> Fields { get => _fields; set => _fields = value; }
    }


}
