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
using static System.Math;
namespace Harlinn.Hydrology
{
    public class Common : Harlinn.Mathematics.Net.Common
    {
        public static string g_output_directory = "";
        public static bool g_suppress_warnings = false;
        public static bool g_suppress_zeros = false;
        public static readonly double[] g_debug_vars = new double[10];
        public static bool g_disable_freezing = false;
        public static double g_min_storage = 0.0;
        public static int g_current_e = DOESNT_EXIST;

        /// <summary>
        /// Calculates saturation vapor pressure [KPa]
        /// </summary>
        /// <param name="T">Temperature in Celsius</param>
        /// <returns>Saturated vapor pressure [kPa]</returns>
        public static double GetSaturatedVaporPressure(double T)//[C]
        {
            const double A1 = 0.61078;
            const double A2 = 17.26939;
            const double A3 = 237.3;
            const double A4 = 21.87456;
            const double A5 = 265.5;

            // Dingman/Brook90 version (Tetens equation, 1930)
            if (T>=0)
            {
                return A1* Exp(A2* T/(T+A3));
            }
            else     
            {
                return A1* Exp(A4* T/(T+A5));
            }
        }

        /// <summary>
        /// Calculates saturation vapor pressure slope [de/dT]
        /// </summary>
        /// <param name="temperature">Temperature in Celsius</param>
        /// <param name="saturatedVapourPressure">Saturated vapour pressure [kPa]</param>
        /// <returns>The saturation vapor pressure slope [de/dT]</returns>
        public static double GetSatVapSlope(double temperature, double saturatedVapourPressure)
        {
            const double A2 = 17.26939;
            const double A3 = 237.3;
            const double A4 = 21.87456;
            const double A5 = 265.5;
            
            if (temperature > 0) 
            { 
                return A2 * A3 / Pow(temperature + A3, 2) * saturatedVapourPressure;
            }
            else 
            {
                return A4 * A5 / Pow(temperature + A5, 2) * saturatedVapourPressure;
            }
        }

        /// <summary>
        /// Calculates latent heat of vaporization [MJ/kg]
        /// </summary>
        /// <param name="temperature">Temperature in Celsius</param>
        /// <returns>Latent heat of vaporization [MJ/kg]</returns>
        public static double GetLatentHeatVaporization(double temperature)
        {
            return 2.495 - 0.002361 * temperature;
        }

        /// <summary>
        /// Returns latent psychrometric constant  [kPa/K]
        /// </summary>
        /// <param name="atmosphericPressure">Atmospheric pressure [kPa]</param>
        /// <param name="latentHeatOfVaporization">Latent heat of vaporization [MJ/kg]</param>
        /// <returns>Psychrometric 'constant' [kPa/K]</returns>
        public static double GetPsychrometricConstant(double atmosphericPressure, double latentHeatOfVaporization)
        {
            return SPH_AIR/AIR_H20_MW_RAT* atmosphericPressure/latentHeatOfVaporization;//[kPa/K];
        }

        /// <summary>
        /// Calculates the wet-bulb temperature based on atmospheric pressure, air temperature, 
        /// and relative humidity.
        /// </summary>
        /// <remarks>
        /// The wet-bulb temperature is the lowest temperature that can be reached by 
        /// evaporative cooling of a water surface. This method uses an iterative approach to 
        /// solve for the wet-bulb temperature and assumes input values are within typical 
        /// atmospheric ranges.
        /// </remarks>
        /// <param name="atmosphericPressure">
        /// The atmospheric pressure [kPa] at which the measurement is taken. Must be a positive value.</param>
        /// <param name="airTemperature">
        /// The air temperature, in degrees Celsius, for which to calculate the wet-bulb temperature.
        /// </param>
        /// <param name="relativeHumidity">
        /// The relative humidity as a fraction between 0.0 and 1.0, where 1.0 represents 100% humidity.
        /// </param>
        /// <returns>
        /// The wet-bulb temperature, in degrees Celsius, corresponding to the specified atmospheric conditions.
        /// </returns>
        public static double GetWetBulbTemperature(double atmosphericPressure, double airTemperature, double relativeHumidity)
        {
            double latentHeatOfVaporization = GetLatentHeatVaporization(airTemperature);
            double gamma = GetPsychrometricConstant(atmosphericPressure, latentHeatOfVaporization);
            double saturatedVaporPressure = GetSaturatedVaporPressure(airTemperature);
            double actualVaporPressure = saturatedVaporPressure * relativeHumidity;

            double change = 10;
            double tolerance = 0.025;
            double Twet = airTemperature; //initial guess
            double F, dF, e_wet;

            // Solve using Newton's method (usually ~2-3 iters)
            while (Abs(change) > tolerance) 
            {
                e_wet=GetSaturatedVaporPressure(Twet);
                F=airTemperature-Twet-1/gamma* (e_wet-actualVaporPressure);
                dF=-1.0-1/gamma* (GetSatVapSlope(Twet, e_wet));
                change=-F/dF;
                Twet+=change;
            }
            return Twet;
        }

