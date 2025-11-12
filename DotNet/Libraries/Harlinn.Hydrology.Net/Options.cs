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
    public class Options
    {
        /// <summary>
        /// version - written to output file headers
        /// </summary>
        public string version;

        /// <summary>
        /// corresponding to t=0, simulation time
        /// </summary>
        public DateTime start_day;
        /// <summary>
        /// simulation duration
        /// </summary>
        public TimeSpan duration;
        /// <summary>
        /// int that specifies calendar of all dates used,
        /// e.g., 2 = "CALENDAR_PROLEPTIC_GREGORIAN"
        /// </summary>
        public int calendar;

        /// <summary>
        /// int that specifies time zone relative to GMT for writing to NetCDF output
        /// </summary>
        public int time_zone;

        /// <summary>
        /// amount for start date/assimilation date/end date to be adjusted by from command line
        /// </summary>
        public double forecast_shift;

        /// <summary>
        /// numerical solution method
        /// </summary>
        public NumericalMethod sol_method;
        /// <summary>
        /// convergence criteria
        /// </summary>
        public double convergence_crit;
        /// <summary>
        /// maximum number of iterations for iterative solver method
        /// </summary>
        public double max_iterations;
        /// <summary>
        /// numerical method timestep (in days)
        /// </summary>
        public double timestep;
        /// <summary>
        /// write to output file every x number of timesteps
        /// </summary>
        public double output_interval;
        /// <summary>
        /// ensemble type (or ENSEMBLE_NONE if single model)
        /// </summary>
        public EnsembleType ensemble;
        /// <summary>
        /// call to external script/.exe once per timestep (or "" if none)
        /// </summary>
        public string external_script;
        /// <summary>
        /// frequency to read rvl file (in d, or 0.0 if not to be read)
        /// </summary>
        public double rvl_read_frequency;
        /// <summary>
        /// true if we should look for stopfile
        /// </summary>
        public bool use_stopfile;

        /// <summary>
        /// type of model being simulated
        /// </summary>
        public ModelType modeltype;
        /// <summary>
        /// frequency of exchange fluxes
        /// </summary>
        public FluxFrequency exchange_freq;
        /// <summary>
        /// method of calculating exchange fluxes
        /// </summary>
        public FluxMethod flux_exchange;

        /// <summary>
        /// Method for interpolating Met Station/Gauge data to HRUs
        /// </summary>
        public InterpMethod interpolation;
        /// <summary>
        /// name of file (in working directory) which stores interpolation weights
        /// </summary>
        public string interp_file;

        /// <summary>
        /// prefix to be used for all output files
        /// </summary>
        public string run_name;
        /// <summary>
        /// run mode - single character used to enable multiple model configs with if statements (default==' ')
        /// </summary>
        public char run_mode;
        /// <summary>
        /// fully qualified filename of rvi (main input) file
        /// </summary>
        public string rvi_filename;
        /// <summary>
        /// fully qualified filename of rvh (HRU-basin) file
        /// </summary>
        public string rvh_filename;
        /// <summary>
        /// fully qualified filename of rvp (parameters) file
        /// </summary>
        public string rvp_filename;
        /// <summary>
        /// fully qualified filename of rvt (time series) file
        /// </summary>
        public string rvt_filename;
        /// <summary>
        /// fully qualified filename of rvc (initial conditions) file
        /// </summary>
        public string rvc_filename;
        /// <summary>
        /// fully qualified filename of rve (ensemble) file
        /// </summary>
        public string rve_filename;
        /// <summary>
        /// fully qualified filename of rvl (live communications) file
        /// </summary>
        public string rvl_filename;
        /// <summary>
        /// fully qualified filename of rvg (groundwater properties) file
        /// </summary>
        public string rvg_filename;
        /// <summary>
        /// fully qualified filename of rvm (management) file
        /// </summary>
        public string rvm_filename;
        /// <summary>
        /// fully qualified filename of runinfo.nc file from FEWS
        /// </summary>
        public string runinfo_filename;
        /// <summary>
        /// fully qualified filename of state_mods.nc file from FEWS
        /// </summary>
        public string stateinfo_filename;
        /// <summary>
        /// fully qualified filename of flowstate_mods.nc file from FEWS
        /// </summary>
        public string flowinfo_filename;
        /// <summary>
        /// fully qualified filename of param_mods.nc file from FEWS
        /// </summary>
        public string paraminfo_filename;
        /// <summary>
        /// run name prefix in warm ensemble solution files
        /// </summary>
        public string warm_ensemble_run;

        /// <summary>
        /// primary output directory (RavenErrors.txt, =output_dir for non-ensemble)
        /// </summary>
        public string main_output_dir;
        /// <summary>
        /// output directory (can change during ensemble run)
        /// </summary>
        public string output_dir;

        /// <summary>
        /// method for correcting interpolated temperatures for elevation
        /// </summary>
        OrographicCorr orocorr_temp;
        /// <summary>
        /// method for correcting interpolated precipitation for elevation
        /// </summary>
        OrographicCorr orocorr_precip;
        /// <summary>
        /// method for correcting interpolated PET for elevation
        /// </summary>
        OrographicCorr orocorr_PET;

        // Algorithm Choices

        /// <summary>
        /// method for converting total precip to rain/snow
        /// </summary>
        RainsnowMethod rainsnow;

        /// <summary>
        /// cloud cover estimation method
        /// </summary>
        CloudcovMethod cloud_cover;
        /// <summary>
        /// method for estimating snow albedo
        /// </summary>
        SnowAlbedoMethod snow_albedo;
        /// <summary>
        /// net longwave radiation estimation method
        /// </summary>
        LWMethod LW_radiation;
        /// <summary>
        /// incoming longwave radiation estimation method
        /// </summary>
        LWincMethod LW_incoming;
        /// <summary>
        /// shortwave radiation estimation method
        /// </summary>
        SWMethod SW_radiation;
        /// <summary>
        /// method for cloudcover correction of shortwave radiation
        /// </summary>
        SWCloudcoverCorr SW_cloudcovercorr;
        /// <summary>
        /// method for estimating canopy transmittance of shortwave radiation
        /// </summary>
        SWCanopyCorr SW_canopycorr;
        /// <summary>
        /// method for calculating net shortwave radiation (calculated or data)
        /// </summary>
        NetSWRadMethod SW_radia_net;
        /// <summary>
        /// PET estimation method
        /// </summary>
        EvapMethod evaporation;
        /// <summary>
        /// Open Water PET estimation method
        /// </summary>
        EvapMethod ow_evaporation;
        /// <summary>
        /// PET estimation method when infilling blank PET_DATA
        /// </summary>
        EvapMethod evap_infill;
        /// <summary>
        /// Open Water PET estimation method when infilling blank PET_DATA
        /// </summary>
        EvapMethod ow_evap_infill;
        /// <summary>
        /// Relative humidity estimation method
        /// </summary>
        RelhumMethod rel_humidity;
        /// <summary>
        /// Air pressure estimation method
        /// </summary>
        AirpressMethod air_pressure;
        /// <summary>
        /// Wind velocity estimation mehtod
        /// </summary>
        WindvelMethod wind_velocity;
        /// <summary>
        /// Wind vertical profile approximation method
        /// </summary>
        WindProfMeth wind_profile;
        /// <summary>
        /// Potential melt estimation method
        /// </summary>
        PotmeltMethod pot_melt;
        /// <summary>
        /// Subdaily PET/Snowmelt temporal downscaling correction
        /// </summary>
        SubdailyMethod subdaily;
        /// <summary>
        /// aquifer/soil recharge method
        /// </summary>
        RechargeMethod recharge;
        /// <summary>
        /// true if PET is used to directly reduce precipitation
        /// </summary>
        bool direct_evap;
        /// <summary>
        /// method for handling snowcover depletion curve
        /// </summary>
        SnowcovMethod snow_depletion;

        /// <summary>
        /// method for calculating canopy interception factor
        /// </summary>
        PrecipIceptMethod interception_factor;

        /// <summary>
        /// channel routing method
        /// </summary>
        RoutingMethod routing;
        /// <summary>
        /// catchment routing method
        /// </summary>
        CatchmentRoute catchment_routing;
        /// <summary>
        /// method used for allocating upstream reservoir support to meet downstream irrigation demand
        /// </summary>
        DemandAlloc res_demand_alloc;
        /// <summary>
        /// method used for handling outflow estimates when max stage exceeded in reservoir
        /// </summary>
        Overflowmode res_overflowmode;
        /// <summary>
        /// means of interpolating monthly data
        /// </summary>
        MonthlyInterp month_interp;

        /// <summary>
        /// true if peculiar UBCWM bugs are retained (only really for BC Hydro use)
        /// </summary>
        bool keepUBCWMbugs;
        /// <summary>
        /// true if competitive ET should be suppressed (for backward compatibility)
        /// </summary>
        bool suppressCompetitiveET;
        /// <summary>
        /// true if presence of snow should set PET to zero
        /// </summary>
        bool snow_suppressPET;
        /// <summary>
        /// true if soil can be filled above capacity (to be handled using overflow routine)
        /// </summary>
        bool allow_soil_overfill;

        // Soil model information
        /// <summary>
        /// number of soil layers
        /// </summary>
        int num_soillayers;

        /// <summary>
        /// characteristic curves for unsaturated flow
        /// </summary>
        SoilCharact soil_representation;

        // Output Options
        /// <summary>
        /// true if debugging mode is on
        /// </summary>
        bool debug_mode;
        /// <summary>
        /// true if parsing information written to screen
        /// </summary>
        bool noisy;
        /// <summary>
        /// true if nothing should be written to screen (overrides noisy)
        /// </summary>
        bool silent;
        /// <summary>
        /// true if specific setings for PAVICS system are applied (such as simulation status JSON file) (default: FALSE)
        /// </summary>
        bool pavics;
        /// <summary>
        /// true if input is generated by Deltares FEWS
        /// </summary>
        bool deltaresFEWS;
        /// <summary>
        /// output format (default: OUTPUT_STANDARD)
        /// </summary>
        OutFormat output_format;
        /// <summary>
        /// custom output interval (i.e., for generating 10-day interval outputs)
        /// </summary>
        double custom_interval;
        /// <summary>
        /// true if ForcingFunctions.csv is written
        /// </summary>
        bool write_forcings;
        /// <summary>
        /// true if WatershedMassEnergyBalance.csv is written
        /// </summary>
        bool write_mass_bal;
        /// <summary>
        /// true if GWHead.csv is written
        /// </summary>
        bool write_gwhead;
        /// <summary>
        /// true if GWFlow.csv is written
        /// </summary>
        bool write_gwflow;
        /// <summary>
        /// true if ReservoirStages.csv is written
        /// </summary>
        bool write_reservoir;
        /// <summary>
        /// true if ReservoirMassBalance.csv is written
        /// </summary>
        bool write_reservoirMB;
        /// <summary>
        /// true if WaterLevels.csv is written
        /// </summary>
        bool write_waterlevels;
        /// <summary>
        /// true if average flows over timestep are reported in hydrograph output
        /// </summary>
        bool ave_hydrograph;
        /// <summary>
        /// true if exhaustive mass balance diagnostics are written
        /// </summary>
        bool write_exhaustiveMB;
        /// <summary>
        /// index (kk) of HRU Group for MB writing, DOESNT_EXIST if not to be written
        /// </summary>
        int write_group_mb;
        /// <summary>
        /// true if writing channel rating curve information
        /// </summary>
        bool write_channels;
        /// <summary>
        /// true if WatershedStorage.csv/tb0/nc is written (default: true)
        /// </summary>
        bool write_watershed_storage;
        /// <summary>
        /// true if constituent mass [mg/m2] is written instead of concentration [mg/L] in output files
        /// </summary>
        bool write_constitmass;
        /// <summary>
        /// true if subbasins params are written to SubbasinParams.csv
        /// </summary>
        bool write_basinfile;
        /// <summary>
        /// true if interpolation weights are written to InterpolationWeights.csv
        /// </summary>
        bool write_interp_wts;
        /// <summary>
        /// true if demands.csv file is to be written
        /// </summary>
        bool write_demandfile;
        /// <summary>
        /// true if simple_out.csv file is to be written (for scripting)
        /// </summary>
        bool write_simpleout;
        /// <summary>
        /// true if MassLoadings.csv file is to be written
        /// </summary>
        bool write_massloading;
        /// <summary>
        /// true if local flows are written to Hydrographs file (csv or nc)
        /// </summary>
        bool write_localflow;
        /// <summary>
        /// true if reservoir net inflows are written to Hydrographs file (csv or nc)
        /// </summary>
        bool write_netresinflow;
        /// <summary>
        /// true if benchmarking output - removes version/timestamps in output
        /// </summary>
        bool benchmarking;
        /// <summary>
        /// true if initial conditions are suppressed when writing output time series
        /// </summary>
        bool suppressICs;
        /// <summary>
        /// true if period ending convention should be used for reading/writing Ensim files
        /// </summary>
        bool period_ending;
        /// <summary>
        /// true if all timestep-averaged output is reported using starttime of timestep
        /// </summary>
        bool period_starting;
        /// <summary>
        /// determines whether the simulation pauses at the end of the model run
        /// </summary>
        bool pause;
        /// <summary>
        /// working directory
        /// </summary>
        public string working_dir;
        /// <summary>
        /// starting month of water year (typically 10=October)
        /// </summary>
        public int wateryr_mo;
        /// <summary>
        /// create an rvp template file after reading the .rvi
        /// </summary>
        public bool create_rvp_template;

        // Diagnostic options

        /// <summary>
        /// Model time to start diagnostics
        /// </summary>
        public double diag_start_time;

        /// <summary>
        /// Model time to end diagnostics
        /// </summary>
        public double diag_end_time;

        // Other

        /// <summary>
        /// turn on streamflow assimilation
        /// </summary>
        public bool assimilate_flow;
        /// <summary>
        /// turn on lake stage assimilation
        /// </summary>
        public bool assimilate_stage;
        /// <summary>
        /// assimilation start time (in model time [d])
        /// </summary>
        public double assimilation_start;
        /// <summary>
        /// apply water management optimization (default: false)
        /// </summary>
        public bool management_optimization;
        /// <summary>
        /// array of NetCDF attrributes {attribute/value pair}
        /// </summary>
        public NetCDFAtt[] aNetCDFattribs;
        /// <summary>
        /// [MB] size of memory chunk for each forcing grid
        /// </summary>
        public int NetCDF_chunk_mem;
        /// <summary>
        /// true if in BMI mode (no rvt files, no end time)
        /// </summary>
        public bool in_bmi_mode;


    }

}
