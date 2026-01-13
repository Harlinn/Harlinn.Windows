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
    /// Custom model output generator
    /// </summary>
    public class CustomOutput
    {
        /// <summary>
        /// output file stream
        /// </summary>
        TextWriter _CUSTOM;

        /// <summary>
        /// netCDF file identifier
        /// </summary>
        int _netcdf_ID;

        /// <summary>
        /// output variable identifier
        /// </summary>
        DiagnosticType _var;
        /// <summary>
        /// state variable output type (if output var is a SV)
        /// </summary>
        SVType _svtype;
        /// <summary>
        /// state variable index (if output var is a SV or flux)
        /// </summary>
        int _svind;
        /// <summary>
        /// target state variable index (if output var is a flux between two compartments)
        /// </summary>
        int _svind2;
        /// <summary>
        /// forcing function name (if output var is a forcing function)
        /// </summary>
        string _force_str;
        /// <summary>
        /// forcing function type (if output var is a forcing function)
        /// </summary>
        ForcingType _ftype;
        /// <summary>
        /// time aggregation statistic(average, max, min, etc.) (spatial average is always used)
        /// </summary>
        AggStat _aggstat;
        /// <summary>
        /// how aggregated (monthly, daily, hourly, etc.)
        /// </summary>
        TimeAgg _timeAgg;
        /// <summary>
        /// how aggregated (by HRU, by Basin, etc.)
        /// </summary>
        SpatialAgg _spaceAgg;

        /// <summary>
        /// histogram min
        /// </summary>
        double _hist_min;
        /// <summary>
        /// Histogram max
        /// </summary>
        double _hist_max;
        /// <summary>
        /// Histogram # of bins
        /// </summary>
        int _nBins;

        /// <summary>
        /// custom output filename (relative path, with extension)
        /// </summary>
        string _filename;
        /// <summary>
        /// custom output filename provided by user
        /// </summary>
        string _filename_user;

        /// <summary>
        /// forcing variable or state variable name
        /// </summary>
        string _varName;
        /// <summary>
        /// forcing variable or state variable units
        /// </summary>
        string _varUnits;
        /// <summary>
        /// temporal aggregation type string
        /// </summary>
        string _timeAggStr;
        /// <summary>
        /// statistic type string
        /// </summary>
        string _statStr;
        /// <summary>
        /// spatial aggregation type string
        /// </summary>
        string _spaceAggStr;

        /// <summary>
        /// stores accumulated data for each HRU,Basin, or WShed (size:[num_store][num_data])
        /// </summary>
        double[,] data;
        /// <summary>
        /// number of data points
        /// </summary>
        int num_data;
        /// <summary>
        /// number of data items needed for each HRU, Basin or WShed
        /// (e.g., =2 if max and min are both tracked)
        /// </summary>
        int num_store;

        /// <summary>
        /// index tracking current output line (e.g., 3=3 years/months/days passed, dependent upon _timeAgg
        /// </summary>
        int _time_index;

        /// <summary>
        /// counts accumulated data (# of timesteps since last output dump)
        /// </summary>
        int count;

        /// <summary>
        /// index of HRUGroup for which output is generated when spaceAgg==BY_SELECT_HRUS
        /// </summary>
        int kk_only;
        /// <summary>
        /// Reference to model
        /// </summary>
        Model pModel;
    }
}
