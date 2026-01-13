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
using static Harlinn.Mathematics.Net.Common;
using static System.Math;


namespace Harlinn.Hydrology
{
    /// <summary>
    /// Calculates the abstraction of rainfall/snowmelt (ponded water) to depression storage
    /// </summary>
    public class AbstractionHydroProcess : HydroProcess
    {
        static readonly IReadOnlyList<ParameterInfo> _percentageParameters = [new ParameterInfo("ABST_PERCENT", ClassType.CLASS_LANDUSE)];
        static readonly IReadOnlyList<ParameterInfo> _fillParameters = [new ParameterInfo("DEP_MAX", ClassType.CLASS_LANDUSE)];
        static readonly IReadOnlyList<ParameterInfo> _scsParameters = [new ParameterInfo("SCS_CN", ClassType.CLASS_LANDUSE), new ParameterInfo("SCS_IA_FRACTION", ClassType.CLASS_LANDUSE)];
        static readonly IReadOnlyList<ParameterInfo> _pdmrofParameters = [new ParameterInfo("PDMROF_B", ClassType.CLASS_LANDUSE), new ParameterInfo("DEP_MAX", ClassType.CLASS_LANDUSE)];
        static readonly IReadOnlyList<ParameterInfo> _uwfsParameters = [new ParameterInfo("MAX_DEP_AREA_FRAC", ClassType.CLASS_LANDUSE), new ParameterInfo("DEP_MAX", ClassType.CLASS_LANDUSE), new ParameterInfo("UWFS_B", ClassType.CLASS_LANDUSE), new ParameterInfo("UWFS_BETAMIN", ClassType.CLASS_LANDUSE)];

        static readonly IReadOnlyList<StateVariableInfo> pdmrofStateVariables = new StateVariableInfo[]
        {
            new StateVariableInfo(SVType.PONDED_WATER),
            new StateVariableInfo(SVType.DEPRESSION),
            new StateVariableInfo(SVType.SURFACE_WATER)
        };

        static readonly IReadOnlyList<StateVariableInfo> uwfsStateVariables = new StateVariableInfo[]
        {
            new StateVariableInfo(SVType.PONDED_WATER),
            new StateVariableInfo(SVType.DEPRESSION),
            new StateVariableInfo(SVType.SURFACE_WATER),
            new StateVariableInfo(SVType.MIN_DEP_DEFICIT)
        };

        static readonly IReadOnlyList<StateVariableInfo> defaultStateVariables = new StateVariableInfo[]
        {
            new StateVariableInfo(SVType.PONDED_WATER),
            new StateVariableInfo(SVType.DEPRESSION)
        };


        /// <summary>
        /// Model of abstraction selected
        /// </summary>
        AbstractionType _type; 
        
        public AbstractionHydroProcess(Model model, AbstractionType absttype)
            :base(model, HydroProcessType.ABSTRACTION)
        {
            _type = absttype;

            if ((_type == AbstractionType.ABST_PERCENTAGE) || (_type == AbstractionType.ABST_FILL) || (_type == AbstractionType.ABST_SCS))
            {
                DynamicSpecifyConnections(1);
                //abstraction (ponded-->depression)
                FromIndices[0] = model.GetStateVarIndex(SVType.PONDED_WATER);
                ToIndices[0] = model.GetStateVarIndex(SVType.DEPRESSION);
            }
            else if (_type == AbstractionType.ABST_PDMROF)
            {
                DynamicSpecifyConnections(2);
                //abstraction (ponded-->depression)
                FromIndices[0] = model.GetStateVarIndex(SVType.PONDED_WATER);
                ToIndices[0] = model.GetStateVarIndex(SVType.DEPRESSION);
                //runoff (ponded-->surface water)
                FromIndices[1] = model.GetStateVarIndex(SVType.PONDED_WATER);
                ToIndices[1] = model.GetStateVarIndex(SVType.SURFACE_WATER);
            }
            else if (_type == AbstractionType.ABST_UWFS)
            {
                DynamicSpecifyConnections(3);
                //abstraction (ponded-->depression)
                FromIndices[0] = model.GetStateVarIndex(SVType.PONDED_WATER);
                ToIndices[0] = model.GetStateVarIndex(SVType.DEPRESSION);
                //runoff (ponded-->surface water)
                FromIndices[1] = model.GetStateVarIndex(SVType.PONDED_WATER);
                ToIndices[1] = model.GetStateVarIndex(SVType.SURFACE_WATER);
                //adjust minimum deficit
                FromIndices[2] = model.GetStateVarIndex(SVType.MIN_DEP_DEFICIT);
                ToIndices[2] = model.GetStateVarIndex(SVType.MIN_DEP_DEFICIT);
            }
        }

        

