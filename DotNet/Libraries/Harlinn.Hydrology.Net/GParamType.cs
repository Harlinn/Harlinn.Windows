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
    public enum GParamType
    {
        /// <summary>
        /// linear decay coefficient  [1/d]
        /// </summary>
        PAR_DECAY_COEFF,
        /// <summary>
        /// zero-order decay or loss [mg/m2/d]
        /// </summary>
        PAR_MASS_LOSS_RATE,
        /// <summary>
        /// linear transformation coeff [1/d for n=1, (mg/L)^-n /d for n!=1]
        /// </summary>
        PAR_TRANSFORM_COEFF,
        /// <summary>
        /// ratio of mass reactant to mass product [mg/mg]
        /// </summary>
        PAR_STOICHIO_RATIO,
        /// <summary>
        /// uptake coefficeint [-]
        /// </summary>
        PAR_UPTAKE_COEFF,
        /// <summary>
        /// transformation exponent [-]
        /// </summary>
        PAR_TRANSFORM_N,
        /// <summary>
        /// fixed equilibrium coefficient [-] (B=cc*A)
        /// </summary>
        PAR_EQFIXED_RATIO,
        /// <summary>
        /// linear equilibrium coefficient [1/d] k*(B-cc*A)
        /// </summary>
        PAR_EQUIL_COEFF,
        /// <summary>
        /// sorption coefficient [l/kg]
        /// </summary>
        PAR_SORPT_COEFF
    }
}
