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
using static Harlinn.Hydrology.Constants;
using static Harlinn.Mathematics.Net.Common;
using static System.Math;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Calculates the loss of water from soil/groundwater to surface water
    /// </summary>
    public class ConvolutionHydroProcess : HydroProcess
    {
        const int MAX_CONVOL_STORES = 50;

        static readonly IReadOnlyList<ParameterInfo> _gr4jParameters = [new ParameterInfo("GR4J_X4", ClassType.CLASS_LANDUSE)];
        static readonly IReadOnlyList<ParameterInfo> _gammaParameters = [new ParameterInfo("GAMMA_SHAPE", ClassType.CLASS_LANDUSE), new ParameterInfo("GAMMA_SCALE", ClassType.CLASS_LANDUSE)];
        static readonly IReadOnlyList<ParameterInfo> _gamma2Parameters = [new ParameterInfo("GAMMA_SHAPE2", ClassType.CLASS_LANDUSE), new ParameterInfo("GAMMA_SCALE2", ClassType.CLASS_LANDUSE)];


        /// <summary>
        /// True if smart algorithm is used to reduce stores
        /// </summary>
        static bool _smartmode;
        /// <summary>
        /// Number of convolution stores used in smart mode
        /// </summary>
        static int _nStores;

        /// <summary>
        /// Model of convolution selected
        /// </summary>
        ConvolutionType _type;

        /// <summary>
        /// state variable index of outflow target
        /// </summary>
        int _iTarget;


        public ConvolutionHydroProcess(Model model, ConvolutionType type,
                               int to_index,
                               int conv_index)
            : base(model, HydroProcessType.CONVOLVE)
        {
            _type = type;
            _iTarget = to_index;

            if (!_smartmode) 
            { 
                _nStores = MAX_CONVOL_STORES; 
            }

            int N = _nStores; 

            DynamicSpecifyConnections(2 * N);
            for (int i = 0; i < N; i++)
            {
                //for applying convolution
                FromIndices[i] = model.GetStateVarIndex(SVType.CONV_STOR, i + conv_index * N);
                ToIndices[i] = _iTarget;

                //for shifting storage history
                if (i < N - 1)
                {
                    FromIndices[N + i] = model.GetStateVarIndex(SVType.CONV_STOR, i + conv_index * N);
                    ToIndices[N + i] = model.GetStateVarIndex(SVType.CONV_STOR, i + 1 + conv_index * N);
                }
            }
            //updating total convolution storage
            FromIndices[2 * N - 1] = model.GetStateVarIndex(SVType.CONVOLUTION, conv_index);
            ToIndices[2 * N - 1] = model.GetStateVarIndex(SVType.CONVOLUTION, conv_index);
        }

        double LocalCumulDist(double t, HydroUnit hydroUnit)
        {
            if (_type== ConvolutionType.CONVOL_GR4J_1)
            {
                double x4= hydroUnit.GetSurfaceProps().GR4J_x4;
                return Math.Min(Math.Pow(t/x4,2.5),1.0);
            }
            else if (_type== ConvolutionType.CONVOL_GR4J_2)
            {
                double x4= hydroUnit.GetSurfaceProps().GR4J_x4;
                if(t/x4<1.0)
                {
                    return 0.5*Math.Pow(t/x4,2.5);
                }
                else if (t/x4<2.0)
                {
                    return 1.0-0.5*Math.Pow(2-t/x4,2.5);
                }
                else
                {
                    return 1.0;
                }
            }
            else if(_type== ConvolutionType.CONVOL_GAMMA)
            {
                double beta = hydroUnit.GetSurfaceProps().gamma_scale;
                double alpha = hydroUnit.GetSurfaceProps().gamma_shape;
                return GammaCumDist(t,alpha,beta);
            }
            else if(_type== ConvolutionType.CONVOL_GAMMA_2)
            {
                double beta = hydroUnit.GetSurfaceProps().gamma_scale2;
                double alpha = hydroUnit.GetSurfaceProps().gamma_shape2;
                return GammaCumDist(t,alpha,beta);
            }
            return 1.0;
        }


        void GenerateUnitHydrograph(HydroUnit hydroUnit, Options options, Span<double> aUnitHydro, Span<int> aInterval, out int N)
        {
            double tstep = options.timestep;
            double max_time = 0;

            if (_type == ConvolutionType.CONVOL_GR4J_1)
            {
                double x4 = hydroUnit.GetSurfaceProps().GR4J_x4;
                max_time = x4;
            }
            else if (_type == ConvolutionType.CONVOL_GR4J_2)
            {
                double x4 = hydroUnit.GetSurfaceProps().GR4J_x4;
                max_time = 2 * x4;
            }
            else if (_type == ConvolutionType.CONVOL_GAMMA)
            {
                double alpha = hydroUnit.GetSurfaceProps().gamma_shape;
                double beta = hydroUnit.GetSurfaceProps().gamma_scale;
                max_time = 4.5 * Pow(alpha, 0.6) / beta;
            }
            else if (_type == ConvolutionType.CONVOL_GAMMA_2)
            {
                double alpha = hydroUnit.GetSurfaceProps().gamma_shape2;
                double beta = hydroUnit.GetSurfaceProps().gamma_scale2;
                max_time = 4.5 * Pow(alpha, 0.6) / beta;
            }
            else
            {
                throw new InvalidOperationException("GenerateUnitHydrograph: negative or zero duration of unit hydrograph (bad GR4J_x4, or GAMMA_SHAPE/GAMMA_SCALE)");
            }

            int NN;

            double sum = 0; ;
            if (!_smartmode)
            {
                max_time = Min(MAX_CONVOL_STORES * tstep, max_time); //must truncate
                N = (int)(Ceiling(max_time / tstep));
                if (N == 0) { N = 1; }
                NN = N;
                for (int n = 0; n < N; n++)
                {
                    aUnitHydro[n] = LocalCumulDist((n + 1) * tstep, hydroUnit) - sum;
                    sum += aUnitHydro[n];

                    aInterval[n] = 1;
                }
            }
            else
            {
                // smart allocation - simplifies history storage
                N = _nStores;
                NN = (int)(Ceiling(max_time / tstep));

                int i = 0;
                int nlast = -1;
                double Flast = 0.0;
                double Fn;

                for (int n = 0; n < NN; n++)
                {
                    Fn = LocalCumulDist((n + 1) * tstep, hydroUnit);
                    if ((i == 0) && (n > 0) && (Fn > 1.0 / _nStores / 4.0))
                    { //handles lag effect
                        aInterval[i] = (n - nlast - 1);
                        aUnitHydro[i] = 0;
                        i++;
                        aInterval[i] = 1;
                        aUnitHydro[i] = Fn - Flast;
                        Flast = Fn;
                        nlast = n;
                        i++;
                    }
                    else if ((Fn >= Flast + 1.0 / _nStores) || (Fn > 0.99))
                    { //CDF has increased enough to start new interval
                        aInterval[i] = (n - nlast);
                        aUnitHydro[i] = (Fn - Flast);
                        sum += aUnitHydro[i];
                        Flast = Fn;
                        nlast = n;
                        i++;
                    }
                }
                for (int ii = i; ii < N; ii++)
                {
                    aUnitHydro[ii] = 0.0;
                    aInterval[ii] = 1;
                }
                N = i;
            }
        }

        public override IReadOnlyList<ParameterInfo> GetParticipatingParamList()
        {
            if ((_type == ConvolutionType.CONVOL_GR4J_1) || (_type == ConvolutionType.CONVOL_GR4J_2))
            {
                return _gr4jParameters;
            }
            else if (_type == ConvolutionType.CONVOL_GAMMA)
            {
                return _gammaParameters;
            }
            else if (_type == ConvolutionType.CONVOL_GAMMA_2)
            {
                return _gamma2Parameters;
            }
            else
            {
                throw new InvalidOperationException("ConvolutionHydroProcess.GetParticipatingParamList: invalid convolution type");
            }
        }

        public static IReadOnlyList<StateVariableInfo> GetParticipatingStateVarList(ConvolutionType absttype, int conv_index)
        {
            var result = new List<StateVariableInfo>(_nStores+1);

            for (int i = 0; i < _nStores; i++)
            {
                result.Add(new StateVariableInfo(SVType.CONV_STOR, (conv_index * _nStores) + i));
            }
            result.Add(new StateVariableInfo(SVType.CONVOLUTION, conv_index) );
            return result;
        }

        public override void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            int i;
            double TS_old;
            double tstep = options.timestep;
            Span<double> S = stackalloc double[MAX_CONVOL_STORES];
            Span<double> aUnitHydro = stackalloc double[MAX_CONVOL_STORES];
            Span<int> aInterval = stackalloc int[MAX_CONVOL_STORES];

            int N = 0;
            GenerateUnitHydrograph(hydroUnit, options, aUnitHydro, aInterval, out N);

            // Calculate S[0] as change in convolution total storage
            // total storage after water added to convol stores earlier in process list
            TS_old = stateVars[FromIndices[2 * _nStores - 1]]; 
            double sum = 0.0;
            int NN = 0;
            for (i = 0; i < N; i++)
            {
                S[i] = stateVars[FromIndices[i]];
                sum += S[i];
                NN += aInterval[i];
            }
            // amount of water added this time step to convol stores
            S[0] += (TS_old - sum); 

            //outflow from convolution storage
            double orig_storage;
            double sumrem;
            if (!_smartmode)
            {
                //usually, we just would do Q=sum UH(n)*R(t-n), but we store depleted R rather than original inputs
                sumrem = 1.0;
                for (i = 0; i < N; i++)
                {
                    if (sumrem < REAL_SMALL) 
                    { 
                        orig_storage = 0.0; 
                    }
                    else 
                    { 
                        orig_storage = S[i] / sumrem; 
                    }
                    rates[i] = aUnitHydro[i] * orig_storage / tstep; //water released to target store from internal store
                    S[i] -= rates[i] * tstep;
                    sumrem -= aUnitHydro[i];
                }//sumrem should ==0 at end, so should S[N-1]
                 //challengee here - original storage is not necessarily S/sum_0^i-1 UH because of partial shifts of mass
            }
            if (_smartmode)
            {
                int sumn = 0;
                sumrem = 1.0;
                i = 0;
                double rel;
                for (int n = 0; n < NN; n++)
                {
                    if (i < _nStores)
                    {
                        if (sumrem < REAL_SMALL) 
                        { 
                            orig_storage = 0.0; 
                        }
                        else 
                        { 
                            orig_storage = S[i] / aInterval[i]; 
                        }
                        rel = aUnitHydro[i] * orig_storage / tstep;
                        
                        //water released to target store from internal store
                        rates[i] += rel;
                        S[i] -= rel * tstep;

                        sumrem -= aUnitHydro[i] / aInterval[i];
                        if ((n + 1 - sumn) >= aInterval[i])
                        {
                            sumn = n + 1;
                            i++;
                        }
                    }
                    else
                    {
                        rates[i] = S[i] / tstep;
                        S[i] = 0;
                    }
                }
            }

            // time shift convolution history
            
            for (i = N - 2; i >= 0; i--)
            {
                double move = S[i] / aInterval[i];
                rates[_nStores + i] = move / tstep;
                S[i] -= move;
                S[i + 1] += move;
            }

            // Update total convolution storage:
            double TS_new = 0;
            for (i = 1; i < N; i++) 
            { 
                TS_new += S[i]; 
            }
            rates[2 * _nStores - 1] = (TS_new - TS_old) / tstep;
        }


    }
}
