using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

namespace RecursiveParallelQuickSort
{
    internal static class Program
    {
        private static void Main()
        {
            var numbers = new List<int>();
            var random = new Random();
            for (var i = 0; i < 1000000; i++)
            {
                numbers.Add(random.Next(0, 1000));
            }

            var stopwatch = new Stopwatch();
            stopwatch.Start();
            var sortedNumbers = Sorter<int>.Sort(numbers);
            stopwatch.Stop();
            foreach (var sortedNumber in sortedNumbers.Take(36))
            {
                Console.WriteLine(sortedNumber);
            }
            Console.WriteLine($"Elapsed time: {stopwatch.ElapsedMilliseconds} ms");
        }
    }
}
