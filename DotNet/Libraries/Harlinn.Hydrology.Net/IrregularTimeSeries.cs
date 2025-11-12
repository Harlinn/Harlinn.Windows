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
    /// Discontinuous irregularly spaced time series
    /// </summary>

    public class IrregularTimeSeries : TimeSeriesBase
    {
        /// <summary>
        /// Array of years
        /// </summary>
        int[] _aYears;
        /// <summary>
        /// Array of julian days
        /// </summary>
        double[] _aDays;
        /// <summary>
        /// Array of model times
        /// </summary>
        double[] _aTimes;
        /// <summary>
        /// Array of values
        /// </summary>
        double[] _aVal;
        /// <summary>
        /// number of values
        /// </summary>
        int _nVals;
        /// <summary>
        /// index of first value within model time
        /// </summary>
        int _indexCorr;
        /// <summary>
        /// number of values within model time
        /// </summary>
        int _nSampVal;
    }

}
