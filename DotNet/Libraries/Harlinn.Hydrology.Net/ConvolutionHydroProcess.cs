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


        void GenerateUnitHydrograph(HydroUnit hydroUnit, Options options, double[] aUnitHydro, int[] aInterval, int N)
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
            throw new InvalidOperationException("GenerateUnitHydrograph: negative or zero duration of unit hydrograph (bad GR4J_x4, or GAMMA_SHAPE/GAMMA_SCALE)");

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

    }
}
