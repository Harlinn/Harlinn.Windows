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

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Models a single contiguous portion of watershed with homogeneous 
    /// land use/land type and homogeneous properties
    /// </summary>
    public class HydroUnit
    {
        Model _pModel;

        /// <summary>
        /// Unique HRU identifier
        /// </summary>
        long _ID;
        /// <summary>
        /// Global model index as stored in CModel array (can/will be different from ID)
        /// </summary>
        int _global_k;
        /// <summary>
        /// contributing drainage area for HydroUnit [km^2]
        /// </summary>
        double _Area;
        /// <summary>
        /// global index p (not ID!) of subbasin this HRU is in
        /// </summary>
        int _SubbasinInd;
        /// <summary>
        /// centroid of HRU
        /// </summary>
        Location _Centroid;
        /// <summary>
        /// Standard, Lake, Rock, Glacier, etc...
        /// </summary>
        HRUType _HRUType;
        /// <summary>
        /// true if processes are not simulated for this HRU
        /// </summary>
        bool _Disabled;
        /// <summary>
        /// true if HRU is linked to Reservoir
        /// </summary>
        bool _res_linked;

        // Model State variables:

        /// <summary>
        /// Array of *current value* of state variable i with size CModel::nStateVars [mm] for water storage, permafrost depth, snow depth, [MJ/m^2] for energy storage
        /// </summary>
        double[] _aStateVar;

        // Model Forcing functions:
        /// <summary>
        /// *current values* of forcing functions for time step (precip, temp, etc.)
        /// </summary>
        Force _Forcings;

        // property structures (from soil, veg, aq, surface classes, class-specific)

        /// <summary>
        /// average elevation of HRU [masl]
        /// </summary>
        double _AvgElevation;

        /// <summary>
        /// average terrain aspect [rad counterclockwise from north]
        /// </summary>
        double _AvgAspect;

        /// <summary>
        /// average terrain slope [rad]
        /// </summary>
        double _AvgSlope;

        /// <summary>
        /// latitude of centroid [rad]
        /// </summary>
        double _LatRad;
        /// <summary>
        /// equivalent latitude for slope/aspect  [rad]
        /// </summary>
        double _LatEq;
        /// <summary>
        /// effective solar noon correction for slope [days]
        /// </summary>
        double _SolarNoon;

        /// <summary>
        /// HRU-specific precipitation correction factor
        /// </summary>
        double _PrecipMult;
        /// <summary>
        /// index of met gauge to be used regardless of interpolation scheme (or DOESNT_EXIST, by default)
        /// </summary>
        int _SpecifiedGaugeIdx;

        /// <summary>
        /// array of pointers to structures with profile soil properties
        /// </summary>
        Soil[] _pSoil = new Soil[MAX_SOILLAYERS];

        /// <summary>
        /// vegetation properties
        /// </summary>
        Vegetation _pVeg;
        /// <summary>
        /// land use/land type properties
        /// </summary>
        Surface _pSurface;
        /// <summary>
        /// terrain properties
        /// </summary>
        Terrain _pTerrain;

        // variable property structures (locally stored, HRU-specific)

        /// <summary>
        /// soil layer thicknesses [m]
        /// </summary>
        double[] aThickness = new double[MAX_SOILLAYERS];


        /// <summary>
        /// derived vegetation properties
        /// </summary>
        VegetationVariable _VegVar;

        internal Location GetCentroid()
        {
            throw new NotImplementedException();
        }

        internal double GetElevation()
        {
            throw new NotImplementedException();
        }
    }
}
