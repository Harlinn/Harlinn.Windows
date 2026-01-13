/*
   Copyright 2024-2026 Espen Harlinn

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

using System.ComponentModel;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    [Serializable]
    public class ResultSet
    {
        private string _name = string.Empty;
        private string _namespace = string.Empty;
        private string _readerTypeName = string.Empty;
        private string _readerNamespace = string.Empty;
        private string _dataTypeName = string.Empty;
        private string _dataNamespace = string.Empty;

        private List<ResultSetColumn> _columns = new List<ResultSetColumn>();

        [XmlAttribute]
        public string Name { get => _name; set => _name = value; }
        [XmlAttribute, DefaultValue("")]
        public string Namespace { get => _namespace; set => _namespace = value; }
        [XmlAttribute, DefaultValue("")]
        public string ReaderTypeName { get => _readerTypeName; set => _readerTypeName = value; }
        [XmlAttribute, DefaultValue("")]
        public string ReaderNamespace { get => _readerNamespace; set => _readerNamespace = value; }
        [XmlAttribute, DefaultValue("")]
        public string DataTypeName { get => _dataTypeName; set => _dataTypeName = value; }
        [XmlAttribute, DefaultValue("")]
        public string DataNamespace { get => _dataNamespace; set => _dataNamespace = value; }


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
