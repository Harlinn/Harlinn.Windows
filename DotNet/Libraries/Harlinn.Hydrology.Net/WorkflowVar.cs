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
    /// <summary>
    /// workflow variable definition
    /// </summary>
    public class WorkflowVar
    {
        /// <summary>
        /// workflow variable name
        /// </summary>
        string? name;

        /// <summary>
        /// current value of workflow variable (evaluated at start of time step)
        /// </summary>
        double current_val;

        /// <summary>
        /// array of operating regimes, which are chosen from conditionals and determine active expression [size:nOperRegimes]
        /// </summary>
        OpRegime[]? pOperRegimes;
        int nOperRegimes;  //< size of operating regime array

        public WorkflowVar()
        { }
        
        Expression GetCurrentExpression() 
        {
            return pOperRegimes[nOperRegimes - 1].pExpression; 
        }
        
        void AddOperatingRegime(OpRegime pOR, bool first)
        { }
        
        void AddOpCondition(ExpCondition pCondition)
        { }
        /// <summary>
        /// adds to most recent operating regime
        /// </summary>
        /// <param name="pExp"></param>
        void AddExpression(Expression pExp)
        {
        }
    }




}
