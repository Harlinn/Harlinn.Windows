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
    public class GWRiverConnection
    {
        public enum CalcMode { RIVER, DRAIN };
        public enum CondType { CONDUCTANCE, UNITCOND };

        /// <summary>
        /// groundwater model
        /// </summary>
        GroundwaterModel pGWModel;
        CalcMode _mode;
        CondType _condtype;
        /// <summary>
        /// Number of gw model segments
        /// </summary>
        int _nSeg;
        /// <summary>
        /// 2D array indices of segment nodes (3x each)
        /// </summary>
        int[,] _aNodes;
        /// <summary>
        /// array of subbasin index for each segment
        /// </summary>
        int[] _aSubBasin;
        /// <summary>
        /// 2D array of node barycentric weights (3x start, 3x end)
        /// </summary>
        double[,] _aWeights;
        /// <summary>
        /// array of Segment lengths (only one per segment!)
        /// </summary>
        double[] _aLength;
        /// <summary>
        /// 2D array of elevations (segment start, end)
        /// </summary>
        double[,] _aElevs;
        /// <summary>
        /// 2D array of conductances (start, end)
        /// </summary>
        double[,] _aCond;
        /// <summary>
        /// array of GW fluxes to river, by segment
        /// </summary>
        double[] _aGWFlux;

        /// <summary>
        /// Local storage of subbasin count
        /// </summary>
        int _NB;
        /// <summary>
        /// Number of segments in each subbasin [NB] (SB index, not SBID)
        /// </summary>
        int[] _anSegmentsBySB;
        /// <summary>
        /// 2D array of segments, arranged as [NB][segments]
        /// </summary>
        int[,] _aSegmentsBySB;

    }

}
