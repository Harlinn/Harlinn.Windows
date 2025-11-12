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
    /// Methods used for calculating potential evapotranspiration (PET)
    /// </summary>
    public enum EvapMethod
    {
        /// <summary>
        /// constant uniform PET 
        /// </summary>
        PET_CONSTANT,
        /// <summary>
        /// read PET from time series file
        /// </summary>
        PET_DATA,
        /// <summary>
        /// all PET calculations disabled - PET==0 (for Routing only mode)
        /// </summary>
        PET_NONE,
        /// <summary>
        /// linearly proportional to temperature above zero
        /// </summary>
        PET_LINEAR_TEMP,
        /// <summary>
        /// PET estimated from specified monthly averages and daily temperature
        /// </summary>
        PET_FROMMONTHLY,
        /// <summary>
        /// PET estimated from specified monthly averages and daily temperature (UBCWM-style)
        /// </summary>
        PET_MONTHLY_FACTOR,
        /// <summary>
        /// Penman-Monteith equation
        /// </summary>
        PET_PENMAN_MONTEITH,
        /// <summary>
        /// Penman Combination approach
        /// </summary>
        PET_PENMAN_COMBINATION,
        /// <summary>
        /// Priestley Taylor
        /// </summary>
        PET_PRIESTLEY_TAYLOR,
        /// <summary>
        /// Hargreaves method
        /// </summary>
        PET_HARGREAVES,
        /// <summary>
        /// Hargreaves (1985) method
        /// </summary>
        PET_HARGREAVES_1985,
        /// <summary>
        /// Hamon (19??) method
        /// </summary>
        PET_HAMON,
        PET_JENSEN_HAISE,
        PET_TURC_1961,
        PET_MAKKINK_1957,
        PET_SHUTTLEWORTH_WALLACE,
        /// <summary>
        /// Simplified Penman equation from eqn 33 of Valiantzas (2006)
        /// </summary>
        PET_PENMAN_SIMPLE33,
        /// <summary>
        /// Simplified Penman equation from eqn 39 of Valiantzas (2006)
        /// </summary>
        PET_PENMAN_SIMPLE39,
        /// <summary>
        /// Granger  Gray PET from CRHM (Granger and Gray, 1989)
        /// </summary>
        PET_GRANGERGRAY,
        /// <summary>
        /// MOHYSE algorithm (https://docplayer.fr/69668879-Le-modele-hydrologique-mohyse.html)
        /// </summary>
        PET_MOHYSE,
        /// <summary>
        /// Simple PET from Oudin et. al., 2005
        /// </summary>
        PET_OUDIN,
        /// <summary>
        /// From Linacre, Agricultural Meteorology, 1977
        /// </summary>
        PET_LINACRE,
        /// <summary>
        /// linear function of vapour deficit, c*(e_sat-e_a) from Seitz and Moore, 2020
        /// </summary>
        PET_VAPDEFICIT,
        /// <summary>
        /// a blended combination of 2 or more of the methods above
        /// </summary>
        PET_BLENDED,
        /// <summary>
        /// special PET type for unrecognized commands
        /// </summary>
        PET_UNKNOWN
    }
}
