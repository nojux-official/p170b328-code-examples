using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace SimpleProgramCS
{
    internal static class Program
    {
        private static void Main()
        {
            var names = new List<string> {"First", "Second"};
            // create a thread object for each name. .Select() calls Executor constructor with each name
            // on the list, second .Select() calls Thread constructor with each executor
            var threads = names
                .Select(name =>
                {
                    var executor = new Executor(name);
                    return new Thread(executor.Execute);
                })
                .ToList();
            // launch all threads
            foreach (var thread in threads)
            {
                thread.Start();
            }
            // wait for all threads to finish
            foreach (var thread in threads)
            {
                thread.Join();
            }
            Console.WriteLine("Program finished execution");
        }
    }
}