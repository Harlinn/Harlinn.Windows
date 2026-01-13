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
    /// Coordinates transport simulation
    /// </summary>
    public class TransportModel
    {
        Model _model;

        /// <summary>
        /// number of advective/dispersive transport connections between water storage units
        /// </summary>
        int _nAdvConnections;
        /// <summary>
        /// state variable indices of water compartment source      [size: nAdvConnections]
        /// </summary>
        int[] _iFromWater;
        /// <summary>
        /// state variable indices of water compartment destination [size: nAdvConnections]
        /// </summary>
        int[] _iToWater;
        /// <summary>
        /// process index (j*) of connection [size: nAdvConnections]
        /// </summary>
        int[] _js_indices;

        /// <summary>
        /// number of lateral advective transport connections between water storage units
        /// </summary>
        int _nLatConnections;
        /// <summary>
        /// state variable indices of water compartment source      [size: _nLatConnections]
        /// </summary>
        int[] _iLatFromWater;
        /// <summary>
        /// state variable indices of water compartment destination [size: _nLatConnections]
        /// </summary>
        int[] _iLatToWater;
        /// <summary>
        /// state variable indices of water compartment source      [size: _nLatConnections]
        /// </summary>
        int[] _iLatFromHRU;
        /// <summary>
        /// state variable indices of water compartment destination [size: _nLatConnections]
        /// </summary>
        int[] _iLatToHRU;
        /// <summary>
        /// process index (q**) of connection                       [size: _nLatConnections]
        /// </summary>
        int[] _latqss_indices;

        /// <summary>
        /// number of water storage compartments which may contain constituent
        /// </summary>
        int _nWaterCompartments;
        /// <summary>
        /// state variable indices of water storage compartments which may contain constituent [size: _nWaterCompartments]
        /// </summary>
        int[] _iWaterStorage;
        /// <summary>
        /// lookup table to convert global state variable index i to local water storage index ii [size: pModel::_nStateVars prior to transport variables being included]
        /// basically inverse of _iWaterStorage
        /// </summary>
        int[] _aIndexMapping;

        /// <summary>
        /// size of index mapping array [=pModel::_nStateVars prior to transport variables being included]
        /// </summary>
        int _nIndexMapping;

        /// <summary>
        /// list of recognized geochemical process names  [size: _nProcessNames]
        /// </summary>
        string[] _aProcessNames;
        /// <summary>
        /// size of process name list
        /// </summary>
        int _nProcessNames;

        /// <summary>
        /// array of geochem parameter structures [size: _nTransParams]
        /// </summary>
        GeochemParam[] _pGeochemParams;
        /// <summary>
        /// number of geochemistry paramers
        /// </summary>
        int _nGeochemParams;

        /// <summary>
        /// number of transported constituents [c=0.._nConstituents-1]
        /// </summary>
        int _nConstituents;
        /// <summary>
        /// array of pointers to constituent models [size:_nConstituents]
        /// </summary>
        ConstituentModel[] _pConstitModels;
        /// <summary>
        /// special pointer to enthalpy constituent, if present (or NULL if not)
        /// </summary>
        EnthalpyModel[] _pEnthalpyModel;

        public TransportModel(Model model)
        {
            ArgumentNullException.ThrowIfNull(model);
            _model = model;
        }

        internal double GetConcentration(int k, int i)
        {
            throw new NotImplementedException();
        }

        internal string GetConstituentLongName(int layerIndex)
        {
            throw new NotImplementedException();
        }

        internal string GetConstituentTypeName2(int layerIndex)
        {
            throw new NotImplementedException();
        }

        internal void IncrementCumulInput(Options options, TimeStruct tt)
        {
            throw new NotImplementedException();
        }

        internal void IncrementCumulOutput(Options options)
        {
            throw new NotImplementedException();
        }

        private void m_to_cj(int m, ref int c, ref int j)
        {
            if((m < 0) || (m > (_nConstituents * _nWaterCompartments)))
            {
                throw new ArgumentException("Invalid layer index", nameof(m));
            }
            j = m % _nWaterCompartments;
            c = (m - j) / _nWaterCompartments;
        }




    }

}
