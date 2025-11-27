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
    /// Contains information that reflects a specific soil type.
    /// </summary>
    public class Soil
    {
        //specified (required) parameters

        /// <summary>
        /// [0..1]    organic content ratio
        /// </summary>
        double _organicContent;
        /// <summary>
        /// [0..1]    sand content ratio
        /// </summary>
        double _sandContent;
        /// <summary>
        /// [0..1]    clay content ratio
        /// </summary>
        double _clayContent;

        // specified or automatically calculated parameters
        // standard soil parameters

        /// <summary>
        /// [0..1]    soil porosity
        /// </summary>
        double _porosity;
        /// <summary>
        /// [0..1]    stone volume fraction
        /// </summary>
        double _stoneFraction;

        /// <summary>
        /// [kg/m3]   bulk dry density
        /// </summary>
        double _bulkDensity;

        /// <summary>
        /// [-] total water storage cap.=thick*_capRatio ; _capRatio=poro*(1-stone_f)
        /// </summary>
        double _capRatio;

        // Thermal properties

        /// <summary>
        /// [MJ/m3/K]   saturated *volumetric* heat capacity
        /// </summary>
        double _heatCapacity;
        /// <summary>
        /// [MJ/m/d/K]  saturated soil thermal conductivity
        /// </summary>
        double _thermalCond;
        /// <summary>
        /// [C] soil freezing point
        /// </summary>
        double _freezingPoint;

        //unsaturated flow parameters

        /// <summary>
        /// [mm/d]  saturated hydraulic conductivity
        /// </summary>
        double hydraul_cond;
        /// <summary>
        /// [-] clapp-hornberger exponent  \math \f$ {\psi}={\psi_a}*S^{-b} \f$
        /// </summary>
        double clapp_b;
        /// <summary>
        /// [-] clapp-hornberger transition parameters for high saturation: \math \f$ {\psi}=m * (S - n) * (S - 1)\f$
        /// </summary>
        double clapp_n;
        /// <summary>
        /// [mm] clapp-hornberger transition parameters for high saturation: \math \f$ {\psi}=m * (S - n) * (S - 1)\f$
        /// </summary>
        double clapp_m;
        /// <summary>
        /// [0..1] Hydroscopic minimum saturation / residual saturation
        /// </summary>
        double sat_res;
        /// <summary>
        /// [0..1]    wilting point saturation
        /// </summary>
        double sat_wilt;
        /// <summary>
        /// [0..1]    saturation at field capacity
        /// </summary>
        double field_capacity;
        /// <summary>
        /// [-mm]     air entry pressure (a positive value)
        /// </summary>
        double air_entry_pressure;
        /// <summary>
        /// [-mm]     Wilting pressure
        /// </summary>
        double wilting_pressure;
        /// <summary>
        /// [-mm]     Wetting front matric potential (for GA model)
        /// </summary>
        double wetting_front_psi;
        /// <summary>
        /// [-]       standard deviation in log(k_sat)
        /// </summary>
        double ksat_std_deviation;
        /// <summary>
        /// [-]       fraction of storage unavailable for transpiration
        /// </summary>
        double unavail_frac;

        //evaporation parameters

        /// <summary>
        /// [d/mm]     soil evaporation resistance at field capacity
        /// </summary>
        double evap_res_fc;
        /// <summary>
        /// [-]        exponent in relation of soil evap res to water potential \math \f$ Res = {evap_res_fc} * ({\Psi}/{\psi_{fc}})^b \f$
        /// </summary>
        double shuttleworth_b;
        /// <summary>
        /// [-]        fraction of PET used for soil evap
        /// </summary>
        double PET_correction;

        //albedo parameters

        /// <summary>
        /// [-]        saturated soil albedo
        /// </summary>
        double albedo_wet;
        /// <summary>
        /// [-]        bone dry soil albedo
        /// </summary>
        double albedo_dry;

        //special params (for specific models)

        /// <summary>
        /// [mm]      Xinanjiang parameters for VIC infiltration model \ref (Woods et al, 1992) \cite Wood1992JoGR
        /// </summary>
        double VIC_zmin;
        /// <summary>
        /// [mm]
        /// </summary>
        double VIC_zmax;
        /// <summary>
        /// [-]
        /// </summary>
        double VIC_alpha;
        /// <summary>
        /// [-]       power law exponent for VIC soil evaporation
        /// </summary>
        double VIC_evap_gamma;

        /// <summary>
        /// [-]       power law exponent for VIC_ARNO infiltration model \ref (Clark et al, 2008)
        /// </summary>
        double VIC_b_exp;

        /// <summary>
        /// [mm/d]    VIC/ARNO/GAWSER percolation rate - user defined between 0.010 - 1000.0
        /// </summary>
        double max_perc_rate;
        /// <summary>
        /// [1/d]     Linear percolation storage coefficient
        /// </summary>
        double perc_coeff;
        /// <summary>
        /// [-]       VIC/ARNO percolation exponent - user defined between 1.00 - 20.00
        /// </summary>
        double perc_n;
        /// <summary>
        /// [-]       Sacramento percolation multiplier (ZPERC in Sac-SMA lingo) - user defined between 0.00 - 80.00
        /// </summary>
        double SAC_perc_alpha;
        /// <summary>
        /// [-]       Sacramento percolation exponent (REXP in Sac-SMA lingo) - user defined between 0-3
        /// </summary>
        double SAC_perc_expon;
        /// <summary>
        /// [0..1]    Sacramento free percentage (PFREE in Sac-SMA lingo) - user defined between 0 and 1
        /// </summary>
        double SAC_perc_pfree;
        /// <summary>
        /// [mm/d]    constant max percolation rate for PERC_ASPEN model (S. Grass, 2018)
        /// </summary>
        double perc_aspen;

        /// <summary>
        /// [mm/d]    max baseflow rate (e.g., VIC_ARNO)- user defined between 0.001 - 10000.00
        /// </summary>
        double max_baseflow_rate;
        /// <summary>
        /// [-]       VIC/ARNO baseflow exponent - user defined between 1.0 - 10.0
        /// </summary>
        double baseflow_n;

        /// <summary>
        /// [1/d]     Linear Baseflow storage coefficient [Q_base=K*S]
        /// </summary>
        double baseflow_coeff;
        /// <summary>
        /// [1/d]     Linear baseflow storage coefficient [threshold]
        /// </summary>
        double baseflow_coeff2;
        /// <summary>
        /// [0..1]    threshold saturation for onset of baseflow
        /// </summary>
        double baseflow_thresh;
        /// <summary>
        /// [mm]      threshold storage for onset of baseflow
        /// </summary>
        double storage_threshold;

        /// <summary>
        /// [mm/d]    HBV max capillary rise rate
        /// </summary>
        double max_cap_rise_rate;

        /// <summary>
        /// [mm/d]    PRMS max_interflow rate
        /// </summary>
        double max_interflow_rate;
        /// <summary>
        /// [1/d]     Linear Interflow storage coefficient
        /// </summary>
        double interflow_coeff;

        /// <summary>
        /// [-]       soil infiltration param from HBV (move to Surface struct?)
        /// </summary>
        double HBV_beta;

        /// <summary>
        /// [mm]      soil deficit at which AET=0.1*PET (UBCWM P0EGEN)
        /// </summary>
        double UBC_evap_soil_def;
        /// <summary>
        /// [mm]      soil deficit at which effective impermeable fraction depletes to 0.1 (UBCWM P0AGEN)
        /// </summary>
        double UBC_infil_soil_def;

        /// <summary>
        /// [mm/d]    GR4J maximum groundwater exchange rate
        /// </summary>
        double GR4J_x2;
        /// <summary>
        /// [mm]      GR4J reference storage for baseflow/GW exchange
        /// </summary>
        double GR4J_x3;

        /// <summary>
        /// [mm/d]    exchange flow rate with mixing zone (greater than 0)
        /// </summary>
        double exchange_flow;


        public double CapRatio => _capRatio;

        public double FieldCapacity => field_capacity;

        public double WiltingPointSaturation => sat_wilt;


    }



}