        /// <summary>
        /// Returns air density [kg/m3]
        /// </summary>
        /// <param name="airTemperature">Temperature in Celsius</param>
        /// <param name="atmosphericPressure">Atmospheric pressure [kPa]</param>
        /// <returns>Air density [kg/m3]</returns>
        public static double GetAirDensity(double airTemperature, double atmosphericPressure)
        {
            double e = GetSaturatedVaporPressure(airTemperature);
            return (atmosphericPressure - 0.378 * e) / (DRY_GAS_CONST * (airTemperature + ZERO_CELSIUS)) * GRAMS_PER_KG;
        }

        /// <summary>
        /// Converts relative humidity to specific humidity
        /// </summary>
        /// <param name="relativeHumidity">
        /// relative humidity [0-1]
        /// </param>
        /// <param name="atmosphericPressure">
        /// Atmospheric pressure [kPa]
        /// </param>
        /// <param name="temperature">
        /// air temperature [Celsius]
        /// </param>
        /// <returns></returns>
        public static double GetSpecificHumidity(double relativeHumidity, double atmosphericPressure, double temperature)
        {
            double e_a = relativeHumidity * GetSaturatedVaporPressure(temperature);
            return AIR_H20_MW_RAT* e_a/(atmosphericPressure- e_a* (1-AIR_H20_MW_RAT));
        }

        /// <summary>
        /// Converts passed temperature from Celsius to Farenheit
        /// </summary>
        /// <param name="temperatureInCelsius">Temperature in Celsius</param>
        /// <returns>The temperature in Fahrenheit</returns>
        public static double CelsiusToFarenheit(double temperatureInCelsius)
        {
            return 1.8*temperatureInCelsius+32.0;
        }

        /// <summary>
        /// Calculates vertical transport efficiency of water vapor by turbulent eddies [m s^2/kg]
        /// </summary>
        /// <param name="atmosphericPressure">
        /// Atmospheric pressure [kPa]
        /// </param>
        /// <param name="measurementHeight">
        /// Measurement height [m]
        /// </param>
        /// <param name="zeroPlaneDisplacement">
        /// Zero plane displacement [m]
        /// </param>
        /// <param name="roughnessCoefficient">
        /// Coefficient of roughness
        /// </param>
        /// <returns>
        /// Vertical transport efficiency [m s^2/kg]
        /// </returns>
        public static double GetVerticalTransportEfficiency(double atmosphericPressure, double measurementHeight, double zeroPlaneDisplacement, double roughnessCoefficient)
        {
            double numer = AIR_H20_MW_RAT* DENSITY_AIR;
            double denom = atmosphericPressure* DENSITY_WATER*(1.0/Pow(VON_KARMAN,2)*(Pow((Log((measurementHeight - zeroPlaneDisplacement)/roughnessCoefficient)),2)));

            return numer/denom;
        }

        /// <summary>
        /// Calculates atmospheric conductivity [mm/s] for ET calculations
        /// </summary>
        /// <param name="windVelocity">
        /// Measurement height of wind vel [m] - must be greater than zero plane displacement
        /// </param>
        /// <param name="windMeasurementHeight">
        /// Measurement height of wind vel [m] - must be greater than zero plane displacement
        /// </param>
        /// <param name="zeroPlaneDisplacement">
        /// Zero plane displacement [m]
        /// </param>
        /// <param name="roughnessHeight">
        /// Roughness height [m]
        /// </param>
        /// <param name="vapourRoughnessHeight">
        /// Vapour roughness height [m]
        /// </param>
        /// <returns></returns>
        public static double CalcAtmosphericConductance(double windVelocity, double windMeasurementHeight, double zeroPlaneDisplacement, double roughnessHeight, double vapourRoughnessHeight)
        {
            if (zeroPlaneDisplacement==0.0)
            {
                return 0.0;
            }
  
            double result=(windVelocity* MM_PER_METER* Pow(VON_KARMAN,2));
            result/= (Log((windMeasurementHeight-zeroPlaneDisplacement)/roughnessHeight)*Log((windMeasurementHeight-zeroPlaneDisplacement)/vapourRoughnessHeight));

            return result;
        }

        /// <summary>
        /// Calculates dew point temperature, in celsius
        /// </summary>
        /// <param name="airTemperature">
        /// Air temperature in Celsius
        /// </param>
        /// <param name="relativeHumidity">
        /// Relative humidity [0..1]
        /// </param>
        /// <returns>
        /// Dew point temperature
        /// </returns>
        public static double GetDewPointTemp(double airTemperature, double relativeHumidity)
        {
            const double a = 17.27;
            const double b = 237.7;//[C]

            double tmp = (a * airTemperature / (b + airTemperature)) + Log(relativeHumidity);
            return b* tmp/(a-tmp);
        }


