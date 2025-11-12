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
    /// Demand optimization
    /// </summary>
    public class DemandOptimizer
    {
        Model _pModel;

        /// <summary>
        /// total number of decision variables considered
        /// </summary>
        int _nDecisionVars;
        /// <summary>
        /// array of decision variable structures [size:_nDecisionVars]
        /// </summary>
        DecisionVar[] _pDecisionVars;

        /// <summary>
        /// total number of workflow variables considered
        /// </summary>
        int _nWorkflowVars;
        /// <summary>
        /// array of workflow variables [size: _nWorkflowVars]
        /// </summary>
        WorkflowVar[] _pWorkflowVars;

        /// <summary>
        /// number of user-defined enforced constraints/goals in management model
        /// </summary>
        int _nGoals;
        /// <summary>
        /// array of pointers to user-defined enforced constraints/goals in management model
        /// </summary>
        ManagementGoal[] _pGoals;

        /// <summary>
        /// number of enabled subbasins in model
        /// </summary>
        int _nEnabledSubBasins;
        /// <summary>
        /// local index of enabled subbasins (0:_nEnabledSubBasins) [size: _nSubBasins]
        /// </summary>
        int[] _aSBIndices;

        /// <summary>
        /// array of booleans to determine whether reservoir stage-discharge curve is overridden [size: _nSubBasins]
        /// </summary>
        bool[] _aDisableSDCurve;

        /// <summary>
        /// local storage of number of enabled lakes/reservoirs
        /// </summary>
        int _nReservoirs;
        /// <summary>
        /// storage of enabled reservoir indices (0:_nReservoirs or DOESNT_EXIST) [size:_nSubBasins]
        /// </summary>
        int[] _aResIndices;

        /// <summary>
        /// array of pointers to water demand instances
        /// </summary>
        Demand[] _pDemands;
        /// <summary>
        /// local storage of number of demand locations
        /// </summary>
        int _nDemands;
        /// <summary>
        /// total number of demands with return flows (<=_nDemands)
        /// </summary>
        int _nReturns;

        /// <summary>
        /// array of delivered water for each water demand [m3/s] [size: _nDemands]
        /// </summary>
        double[] _aDelivery;
        /// <summary>
        /// array of cumulative deliveries of demand since _aCumDivDate of this year [m3] [size: _nDemands]
        /// </summary>
        double[] _aCumDelivery;

        /// <summary>
        /// demand indices (d) upstream (inclusive) of subbasin p [size: nSBs][size: _aUpCount] (only restricted demands)
        /// </summary>
        int[,] _aUpstreamDemands;
        /// <summary>
        /// number of demands upstream (inclusive) of subbasin p [size: nSBs]
        /// </summary>
        int[] _aUpCount;

        /// <summary>
        /// number of demand groups
        /// </summary>
        int _nDemandGroups;
        /// <summary>
        /// array of demand groups
        /// </summary>
        DemandGroup[] _pDemandGroups;

        /// <summary>
        /// number of *active* environmental flow goals
        /// </summary>
        int _nEnviroFlowGoals;
        /// <summary>
        /// array of slack variable values [size: _nSlackVars]
        /// </summary>
        double[] _aSlackValues;
        /// <summary>
        /// number of slack variables
        /// </summary>
        int _nSlackVars;

        /// <summary>
        /// number of user-specified decision variables
        /// </summary>
        int _nUserDecisionVars;
        /// <summary>
        /// array of user-specified decision vars [size: _nUserDecisionVars] (overlaps content of _pDecisionVars)
        /// </summary>
        DecisionVar[] _pUserDecisionVars;

        /// <summary>
        /// number of user-specified named constants
        /// </summary>
        int _nUserConstants;
        /// <summary>
        /// array of names of user-specified constants
        /// </summary>
        string[] _aUserConstNames;
        /// <summary>
        /// array of values of user-specified constants
        /// </summary>
        double[] _aUserConstants;

        /// <summary>
        /// number of user variable time series
        /// </summary>
        int _nUserTimeSeries;
        /// <summary>
        /// array of pointers to user variable time series
        /// </summary>
        TimeSeries[] _pUserTimeSeries;

        /// <summary>
        /// number of user variable lookup tables
        /// </summary>
        int _nUserLookupTables;
        /// <summary>
        /// array of pointers to user variable lookup tables
        /// </summary>
        LookupTable[] _pUserLookupTables;

        /// <summary>
        /// size of flow/demand/stage history that needs to be stored (in time steps) (from :LookbackDuration)
        /// </summary>
        int _nHistoryItems;
        /// <summary>
        /// history of subbasin discharge [size: _nEnabledSBs * _nHistoryItems]
        /// </summary>
        double[,] _aQhist;
        /// <summary>
        /// history of actual delivery [size: _nEnabledSBs * _nHistoryItems]
        /// </summary>
        double[,] _aDhist;
        /// <summary>
        /// history of reservoir inflows [size: _nEnabledSBs * _nHistoryItems]
        /// </summary>
        double[,] _aIhist;
        /// <summary>
        /// history of actual reservoir stages  (or 0 for non-reservoir basins) [size: _nEnabledSBs * _nHistoryItems]
        /// </summary>
        double[,] _ahhist;

        /// <summary>
        /// number of residuals of solution (equal to lp_lib::nRows)
        /// </summary>
        int _nSolverResiduals;
        /// <summary>
        /// vector of residuals of solution [size: _nSolverResiduals]
        /// </summary>
        double[] _aSolverResiduals;
        /// <summary>
        /// vector of solver row names [size: _nSolverResiduals]
        /// </summary>
        string[] _aSolverRowNames;

        /// <summary>
        /// for ManagementOptimization.csv
        /// </summary>
        TextWriter _MANOPT;
        /// <summary>
        /// for GoalSatisfaction.csv
        /// </summary>
        TextWriter _GOALSAT;
        /// <summary>
        /// ofstream for OptimizationResidual.csv
        /// </summary>
        TextWriter _RESID;

        /// <summary>
        /// =1 if debug info is to be printed to screen, =2 if LP matrix also printed (full debug), 0 for nothing
        /// </summary>
        int _do_debug_level;
    }
}
