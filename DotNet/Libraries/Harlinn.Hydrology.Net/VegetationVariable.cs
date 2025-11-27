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
    /// Contains derived vegetation / canopy / root properties - unique for each HRU
    /// </summary>
    public class VegetationVariable
    {
        // derived properties (temporally variable)

        /// <summary>
        /// [m2/m2] Leaf Area Index
        /// </summary>
        public double LAI;
        /// <summary>
        /// [m2/m2] Stem Area Index
        /// </summary>
        public double SAI;
        /// <summary>
        /// [m]     vegetation height
        /// </summary>
        public double height;
        /// <summary>
        /// [mm]    rain storage capacity
        /// </summary>
        public double capacity;
        /// <summary>
        /// [mm SWE]snow storage capacity
        /// </summary>
        public double snow_capacity;
        /// <summary>
        /// [mm/s]  leaf conductance (same as stomatal conductance?)
        /// </summary>
        public double leaf_cond;
        /// <summary>
        /// [mm/s]  leaf conductance corrected for shelter & LAI
        /// </summary>
        public double canopy_conductance;
        /// <summary>
        /// [0..1]  percentage of rain intercepted  (only on canopy portion)
        /// </summary>
        public double rain_icept_pct;

        /// <summary>
        /// [0..1]  percentage of snow intercepted  (only on canopy portion)
        /// </summary>
        public double snow_icept_pct;

        /// <summary>
        /// [-]    accounts for sheltered leaves : about 0.5-1.0
        /// </summary>
        public double shelter_factor;
        /// <summary>
        /// [0..1] skyview factor, pct of ground visible from sky
        /// </summary>
        public double skyview_fact;

        /// <summary>
        /// [m]    surface roughness parameter for momentum transfer
        /// </summary>
        public double roughness;
        /// <summary>
        /// [m]    zero-plane displacement, height where wind vel. goes to zero
        /// </summary>
        public double zero_pln_disp;
        /// <summary>
        /// [m]    reference height for air properties above ground
        /// </summary>
        public double reference_height;

        // derived root properties (temporally variable)

        /// <summary>
        /// [mm/m2]root length per unit land area
        /// </summary>
        public double root_length;

        /// <summary>
        /// [d/mm] plant resistance to water flow
        /// </summary>
        public double resistivity;


        // other

        /// <summary>
        /// [m/m3] relative values of root length per unit volume
        /// </summary>
        public double rel_rootden;
        /// <summary>
        /// [d]    root resistance for layer
        /// </summary>
        public double root_resistance;
        /// <summary>
        /// [MPa]  modified Cowan alpha for layer
        /// </summary>
        public double cowan_alpha;


    }

}
