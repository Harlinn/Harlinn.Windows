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

using Microsoft.Data.SqlClient;
using System.Xml.Serialization;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.MSSql.Tool.Input.Types
{
    [Serializable]
    public class StoredProcedureDefinition : SchemaObject
    {
        public override SchemaObjectType Type => SchemaObjectType.StoredProcedure;


        [XmlArray("Parameters")]
        [XmlArrayItem(typeof(BooleanParameterDefinition), ElementName = "Boolean")]
        [XmlArrayItem(typeof(ByteParameterDefinition), ElementName = "Byte")]
        [XmlArrayItem(typeof(SByteParameterDefinition), ElementName = "SByte")]
        [XmlArrayItem(typeof(CharParameterDefinition), ElementName = "Char")]
        [XmlArrayItem(typeof(Int16ParameterDefinition), ElementName = "Int16")]
        [XmlArrayItem(typeof(UInt16ParameterDefinition), ElementName = "UInt16")]
        [XmlArrayItem(typeof(Int32ParameterDefinition), ElementName = "Int32")]
        [XmlArrayItem(typeof(UInt32ParameterDefinition), ElementName = "UInt32")]
        [XmlArrayItem(typeof(Int64ParameterDefinition), ElementName = "Int64")]
        [XmlArrayItem(typeof(UInt64ParameterDefinition), ElementName = "UInt64")]
        [XmlArrayItem(typeof(SingleParameterDefinition), ElementName = "Single")]
        [XmlArrayItem(typeof(DoubleParameterDefinition), ElementName = "Double")]
        [XmlArrayItem(typeof(DecimalParameterDefinition), ElementName = "Decimal")]
        [XmlArrayItem(typeof(DateTimeParameterDefinition), ElementName = "DateTime")]
        [XmlArrayItem(typeof(TimeSpanParameterDefinition), ElementName = "TimeSpan")]
        [XmlArrayItem(typeof(GuidParameterDefinition), ElementName = "Guid")]
        [XmlArrayItem(typeof(StringParameterDefinition), ElementName = "String")]
        [XmlArrayItem(typeof(BinaryParameterDefinition), ElementName = "Binary")]
        [XmlArrayItem(typeof(SqlVariantParameterDefinition), ElementName = "SqlVariant")]
        [XmlArrayItem(typeof(HierarchyIdParameterDefinition), ElementName = "HierarchyId")]
        [XmlArrayItem(typeof(GeometryParameterDefinition), ElementName = "Geometry")]
        [XmlArrayItem(typeof(GeographyParameterDefinition), ElementName = "Geography")]
        [XmlArrayItem(typeof(XmlParameterDefinition), ElementName = "Xml")]
        [XmlArrayItem(typeof(ObjectParameterDefinition), ElementName = "Object")]
        [XmlArrayItem(typeof(EnumParameterDefinition), ElementName = "Enum")]
        public List<ParameterDefinition> Parameters { get; set; } = new List<ParameterDefinition>();

        internal void ImportProcedure(SqlConnection sqlConnection, Procedure procedure)
        {
            
        }
    }



}
