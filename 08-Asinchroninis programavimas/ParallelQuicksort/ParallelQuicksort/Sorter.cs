using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ParallelQuicksort
{
    public static class Sorter
    {
        public static List<int> GetSorted(List<int> listToSort)
        {
            var processorCount = Environment.ProcessorCount;
            var maxDepth = (int)Math.Floor(Math.Log2(processorCount));
            return GetSorted(listToSort, maxDepth);
        }

        /// <summary>
        /// Creates a new list that is a sorted listToSort
        /// </summary>
        /// <param name="listToSort">The initial list to sort</param>
        /// <param name="depth">Current recursion depth</param>
        /// <returns></returns>
        private static List<int> GetSorted(List<int> listToSort, int depth)
        {
            if (listToSort.Count == 0) {
                // list is empty, nothing to do
                return listToSort;
            }
            // pick a pivot
            var pivot = listToSort[0];
            // get all items smaller than pivot
            var lowerPart = listToSort.Skip(1).Where(item => item < pivot).ToList();
            // new lower is calculated asynchronously if depth limit has not been reached
            var newLower = depth >= 0 ? 
                Task.Run(() => GetSorted(lowerPart, depth - 1)) : 
                Task.FromResult(GetSorted(lowerPart, depth - 1));
            // get all items larger than pivot and sort synchronously
            var higherPart = listToSort.Skip(1).Where(item => item >= pivot).ToList();
            var newHigher = GetSorted(higherPart, depth - 1);
            // create new list - sorted lower part + pivot + sorted higher part
            return newLower.Result // when Result is called, the thread is blocked until the result is calculated
                .Concat(new List<int> { pivot })
                .Concat(newHigher)
                .ToList();
        }
    }
}