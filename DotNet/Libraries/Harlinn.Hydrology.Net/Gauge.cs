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
    /// atmospheric measurement locations
    /// </summary>
    public class Gauge
    {
        /// <summary>
        /// Gauge name
        /// </summary>
        string _name;
        /// <summary>
        /// Gauge Location
        /// </summary>
        Location _Loc;
        /// <summary>
        /// Gauge Elevation [masl]
        /// </summary>
        double _elevation;
        /// <summary>
        /// Gauge Measurement height above land surface [m]
        /// </summary>
        double _meas_ht;

        /// <summary>
        /// Array of time series
        /// </summary>
        TimeSeries[] _pTimeSeries;
        /// <summary>
        /// number of time series linked to gauge
        /// </summary>
        int _nTimeSeries;
        /// <summary>
        /// lookup array for time series by forcing type
        /// </summary>
        int[] _aTSindex = new int[MAX_FORCING_TYPES];

        /// <summary>
        /// representative average monthly temperatures [C]
        /// </summary>
        double[] _aAveTemp = new double[12];
        /// <summary>
        /// representative minimum monthly temperatures [C]
        /// </summary>
        double[] _aMinTemp = new double[12];
        /// <summary>
        /// representative maximum monthly temperatures [C]
        /// </summary>
        double[] _aMaxTemp = new double[12];
        /// <summary>
        /// representative average monthly PET [mm/d] (or monthly PET factor [mm/d/K], if MONTHLY_FACTOR is used)
        /// </summary>
        double[] _aAvePET = new double[12];

        /// <summary>
        /// correction factor for rainfall (stored with gauge, used elsewhere)
        /// </summary>
        double _rainfall_corr;
        /// <summary>
        /// correction factor for snowfall (stored with gauge, used elsewhere)
        /// </summary>
        double _snowfall_corr;
        /// <summary>
        /// correction factor for temperature (stored with gauge, used elsewhere)
        /// </summary>
        double _temperature_corr;
        /// <summary>
        /// minimum temperature threshold used to determine cloud_cover factor
        /// </summary>
        double _cloud_min_temp;
        /// <summary>
        /// maximum temparature threshold used to determine cloud_cover factor
        /// </summary>
        double _cloud_max_temp;
    }
}
