using System;
using System.Linq;
using System.Threading;

namespace ConsoleApplication1
{
    internal static class Program
    {
        public static void Main(string[] args)
        {
            var counter = new SimpleBoundedCounter();
            var increaseThreads = Enumerable.Range(0, 10).Select(i => new Thread(() =>
            {
                for (var j = 0; j < 50; j++)
                {
                    counter.Increase();
                }
            }));
            var decreaseThreads = Enumerable.Range(0, 9).Select(i => new Thread(() =>
            {
                for (var j = 0; j < 50; j++)
                {
                    counter.Decrease();
                }
            }));
            var threads = increaseThreads.Concat(decreaseThreads).ToList();
            foreach (var thread in threads)
            {
                thread.Start();
            }

            foreach (var thread in threads)
            {
                thread.Join();
            }
            Console.WriteLine(counter.Count);
        }
    }
}