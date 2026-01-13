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
    /// Methods of handling upstream allocation of downstream irrigation demand
    /// </summary>
    public enum DemandAlloc
    {
        /// <summary>
        /// downstream demand support weighted by maximum storage capacity of reservoir
        /// </summary>
        DEMANDBY_MAX_CAPACITY,
        /// <summary>
        /// downstream demand support weighted by contributing area to reservoir
        /// </summary>
        DEMANDBY_CONTRIB_AREA,
        /// <summary>
        /// downstream demand support weighted inversely to storage deficit
        /// </summary>
        DEMANDBY_STOR_DEFICIT
    }
}
