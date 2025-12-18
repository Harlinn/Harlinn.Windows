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

using System.Reflection.Metadata;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    [Serializable]
    public abstract class ObjectDefinition : TypeDefinition
    {
        [XmlIgnore]
        Dictionary<string, PropertyDefinition> PropertiesByName { get; set; } = new Dictionary<string, PropertyDefinition>();

        [XmlArray("Properties")]
        [XmlArrayItem(typeof(BooleanPropertyDefinition), ElementName = "Boolean")]
        [XmlArrayItem(typeof(SBytePropertyDefinition), ElementName = "SByte")]
        [XmlArrayItem(typeof(BytePropertyDefinition), ElementName = "Byte")]
        [XmlArrayItem(typeof(CharPropertyDefinition), ElementName = "Char")]
        [XmlArrayItem(typeof(Int16PropertyDefinition), ElementName = "Int16")]
        [XmlArrayItem(typeof(UInt16PropertyDefinition), ElementName = "UInt16")]
        [XmlArrayItem(typeof(Int32PropertyDefinition), ElementName = "Int32")]
        [XmlArrayItem(typeof(UInt32PropertyDefinition), ElementName = "UInt32")]
        [XmlArrayItem(typeof(Int64PropertyDefinition), ElementName = "Int64")]
        [XmlArrayItem(typeof(UInt64PropertyDefinition), ElementName = "UInt64")]
        [XmlArrayItem(typeof(SinglePropertyDefinition), ElementName = "Single")]
        [XmlArrayItem(typeof(DoublePropertyDefinition), ElementName = "Double")]
        [XmlArrayItem(typeof(DecimalPropertyDefinition), ElementName = "Decimal")]
        [XmlArrayItem(typeof(DateTimePropertyDefinition), ElementName = "DateTime")]
        [XmlArrayItem(typeof(TimeSpanPropertyDefinition), ElementName = "TimeSpan")]
        [XmlArrayItem(typeof(GuidPropertyDefinition), ElementName = "Guid")]
        [XmlArrayItem(typeof(StringPropertyDefinition), ElementName = "String")]
        [XmlArrayItem(typeof(BinaryPropertyDefinition), ElementName = "Binary")]
        [XmlArrayItem(typeof(EnumPropertyDefinition), ElementName = "Enum")]
        [XmlArrayItem(typeof(ObjectPropertyDefinition), ElementName = "Object")]
        public List<PropertyDefinition> Properties { get; set; } = new List<PropertyDefinition>();

        internal override void Initialize()
        {
            base.Initialize();
            PropertiesByName.Clear();
            foreach (var property in Properties)
            {
                property.Owner = this;
                PropertiesByName[property.Name] = property;
                property.Initialize();
            }
        }

        internal override void Initialize2()
        {
            base.Initialize2();

            foreach (var property in Properties)
            {
                property.Initialize2();
            }
        }




    }



}
