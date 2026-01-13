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
/// Represents an element definition within an XML Schema, providing metadata and characteristics such as name, type,
/// derivation, and constraints.
/// </summary>
/// <remarks>Use this class to access schema element information, including its qualified name, type derivation,
/// default value, and blocking or finalization constraints. The properties expose details relevant for schema analysis,
/// validation, or code generation scenarios. This class does not perform schema validation or parsing; it is intended
/// for representing and querying schema element metadata.</remarks>
public class XmlSchemaElement
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
    readonly bool _isDefaultFixed = false;
    readonly bool _isAbstract = false;
    readonly bool _isNillable = false;
    readonly bool _mustBeQualified = false;
    readonly bool _isExtensionBlocked = false;
    readonly bool _isRestrictionBlocked = false;
    readonly bool _isSubstitutionBlocked = false;
    readonly bool _isFinalExtension = false;
    readonly bool _isFinalRestriction = false;
    readonly string? _defaultValue;

    public XmlSchemaElement( )
    {
    }

    public XmlSchemaElement(int xmlComponentId,
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
        bool isDefaultFixed,
        bool isAbstract,
        bool isNillable,
        bool mustBeQualified,
        bool isExtensionBlocked,
        bool isRestrictionBlocked,
        bool isSubstitutionBlocked,
        bool isFinalExtension,
        bool isFinalRestriction,
        string? defaultValue)
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
        _isDefaultFixed = isDefaultFixed;
        _isAbstract = isAbstract;
        _isNillable = isNillable;
        _mustBeQualified = mustBeQualified;
        _isExtensionBlocked = isExtensionBlocked;
        _isRestrictionBlocked = isRestrictionBlocked;
        _isSubstitutionBlocked = isSubstitutionBlocked;
        _isFinalExtension = isFinalExtension;
        _isFinalRestriction = isFinalRestriction;
        _defaultValue = defaultValue;
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
    public bool IsDefaultFixed => _isDefaultFixed;
    public bool IsAbstract => _isAbstract;
    public bool IsNillable => _isNillable;
    public bool MustBeQualified => _mustBeQualified;
    public bool IsExtensionBlocked => _isExtensionBlocked;
    public bool IsRestrictionBlocked => _isRestrictionBlocked;
    public bool IsSubstitutionBlocked => _isSubstitutionBlocked;
    public bool IsFinalExtension => _isFinalExtension;
    public bool IsFinalRestriction => _isFinalRestriction;
    public string? DefaultValue => _defaultValue;
}
