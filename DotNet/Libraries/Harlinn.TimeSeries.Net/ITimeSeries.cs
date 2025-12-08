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

namespace Harlinn.TimeSeries.Net
{
    public enum TimeSeriesType
    {
        Regular,
        Irregular,
        Constant
    }

    public interface ITimeSeries : IReadOnlyList<Value>
    {
        TimeSeriesType Type { get; }

        bool Pulse { get; }

        Value First { get; }
        Value Last { get; }

        Value this[DateTime time] { get; }

        public int Capacity { get; }

        Value[] GetValues(Interval interval);

        /*
        double GetAvgValue(Interval duration, TimeSpan interval);
        double GetMinValue(Interval duration, TimeSpan interval);
        double GetMaxValue(Interval duration, TimeSpan interval);
        */
    }


}
