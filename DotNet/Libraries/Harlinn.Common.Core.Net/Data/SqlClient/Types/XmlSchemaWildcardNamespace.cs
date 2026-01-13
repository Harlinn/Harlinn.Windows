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
using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

/// <summary>
/// Represents a namespace specification used in XML schema wildcards, associating a component identifier with a
/// namespace URI.
/// </summary>
/// <remarks>Use this class to encapsulate the namespace and component information for XML schema elements that
/// support wildcard namespace matching. Instances are typically used when processing or validating XML schemas that
/// include wildcard elements or attributes.</remarks>
public class XmlSchemaWildcardNamespace
{
    readonly int _xmlComponentId = 0;
    readonly string _namespace = string.Empty;

    public XmlSchemaWildcardNamespace( )
    {
    }

    public XmlSchemaWildcardNamespace(int xmlComponentId,
        string namespace__)
    {
        _xmlComponentId = xmlComponentId;
        _namespace = namespace__;
    }

    public int XmlComponentId => _xmlComponentId;
    public string Namespace => _namespace;
}
