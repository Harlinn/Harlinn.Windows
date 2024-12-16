using System;
using System.Collections.Generic;

using Harlinn.Examples.Data.Net;
using Harlinn.Examples.TcpClient.Net;


namespace Harlinn.Examples.TestTcpClient.Net
{
    class Program
    {
        Session _session;
        string _catalog1Name = "Catalog1";
        string _catalog2Name = "Catalog2";
        Catalog _catalog1a;
        Catalog _catalog2a;
        Catalog _catalog1b;
        Catalog _catalog2b;
        string _asset1Name = "Asset1";
        string _asset2Name = "Asset2";
        Asset _asset1a;
        Asset _asset2a;
        Asset _asset1b;
        Asset _asset2b;
        string _sensor1Name = "Sensor1";
        string _sensor2Name = "Sensor2";
        Sensor _sensor1a;
        Sensor _sensor2a;
        Sensor _sensor1b;
        Sensor _sensor2b;
        Dictionary<Guid, CatalogItem> _allCatalogItems;
        Dictionary<Guid, CatalogItem> _rootCatalogs;
        Dictionary<Guid, CatalogItem> _catalog1Assets;
        Dictionary<Guid, CatalogItem> _catalog2Assets;
        Dictionary<Guid, Sensor> _allSensors;
        Dictionary<Guid, Sensor> _asset1Sensors;
        Dictionary<Guid, Sensor> _asset2Sensors;

        DateTime _intervalStart = new DateTime(2019, 9, 1, 0, 0, 0, DateTimeKind.Utc);
        DateTime _intervalEnd = new DateTime(2020, 9, 1, 0, 0, 0, DateTimeKind.Utc);
        //DateTime _intervalEnd = new DateTime(2020, 8, 1, 2, 0, 0, DateTimeKind.Utc);
        SensorPoint[] _points1Stored;
        SensorPoint[] _points2Stored;
        SensorPoint[] _points1Retrieved;
        SensorPoint[] _points2Retrieved;
        SensorValue[] _allSensorValues;


        Program()
        {
        }



        void Connect()
        {
            _session = new Session("localhost", 42000);
            _session.Connect();
        }

        Catalog CreateCatalog(string name)
        {
            var catalog = _session.CreateOrRetrieveCatalog(Guid.Empty, name);
            if (catalog == null)
            {
                Console.WriteLine("Unexpected: CreateOrRetrieveCatalog returned null");
            }
            if (catalog.Name != name)
            {
                Console.WriteLine("Unexpected: Catalog named {0} expected {1}", catalog.Name, name);
            }
            return catalog;
        }

        void CreateCatalogs()
        {
            _catalog1a = CreateCatalog(_catalog1Name);
            _catalog2a = CreateCatalog(_catalog2Name);
        }

        Asset CreateAsset(Catalog catalog, string name)
        {
            var asset = _session.CreateOrRetrieveAsset(catalog.Id, name);
            if (asset == null)
            {
                Console.WriteLine("Unexpected: CreateOrRetrieveAsset returned null");
            }
            if (asset.Name != name)
            {
                Console.WriteLine("Unexpected: Asset named {0} expected {1}", asset.Name, name);
            }
            return asset;
        }

        void CreateAssets()
        {
            _asset1a = CreateAsset(_catalog1a, _asset1Name);
            _asset2a = CreateAsset(_catalog2a, _asset2Name);
        }

        Sensor CreateSensor(Asset asset, string name)
        {
            var sensor = _session.CreateOrRetrieveSensor(asset.Id, name);

            if (sensor == null)
            {
                Console.WriteLine("Unexpected: CreateOrRetrieveSensor returned null");
            }
            if (sensor.Name != name)
            {
                Console.WriteLine("Unexpected: Sensor named {0} expected {1}", sensor.Name, name);
            }

            return sensor;
        }

        void CreateSensors()
        {
            _sensor1a = CreateSensor(_asset1a, _sensor1Name);
            _sensor2a = CreateSensor(_asset2a, _sensor2Name);
        }

        void GetAllCatalogItems()
        {
            _allCatalogItems = _session.GetAllCatalogItems();
        }
        void GetRootCatalogs()
        {
            _rootCatalogs = _session.GetCatalogItems(Guid.Empty);
        }

        void GetCatalogAssets()
        {
            _catalog1Assets = _session.GetCatalogItems(_catalog1a.Id);
            _catalog2Assets = _session.GetCatalogItems(_catalog2a.Id);
        }
        void GetAllSensors()
        {
            _allSensors = _session.GetAllSensors();
        }

