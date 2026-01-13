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
    /// Custom table output generator
    /// </summary>
    public class CustomTable
    {
        /// <summary>
        /// output file stream
        /// </summary>
        TextWriter _CUSTTAB;
        string _filename;

        /// <summary>
        /// index of subbasin group
        /// </summary>
        int _sb_grp_ind;

        /// <summary>
        /// pointer to model
        /// </summary>
        Model _pModel;

        ForcingType _aForcings;
        SVType _aSVtypes;
        int[] _aLayers;
        int _nCols;
    }
}