        public override IReadOnlyList<ParameterInfo> GetParticipatingParamList( )
        {
            if (_type == AbstractionType.ABST_PERCENTAGE)
            {
                return _percentageParameters;
            }
            else if (_type == AbstractionType.ABST_FILL)
            {
                return _fillParameters;
            }
            else if (_type == AbstractionType.ABST_SCS)
            {
                return _scsParameters;
            }
            else if (_type == AbstractionType.ABST_PDMROF)
            {
                return _pdmrofParameters;
            }
            else if (_type == AbstractionType.ABST_UWFS)
            {
                return _uwfsParameters;
            }
            else
            {
                throw new InvalidOperationException("AbstractionHydroProcess.GetParticipatingParamList: undefined abstraction algorithm");
            }
        }


        


        public static IReadOnlyList<StateVariableInfo> GetParticipatingStateVarList(AbstractionType absttype)
        {
            if (absttype == AbstractionType.ABST_PDMROF)
            {
                return pdmrofStateVariables;
            }
            else if (absttype == AbstractionType.ABST_UWFS)
            {
                return uwfsStateVariables;
            }
            else
            {
                return defaultStateVariables;
            }
        }

        public override void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            double ponded = stateVars[FromIndices[0]];
            double depression = stateVars[ToIndices[0]];

