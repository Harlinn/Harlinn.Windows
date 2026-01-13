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
using System;
using System.IO;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Coordinates transport simulation for specific constituent
    /// </summary>
    public class ConstituentModel
    {
        Model _pModel;
        TransportModel _pTransModel;

        /// <summary>
        /// constituent name (e.g., "Nitrogen")
        /// </summary>
        string _name;
        /// <summary>
        /// master constituent index, c,  of this constituent
        /// </summary>
        int _constit_index;
        /// <summary>
        /// AQUEOUS [mg], ENTHALPY [MJ], ISOTOPE [mg/mg] or TRACER [-]
        /// </summary>
        ConstitType _type;
        /// <summary>
        /// doesn't transport via advection (default: false)
        /// </summary>
        bool _is_passive;

        /// <summary>
        /// true if lateral mass/energy transfer handled within routing convolution (default: false)
        /// </summary>
        bool _lateral_via_convol;

        // Routing/state var storage

        /// <summary>
        /// size of upstream loading history in each basin [size: nSubBasins]
        /// </summary>
        int[] _nMinHist;
        /// <summary>
        /// array used for storing routing upstream loading history [mg/d] or [MJ/d] [size: nSubBasins x _nMinHist[p]]
        /// </summary>
        double[,] _aMinHist;
        /// <summary>
        /// size of lateral loading history in each basin [size: nSubBasins]
        /// </summary>
        int[] _nMlatHist;
        /// <summary>
        /// array used for storing routing lateral loading history [mg/d] or [MJ/d] [size: nSubBasins  x _nMlatHist[p]]
        /// </summary>
        double[,] _aMlatHist;
        /// <summary>
        /// array storing current mass flow at points along channel [mg/d] or [MJ/d] [size: nSubBasins x _nSegments(p)]
        /// </summary>
        double[,] _aMout;
        /// <summary>
        /// array used for storing mass outflow from channel at start of timestep [mg/d] or [MJ/d] [size: nSubBasins ]
        /// </summary>
        double[] _aMout_last;
        /// <summary>
        /// array storing mass/energy outflow from start of timestep [size: nSubBasins]
        /// </summary>
        double[] _aMlat_last;
        /// <summary>
        /// local contribution to current subbasin mass/energy outflow [mg/d] or [MJ/d] [size: nSubBasins] (just from in-catchment mass/energy routing)
        /// </summary>
        double[] _aMlocal;
        /// <summary>
        /// last local contribution [mg/d] or [MJ/d] [size: nSubBasins]
        /// </summary>
        double[] _aMlocLast;

        /// <summary>
        /// array used for storing reservoir masses [mg] or enthalpy [MJ] [size: nSubBasins]
        /// </summary>
        double[] _aMres;
        /// <summary>
        /// array storing reservoir mass [mg] or enthalpy [MJ] at start of timestep [size: nSubBasins]
        /// </summary>
        double[] _aMres_last;
        /// <summary>
        /// array storing reservoir sediment mass [mg] [size: nSubBasins]
        /// </summary>
        double[] _aMsed;
        /// <summary>
        /// array storing reservoir sediment mass [mg] at start of timestep [size: nSubBasins]
        /// </summary>
        double[] _aMsed_last;
        /// <summary>
        /// array storing reservoir mass outflow [mg/d] or heat loss [MJ/d] [size: nSubBasins]
        /// </summary>
        double[] _aMout_res;
        /// <summary>
        /// array storing reservoir mass outflow [mg/d] or enthalpy outflow  [MJ/d] at start of timestep  [size: nSubBasins]
        /// </summary>
        double[] _aMout_res_last;
        /// <summary>
        /// array storing reservoir rain inputs [mg/d] or enthalpy input [MJ/d] [size: nSubBasins]
        /// </summary>
        double[] _aMresRain;

        // Mass balance tracking variables

        /// <summary>
        /// array storing channel storage [mg] or [MJ] [size: nSubBasins]
        /// </summary>
        double[] _channel_storage;
        /// <summary>
        /// array storing rivulet storage [mg] or [MJ] [size: nSubBasins]
        /// </summary>
        double[] _rivulet_storage;
        /// <summary>
        /// cumulative mass [mg] or enthalpy [MJ] added to system
        /// </summary>
        double _cumul_input;
        /// <summary>
        /// cumulative mass [mg] or enthalpy [MJ] lost from system
        /// </summary>
        double _cumul_output;
        /// <summary>
        /// initial mass [mg] or enthalpy [MJ] in system
        /// </summary>
        double _initial_mass;

        // Source information


        /// <summary>
        /// array of constituent sources [size: nSources]
        /// </summary>
        ConstitSource[] _pSources;
        /// <summary>
        /// number of constituent sources
        /// </summary>
        int _nSources;

        /// <summary>
        /// lookup table to convert (global) water storage index to corresponding source, if any [size: nStateVariables][size: nHRUs]
        /// </summary>
        int[][] _aSourceIndices;

        /// <summary>
        /// number of specified flow concentration/temperature time series [mg/L]
        /// </summary>
        int _nSpecFlowConcs;
        /// <summary>
        /// array of time series of specified flow concentration/temperatures - TS tag corresponds to SBID
        /// </summary>
        TimeSeries[] _pSpecFlowConcs;
        /// <summary>
        /// number of specified mass/energy loading time series [kg/d]
        /// </summary>
        int _nMassLoadingTS;
        /// <summary>
        /// array of time series of mass loadings [kg/d] - TS tag corresponds to SBID
        /// </summary>
        TimeSeries[] _pMassLoadingTS;

        /// <summary>
        /// output for Concentrations.csv/Temperatures.csv
        /// </summary>
        TextWriter _OUTPUT;
        /// <summary>
        /// output for Pollutograph.csv/StreamTemperatures.csv
        /// </summary>
        TextWriter _POLLUT;
        /// <summary>
        /// output for MassLoadings.csv
        /// </summary>
        TextWriter _LOADING;
        /// <summary>
        /// NetCDF id for Concentrations.nc/Temperatures.nc
        /// </summary>
        int _CONC_ncid;
        /// <summary>
        /// NetCDF id for Pollutograph.nc/StreamTemperatures.nc
        /// </summary>
        int _POLLUT_ncid;
        /// <summary>
        /// NetCDF id for MassLoadings.nc
        /// </summary>
        int _LOADING_ncid;


        public ConstituentModel(Model model, TransportModel transportModel, string name, ConstitType type, bool isPassive, int constitIndex)
        {
            _constit_index = constitIndex;
            _pModel = model;
            _pTransModel = transportModel;
            _name = name;
            _type = type;
            _is_passive = false;
            _CONC_ncid = -9;
            _POLLUT_ncid = -9;
            _LOADING_ncid = -9;
        }

        public ConstitType Type => _type;

        public string Name => _name;

        public bool IsPassive => _is_passive;

        public double GetAdvectionCorrection(HydroUnit hru, int iFromWater, int iToWater, double Cs)
        {
            return 1.0;
        }

        public double GetTotalRivuletConstituentStorage()
        {
            double sum = 0.0;
            for (int p = 0; p < _pModel.GetNumSubBasins(); p++)
            {
                sum += _rivulet_storage[p]; //[mg] or [MJ]
            }
            return sum; //[mg] or [MJ]
        }



    }


}
