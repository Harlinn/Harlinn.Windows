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
    /// Methods of calculating precipitation interception fraction
    /// </summary>
    public enum PrecipIceptMethod
    {
        /// <summary>
        /// interception is not represented (for routing mostly)
        /// </summary>
        PRECIP_ICEPT_NONE,
        /// <summary>
        /// pct of precip captured by canopy is user specified (TFRAIN,TFSNOW)
        /// </summary>
        PRECIP_ICEPT_USER,
        /// <summary>
        /// pct of precip captured by canopy is linearly proportional to LAI (Dingman)
        /// </summary>
        PRECIP_ICEPT_LAI,
        /// <summary>
        /// pct of precip captured by canopy is proportional to exp(LAI) (CLM)
        /// </summary>
        PRECIP_ICEPT_EXPLAI,
        /// <summary>
        /// pct of snow captured by canopy is proportional to LAI & snowfall rate (Hedstrom & Pomeroy 1998)
        /// </summary>
        PRECIP_ICEPT_HEDSTROM,
        /// <summary>
        /// pct of snow captured by canopy is function of temperature (SUMMA-like)
        /// </summary>
        PRECIP_ICEPT_STICKY
    }

}
