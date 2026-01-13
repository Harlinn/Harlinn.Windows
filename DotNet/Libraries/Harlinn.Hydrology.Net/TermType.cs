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
    public enum TermType
    {
        /// <summary>
        /// decision variable !Q123 or named
        /// </summary>
        TERM_DV,
        /// <summary>
        /// time series @ts(name,n)
        /// </summary>
        TERM_TS,
        /// <summary>
        /// lookup table @lookup(x)
        /// </summary>
        TERM_LT,
        /// <summary>
        /// state variable @HRU_var(SNOW,2345)
        /// </summary>
        TERM_HRU,
        /// <summary>
        /// state variable @SB_var(SNOW,234)
        /// </summary>
        TERM_SB,
        /// <summary>
        /// constant
        /// </summary>
        TERM_CONST,
        /// <summary>
        /// workflow variable (constant updated each time step)
        /// </summary>
        TERM_WORKFLOW,
        /// <summary>
        /// bracketed - !Q123[-2]
        /// </summary>
        TERM_HISTORY,
        /// <summary>
        /// @max(x,y)
        /// </summary>
        TERM_MAX,
        /// <summary>
        /// @min(x,y)
        /// </summary>
        TERM_MIN,
        /// <summary>
        /// @convert(x,units)
        /// </summary>
        TERM_CONVERT,
        /// <summary>
        /// @cumul(ts_name,duration) //MAY WANT @cumul(ts_name,duration,n) to handle time shift, e.g., 3 days to 10 days ago?
        /// </summary>
        TERM_CUMUL_TS,
        /// <summary>
        /// cumulative delivery !C123
        /// </summary>
        TERM_CUMUL,
        /// <summary>
        /// unknown
        /// </summary>
        TERM_UNKNOWN
    }

}
