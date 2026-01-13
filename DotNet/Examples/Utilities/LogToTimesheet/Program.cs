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
﻿
using System;
using System.IO;
using System.Collections.Generic;

namespace LogToTimesheet
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var logFiles = new List<string>();
            for (int i = 0; i < args.Length; i++)
            {
                var arg = args[i];
                if(File.Exists(arg))
                {
                    logFiles.Add(arg);
                }
            }

            DateTime? firstForTheDay = null;
            DateTime? endOfTheDay = null;
            DateTime? previousEntryTime = null;
            DateTime? generated = null;

            var logFileCount = logFiles.Count;
            for (int i = 0; i < logFileCount; i++)
            {
                var file = logFiles[i];
                var fileStream = File.Open(file, FileMode.Open, FileAccess.Read);
                TextReader reader = new StreamReader(fileStream, System.Text.Encoding.Latin1);
                string? line = reader.ReadLine();
                while(line != null)
                {
                    if(firstForTheDay.HasValue == false)
                    {
                        if(GetDateTime(line, out firstForTheDay))
                        {
                            endOfTheDay = firstForTheDay?.AddDays(1).Date + TimeSpan.FromHours(7);
                            previousEntryTime = firstForTheDay;
                        }
                    }
                    else
                    {
                        if (GetDateTime(line, out generated))
                        {
                            if (generated > endOfTheDay)
                            {
                                var hours = previousEntryTime - firstForTheDay;
                                var message = $"Start:{firstForTheDay}, End:{previousEntryTime}, Hours: {hours}";
                                System.Console.WriteLine(message);
                                firstForTheDay = generated;
                                endOfTheDay = firstForTheDay?.AddDays(1).Date + TimeSpan.FromHours(7);
                                previousEntryTime = firstForTheDay;
                            }
                            else
                            {
                                previousEntryTime = generated;
                            }
                        }
                    }
                    line = reader.ReadLine();
                }
            }
            var lastHours = previousEntryTime - firstForTheDay;
            var lastMessage = $"Start:{firstForTheDay}, End:{previousEntryTime}, Hours: {lastHours}";
            System.Console.WriteLine(lastMessage);




        }

        static bool GetDateTime( string line, out DateTime? result)
        {
            result = null;
            if(line != null)
            {
                var timestampString = line.Substring(0, 23);
                if(DateTime.TryParseExact(timestampString, "yyyy/MM/dd HH:mm:ss.fff",System.Globalization.CultureInfo.InvariantCulture, System.Globalization.DateTimeStyles.AssumeLocal, out var dt))
                {
                    result = dt;
                    return true;
                }
            }
            return false;
        }

    }
}
