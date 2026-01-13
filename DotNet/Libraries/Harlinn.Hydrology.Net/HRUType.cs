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
namespace Harlinn.Hydrology
{
    /// <summary>
    /// Types of HRUs
    /// </summary>
    /// <remarks>
    /// Lake, Rock, and Glacier types are special because there is no soil storage
    /// </remarks>
    public enum HRUType
    {
        /// <summary>
        /// Standard HRU
        /// </summary>
        HRU_STANDARD,
        /// <summary>
        /// Lake HRU
        /// </summary>
        HRU_LAKE,
        /// <summary>
        /// Non-lake Waterbody HRU (streams)
        /// </summary>
        HRU_WATER,
        /// <summary>
        /// Glacier HRU
        /// </summary>
        HRU_GLACIER,
        /// <summary>
        /// Wetland HRU
        /// </summary>
        HRU_WETLAND,
        /// <summary>
        /// Open Rock or Pavement (impermeable) HRUs
        /// </summary>
        HRU_ROCK,
        /// <summary>
        /// returned if type is invalid
        /// </summary>
        HRU_INVALID_TYPE
    }
}
