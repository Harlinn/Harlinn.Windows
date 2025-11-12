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
    /// Statistics of an aggregation
    /// </summary>
    public enum AggStat
    {
        /// <summary>
        /// Average of data set
        /// </summary>
        AGG_AVERAGE,
        /// <summary>
        /// Maximum of data set
        /// </summary>
        AGG_MAXIMUM,
        /// <summary>
        /// Minimum of data set
        /// </summary>
        AGG_MINIMUM,
        /// <summary>
        /// Median of data set
        /// </summary>
        AGG_MEDIAN,
        /// <summary>
        /// Cumulative sum of data set (of rates)
        /// </summary>
        AGG_CUMULSUM,
        /// <summary>
        /// Range of data set
        /// </summary>
        AGG_RANGE,
        /// <summary>
        /// 5% and 95% quantiles of data set
        /// </summary>
        AGG_95CI,
        /// <summary>
        /// Quartiles of data set
        /// </summary>
        AGG_QUARTILES,
        /// <summary>
        /// Full histogram of data set
        /// </summary>
        AGG_HISTOGRAM
    }






}
