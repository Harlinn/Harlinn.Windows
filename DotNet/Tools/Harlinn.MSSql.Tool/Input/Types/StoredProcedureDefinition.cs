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

using Harlinn.Common.Core.Net.Data.SqlClient;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;
using Harlinn.MSSql.Tool.Import;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Management.Smo;
using System.ComponentModel;
using System.Xml.Serialization;

namespace Harlinn.MSSql.Tool.Input.Types
{
    [Serializable]
    public class StoredProcedureDefinition : SchemaObject
    {
        private List<ParameterDefinition> _parameters = new List<ParameterDefinition>();
        private List<StoredProcedureResultSet> _resultSets = new List<StoredProcedureResultSet>();

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
        public List<ParameterDefinition> Parameters { get => _parameters; set => _parameters = value; }


        [XmlArray("ResultSets"), DefaultValue(null)]
        [XmlArrayItem(typeof(StoredProcedureResultSet), ElementName = "ResultSet")]
        public List<StoredProcedureResultSet>? ResultSetsOrNull
        {
            get
            {
                if (_resultSets.Count == 0)
                {
                    return null;
                }
                return _resultSets;
            }
            set
            {
                if (value == null)
                {
                    _resultSets.Clear();
                }
                else
                {
                    _resultSets = value;
                }
            }
        }


        [XmlIgnore]
        public List<StoredProcedureResultSet> ResultSets { get => _resultSets; set => _resultSets = value; }

        int IndexOfParameter(string name)
        {
            for (int i = 0; i < Parameters.Count; i++)
            {
                if (string.Equals(Parameters[i].Name, name, StringComparison.OrdinalIgnoreCase))
                {
                    return i;
                }
            }
            return -1;
        }

        internal void ImportParameters(SqlConnection sqlConnection, Procedure procedure)
        {
            if (procedure == null)
            {
                throw new ArgumentNullException(nameof(procedure));
            }

            var parameters = sqlConnection.GetParameters(procedure);

            foreach (var parameter in parameters)
            {

                var parameterDefinition = parameter.ToParameterDefinition(sqlConnection);
                var index = IndexOfParameter(parameterDefinition.Name);
                if (index >= 0)
                {
                    Parameters[index] = parameterDefinition;
                }
                else
                {
                    Parameters.Add(parameterDefinition);
                }
            }
        }

        internal void ImportProcedure(SqlConnection sqlConnection, Procedure procedure)
        {
            if (procedure == null)
            {
                throw new ArgumentNullException(nameof(procedure));
            }
            ImportParameters(sqlConnection, procedure);
            if (string.IsNullOrEmpty(Description))
            {
                Description = sqlConnection.GetObjectDescription(procedure.ObjectId);
            }
        }
    }



}
