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
﻿using System;
using Oracle.ManagedDataAccess.Client;

namespace Harlinn.Examples.ODP.Basics01
{



    class Program
    {
        static void BasicInsert(OracleConnection connection)
        {
            var tsv2 = new TimeseriesValue2(connection);
            tsv2.Clear();
            tsv2.BasicInsert();
        }

        static void BasicInsertDT(OracleConnection connection)
        {
            var tsv1 = new TimeseriesValue1(connection);
            tsv1.Clear();
            tsv1.BasicInsert();
        }

        static void Insert(OracleConnection connection)
        {
            var tsv2 = new TimeseriesValue2(connection);
            tsv2.Clear();
            tsv2.Insert();
        }

        static void InsertDT(OracleConnection connection)
        {
            var tsv1 = new TimeseriesValue1(connection);
            tsv1.Clear();
            tsv1.Insert();
        }

        static void Select(OracleConnection connection)
        {
            var tsv2 = new TimeseriesValue2(connection);
            tsv2.Select();
        }
        static void SelectDT(OracleConnection connection)
        {
            var tsv1 = new TimeseriesValue1(connection);
            tsv1.Select();
        }

        static void BasicUpdateDT(OracleConnection connection)
        {
            var tsv1 = new TimeseriesValue1(connection);
            tsv1.BasicUpdate();
        }

        static void UpdateDT(OracleConnection connection)
        {
            var tsv1 = new TimeseriesValue1(connection);
            tsv1.Update();
        }

        static void Delete(OracleConnection connection)
        {
            var tsv2 = new TimeseriesValue2(connection);
            tsv2.Clear();
        }

        static void SimpleTest(OracleConnection connection)
        {
            var simpleTest1 = new SimpleTest1(connection);
            simpleTest1.Execute();
        }

        static void Execute(OracleConnection connection, ProgramOperation programOperation)
        {
            switch (programOperation)
            {
                case ProgramOperation.QueryAllUsers:
                    QueryAllUsers(connection);
                    break;
                case ProgramOperation.BasicInsert:
                    BasicInsert(connection);
                    break;
                case ProgramOperation.BasicInsertDT:
                    BasicInsertDT(connection);
                    break;
                case ProgramOperation.Insert:
                    Insert(connection);
                    break;
                case ProgramOperation.InsertDT:
                    InsertDT(connection);
                    break;
                case ProgramOperation.Select:
                    Select(connection);
                    break;
                case ProgramOperation.SelectDT:
                    SelectDT(connection);
                    break;
                case ProgramOperation.BasicUpdateDT:
                    BasicUpdateDT(connection);
                    break;
                case ProgramOperation.UpdateDT:
                    UpdateDT(connection);
                    break;
                case ProgramOperation.Delete:
                    Delete(connection);
                    break;
                case ProgramOperation.SimpleTest:
                    SimpleTest(connection);
                    break;
                default:
                    
                    break;
            }
        }


        static void Main(string[] args)
        {
            var connectionString = CommandLine.GetConnectionString(args);
            var operation = CommandLine.GetProgramOperation(args);
            var connection = new OracleConnection(connectionString);
            using (connection)
            {
                connection.Open();
                Execute(connection, operation);
            }
        }

        static void QueryAllUsers(OracleConnection connection)
        {
            using (var command = connection.CreateCommand())
            {
                command.CommandText = "SELECT * FROM ALL_USERS";
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        var userName = reader.GetString(0);
                        Console.Out.WriteLine(userName);
                    }
                }
            }
        }

    }
}
