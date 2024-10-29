using System;
using Microsoft.Data.SqlClient;
using Harlinn.Common.Core.Net.Data.SqlClient;
using System.Diagnostics;
using System.Data;

namespace SqlClientBasicCRUD01
{
    internal class Program
    {
        static string ConnectionString = "Data Source=(local);Integrated Security=true;Encrypt=false;Initial Catalog=AjaworksDev;";

#if DEBUG
        const int rowCount = 10;
#else
        const int rowCount = 1_000_000;
#endif
        static void CreateRows(SqlConnection connection)
        {
            var lastTimestamp = new DateTime( 2020, 1, 1,0,0,0,DateTimeKind.Utc );
            var firstTimestamp = lastTimestamp - TimeSpan.FromSeconds(rowCount);
            var oneSecond = TimeSpan.FromSeconds(1).Ticks;

            var stopwatch = new Stopwatch();
            stopwatch.Start();

            var command = connection.CreateCommand();
            using (command)
            {
                command.CommandText = "INSERT INTO dbo.TimeseriesValue1(Id,Ts,Flags,Val) VALUES(@id,@ts,@flags,@val)";
                command.CommandType = CommandType.Text;
                var parameters = command.Parameters;
                var idParameter = parameters.AddInt64("@id", 3);
                idParameter.Size = sizeof(long);
                var tsParameter = parameters.AddDateTime("@ts", DateTime.UtcNow);
                tsParameter.Size = sizeof(long);
                var flagsParameter = parameters.AddInt32("@flags", 0);
                flagsParameter.Size = sizeof(int);
                var valParameter = parameters.AddDouble("@val", 0);
                valParameter.Size = sizeof(double);

                using (var transaction = connection.BeginTransaction())
                {
                    command.Transaction = transaction;

                    command.Prepare();

                    for (int i = 0; i < rowCount; ++i)
                    {
                        tsParameter.Value = firstTimestamp + new TimeSpan(oneSecond * (i + 1));
                        flagsParameter.Value = ((double)i) + 1.0;

                        command.ExecuteNonQuery();
                    }
                    transaction.Commit();
                }
                
            }
            stopwatch.Stop();
            var message = $"{rowCount} rows inserted in {stopwatch.Elapsed.TotalSeconds} seconds.";
            Console.WriteLine(message);

        }

        static void RetrieveRows(SqlConnection connection)
        {
            var stopwatch = new Stopwatch();
            stopwatch.Start();
            int count = 0;
            var command = connection.CreateCommand();
            using (command)
            {
                command.CommandText = "SELECT Id,Ts,Flags,Val FROM dbo.TimeseriesValue1";
                command.CommandType = CommandType.Text;
                var reader = command.ExecuteReader();
                using (reader)
                {
                    while (reader.Read())
                    {
                        var id = reader.GetInt64(0);
                        var ts = reader.GetDateTime(1);
                        var flags = reader.GetInt32(2);
                        var val = reader.GetDouble(3);
                        count++;
                    }
                }
            }

            stopwatch.Stop();
            var message = $"{count} rows retrieved in {stopwatch.Elapsed.TotalSeconds} seconds.";
            Console.WriteLine(message);
        }

        static void UpdateRows(SqlConnection connection)
        {

        }

        static void DeleteRows(SqlConnection connection)
        {
            var stopwatch = new Stopwatch();
            stopwatch.Start();

            var command = connection.CreateCommand();
            using (command)
            {
                command.CommandText = "delete from dbo.TimeseriesValue1";
                command.CommandType = CommandType.Text;

                using (var transaction = connection.BeginTransaction())
                {
                    command.Transaction = transaction;
                    command.ExecuteNonQuery();
                    transaction.Commit();
                }

            }
            stopwatch.Stop();
            var message = $"{rowCount} rows deleted in {stopwatch.Elapsed.TotalSeconds} seconds.";
            Console.WriteLine(message);
        }


        static void Run()
        {
            var connection = new SqlConnection(ConnectionString);
            connection.Open();
            DeleteRows(connection);
            CreateRows(connection);
            RetrieveRows(connection);
            UpdateRows(connection);
            DeleteRows(connection);
        }

        static void Main(string[] args)
        {
            Run();
        }
    }
}