        void GetAssetSensors()
        {
            _asset1Sensors = _session.GetSensors(_asset1a.Id);
            _asset2Sensors = _session.GetSensors(_asset2a.Id);
        }


        void GetCatalogs()
        {
            _catalog1b = (Catalog)_session.GetCatalogItem(_catalog1a.Id);
            _catalog2b = (Catalog)_session.GetCatalogItem(_catalog2a.Id);
        }

        void GetAssets()
        {
            _asset1b = (Asset)_session.GetCatalogItem(_asset1a.Id);
            _asset2b = (Asset)_session.GetCatalogItem(_asset2a.Id);
        }

        void GetSensors()
        {
            _sensor1b = _session.GetSensor(_sensor1a.Id);
            _sensor2b = _session.GetSensor(_sensor2a.Id);
        }

        SensorPoint[] GenerateSensorPoints(TimeSpan offset)
        {
            var start = _intervalStart;
            var end = _intervalEnd;
            var duration = end - start;
            int minutes = (int)duration.TotalMinutes;
            var step = TimeSpan.FromMinutes(1);

            var generator = new Harlinn.Common.Core.Net.Generators.SineGenerator(10, TimeSpan.FromHours(1), offset, 5);

            var points = new SensorPoint[minutes];
            var current = start;
            int index = 0;
            while (current < end)
            {
                double value = generator.Generate(current);
                points[index].Timestamp = current;
                points[index].Value = value;
                current += step;
                index++;
            }
            return points;
        }

        SensorPoint[] GenerateSensorPoints(Sensor sensor, TimeSpan offset  )
        {
            var points = GenerateSensorPoints(offset);
            var stopwatch = new System.Diagnostics.Stopwatch();
            stopwatch.Start();
            _session.StoreSensorPoints(sensor.Id, points);
            stopwatch.Stop();
            var seconds = stopwatch.Elapsed.TotalSeconds;
            var pointsPerSecond = points.Length / seconds;

            Console.Out.WriteLine("Wrote {0} records in {1} seconds, {2} records per second.", 
                            points.Length, seconds, pointsPerSecond);

            return points;
        }

        void GenerateSensorPoints()
        {
            _points1Stored = GenerateSensorPoints(_sensor1a, TimeSpan.FromMinutes(0));
            _points2Stored = GenerateSensorPoints(_sensor2a, TimeSpan.FromMinutes(7));
        }

        void Verify(SensorPoint[] first, SensorPoint[] second)
        {
            if (first == null)
            {
                Console.Out.WriteLine("Unexpected: first is null");
                return;
            }
            if (second == null)
            {
                Console.Out.WriteLine("Unexpected: second is null");
                return;
            }
            if (first.Length != second.Length)
            {
                Console.Out.WriteLine("Unexpected: Lengths are not equal first: {0} and second:{1}", first.Length, second.Length);
                return;
            }
            var count = first.Length;
            for (int i = 0; i < count; i++)
            {
                if (first[i].Timestamp != second[i].Timestamp)
                {
                    Console.Out.WriteLine("Unexpected: Timestamps at {0} are not equal first: {1} and second:{2}", i , first[i].Timestamp, second[i].Timestamp);
                    return;
                }
                if (first[i].Flags != second[i].Flags)
                {
                    Console.Out.WriteLine("Unexpected: Flags at {0} are not equal first: {1} and second:{2}", i, first[i].Flags, second[i].Flags);
                    return;
                }
                if (first[i].Value != second[i].Value)
                {
                    Console.Out.WriteLine("Unexpected: Values at {0} are not equal first: {1} and second:{2}", i, first[i].Value, second[i].Value);
                    return;
                }
            }

        }

        void GetSensorPoints()
        {

            var stopwatch = new System.Diagnostics.Stopwatch();
            stopwatch.Start();

            _points1Retrieved = _session.GetSensorPoints(_sensor1a.Id, _intervalStart, _intervalEnd);
            _points2Retrieved = _session.GetSensorPoints(_sensor2a.Id, _intervalStart, _intervalEnd);

            stopwatch.Stop();
            var numberOfPoints = _points1Retrieved.Length + _points2Retrieved.Length;
            var seconds = stopwatch.Elapsed.TotalSeconds;
            var pointsPerSecond = numberOfPoints / seconds;

            Console.Out.WriteLine("Retrieved {0} records in {1} seconds, {2} records per second.", numberOfPoints, seconds, pointsPerSecond);

            Verify(_points1Retrieved, _points1Stored);
            Verify(_points2Retrieved, _points2Stored);
        }

