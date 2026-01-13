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
    /// Stores external forcing functions for single HRU over current time step
    /// </summary>
    public enum ForcingType
    {
        F_PRECIP, F_PRECIP_DAILY_AVE, F_PRECIP_5DAY, F_SNOW_FRAC,
        F_RAINFALL, F_SNOWFALL, F_IRRIGATION,
        F_TEMP_AVE,
        F_TEMP_DAILY_MIN, F_TEMP_DAILY_MAX, F_TEMP_DAILY_AVE,
        F_TEMP_MONTH_MAX, F_TEMP_MONTH_MIN, F_TEMP_MONTH_AVE,
        F_TEMP_AVE_UNC, F_TEMP_MIN_UNC, F_TEMP_MAX_UNC,
        F_AIR_PRES, F_AIR_DENS, F_REL_HUMIDITY,
        F_CLOUD_COVER, F_SW_RADIA, F_LW_RADIA_NET, F_ET_RADIA, F_ET_RADIA_FLAT,
        F_SW_RADIA_NET, F_SW_RADIA_UNC, F_LW_INCOMING, F_SW_RADIA_SUBCAN, F_SW_SUBCAN_NET,
        F_DAY_LENGTH, F_DAY_ANGLE, F_WIND_VEL,
        F_PET, F_OW_PET, F_PET_MONTH_AVE,
        F_SUBDAILY_CORR, F_POTENTIAL_MELT,
        F_RECHARGE,
        F_PRECIP_CONC,
        F_PRECIP_TEMP,
        F_UNRECOGNIZED
    }






}
