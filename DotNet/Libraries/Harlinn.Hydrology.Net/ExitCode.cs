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
namespace Harlinn.Hydrology
{
    /// <summary>
    /// Series of codes containing possible reasons for exiting
    /// </summary>
    public enum ExitCode
    {
        /// <summary>
        /// For bad input provided by user (requires immediate exit from program)
        /// </summary>
        BAD_DATA,
        /// <summary>
        /// For bad input provided by user (requires shutdown prior to simulation)
        /// </summary>
        BAD_DATA_WARN,
        /// <summary>
        /// For runtime error (bad programming)
        /// </summary>
        RUNTIME_ERR,
        /// <summary>
        /// For bad file open (requires immediate exit)
        /// </summary>
        FILE_OPEN_ERR,
        /// <summary>
        /// for bad RavenErrors.txt file open
        /// </summary>
        RAVEN_OPEN_ERR,
        /// <summary>
        /// Stub function
        /// </summary>
        STUB,
        /// <summary>
        /// When out of memory
        /// </summary>
        OUT_OF_MEMORY,
        /// <summary>
        /// Upon completion of the simulation
        /// </summary>
        SIMULATION_DONE
    };

}
