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
    /// Methods of aggregating geographical coverage
    /// </summary>
    public enum ApatialAgg
    {
        /// <summary>
        /// Aggregate by HRU
        /// </summary>
        BY_HRU,
        /// <summary>
        /// Aggregate by drainage basin
        /// </summary>
        BY_BASIN,
        /// <summary>
        /// Aggregate by watershed
        /// </summary>
        BY_WSHED,
        /// <summary>
        /// Aggregate by HRU group
        /// </summary>
        BY_HRU_GROUP,
        /// <summary>
        /// Aggregate by SubBasin group
        /// </summary>
        BY_SB_GROUP,
        /// <summary>
        /// Aggregate by HRU, but only include one HRU Group
        /// </summary>
        BY_SELECT_HRUS
    }




}
