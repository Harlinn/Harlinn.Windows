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

public class DmOsWindowsInfoDataType
{
    readonly string _windowsRelease = string.Empty;
    readonly string _windowsServicePackLevel = string.Empty;
    readonly int? _windowsSku;
    readonly int _osLanguageVersion = 0;

    public DmOsWindowsInfoDataType( )
    {
    }

    public DmOsWindowsInfoDataType(string windowsRelease,
        string windowsServicePackLevel,
        int? windowsSku,
        int osLanguageVersion)
    {
        _windowsRelease = windowsRelease;
        _windowsServicePackLevel = windowsServicePackLevel;
        _windowsSku = windowsSku;
        _osLanguageVersion = osLanguageVersion;
    }

    public string WindowsRelease => _windowsRelease;
    public string WindowsServicePackLevel => _windowsServicePackLevel;
    public int? WindowsSku => _windowsSku;
    public int OsLanguageVersion => _osLanguageVersion;
}
