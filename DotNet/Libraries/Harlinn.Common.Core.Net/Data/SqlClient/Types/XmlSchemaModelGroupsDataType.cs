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

public class XmlSchemaModelGroupsDataType
{
    readonly int _xmlComponentId = 0;
    readonly int _xmlCollectionId = 0;
    readonly int _xmlNamespaceId = 0;
    readonly bool _isQualified = false;
    readonly string? _name;
    readonly string _symbolSpace = string.Empty;
    readonly string? _symbolSpaceDesc;
    readonly string _kind = string.Empty;
    readonly string? _kindDesc;
    readonly string _derivation = string.Empty;
    readonly string? _derivationDesc;
    readonly int? _baseXmlComponentId;
    readonly int? _scopingXmlComponentId;
    readonly string _compositor = string.Empty;
    readonly string? _compositorDesc;

    public XmlSchemaModelGroupsDataType( )
    {
    }

    public XmlSchemaModelGroupsDataType(int xmlComponentId,
        int xmlCollectionId,
        int xmlNamespaceId,
        bool isQualified,
        string? name,
        string symbolSpace,
        string? symbolSpaceDesc,
        string kind,
        string? kindDesc,
        string derivation,
        string? derivationDesc,
        int? baseXmlComponentId,
        int? scopingXmlComponentId,
        string compositor,
        string? compositorDesc)
    {
        _xmlComponentId = xmlComponentId;
        _xmlCollectionId = xmlCollectionId;
        _xmlNamespaceId = xmlNamespaceId;
        _isQualified = isQualified;
        _name = name;
        _symbolSpace = symbolSpace;
        _symbolSpaceDesc = symbolSpaceDesc;
        _kind = kind;
        _kindDesc = kindDesc;
        _derivation = derivation;
        _derivationDesc = derivationDesc;
        _baseXmlComponentId = baseXmlComponentId;
        _scopingXmlComponentId = scopingXmlComponentId;
        _compositor = compositor;
        _compositorDesc = compositorDesc;
    }

    public int XmlComponentId => _xmlComponentId;
    public int XmlCollectionId => _xmlCollectionId;
    public int XmlNamespaceId => _xmlNamespaceId;
    public bool IsQualified => _isQualified;
    public string? Name => _name;
    public string SymbolSpace => _symbolSpace;
    public string? SymbolSpaceDesc => _symbolSpaceDesc;
    public string Kind => _kind;
    public string? KindDesc => _kindDesc;
    public string Derivation => _derivation;
    public string? DerivationDesc => _derivationDesc;
    public int? BaseXmlComponentId => _baseXmlComponentId;
    public int? ScopingXmlComponentId => _scopingXmlComponentId;
    public string Compositor => _compositor;
    public string? CompositorDesc => _compositorDesc;
}
