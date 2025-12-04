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
using System.Diagnostics.Metrics;
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
        TimeSeries[]? _pTimeSeries;
        /// <summary>
        /// number of time series linked to gauge
        /// </summary>
        int _nTimeSeries;
        /// <summary>
        /// lookup array for time series by forcing type
        /// </summary>
        readonly int[] _aTSindex = new int[MAX_FORCING_TYPES];

        /// <summary>
        /// representative average monthly temperatures [C]
        /// </summary>
        readonly double[] _aAveTemp = new double[12];
        /// <summary>
        /// representative minimum monthly temperatures [C]
        /// </summary>
        readonly double[] _aMinTemp = new double[12];
        /// <summary>
        /// representative maximum monthly temperatures [C]
        /// </summary>
        readonly double[] _aMaxTemp = new double[12];
        /// <summary>
        /// representative average monthly PET [mm/d] (or monthly PET factor [mm/d/K], if MONTHLY_FACTOR is used)
        /// </summary>
        readonly double[] _aAvePET = new double[12];

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


        public Gauge(string gauge_name, double latit, double longit, double elev)
        {
            _Loc.latitude = latit;
            _Loc.longitude = longit;

            _elevation = elev;

            // [m], default
            _meas_ht = 2.0; 
            _rainfall_corr = 1.0;
            _snowfall_corr = 1.0;
            _temperature_corr = 0.0;

            //ensures cloud-free status always unless overriden
            _cloud_min_temp = -20.0;
            _cloud_max_temp = 40.0;

            _name = gauge_name;

            _nTimeSeries = 0;
            _pTimeSeries = null;

            for (int i = 0; i < MAX_FORCING_TYPES; i++)
            {
                _aTSindex[i] = DOESNT_EXIST;
            }

            for (int i = 0; i < 12; i++)
            {
                _aAveTemp[i] = NOT_SPECIFIED;
                _aMinTemp[i] = NOT_SPECIFIED;
                _aMaxTemp[i] = NOT_SPECIFIED;
                _aAvePET[i] = NOT_SPECIFIED;
            }
        }

        public void Initialize(Options options, int utmZone)
        {
            _Loc.InitializeUTM(utmZone);

        }

        /// <summary>
        /// Gets time series representing forcing data type ftype
        /// </summary>
        /// <param name="ftype">
        /// forcing data type
        /// </param>
        /// <returns>
        /// The time series representing the forcing data type ftype, if time series exists, otherwise null.
        /// </returns>
        public TimeSeries? GetTimeSeries(ForcingType ftype)
        {
            int index = _aTSindex[(int)(ftype)];
            if (index != DOESNT_EXIST && _pTimeSeries != null)
            {
                return _pTimeSeries[index];
            }
            return null;
        }

        /// <summary>
        /// returns true if forcing exists at gauge
        /// </summary>
        /// <param name="ftype">
        /// forcing data type
        /// </param>
        /// <returns>
        /// true if forcing exists at gauge.
        /// </returns>
        public bool TimeSeriesExists(ForcingType ftype)
        {
            return (_aTSindex[(int)(ftype)] != DOESNT_EXIST);
        }

        internal Location GetLocation()
        {
            throw new NotImplementedException();
        }

        internal double GetElevation()
        {
            throw new NotImplementedException();
        }

        internal string GetName()
        {
            throw new NotImplementedException();
        }
    }
}
