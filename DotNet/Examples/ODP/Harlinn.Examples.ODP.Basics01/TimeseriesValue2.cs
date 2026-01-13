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
﻿using System.Diagnostics;
using Oracle.ManagedDataAccess.Client;

namespace Harlinn.Examples.ODP.Basics01
{

    class TimeseriesValue2
    {
        OracleConnection _connection;

        public TimeseriesValue2(OracleConnection connection)
        {
            _connection = connection;
        }


        OracleCommand CreateCommand(string sql)
        {
            var result = _connection.CreateCommand();
            result.CommandText = sql;
            return result;
        }

        



        public void Clear()
        {
            using (var command = CreateCommand("DELETE FROM TimeseriesValue2"))
            {
                var transaction = _connection.BeginTransaction();
                using (transaction)
                {
                    command.ExecuteNonQuery();
                    transaction.Commit();
                }
                System.Console.Out.WriteLine("Cleared TimeseriesValue2");
            }
        }

        public void BasicInsert()
        {
            int count = 1000000;

            var stopwatch = new Stopwatch();
            stopwatch.Start();

            for (int i = 0; i < count; ++i)
            {
                var transaction = _connection.BeginTransaction();
                using (transaction)
                {
                    using (var command = _connection.CreateCommand())
                    {
                        command.CommandText = "INSERT INTO TimeseriesValue2(Id,Ts,Flags,Val) "+
                                        "VALUES(:1,:2,:3,:4)";

                        OracleParameter id = new OracleParameter();
                        id.OracleDbType = OracleDbType.Int64;
                        id.Value = i + 1;

                        OracleParameter timestamp = new OracleParameter();
                        timestamp.OracleDbType = OracleDbType.Int64;
                        timestamp.Value = i + 1;

                        OracleParameter flag = new OracleParameter();
                        flag.OracleDbType = OracleDbType.Int64;
                        flag.Value = i + 1;

                        OracleParameter value = new OracleParameter();
                        value.OracleDbType = OracleDbType.BinaryDouble;
                        value.Value = (double)i + 1.0;

                        command.Parameters.Add(id);
                        command.Parameters.Add(timestamp);
                        command.Parameters.Add(flag);
                        command.Parameters.Add(value);
                    
                        command.ExecuteNonQuery();
                    }
                    transaction.Commit();
                }
            }
            stopwatch.Stop();
            var duration = stopwatch.Elapsed.TotalSeconds;
            var rowsPerSecond = count / duration;
            System.Console.Out.WriteLine("Inserted {0} rows in {1} seconds - rows per second: {2} ",
                count, duration, rowsPerSecond);
        }

        public void Insert()
        {
            int count = 1000000;
            long[] ids = new long[count];
            long[] timestamps = new long[count];
            long[] flags = new long[count];
            double[] values = new double[count];

            for (int i = 0; i < count; ++i)
            {
                ids[i] = i + 1;
                timestamps[i] = i + 1;
                flags[i] = i + 1;
                values[i] = i + 1;
            }

            using (var command = _connection.CreateCommand())
            {
                command.CommandText = "INSERT INTO TimeseriesValue2(Id,Ts,Flags,Val) VALUES(:1,:2,:3,:4)";

                OracleParameter id = new OracleParameter();
                id.OracleDbType = OracleDbType.Int64;
                id.Value = ids;

                OracleParameter timestamp = new OracleParameter();
                timestamp.OracleDbType = OracleDbType.Int64;
                timestamp.Value = timestamps;

                OracleParameter flag = new OracleParameter();
                flag.OracleDbType = OracleDbType.Int64;
                flag.Value = flags;

                OracleParameter value = new OracleParameter();
                value.OracleDbType = OracleDbType.BinaryDouble;
                value.Value = values;

                command.ArrayBindCount = ids.Length;
                command.Parameters.Add(id);
                command.Parameters.Add(timestamp);
                command.Parameters.Add(flag);
                command.Parameters.Add(value);

                var stopwatch = new Stopwatch();
                stopwatch.Start();
                var transaction = _connection.BeginTransaction();
                using (transaction)
                {
                    command.ExecuteNonQuery();
                    transaction.Commit();
                }
                stopwatch.Stop();
                var duration = stopwatch.Elapsed.TotalSeconds;
                var rowsPerSecond = count / duration;
                System.Console.Out.WriteLine("Inserted {0} rows in {1} seconds - rows per second: {2} ", 
                    count, duration, rowsPerSecond);
            }
        }



        public void Select()
        {
            using (var command = _connection.CreateCommand())
            {
                
                int count = 0;
                var stopwatch = new Stopwatch();
                command.CommandText = "SELECT Id,Ts,Flags,Val FROM TimeseriesValue2 ORDER BY Id,Ts";
                stopwatch.Start();
                var start = SystemCalls.GetUserTime();
                var reader = command.ExecuteReader();
                while (reader.Read())
                {
                    var id = reader.GetInt64(0);
                    var ts = reader.GetInt64(1);
                    var flags = reader.GetInt64(2);
                    var value = reader.GetDouble(3);
                    count++;
                }
                var stop = SystemCalls.GetUserTime();
                stopwatch.Stop();
                var duration = stopwatch.Elapsed.TotalSeconds;
                double userTime = stop.TotalSeconds - start.TotalSeconds;
                var rowsPerSecond = count / duration;
                System.Console.Out.WriteLine("Retrieved {0} rows in {1} seconds - rows per second: {2}, user time: {3} ",
                    count, duration, rowsPerSecond, userTime);

            }
        }

    }
}
