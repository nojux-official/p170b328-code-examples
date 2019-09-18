using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace ThreadSafeRarelyUpdatedDictionaryCS
{
    internal static class Program
    {
        public static void Main(string[] args)
        {
            var dictionary = new RarelyUpdatedDictionary<string, int>();
            var readItems = new List<int>();
            var threads = Enumerable.Range(0, 10).Select(n => new Thread(() =>
            {
                for (var i = 0; i < 100; i++)
                {
                    var item = -1;
                    while (item < 0)
                    {
                        try
                        {
                            item = dictionary[i.ToString()];
                        } catch(KeyNotFoundException) {}                        
                    }

                    lock (readItems)
                    {
                        readItems.Add(item);
                    }
                }
            })).ToList();
            threads.Add(new Thread(() =>
            {
                for (var i = 0; i < 100; i++)
                {
                    dictionary[i.ToString()] = i * i;
                }
            }));
            foreach (var thread in threads)
            {
                thread.Start();
            }

            foreach (var thread in threads)
            {
                thread.Join();
            }

            foreach (var readItem in readItems)
            {
                Console.WriteLine(readItem);
            }
        }
    }
}