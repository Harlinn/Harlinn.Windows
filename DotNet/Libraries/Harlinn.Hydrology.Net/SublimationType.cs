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
    /// Techniques for modelling sublimation
    /// </summary>
    public enum SublimationType
    {
        /// <summary>
        /// HBV model
        /// </summary>
        SUBLIM_ALL,
        /// <summary>
        /// sublimates at PET rate (not very realistic)
        /// </summary>
        SUBLIM_MAXIMUM,
        /// <summary>
        /// Sverdrup 1946 : adapted from Gray 1973 \cite Sverdrup1946JoAS \cite gray1974
        /// </summary>
        SUBLIM_SVERDRUP,
        /// <summary>
        /// Kuzmin 1972 : adapted from Gray 1973
        /// </summary>
        SUBLIM_KUZMIN,
        /// <summary>
        /// US Army Corps of Engineers : adapted from Gray 1973 \cite Engineers1956NPDPO
        /// </summary>
        SUBLIM_CENTRAL_SIERRA,
        /// <summary>
        /// Pomeroy Prairie Blowing Snow Model Sublimation : adapted from Pomeroy 1993 \cite Pomeroy1993JoH
        /// </summary>
        SUBLIM_PBSM,
        /// <summary>
        /// Canadian National Research Council [1959] - developed from Sverdrup
        /// </summary>
        SUBLIM_WILLIAMS,
        /// <summary>
        /// Kuchment Gelfan (1996) - essentially equivalent to Kuzmin
        /// </summary>
        SUBLIM_KUCHMENT_GELFAN,
        /// <summary>
        /// Bulk aerodynamic approach of Hock (2005)
        /// </summary>
        SUBLIM_BULK_AERO
    }

}
