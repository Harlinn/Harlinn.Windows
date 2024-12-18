using Harlinn.GeographicLib.Net;

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
