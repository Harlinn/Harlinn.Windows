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
    /// Methods for modelling a convolution
    /// </summary>
    public enum ConvolutionType
    {
        /// <summary>
        /// Triangular UH
        /// </summary>
        CONVOL_TRIANGLE,
        /// <summary>
        /// GR4J UH type 1
        /// </summary>
        CONVOL_GR4J_1,
        /// <summary>
        /// GR4J UH type 2
        /// </summary>
        CONVOL_GR4J_2,
        /// <summary>
        /// Gamma distribution unit hydrograph - uses params alpha_Gamma, beta_Gamma
        /// </summary>
        CONVOL_GAMMA,
        /// <summary>
        /// Gamma distribution unit hydrograph 2 - uses params alpha_Gamma2, beta_Gamma2
        /// </summary>
        CONVOL_GAMMA_2
    }
}
