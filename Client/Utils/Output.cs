using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Utils
{
    public static class Output
    {
        public static event EventHandler<string> OutputEventHandler;
        public static void Log(string message)
        {
            Trace.WriteLine(message);
            OutputEventHandler?.Invoke(null, message);
        }
        public static void LogError(string message)
        {
            Trace.WriteLine($"[ERROR] {message}");
            OutputEventHandler?.Invoke(null, $"[ERROR] {message}");
        }
        public static void Log(string prefix, string message)
        {
            Trace.WriteLine($"[{prefix}] {message}");
            OutputEventHandler?.Invoke(null, $"[{prefix}] {message}");
        }
        public static void LogError(string prefix, string message)
        {
            Trace.WriteLine($"[ERROR] [{prefix}] {message}");
            OutputEventHandler?.Invoke(null, $"[ERROR] [{prefix}] {message}");
        }
    }
}
