using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace RecursiveParallelQuickSort
{
    public static class Sorter<T> where T: IComparable<T>
    {
        public static List<T> Sort(List<T> input)
        {
            var availableThreads = Environment.ProcessorCount;
            var maxDepth = Math.Ceiling(Math.Log2(availableThreads));
            return RunSort(input, (int) maxDepth - 1);
        }

        private static List<T> RunSort(List<T> input, int depth)
        {
            if (input.Count == 0)
            {
                // list is empty, nothing to sort
                return input;
            }

            // first element is the pivot. The remaining items are split into higher than pivot and lower than pivot
            var pivot = input[0];
            // the split is here - group by a boolean value indicating if the item is less than pivot (true) or not
            // (false)
            var itemLists = input.Skip(1)
                .GroupBy(t => t.CompareTo(pivot) < 0)
                .ToDictionary(g => g.Key, g => g.ToList());
            // get the split lists (if all items are lower than pivot, false key will not be in dictionary and vice
            // versa
            var lowerItems = itemLists.TryGetValue(true, out var list) ? list : new List<T>();
            var higherItems = itemLists.TryGetValue(false, out var itemList) ? itemList : new List<T>();
            List<T> sortedLowerItems = null;
            Thread thread = null;
            // sort lower half in the same thread in depth is negative or new thread if depth has not yet reached
            // negative values
            if (depth >= 0)
            {
                thread = new Thread(() =>
                {
                    sortedLowerItems = RunSort(lowerItems, depth - 1);
                });
                thread.Start();
            }
            else
            {
                sortedLowerItems = RunSort(lowerItems, -1);
            }
            
            // higher items is always computed on the same thread
            var sortedHigherItems = RunSort(higherItems, depth - 1);
            // if the thread was started, join it
            thread?.Join();
            // add all items into a single list and return it
            sortedLowerItems.Add(pivot);
            sortedLowerItems.AddRange(sortedHigherItems);
            return sortedLowerItems;
        }
    }
}