        /// <summary>
        /// Calculates dew point temperature
        /// </summary>
        /// <param name="vapourPressure">vapour pressure [kPa]</param>
        /// <returns>Dew point temperature [C]</returns>
        public static double GetDewPointTemp(double vapourPressure)
        {
            double numer=  Log(vapourPressure)+0.4926;
            double denom =  0.0708 - 0.00421*Log(vapourPressure);

            return numer/denom;
        }

        /// <summary>
        /// Converts volumetric enthalpy of water/ice only [MJ/m3 water] to temperature
        /// </summary>
        /// <param name="volumetricEnthapy">
        /// volumetric enthapy [MJ/m3 water]
        /// </param>
        /// <returns>
        /// Water temperature [C]
        /// </returns>
        public static double ConvertVolumetricEnthalpyToTemperature(double volumetricEnthapy)
        {

            if (g_disable_freezing)
            {
                if (volumetricEnthapy / SPH_WATER / DENSITY_WATER > 40) 
                {
                    //upper limit - due to small volume, small energy roundoff error
                    return 40.0; 
                } 
                return volumetricEnthapy / SPH_WATER / DENSITY_WATER;
            }

            double g_freeze_temp = -0.0;
            double hvt = (g_freeze_temp * SPH_ICE - LH_FUSION) * DENSITY_WATER;//transition enthalpy [MJ/m3 water]

            if (volumetricEnthapy / SPH_WATER / DENSITY_WATER > 40) 
            {
                //upper limit - due to small volume, small energy roundoff error
                return 40.0; 
            } 
            if ((volumetricEnthapy - hvt) / SPH_ICE / DENSITY_ICE < -40) 
            {
                //lower limit
                return -40.0; 
            } 

            if (volumetricEnthapy > 0) 
            { 
                return volumetricEnthapy / SPH_WATER / DENSITY_WATER; 
            }
            else if (volumetricEnthapy > hvt) 
            { 
                return g_freeze_temp * volumetricEnthapy / hvt; 
            }
            else 
            { 
                return (volumetricEnthapy - hvt) / SPH_ICE / DENSITY_ICE; 
            }
        }

        /// <summary>
        /// Converts volumetric enthalpy of water/ice only [MJ/m3 water] to ice fraction
        /// </summary>
        /// <param name="volumetricEnthapy">
        /// volumetric enthapy [MJ/m3 water]
        /// </param>
        /// <returns>
        /// Ice fraction [0..1]
        /// </returns>
        public static double ConvertVolumetricEnthalpyToIceContent(double volumetricEnthapy)
        {
            if (g_disable_freezing) 
            { 
                return 0; 
            }

            double g_freeze_temp = -0.0;
            // transition enthalpy [MJ/m3 water]
            double hvt = (g_freeze_temp * SPH_ICE - LH_FUSION) * DENSITY_WATER;

            if (volumetricEnthapy > 0) 
            { 
                return 0; 
            }
            else if (volumetricEnthapy > hvt) 
            { 
                return volumetricEnthapy / hvt; 
            }
            else 
            { 
                return 1.0; 
            }
        }

        /// <summary>
        /// calculates dT/dh corresponding to volumetric enthalpy hv
        /// </summary>
        /// <param name="hv">
        /// volumetric enthapy [MJ/m3 water]
        /// </param>
        /// <returns>
        /// dT/dh [C-m3/MJ]
        /// </returns>
        public static double TemperatureEnthalpyDerivative(double hv)
        {
            if (g_disable_freezing) 
            { 
                return 1.0 / SPH_WATER / DENSITY_WATER; 
            }

            double g_freeze_temp = -0.0;
            // transition enthalpy [MJ/m3 water]
            double hvt = (g_freeze_temp * SPH_ICE - LH_FUSION) * DENSITY_WATER; 

            // Derivative of temperature with respect to volumetric enthalpy
            if (hv > 0) 
            { 
                return 1.0 / SPH_WATER / DENSITY_WATER; 
            }
            else if (hv > hvt) 
            { 
                return g_freeze_temp / hvt; 
            }
            else 
            {
                return 1.0 / SPH_ICE / DENSITY_ICE; 
            }
        }

        public static double ConvertTemperatureToVolumetricEnthalpy(double T, double pctfroz)
        {
            if (g_disable_freezing) 
            { 
                return T * SPH_WATER * DENSITY_WATER; 
            }

            double g_freeze_temp = -0.0;
            // transition enthalpy [MJ/m3 water]
            double hvt = (g_freeze_temp * SPH_ICE - LH_FUSION) * DENSITY_WATER;

            if ((g_freeze_temp == 0.0) && (Abs(T) < REAL_SMALL))
            {
                // along zero line
                return pctfroz * hvt;
            } 
            else if (T > 0) 
            { 
                return T * SPH_WATER * DENSITY_WATER; 
            }
            else if ((hvt < 0.0) && (T > g_freeze_temp)) 
            { 
                return pctfroz * hvt; 
            }
            else 
            { 
                return T * SPH_ICE * DENSITY_ICE + hvt; 
            } 
        }



    }
}
