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
using Serilog;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Stores physical location for interpolation/radiation calculations
    /// </summary>
    public struct Location
    {
        /// <summary>
        /// Latitude
        /// </summary>
        public double latitude;
        /// <summary>
        /// Longitude
        /// </summary>
        public double longitude;
        /// <summary>
        /// x-coordinate in Universal Transverse Mercator coordinate system
        /// </summary>
        public double UTM_x;
        /// <summary>
        /// y-coordinate in Universal Transverse Mercator coordinate system
        /// </summary>
        public double UTM_y;


        public Location()
        { }

        public Location(double lat, double lon)
        {
            latitude = lat;
            longitude = lon;
        }

        public Location(double lat, double lon, int utmZone)
        {
            latitude = lat;
            longitude = lon;
            UTMUtils.LatLonToUTMXY(lat, lon, utmZone, out UTM_x, out UTM_y);
        }

        public void InitializeUTM(int utmZone)
        {
            UTMUtils.LatLonToUTMXY(latitude, longitude, utmZone, out UTM_x, out UTM_y);
        }




    }
}
