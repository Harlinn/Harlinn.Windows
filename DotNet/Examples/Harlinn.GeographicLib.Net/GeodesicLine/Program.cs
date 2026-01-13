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

namespace GeodesicLineExample
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Geodesic geod = Geodesic.WGS84;

            double
              // JFK airport
              lat1 = 40.640, lon1 = -73.779,
              // SIN airport
              lat2 = 1.359, lon2 = 103.989; 

            GeodesicLine line = geod.InverseLine(lat1, lon1, lat2, lon2);

            // Nominal distance between points = 500 km
            double ds0 = 500e3;

            // The number of intervals
            int num = (int)Math.Ceiling(line.Distance / ds0);

            double ds = line.Distance / num;
            for (int i = 0; i <= num; ++i)
            {
                double lat, lon;
                line.Position(i * ds, out lat, out lon);
                Console.WriteLine($"{i} -> Latitude: {lat}, Longitude: {lon} ");
            }
        }
    }
}