            if (_type == AbstractionType.ABST_PERCENTAGE)
            {
                rates[0] = hydroUnit.GetSurfaceProps().abst_percent * ponded / options.timestep;
            }
            else if (_type == AbstractionType.ABST_FILL)
            {
                // fills up storage, then stops
                // [mm] available space left in depression storage
                double dep_space;

                dep_space = Max(hydroUnit.GetSurfaceProps().dep_max - depression, 0.0);

                rates[0] = Min(dep_space, Max(ponded, 0.0)) / options.timestep;
            }
            else if (_type == AbstractionType.ABST_SCS)
            {
                double S, CN, TR, Ia;

                int condition = 2;

                // S should really be calculated as auxilliary land surface param
                TR = hydroUnit.GetForcingFunctions().precip_5day / MM_PER_INCH;
                CN = hydroUnit.GetSurfaceProps().SCS_CN;

                // correct curve number for antecedent moisture conditions
                if ((tt.month > 4) && (tt.month < 9))
                {
                    //growing season?? (northern hemisphere)
                    //if (pHRU->GetForcingFunctions()->is_growing_season){
                    if (TR < 1.4) { condition = 1; }
                    else if (TR > 2.1) { condition = 3; }
                }
                else
                {
                    if (TR < 0.5) { condition = 1; }
                    else if (TR > 1.1) { condition = 3; }
                }
                if (condition == 1) 
                {
                    CN = 5E-05 * Pow(CN, 3) + 0.0008 * Pow(CN, 2) + 0.4431 * CN; 
                }
                else if (condition == 3) 
                { 
                    CN = 0.0003 * Pow(CN, 3) - 0.0185 * Pow(CN, 2) + 2.1586 * CN; 
                }

                // calculate amount of runoff
                S = MM_PER_INCH * (1000 / CN - 10);
                Ia = (hydroUnit.GetSurfaceProps().SCS_Ia_fraction) * S;

                rates[0] = Max(Ia, ponded) / options.timestep;
            }
            else if (_type == AbstractionType.ABST_PDMROF)
            {
                //uses PDMROF algorithm from Mekonnen et al., Towards an improved land surface scheme for prairie landscapes, Journal of Hydrology 511, 2014
                //[-] pareto distribution parameter
                double b;
                //[mm] maximum depression storage across HRU
                double dep_max;
                //[mm] maximum local storage capacity in HRU
                double c_max;
                //[mm] critical capacity, c*
                double c_star;
                //[mm] total amount abstracted
                double abstracted; 

                dep_max = hydroUnit.GetSurfaceProps().dep_max;
                b = hydroUnit.GetSurfaceProps().PDMROF_b;

                c_max = (b + 1) * dep_max;

                c_star = c_max * (1.0 - Pow(1.0 - (depression / dep_max), 1.0 / (b + 1.0)));

                
                abstracted = dep_max * (Pow(1.0 - (c_star / c_max), b + 1.0) - Pow(1.0 - Min(c_star + ponded, c_max) / c_max, b + 1.0));
                abstracted = Min(abstracted, ponded);

                rates[0] = (abstracted) / options.timestep; 
                rates[1] = (ponded - abstracted) / options.timestep; 
            }
            else if (_type == AbstractionType.ABST_UWFS)
            {
                //[mm] total runoff amount, <O_1> (averaged over HRU)
                double runoff;
                //[mm] total "preciptiation" (averaged over HRU)
                double P = ponded;
                //[mm] change in Dmin (in wetland; not averaged over HRU)
                double deltaDmin = 0;

                double alpha = 1;
                double b = hydroUnit.GetSurfaceProps().uwfs_b;
                double beta_min = hydroUnit.GetSurfaceProps().uwfs_betamin;
                double depfrac = hydroUnit.GetSurfaceProps().max_dep_area_frac; 
                double depmax = hydroUnit.GetSurfaceProps().dep_max;
                if (depfrac == 0) 
                {
                    //no abstraction, all will run off
                    runoff = ponded; 
                } 
                else
                {
                    // mm in wetland (not averaged over HRU as depression storage is)
                    double Davg = (depmax - depression) / depfrac;
                    // Dmin [mm] if positive,=-Pf if negative
                    double Dmin = stateVars[FromIndices[2]];
                    // Fraction full
                    double Pf = 0.0;
                    // deficit distribution parameter
                    double d;
                    double beta_ave = beta_min + 1 / b;
                    double a = b / (P + 0.0001);
                    double mult = alpha / (beta_ave - 1.0 + alpha);

                    if (Dmin < 0.0)
                    { 
                        //partially full
                        Pf = -Dmin;
                    }

                    double Pstar = beta_min * P - Dmin;

                    // backcalculate d from Dmin (or Pf) and Davg

                    d = Min((1.0 - Pf) / (Davg - Dmin + 0.00001) + 0.0001, 1000.0);
                    // Calculate net runoff (in mm averaged over basin)

                    if (Pstar > 0.0)
                    {
                        runoff = mult * a * d / (a + d) * ((1 - Pf) * ((d * Pstar - 1 + Exp(-d * Pstar)) / d / d) + (1 - Pf) * (a * Pstar + 1) / a / a + (Pf) * (Pstar + 1.0 / a));
                    }
                    else
                    {
                        runoff = mult * a * d / (a + d) * (Exp(a * Pstar) / a / a);
                    }

                    if (runoff > 0.001)
                    {
                        if (Pstar > 0.0)
                        {
                            Pf = 1 - (a / (a + d) * Exp(-d * Pstar)) * (1 - Pf);
                        }
                        else
                        {
                            Pf = 1 - (a / (a + d) * (1 - Pf) + (d / (a + d) * (1 - Pf) + Pf) * (1 - Exp(a * Pstar)));
                        }
                        deltaDmin = (-Pf) - Dmin;
                        Dmin = 0;
                    }
                    else
                    {
                        deltaDmin = -Min(beta_ave * P, Dmin);
                        Pf = 0.0; 
                    }
                }

                rates[0] = (ponded - runoff) / options.timestep; 
                rates[1] = (runoff) / options.timestep; 
                rates[2] = (deltaDmin) / options.timestep; 
            }
        }

        public override void ApplyConstraints(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            //cant remove more than is there (should never be an option)
            double pond = Max(stateVars[FromIndices[0]], 0.0);
            rates[0] = Min(rates[0], pond / options.timestep);

            //reaching maximum depression storage
            double stor = Max(stateVars[ToIndices[0]], 0.0);
            double max_stor = hydroUnit.GetStateVarMax(ToIndices[0], stateVars, options);
            double deficit = Max(max_stor - stor, 0.0);
            double abst = Min(rates[0], deficit / options.timestep);
            rates[0] = abst;
        }


    }




}
