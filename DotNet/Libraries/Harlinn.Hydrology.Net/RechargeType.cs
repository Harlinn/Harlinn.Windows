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
    /// Method of modeling recharge to aquifers
    /// </summary>
    public enum RechargeType
    {
        /// <summary>
        /// uses recharge from data
        /// </summary>
        RECHARGE_FROMFILE,
        /// <summary>
        /// constant recharge method applied to aquifers
        /// </summary>
        RECHARGE_CONSTANT,
        /// <summary>
        /// constant recharge method applied to aquifers with area weighted separation to connected gw cells
        /// </summary>
        RECHARGE_CONSTANT_OVERLAP, 
    }

}
