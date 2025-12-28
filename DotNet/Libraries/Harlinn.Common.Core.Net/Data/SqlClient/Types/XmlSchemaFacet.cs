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
using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

/// <summary>
/// Represents a facet of an XML schema component, such as a restriction or constraint applied to a data type.
/// </summary>
/// <remarks>Facets are used in XML Schema to define additional rules or limitations for data types, such as
/// minimum or maximum values, patterns, or fixed values. This class provides information about a specific facet,
/// including its type, description, and value. Instances of this class are typically used when analyzing or processing
/// XML schema definitions.</remarks>
public class XmlSchemaFacet
{
    readonly int _xmlComponentId = 0;
    readonly int _facetId = 0;
    readonly string _kind = string.Empty;
    readonly string? _kindDesc;
    readonly bool _isFixed = false;
    readonly string? _value;

    public XmlSchemaFacet( )
    {
    }

    public XmlSchemaFacet(int xmlComponentId,
        int facetId,
        string kind,
        string? kindDesc,
        bool isFixed,
        string? value)
    {
        _xmlComponentId = xmlComponentId;
        _facetId = facetId;
        _kind = kind;
        _kindDesc = kindDesc;
        _isFixed = isFixed;
        _value = value;
    }

    public int XmlComponentId => _xmlComponentId;
    public int FacetId => _facetId;
    public string Kind => _kind;
    public string? KindDesc => _kindDesc;
    public bool IsFixed => _isFixed;
    public string? Value => _value;
}
