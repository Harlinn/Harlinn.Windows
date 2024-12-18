using Harlinn.GeographicLib.Net;

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
