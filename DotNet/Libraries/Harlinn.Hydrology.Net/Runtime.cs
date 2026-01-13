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
﻿

namespace Harlinn.Hydrology
{
    public class Runtime
    {
        public static void FinalizeGracefully(string statement, ExitCode code)
        {
            // Implementation for graceful finalization
        }

        public static void ExitGracefully(string statement, ExitCode code)
        {
            // Implementation for graceful exit
        }

        public static void ExitGracefullyIf(bool condition, string statement, ExitCode code)
        {
            if (condition)
            {
                ExitGracefully(statement, code);
            }
        }

        internal static void WriteWarning(string warn, bool v)
        {
            throw new NotImplementedException();
        }

        internal static void WriteWarning(string warningMessage, ExitCode bAD_DATA_WARN)
        {
            throw new NotImplementedException();
        }

        internal static void WriteAdvisory(string warn, bool noisy)
        {
            throw new NotImplementedException();
        }
    }
}
