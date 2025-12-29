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
        private List<ResultSetColumn> _columns = new List<ResultSetColumn>();

        [XmlArray("Columns")]
        [XmlArrayItem(typeof(BooleanResultSetColumn), ElementName = "Boolean")]
        [XmlArrayItem(typeof(ByteResultSetColumn), ElementName = "Byte")]
        [XmlArrayItem(typeof(SByteResultSetColumn), ElementName = "SByte")]
        [XmlArrayItem(typeof(CharResultSetColumn), ElementName = "Char")]
        [XmlArrayItem(typeof(Int16ResultSetColumn), ElementName = "Int16")]
        [XmlArrayItem(typeof(UInt16ResultSetColumn), ElementName = "UInt16")]
        [XmlArrayItem(typeof(Int32ResultSetColumn), ElementName = "Int32")]
        [XmlArrayItem(typeof(UInt32ResultSetColumn), ElementName = "UInt32")]
        [XmlArrayItem(typeof(Int64ResultSetColumn), ElementName = "Int64")]
        [XmlArrayItem(typeof(UInt64ResultSetColumn), ElementName = "UInt64")]
        [XmlArrayItem(typeof(SingleResultSetColumn), ElementName = "Single")]
        [XmlArrayItem(typeof(DoubleResultSetColumn), ElementName = "Double")]
        [XmlArrayItem(typeof(DecimalResultSetColumn), ElementName = "Decimal")]
        [XmlArrayItem(typeof(DateTimeResultSetColumn), ElementName = "DateTime")]
        [XmlArrayItem(typeof(TimeSpanResultSetColumn), ElementName = "TimeSpan")]
        [XmlArrayItem(typeof(GuidResultSetColumn), ElementName = "Guid")]
        [XmlArrayItem(typeof(StringResultSetColumn), ElementName = "String")]
        [XmlArrayItem(typeof(BinaryResultSetColumn), ElementName = "Binary")]
        [XmlArrayItem(typeof(SqlVariantResultSetColumn), ElementName = "SqlVariant")]
        [XmlArrayItem(typeof(HierarchyIdResultSetColumn), ElementName = "HierarchyId")]
        [XmlArrayItem(typeof(GeometryResultSetColumn), ElementName = "Geometry")]
        [XmlArrayItem(typeof(GeographyResultSetColumn), ElementName = "Geography")]
        [XmlArrayItem(typeof(XmlResultSetColumn), ElementName = "Xml")]
        [XmlArrayItem(typeof(ObjectResultSetColumn), ElementName = "Object")]
        [XmlArrayItem(typeof(EnumResultSetColumn), ElementName = "Enum")]
        public List<ResultSetColumn> Columns { get => _columns; set => _columns = value; }
    }

    public class StoredProcedureResultSet : ResultSet
    {
        StoredProcedureDefinition? _owner;
    }

    public class QueryResultSet : ResultSet
    {
        QueryDefinition? _owner;
    }



}
