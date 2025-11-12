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
namespace Harlinn.Hydrology
{

    /// <summary>
    /// EnKF model ensemble run
    /// </summary>
    public class EnKFEnsemble : Ensemble
    {
        /// <summary>
        /// number of members in ensemble (=1/2 of _nMembers, because pre/post runs are separate)
        /// </summary>
        int _nEnKFMembers;

        /// <summary>
        /// run mode (spinup, closed-loop, or open-loop)
        /// </summary>
        EnKFMode _EnKF_mode;

        /// <summary>
        /// current array of state vectors, X [size: _nEnKFMembers x_nStateVars]
        /// </summary>
        double[,] _state_matrix;
        /// <summary>
        /// total number of assimilated state variables
        /// </summary>
        int _nStateVars;
        /// <summary>
        /// array of state names
        /// </summary>
        string[] _state_names;

        /// <summary>
        /// matrix of perturbed observations, D [size: _nEnKFMembers x _nObsDatapoints]
        /// </summary>
        double[,] _obs_matrix;
        /// <summary>
        /// matrix of simulated values corresponding to observations, HA [size: _nEnKFMembers x _nObsDatapoints]
        /// </summary>
        double[,] _output_matrix;
        /// <summary>
        /// matrix of observational noise [size: _nEnKFMembers x _nObsDatapoints]
        /// </summary>
        double[,] _noise_matrix;
        /// <summary>
        /// number of valid datapoints available for assimilation
        /// </summary>
        int _nObsDatapoints;

        /// <summary>
        /// array of observation perturbation data [size _nObsPerturbations]
        /// </summary>
        ObsPerturb[] _pObsPerturbations;
        /// <summary>
        /// number of observational perturbations. If observation does not have perturbation, it is assumed "perfect" data
        /// </summary>
        int _nObsPerturbations;

        /// <summary>
        /// assimilated state variable [size: _nAssimStates]
        /// </summary>
        SVType[] _aAssimStates;
        /// <summary>
        /// layer of assimilated state variable [size: _nAssimStates]
        /// </summary>
        int[] _aAssimLayers;
        /// <summary>
        /// index (kk) of HRU group or SubBasin group  [size: _nAssimStates]
        /// </summary>
        int[] _aAssimGroupID;
        /// <summary>
        /// number of assimilated state variable types (!= number of total state vars)
        /// </summary>
        int _nAssimStates;

        /// <summary>
        /// number of data points back in time to be used in assimilation (=1 for classic EnKF, more for variational methods)
        /// </summary>
        int _window_size;
        /// <summary>
        /// number of timesteps in hindcast period (prior to t0)
        /// </summary>
        int _nTimeSteps;

        /// <summary>
        /// run name of closed loop or open loop solution files (e.g., run1_solution.rvc)
        /// </summary>
        string _warm_runname;

        /// <summary>
        /// name of extra-data .rvt file for ensemble member-specific time series
        /// </summary>
        string _extra_rvt;
        /// <summary>
        /// original rvc filename (full path)
        /// </summary>
        string _orig_rvc_file;

        /// <summary>
        /// indices of CModel::pObsTS array corresponding to assimilation time series [size:_nObs]
        /// </summary>
        int[] _aObsIndices;
        /// <summary>
        /// number of time series to be assimilated
        /// </summary>
        int _nObs;

        /// <summary>
        /// output 
        /// </summary>
        TextWriter _ENKFOUT;
    }
}
