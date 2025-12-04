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
using System.Collections;

namespace Harlinn.Hydrology
{
    public class HRUGroup : IReadOnlyList<HydroUnit>
    {
        /// <summary>
        /// HRU group name
        /// </summary>
        string _name;
        
        /// <summary>
        /// member HRUs (size = nHRUs)
        /// </summary>
        List<HydroUnit> _hydroUnits;
        
        /// <summary>
        /// index of group in master HRU Group array (in Model)
        /// </summary>
        int _global_kk;
        
        /// <summary>
        /// true if all HRUs in group are disabled
        /// </summary>
        bool _disabled;

        public HRUGroup(string tag, int global_ind)
        {
            _name = tag;
            _hydroUnits = new List<HydroUnit>();
            _global_kk = global_ind;
            _disabled = false;
        }

        /// <summary>
        /// Returns number of HRUs in instantiated HRU group.
        /// </summary>
        /// <returns>
        /// Number of HRUs in group.
        /// </returns>
        public int GetNumHRUs()
        {
            return _hydroUnits.Count;
        }

        /// <summary>
        /// Returns the name of HRU group.
        /// </summary>
        /// <returns>
        /// The name of HRU group.
        /// </returns>
        public string GetName() 
        {
            return _name;
        }

        public string Name => _name;

        /// <summary>
        /// Returns the unique HRU group global model index (kk)
        /// </summary>
        /// <returns>
        /// The index of HRU in global model array
        /// </returns>
        public int GetGlobalIndex()
        {
            return _global_kk;
        }

        /// <summary>
        /// Returns true if HRU with global index k_global is in group
        /// </summary>
        /// <param name="k_global">
        /// Global model index of an HRU
        /// </param>
        /// <returns>
        /// true if HRU with global index k_global is in group
        /// </returns>
        public bool IsInGroup(int k_global)
        {
            var count = _hydroUnits.Count;
            for (int k = 0; k < count; k++)
            {
                if (_hydroUnits[k].GetGlobalIndex() == k_global) 
                { 
                    return true; 
                }
            }
            return false;
        }

        /// <summary>
        /// Returns HRU corresponding to index k in group
        /// </summary>
        /// <param name="k">
        /// Index referring to kth element of the HRU Group
        /// </param>
        /// <returns>
        /// HRU corresponding to index k
        /// </returns>
        /// <exception cref="ArgumentOutOfRangeException">
        /// Thrown when the index k is out of range
        /// </exception>
        public HydroUnit GetHRU(int k)
        {
            if (k < 0 || k >= _hydroUnits.Count)
            {
                throw new ArgumentOutOfRangeException(nameof(k), "Invalid HRU index");
            }
            return _hydroUnits[k];
        }

        /// <summary>
        /// Adds a HydroUnit to the HRU group.
        /// </summary>
        /// <param name="pHRU"></param>
        public void AddHRU(HydroUnit pHRU)
        {
            ArgumentNullException.ThrowIfNull(pHRU);
            _hydroUnits.Add(pHRU);
        }

        /// <summary>
        /// Initializes the HRU group.
        /// </summary>
        public void Initialize()
        {
            if (_disabled)
            {
                var count = _hydroUnits.Count;
                for (int k = 0; k < count; k++)
                {
                    _hydroUnits[k].Disable();
                }
            }
        }

        /// <summary>
        /// disables HRU Group
        /// </summary>
        public void DisableGroup()
        {
            _disabled = true;
        }

        public void EmptyGroup()
        {
            _hydroUnits.Clear();
        }

        /// <summary>
        /// Returns average value of a state variable specified by index i over the total area covered by the HRU group
        /// </summary>
        /// <param name="i">
        /// Index corresponding to the state variable whose average will be calculated
        /// </param>
        /// <returns>
        /// Average of state variable with index i across all HRUs in group, per unit area coverage of group
        /// </returns>
        public double GetAvgStateVar(int i)
        {
            double sum = 0.0;
            double areasum = 0.0;
            double area;
            var count = _hydroUnits.Count;
            for (int k = 0; k < count; k++)
            {
                var hydroUnit = _hydroUnits[k];
                if (hydroUnit.IsEnabled)
                {
                    area = hydroUnit.GetArea();
                    sum += hydroUnit.GetStateVarValue(i) * area;
                    areasum += area;
                }
            }
            if (areasum == 0.0) 
            { 
                return 0.0; 
            }
            return sum / areasum;
        }

