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
    public class ExpressionTerm
    {
        /// <summary>
        /// type of expression
        /// </summary>
        TermType type;
        /// <summary>
        /// multiplier of expression (+/- 1, depending upon operator and location in exp)
        /// </summary>
        double mult;
        /// <summary>
        /// true if term is in denominator
        /// </summary>
        bool reciprocal;

        /// <summary>
        /// constant value or conversion multiplier
        /// </summary>
        double value;
        /// <summary>
        /// pointer to time series, if this is a named time series
        /// </summary>
        TimeSeries pTS;
        /// <summary>
        /// pointer to lookup table, if this is a named time series
        /// </summary>
        LookupTable pLT;
        /// <summary>
        /// true if nested within (i.e., an argument to) another term
        /// </summary>
        bool is_nested;
        /// <summary>
        /// for time series (+ or -) or lookback value (+)
        /// </summary>
        int timeshift;
        /// <summary>
        /// index of decision variable
        /// </summary>
        int DV_ind;
        /// <summary>
        /// index k of first argument (e.g., for lookup table with term entry)
        /// </summary>
        int nested_ind1;
        /// <summary>
        /// index k of second argument (e.g., for min/max functions)
        /// </summary>
        int nested_ind2;
        /// <summary>
        /// contents of first argument to function - can be expression
        /// </summary>
        string nested_exp1;
        /// <summary>
        /// contents of second argument to function
        /// </summary>
        string nested_exp2;

        /// <summary>
        /// original string expression
        /// </summary>
        string origexp;
        /// <summary>
        /// subbasin index p (for history variables, e.g, !Q324[-2] or @SB_var() command )
        /// </summary>
        int p_index;
        /// <summary>
        /// HRU index k (for @HRU_var command)
        /// </summary>
        int HRU_index;
        /// <summary>
        /// state variable index i (for @SB_var or @HRU_var command)
        /// </summary>
        int SV_index;
    }

}
