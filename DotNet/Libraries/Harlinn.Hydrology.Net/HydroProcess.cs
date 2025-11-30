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
    /// Base class for physical hydrological processes
    /// </summary>
    public abstract class HydroProcess
    {
    
        readonly static IReadOnlyList<ParameterInfo> _emptyParameters = [];

        Model _model;

        /// <summary>
        /// Hydrological proccess, e.g., sublimation, infiltration, etc.
        /// </summary>
        HydroProcessType _process;
        
        /// <summary>
        /// indices of state variables/storage units that (typically) lose water/energy/mass (size: nConnections)
        /// </summary>
        int[] _fromIndices;
        
        /// <summary>
        /// indices of state variables/storage units that (typically) gain water/energy/mass (size: nConnections) (==iFrom if no mass/energy is exchanged in change of state variable)
        /// </summary>
        int[] _toIndices;
        
        /// <summary>
        /// usually 1, number of transfer routes between state variables/storage units
        /// </summary>
        int _nConnections;

        /// <summary>
        /// array of conditions for process to occur (ALL must be satisfied)
        /// </summary>
        Condition[] _pConditions;
        /// <summary>
        /// number of conditions
        /// </summary>
        int _nConditions;


        /// <summary>
        /// Initializes a new instance of the HydroProcess class using the specified model and hydro process type.
        /// </summary>
        /// <param name="model">The model that provides the data and configuration for the hydro process. Cannot be null.</param>
        /// <param name="hydroProcessType">The type of hydro process to be represented by this instance.</param>
        public HydroProcess(Model model, HydroProcessType hydroProcessType)
        {
            _model = model;
            _process = hydroProcessType;
        }

        /// <summary>
        /// multiple connection dynamic constructor
        /// </summary>
        public HydroProcess(Model model, HydroProcessType hydroProcessType, int nConns)
        {
            _model = model;
            _process = hydroProcessType;
            _nConnections = nConns;
            _fromIndices = new int[nConns];
            _toIndices = new int[nConns];
        }

        /// <summary>
        /// single connection constructor
        /// </summary>
        public HydroProcess(Model model, HydroProcessType hydroProcessType, int inIndex, int outIndex)
        {
            _model = model;
            _process = hydroProcessType;
            _nConnections = 1;
            _fromIndices = new int[1];
            _toIndices = new int[1];
            _fromIndices[0] = inIndex;
            _toIndices[0] = outIndex;
        }
        /// <summary>
        /// multiple connection constructor
        /// </summary>
        /// <param name="ptype"></param>
        /// <param name=""></param>
        public HydroProcess(Model model, HydroProcessType hydroProcessType, int[] inIndices, int[] outIndices, int nConnect)
        {

        }

        /// <summary>
        /// Returns the array of 'from' indices
        /// </summary>
        /// <returns></returns>
        public int[] GetFromIndices() 
        { 
            return _fromIndices; 
        }

        public int[] FromIndices => _fromIndices;

        /// <summary>
        /// Returns the array of 'to' indices
        /// </summary>
        /// <returns></returns>
        public int[] GetToIndices() 
        { 
            return _toIndices;   
        }

        public int[] ToIndices => _toIndices;


        /// <summary>
        /// Returns total number of connections between state variables manipulated by process
        /// </summary>
        /// <returns></returns>
        public int GetNumConnections() 
        { 
            return _nConnections; 
        }
        public HydroProcessType GetProcessType()
        {
            return _process;
        }

        public virtual int GetNumLatConnections() 
        { 
            return 0; 
        }

        public bool ShouldApply(HydroUnit pHRU)
        {
            return false;
        }

        //functions
        public void SetModel(Model model)
        {
            _model = model;
        }

        public Model Model => _model;

        public void AddCondition(ConditionBasis basis, Comparison compare_method, string data)
        {

        }

        public void Redirect(int toSVindex, int newToSVindex)
        {
                   
        }

        public virtual void Initialize()
        {
        }

        public virtual IReadOnlyList<ParameterInfo> GetParticipatingParamList()
        {
            return _emptyParameters;
        }


        //calculates and returns rates of water/energy LOSS of "iFrom" Storage Units/state variables (e.g., [mm/d] or [MJ/m2/d])
        //This is the gain of the "iTo" storage units [mm/d] or [MJ/m2/d] . For changes to state variables
        //that do not involve the movement of water/energy/mass between units (i.e., density changes), the iFrom and
        //iTo units are the same.
        public abstract void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates);

        public virtual void ApplyConstraints(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        { 
        }


        protected void DynamicSpecifyConnections(int nConnects)
        {
            _nConnections = nConnects;
            _fromIndices = new int[_nConnections];
            _toIndices = new int[_nConnections];
            for (int q = 0; q < _nConnections; q++)
            {
                _fromIndices[q] = DOESNT_EXIST;
                _toIndices[q] = DOESNT_EXIST;
            }
        }

    }
}
