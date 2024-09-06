using System;
using System.Diagnostics;
namespace EventLogToTimesheet
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var eventLogs = EventLog.GetEventLogs();
            var eventLogCount = eventLogs.Length;
            for (int i = 0; i < eventLogCount; i++)
            {
                var log = eventLogs[i];
                var logName = log.Log;
                if(logName == "System")
                {
                    ProcessEventLog(log);
                }
            }
        }

        static void ProcessEventLog(EventLog eventLog)
        {
            var entries = eventLog.Entries;
            var entryCount = entries.Count;
            if (entryCount > 0)
            {
                DateTime firstForTheDay = entries[0].TimeGenerated;
                DateTime endOfTheDay = firstForTheDay.AddDays(1).Date + TimeSpan.FromHours(7);
                DateTime previousEntryTime = firstForTheDay;
                for (int i = 0; i < entryCount; i++)
                {
                    var entry = entries[i];
                    var generated = entry.TimeGenerated;
                    if(generated > endOfTheDay)
                    {
                        var hours = previousEntryTime - firstForTheDay;
                        var message = $"Start:{firstForTheDay}, End:{previousEntryTime}, Hours: {hours}";
                        System.Console.WriteLine(message);
                        firstForTheDay = generated;
                        endOfTheDay = firstForTheDay.AddDays(1).Date + TimeSpan.FromHours(7);
                        previousEntryTime = firstForTheDay;
                    }
                    else
                    {
                        previousEntryTime = generated;
                    }
                }
                var lastHours = previousEntryTime - firstForTheDay;
                var lastMessage = $"Start:{firstForTheDay}, End:{previousEntryTime}, Hours: {lastHours}";
                System.Console.WriteLine(lastMessage);
            }
        }
    }
}
