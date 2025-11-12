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
    /// Class Type
    /// </summary>
    public enum ClassType
    {
        /// <summary>
        /// Soil class
        /// </summary>
        CLASS_SOIL,
        /// <summary>
        /// Vegetation class
        /// </summary>
        CLASS_VEGETATION,
        /// <summary>
        /// Landuse class
        /// </summary>
        CLASS_LANDUSE,
        /// <summary>
        /// Terrain class
        /// </summary>
        CLASS_TERRAIN,
        /// <summary>
        /// Transport class
        /// </summary>
        CLASS_TRANSPORT,
        /// <summary>
        /// Global parameter class
        /// </summary>
        CLASS_GLOBAL,
        /// <summary>
        /// Subbasin parameter class
        /// </summary>
        CLASS_SUBBASIN,
        /// <summary>
        /// Gauge parameter class
        /// </summary>
        CLASS_GAUGE,
        /// <summary>
        /// special flag to handle HRU type changes; not assoc. with parameters
        /// </summary>
        CLASS_HRUTYPE,
        CLASS_UNKNOWN
    }
}
