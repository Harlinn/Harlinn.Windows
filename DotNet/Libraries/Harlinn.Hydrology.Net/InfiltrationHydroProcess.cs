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

using static Harlinn.Hydrology.Common;
using static Harlinn.Hydrology.Constants;
using static Harlinn.Mathematics.Net.Common;
using static System.Math;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Infiltration hydro process, partitions ponded water (rainfall/snowmelt) to either soil storage or runoff.
    /// </summary>
    public class InfiltrationHydroProcess : HydroProcess
    {
        static readonly IReadOnlyList<ParameterInfo> scsParameters = new ParameterInfo[]
        {
            new ParameterInfo("SCS_CN", ClassType.CLASS_LANDUSE),
            new ParameterInfo("SCS_IA_FRACTION", ClassType.CLASS_LANDUSE)
        };

        static readonly IReadOnlyList<ParameterInfo> scsNoAbstractionParameters = new ParameterInfo[]
        {
            new ParameterInfo("SCS_CN", ClassType.CLASS_LANDUSE)
        };

        static readonly IReadOnlyList<ParameterInfo> rationalParameters = new ParameterInfo[]
        {
            new ParameterInfo("PARTITION_COEFF", ClassType.CLASS_LANDUSE)
        };

        static readonly IReadOnlyList<ParameterInfo> infiltratesParameters = new ParameterInfo[]
        {
            new ParameterInfo("IMPERMEABLE_FRAC", ClassType.CLASS_LANDUSE)
        };

        static readonly IReadOnlyList<ParameterInfo> gaParameters = new ParameterInfo[]
        {
            new ParameterInfo("HYDRAUL_COND", ClassType.CLASS_SOIL),
            new ParameterInfo("WETTING_FRONT_PSI", ClassType.CLASS_SOIL),
            new ParameterInfo("POROSITY", ClassType.CLASS_SOIL),
            new ParameterInfo("IMPERMEABLE_FRAC", ClassType.CLASS_LANDUSE)
        };

        static readonly IReadOnlyList<ParameterInfo> upscaledGreenAmptParameters = new ParameterInfo[]
        {
            new ParameterInfo("HYDRAUL_COND", ClassType.CLASS_SOIL),
            new ParameterInfo("WETTING_FRONT_PSI", ClassType.CLASS_SOIL),
            new ParameterInfo("KSAT_STD_DEVIATION", ClassType.CLASS_SOIL),
            new ParameterInfo("POROSITY", ClassType.CLASS_SOIL),
            new ParameterInfo("IMPERMEABLE_FRAC", ClassType.CLASS_LANDUSE)
        };

        static readonly IReadOnlyList<ParameterInfo> philip1957Parameters = [];

        static readonly IReadOnlyList<ParameterInfo> hmetsParameters = new ParameterInfo[]
        {
            new ParameterInfo("HMETS_RUNOFF_COEFF", ClassType.CLASS_LANDUSE),
            new ParameterInfo("IMPERMEABLE_FRAC", ClassType.CLASS_LANDUSE)
        };

        static readonly IReadOnlyList<ParameterInfo> vicParameters = new ParameterInfo[]
        {
            new ParameterInfo("VIC_ZMAX", ClassType.CLASS_SOIL),
            new ParameterInfo("VIC_ZMIN", ClassType.CLASS_SOIL),
            new ParameterInfo("VIC_ALPHA", ClassType.CLASS_SOIL),
            new ParameterInfo("POROSITY", ClassType.CLASS_SOIL),
            new ParameterInfo("IMPERMEABLE_FRAC", ClassType.CLASS_LANDUSE)
        };

        static readonly IReadOnlyList<ParameterInfo> vicArnoParameters = new ParameterInfo[]
        {
            new ParameterInfo("VIC_B_EXP", ClassType.CLASS_SOIL),
            new ParameterInfo("POROSITY", ClassType.CLASS_SOIL),
            new ParameterInfo("IMPERMEABLE_FRAC", ClassType.CLASS_LANDUSE)
        };

        static readonly IReadOnlyList<ParameterInfo> topmodelParameters = [];

        static readonly IReadOnlyList<ParameterInfo> prmsParameters = new ParameterInfo[]
        {
            new ParameterInfo( "MAX_SAT_AREA_FRAC", ClassType.CLASS_LANDUSE),
            new ParameterInfo( "POROSITY", ClassType.CLASS_SOIL),
            new ParameterInfo( "FIELD_CAPACITY", ClassType.CLASS_SOIL),
            new ParameterInfo( "SAT_WILT", ClassType.CLASS_SOIL),
            new ParameterInfo( "IMPERMEABLE_FRAC", ClassType.CLASS_LANDUSE)
        };

        static readonly IReadOnlyList<ParameterInfo> hbvParameters = new ParameterInfo[]
        {
            new ParameterInfo("POROSITY", ClassType.CLASS_SOIL),
            new ParameterInfo("HBV_BETA", ClassType.CLASS_SOIL),
            new ParameterInfo("IMPERMEABLE_FRAC", ClassType.CLASS_LANDUSE)
        };

        static readonly IReadOnlyList<ParameterInfo> ubcParameters = new ParameterInfo[]
        {
            new ParameterInfo("IMPERMEABLE_FRAC", ClassType.CLASS_LANDUSE),
            new ParameterInfo("MAX_PERC_RATE", ClassType.CLASS_SOIL),
            new ParameterInfo("UBC_INFIL_SOIL_DEF", ClassType.CLASS_SOIL),
            new ParameterInfo("POROSITY", ClassType.CLASS_SOIL),
            new ParameterInfo("UBC_GW_SPLIT", ClassType.CLASS_GLOBAL),
            new ParameterInfo("UBC_FLASH_PONDING", ClassType.CLASS_GLOBAL)
        };

        static readonly IReadOnlyList<ParameterInfo> gr4jParameters = new ParameterInfo[]
        {
            new ParameterInfo("POROSITY", ClassType.CLASS_SOIL),
            new ParameterInfo("IMPERMEABLE_FRAC", ClassType.CLASS_LANDUSE)
        };


        static readonly IReadOnlyList<ParameterInfo> xinanxiangParameters = new ParameterInfo[]
        {
            new ParameterInfo("IMPERMEABLE_FRAC", ClassType.CLASS_LANDUSE),
            new ParameterInfo("XINANXIANG_A", ClassType.CLASS_SOIL),
            new ParameterInfo("XINANXIANG_B", ClassType.CLASS_SOIL),
            new ParameterInfo("SAT_WILT", ClassType.CLASS_SOIL),
            new ParameterInfo("POROSITY", ClassType.CLASS_SOIL),
            new ParameterInfo("FIELD_CAPACITY", ClassType.CLASS_SOIL),
            new ParameterInfo("XINANXIANG_SHP", ClassType.CLASS_SOIL)
        };

        static readonly IReadOnlyList<ParameterInfo> pdmParameters = new ParameterInfo[]
        {
            new ParameterInfo("IMPERMEABLE_FRAC", ClassType.CLASS_LANDUSE),
            new ParameterInfo("PDM_B", ClassType.CLASS_LANDUSE),
            new ParameterInfo("POROSITY", ClassType.CLASS_SOIL)
        };


        static readonly IReadOnlyList<ParameterInfo> awbmParameters = new ParameterInfo[]
        {
            new ParameterInfo("AWBM_AREAFRAC1", ClassType.CLASS_LANDUSE),
            new ParameterInfo("AWBM_AREAFRAC2", ClassType.CLASS_LANDUSE),
            new ParameterInfo("AWBM_BFLOW_INDEX", ClassType.CLASS_LANDUSE)
        };


        static readonly IReadOnlyList<StateVariableInfo> gaSimpleStateVariableInfos = new StateVariableInfo[]
        {
            new StateVariableInfo(SVType.PONDED_WATER),
            new StateVariableInfo(SVType.SURFACE_WATER),
            new StateVariableInfo(SVType.CUM_INFIL),
            new StateVariableInfo(SVType.GA_MOISTURE_INIT)
        };

        static readonly IReadOnlyList<StateVariableInfo> ubcStateVariableInfos = new StateVariableInfo[]
        {
            new StateVariableInfo(SVType.PONDED_WATER),
            new StateVariableInfo(SVType.SURFACE_WATER),
            new StateVariableInfo(SVType.SOIL, 1),
            new StateVariableInfo(SVType.SOIL, 2),
            new StateVariableInfo(SVType.SOIL, 3)
        };

        static readonly IReadOnlyList<StateVariableInfo> hmetsStateVariableInfos = new StateVariableInfo[]
        {
            new StateVariableInfo(SVType.PONDED_WATER),
            new StateVariableInfo(SVType.SURFACE_WATER),
            new StateVariableInfo(SVType.CONVOLUTION, 0),
            new StateVariableInfo(SVType.CONVOLUTION, 1)
        };

        static readonly IReadOnlyList<StateVariableInfo> defaultStateVariableInfos = new StateVariableInfo[]
        {
            new StateVariableInfo(SVType.PONDED_WATER),
            new StateVariableInfo(SVType.SURFACE_WATER)
        };


        /// <summary>
        /// Infiltration algorithm
        /// </summary>
        InfilType type;

        public InfiltrationHydroProcess(Model model, InfilType itype)
            : base(model, HydroProcessType.INFILTRATION)
        {
            type = itype;
            DynamicSpecifyConnections(2);
            //infiltration (ponded-->soil)
            FromIndices[0] = model.GetStateVarIndex(SVType.PONDED_WATER); ToIndices[0] = model.GetStateVarIndex(SVType.SOIL, 0);
            //runoff/remainder (ponded->surface water)
            FromIndices[1] = model.GetStateVarIndex(SVType.PONDED_WATER); ToIndices[1] = model.GetStateVarIndex(SVType.SURFACE_WATER);

            if (itype == InfilType.INF_GA_SIMPLE)
            {
                DynamicSpecifyConnections(4);

                FromIndices[0] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[0] = model.GetStateVarIndex(SVType.SOIL, 0);

                FromIndices[1] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[1] = model.GetStateVarIndex(SVType.SURFACE_WATER);

                FromIndices[2] = model.GetStateVarIndex(SVType.CUM_INFIL); 
                ToIndices[2] = model.GetStateVarIndex(SVType.CUM_INFIL);

                FromIndices[3] = model.GetStateVarIndex(SVType.GA_MOISTURE_INIT); 
                ToIndices[3] = model.GetStateVarIndex(SVType.GA_MOISTURE_INIT);
            }
            else if (type == InfilType.INF_UBC)
            {
                DynamicSpecifyConnections(5);
                if(model.GetNumSoilLayers() < 4)
                {
                    throw new ArgumentException("INF_UBC infiltration algorithm requires at least 4 soil layers to operate. Please use a different :SoilModel or replace this infiltration algorithm.");
                }
                FromIndices[0] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[0] = model.GetStateVarIndex(SVType.SOIL, 0);

                FromIndices[1] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[1] = model.GetStateVarIndex(SVType.SURFACE_WATER);

                FromIndices[2] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[2] = model.GetStateVarIndex(SVType.SOIL, 1);

                FromIndices[3] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[3] = model.GetStateVarIndex(SVType.SOIL, 2);

                FromIndices[4] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[4] = model.GetStateVarIndex(SVType.SOIL, 3);
            }
            else if (type == InfilType.INF_HMETS)
            {
                DynamicSpecifyConnections(4);
                FromIndices[0] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[0] = model.GetStateVarIndex(SVType.SOIL, 0);

                FromIndices[1] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[1] = model.GetStateVarIndex(SVType.SURFACE_WATER);

                FromIndices[2] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[2] = model.GetStateVarIndex(SVType.CONVOLUTION, 0);

                FromIndices[3] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[3] = model.GetStateVarIndex(SVType.CONVOLUTION, 1);
            }
            else if (type == InfilType.INF_XINANXIANG)
            {
                DynamicSpecifyConnections(5);
                FromIndices[0] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[0] = model.GetStateVarIndex(SVType.SOIL, 0);

                FromIndices[1] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[1] = model.GetStateVarIndex(SVType.SURFACE_WATER);

                FromIndices[2] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[2] = model.GetStateVarIndex(SVType.SOIL, 1);

                FromIndices[3] = model.GetStateVarIndex(SVType.SOIL, 0); 
                ToIndices[3] = model.GetStateVarIndex(SVType.SOIL, 1);

                FromIndices[4] = model.GetStateVarIndex(SVType.SOIL, 1); 
                ToIndices[4] = model.GetStateVarIndex(SVType.SURFACE_WATER);
            }
            else if (type == InfilType.INF_AWBM)
            {
                DynamicSpecifyConnections(5);
                FromIndices[0] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[0] = model.GetStateVarIndex(SVType.SOIL, 0);

                FromIndices[1] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[1] = model.GetStateVarIndex(SVType.SOIL, 1);

                FromIndices[2] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[2] = model.GetStateVarIndex(SVType.SOIL, 2);

                FromIndices[3] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[3] = model.GetStateVarIndex(SVType.SURFACE_WATER);

                FromIndices[4] = model.GetStateVarIndex(SVType.PONDED_WATER); 
                ToIndices[4] = model.GetStateVarIndex(SVType.SOIL, 3);
            }
        }


        public override void Initialize()
        {
            if(Model.GetStateVarType(ToIndices[0]) != SVType.SOIL)
            {
                throw new InvalidOperationException("InfiltrationHydroProcess.Initialize: infiltration must be to soil.");
            }
        }

        


        public override IReadOnlyList<ParameterInfo> GetParticipatingParamList()
        {
            if (type == InfilType.INF_SCS)
            {
                return scsParameters;
            }
            else if (type == InfilType.INF_SCS_NOABSTRACTION)
            {
                return scsNoAbstractionParameters;
            }
            else if (type == InfilType.INF_RATIONAL)
            {
                return rationalParameters;
            }
            else if (type == InfilType.INF_ALL_INFILTRATES)
            {
                return infiltratesParameters;
            }
            else if ((type == InfilType.INF_GREEN_AMPT) || (type == InfilType.INF_GA_SIMPLE))
            {
                return gaParameters;
            }
            else if (type == InfilType.INF_UPSCALED_GREEN_AMPT)
            {
                return upscaledGreenAmptParameters;
            }
            else if (type == InfilType.INF_PHILIP_1957)
            {
                return philip1957Parameters;
            }
            else if (type == InfilType.INF_HMETS)
            {
                return hmetsParameters;
            }
            else if (type == InfilType.INF_VIC)
            {
                return vicParameters;
            }
            else if (type == InfilType.INF_VIC_ARNO)
            {
                return vicArnoParameters;
            }
            else if (type == InfilType.INF_TOPMODEL)
            {
                // algorithm not completed
                return topmodelParameters;
            }
            else if (type == InfilType.INF_PRMS)
            {
                return prmsParameters;
            }
            else if (type == InfilType.INF_HBV)
            {
                return hbvParameters;
            }
            else if (type == InfilType.INF_UBC)
            {
                return ubcParameters;
            }
            else if (type == InfilType.INF_GR4J)
            {
                return gr4jParameters;
            }
            else if (type == InfilType.INF_XINANXIANG)
            {
                return xinanxiangParameters;
            }
            else if (type == InfilType.INF_PDM)
            {
                return pdmParameters;
            }
            else if (type == InfilType.INF_AWBM)
            {
                return awbmParameters;
            }
            else
            {
                throw new InvalidOperationException("InfiltrationHydroProcess.GetParticipatingParamList: undefined infiltration algorithm");
            }
        }


        


        public static IReadOnlyList<StateVariableInfo> GetParticipatingStateVarList(InfilType itype)
        {

            // Special cases - modify more than just ponded water, soil and surface water storage

            if (itype == InfilType.INF_GA_SIMPLE)
            { 
                // Tracks and updates cumulative infiltration
                return gaSimpleStateVariableInfos;
            }
            else if (itype == InfilType.INF_UBC)
            {
                return ubcStateVariableInfos;
            }
            else if (itype == InfilType.INF_HMETS)
            {
                return hmetsStateVariableInfos;
            }
            else
            {
                return defaultStateVariableInfos;
            }
        }


        /// <summary>
        /// Calculates runoff [mm/d] from rainfall using SCS curve number method
        /// </summary>
        /// <param name="hydroUnit">
        /// The hydro unit.
        /// </param>
        /// <param name="options">
        /// The options.
        /// </param>
        /// <param name="tt">
        /// Current simulation time.
        /// </param>
        /// <param name="rainthru">
        /// Rainfall/snowmelt rate [mm/d].
        /// </param>
        /// <returns>
        /// Runoff from rainfall [mm/d] according to SCS curve number method
        /// </returns>
        double GetSCSRunoff(HydroUnit hydroUnit, Options options, TimeStruct tt, double rainthru)
        {
            int condition = 2;     //antecedent moisture condition
            double S, CN, W, Weff;     //retention parameter [mm], CNII, rainfall [mm], runoff [mm]
            double TR;              //total rain over past 5 days [in]
            double Ia;              //initial abstraction, [mm]

            TR = hydroUnit.GetForcingFunctions().precip_5day / MM_PER_INCH;
            CN = hydroUnit.GetSurfaceProps().SCS_CN;

            // correct curve number for antecedent moisture conditions
            if((tt.month>4) && (tt.month<9)) 
            {
                //growing season?? (northern hemisphere)
                if (TR<1.4) 
                { 
                    condition=1; 
                }
                else if(TR>2.1) 
                { 
                    condition=3; 
                }
            }
            else
            {
                if (TR < 0.5) 
                { 
                    condition = 1; 
                }
                else if (TR > 1.1) 
                { 
                    condition = 3; 
                }
            }
            if (condition == 1) 
            { 
                CN = 5E-05 * Pow(CN, 3) + 0.0008 * Pow(CN, 2) + 0.4431 * CN; 
            }
            else if (condition == 3) 
            { 
                CN = 7E-05 * Pow(CN, 3) - 0.0185 * Pow(CN, 2) + 2.1586 * CN; 
            }
            CN = Min(CN, 100.0);

            // Calculate amount of runoff
            S = MM_PER_INCH * (1000.0 / CN - 10.0);
            W = rainthru * options.timestep;//[mm]
            if (type != InfilType.INF_SCS_NOABSTRACTION)
            {
                //SCS_Ia_fraction is =0.2 for standard SCS implementation
                Ia = (hydroUnit.GetSurfaceProps().SCS_Ia_fraction) * S;
            }
            else
            {
                // abstraction handled by another routine
                // 
                // when tied to an SCS Abstraction algorithm which explicitly tracks depression storage
                // "rainthru" is what remains after abstraction, i.e., W=W-Ia, or SCS_Ia_fraction=0.0
                Ia = 0.0;
            }
            Weff = Pow(ThreshPositive(W - Ia), 2) / (W + (S - Ia));//[mm]
            if (W + (S - Ia) == 0.0) { Weff = 0.0; }

            return Weff / options.timestep;
        }

        /// <summary>
        /// Calculates runoff [mm/d] from rainfall using UBCWM method
        /// </summary>
        /// <param name="stateVars">
        /// Array of current state variables
        /// </param>
        /// <param name="hydroUnit">
        /// The hydro unit.
        /// </param>
        /// <param name="options">
        /// The simulation options.
        /// </param>
        /// <param name="tt">
        /// The time step.
        /// </param>
        /// <param name="rates">
        /// Calculated runoff  and infiltration from rainfall [mm/d]
        /// </param>
        /// <param name="rainthru">
        /// Rainfall/snowmelt rate applied to ground surface [mm/d]
        /// </param>
        void GetUBCWMRunoff(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates, double rainthru)
        {
            const double V0FLAX = 1800.0; //[mm]

            double infil, to_GW, to_interflow, runoff;
            double flash_factor, b1, b2;

            double soil_deficit = Max(0.0, hydroUnit.GetSoilCapacity(0) - stateVars[ToIndices[0]]);

            double Fimp = hydroUnit.GetSurfaceProps().impermeable_frac;
            double max_perc_rate = hydroUnit.GetSoilProps(1).max_perc_rate;
            double P0AGEN = hydroUnit.GetSoilProps(0).UBC_infil_soil_def;
            double P0DSH = Model.GetGlobalParams().UBC_GW_split;
            double V0FLAS = Model.GetGlobalParams().UBC_flash_ponding;  //[mm]

            // Calculate b1 parameter (effective permeable area without flash factor)
            b1 = 1.0;
            if (Fimp<1.0) 
            {
                b1 = Fimp* Pow(10.0, -soil_deficit / P0AGEN);
            }

            // Calculate flash factor (for high intensity storms)
            flash_factor=0.0;
            if (rainthru>V0FLAS)
            {
                flash_factor = (1.0 + Log(rainthru/V0FLAX)/Log(V0FLAX/V0FLAS));
            }
            flash_factor = Clamp(flash_factor, 0.0, 1.0);

            // calculate b2 (effective permeable area pct)
            b2 = (b1) * (1.0) + (1.0 - b1) * flash_factor;

            // part of "cheat" to send b2 to glacial HRUs for infiltration calcs
            g_debug_vars[0] = b2;

            //distribute ponded water to surface water and soil stores
            infil = Min(soil_deficit / options.timestep, rainthru);//fills soil deficit
            to_GW = Min(max_perc_rate, rainthru - infil); //overflows to GW
            to_interflow = (rainthru - infil - to_GW);//overflows to interflow

            infil *= 1 - b2;
            to_GW *= 1 - b2;
            to_interflow *= 1 - b2;

            runoff = rainthru - infil - to_GW - to_interflow; //equivalently, b2*rainthru?

            // ponded water->soil deficit
            rates[0] = infil;
            // ponded water->surface water
            rates[1] = runoff;
            // ponded water->interflow
            rates[2] = to_interflow;
            // ponded water->upper groundwater
            rates[3] = (1.0 - P0DSH) * to_GW;
            // ponded water->lower groundwater
            rates[4] = (P0DSH) * to_GW;
        }

        /// <summary>
        /// Returns dimensionless time, X
        /// </summary>
        /// <param name="tstar">
        /// Dimensionless time t*
        /// </param>
        /// <returns>
        /// dimensionless time X
        /// </returns>
        static double CalcX(double tstar)
        {
            if (tstar==0.0)
            {
                return 0.0;
            }
            return 1.0/(1.0/tstar+1.0);
        }

        /// <summary>
        /// Returns value of epsilon function used in upscaled GA
        /// </summary>
        /// <param name="t">
        /// time since onset of constant rainfall
        /// </param>
        /// <param name="alpha">
        /// GA Alpha value [mm]
        /// </param>
        /// <param name="Ks">
        /// Saturated conductivity [mm/d]
        /// </param>
        /// <param name="w">
        /// rainfall rate [mm/d]
        /// </param>
        /// <returns>
        /// Epsilon approximation at t
        /// </returns>
        static double Epsilon(double t, double alpha, double Ks, double w)
        {
            double X = CalcX(w * t / alpha);
            if (X==0)
            {
                return 0.0;
            }
            double kp = Ks / w / X;
            if ((kp<=0) || (kp>=1.0))
            {
                return 0.0;
            }
            return 0.135*Pow(1-X,0.484)*2.69*Pow(1.0-kp,1.74)*Pow(kp,0.38);
        }


        /// <summary>
        /// Upscaled Green Ampt infiltration
        /// </summary>
        /// <remarks>
        /// <para>
        /// Analytical / semi-analytical upscaling of GA infiltration with
        /// spatially variable conductivity.
        /// </para>
        /// <para>
        /// if eps_in:
        /// </para>
        /// <list type="table">
        /// <listheader>
        /// <term>Value</term>
        /// <description>Description</description>
        /// </listheader>
        /// <item>
        /// <term>0</term>
        /// <description>Uses linear approximation.</description>
        /// </item>
        /// <item>
        /// <term>1</term>
        /// <description>Uses dirac approx of epsilon integral.</description>
        /// </item>
        /// <item>
        /// <term>2</term>
        /// <description>Uses 2pt gauss integration of epsilon integral.</description>
        /// </item>
        /// <item>
        /// <term>3</term>
        /// <description>Numerically integrate epsilon integral.</description>
        /// </item>
        /// </list>
        /// </remarks>
        /// <param name="t">
        /// time since onset of rainfall
        /// </param>
        /// <param name="alpha">Alpha value</param>
        /// <param name="mu_Y">Mean of log-conductivity</param>
        /// <param name="sig_Y">Standard Deviation of log-conductivity</param>
        /// <param name="w">rainfall rate</param>
        /// <param name="eps_in">Input epsilon value</param>
        /// <returns>Upscaled GA infiltration rate[mm/d]</returns>
        static double Smooth_GA_k( double t, double alpha, double mu_Y, double sig_Y, double w, int eps_in)
        {
            /// \ref eqn 10 from text of Craig et al., 2010
            if (t <= 0)
            {
                return w;
            }

            double sum = 0.0;
            double X = CalcX(t * w / alpha);
            double kbar = Exp(mu_Y + sig_Y * sig_Y / 2);  //average conductivity
            double A = (Log(w * X) - mu_Y) / sig_Y / Sqrt(2.0);//upper limit (wX) in normalized Y space
            if (sig_Y==0)
            {
                A=1e99;
            }

            sum += 0.5 * w * Erfc(A);
            sum += 0.5 / X * kbar * Erfc(sig_Y / Sqrt(2.0) - A);

            if (eps_in == 1)
            { 
                // Approximate:
                double P = 0.5 * (1.0 + Erf(A));
                double ktest = 0.5 * kbar * Erfc(sig_Y / Sqrt(2.0) - A) / P;

                sum += w * P * Epsilon(t, alpha, ktest, w);
            }
            else if (eps_in == 2)
            { 
                // 2-point gauss integration:
                double km, k1, k2, halfrange;
                halfrange = 0.5 * (w * X - Exp(mu_Y - 3.0 * sig_Y));
                km = w * X - halfrange;
                k1 = km - 0.577 * halfrange;
                k2 = km + 0.577 * halfrange;
                if (halfrange > 0)
                {
                    sum += halfrange * w * Epsilon(t, alpha, k1, w) * LogPdf(k1, mu_Y, sig_Y);
                    sum += halfrange * w * Epsilon(t, alpha, k2, w) * LogPdf(k2, mu_Y, sig_Y);
                }
            }
            else if (eps_in == 3)
            {
                // Numerically integrated:
                double maxk = Exp(mu_Y + 4 * sig_Y);
                
                double mink = Exp(mu_Y - 4 * sig_Y);
                double dk = (maxk - mink) / 25000;
                double integ = 0.0,ki;
                for (double k = mink; k < maxk; k += dk)
                {
                    ki = (k + 0.5 * dk);
                    // just epsilon:
                    integ += (w * Epsilon(t, alpha, ki, w)) * LogPdf(ki, mu_Y, sig_Y) * dk;
                }
                sum += integ;
            }
            return sum;
        }

        /// <summary>
        /// Calculates Green Ampt cumulative infiltration over time step
        /// </summary>
        /// <param name="t">
        /// Time from start of constant rainfall (or time step) [d]
        /// </param>
        /// <param name="alpha">
        /// GA alpha parameter [mm]
        /// </param>
        /// <param name="Ks">
        /// Saturated conductivity [mm/d]
        /// </param>
        /// <param name="w">
        /// Rainfall rate [mm/d]
        /// </param>
        /// <returns>
        /// Cumulative infiltration [mm]
        /// </returns>
        static double GreenAmptCumInf(double t, double alpha, double Ks, double w)
        {
            // explicit solution to green ampt formulae
            if (Ks==0)
            {
                return 0.0;
            }
            if (w==0)
            {
                return 0.0;
            }
            if (alpha==0)
            {
                return 0.0;
            }

            // ponding time
            double tp = alpha * Ks / w / (w - Ks); 
            if ((t<tp) || (w<Ks))
            {
                // Cumulative infiltration [mm]
                return w * t; 
            }
            else
            {
                double tstar, x;
                double Fp = w * tp;
                tstar=Ks/alpha* (t-tp);
                x=-(1.0+Fp/alpha)* Exp(-(1.0+tstar+Fp/alpha));

                // Cumulative infiltration
                return alpha * (-1.0-LambertN(x,3));
            }
        }

        /// <summary>
        /// Calculates Green Ampt Runoff
        /// </summary>
        /// <remarks>
        /// Calculates runoff [mm/d] from rainfall (rainthru) using GA infiltration method
        /// </remarks>
        /// <param name="stateVars">Array of current model state variables for hydro unit.</param>
        /// <param name="hydroUnit">
        /// The hydro unit.
        /// </param>
        /// <param name="options">
        /// The simulation options.
        /// </param>
        /// <param name="tt">
        /// Current simulation time.
        /// </param>
        /// <param name="rates">
        /// [out] Calculated runoff and infiltration from rainfall [mm/d]
        /// </param>
        /// <param name="rainthru">
        /// Rate of rainfall [mm/day]
        /// </param>
        void GetGreenAmptRunoff(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates, double rainthru)
        {
            double finf; //[mm/day]
            double cumInf = 0; //[mm] - cumulative infiltration at time t
            double Keff; //[mm/day] -effective hydraulic conductivity
            double alpha;//|psi_f|*(saturation deficit)
            double deficit;
            double runoff;

            Soil S = hydroUnit.GetSoilProps(0);
            double Ksat = S.hydraul_cond;//[mm/d]
            double psi_wf = S.wetting_front_psi;//[-mm]
            double poro = S._porosity;
            double stor = stateVars[ToIndices[0]];
            double max_stor = hydroUnit.GetSoilCapacity(0);
            double Fimp = hydroUnit.GetSurfaceProps().impermeable_frac;
            double initStor = 0;

            Keff=Ksat;

            if(type == InfilType.INF_GA_SIMPLE)
            {
                cumInf=stateVars[Model.GetStateVarIndex(SVType.CUM_INFIL)];//[mm]
                initStor = stateVars[Model.GetStateVarIndex(SVType.GA_MOISTURE_INIT)];//[mm] Storage at start of rainfall

                // Redistribute during periods of low rainfall
                if(rainthru <= Keff)
                {
                    if(cumInf<=0 ) 
                    {
                        // reset
                        cumInf = 0;
                        initStor=0;
                    }
                    else 
                    {
                        //redistribute
                        double distribution_rate;

                        // 2/3 is an arbitrary number, and doesn't have a huge impact ...
                        distribution_rate = Max(cumInf*2/3, Keff); 

                        cumInf -= distribution_rate* options.timestep;
                        initStor += distribution_rate* options.timestep;
                        initStor = Min(initStor, stor);

                        if(cumInf<=0)
                        {
                            cumInf = 0;
                            initStor=0;
                        }
                    }
                    rates[2] = (cumInf - stateVars[Model.GetStateVarIndex(SVType.CUM_INFIL)]) / options.timestep;
                    rates[3] = (initStor - stateVars[Model.GetStateVarIndex(SVType.GA_MOISTURE_INIT)]) / options.timestep;
                }
            }

            // no rain, no infiltration
            if (rainthru <= REAL_SMALL)
            {
                rates[0] = 0;
                rates[1] = 0;
                return;
            }

            deficit = (1.0 - stor / max_stor) * poro;
            alpha = psi_wf * deficit;

            double tstep = options.timestep;
            if (type == InfilType.INF_GREEN_AMPT)
            {
                // high-order approximation
                cumInf = GreenAmptCumInf(tstep, alpha, Keff, rainthru);//[mm]
            }
            else if (type == InfilType.INF_GA_SIMPLE)
            {
                if (cumInf <= 0) 
                {
                    // First time step of rainfall event
                    cumInf = GreenAmptCumInf(tstep, alpha, Keff, rainthru);//[mm]
                    initStor = stor; //set initial storage
                }
                else
                {
                    deficit = (1.0 - initStor / max_stor) * poro;
                    alpha = psi_wf * deficit;
                }
            }

            if (cumInf > 0)
            {
                finf = Keff * (1.0 + alpha / cumInf);//[mm/day]
            }
            else
            {
                finf = 0.0;
            }

            runoff = ThreshPositive(rainthru - finf); //THRESHOLD BEHAVIOUR
            runoff = (Fimp) * rainthru + (1 - Fimp) * runoff; //correct for impermeable surfaces

            if (type == InfilType.INF_GA_SIMPLE)
            {
                cumInf += (rainthru - runoff) * options.timestep;
                rates[2] = (cumInf - stateVars[Model.GetStateVarIndex(SVType.CUM_INFIL)]) / options.timestep;
                rates[3] = (initStor - stateVars[Model.GetStateVarIndex(SVType.GA_MOISTURE_INIT)]) / options.timestep;
            }

            rates[0] = rainthru - runoff;
            rates[1] = runoff;
        }

        /// <summary>
        /// Calculates heterogeneous Green Ampt runoff
        /// </summary>
        /// <remarks>
        /// Calculates runoff (mm/day) from rainfall (rainthru) using upscaled Green ampt infiltration method
        /// </remarks>
        /// <param name="rainthru">
        /// Rainthru [mm/d]
        /// </param>
        /// <param name="S">
        /// The soil properties.
        /// </param>
        /// <param name="thickness">
        /// Soil layer thickness [mm]
        /// </param>
        /// <param name="soil_water_content">
        /// Soil water content [mm].
        /// </param>
        /// <param name="tt">
        /// Current simulation time.
        /// </param>
        /// <param name="options">
        /// Global model options information.
        /// </param>
        /// <returns>
        /// Heterogenous GA runoff [mm/d]
        /// </returns>
        static double GetHeterogeneousGreenAmptRunoff( double rainthru, Soil S, double thickness, double soil_water_content, TimeStruct tt, Options options)
        {
            double finf;
            double alpha;
            double mu_Y;

            double poro = S._porosity;
            double Ksat = S.hydraul_cond;

            double psi_wf = S.wetting_front_psi;
            double sig_Y = S.ksat_std_deviation;

            alpha=psi_wf* poro*(1.0-soil_water_content/(poro* thickness));

            mu_Y=Log(Ksat)-0.5*sig_Y* sig_Y;

            finf=Smooth_GA_k(options.timestep*0.5, alpha, mu_Y, sig_Y, rainthru,1);//1 point gauss integration @ midpoint

            return ThreshPositive(rainthru-finf);
        }

        public override void GetRatesOfChange(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            if ((hydroUnit.GetHRUType() != HRUType.HRU_STANDARD) && (hydroUnit.GetHRUType() != HRUType.HRU_ROCK)) 
            {
                // Lakes & glaciers
                return; 
            }

            double runoff;
            double rainthru;
            double Fimp;
            double ponded_water;

            Fimp = hydroUnit.GetSurfaceProps().impermeable_frac;

            ponded_water = Max(stateVars[Model.GetStateVarIndex(SVType.PONDED_WATER)], 0.0);

            rainthru = (ponded_water / options.timestep);//potential infiltration rate, mm/d

            if (hydroUnit.GetHRUType() == HRUType.HRU_ROCK) 
            {
                //if rock, nothing infiltrates, everything runs off
                rates[1] = rainthru; 
                return; 
            } 

            int iTopSoil = Model.GetStateVarIndex(SVType.SOIL, 0);

            //-----------------------------------------------------------------
            if (type == InfilType.INF_RATIONAL)
            {
                runoff = hydroUnit.GetSurfaceProps().partition_coeff * rainthru;
                rates[0] = rainthru - runoff;
                rates[1] = runoff;
            }
            //-----------------------------------------------------------------
            else if ((type == InfilType.INF_SCS) || (type == InfilType.INF_SCS_NOABSTRACTION))
            {
                runoff = GetSCSRunoff(hydroUnit, options, tt, rainthru);
                rates[0] = rainthru - runoff;
                rates[1] = runoff;
            }
            //-----------------------------------------------------------------
            else if (type == InfilType.INF_ALL_INFILTRATES)
            {
                runoff = 0.0;
                runoff = (Fimp) * rainthru + (1 - Fimp) * runoff; //correct for impermeable surfaces
                rates[0] = rainthru - runoff;
                rates[1] = runoff;
            }
            //-----------------------------------------------------------------
            else if (type == InfilType.INF_PHILIP_1957)
            {
                //< \todo [add funct] Add Philip 1957 infiltration alg.
                Runtime.ExitGracefully("CmvInfiltration::INF_PHILIP_1957", ExitCode.STUB);
            }
            //-----------------------------------------------------------------
            else if (type == InfilType.INF_VIC)
            {
                double gamma, K1, sat, Smax;
                double zmax, zmin, alpha;
                double stor, max_stor;

                stor = stateVars[iTopSoil];
                max_stor = hydroUnit.GetSoilCapacity(0);
                zmax = hydroUnit.GetSoilProps(0).VIC_zmax;
                zmin = hydroUnit.GetSoilProps(0).VIC_zmin;
                alpha = hydroUnit.GetSoilProps(0).VIC_alpha;

                sat = Min(stor / max_stor, 1.0);
                gamma = 1.0 / (alpha + 1.0);
                K1 = Pow((zmax - zmin) * alpha * gamma, -gamma);
                Smax = gamma * (alpha * zmax + zmin);

                runoff = rainthru * ThreshMax(1.0 - K1 * Pow(Smax - sat, gamma), 1.0, 0.0);

                runoff = (Fimp) * rainthru + (1 - Fimp) * runoff; //correct for impermeable surfaces

                rates[0] = rainthru - runoff;
                rates[1] = runoff;
            }
            //-----------------------------------------------------------------
            else if (type == InfilType.INF_HBV)
            {
                double beta, stor, max_stor, sat;
                stor = stateVars[iTopSoil];
                max_stor = hydroUnit.GetSoilCapacity(0);
                beta = hydroUnit.GetSoilProps(0).HBV_beta;
                sat = Max(Min(stor / max_stor, 1.0), 0.0);

                runoff = Pow(sat, beta) * rainthru;

                runoff = (Fimp) * rainthru + (1 - Fimp) * runoff; //correct for impermeable surfaces

                rates[0] = rainthru - runoff;
                rates[1] = runoff;
            }
            //-----------------------------------------------------------------
            else if (type == InfilType.INF_VIC_ARNO)
            {
                double sat_area, stor, max_stor, b, sat;

                stor = stateVars[iTopSoil];
                max_stor = hydroUnit.GetSoilCapacity(0);        //maximum storage of top soil layer [mm]
                b = hydroUnit.GetSoilProps(0).VIC_b_exp;//ARNO/VIC b exponent for runoff [-]
                sat = Min(stor / max_stor, 1.0);          //soil saturation
                sat_area = 1.0 - Pow(1.0 - sat, b);            //saturated area [-] fraction

                runoff = sat_area * rainthru;

                runoff = (Fimp) * rainthru + (1 - Fimp) * runoff; //correct for impermeable surfaces

                rates[0] = rainthru - runoff;
                rates[1] = runoff;
            }
            //-----------------------------------------------------------------
            else if (type == InfilType.INF_PRMS)
            {
                double stor, tens_stor, sat_frac;
                sat_frac = hydroUnit.GetSurfaceProps().max_sat_area_frac;
                tens_stor = hydroUnit.GetSoilTensionStorageCapacity(0);
                stor = stateVars[iTopSoil];

                runoff = sat_frac * Min(stor / tens_stor, 1.0) * rainthru;

                runoff = (Fimp) * rainthru + (1 - Fimp) * runoff; //correct for impermeable surfaces

                rates[0] = rainthru - runoff;
                rates[1] = runoff;
            }
            //-----------------------------------------------------------------
            else if (type == InfilType.INF_TOPMODEL)
            {
                double sat_area;

                sat_area = 0;

                Runtime.ExitGracefully("GetTOPMODELRUNOFF", ExitCode.STUB);

                runoff = sat_area * rainthru;              //runoff rate [mm/d]

                runoff = (Fimp) * rainthru + (1 - Fimp) * runoff; //correct for impermeable surfaces

                rates[0] = rainthru - runoff;
                rates[1] = runoff;
            }
            //-----------------------------------------------------------------
            else if ((type == InfilType.INF_GREEN_AMPT) || (type == InfilType.INF_GA_SIMPLE))
            {
                GetGreenAmptRunoff(stateVars, hydroUnit, options, tt, rates, rainthru);
            }
            //-----------------------------------------------------------------
            else if (type == InfilType.INF_UPSCALED_GREEN_AMPT)
            {
                runoff = GetHeterogeneousGreenAmptRunoff(rainthru,
                                                       hydroUnit.GetSoilProps(0),
                                                       hydroUnit.GetSoilThickness(0),
                                                       stateVars[iTopSoil],
                                                       tt, options);
                // correct for impermeable surfaces
                runoff = (Fimp) * rainthru + (1 - Fimp) * runoff; 

                rates[0] = rainthru - runoff;
                rates[1] = runoff;
            }
            //-----------------------------------------------------------------
            else if (type == InfilType.INF_UBC)
            {
                GetUBCWMRunoff(stateVars, hydroUnit, options, tt, rates, rainthru);
            }
            //-----------------------------------------------------------------
            else if (type == InfilType.INF_GR4J)
            {
                double x1 = hydroUnit.GetSoilCapacity(0);
                double infil;
                double tmp;
                double stor = stateVars[iTopSoil];
                double sat = stor / x1;
                tmp = Tanh(ponded_water / x1);
                infil = x1 * (1.0 - (sat * sat)) * tmp / (1.0 + sat * tmp);
                // correct for impermeable surfaces
                infil = (1.0 - Fimp) * infil; 
                rates[0] = infil;
                rates[1] = rainthru - infil;
            }
            //-----------------------------------------------------------------
            else if (type == InfilType.INF_HMETS)
            {
                double infil, delayed, direct;

                double stor = stateVars[iTopSoil];
                double max_stor = hydroUnit.GetSoilCapacity(0);
                double coef_runoff = hydroUnit.GetSurfaceProps().HMETS_runoff_coeff; //[-]

                double sat = Min(Max(stor / max_stor, 0.0), 1.0);

                direct = Fimp * rainthru;

                //[mm/d] 'horizontal transfer'
                runoff = coef_runoff * (sat) * (1.0 - Fimp) * rainthru; 

                infil = (1.0 - Fimp) * rainthru - runoff;

                delayed = coef_runoff * Pow(sat, 2.0) * infil; //[mm/d]
                infil -= delayed;

                // PONDED->SOIL[0]
                rates[0] = infil;
                // PONDED->SW
                rates[1] = direct;
                // PONDED->CONVOL[0]
                rates[2] = runoff;
                // PONDED->CONVOL[1]
                rates[3] = delayed;
            }
            //-----------------------------------------------------------------
            else if (type == InfilType.INF_XINANXIANG)
            {
                // from Jayawardena, AW and MC Zhou A modified spatial soil moisture storage capacity distribution curve for the Xinanjiang model.
                // Journal of Hydrology, 227(1-4), p93-113, 2000

                double b = 1.0;//hydroUnit.GetSoilProps(0).Xinanxiang_b;
                double c = 1.0;//hydroUnit.GetSoilProps(0).Xinanxiang_shp; [-0.5<c<0.5]
                double stor = stateVars[iTopSoil];
                double tens_stor = hydroUnit.GetSoilTensionStorageCapacity(0);
                double max_stor = hydroUnit.GetSoilCapacity(0);
                double infil, sat_excess, direct;

                direct = (1.0 - Fimp) * rainthru;

                double sat = Max(0.0, stor / tens_stor);
                double sat1 = Max(0.0, stor / (max_stor - tens_stor));
                if (sat <= 0.5 - c) 
                { 
                    infil = (Pow(0.5 - c, 1 - b) * Pow(sat, b)) * direct; 
                }
                else 
                { 
                    infil = (1.0 - Pow(0.5 + c, 1 - b) * Pow(1 - sat, b)) * direct; 
                }

                sat_excess = 1.0;//(1.0-pow(1-sat1,n))*direct;

                Runtime.ExitGracefully("INF_XINANXIANG", ExitCode.STUB);

                // correct for impermeable surfaces
                infil = (1.0 - Fimp) * infil;
                // PONDED->SOIL
                rates[0] = infil;
                // PONDED->SW
                rates[1] = rainthru - infil;
            }
            //----------------------------------------------------------------------------
            else if (type == InfilType.INF_PDM)
            {
                //uses PDM algorithm from Moore (1985)

                // [-] pareto distribution parameter
                double b;
                // [mm] maximum local storage capacity in HRU
                double c_max;
                // [mm] critical capacity, c*
                double c_star;
                // [mm] total amount abstracted
                double infil;

                b = hydroUnit.GetSurfaceProps().PDM_b;

                double stor = stateVars[iTopSoil];
                double max_stor = hydroUnit.GetSoilCapacity(0);

                c_max = (b + 1) * max_stor;

                c_star = c_max * (1.0 - Pow(1.0 - (stor / max_stor), 1.0 / (b + 1.0)));

                //analytical evaluation of P*dt-equation 3 of Mekonnen et al. (2014); min() handles case where entire landscape sheds
                infil = max_stor * (Pow(1.0 - (c_star / c_max), b + 1.0) - Pow(1.0 - Min(c_star + ponded_water, c_max) / c_max, b + 1.0));
                infil = Min(infil, ponded_water);

                // correct for impermeable surfaces
                infil = (1.0 - Fimp) * infil / options.timestep;

                // PONDED->SOIL[0]
                rates[0] = infil;
                // PONDED->SW
                rates[1] = rainthru - infil;
            }
            //----------------------------------------------------------------------------
            else if (type == InfilType.INF_AWBM)
            { 
                // uses Australia Water Balance algorithm from Boughton (2004)
                double infil1, infil2, infil3, runoff1, runoff2, runoff3, excess, to_GW;
                double def1, def2, def3; //[mm]
                double a1 = hydroUnit.GetSurfaceProps().AWBM_areafrac1;
                double a2 = hydroUnit.GetSurfaceProps().AWBM_areafrac2;
                double a3 = 1.0 - a1 - a2;
                double BFI = hydroUnit.GetSurfaceProps().AWBM_bflow_index;

                def1 = Max(a1 * hydroUnit.GetSoilCapacity(0) - stateVars[FromIndices[0]], 0.0); // deficit averaged over domain
                def2 = Max(a2 * hydroUnit.GetSoilCapacity(1) - stateVars[FromIndices[1]], 0.0);
                def3 = Max(a3 * hydroUnit.GetSoilCapacity(2) - stateVars[FromIndices[2]], 0.0);

                runoff1 = Max(a1 * ponded_water - def1, 0.0);
                runoff2 = Max(a2 * ponded_water - def2, 0.0);
                runoff3 = Max(a3 * ponded_water - def3, 0.0);
                infil1 = a1 * ponded_water - runoff1;
                infil2 = a2 * ponded_water - runoff2;
                infil3 = a3 * ponded_water - runoff3;

                excess = (1.0 - BFI) * (runoff1 + runoff2 + runoff3);
                to_GW = (BFI) * (runoff1 + runoff2 + runoff3);

                rates[0] = infil1 / options.timestep;   //PONDED->SOIL[0]
                rates[1] = infil2 / options.timestep;   //PONDED->SOIL[1]
                rates[2] = infil3 / options.timestep;   //PONDED->SOIL[2]
                rates[3] = excess / options.timestep;   //PONDED->SURFACE_WATER
                rates[4] = to_GW / options.timestep;    //PONDED->SOIL[3]
            }
        }

        public override void ApplyConstraints(double[] stateVars, HydroUnit hydroUnit, Options options, TimeStruct tt, double[] rates)
        {
            if (hydroUnit.GetHRUType() != HRUType.HRU_STANDARD) 
            {
                // Lakes & glaciers
                return; 
            }

            // cannot remove more than is there (should never be an option)
            rates[0] = Min(rates[0], stateVars[FromIndices[0]] / options.timestep);

            // reaching soil saturation level
            double inf = rates[0];
            double max_stor;
            if (!options.allow_soil_overfill)
            {
                max_stor = hydroUnit.GetStateVarMax(ToIndices[0], stateVars, options);
                inf = Min(rates[0], Max(max_stor - stateVars[ToIndices[0]], 0.0) / options.timestep);
            }

            rates[1] += (rates[0] - inf);
            rates[0] = inf;
        }


}
}
