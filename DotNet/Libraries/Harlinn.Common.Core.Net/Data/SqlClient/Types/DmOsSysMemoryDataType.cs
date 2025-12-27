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

public class DmOsSysMemoryDataType
{
    readonly long _totalPhysicalMemoryKb = 0;
    readonly long _availablePhysicalMemoryKb = 0;
    readonly long _totalPageFileKb = 0;
    readonly long _availablePageFileKb = 0;
    readonly long _systemCacheKb = 0;
    readonly long _kernelPagedPoolKb = 0;
    readonly long _kernelNonpagedPoolKb = 0;
    readonly bool _systemHighMemorySignalState = false;
    readonly bool _systemLowMemorySignalState = false;
    readonly string _systemMemoryStateDesc = string.Empty;

    public DmOsSysMemoryDataType( )
    {
    }

    public DmOsSysMemoryDataType(long totalPhysicalMemoryKb,
        long availablePhysicalMemoryKb,
        long totalPageFileKb,
        long availablePageFileKb,
        long systemCacheKb,
        long kernelPagedPoolKb,
        long kernelNonpagedPoolKb,
        bool systemHighMemorySignalState,
        bool systemLowMemorySignalState,
        string systemMemoryStateDesc)
    {
        _totalPhysicalMemoryKb = totalPhysicalMemoryKb;
        _availablePhysicalMemoryKb = availablePhysicalMemoryKb;
        _totalPageFileKb = totalPageFileKb;
        _availablePageFileKb = availablePageFileKb;
        _systemCacheKb = systemCacheKb;
        _kernelPagedPoolKb = kernelPagedPoolKb;
        _kernelNonpagedPoolKb = kernelNonpagedPoolKb;
        _systemHighMemorySignalState = systemHighMemorySignalState;
        _systemLowMemorySignalState = systemLowMemorySignalState;
        _systemMemoryStateDesc = systemMemoryStateDesc;
    }

    public long TotalPhysicalMemoryKb => _totalPhysicalMemoryKb;
    public long AvailablePhysicalMemoryKb => _availablePhysicalMemoryKb;
    public long TotalPageFileKb => _totalPageFileKb;
    public long AvailablePageFileKb => _availablePageFileKb;
    public long SystemCacheKb => _systemCacheKb;
    public long KernelPagedPoolKb => _kernelPagedPoolKb;
    public long KernelNonpagedPoolKb => _kernelNonpagedPoolKb;
    public bool SystemHighMemorySignalState => _systemHighMemorySignalState;
    public bool SystemLowMemorySignalState => _systemLowMemorySignalState;
    public string SystemMemoryStateDesc => _systemMemoryStateDesc;
}
