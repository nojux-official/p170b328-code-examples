using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ParallelQuicksort
{
    public static class Sorter
    {
        public static List<int> GetSorted(List<int> listToSort) {
            if (listToSort.Count == 0) {
                return listToSort;
            }
            var pivot = listToSort[0];
            var lowerPart = listToSort.Skip(1).Where(item => item < pivot).ToList();
            // new lower is calculated asynchronously
            var newLower = Task.Run(() => GetSorted(lowerPart));
            var higherPart = listToSort.Skip(1).Where(item => item >= pivot).ToList();
            var newHigher = GetSorted(higherPart);
            return newLower.Result  // when Result is called, the thread is blocked until the result is calculated
                .Concat(new List<int> { pivot })
                .Concat(newHigher)
                .ToList();
        }
    }
}