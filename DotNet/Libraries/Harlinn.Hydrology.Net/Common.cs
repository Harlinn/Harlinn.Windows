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

using System.Globalization;
using static Harlinn.Hydrology.Constants;
using static Harlinn.Mathematics.Net.Common;
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


        /// <summary>
        /// Returns true if the given year is a leap year for the specified calendar.
        /// </summary>
        public static bool IsLeapYear(int year, Calendars calendar)
        {
            bool leap = false;

            // handle default CALENDAR_PROLEPTIC_GREGORIAN first for code efficiency
            if (calendar == Calendars.CALENDAR_PROLEPTIC_GREGORIAN)
            {
                leap = (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
                return leap;
            }

            if (calendar == Calendars.CALENDAR_365_DAY) return false;
            if (calendar == Calendars.CALENDAR_366_DAY) return true;

            // other calendars
            if ((calendar == Calendars.CALENDAR_JULIAN || calendar == Calendars.CALENDAR_GREGORIAN) && (year % 4 == 0))
            {
                leap = true;
                if ((calendar == Calendars.CALENDAR_GREGORIAN) && (year % 100 == 0) && (year % 400 != 0) && (year > 1583))
                {
                    leap = false;
                }
            }
            return leap;
        }

        /// <summary>
        /// Converts model_time and start date/year into full TimeStruct (fills fields similar to C++ JulianConvert).
        /// </summary>
        public static void JulianConvert(double model_time, double start_date, int start_year, Calendars calendar, out TimeStruct tt)
        {
            tt = new TimeStruct();
            int leap = 0;
            string mon;
            double sum, days, ddate;
            double dday;
            int dmonth, dyear;

            // handles daily roundoff error
            if ((model_time - Math.Floor(model_time)) > (1 - TIME_CORRECTION))
            {
                model_time = Math.Floor(model_time + TIME_CORRECTION);
            }
            // handles hourly roundoff error
            if ((model_time * HR_PER_DAY - Math.Floor(model_time * HR_PER_DAY)) > (1.0 - TIME_CORRECTION) * HR_PER_DAY)
            {
                model_time = Math.Floor(HR_PER_DAY * (model_time + TIME_CORRECTION)) / HR_PER_DAY;
            }

            double dec_date = start_date + model_time; // decimal day-of-year relative to start year
            dyear = start_year;
            ddate = dec_date;

            if (IsLeapYear(dyear, calendar)) leap = 1;
            while (ddate >= (365 + leap))
            {
                ddate -= (365.0 + leap);
                dyear++;
                leap = 0;
                if (IsLeapYear(dyear, calendar)) leap = 1;
            }
            // ddate is decimal julian date from Jan 1 0:00:00 of current dyear

            dmonth = 1; days = 31; sum = 31 - TIME_CORRECTION; mon = "Jan";
            if (ddate >= sum) { dmonth += 1; days = 28 + leap; sum += days; mon = "Feb"; }
            if (ddate >= sum) { dmonth += 1; days = 31; sum += days; mon = "Mar"; }
            if (ddate >= sum) { dmonth += 1; days = 30; sum += days; mon = "Apr"; }
            if (ddate >= sum) { dmonth += 1; days = 31; sum += days; mon = "May"; }
            if (ddate >= sum) { dmonth += 1; days = 30; sum += days; mon = "Jun"; }
            if (ddate >= sum) { dmonth += 1; days = 31; sum += days; mon = "Jul"; }
            if (ddate >= sum) { dmonth += 1; days = 31; sum += days; mon = "Aug"; }
            if (ddate >= sum) { dmonth += 1; days = 30; sum += days; mon = "Sep"; }
            if (ddate >= sum) { dmonth += 1; days = 31; sum += days; mon = "Oct"; }
            if (ddate >= sum) { dmonth += 1; days = 30; sum += days; mon = "Nov"; }
            if (ddate >= sum) { dmonth += 1; days = 31; sum += days; mon = "Dec"; }

            dday = ddate - sum + days; // decimal days since 0:00 on first of month

            tt.model_time = model_time;
            tt.julian_day = ddate;
            tt.day_of_month = (int)(Math.Ceiling(dday + REAL_SMALL));
            if (tt.day_of_month == 0) tt.day_of_month = 1;
            tt.month = dmonth;
            tt.year = dyear;

            tt.day_changed = false;
            if ((model_time <= PRETTY_SMALL) || (tt.julian_day - Math.Floor(tt.julian_day + TIME_CORRECTION) < 0.001))
            {
                tt.day_changed = true;
            }

            tt.date_string = string.Format("{0:0000}-{1:00}-{2:00}", dyear, tt.month, tt.day_of_month);
            tt.leap_yr = IsLeapYear(tt.year, calendar);
        }

        /// <summary>
        /// Returns time-of-day string for decimal date (e.g., day=124.3 -> "07:12").
        /// </summary>
        public static string DecDaysToHours(double dec_date, bool truncate)
        {
            double hours = (dec_date - Math.Floor(dec_date)) * 24.0;
            double mind = (hours - Math.Floor(hours)) * 60.0;
            double sec = (mind - Math.Floor(mind)) * 60.0;

            int hr = (int)Math.Floor(hours);
            int min = (int)Math.Floor(mind);

            if (sec >= 59.995) { min++; sec = 0.0; }
            if (min == 60) { hr++; min = 0; }
            if (hr == 24) { hr = 0; }

            if (truncate)
            {
                return string.Format("{0:00}:{1:00}:{2:00}", hr, min, (int)sec);
            }
            else
            {
                return string.Format(CultureInfo.InvariantCulture, "{0:00}:{1:00}:{2:00.00}", hr, min, sec);
            }
        }

        /// <summary>
        /// Parse ISO date and time strings into TimeStruct.
        /// sDate must be "yyyy-mm-dd" (or "yyyy/mm/dd"). sTime is "hh:mm:ss" (or "h:mm:ss" accepted).
        /// </summary>
        public static TimeStruct DateStringToTimeStruct(string sDate, string sTime, Calendars calendar)
        {
            ArgumentNullException.ThrowIfNull(sDate, nameof(sDate));

            if (sDate.Length != 10)
            {
                throw new ArgumentException("DateStringToTimeStruct: Invalid date format used: " + sDate, nameof(sDate));
            }
            if (sTime == null || sTime.Length < 7)
            { 
                throw new ArgumentException("DateStringToTimeStruct: Invalid time format used (hourstamp): " + sTime, nameof(sTime));
            }

            var tt = new TimeStruct();
            tt.date_string = sDate;
            tt.year = ParseIntSafe(sDate.Substring(0, 4), "DateStringToTimeStruct: year parse");
            tt.month = ParseIntSafe(sDate.Substring(5, 2), "DateStringToTimeStruct: month parse");
            if (tt.month > 12)
            {
                throw new ArgumentOutOfRangeException(nameof(sDate), "DateStringToTimeStruct: Invalid time format used (month>12): " + sDate);
            }
            tt.day_of_month = ParseIntSafe(sDate.Substring(8, 2), "DateStringToTimeStruct: day parse");
            tt.model_time = 0.0;
            tt.leap_yr = IsLeapYear(tt.year, calendar);

            tt.julian_day = tt.day_of_month - 1;
            // add month offsets
            if (tt.month >= 2) tt.julian_day += 31;
            if (tt.month >= 3) tt.julian_day += 28;
            if (tt.month >= 4) tt.julian_day += 31;
            if (tt.month >= 5) tt.julian_day += 30;
            if (tt.month >= 6) tt.julian_day += 31;
            if (tt.month >= 7) tt.julian_day += 30;
            if (tt.month >= 8) tt.julian_day += 31;
            if (tt.month >= 9) tt.julian_day += 31;
            if (tt.month >= 10) tt.julian_day += 30;
            if (tt.month >= 11) tt.julian_day += 31;
            if (tt.month == 12) tt.julian_day += 30;
            if ((tt.leap_yr) && (tt.month > 2)) tt.julian_day += 1;

            int leap = tt.leap_yr ? 1 : 0;
            if (tt.day_of_month > (DAYS_PER_MONTH[tt.month - 1] + leap))
            {
                throw new ArgumentOutOfRangeException(nameof(sDate), "DateStringToTimeStruct: Invalid time format used - exceeded max day of month: " + sDate);
            }
            if(tt.month <= 0)
            {
                throw new ArgumentOutOfRangeException(nameof(sDate), "DateStringToTimeStruct: Invalid time format used - negative or zero month: " + sDate);
            }

            // normalize time string "h:mm:ss" -> "hh:mm:ss"
            if (sTime.Length >= 2 && sTime[1] == ':')
            {
                sTime = "0" + sTime;
            }
            if(sTime.Length < 8 || sTime[2] != ':')
            {
                throw new ArgumentException("DateStringToTimeStruct: Invalid time format used: " + sTime, nameof(sTime));
            }
            if(sTime.Length < 8 || sTime[5] != ':')
            {
                throw new ArgumentException("DateStringToTimeStruct: Invalid time format used: " + sTime, nameof(sTime));
            }

            int hr = ParseIntSafe(sTime.Substring(0, 2), "hour parse");
            int min = ParseIntSafe(sTime.Substring(3, 2), "min parse");
            double sec = ParseDoubleSafe(sTime.Substring(6, Math.Min(6, sTime.Length - 6)), "sec parse");

            tt.julian_day += (double)hr / HR_PER_DAY;
            tt.julian_day += (double)min / (HR_PER_DAY * 60.0);
            tt.julian_day += sec / SEC_PER_DAY;

            // reprocess to fill tt fields consistently with JulianConvert
            JulianConvert(0.0, tt.julian_day, tt.year, calendar, out tt);
            return tt;
        }

        private static int ParseIntSafe(string s, string context)
        {
            if (!int.TryParse(s, NumberStyles.Integer, CultureInfo.InvariantCulture, out int v))
            {
                throw new ArgumentException(context + ": invalid integer '" + s + "'");
            }
            return v;
        }
        private static double ParseDoubleSafe(string s, string context)
        {
            if (!double.TryParse(s, NumberStyles.Float | NumberStyles.AllowThousands, CultureInfo.InvariantCulture, out double v))
            {
                throw new ArgumentException(context + ": invalid double '" + s + "'");
            }
            return v;
        }

        /// <summary>
        /// Returns true if julian_day is between julian_start and julian_end (inclusive).
        /// Wrap-around is supported.
        /// </summary>
        public static bool IsInDateRange(double julian_day, int julian_start, int julian_end)
        {
            if (julian_start < julian_end)
            {
                return (julian_day >= julian_start) && (julian_day <= julian_end);
            }
            else
            {
                return (julian_day >= julian_start) || (julian_day <= julian_end);
            }
        }

        /// <summary>
        /// Returns zero-indexed julian day (0..364/365) for date strings in multiple formats: Mmm-dd, mm-dd or integer julian day.
        /// </summary>
        public static int GetJulianDayFromMonthYear(string date_str, Calendars calendar)
        {
            if (date_str.Length == 3 && date_str.Length >= 2 && date_str[1] == '-') // m-d
            {
                string fulldate_str = "1999-0" + date_str.Substring(0, 1) + "-0" + date_str.Substring(2, 1);
                TimeStruct tt = DateStringToTimeStruct(fulldate_str, "00:00:00", calendar);
                return (int)tt.julian_day;
            }
            else if (date_str.Length >= 2 && date_str.Length >= 2 && date_str[1] == '-') // m-dd
            {
                string fulldate_str = "1999-0" + date_str;
                TimeStruct tt = DateStringToTimeStruct(fulldate_str, "00:00:00", calendar);
                return (int)tt.julian_day;
            }
            else if (date_str.Length == 4 && date_str[2] == '-') // mm-d
            {
                string fulldate_str = "1999-" + date_str.Substring(0, 3) + "0" + date_str.Substring(3, 1);
                TimeStruct tt = DateStringToTimeStruct(fulldate_str, "00:00:00", calendar);
                return (int)tt.julian_day;
            }
            else if (date_str.Length == 5 && date_str[2] == '-') // mm-dd
            {
                string fulldate_str = "1999-" + date_str;
                TimeStruct tt = DateStringToTimeStruct(fulldate_str, "00:00:00", calendar);
                return (int)tt.julian_day;
            }
            else if (date_str.Length >= 3 && date_str.Length > 3 && date_str[3] == '-') // Mmm-dd
            {
                string[] months = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
                string fulldate_str = "";
                for (int mon = 0; mon < 12; mon++)
                {
                    if (date_str.Substring(0, 3) == months[mon])
                    {
                        if (mon < 9) fulldate_str = "0";
                        if (date_str.Length <= 5) // Apr-1
                            fulldate_str = fulldate_str + (mon + 1).ToString() + "-0" + date_str.Substring(4, 1);
                        else
                            fulldate_str = fulldate_str + (mon + 1).ToString() + "-" + date_str.Substring(4, 2);
                    }
                }
                if (fulldate_str == "")
                {
                    throw new ArgumentException("GetJulianDayFromMonthYear: invalid month indicated in Mmm-dd date format");
                }
                fulldate_str = "1999-" + fulldate_str;
                TimeStruct tt = DateStringToTimeStruct(fulldate_str, "00:00:00", calendar);
                return (int)tt.julian_day;
            }
            else
            {
                if (!int.TryParse(date_str, out int val))
                {
                    throw new ArgumentException("GetJulianDayFromMonthYear: invalid format of julian date");
                }
                if (val == 0 || val > 365)
                {
                    throw new ArgumentException("GetJulianDayFromMonthYear: invalid format of julian date. Should be in 'Mmm-dd', 'mm-dd', or 1..365");
                }
                return val - 1; // convert to 0-index
            }
        }

        /// <summary>
        /// Parses NetCDF time-unit string and returns DateStringToTimeStruct result.
        /// (This function follows the logic of the original but is tolerant of slightly different formatting.)
        /// </summary>
        public static TimeStruct TimeStructFromNetCDFString(string unit_t_str, string timestr, Calendars calendar, out double timezone)
        {
            string tmp = unit_t_str;
            timezone = 0.0;
            int start = timestr.Length;
            start += 7; // first char of year YYYY (7 = length of " since ")

            if (start + 4 >= tmp.Length)
            {
                throw new ArgumentException("TimeStructFromNetCDFString: time unit string too short");
            }

            string dash = tmp.Substring(start + 4, 1);
            if (dash != "-")
            {
                throw new ArgumentException("CommonFunctions:TimeStructFromNetCDFString: time unit string has weird format!");
            }

            // attempt to fix some common formatting issues (mimic C++ behavior)
            if (start + 7 < tmp.Length && tmp.Substring(start + 7, 1) != "-")
            {
                tmp = tmp.Insert(start + 5, "0");
            }

            bool date_only = tmp.Length <= (start + 12);
            if (!date_only)
            {
                if (start + 10 < tmp.Length && tmp[start + 10] == 'T') tmp = tmp.Remove(start + 10, 1).Insert(start + 10, " ");
                if (start + 13 < tmp.Length && tmp[start + 13] != ':') tmp = tmp.Insert(start + 11, "0");
                if (start + 16 < tmp.Length && tmp[start + 16] != ':') tmp = tmp.Insert(start + 14, "0");
            }
            else
            {
                if (tmp.Length == start + 9) tmp = tmp.Insert(start + 8, "0");
            }

            string sDate = tmp.Substring(start, 10);
            string sTime = date_only ? "00:00:00" : tmp.Substring(start + 11, 8);

            if (tmp.Length - start == 26)
            {
                char sign = tmp[start + 22];
                string tzStr = tmp.Substring(start + 23, 4);
                if (int.TryParse(tzStr, out int tzVal))
                {
                    double tzDays = (double)tzVal / HR_PER_DAY / 100.0;
                    timezone = sign == '+' ? tzDays : -tzDays;
                }
            }

            return DateStringToTimeStruct(sDate, sTime, calendar);
        }

        /// <summary>
        /// Returns timezone string like " +0700" or "".
        /// </summary>
        public static string TimeZoneToString(int tz)
        {
            if (tz < 0)
            {
                if (tz < -9) return " -" + (-tz).ToString() + "00";
                return " -0" + (-tz).ToString() + "00";
            }
            else if (tz > 0)
            {
                if (tz > 9) return " +" + tz.ToString() + "00";
                return " +0" + tz.ToString() + "00";
            }
            return "";
        }

        /// <summary>
        /// Validates NetCDF time string roughly matching "[units] since YYYY-MM-DD [HH:MM:SS ...]".
        /// </summary>
        public static bool IsValidNetCDFTimeString(string time_string)
        {
            if (string.IsNullOrEmpty(time_string) || time_string.Length < 15) return false;
            int pos = time_string.IndexOf("since", StringComparison.Ordinal);
            if (pos == -1) return false;
            pos += 6;
            if (pos + 10 > time_string.Length) return false;
            string date_string = time_string.Substring(pos, 10);
            if (date_string.Length < 10) return false;
            if (date_string[4] != '-' && date_string[4] != '/') return false;
            if (date_string[7] != '-' && date_string[7] != '/') return false;
            if (time_string.Length < pos + 19) return true; // no timestamp present -> still acceptable
            string hr_string = time_string.Substring(pos + 11, 8);
            if (hr_string.Length < 8) return false;
            if (hr_string[2] != ':' || hr_string[5] != ':') return false;
            return true;
        }

        /// <summary>
        /// TimeDifference in days between two dates (jul_day2/year2 minus jul_day1/year1), accounting for leap years.
        /// </summary>
        public static double TimeDifference(double jul_day1, int year1, double jul_day2, int year2, Calendars calendar)
        {
            int leap, yr;
            double diff = jul_day2 - jul_day1;
            yr = year2 - 1;
            while (yr >= year1)
            {
                leap = IsLeapYear(yr, calendar) ? 1 : 0;
                diff += (365 + leap);
                yr--;
            }
            yr = year2;
            while (yr < year1)
            {
                leap = IsLeapYear(yr, calendar) ? 1 : 0;
                diff -= (365 + leap);
                yr++;
            }
            return diff;
        }

        /// <summary>
        /// Adds daysadded to jul_day1/year1 and returns resultant julian day and year via out parameters.
        /// </summary>
        public static void AddTime(double jul_day1, int year1, double daysadded, Calendars calendar, out double jul_day_out, out int year_out)
        {
            int yr = year1;
            jul_day_out = jul_day1;

            if (daysadded >= 0)
            {
                double daysleft = daysadded;
                while (true)
                {
                    double leap = IsLeapYear(yr, calendar) ? 1.0 : 0.0;
                    if ((jul_day_out + daysleft) < (365.0 + leap))
                    {
                        jul_day_out += daysleft;
                        year_out = yr;
                        break;
                    }
                    else
                    {
                        yr++;
                        daysleft -= (365.0 + leap - jul_day_out);
                        jul_day_out = 0.0;
                    }
                    if (daysleft < 0.0)
                    {
                        throw new ArgumentException("Invalid input to AddTime routine (negative julian day?)");
                    }
                }
            }
            else
            {
                double daysleft = -daysadded;
                while (true)
                {
                    if ((jul_day_out - daysleft) >= 0.0)
                    {
                        jul_day_out -= daysleft;
                        year_out = yr;
                        return;
                    }
                    else
                    {
                        yr--;
                        double leap = IsLeapYear(yr, calendar) ? 1.0 : 0.0;
                        daysleft -= jul_day_out;
                        if (daysleft < (365 + leap))
                        {
                            jul_day_out = (365 + leap) - daysleft;
                            year_out = yr;
                            break;
                        }
                        else
                        {
                            jul_day_out = 0.0;
                            daysleft -= (365 + leap);
                        }
                    }
                    if (daysleft < 0.0)
                    {
                        throw new ArgumentException("Invalid input to AddTime routine (negative julian day?)");
                    }
                }
            }

            // Handle Gregorian calendar historical gap (4 Oct 1582 -> 15 Oct 1582)
            if ((calendar == Calendars.CALENDAR_GREGORIAN) &&
                ((year1 == 1582 && jul_day1 <= 277) || (year1 < 1582)) &&
                ((year_out > 1582) || ((year_out == 1582) && (jul_day_out >= 278))))
            {
                double tmp_day = jul_day_out;
                int tmp_yr = year_out;
                AddTime(tmp_day, tmp_yr, 10.0, calendar, out jul_day_out, out year_out);
                return;
            }

            return;
        }

        /// <summary>
        /// Converts a calendar name string to calendar constant.
        /// </summary>
        public static Calendars StringToCalendar(string cal_chars)
        {
            if (cal_chars == null)
            {
                throw new ArgumentNullException(nameof(cal_chars), "CommonFunctions: StringToCalendar: null calendar");
            }
            string str = cal_chars.ToUpperInvariant();
            if (str == "STANDARD" || str == "GREGORIAN")
            {
                return Calendars.CALENDAR_GREGORIAN;
            }
            if (str == "PROLEPTIC_GREGORIAN")
            {
                return Calendars.CALENDAR_PROLEPTIC_GREGORIAN;
            }
            if (str == "NOLEAP" || str == "NO_LEAP" || str == "365_DAY")
            {
                return Calendars.CALENDAR_365_DAY;
            }
            if (str == "JULIAN")
            {
                return Calendars.CALENDAR_JULIAN;
            }
            if (str == "ALL_LEAP" || str == "366_DAY")
            {
                return Calendars.CALENDAR_366_DAY;
            }
            throw new ArgumentException("StringToCalendar: Unknown calendar specified!", nameof(cal_chars));
        }

        /// <summary>
        /// Round timestep to nearest fractional day that divides 1 day evenly.
        /// </summary>
        public static double FixTimestep(double tstep)
        {
            double tmp = Math.Round(1.0 / tstep);
            if (Abs(tstep * tmp - 1.0) > 0.1)
            {
                throw new ArgumentException("FixTimestep: timesteps and time intervals must evenly divide into one day");
            }
            return 1.0 / tmp;
        }

        /// <summary>
        /// True if string looks like ISO date yyyy-mm-dd or yyyy/mm/dd
        /// </summary>
        public static bool IsValidDateString(string sDate)
        {
            if (string.IsNullOrEmpty(sDate)) return false;
            return (sDate.Length == 10) &&
                   (sDate[4] == '/' || sDate[4] == '-') &&
                   (sDate[7] == '/' || sDate[7] == '-');
        }

        /// <summary>
        /// Returns current machine time in "YYYY-MM-DD hh:mm:ss" format.
        /// </summary>
        public static string GetCurrentMachineTime()
        {
            DateTime now = DateTime.Now;
            return now.ToString("yyyy-MM-dd HH:mm:ss", CultureInfo.InvariantCulture);
        }

        /// <summary>
        /// Interpolate monthly value for given TimeStruct and options.
        /// </summary>
        public static double InterpolateMo(double[] aVal /* length 12 */, TimeStruct tt, Options Options)
        {
            double wt;
            int leap = 0, mo, nextmo;
            int day = tt.day_of_month;
            int month = tt.month;
            int year = tt.year;

            if (Options.month_interp == MonthlyInterp.MONTHINT_UNIFORM)
            {
                return aVal[month - 1];
            }
            else if (Options.month_interp == MonthlyInterp.MONTHINT_LINEAR_FOM)
            {
                mo = month - 1;
                nextmo = mo + 1;
                if (nextmo == 12) nextmo = 0;
                leap = (IsLeapYear(year, Options.calendar) && mo == 1) ? 1 : 0;
                wt = 1.0 - (double)(day) / (DAYS_PER_MONTH[mo] + leap);
                return wt * aVal[mo] + (1 - wt) * aVal[nextmo];
            }
            else if (Options.month_interp == MonthlyInterp.MONTHINT_LINEAR_21 || Options.month_interp == MonthlyInterp.MONTHINT_LINEAR_MID)
            {
                double pivot = 0.0;
                if (Options.month_interp == MonthlyInterp.MONTHINT_LINEAR_21) pivot = 21;
                else
                {
                    pivot = 0.5 * DAYS_PER_MONTH[month - 1];
                    if ((IsLeapYear(year, Options.calendar)) && (month == 2)) pivot += 0.5;
                }

                int moIdx, nextIdx;
                if (day <= pivot)
                {
                    moIdx = month - 2;
                    nextIdx = moIdx + 1;
                    if (moIdx == -1) { moIdx = 11; nextIdx = 0; }
                    leap = (IsLeapYear(year, Options.calendar) && moIdx == 1) ? 1 : 0;
                    wt = 1.0 - (double)(day + (DAYS_PER_MONTH[moIdx] + leap) - pivot) / (double)(DAYS_PER_MONTH[moIdx] + leap);
                }
                else
                {
                    moIdx = month - 1;
                    nextIdx = moIdx + 1;
                    int lastmo = moIdx - 1;
                    if (lastmo == -1) lastmo = 11;
                    if (nextIdx == 12) nextIdx = 0;
                    leap = (IsLeapYear(year, Options.calendar) && lastmo == 1) ? 1 : 0;
                    wt = 1.0 - (double)(day - pivot) / (double)(DAYS_PER_MONTH[lastmo] + leap);
                }

                int useMo = (day <= pivot) ? ((month - 2 == -1) ? 11 : month - 2) : (month - 1);
                int useNext = (useMo + 1) % 12;
                return wt * aVal[useMo] + (1 - wt) * aVal[useNext];
            }

            return 0.0;
        }

        public static HRUType StringToHRUType(string s)
        {
            string sup = s.ToUpperInvariant();

            if (sup == "GLACIER") { return HRUType.HRU_GLACIER; }
            else if (sup == "LAKE") { return HRUType.HRU_LAKE; }
            else if (sup == "WATER") { return HRUType.HRU_WATER; }
            else if (sup == "ROCK") { return HRUType.HRU_ROCK; }
            else if (sup == "PAVEMENT") { return HRUType.HRU_ROCK; }
            else if (sup == "WETLAND") { return HRUType.HRU_WETLAND; }
            else if (sup == "STANDARD") { return HRUType.HRU_STANDARD; }


            return HRUType.HRU_INVALID_TYPE;
        }


    }
}
