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
    /// collection of Subbasins
    /// </summary>
    public class SubbasinGroup
    {
        /// <summary>
        /// Subbasin group name
        /// </summary>
        string _name;
        /// <summary>
        /// Number of HRUs present in group
        /// </summary>
        int _nSubbasins;
        /// <summary>
        /// member HRUs (size = nHRUs)
        /// </summary>
        SubBasin[] _pSubbasins;
        /// <summary>
        /// index of group in master Subbasin Group array (in CModel)
        /// </summary>
        int _global_pp;
        /// <summary>
        /// true if all Subbasins in group are disabled
        /// </summary>
        bool _disabled;

        internal int GetGlobalIndex()
        {
            throw new NotImplementedException();
        }

        internal string GetName()
        {
            throw new NotImplementedException();
        }

        internal int GetNumSubbasins()
        {
            throw new NotImplementedException();
        }

        internal SubBasin? GetSubBasin(int p_loc)
        {
            throw new NotImplementedException();
        }
    }

}
