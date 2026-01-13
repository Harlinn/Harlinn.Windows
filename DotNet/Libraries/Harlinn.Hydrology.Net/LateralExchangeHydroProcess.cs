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
using static Harlinn.Hydrology.Constants;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Base class for lateral exchange processes
    /// </summary>
    public abstract class LateralExchangeHydroProcess : HydroProcess
    {
        static readonly int[] _emptyInt32Array = Array.Empty<int>();


        /// <summary>
        /// number of HRU lateral connections
        /// </summary>
        int _nLatConnections;
        /// <summary>
        /// array of HRU from indices [size: nLatConnections] (JRC: Usually 1?)
        /// </summary>
        int[] _kFrom = _emptyInt32Array;
        /// <summary>
        /// array of HRU to indices [size: nLatConnections]
        /// </summary>
        int[] _kTo = _emptyInt32Array;
        /// <summary>
        /// array of 'From' state variable indices [size: nLatConnections]
        /// </summary>
        int[] _iFromLat = _emptyInt32Array;
        /// <summary>
        /// array of 'To' state variable indices [size: nLatConnections]
        /// </summary>
        int[] _iToLat = _emptyInt32Array;

        /// <summary>
        /// global index of lateral flow process
        /// </summary>
        int _LatFlowIndex;


        public LateralExchangeHydroProcess(Model model, HydroProcessType hydroProcessType)
            : base(model, hydroProcessType)
        {
            _LatFlowIndex = model.GetNumLatFlowProcesses();
            model.CountOneMoreLatFlowProcess();
        }

        protected void DynamicSpecifyLatConnections(int nLatConnects)
        {
            _nLatConnections = nLatConnects;
            if (_nLatConnections != 0)
            {
                _kFrom = new int[_nLatConnections];
                _kTo = new int[_nLatConnections];
                _iFromLat = new int[_nLatConnections];
                _iToLat = new int[_nLatConnections];

                Array.Fill(_kFrom, DOESNT_EXIST);
                Array.Fill(_kTo, DOESNT_EXIST);
                Array.Fill(_iFromLat, DOESNT_EXIST);
                Array.Fill(_iToLat, DOESNT_EXIST);
            }
        }

        /// <summary>
        /// Returns global lateral flow process index (ranges from 0 to _nLatFlowProcesses)
        /// </summary>
        /// <returns>
        /// The global lateral flow process index
        /// </returns>
        public int GetLateralFlowIndex()
        {
            return _LatFlowIndex;
        }

        /// <summary>
        /// Returns number of lateral connections between hydro units.
        /// </summary>
        /// <returns>
        /// Number of lateral connections between hydro units
        /// </returns>
        public override int GetNumLatConnections()
        {
            return _nLatConnections;
        }

        /// <summary>
        /// Returns array of global indices (k's) of 'from' HRUs
        /// </summary>
        /// <returns>
        /// array of global indices (k's) of 'from' HRUs
        /// </returns>
        public int[] GetFromHRUIndices()
        {
            return _kFrom;
        }

        /// <summary>
        /// Returns array of global indices (k's) of 'to' HRUs
        /// </summary>
        /// <returns>
        /// array of global indices (k's) of 'to' HRUs
        /// </returns>
        public int[] GetToHRUIndices()
        {
            return _kTo;
        }

        /// <summary>
        /// Returns array of global indices (i's) of 'from' state variables
        /// </summary>
        /// <returns>
        /// array of global indices (i's) of 'from' state variables
        /// </returns>
        public int[] GetLateralFromIndices()
        {
            return _iFromLat;
        }

        /// <summary>
        /// Returns array of global indices (i's) of 'to' state variables
        /// </summary>
        /// <returns>
        /// array of global indices (i's) of 'to' state variables
        /// </returns>
        public int[] GetLateralToIndices()
        {
            return _iToLat;
        }

        public override void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
        }

        public abstract void GetRatesOfChange(double[,] stateVars, HydroUnit[] hydroUnits, Options options, TimeStruct tt, double[] exchangeRates);


    }
}
