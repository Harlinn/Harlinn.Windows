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

public class DmOsHostInfoDataType
{
    readonly string _hostPlatform = string.Empty;
    readonly string _hostDistribution = string.Empty;
    readonly string _hostRelease = string.Empty;
    readonly string _hostServicePackLevel = string.Empty;
    readonly int? _hostSku;
    readonly int _osLanguageVersion = 0;
    readonly string _hostArchitecture = string.Empty;

    public DmOsHostInfoDataType( )
    {
    }

    public DmOsHostInfoDataType(string hostPlatform,
        string hostDistribution,
        string hostRelease,
        string hostServicePackLevel,
        int? hostSku,
        int osLanguageVersion,
        string hostArchitecture)
    {
        _hostPlatform = hostPlatform;
        _hostDistribution = hostDistribution;
        _hostRelease = hostRelease;
        _hostServicePackLevel = hostServicePackLevel;
        _hostSku = hostSku;
        _osLanguageVersion = osLanguageVersion;
        _hostArchitecture = hostArchitecture;
    }

    public string HostPlatform => _hostPlatform;
    public string HostDistribution => _hostDistribution;
    public string HostRelease => _hostRelease;
    public string HostServicePackLevel => _hostServicePackLevel;
    public int? HostSku => _hostSku;
    public int OsLanguageVersion => _osLanguageVersion;
    public string HostArchitecture => _hostArchitecture;
}
