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
    /// surface parameters
    /// </summary>
    public class Surface
    {
        /// <summary>
        /// name of land use linked to this data
        /// </summary>
        public string landuse_name;

        /// <summary>
        /// [-]       fraction of surface that is impermeable
        /// </summary>
        public double impermeable_frac;

        /// <summary>
        /// [m]       roughness parameter of ground surface
        /// </summary>
        public double roughness;

        // used for evapotranspiration calcs

        /// <summary>
        /// [0..1]    fraction of land covered by canopy
        /// </summary>
        public double forest_coverage;
        /// <summary>
        /// [0..1]    sparseness of canopy in land covered by forest
        /// </summary>
        public double forest_sparseness;
        /// <summary>
        /// [0..1]    effective forest cover for interception (C0TREE*C0CANY)
        /// </summary>
        public double UBC_icept_factor;
        /// <summary>
        /// [0..1]    fraction of land covered by streams/lakes/riparian vegetation
        /// </summary>
        public double stream_fraction;

        /// <summary>
        /// [0..1]    basin wind coefficient (1 for unforested areas)
        /// </summary>
        public double wind_exposure;
        /// <summary>
        /// [m/s]     minimum wind speed used in regression estimates of windspeed from T_min-T_max
        /// </summary>
        public double min_wind_speed;
        /// <summary>
        /// [m/s]     maximum wind speed used in regression estimates of windspeed from T_min-T_max
        /// </summary>
        public double max_wind_speed;

        // Snow parameters

        /// <summary>
        /// [mm/d/C]  maximum snow melt factor used in degree day and hybrid snowmelt models
        /// </summary>
        public double melt_factor;

        /// <summary>
        /// [mm/d/C]  minimum snow melt factor used in degree day and hybrid snowmelt models
        /// </summary>
        public double min_melt_factor;
        /// <summary>
        /// [mm/d/C]  maximum snow melt factor used in degree day and hybrid snowmelt models
        /// </summary>
        public double max_melt_factor;
        /// <summary>
        /// [C]       melting base temperature in degree day methods
        /// </summary>
        public double DD_melt_temp;

        /// <summary>
        /// [1/mm]    rate of increase of melt factor with cumulative snowmelt (Kcum in HMETS)
        /// </summary>
        public double DD_aggradation;

        /// <summary>
        /// [mm/d/C]  maximum refreeze factor used in degree day and hybrid snowmelt models
        /// </summary>
        public double refreeze_factor;
        /// <summary>
        /// [C]       degree day refreeze temperature (refreeze base temperature)
        /// </summary>
        public double DD_refreeze_temp;
        /// <summary>
        /// [-]       empirical exponent for DD freezing equation
        /// </summary>
        public double refreeze_exp;
        /// <summary>
        /// [-]       HBV snowmelt forest correction (MRF in HBV-EC)
        /// </summary>
        public double HBV_melt_for_corr;
        /// <summary>
        /// [-]       HBV snowmelt aspect correction (AM in HBV-EC)
        /// </summary>
        public double HBV_melt_asp_corr;
        /// <summary>
        /// [mm]      SWE limit below which snow does not completely cover ground.  Used as a threshold for snow-patching algorithms (default=0.0).
        /// </summary>
        public double snow_patch_limit;
        /// <summary>
        /// [m]       distance of unobstructed wind flow (g.t. 300m)
        /// </summary>
        public double fetch;
        /// <summary>
        /// [-]       convection melt multiplier
        /// </summary>
        public double conv_melt_mult;
        /// <summary>
        /// [-]       condensation melt multiplier
        /// </summary>
        public double cond_melt_mult;
        /// <summary>
        /// [-]       rain melt multiplier
        /// </summary>
        public double rain_melt_mult;
        /// <summary>
        /// [-]       blowing snow distribution parameter
        /// </summary>
        public double bsnow_distrib;
        /// <summary>
        /// [mmSWE]   height of snow above which potential melt energy doest reach lake ice
        /// </summary>
        public double lakesnow_buffer_ht;

        // Glacier parameters

        /// <summary>
        /// [-]     maximum linear storage coefficient for glacial melt =K*G
        /// </summary>
        public double glac_storage_coeff;

        /// <summary>
        /// [-]    degree day correction factor for glacial melt (MRG in HBV-EC)
        /// </summary>
        public double HBV_melt_glacier_corr;
        /// <summary>
        /// [-]       minimum linear storage coefficient for glacial melt =K*G (KG1 in HBV-EC)
        /// </summary>
        public double HBV_glacier_Kmin;
        /// <summary>
        /// [1/mm]    extinction coefficient for diminishing storage coefficient with snow depth atop glacier, AG (K=Kmin+(Kmax-Kmin)*exp(-ag*snow_depth))
        /// </summary>
        public double HBV_glacier_Ag;

        /// <summary>
        /// [1/d]     linear decay coefficient for decreasing cold content
        /// </summary>
        public double CC_decay_coeff;

        // runoff parameters

        /// <summary>
        /// [-]       SCS curve number (for antecedent wetness condition II)
        /// </summary>
        public double SCS_CN;
        /// <summary>
        /// [0..1]    simple partitioning coefficient: percentage of rainfall that runs off used for rational method
        /// </summary>
        public double partition_coeff;
        /// <summary>
        /// [0..1]    fraction of rainfall/melt which is initially abstracted to depression storage (default=0.2)
        /// </summary>
        public double SCS_Ia_fraction;
        /// <summary>
        /// [0..1]    HMETS algorithm runoff coeff - maximum fraction of ponded water which can infiltrate
        /// </summary>
        public double HMETS_runoff_coeff;

        // surface storage variables

        /// <summary>
        /// [-] PRMS maximum saturated area (pct)- user defined between 0.050 - 0.950
        /// </summary>
        public double max_sat_area_frac;

        /// <summary>
        /// [mm]      maximum amount of water that can be stored in depressions
        /// </summary>
        public double dep_max;

        /// <summary>
        /// [0..1]    percentage of rainfall/melt which is abstracted to depression storage
        /// </summary>
        public double abst_percent;

        /// <summary>
        /// [mm/d]    outflow rate with full depression storage (dep_stor=dep_max)
        /// </summary>
        public double dep_max_flow;

        /// <summary>
        /// [-]       power law coefficient for depression outflow
        /// </summary>
        public double dep_n;

        /// <summary>
        /// [mm]      threshold storage at which flow commences
        /// </summary>
        public double dep_threshold;

        /// <summary>
        /// [1/d]     linear overflow coefficient Q=k*(h-dep_threshold)
        /// </summary>
        public double dep_k;
        /// <summary>
        /// [1/d]     linear seepage coefficient Q=k*h
        /// </summary>
        public double dep_seep_k;
        /// <summary>
        /// -[m/m]     ratio of crest width to square root of HRU area (0-5) ~1.5
        /// </summary>
        public double dep_crestratio;
        /// <summary>
        /// [-]       PDMROF Pareto distribution function exponent
        /// </summary>
        public double PDMROF_b;
        /// <summary>
        /// [-]       PDM (Moore, 1985) Pareto distribution function exponent
        /// </summary>
        public double PDM_b;

        /// <summary>
        /// [0..1]    ET lower resistance parameter in HYMOD2 (Roy et al., 2017) AET calculation
        /// </summary>
        public double HYMOD2_G;

        /// <summary>
        /// [0..1]    ET resistance parameter in HYMOD2 (Roy et al., 2017) AET calculation
        /// </summary>
        public double HYMOD2_Kmax;
        /// <summary>
        /// [-]       ET exponent parameter in HYMOD2 (Roy et al., 2017) AET calculation
        /// </summary>
        public double HYMOD2_exp;
        /// <summary>
        /// [0..1]    maximum fraction of depression relative to total surface area
        /// </summary>
        public double max_dep_area_frac;

        /// <summary>
        /// [-]       exponent of depression surface area / depression storage relationship A~=(S/Smax)^n
        /// </summary>
        public double ponded_exp;
        /// <summary>
        /// [-]       upscaled wetland fill and spill b parameter, defined distribution of contributing area
        /// </summary>
        public double uwfs_b;
        /// <summary>
        /// [-]       upscaled wetland fill and spill betamin parameter, defined distribution of contributing area
        /// </summary>
        public double uwfs_betamin;
        /// <summary>
        /// [0..1]    fraction of baseflow which never reaches stream (in SAC-SMA) =1-1/(1+side)
        /// </summary>
        public double bf_loss_fraction;
        /// <summary>
        /// [0..1]    fraction of infiltration to smallest landscape store in AWBM model (nonzero)
        /// </summary>
        public double AWBM_areafrac1;
        /// <summary>
        /// [0..1]    fraction of infiltration to medium landscape store in AWBM model (nonzero)
        /// </summary>
        public double AWBM_areafrac2;
        /// <summary>
        /// [0..1]    fraction of excess going to groundwater in AWBM model
        /// </summary>
        public double AWBM_bflow_index;

        /// <summary>
        /// [-]       fraction of PET to apply to open water evaporation
        /// </summary>
        public double ow_PET_corr;
        /// <summary>
        /// [-]       fraction of PET to apply to lake evaporation
        /// </summary>
        public double lake_PET_corr;
        /// <summary>
        /// [-]       fraction of PET to apply to forest evapotranspiration
        /// </summary>
        public double forest_PET_corr;
        /// <summary>
        /// [-]       linear AET coefficient
        /// </summary>
        public double AET_coeff;
        /// <summary>
        /// [-]   Priestley-Taylor coefficient (defaults to 1.28)
        /// </summary>
        public double priestleytaylor_coeff;
        /// <summary>
        /// [mm/d/K]  linear PET relation with temperature ~(0.1-0.3)
        /// </summary>
        public double pet_lin_coeff;
        /// <summary>
        /// [mm/d/kPa] linear PET relation with vapor deficit ~(1-3 mm/d/kPa, ~1.5 for mountain streams)
        /// </summary>
        public double pet_vap_coeff;

        /// <summary>
        /// [-]       local correction factor for relative humidity (defaults to 1)
        /// </summary>
        public double relhum_corr;
        /// <summary>
        /// [-]       local correction factor for wind speed (defaults to 1)
        /// </summary>
        public double wind_vel_corr;

        /// <summary>
        /// [1/d]     linear lake storage coefficient
        /// </summary>
        public double lake_rel_coeff;

        /// <summary>
        /// [d]       GR4J time routing parameter
        /// </summary>
        public double GR4J_x4;
        /// <summary>
        /// [-]       gamma distribution shape parameter for convolution routing
        /// </summary>
        public double gamma_shape;
        /// <summary>
        /// [-]       gamma distribution scaling parameter for convolution routing
        /// </summary>
        public double gamma_scale;
        /// <summary>
        /// [-]       gamma distribution shape parameter for convolution routing (v2)
        /// </summary>
        public double gamma_shape2;
        /// <summary>
        /// [-]       gamma distribution scaling parameter for convolution routing (v2)
        /// </summary>
        public double gamma_scale2;
        /// <summary>
        /// [-]       sky view factor for estimating incoming longwave radiation (should be terrain param?)
        /// </summary>
        public double sky_view_factor;

        /// <summary>
        /// [MJ/m2/d/K] thermal convection coefficieint q=h(T_a-T)
        /// </summary>
        public double convection_coeff;
        /// <summary>
        /// [C/m]     local geothermal gradient (positive upward)
        /// </summary>
        public double geothermal_grad;
    }

}
