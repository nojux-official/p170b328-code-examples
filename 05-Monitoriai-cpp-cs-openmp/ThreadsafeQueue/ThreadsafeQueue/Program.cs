using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace ThreadsafeQueue
{
    internal class Program
    {
        /// <summary>
        /// Program that demonstrates a possible race condition even when all methods are properly protected from
        /// concurrent access individually
        /// </summary>
        /// <param name="args"></param>
        public static void Main(string[] args)
        {
            var threadSafeQueue = new ThreadSafeQueue<int>();  // a queue that has all methods protected with locks
            const int itemsToProcess = 100000;  // a number of elements to process
            const int popperThreadCount = 10;  // a number of threads to use to remove items from queue
            var threads = Enumerable.Range(0, popperThreadCount).Select(i =>
            {
                // a thread that removes one tenth of all items from the queue
                return new Thread(() =>
                {
                    var itemsRemoved = 0;  // counter of removed items
                    while (itemsRemoved < itemsToProcess / popperThreadCount)
                    {
                        // possible race condition is here. When ItemCount is called, the queue may be empty, but
                        // between the call to ItemCount and the call to PopItem another thread may call PopItem and the
                        // queue may become empty even our condition was true a moment ago.
                        if (threadSafeQueue.ItemCount > 0)
                        {
                            threadSafeQueue.PopItem();  // exception is likely to occur on this line
                            itemsRemoved++;
                        }
                    }
                });
            }).ToList();
            threads.Add(new Thread(() =>
            {
                // adds numbers from 0 to itemsToProcess to the queue
                var itemsToAdd = Enumerable.Range(0, itemsToProcess);
                foreach (var i in itemsToAdd)
                {
                    threadSafeQueue.AddItem(i);
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
        }
    }
}