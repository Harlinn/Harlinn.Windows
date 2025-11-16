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
using System.Runtime.InteropServices.JavaScript;

namespace Harlinn.Hydrology
{

    public abstract class TimeSeriesBase
    {
        /// <summary>
        /// type - regular or irregular
        /// </summary>
        TimeSeriesType _type;
        /// <summary>
        /// name of time series (used only for error messages)
        /// </summary>
        string _name;
        /// <summary>
        /// location ID (stores additional info, like HRU or SBID for observation data)
        /// </summary>
        long _loc_ID;
        /// <summary>
        /// constituent index, if a concentration/temperature observation
        /// </summary>
        int _constit_ind;
        /// <summary>
        /// original source file
        /// </summary>
        string _srcfile;
        /// <summary>
        /// integer ID tag for (e.g.,) demand ID
        /// </summary>
        long _demand_ID;


        /// <summary>
        /// type - regular or irregular
        /// </summary>
        public TimeSeriesType Type => _type;

        /// <summary>
        /// name of time series (used only for error messages)
        /// </summary>
        public string Name => _name;

        /// <summary>
        /// Retrieves the location ID (stores additional info, like HRU or SBID for observation data).
        /// </summary>
        /// <returns>
        /// The location ID.
        /// </returns>
        public long GetLocID()
        { 
            return _loc_ID; 
        }

        /// <summary>
        /// Retrieves the constituent index, if the timeseries is a concentration/temperature observation
        /// </summary>
        /// <returns>
        /// The constituent index.
        /// </returns>
        public int GetConstitInd()
        {
            return _constit_ind;
        }

        /// <summary>
        /// Retrieves the original source file of the timeseries.
        /// </summary>
        /// <returns>
        /// The original source file of the timeseries.
        /// </returns>
        public string GetSourceFile()
        { 
            return _srcfile; 
        }

        /// <summary>
        /// Retrieves the integer ID tag for (e.g.,) demand ID
        /// </summary>
        /// <returns>
        /// The integer ID tag.
        /// </returns>
        public long GetDemandID()
        { 
            return _demand_ID; 
        }

        public abstract double GetInterval();
        public abstract double GetTime(int n);
        public abstract double GetValue(int n);
        public abstract int GetNumValues();
        public abstract double GetAvgValue(double t, double tstep);
        public abstract double GetMinValue(double t, double tstep);
        public abstract double GetMaxValue(double t, double tstep);

        public abstract double GetSampledValue(int nn);
        public abstract double GetSampledTime(int nn);
        public abstract double GetSampledInterval();
        public abstract int GetNumSampledValues();

        public abstract int GetTimeIndexFromModelTime(double t_mod);



    }
}
