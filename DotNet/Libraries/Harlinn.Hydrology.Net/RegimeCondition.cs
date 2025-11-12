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
    /// Defines single condition under which regime applies
    /// </summary>
    public class RegimeCondition
    {
        /// <summary>
        /// one of {DATE, DOY, STAGE, FLOW, ...}
        /// </summary>
        string variable;
        /// <summary>
        /// defaults to -1 (this basin)
        /// </summary>
        long basinID;
        /// <summary>
        /// e.g., greater than, between, etc.
        /// </summary>
        Comparison compare;
        /// <summary>
        /// primary comparison value
        /// </summary>
        double compare_val1;
        /// <summary>
        /// secondary comparison value (used for between)
        /// </summary>
        double compare_val2; 
    }

}
