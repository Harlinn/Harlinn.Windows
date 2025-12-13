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

namespace Harlinn.MSSql.Tool.Input.Types
{
    [Serializable]
    public class GuidFieldDefinition : FieldDefinition
    {
        public override FieldType FieldType => FieldType.Guid;
    }

    [Serializable]
    public class SqlVariantFieldDefinition : FieldDefinition
    {
        public override FieldType FieldType => FieldType.SqlVariant;
    }

    [Serializable]
    public class HierarchyIdFieldDefinition : FieldDefinition
    {
        public override FieldType FieldType => FieldType.HierarchyId;
    }

    [Serializable]
    public class GeometryFieldDefinition : FieldDefinition
    {
        public override FieldType FieldType => FieldType.Geometry;
    }

    [Serializable]
    public class GeographyFieldDefinition : FieldDefinition
    {
        public override FieldType FieldType => FieldType.Geography;
    }

    [Serializable]
    public class XmlFieldDefinition : FieldDefinition
    {
        public override FieldType FieldType => FieldType.Xml;
    }

    [Serializable]
    public class TypedFieldDefinition : FieldDefinition
    {
        public override FieldType FieldType => FieldType.Typed;
    }


}