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
    /// operating regime
    /// </summary>
    public class OpRegime
    {
        /// <summary>
        /// regime name
        /// </summary>
        public string reg_name;

        /// <summary>
        /// goal expression
        /// </summary>
        public Expression? pExpression;

        /// <summary>
        /// number of conditional statments
        /// </summary>
        public int nConditions;
        /// <summary>
        /// array of pointers to conditional statements
        /// </summary>
        public ExpCondition[]? pConditions;

        /// <summary>
        /// penalty associated with not satisfying goal (or RAV_BLANK_DATA, if default is to be used)
        /// </summary>
        public double penalty_under;
        /// <summary>
        /// penalty associated with not satisfying goal (or RAV_BLANK_DATA, if default is to be used)
        /// </summary>
        public double penalty_over;

        public OpRegime(string name)
        {
            reg_name = name;
            penalty_under = RAV_BLANK_DATA;
            penalty_over = RAV_BLANK_DATA;
        }
    }

}
