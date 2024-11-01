using System;
using System.Diagnostics;
using System.Linq;

namespace ParallelQuicksort
{
    internal static class Program
    {
        private static void Main()
        {
            var stopwatch = new Stopwatch();
            var rand = new Random();
            var numbers = Enumerable.Range(0, 45000).Select(_ => rand.Next(1000)).ToList();
            stopwatch.Start();
            var sorted = Sorter.GetSorted(numbers);
            stopwatch.Stop();
            var median = sorted.Count % 2 == 1
                ? sorted[sorted.Count / 2]
                : (sorted[sorted.Count / 2 - 1] + sorted[sorted.Count / 2]) / 2.0;
            Console.WriteLine($"Median is {median}");
            Console.WriteLine($"Elapsed time: {stopwatch.ElapsedMilliseconds} ms");
        }
    }
}