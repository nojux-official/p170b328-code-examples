using System;
using System.Collections.Generic;
using System.Linq;

namespace functional_cs
{
    internal static class Program
    {
        private static IEnumerable<int> GetVector() => Enumerable.Range(0, 21);

        private static void Main()
        {
            var vector = GetVector();
            var sum = vector
                .Where(x => x % 2 == 0)
                .Select(x => x * x)
                .Aggregate((acc, x) => acc + x);
            Console.WriteLine(sum);
        }
    }
}