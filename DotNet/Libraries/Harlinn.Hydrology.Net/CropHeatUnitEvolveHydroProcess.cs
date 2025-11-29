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

using static Harlinn.Hydrology.Constants;
using static System.Math;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Calculates the evolution of Crop Heat Units
    /// </summary>
    public class CropHeatUnitEvolveHydroProcess : HydroProcess
    {
        /// <summary>
        /// Method of modeling CHUs selected
        /// </summary>
        CHUEvolveType _type;

        public CropHeatUnitEvolveHydroProcess(Model model, CHUEvolveType type) 
            : base(model, HydroProcessType.CROP_HEAT_UNIT_EVOLVE)
        {
            _type = type;

            //used by all crop heat routines
            int iCropHeat; 
            iCropHeat = model.GetStateVarIndex(SVType.CROP_HEAT_UNITS);
            Runtime.ExitGracefullyIf(iCropHeat == DOESNT_EXIST, "CROP HEAT EVOLVE: crop heat unit state variable required", ExitCode.BAD_DATA);

            if (type == CHUEvolveType.CHU_ONTARIO)
            {
                DynamicSpecifyConnections(1);
                FromIndices[0] = iCropHeat; 
                ToIndices[0] = iCropHeat;
            }
            else
            {
                Runtime.ExitGracefully("CmvCropHeatUnitEvolve::Constructor: undefined crop heat evolution algorithm", ExitCode.BAD_DATA);
            }
        }

        public static void GetParticipatingStateVarList(CHUEvolveType CHU_type, out SVType[] aSV, out int[] aLev)
        {
            aSV = [SVType.CROP_HEAT_UNITS];
            aLev = [DOESNT_EXIST];
        }

        public override void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            if (hydroUnit.GetHRUType() != HRUType.HRU_STANDARD) 
            {
                //Lakes & Glaciers
                return; 
            }

            double CHU, old_CHU;
            CHU = stateVars[Model.GetStateVarIndex(SVType.CROP_HEAT_UNITS)];
            old_CHU = CHU;

            if (_type == CHUEvolveType.CHU_ONTARIO)
            {

                double CHU_day, CHU_night;

                double temp_ave = hydroUnit.GetForcingFunctions().temp_daily_ave;
                double temp_max = hydroUnit.GetForcingFunctions().temp_daily_max;
                double temp_min = hydroUnit.GetForcingFunctions().temp_daily_min;
                bool growing_season = (CHU > -0.5);

                if (!growing_season)
                {
                    if (temp_ave > 12.8) 
                    {
                        // [fix hack] This is a stopgap, should use 3_day min temp (non-existent F.temp_3daymin??)

                        //CHU reset to zero at beginning of growing season
                        CHU = 0.0; 
                    }
                }
                else if (growing_season)
                {
                    CHU_day = Max(3.33 * (temp_max - 10) - 0.084 * Pow(temp_max - 10.0, 2.0), 0.0);
                    CHU_night = Max(1.8 * (temp_min - 4.4), 0.0);
                    CHU += 0.5 * (CHU_day + CHU_night);

                    // end of growing season: CHU set to -1
                    if (temp_ave < -2.0) 
                    { 
                        CHU = -1.0; 
                    }
                    if (tt.month > 9) 
                    {
                        // september 30th
                        CHU = -1.0; 
                    }
                }
                rates[0] = (CHU - old_CHU) / options.timestep;
            }
            else
            {
                rates[0] = 0.0;
            }
        }
    }
}
