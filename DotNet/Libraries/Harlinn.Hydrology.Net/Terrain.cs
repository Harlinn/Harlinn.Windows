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
    /// Terrain properties
    /// </summary>
    public class Terrain
    {
        /// <summary>
        /// [km/km2] length of *all* rivers in a basin divided by the area of the drainage basin
        /// </summary>
        public double drainage_density;
        /// <summary>
        /// [m]      representative hillslope length within the watershed
        /// </summary>
        public double hillslope_length;

        /// <summary>
        /// [m]      TOPMODEL mean of the log-transformed topographic index (between 5.0 - 10.0)
        /// </summary>
        public double topmodel_lambda;
    }

}
