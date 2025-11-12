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
    /// The numerical methods with which a solution to differential equations can be found
    /// </summary>
    public enum NumericalMethod
    {
        /// <summary>
        /// Euler's method
        /// </summary>
        EULER,
        /// <summary>
        /// Conventional WB model method - processes in series
        /// </summary>
        ORDERED_SERIES,
        /// <summary>
        /// 2nd Order Convergence Method
        /// </summary>
        ITERATED_HEUN
    }

}
