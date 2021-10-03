using System;
using System.Linq;

namespace ParallelQuicksort
{
    internal static class Program
    {
        private static void Main()
        {
            var rand = new Random();
            var numbers = Enumerable.Range(0, 30).Select(_ => rand.Next(1000)).ToList();
            var sorted = Sorter.GetSorted(numbers);
            foreach (var number in sorted)
            {
                Console.WriteLine(number);
            }
        }
    }
}