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
/// Represents an XML Schema wildcard component, providing metadata and configuration for schema elements that allow
/// extensibility through namespace wildcards.
/// </summary>
/// <remarks>Use this class to access information about an XML Schema wildcard, such as its qualification,
/// associated namespaces, derivation, and processing rules. Wildcards are commonly used in XML Schema to permit
/// elements or attributes from namespaces not explicitly defined in the schema. This type exposes properties describing
/// the wildcard's scope, kind, derivation, and content processing behavior, which can be useful for schema analysis,
/// validation, or tooling scenarios.</remarks>
public class XmlSchemaWildcard
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
    readonly string _processContent = string.Empty;
    readonly string? _processContentDesc;
    readonly bool _disallowNamespaces = false;

    public XmlSchemaWildcard( )
    {
    }

    public XmlSchemaWildcard(int xmlComponentId,
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
        string processContent,
        string? processContentDesc,
        bool disallowNamespaces)
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
        _processContent = processContent;
        _processContentDesc = processContentDesc;
        _disallowNamespaces = disallowNamespaces;
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
    public string ProcessContent => _processContent;
    public string? ProcessContentDesc => _processContentDesc;
    public bool DisallowNamespaces => _disallowNamespaces;
}
