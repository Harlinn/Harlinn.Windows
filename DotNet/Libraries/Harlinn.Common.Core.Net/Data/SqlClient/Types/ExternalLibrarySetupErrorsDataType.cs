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

public class ExternalLibrarySetupErrorsDataType
{
    readonly int _dbId = 0;
    readonly int _principalId = 0;
    readonly int _externalLibraryId = 0;
    readonly int _errorCode = 0;
    readonly DateTime _errorTimestamp;
    readonly string? _errorMessage;

    public ExternalLibrarySetupErrorsDataType( )
    {
    }

    public ExternalLibrarySetupErrorsDataType(int dbId,
        int principalId,
        int externalLibraryId,
        int errorCode,
        DateTime errorTimestamp,
        string? errorMessage)
    {
        _dbId = dbId;
        _principalId = principalId;
        _externalLibraryId = externalLibraryId;
        _errorCode = errorCode;
        _errorTimestamp = errorTimestamp;
        _errorMessage = errorMessage;
    }

    public int DbId => _dbId;
    public int PrincipalId => _principalId;
    public int ExternalLibraryId => _externalLibraryId;
    public int ErrorCode => _errorCode;
    public DateTime ErrorTimestamp => _errorTimestamp;
    public string? ErrorMessage => _errorMessage;
}
