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
/// Represents the placement details of an XML schema component, including its identifiers, occurrence constraints, and
/// default value information.
/// </summary>
/// <remarks>This class encapsulates metadata about how an XML schema component is positioned within a schema,
/// such as its unique identifiers, whether its default value is fixed, and the allowed number of occurrences. It is
/// typically used when processing or generating XML schemas that require explicit control over component placement and
/// constraints.</remarks>
public class XmlSchemaComponentPlacement
{
    readonly int _xmlComponentId = 0;
    readonly int _placementId = 0;
    readonly int _placedXmlComponentId = 0;
    readonly bool _isDefaultFixed = false;
    readonly int _minOccurences = 0;
    readonly int _maxOccurences = 0;
    readonly string? _defaultValue;

    public XmlSchemaComponentPlacement( )
    {
    }

    public XmlSchemaComponentPlacement(int xmlComponentId,
        int placementId,
        int placedXmlComponentId,
        bool isDefaultFixed,
        int minOccurences,
        int maxOccurences,
        string? defaultValue)
    {
        _xmlComponentId = xmlComponentId;
        _placementId = placementId;
        _placedXmlComponentId = placedXmlComponentId;
        _isDefaultFixed = isDefaultFixed;
        _minOccurences = minOccurences;
        _maxOccurences = maxOccurences;
        _defaultValue = defaultValue;
    }

    public int XmlComponentId => _xmlComponentId;
    public int PlacementId => _placementId;
    public int PlacedXmlComponentId => _placedXmlComponentId;
    public bool IsDefaultFixed => _isDefaultFixed;
    public int MinOccurences => _minOccurences;
    public int MaxOccurences => _maxOccurences;
    public string? DefaultValue => _defaultValue;
}
