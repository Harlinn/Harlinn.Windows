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
    /// Algorithms for modeling infiltration
    /// </summary>
    public enum InfilType
    {
        /// <summary>
        /// SCS curve number method for infiltration
        /// </summary>
        INF_SCS,
        /// <summary>
        /// SCS curve number method for infiltration without abstraction representation
        /// </summary>
        INF_SCS_NOABSTRACTION,
        /// <summary>
        /// Rational method for infiltration
        /// </summary>
        INF_RATIONAL,
        /// <summary>
        /// Simple infiltration method where all rainfall infiltrates into soil
        /// </summary>
        INF_ALL_INFILTRATES,
        /// <summary>
        /// Standard Green-Ampt infiltration model
        /// </summary>
        INF_GREEN_AMPT,
        /// <summary>
        /// Simple Green-Ampt infiltration model
        /// </summary>
        INF_GA_SIMPLE,
        /// <summary>
        /// Upscaled Green-Ampt infiltration model from Craig (2010)
        /// </summary>
        INF_UPSCALED_GREEN_AMPT,
        /// <summary>
        /// Philip 1957 Infiltration model
        /// </summary>
        INF_PHILIP_1957,
        /// <summary>
        /// VIC (Variable Infiltration Capacity) Infiltration model
        /// </summary>
        INF_VIC,
        /// <summary>
        /// VIC-ARNO Infiltration model
        /// </summary>
        INF_VIC_ARNO,
        /// <summary>
        ///  TOPMODEL Infiltration model
        /// </summary>
        INF_TOPMODEL,
        /// <summary>
        /// PRMS Infiltration model
        /// </summary>
        INF_PRMS,
        /// <summary>
        /// HBV Infiltration model
        /// </summary>
        INF_HBV,
        /// <summary>
        /// UBC Watershed model infiltration algorithm
        /// </summary>
        INF_UBC,
        /// <summary>
        /// GR4J Watershed model infiltration algorithm
        /// </summary>
        INF_GR4J,
        /// <summary>
        /// HMETS model infiltration algorithm
        /// </summary>
        INF_HMETS,
        /// <summary>
        /// Xinanxiang model infiltration algorithm
        /// </summary>
        INF_XINANXIANG,
        /// <summary>
        /// Probability Distributed Model (PDM) of Moore (1985) [HYMOD]
        /// </summary>
        INF_PDM,
        /// <summary>
        /// Austrailian Water Balance Model of Boughton (1993)
        /// </summary>
        INF_AWBM
    }
}
