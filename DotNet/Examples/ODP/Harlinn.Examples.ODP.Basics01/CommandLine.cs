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
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harlinn.Examples.ODP.Basics01
{
    public enum ProgramOperation
    {
        Unknown,
        QueryAllUsers,
        SimpleTest,
        BasicInsert,
        BasicInsertDT,
        Insert,
        InsertDT,
        Select,
        SelectDT,
        BasicUpdateDT,
        Update,
        UpdateDT,
        Delete
    }

    public class CommandLine
    {
        public static ProgramOperation GetProgramOperation(string[] args)
        {
            ProgramOperation result = ProgramOperation.Unknown;
            string operation = "";
            var count = args.Length;
            int i = 0;
            while (i < count)
            {
                var str = args[i];
                if (str.StartsWith("-o"))
                {
                    var remaining = str.Substring(2);
                    if (string.IsNullOrWhiteSpace(remaining))
                    {
                        ++i;
                        remaining = args[i];
                    }
                    operation = remaining;
                    break;
                }
                else if (str.StartsWith("--operation="))
                {
                    operation = str.Substring(11);
                    break;
                }
                ++i;
            }

            if (string.IsNullOrWhiteSpace(operation) == false)
            {
                operation = operation.ToLowerInvariant();
                switch (operation)
                {
                    case "queryallusers":
                    {
                        result = ProgramOperation.QueryAllUsers;
                    }
                    break;
                    case "simpletest":
                    {
                        result = ProgramOperation.SimpleTest;
                    }
                    break;
                    case "basicinsert":
                    {
                        result = ProgramOperation.BasicInsert;
                    }
                    break;
                    case "basicinsertdt":
                    {
                        result = ProgramOperation.BasicInsertDT;
                    }
                    break;
                    case "insert":
                    {
                        result = ProgramOperation.Insert;
                    }
                    break;
                    case "insertdt":
                    {
                        result = ProgramOperation.InsertDT;
                    }
                    break;
                    case "select":
                    {
                        result = ProgramOperation.Select;
                    }
                    break;
                    case "selectdt":
                    {
                        result = ProgramOperation.SelectDT;
                    }
                    break;
                    case "basicupdatedt":
                    {
                        result = ProgramOperation.BasicUpdateDT;
                    }
                    break;
                    case "update":
                    {
                        result = ProgramOperation.Update;
                    }
                    break;
                    case "updatedt":
                    {
                        result = ProgramOperation.UpdateDT;
                    }
                    break;
                    case "delete":
                    {
                        result = ProgramOperation.Delete;
                    }
                    break;
                }
            }

            return result;
        }

        public static string GetConnectionString(string[] args)
        {
            string userId = "";
            string password = "";
            string dataSource = "localhost:1521/orclpdb.lan";
            var count = args.Length;
            int i = 0;
            while (i < count)
            {
                var str = args[i];
                if (str.StartsWith("-u"))
                {
                    var remaining = str.Substring(2);
                    if (string.IsNullOrWhiteSpace(remaining))
                    {
                        ++i;
                        remaining = args[i];
                    }
                    userId = remaining;
                }
                else if (str.StartsWith("--userid="))
                {
                    userId = str.Substring(9);
                }
                else if (str.StartsWith("-p"))
                {
                    var remaining = str.Substring(2);
                    if (string.IsNullOrWhiteSpace(remaining))
                    {
                        ++i;
                        remaining = args[i];
                    }
                    password = remaining;
                }
                else if (str.StartsWith("--password="))
                {
                    password = str.Substring(11);
                }
                else if (str.StartsWith("-d"))
                {
                    var remaining = str.Substring(2);
                    if (string.IsNullOrWhiteSpace(remaining))
                    {
                        ++i;
                        remaining = args[i];
                    }
                    dataSource = remaining;
                }
                else if (str.StartsWith("--datasource="))
                {
                    dataSource = str.Substring(11);
                }
                ++i;
            }

            var connectionString = $"User Id={userId};Password={password};Data Source={dataSource}";
            return connectionString;
        }
    }
}
