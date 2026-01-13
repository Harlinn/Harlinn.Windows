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

public class CertificatesDataType
{
    readonly string _name = string.Empty;
    readonly int _certificateId = 0;
    readonly int? _principalId;
    readonly string _pvtKeyEncryptionType = string.Empty;
    readonly string? _pvtKeyEncryptionTypeDesc;
    readonly bool? _isActiveForBeginDialog;
    readonly string? _issuerName;
    readonly string? _certSerialNumber;
    readonly byte[]? _sid;
    readonly string? _stringSid;
    readonly string? _subject;
    readonly DateTime? _expiryDate;
    readonly DateTime? _startDate;
    readonly byte[] _thumbprint = Array.Empty<byte>();
    readonly string? _attestedBy;
    readonly DateTime? _pvtKeyLastBackupDate;
    readonly int? _keyLength;

    public CertificatesDataType( )
    {
    }

    public CertificatesDataType(string name,
        int certificateId,
        int? principalId,
        string pvtKeyEncryptionType,
        string? pvtKeyEncryptionTypeDesc,
        bool? isActiveForBeginDialog,
        string? issuerName,
        string? certSerialNumber,
        byte[]? sid,
        string? stringSid,
        string? subject,
        DateTime? expiryDate,
        DateTime? startDate,
        byte[] thumbprint,
        string? attestedBy,
        DateTime? pvtKeyLastBackupDate,
        int? keyLength)
    {
        _name = name;
        _certificateId = certificateId;
        _principalId = principalId;
        _pvtKeyEncryptionType = pvtKeyEncryptionType;
        _pvtKeyEncryptionTypeDesc = pvtKeyEncryptionTypeDesc;
        _isActiveForBeginDialog = isActiveForBeginDialog;
        _issuerName = issuerName;
        _certSerialNumber = certSerialNumber;
        _sid = sid;
        _stringSid = stringSid;
        _subject = subject;
        _expiryDate = expiryDate;
        _startDate = startDate;
        _thumbprint = thumbprint;
        _attestedBy = attestedBy;
        _pvtKeyLastBackupDate = pvtKeyLastBackupDate;
        _keyLength = keyLength;
    }

    public string Name => _name;
    public int CertificateId => _certificateId;
    public int? PrincipalId => _principalId;
    public string PvtKeyEncryptionType => _pvtKeyEncryptionType;
    public string? PvtKeyEncryptionTypeDesc => _pvtKeyEncryptionTypeDesc;
    public bool? IsActiveForBeginDialog => _isActiveForBeginDialog;
    public string? IssuerName => _issuerName;
    public string? CertSerialNumber => _certSerialNumber;
    public byte[]? Sid => _sid;
    public string? StringSid => _stringSid;
    public string? Subject => _subject;
    public DateTime? ExpiryDate => _expiryDate;
    public DateTime? StartDate => _startDate;
    public byte[] Thumbprint => _thumbprint;
    public string? AttestedBy => _attestedBy;
    public DateTime? PvtKeyLastBackupDate => _pvtKeyLastBackupDate;
    public int? KeyLength => _keyLength;
}
