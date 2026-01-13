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
    struct ManagementGoal
    {
        /// <summary>
        /// goal or constraint name
        /// </summary>
        string? name;

        /// <summary>
        /// true if constraint is soft (goal rather than constraint)
        /// </summary>
        bool is_goal;
        /// <summary>
        /// priority (default==1, for goals only)
        /// </summary>
        int priority;
        /// <summary>
        /// DEFAULT penalty if under specified value (for goals only)
        /// </summary>
        double penalty_under;
        /// <summary>
        /// DEFAULT penalty if over value (for goals only)
        /// </summary>
        double penalty_over;
        /// <summary>
        /// slack index (0.._nSlackVars) of under/over slack index for goal, or DOESNT_EXIST if constraint
        /// </summary>
        int slack_ind1;
        /// <summary>
        /// slack index (0.._nSlackVars) of over slack index for target goal, or DOESNT_EXIST if constraint
        /// </summary>
        int slack_ind2;

        /// <summary>
        /// array of operating regimes, which are chosen from conditionals and determine active expression [size:nOperRegimes]
        /// </summary>
        OpRegime[]? pOperRegimes;
        /// <summary>
        /// size of operating regime array
        /// </summary>
        int nOperRegimes;

        /// <summary>
        /// currently active operating regime (or DOESNT_EXIST if none)
        /// </summary>
        int active_regime;
        /// <summary>
        /// true if any operating regime satisfied during current timestep
        /// </summary>
        bool conditions_satisfied;
        /// <summary>
        /// true if any operating regime ever satisfied during simulation (for warning at end of sim)
        /// </summary>
        bool ever_satisfied;

        /// <summary>
        /// true if goal penalty needs to be converted to units of s/m3
        /// </summary>
        bool use_stage_units;
        /// <summary>
        /// penalty correction for units different than m3/s [default: 1]
        /// </summary>
        double units_correction;
        /// <summary>
        /// p index of reservoir for stage conversion
        /// </summary>
        int reservoir_index;

        public ManagementGoal()
        { }
        
        public Expression GetCurrentExpression() 
        {
            return pOperRegimes[nOperRegimes - 1].pExpression; 
        }
        public void AddOperatingRegime(OpRegime or, bool first)
        { }

        /// <summary>
        /// adds to most recent operating regime
        /// </summary>
        /// <param name="pCondition"></param>
        public void AddOpCondition(ExpCondition condition)
        { }

        /// <summary>
        /// adds to most recent operating regime
        /// </summary>
        /// <param name="pExp"></param>
        public void AddExpression(Expression pExp)
        { }
    }
}
