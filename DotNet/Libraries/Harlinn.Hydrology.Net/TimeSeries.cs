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

using System.Reflection;
using static Harlinn.Hydrology.Common;
using static Harlinn.Hydrology.Constants;
using static System.Math;
using static System.Runtime.InteropServices.JavaScript.JSType;

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

        public TimeSeries(string name, long locID, double oneValue)
            : base(TimeSeriesType.TS_REGULAR, name, locID, string.Empty)
        {
            _start_day = 0.0;
            _start_year = 0;
            _nPulses = 2;
            _interval = double.PositiveInfinity;
            _aVal = new double[_nPulses];
            _aVal[0] = oneValue;
            _aVal[1] = oneValue;
            _sub_daily = false;
            _t_corr = 0.0;
            _pulse = true;
            _aSampVal = null;
            _nSampVal = 0;
            _sampInterval = 1.0;
        }

        // Regular time series from arrays
        public TimeSeries(string name, long locID, string filename, double strt_day, int start_yr,
                          double data_interval, double[] aValues, int numPulses, bool isPulse)
            : base(TimeSeriesType.TS_REGULAR, name, locID, filename)
        {
            if(numPulses <= 0)
            {
                throw new ArgumentException("TimeSeries: Constructor: no entries in time series");
            }
            if(data_interval <= 0.0)
            {
                throw new ArgumentException("TimeSeries: Constructor: negative time interval is not allowed");
            }

            _start_day = strt_day;
            _start_year = start_yr;
            _pulse = isPulse;
            _interval = data_interval;
            _nPulses = numPulses;

            _aVal = new double[_nPulses];
            Array.Copy(aValues, _aVal, _nPulses);

            _sub_daily = (_interval < (1.0 - Constants.TIME_CORRECTION));
            _t_corr = 0.0;

            _aSampVal = null;
            _nSampVal = 0;
            _sampInterval = 1.0;
        }

        // Empty time series of given length (initialized to RAV_BLANK_DATA)
        public TimeSeries(string name, long locID, string filename, double strt_day, int start_yr,
                          double data_interval, int numPulses, bool isPulse)
            : base(TimeSeriesType.TS_REGULAR, name, locID, filename)
        {

            if (numPulses <= 0)
            {
                throw new ArgumentException("TimeSeries: Constructor: no entries in time series");
            }
            if (data_interval <= 0.0)
            {
                throw new ArgumentException("TimeSeries: Constructor: negative time interval is not allowed");
            }

            _start_day = strt_day;
            _start_year = start_yr;
            _pulse = isPulse;
            _interval = data_interval;
            _nPulses = numPulses;

            _aVal = Enumerable.Repeat(Constants.RAV_BLANK_DATA, _nPulses).ToArray();

            _sub_daily = (_interval < (1.0 - Constants.TIME_CORRECTION));
            _t_corr = 0.0;

            _aSampVal = null;
            _nSampVal = 0;
            _sampInterval = 1.0;
        }

        // Copy constructor
        public TimeSeries(string name, TimeSeries t)
            : base(name, t)
        {

            _start_day = t._start_day;
            _start_year = t._start_year;
            _pulse = t._pulse;
            _interval = t._interval;
            _nPulses = t._nPulses;
            _aVal = new double[_nPulses];
            Array.Copy(t._aVal, _aVal, _nPulses);

            _sub_daily = t._sub_daily;
            _t_corr = 0.0;

            _aSampVal = null;
            _nSampVal = 0;
            _sampInterval = 1.0;
        }

        // Dispose
        public void Dispose()
        {
            _aVal = null;
            _aSampVal = null;
            GC.SuppressFinalize(this);
        }

        // --- Accessors ---
        public bool IsDaily() => !_sub_daily;
        public override int GetNumValues() => _nPulses;
        public override double GetInterval() => _interval;
        public int GetStartYear() => _start_year;
        public double GetStartDay() => _start_day;
        public override double GetTime(int n) => _interval * n;
        public override double GetValue(int n) => _aVal[n];
        public bool IsPulseType() => _pulse;

        // Initialize (set _t_corr and resample)
        public void Initialize(double model_start_day, int model_start_year, double model_duration, double timestep, bool isObservation, Calendars calendar)
        {
            // _t_corr is number of days between model start date and gauge start date (positive if data exists before model start)
            _t_corr = -TimeDifference(model_start_day, model_start_year, _start_day, _start_year, calendar);

            if (!isObservation)
            {
                double duration = (double)(_nPulses) * _interval;
                double local_simulation_start = (_t_corr);
                double local_simulation_end = (_t_corr + model_duration);

                if (duration < local_simulation_start)
                {
                    throw new InvalidOperationException("Initialize: time series forcing data not available at beginning of model simulation");
                }
                if (duration + 0.0 * timestep + Constants.TIME_CORRECTION < local_simulation_end)
                {
                    throw new InvalidOperationException("Initialize: time series forcing data not available at end of model simulation");
                }
                if ((local_simulation_start < 0) || (_start_year > model_start_year))
                {
                    throw new InvalidOperationException("Initialize: time series forcing data not available at beginning of model simulation");
                }
            }

            // Resample time series
            if (isObservation)
            {
                // extra step for last observation of continuous hydrograph
                Resample(timestep, model_duration + timestep);
            }
            else
            {
                Resample(timestep, model_duration);
            }
        }

        // Resample
        public void Resample(double tstep, double model_duration)
        {
            int nSampVal = (int)Math.Ceiling(model_duration / tstep - Constants.TIME_CORRECTION);
            if (!_pulse)
            {
                nSampVal++;
            }

            InitializeResample(nSampVal, tstep);

            double t = 0.0;
            for (int nn = 0; nn < _nSampVal; nn++)
            {
                if (_pulse)
                {
                    _aSampVal[nn] = GetAvgValue(t, tstep);
                }
                else
                {
                    _aSampVal[nn] = GetValue(t);
                }
                t += tstep;
            }
        }

        public void InitializeResample(int nSampVal, double sampInterval)
        {
            if(nSampVal <= 0)
            {
                throw new ArgumentException("TimeSeries::InitializeResample: bad # of samples");
            }
            _nSampVal = nSampVal;
            _sampInterval = sampInterval;

            _aSampVal = new double[_nSampVal];
            for (int nn = 0; nn < _nSampVal; nn++)
            {
                _aSampVal[nn] = Constants.RAV_BLANK_DATA;
            }
        }

        public int GetTimeIndex(double t_loc)
        {
            int idx = (int)Math.Min(Math.Max(Math.Floor(t_loc / _interval), 0.0), _nPulses - 1);
            return idx;
        }

        public override int GetTimeIndexFromModelTime(double t_mod)
        {
            int idx = (int)Math.Min(Math.Max(Math.Floor((t_mod + Constants.TIME_CORRECTION) / _sampInterval), 0.0), _nSampVal - 1);
            return idx;
        }

        // Global-time GetValue
        public double GetValue(double t)
        {
            double t_loc = t + _t_corr;
            int n = GetTimeIndex(t_loc);

            if (_pulse) return _aVal[n];
            else
            {
                if (n == _nPulses - 1) return _aVal[n];
                return _aVal[n] + (t_loc - (double)(n) * _interval) / (_interval) * (_aVal[n + 1] - _aVal[n]);
            }
        }

        // Average across interval t..t+tstep
        public override double GetAvgValue(double t, double tstep)
        {
            int n1 = 0, n2 = 0;
            double sum = 0.0;
            double t_loc = t + _t_corr;
            n1 = GetTimeIndex(t_loc);
            n2 = GetTimeIndex(t_loc + tstep);

            double blank = 0.0;
            if (t_loc < -Constants.TIME_CORRECTION) return Constants.RAV_BLANK_DATA;
            if (t_loc > _nPulses * _interval) return Constants.RAV_BLANK_DATA;

            if (_pulse)
            {
                if (n1 == n2) return _aVal[n1];
                sum = 0.0;
                double inc = ((double)(n1 + 1) * _interval - t_loc);
                if (_aVal[n1] == Constants.RAV_BLANK_DATA) blank += inc;
                else sum += _aVal[n1] * inc;

                for (int n = n1 + 1; n < n2; n++)
                {
                    if (_aVal[n] == Constants.RAV_BLANK_DATA) blank += _interval;
                    else sum += _aVal[n] * _interval;
                }

                inc = ((t_loc + tstep) - (double)(n2) * _interval);
                if (_aVal[n2] == Constants.RAV_BLANK_DATA) blank += inc;
                else sum += _aVal[n2] * inc;
            }
            else
            {
                throw new NotImplementedException("GetAvgValue (non-pulse) not implemented");
            }

            if (blank / tstep > 0.001) return Constants.RAV_BLANK_DATA;
            return sum / tstep;
        }

        public override double GetMinValue(double t, double tstep)
        {
            int n1, n2;
            double vmin = double.PositiveInfinity;
            double t_loc = t + _t_corr;
            n1 = GetTimeIndex(t_loc + Constants.TIME_CORRECTION);
            n2 = GetTimeIndex(t_loc + tstep - Constants.TIME_CORRECTION);
            if(!_pulse)
            {
                throw new NotImplementedException("GetMinValue (non-pulse) not implemented");
            }

            if (n1 == n2)
            {
                return _aVal[n1];
            }
            for (int n = n1; n <= n2; n++)
            {
                vmin = Math.Min(vmin, _aVal[n]);
            }
            return vmin;
        }

        public override double GetMaxValue(double t, double tstep)
        {
            int n1, n2;
            double vmax = double.NegativeInfinity;
            double t_loc = t + _t_corr;
            n1 = GetTimeIndex(t_loc + Constants.TIME_CORRECTION);
            n2 = GetTimeIndex(t_loc + tstep - Constants.TIME_CORRECTION);

            if (!_pulse)
            {
                throw new NotImplementedException("GetMaxValue (non-pulse) not implemented");
            }

            if (n1 == n2)
            {
                return _aVal[n1];
            }
            for (int n = n1; n <= n2; n++)
            {
                vmax = Math.Max(vmax, _aVal[n]);
            }
            return vmax;
        }

        public void Multiply(double factor)
        {
            for (int n = 0; n < _nPulses; n++) _aVal[n] *= factor;
        }

        public override double GetSampledValue(int nn)
        {
            if (nn > _nSampVal - 1)
            {
                return Constants.RAV_BLANK_DATA;
            }
            return _aSampVal[nn];
        }

        public override double GetSampledTime(int nn) => _sampInterval * nn;
        public override double GetSampledInterval() => _sampInterval;
        public override int GetNumSampledValues() => _nSampVal;

        public double GetDailyAvg(int model_day) => GetAvgValue((double)model_day, 1.0);
        public double GetDailyMin(int model_day) => GetMinValue((double)model_day, 1.0);
        public double GetDailyMax(int model_day) => GetMaxValue((double)model_day, 1.0);

        public double GetModelledValue(double t, TimeSeriesType type)
        {
            int n;
            double t_loc = t + _t_corr;
            n = GetTimeIndex(t_loc);
            if (type == TimeSeriesType.TS_REGULAR)
            {
                return GetAvgValue(t, _sampInterval);
            }
            else
            {
                if (n == _nPulses - 1) return _aVal[n];
                return _aVal[n] + (t_loc - (double)(n) * _interval) / (_interval) * (_aVal[n + 1] - _aVal[n]);
            }
        }

        public void SetValue(int n, double val)
        {
            _aVal[n] = val;
        }

        public void SetSampledValue(int nn, double val)
        {
            _aSampVal[nn] = val;
        }

        // Static Sum (similar to C++ static function)
        public static TimeSeries Sum(TimeSeries ts1, TimeSeries ts2, string name)
        {
            double start_day = ts1.GetStartDay();
            int start_yr = ts1.GetStartYear();
            double interval = ts1.GetInterval();
            int nPulses = ts1.GetNumValues();
            bool is_pulse = ts1.IsPulseType();

            if(start_day != ts2.GetStartDay() || start_yr != ts2.GetStartYear())
            {
                throw new ArgumentException("Sum: time series must have same start date");
            }
            if(interval != ts2.GetInterval())
            {
                throw new ArgumentException("Sum: time series must have same interval");
            }
            if(nPulses != ts2.GetNumValues())
            {
                throw new ArgumentException("Sum: time series must have same number of data points");
            }

            double[] aVal = new double[nPulses];
            for (int n = 0; n < nPulses; n++) aVal[n] = ts1.GetValue(n) + ts2.GetValue(n);

            var outTs = new TimeSeries(name, Constants.DOESNT_EXIST, string.Empty, start_day, start_yr, interval, aVal, nPulses, is_pulse);
            return outTs;
        }

        
        public static TimeSeries Parse(object parser, bool isPulse, string name, long locID, string gaugeName, Options options, bool shiftToPerEnding)
        {
            throw new NotImplementedException();
        }

        public static TimeSeries[] ParseMultiple(object parser, out int nTS, ForcingType[] aType, bool isPulse, Options options)
        {
            throw new NotImplementedException();
        }

        public static TimeSeries[] ParseEnsimTb0(string filename, out int nTS, ForcingType[] aType, Options options)
        {
            throw new NotImplementedException();
        }

        public static TimeSeries ReadTimeSeriesFromNetCDF(Options options, string name, long locID, string gaugeName,
                                                          bool shiftToPerEnding, bool shiftFromPerEnding,
                                                          string fileNameNC, string varNameNC, string dimNamesNCStations,
                                                          string dimNamesNCTime, int stationIdx, double timeShift,
                                                          double linTransA, double linTransB)
        {
            throw new NotImplementedException();
        }
    }

}
