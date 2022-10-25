using System;
using System.Linq;

namespace ParallelQuicksort
{
    internal static class Program
    {
        private static void Main()
        {
            var rand = new Random();
            var numbers = Enumerable.Range(0, 40000).Select(_ => rand.Next(1000)).ToList();
            var sorted = Sorter.GetSorted(numbers);
            double median = sorted.Count % 2 == 1
                ? sorted[sorted.Count / 2]
                : (sorted[sorted.Count / 2 - 1] + sorted[sorted.Count / 2]) / 2;
            Console.WriteLine($"Median is {median}");
        }
    }
}