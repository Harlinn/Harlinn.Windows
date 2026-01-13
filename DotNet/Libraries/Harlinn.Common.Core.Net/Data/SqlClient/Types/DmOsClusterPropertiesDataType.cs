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

public class DmOsClusterPropertiesDataType
{
    readonly long? _verboselogging;
    readonly long? _sqldumperdumpflags;
    readonly string _sqldumperdumppath = string.Empty;
    readonly long? _sqldumperdumptimeout;
    readonly long? _failureconditionlevel;
    readonly long? _healthchecktimeout;

    public DmOsClusterPropertiesDataType( )
    {
    }

    public DmOsClusterPropertiesDataType(long? verboselogging,
        long? sqldumperdumpflags,
        string sqldumperdumppath,
        long? sqldumperdumptimeout,
        long? failureconditionlevel,
        long? healthchecktimeout)
    {
        _verboselogging = verboselogging;
        _sqldumperdumpflags = sqldumperdumpflags;
        _sqldumperdumppath = sqldumperdumppath;
        _sqldumperdumptimeout = sqldumperdumptimeout;
        _failureconditionlevel = failureconditionlevel;
        _healthchecktimeout = healthchecktimeout;
    }

    public long? Verboselogging => _verboselogging;
    public long? Sqldumperdumpflags => _sqldumperdumpflags;
    public string Sqldumperdumppath => _sqldumperdumppath;
    public long? Sqldumperdumptimeout => _sqldumperdumptimeout;
    public long? Failureconditionlevel => _failureconditionlevel;
    public long? Healthchecktimeout => _healthchecktimeout;
}