        void GetAllSensorValues()
        {
            var stopwatch = new System.Diagnostics.Stopwatch();
            stopwatch.Start();

            _allSensorValues = _session.GetAllSensorValues();

            stopwatch.Stop();
            var numberOfPoints = _allSensorValues.Length;
            var seconds = stopwatch.Elapsed.TotalSeconds;
            var pointsPerSecond = numberOfPoints / seconds;

            Console.Out.WriteLine("Retrieved {0} records in {1} seconds, {2} records per second.", numberOfPoints, seconds, pointsPerSecond);

        }


        void Disconnect()
        {
            if (_session != null)
            {
                _session.Close();
            }
            _session = null;
        }


        void SendSensorPoints()
        {
            const int iterations = 1000;
            var points = GenerateSensorPoints(default);
            var stopwatch = new System.Diagnostics.Stopwatch();
            stopwatch.Start();
            for (int i = 0; i < iterations; ++i)
            {
                _session.SendSensorPoints(Guid.Empty, points);
            }
            stopwatch.Stop();
            var seconds = stopwatch.Elapsed.TotalSeconds;
            var totalPoints = iterations * points.Length;
            var pointsPerSecond = totalPoints / seconds;

            Console.Out.WriteLine("Sendt {0} records in {1} seconds, {2} records per second.", totalPoints, seconds, pointsPerSecond);
        }



        void SendSensorPointsAsJSON()
        {
            const int iterations = 1000;
            var points = GenerateSensorPoints(default);
            var stopwatch = new System.Diagnostics.Stopwatch();
            stopwatch.Start();
            for (int i = 0; i < iterations; ++i)
            {
                var json = System.Text.Json.JsonSerializer.Serialize(points);
                _session.SendJSON(json);
            }
            stopwatch.Stop();
            var seconds = stopwatch.Elapsed.TotalSeconds;
            var totalPoints = iterations * points.Length;
            var pointsPerSecond = totalPoints / seconds;

            Console.Out.WriteLine("Serialized and sendt {0} records as JSON in {1} seconds, {2} records per second.", totalPoints, seconds, pointsPerSecond);
        }

        void SerializeSensorPointsToJSON()
        {
            const int iterations = 1000;
            var points = GenerateSensorPoints(default);
            var stopwatch = new System.Diagnostics.Stopwatch();
            stopwatch.Start();
            for (int i = 0; i < iterations; ++i)
            {
                System.Text.Json.JsonSerializer.Serialize(points);
            }
            stopwatch.Stop();
            var seconds = stopwatch.Elapsed.TotalSeconds;
            var totalPoints = iterations * points.Length;
            var pointsPerSecond = totalPoints / seconds;

            Console.Out.WriteLine("Serialized {0} records to JSON in {1} seconds, {2} records per second.", totalPoints, seconds, pointsPerSecond);
        }

        void DeserializeSensorPointsToJSON()
        {
            const int iterations = 1000;
            var points = GenerateSensorPoints(default);
            var stopwatch = new System.Diagnostics.Stopwatch();
            var json = System.Text.Json.JsonSerializer.Serialize(points);
            stopwatch.Start();
            for (int i = 0; i < iterations; ++i)
            {
                System.Text.Json.JsonSerializer.Deserialize(json, points.GetType());
            }
            stopwatch.Stop();
            var seconds = stopwatch.Elapsed.TotalSeconds;
            var totalPoints = (iterations * points.Length);
            var pointsPerSecond = totalPoints / seconds;

            Console.Out.WriteLine("Deserialized {0} records from JSON in {1} seconds, {2} records per second.", totalPoints, seconds, pointsPerSecond);
        }


        void RunJSON()
        {
            Connect();
            SendSensorPointsAsJSON();
            SerializeSensorPointsToJSON();
            DeserializeSensorPointsToJSON();
            Disconnect();
        }


        void Run()
        {
            Connect();
            CreateCatalogs();
            CreateAssets();
            CreateSensors();
            GetAllCatalogItems();
            GetRootCatalogs();
            GetCatalogAssets();
            GetAllSensors();
            GetAssetSensors();
            GetCatalogs();
            GetAssets();
            GetSensors();
            GenerateSensorPoints();
            GetSensorPoints();
            GetAllSensorValues();
            SendSensorPoints();
            Disconnect();
        }

        static void Main(string[] args)
        {
            var program = new Program();
            program.Run();
            program.RunJSON();
        }
    }
}
