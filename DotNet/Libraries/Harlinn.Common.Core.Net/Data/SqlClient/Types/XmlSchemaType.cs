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
/// Represents an XML Schema type, including its identity, derivation, and structural characteristics as defined in an
/// XML schema collection.
/// </summary>
/// <remarks>Use this class to access metadata about an XML Schema type, such as its name, namespace, derivation
/// method, and content model. The properties provide information about the type's abstract status, content allowance,
/// and blocking or finalization constraints, which are relevant when validating or processing XML documents against
/// schema definitions.</remarks>
public class XmlSchemaType
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
    readonly bool _isAbstract = false;
    readonly bool _allowsMixedContent = false;
    readonly bool _isExtensionBlocked = false;
    readonly bool _isRestrictionBlocked = false;
    readonly bool _isFinalExtension = false;
    readonly bool _isFinalRestriction = false;
    readonly bool _isFinalListMember = false;
    readonly bool _isFinalUnionMember = false;

    public XmlSchemaType( )
    {
    }

    public XmlSchemaType(int xmlComponentId,
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
        bool isAbstract,
        bool allowsMixedContent,
        bool isExtensionBlocked,
        bool isRestrictionBlocked,
        bool isFinalExtension,
        bool isFinalRestriction,
        bool isFinalListMember,
        bool isFinalUnionMember)
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
        _isAbstract = isAbstract;
        _allowsMixedContent = allowsMixedContent;
        _isExtensionBlocked = isExtensionBlocked;
        _isRestrictionBlocked = isRestrictionBlocked;
        _isFinalExtension = isFinalExtension;
        _isFinalRestriction = isFinalRestriction;
        _isFinalListMember = isFinalListMember;
        _isFinalUnionMember = isFinalUnionMember;
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
    public bool IsAbstract => _isAbstract;
    public bool AllowsMixedContent => _allowsMixedContent;
    public bool IsExtensionBlocked => _isExtensionBlocked;
    public bool IsRestrictionBlocked => _isRestrictionBlocked;
    public bool IsFinalExtension => _isFinalExtension;
    public bool IsFinalRestriction => _isFinalRestriction;
    public bool IsFinalListMember => _isFinalListMember;
    public bool IsFinalUnionMember => _isFinalUnionMember;
}
