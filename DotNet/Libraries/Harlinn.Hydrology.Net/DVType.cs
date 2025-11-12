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
    /// Decision variable type
    /// </summary>
    public enum DVType
    {
        /// <summary>
        /// outflow from reach
        /// </summary>
        DV_QOUT,
        /// <summary>
        /// outflow from reservoir
        /// </summary>
        DV_QOUTRES,
        /// <summary>
        /// reservoir stage
        /// </summary>
        DV_STAGE,
        /// <summary>
        /// change in reservoir stage over time step
        /// </summary>
        DV_DSTAGE,
        /// <summary>
        /// binary integer value for above/beneath stage-discharge sill
        /// </summary>
        DV_BINRES,
        /// <summary>
        /// delivery of water demand
        /// </summary>
        DV_DELIVERY,
        /// <summary>
        /// return flows to reach
        /// </summary>
        DV_RETURN,
        /// <summary>
        /// user specified decision variable
        /// </summary>
        DV_USER,
        /// <summary>
        /// slack variable for goal satisfaction
        /// </summary>
        DV_SLACK
    }
}
