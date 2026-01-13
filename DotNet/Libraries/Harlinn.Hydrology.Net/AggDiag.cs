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
    public struct AggDiag
    {
        AggStat _aggType;
        string _dataType;
        int _groupIndex;

        public AggDiag()
        {
            _dataType = string.Empty;
            _groupIndex = -1;
        }

        public AggDiag(AggStat aggType, string dataType, int groupIndex = Constants.DOESNT_EXIST)
        {
            _aggType = aggType;
            _dataType = dataType;
            _groupIndex = groupIndex;
        }

        /// <summary>
        /// aggregation type (supports AVERAGE/MEDIAN/MIN/MAX)
        /// </summary>
        public AggStat AggType { get => _aggType; set => _aggType = value; }
        /// <summary>
        /// observation datatype string e.g., "HYDROGRAPH"
        /// </summary>
        public string DataType { get => _dataType; set => _dataType = value; }
        /// <summary>
        /// group index (or DOESNT_EXIST, if applied to all)
        /// </summary>
        public int GroupIndex { get => _groupIndex; set => _groupIndex = value; }

        /// <summary>
        /// group index (or DOESNT_EXIST, if applied to all)
        /// </summary>
        public int kk { get => _groupIndex; set => _groupIndex = value; }

    }


}
