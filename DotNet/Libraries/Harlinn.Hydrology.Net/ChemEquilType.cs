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
    enum ChemEquilType
    {
        /// <summary>
        /// constitutent 2 mass is a linear function of constituent 1 mass (B=cc*A)
        /// </summary>
        EQUIL_FIXED_RATIO,
        /// <summary>
        /// rate-limited linear equilibrium dB/dt=-k*(B-cc*A)
        /// </summary>
        EQUIL_LINEAR,
        /// <summary>
        /// linear equilibrium sorption Cs=Kd*Cw (constit1=aqueous, constit2=sorbed)
        /// </summary>
        EQUIL_LINEAR_SORPTION
    }
}
