using System;
using System.Collections.Generic;
using System.Linq;

namespace RecursiveParallelQuickSort
{
    internal static class Program
    {
        private static void Main()
        {
            var numbers = new List<int>();
            var random = new Random();
            for (var i = 0; i < 900000; i++)
            {
                numbers.Add(random.Next(0, 1000));
            }

            var sortedNumbers = Sorter<int>.Sort(numbers);
            foreach (var sortedNumber in sortedNumbers.Take(36))
            {
                Console.WriteLine(sortedNumber);
            }
        }
    }
}
