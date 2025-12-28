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
/// Represents a row from the sys.trusted_assemblies catalog view.
/// </summary>
public class TrustedAssembly
{
    readonly byte[]? _hash;
    readonly string? _description;
    readonly DateTime _createDate;
    readonly string _createdBy = string.Empty;

    public TrustedAssembly( )
    {
    }

    public TrustedAssembly(byte[]? hash,
        string? description,
        DateTime createDate,
        string createdBy)
    {
        _hash = hash;
        _description = description;
        _createDate = createDate;
        _createdBy = createdBy;
    }

    public byte[]? Hash => _hash;
    public string? Description => _description;
    public DateTime CreateDate => _createDate;
    public string CreatedBy => _createdBy;
}