        /// <summary>
        /// Returns average value of the concentration specified by index i over the total area covered by the HRU group
        /// </summary>
        /// <param name="i">
        /// Index corresponding to the concentration whose average will be calculated
        /// </param>
        /// <returns>
        /// Average of the concentration with index i across all HRUs in group, per unit area coverage of group
        /// </returns>
        public double GetAvgConcentration(int i)
        {
            double sum = 0.0;
            double areasum = 0.0;
            double area;
            var count = _hydroUnits.Count;
            for (int k = 0; k < count; k++)
            {
                var hydroUnit = _hydroUnits[k];
                if (hydroUnit.IsEnabled)
                {
                    area = hydroUnit.GetArea();
                    sum += hydroUnit.GetConcentration(i) * area;
                    areasum += area;
                }
            }
            if (areasum == 0.0) 
            { 
                return 0.0; 
            }
            return sum / areasum;
        }

        /// <summary>
        /// Returns average value of a forcing function over the total area covered by the HRU group
        /// </summary>
        /// <param name="ftype">
        /// Type of the forcing whose average will be calculated
        /// </param>
        /// <returns>
        /// Average of forcing function across all HRUs in group, per unit area coverage of group
        /// </returns>
        public double GetAvgForcing(ForcingType ftype) 
        {
            double sum = 0.0;
            double areasum = 0.0;
            double area;
            var count = _hydroUnits.Count;
            for (int k=0;k<count;k++)
            {
                var hydroUnit = _hydroUnits[k];
                if (hydroUnit.IsEnabled)
                {
                    area = hydroUnit.GetArea();
                    sum += hydroUnit.GetForcing(ftype) * area;
                    areasum += area;
                }
            }
            if (areasum == 0.0) 
            { 
                return 0.0; 
            }
            return sum / areasum;
        }

        /// <summary>
        /// Returns area-weighted average of specified cumulative flux over HRU group
        /// </summary>
        /// <param name="i">
        /// index of storage compartment
        /// </param>
        /// <param name="to">
        /// true if evaluating cumulative flux to storage compartment, false for 'from'
        /// </param>
        /// <returns>
        /// Area-weighted average of cumulative flux to storage compartment i
        /// </returns>
        public double GetAvgCumulFlux(int i, bool to)
        {
            // Area-weighted average
            double sum = 0.0;
            double areasum = 0.0;
            double area;
            var count = _hydroUnits.Count;
            for (int k = 0; k < count; k++)
            {
                var hydroUnit = _hydroUnits[k];
                if (hydroUnit.IsEnabled)
                {
                    area = hydroUnit.GetArea();
                    sum += hydroUnit.GetCumulFlux(i, to) * area;
                    areasum += area;
                }
            }
            if (areasum == 0.0) 
            { 
                return 0.0; 
            }
            return sum / areasum;
        }

        /// <summary>
        /// Returns area-weighted average of  cumulative flux between two compartments over HRU Group
        /// </summary>
        /// <param name="iFrom">
        /// index of 'from' storage compartment
        /// </param>
        /// <param name="iTo">
        /// index of 'to' storage compartment
        /// </param>
        /// <returns>
        /// Area-weighted average of cumulative flux between two compartments over HRU Group
        /// </returns>
        public double GetAvgCumulFluxBet(int iFrom, int iTo)
        {
            //Area-weighted average
            double sum = 0.0;
            double areasum = 0.0;
            double area;
            var count = _hydroUnits.Count;
            for (int k = 0; k < count; k++)
            {
                var hydroUnit = _hydroUnits[k];
                if (hydroUnit.IsEnabled)
                {
                    area = hydroUnit.GetArea();
                    sum += hydroUnit.GetCumulFluxBet(iFrom, iTo) * area;
                    areasum += area;
                }
            }
            if (areasum == 0.0) 
            { 
                return 0.0; 
            }
            return sum / areasum;
        }

        public int Count => ((IReadOnlyCollection<HydroUnit>)_hydroUnits).Count;

        public HydroUnit this[int index] => ((IReadOnlyList<HydroUnit>)_hydroUnits)[index];

        public IEnumerator<HydroUnit> GetEnumerator()
        {
            return ((IEnumerable<HydroUnit>)_hydroUnits).GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return ((IEnumerable)_hydroUnits).GetEnumerator();
        }
    }

}
