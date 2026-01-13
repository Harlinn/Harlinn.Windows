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
    /// Methods for interpolating Met Station/Gauge data to HRUs
    /// </summary>
    public enum InterpMethod
    {
        /// <summary>
        /// Interpolation by taking the average of all values
        /// </summary>
        INTERP_AVERAGE_ALL,
        /// <summary>
        /// Interpolation by assuming the value of the nearest-neighbour
        /// </summary>
        INTERP_NEAREST_NEIGHBOR,
        /// <summary>
        /// Interpolates by a average of all values, weighted by the inverse distance to the interpolated point
        /// </summary>
        INTERP_INVERSE_DISTANCE,
        /// <summary>
        /// Interpolates by a average of all values, weighted by the inverse elevation distance to the interpolated point
        /// </summary>
        INTERP_INVERSE_DISTANCE_ELEVATION,
        /// <summary>
        /// User-specified file used to specify interpolation weights for all HRUs
        /// </summary>
        INTERP_FROM_FILE
    }
}
