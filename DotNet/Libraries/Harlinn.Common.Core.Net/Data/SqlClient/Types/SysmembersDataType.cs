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

public class SysmembersDataType
{
    readonly short? _memberuid;
    readonly short? _groupuid;

    public SysmembersDataType( )
    {
    }

    public SysmembersDataType(short? memberuid,
        short? groupuid)
    {
        _memberuid = memberuid;
        _groupuid = groupuid;
    }

    public short? Memberuid => _memberuid;
    public short? Groupuid => _groupuid;
}
