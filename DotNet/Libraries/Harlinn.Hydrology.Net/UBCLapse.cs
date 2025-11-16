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
    /// UBC lapse rate codes
    /// </summary>
    public class UBCLapse
    {
        // defined in UBCWM manual

        /// <summary>
        /// [0..1] Precipitation gradient modification factor (default 0.01)
        /// </summary>
        public double A0STAB;
        /// <summary>
        /// [degC / 1000 m] Lapse rate for maximum temperatures when  the station elevation is less than 2000 m (default 10)
        /// </summary>
        public double A0TLXM;
        /// <summary>
        /// [degC / 1000 m] Lapse rate for minimum temperatures when the station elevation is less than 2000 m (default 0.5)
        /// </summary>
        public double A0TLNM;
        /// <summary>
        /// [degC / 1000 m] Lapse rate for maximum temperatures when the station elevation is greater than 2000 m (default 6.4)
        /// </summary>
        public double A0TLXH;
        /// <summary>
        /// [degC / 1000 m] Lapse rate for minimum temperatures when the station elevation is greater than 2000 m (default 2.0)
        /// </summary>
        public double A0TLNH;
        /// <summary>
        /// [degC / 1000 m] Lapse rate of maximum temperature range for elevations below 2000 m (default 6.0)
        /// </summary>
        public double P0TEDL;
        /// <summary>
        /// [degC / 1000 m] Lapse rate of maximum temperature range for elevations above 2000 m (default 0.0)
        /// </summary>
        public double P0TEDU;
        /// <summary>
        /// [m] Reference elevation for precipitation gradient P0GRADL
        /// </summary>
        public double E0LLOW;
        /// <summary>
        /// [m] Elevation above which precipitation gradient P0GRADM applies. Set at approx. 1/2 barrier height
        /// </summary>
        public double E0LMID;
        /// <summary>
        /// [m] Elevation above which the precipitation gradient P0GRADU applies.  Set at approx. 2/3 barrier height
        /// </summary>
        public double E0LHI;
        /// <summary>
        /// [%, 0..20] Precipitation gradient factor for elevations below E0LMID (default 5)
        /// </summary>
        public double P0GRADL;
        /// <summary>
        /// [%, 0..20] Precipitation gradient factor for elevations below E0LHI (default 0)
        /// </summary>
        public double P0GRADM;
        /// <summary>
        /// [%, 0..20] Precipitation gradient factor for elevations above E0LHI (default 0)
        /// </summary>
        public double P0GRADU;
        /// <summary>
        /// [mm / 1000 m] Lapse rate of potential evapotranspiration factor A0EDDF (default 0.9)
        /// </summary>
        public double A0PELA;
        /// <summary>
        /// [degC] (A0TERM)
        /// </summary>
        public double max_range_temp;
        /// <summary>
        /// [mm/d] Threshold precipitation for temperature lapse rate (default 5.0)
        /// </summary>
        public double A0PPTP;  
    }

}
