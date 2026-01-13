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
    /// coordinates transport simulation for enthalpy
    /// </summary>
    public class EnthalpyModel : ConstituentModel
    {
        /// <summary>
        /// recent time history of reach source term [MJ/m3/d] [size: nSubBasins x nMinhist(p)]
        /// </summary>
        double[,] _aEnthalpySource;
        /// <summary>
        /// array of beta terms for reach energy exchange [1/d] [size: nSubBasins]
        /// </summary>
        double[] _aEnthalpyBeta;

        /// <summary>
        /// recent time history of in-catchment source term [MJ/m3/d] [size: nSubBasins x nMlathist(p)]
        /// </summary>
        double[,] _aEnthalpySource2;
        /// <summary>
        /// array of a terms for in-catchment energy exchange [1/d] [size: nSubBasins]
        /// </summary>
        double[] _aInCatch_a;
        /// <summary>
        /// array of b terms for in-catchment energy exchange [1/d] [size: nSubBasins]
        /// </summary>
        double[] _aInCatch_b;
        /// <summary>
        /// bed heat transfer coefficient [MJ/m2/d/K] [size: nSubBasins]
        /// </summary>
        double[] _aKbed;

        /// <summary>
        /// model soil layer corresponding to hyporheic mixing layer (default=2)
        /// </summary>
        int _mHyporheic;
        /// <summary>
        /// minimum residence time [d] (<1 dt) in each stream reach [size: nSubBasins]
        /// </summary>
        double[] _aMinResTime;

        /// <summary>
        /// array of riverbed temperatures (*state variable*) [C] [size: nSubBasins]
        /// </summary>
        double[] _aBedTemp;

        /// <summary>
        /// time-lagged average reach water temperature [C] [size: nSubBasins]
        /// </summary>
        double[] _aTave_reach;
        /// <summary>
        /// array of steady state target temperatures in each basin [C] [size: nSubBasins]
        /// </summary>
        double[] _aSS_temperature;

        /// <summary>
        /// Output StreamReachEnergyBalances.csv
        /// </summary>
        TextWriter _STREAMOUT;
        /// <summary>
        /// Output LakeEnergyBalances.csv
        /// </summary>
        TextWriter _LAKEOUT;

        public EnthalpyModel(Model model, TransportModel transportModel, string name, ConstitType type, bool isPassive, int constitIndex) : base(model, transportModel, name, type, isPassive, constitIndex)
        {
        }
    }
}
