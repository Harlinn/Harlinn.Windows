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

using Serilog;
using static Harlinn.Hydrology.Constants;
using static System.Math;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Universal Transverse Mercator utility class
    /// </summary>
    /// <remarks>
    /// The Universal Transverse Mercator (UTM) is a projected coordinate system 
    /// that divides the world into 60 zones to map the Earth's surface onto a plane, 
    /// minimizing distortion. It provides a grid of coordinates, called "northing" 
    /// and "easting," measured in meters within a specific zone. This system is based 
    /// on the Transverse Mercator map projection and is widely used in surveying, 
    /// navigation, and mapping for its precision over large areas.  
    /// </remarks>
    public class UTMUtils
    {
        // Ellipsoid model constants (actual values here are for WGS84) 

        /// <summary>
        /// Ellipsoid model constant for WGS 1984
        /// </summary>
        const double sm_a = 6378137.0;
        /// <summary>
        /// Ellipsoid model constant for WGS 1984
        /// </summary>
        const double sm_b = 6356752.314;

        /// <summary>
        /// UTM scale factor for WGS 1984
        /// </summary>
        const double UTMScaleFactor = 0.9996;

        /// <summary>
        /// Computes ellipsoidal distance from the equator to a point at a given latitude
        /// </summary>
        /// <param name="phi">
        /// phi [in] Latitude of point [rad]
        /// </param>
        /// <returns></returns>
        public static double ArcLengthOfMeridian(double phi)
        {
            //double alpha, beta, gamma, delta, epsilon, n;

            double n = (sm_a - sm_b) / (sm_a + sm_b);
            double alpha = ((sm_a + sm_b) / 2.0)* (1.0 + (Math.Pow(n, 2.0) / 4.0) + (Math.Pow(n, 4.0) / 64.0));
            double beta = (-3.0 * n / 2.0) + (  9.0 * Math.Pow(n, 3.0) / 16.0 ) + ( -3.0 * Math.Pow(n, 5.0) / 32.0 );
            double gamma = ( 15.0 * Math.Pow(n, 2.0) / 16.0 ) + (-15.0 * Math.Pow(n, 4.0) / 32.0 );
            double delta = (-35.0 * Math.Pow(n, 3.0) / 48.0 ) + (105.0 * Math.Pow(n, 5.0) / 256.0);
            double epsilon = (315.0 * Math.Pow(n, 4.0) / 512.0);

            return alpha
                * (phi + (beta* Math.Sin(2.0 * phi))
                        + (gamma* Math.Sin(4.0 * phi))
                        + (delta* Math.Sin(6.0 * phi))
                        + (epsilon* Math.Sin(8.0 * phi)));
        }

        public static double UTMCentralMeridian(int zone)
        {
          return (-183.0 + (zone* 6.0))*DEGREES_TO_RADIANS;
        }


        /// <summary>
        /// Computes the footpoint latitude for use in converting transver Mercator coordinates to ellipsoidal coordinates
        /// </summary>
        public static double FootpointLatitude(double utmNorthingLatitude)
        {
            double y_, alpha_, beta_, gamma_, delta_, epsilon_, n;

            n = (sm_a - sm_b) / (sm_a + sm_b);// (Eq. 10.18)
            alpha_ = ((sm_a + sm_b) / 2.0) * (1 + (Math.Pow(n, 2.0) / 4) + (Math.Pow(n, 4.0) / 64));
            y_ = utmNorthingLatitude / alpha_;
            beta_ = ( 3.0 * n  / 2.0  ) + ( -27.0 * Math.Pow(n, 3.0) / 32.0) + (269.0 * Math.Pow(n, 5.0) / 512.0);
            gamma_ = (  21.0 * Math.Pow(n, 2.0) / 16.0 ) + ( -55.0 * Math.Pow(n, 4.0) / 32.0);
            delta_ = ( 151.0 * Math.Pow(n, 3.0) / 96.0 ) + (-417.0 * Math.Pow(n, 5.0) / 128.0);
            epsilon_= (1097.0 * Math.Pow(n, 4.0) / 512.0);

            return y_ + (beta_* Math.Sin(2.0 * y_))
                    + (gamma_* Math.Sin(4.0 * y_))
                    + (delta_* Math.Sin(6.0 * y_))
                    + (epsilon_* Math.Sin(8.0 * y_));
        }

        /// <summary>
        /// Converts a latitude/longitude pair to (x,y) coordintes in the Transverse Mercator (not UTM!) projection
        /// </summary>
        /// <param name="phi">
        /// Latitude of point [rad]
        /// </param>
        /// <param name="lambda">
        /// Longitude of point [rad]
        /// </param>
        /// <param name="lambda0">
        /// Central meridian [rad]
        /// </param>
        /// <param name="x">
        /// x coordinate of point (transverse mercator)
        /// </param>
        /// <param name="y">
        /// y coordinate of point (transverse mercator)
        /// </param>
        public static void MapLatLonToXY(double phi, double lambda, double lambda0, out double x, out double y)
        {
            double N, nu2, ep2, t, t2, l;
            double l3coef, l4coef, l5coef, l6coef, l7coef, l8coef;

            ep2 = (Pow(sm_a, 2.0) - Pow(sm_b, 2.0)) / Pow(sm_b, 2.0);
            nu2 = ep2* Pow(Cos (phi), 2.0);
            N = Pow(sm_a, 2.0) / (sm_b* Sqrt (1 + nu2));
            t = Tan(phi);
            t2 = t* t;

            l = lambda - lambda0;

            // Precalculate coefficients for l**n in the equations below
            // so a normal human being can read the expressions for easting
            // and northing
            // --l **1 and l**2 have coefficients of 1.0 
            l3coef = 1.0 - t2 + nu2;
            l4coef = 5.0 - t2 + 9 * nu2 + 4.0 * (nu2* nu2);
            l5coef = 5.0 - 18.0 * t2 + (t2* t2) + 14.0 * nu2- 58.0 * t2* nu2;
                        l6coef = 61.0 - 58.0 * t2 + (t2* t2) + 270.0 * nu2- 330.0 * t2* nu2;
                        l7coef = 61.0 - 479.0 * t2 + 179.0 * (t2* t2) - (t2* t2 * t2);
                        l8coef = 1385.0 - 3111.0 * t2 + 543.0 * (t2* t2) - (t2* t2 * t2);

            // Calculate easting (x) 
            x = N* Cos(phi) * l
                        + (N / 6.0 * Pow(Cos (phi), 3.0) * l3coef* Pow(l, 3.0))
                        + (N / 120.0 * Pow(Cos (phi), 5.0) * l5coef* Pow(l, 5.0))
                        + (N / 5040.0 * Pow(Cos (phi), 7.0) * l7coef* Pow(l, 7.0));

            // Calculate northing (y) 
            y = ArcLengthOfMeridian(phi)
                        + (t / 2.0 * N* Pow(Cos(phi), 2.0) * Pow(l, 2.0))
                        + (t / 24.0 * N* Pow(Cos(phi), 4.0) * l4coef* Pow(l, 4.0))
                        + (t / 720.0 * N* Pow(Cos (phi), 6.0) * l6coef* Pow(l, 6.0))
                        + (t / 40320.0 * N* Pow(Cos (phi), 8.0) * l8coef* Pow(l, 8.0));
        }

        /// <summary>
        /// Converts (x,y) coordintes in the Transverse Mercator (not UTM!) to projection a latitude/longitude pair
        /// </summary>
        /// <param name="x">
        /// x ordinate of point (transverse mercator)
        /// </param>
        /// <param name="y">
        /// y ordinate of point (transverse mercator)
        /// </param>
        /// <param name="lambda0">
        /// Central meridian [rad]
        /// </param>
        /// <param name="phi">
        /// Latitude of point [rad]
        /// </param>
        /// <param name="lambda">
        /// Longitude of point [rad]
        /// </param>
        public static void MapXYToLatLon(double x,
                    double y,
                    double lambda0,
                    out double phi,
                    out double lambda)
        {
            double phif, Nf, Nfpow, nuf2, ep2, tf, tf2, tf4, cf;
            double x1frac, x2frac, x3frac, x4frac, x5frac, x6frac, x7frac, x8frac;
            double x2poly, x3poly, x4poly, x5poly, x6poly, x7poly, x8poly;

            // Get the value of phif, the footpoint latitude. 
            phif = FootpointLatitude(y);
            ep2 = (Math.Pow(sm_a, 2.0) - Math.Pow(sm_b, 2.0))/ Math.Pow(sm_b, 2.0);
            cf = Math.Cos(phif);
            nuf2 = ep2* Math.Pow(cf, 2.0);
            Nf = Math.Pow(sm_a, 2.0) / (sm_b* Math.Sqrt(1 + nuf2));
            Nfpow  = Nf;
            tf = Math.Tan(phif);
            tf2 = tf* tf;
            tf4 = tf2* tf2;

            // Precalculate fractional coefficients for x^n in the equations
            // below to simplify the expressions for latitude and longitude. 
            x1frac = 1.0 / (Nfpow* cf);
            Nfpow  *= Nf;
            x2frac = tf / (2.0 * Nfpow );
            Nfpow  *= Nf;
            x3frac = 1.0 / (6.0 * Nfpow* cf);
            Nfpow  *= Nf;
            x4frac = tf / (24.0 * Nfpow );
            Nfpow  *= Nf;
            x5frac = 1.0 / (120.0 * Nfpow* cf);
            Nfpow  *= Nf;
            x6frac = tf / (720.0 * Nfpow );
            Nfpow  *= Nf;
            x7frac = 1.0 / (5040.0 * Nfpow* cf);
            Nfpow  *= Nf;   // now equals Nf^8)
            x8frac = tf / (40320.0 * Nfpow );

            /* Precalculate polynomial coefficients for x**n.
                -- x**1 does not have a polynomial coefficient. */
            x2poly = -1.0 - nuf2;
            x3poly = -1.0 - 2 * tf2 - nuf2;
            x4poly = 5.0 + 3.0 * tf2 + 6.0 * nuf2 - 6.0 * tf2* nuf2
            - 3.0 * (nuf2* nuf2) - 9.0 * tf2* (nuf2* nuf2);
            x5poly = 5.0 + 28.0 * tf2 + 24.0 * tf4 + 6.0 * nuf2 + 8.0 * tf2* nuf2;
                x6poly = -61.0 - 90.0 * tf2 - 45.0 * tf4 - 107.0 * nuf2+ 162.0 * tf2* nuf2;
                x7poly = -61.0 - 662.0 * tf2 - 1320.0 * tf4 - 720.0 * (tf4* tf2);
            x8poly = 1385.0 + 3633.0 * tf2 + 4095.0 * tf4 + 1575 * (tf4* tf2);

            /* Calculate latitude */
            phi = phif + x2frac* x2poly * (x* x)
            + x4frac* x4poly * Math.Pow(x, 4.0)
            + x6frac* x6poly * Math.Pow(x, 6.0)
            + x8frac* x8poly * Math.Pow(x, 8.0);

                /* Calculate longitude */
                lambda = lambda0 + x1frac* x
            + x3frac* x3poly * Math.Pow(x, 3.0)
            + x5frac* x5poly * Math.Pow(x, 5.0)
            + x7frac* x7poly * Math.Pow(x, 7.0);
        }

        /// <summary>
        /// Converts a latitude/longitude pair to x,y coordinates in the UTM system
        /// </summary>
        /// <param name="lat">
        /// Latitude, in degrees
        /// </param>
        /// <param name="lon">
        /// Longitude, in degrees
        /// </param>
        /// <param name="zone">
        /// UTM zone in which the point lies
        /// </param>
        /// <param name="x">
        /// x-cooordinate in UTM system
        /// </param>
        /// <param name="y">
        /// y-coordinate in UTM system
        /// </param>
        public static void LatLonToUTMXY(double lat, double lon, int zone, out double x, out double y)
        {
            MapLatLonToXY(lat* DEGREES_TO_RADIANS, lon* DEGREES_TO_RADIANS, UTMCentralMeridian (zone), out x, out y);
            // Adjust easting and northing for UTM system. 
            x = x* UTMScaleFactor + 500000.0;
            y = y* UTMScaleFactor;
            if (y< 0.0)
            { 
                y = y + 10000000.0; 
            }
        }

        /// <summary>
        /// Converts (x,y) coordinates in UTM projection to a lat/long pair
        /// </summary>
        /// <param name="x">
        /// x-coordinate in UTM system
        /// </param>
        /// <param name="y">
        /// y-coordinate in UTM system
        /// </param>
        /// <param name="zone">
        /// UTM zone in which the point lies
        /// </param>
        /// <param name="southhemi">
        /// true if point is in southern hemisphere
        /// </param>
        /// <param name="lat">
        /// Latitude, in degrees
        /// </param>
        /// <param name="lon">
        /// Longitude, in degrees
        /// </param>
        public static void UTMXYToLatLon(double x, double y, int zone, bool southhemi, out double lat, out double lon)
        {
            double tmpx = x- 500000.0;
            tmpx /= UTMScaleFactor;

            // If in southern hemisphere, adjust y accordingly. 
            double tmpy = y;
            if (southhemi)
            {
                tmpy -= 10000000.0;
            }
            tmpy /= UTMScaleFactor;

            MapXYToLatLon(tmpx, tmpy, UTMCentralMeridian(zone), out lat, out lon);
            lat*=RADIANS_TO_DEGREES;
            lon*=RADIANS_TO_DEGREES;
        }

    }
}
