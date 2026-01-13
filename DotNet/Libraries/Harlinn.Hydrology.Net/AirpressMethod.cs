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
    /// Methods for estimating air pressure
    /// </summary>
    public enum AirpressMethod
    {
        /// <summary>
        /// standard atm pressure at 20C
        /// </summary>
        AIRPRESS_CONST,
        /// <summary>
        /// air pressure specified as time series at gauge
        /// </summary>
        AIRPRESS_DATA,
        /// <summary>
        /// power law correction for elevation (source unknown)
        /// </summary>
        AIRPRESS_BASIC,
        /// <summary>
        /// from UBC Watershed model - simple elevation correction
        /// </summary>
        AIRPRESS_UBC
    }






}
