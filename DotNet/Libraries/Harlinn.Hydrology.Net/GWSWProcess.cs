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
    /// Base class for groundwater-surface water processes
    /// </summary>
    public class GWSWProcess
    {
        /// <summary>
        /// pointer to groundwater model
        /// </summary>
        GroundwaterModel pGWModel;

        /// <summary>
        /// Number of gw model nodes with process
        /// </summary>
        int _nnodes;
        /// <summary>
        /// array of nodes with process
        /// </summary>
        int[] _inodes;
        /// <summary>
        /// Name of process to be displayed in MFUSG Budget
        /// </summary>
        string _pProcName;

        /// <summary>
        /// Map of the set of nodes with process, keyed by HRU
        /// </summary>
        Dictionary<int, SortedSet<int>> _mNodesByHRU;
        /// <summary>
        /// Hash to easily find index of a node within _inode [nodeid, index]
        /// </summary>
        Dictionary<int, int> _mNodeIndex;
    }
}
