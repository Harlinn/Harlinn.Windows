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
    public class GroundwaterModel
    {
        Model _pModel;
        GWRiverConnection _pRiver;

        /// <summary>
        /// Nodes in the groundwater model
        /// </summary>
        int _nNodes;
        /// <summary>
        /// number of layers in the groundwater model
        /// </summary>
        int _nLayers;
        /// <summary>
        /// Array of number of nodes per layer [size:_nLayers]
        /// </summary>
        int[] _aNodesPerLayer;

        /// <summary>
        /// Total # of Stress periods
        /// </summary>
        int _nStressPeriods;
        /// <summary>
        /// Current stress period (kper in MFUSG)
        /// </summary>
        int _iStressPeriod;

        /// <summary>
        /// Number of steps in each stress period [size:_nStressPeriods]
        /// </summary>
        int[] _aNumSteps;
        /// <summary>
        /// Current time step (kstp in MFUSG)
        /// </summary>
        int _iStep;

        /// <summary>
        /// Maximum outer interations for GW Solver
        /// </summary>
        int _maxiter;
        /// <summary>
        /// Number of items in the Modflow IUNIT array
        /// </summary>
        int _niunit;
        /// <summary>
        /// Equivalent to MFUSG var "idoflow" - 0 means don't solve (Steady state or transport step).
        /// </summary>
        int _doSolve;
        /// <summary>
        /// Model Convergence success (from MFUSG)
        /// </summary>
        bool _Converged;

        /// <summary>
        /// GW-SW Processes in Raven
        /// </summary>
        int _nProcesses;
        /// <summary>
        /// map of GWSW Processes with type as key (IMPORTANT: are also in Model _pProcesses).
        /// </summary>
        Dictionary<HydroProcessType, GWSWProcess> _mGWSWProcesses;

        /// <summary>
        /// Length of each stress period [d] (perlen in MFUSG)
        /// </summary>
        double[] _aStressPeriodLength;
        /// <summary>
        /// Array of conductance terms to be added to MFUSG LHS, by node [size _nNodes+1] (to index from 1)
        /// </summary>
        double[] _aProcessesAMAT;
        /// <summary>
        /// Array of volumes to added to MFUSG RHS, by node [size _nNodes+1] (to index from 1)
        /// </summary>
        double[] _aProcessesRHS;
        /// <summary>
        /// Sum of fluxes (one for each HRU) to/from the GW compartment.
        /// Used to determine non-GWSW process flux to GW model
        /// </summary>
        double[] _aGWSWFluxes;

        /// <summary>
        /// 2D "matrix" of weights relating which HRUs are connected to which GW cells
        /// =A_ki/A_i where A_ki is area of overlap between HRU k and node i and A_i is area of node i
        /// Only contains weights for layer 1 (see HRU-node comment at top)
        /// Dimensions : [_nHydroUnits][_aNodesPerLayer[0]] (variable)
        /// </summary>
        Dictionary<Tuple<int, int>, double> _mOverlapWeights;
        /// <summary>
        /// Map of length _nNodes with vectors of the HRUs connected to that node
        /// </summary>
        Dictionary<int, List<int>> _mNodesByHRU;
        /// <summary>
        /// Map of length _nHRU with vectors of the nodes connected to that HRU
        /// </summary>
        Dictionary<int, List<int>> _mHRUsByNode;
    }

}
