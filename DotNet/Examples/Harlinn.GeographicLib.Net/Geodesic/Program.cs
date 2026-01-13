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
﻿using Harlinn.GeographicLib.Net;

namespace GeodesicExample
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Geodesic geod = Geodesic.WGS84;

            // Sample direct calculation, travelling about NE from JFK
            var jfkLocation = new GeoPoint(40.6, -73.8);
            double s12 = 5.5e6, azi1 = 51;
            double lat2, lon2;
            geod.Direct(jfkLocation, azi1, s12, out lat2, out lon2);

            Console.WriteLine($"Latitude: {lat2}, Longitude:{lon2}");

            // Sample inverse calculation, JFK to LHR

            // JFK Airport
            var lat1 = 40.6;
            var lon1 = -73.8;

            // LHR Airport
            lat2 = 51.6; 
            lon2 = -0.5;  
            
            geod.Inverse(lat1, lon1, lat2, lon2, out s12);

            Console.WriteLine($"Distance: {s12}");

        }
    }
}
