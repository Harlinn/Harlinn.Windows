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
using static Harlinn.Hydrology.Constants;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// goal/constraint condition
    /// </summary>
    public class ExpCondition
    {
        /// <summary>
        /// decision variable name (e.g., Q1023) or "MONTH" or "DATE" or "DAY_OF_YEAR" or "YEAR"
        /// </summary>
        string dv_name;
        /// <summary>
        /// conditional value
        /// </summary>
        double value;
        /// <summary>
        /// second conditional (if COMPARE_BETWEEN)
        /// </summary>
        double value2;
        /// <summary>
        /// conditional value (if date)
        /// </summary>
        string date_string;
        /// <summary>
        /// second conditional (if DATE COMPARE_BETWEEN)
        /// </summary>
        string date_string2;
        /// <summary>
        /// comparison operator, e.g., COMPARE_IS_EQUAL
        /// </summary>
        Comparison compare;
        /// <summary>
        /// subbasin or demand index of LHS of condition expression (or DOESNT_EXIST)
        /// </summary>
        int p_index;

        /// <summary>
        /// condition expression (or null if not used)
        /// </summary>
        Expression? pExp;

        public ExpCondition()
        {
            dv_name = "";
            value = value2 = 0.0;
            date_string = date_string2 = "";
            compare = Comparison.COMPARE_IS_EQUAL;
            p_index = DOESNT_EXIST;
        }
    }

}
