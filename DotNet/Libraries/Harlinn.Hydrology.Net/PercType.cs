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
    /// Method of modeling percolation between soil layers
    /// </summary>
    public enum PercType
    {
        /// <summary>
        /// percolation method used in GAWSER (Schroeter, 19..) \cite Schroeter1988
        /// </summary>
        PERC_GAWSER,
        /// <summary>
        /// percolation method used in GAWSER limited down to FC
        /// </summary>
        PERC_GAWSER_CONSTRAIN,
        /// <summary>
        /// percolation method used in VIC (clark et al., 2007), HBV (soil to fast res) \cite Clark2008WRR
        /// </summary>
        PERC_POWER_LAW,
        /// <summary>
        /// percolation methods used in PRMS (clark et al., 2007)
        /// </summary>
        PERC_PRMS,
        /// <summary>
        /// percolation method in Sacremento  (Clark et al., 2007)
        /// </summary>
        PERC_SACRAMENTO,
        /// <summary>
        /// Linear storage approach
        /// </summary>
        PERC_LINEAR,
        /// <summary>
        /// Linear storage approach, analytical sol'n over timestep
        /// </summary>
        PERC_LINEAR_ANALYTIC,
        /// <summary>
        /// constant percolation rate (e.g., HBV)
        /// </summary>
        PERC_CONSTANT,
        /// <summary>
        /// percolation method from GR4J model
        /// </summary>
        PERC_GR4J,
        /// <summary>
        /// groundwater exchange from GR4J model
        /// </summary>
        PERC_GR4JEXCH,
        /// <summary>
        /// groundwater exchange from GR4J model
        /// </summary>
        PERC_GR4JEXCH2,
        /// <summary>
        /// percolation to aspen trees (S. Grass, 2018)
        /// </summary>
        PERC_ASPEN
    }











}
