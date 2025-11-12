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

using static Harlinn.Hydrology.Constants;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Contains information that reflects a specific type of vegetation
    /// </summary>
    public class Vegetation
    {
        /// <summary>
        /// name of vegetation class
        /// </summary>
        string vegetation_name;

        //specified (required) properties

        /// <summary>
        /// [m]       maximum vegetation height
        /// </summary>
        double max_height;
        /// <summary>
        /// [mm/s]    maximum leaf conductance
        /// </summary>
        double max_leaf_cond;
        /// <summary>
        /// [m2/m2]   maximum Leaf Area Index
        /// </summary>
        double max_LAI;

        //estimable parameters - usually unchanged

        /// <summary>
        /// [-]       extinction coefficient used to calculate skyview factor; SVF=exp(-extinct*LAI)
        /// </summary>
        double svf_extinction;
        /// <summary>
        /// [-]       relates percentage of throughfall of rain to LAI+SAI (~0.06)
        /// </summary>
        double rain_icept_fact;
        /// <summary>
        /// [-]       relates percentage of throughfall of snow to LAI+SAI (~0.04)
        /// </summary>
        double snow_icept_fact;
        /// <summary>
        /// [0..1]    percentage of rain intercepted (maximum) (only on canopy portion)
        /// </summary>
        double rain_icept_pct;
        /// <summary>
        /// [0..1]    percentage of snow intercepted (maximum) (only on canopy portion)
        /// </summary>
        double snow_icept_pct;

        /// <summary>
        /// [m2/m3]   ratio of stem area index to height
        /// </summary>
        double SAI_ht_ratio;
        /// <summary>
        /// [0..1]    fraction of canopy attributed to tree trunk
        /// </summary>
        double trunk_fraction;
        /// <summary>
        /// [0..1]    ~0.03
        /// </summary>
        double stemflow_frac;

        /// <summary>
        /// [-]       visible/near-infrared albedo of leaf
        /// </summary>
        double albedo;

        /// <summary>
        /// [-]       albedo of wet leaf
        /// </summary>
        double albedo_wet;

        /// <summary>
        /// [m/m]     relative vegetation height over 12 mos (ht=rel_ht*max_ht)
        /// </summary>
        readonly double[] relative_ht = new double[12];
        /// <summary>
        /// [m/m]     relative vegetation LAI over 12 mos
        /// </summary>
        readonly double[] relative_LAI = new double[12];

        /// <summary>
        /// [mm]      maximum canopy storage capacity
        /// </summary>
        double max_capacity;
        /// <summary>
        /// [mm]      maximum canopy snow storage capacity
        /// </summary>
        double max_snow_capacity;
        /// <summary>
        /// [kg/m2]   maximum snow load on vegetation ~5.9-6.6 kg/m2
        /// </summary>
        double max_snow_load;
        /// <summary>
        /// [1/m2]    vegetation count per meter squared (range: 1.0-500.0; recommended 300.0 for crops and grass, 1.0 for forests and shrubs)
        /// </summary>
        double veg_dens;
        /// <summary>
        /// [m]       vegetation diameter (range 0.0-2.0; recommended 0.003 for crops and grass, 0.5-1.0 for forests and shrubs [m]
        /// </summary>
        double veg_diam;
        /// <summary>
        /// [-]       mBeta parameter
        /// </summary>
        double veg_mBeta;

        /// <summary>
        /// [MJ/m2/d/K] vegetation convection coefficient (multiplied by LAI) =~2.0
        /// </summary>
        double veg_conv_coeff;

        /// <summary>
        /// [0..1]    vegetation-based PET correction (multiplicative)
        /// </summary>
        double PET_veg_corr;

        /// <summary>
        /// [mm]      ratio of leaf liquid water capacity to LAI (~0.15)
        /// </summary>
        double Cap_LAI_ratio;
        /// <summary>
        /// [mm]      ratio of leaf snow water capacity to LAI (~0.6)
        /// </summary>
        double SnoCap_LAI_ratio;

        //root properties

        // [-]       extinction coefficient for roots, exp(-ext*z)
        double root_extinct;

        /// <summary>
        /// [mm/m2]   root length per unit canopy area
        /// </summary>
        double max_root_length;
        /// <summary>
        /// [d/mm]    1.0/max_conductivity
        /// </summary>
        double min_resistivity;
        /// <summary>
        /// [0..1]    fraction of plant resistance in xylem (used to calculate xylem resistance)
        /// </summary>
        double xylem_frac;
        /// <summary>
        /// [mm]      average root radius (used to calculate cowan alpha)
        /// </summary>
        double rootradius;
        /// <summary>
        /// [-mm]     minimum plant leaf water potential the critical potential at which stomates close
        /// </summary>
        double psi_critical;

        //special process-specific params (may not be used)

        /// <summary>
        /// [1/d]     drip proportion for bucket drip model: \math \f$ dS/dt=-dp*S \f$
        /// </summary>
        double drip_proportion;
        /// <summary>
        /// [mm/d]    maximum rate of rainfall interception
        /// </summary>
        double max_intercept_rate;
        /// <summary>
        /// [-]       crop heat unit maturity; level at which PET is maximized
        /// </summary>
        double CHU_maturity;

        //Transport parameters

        /// <summary>
        /// [-] vegetation-specific uptake factor
        /// </summary>
        readonly double[] uptake_moderator = new double[MAX_CONSTITUENTS]; 
    }

}
