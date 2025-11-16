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
    public class TimeSeries : TimeSeriesBase
    {
        /// <summary>
        /// Day corresponding to local TS time 0.0 (beginning of time series)
        /// </summary>
        double _start_day;
        /// <summary>
        /// Year corresponding to local TS time 0.0 (beginning of time series)
        /// </summary>
        int _start_year;

        /// <summary>
        /// uniform interval between data points (in days)
        /// </summary>
        double _interval;
        /// <summary>
        /// Array of magnitude of pulse (variable units)
        /// </summary>
        double[] _aVal;
        /// <summary>
        /// number of pulses (total duration=(nPulses-1)*_interval)
        /// </summary>
        int _nPulses;

        /// <summary>
        /// Array of resampled time series values every timestep for model duration
        /// </summary>
        double[] _aSampVal;
        /// <summary>
        /// size of aSampVal (~model_duration/timestep)
        /// </summary>
        int _nSampVal;
        /// <summary>
        /// timestep of resampled timeseries
        /// </summary>
        double _sampInterval;

        /// <summary>
        /// true if smallest time interval is sub-daily
        /// </summary>
        bool _sub_daily;

        /// <summary>
        /// number of days between model start date and gauge start date (positive if data exists before model start date)
        /// correction from model time (t) to time series/local time
        /// </summary>
        double _t_corr;

        /// <summary>
        /// flag determining whether this is a pulse-based or piecewise-linear time series
        /// </summary>
        /// <remarks>
        /// forcing functions are all pulse-based
        /// </remarks>
        bool _pulse;

        public override double GetAvgValue(double t, double tstep)
        {
            throw new NotImplementedException();
        }

        public override double GetInterval()
        {
            throw new NotImplementedException();
        }

        public override double GetMaxValue(double t, double tstep)
        {
            throw new NotImplementedException();
        }

        public override double GetMinValue(double t, double tstep)
        {
            throw new NotImplementedException();
        }

        public override int GetNumSampledValues()
        {
            throw new NotImplementedException();
        }

        public override int GetNumValues()
        {
            throw new NotImplementedException();
        }

        public override double GetSampledInterval()
        {
            throw new NotImplementedException();
        }

        public override double GetSampledTime(int nn)
        {
            throw new NotImplementedException();
        }

        public override double GetSampledValue(int nn)
        {
            throw new NotImplementedException();
        }

        public override double GetTime(int n)
        {
            throw new NotImplementedException();
        }

        public override int GetTimeIndexFromModelTime(double t_mod)
        {
            throw new NotImplementedException();
        }

        public override double GetValue(int n)
        {
            throw new NotImplementedException();
        }
    }

}
