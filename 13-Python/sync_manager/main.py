import random
import time
from multiprocessing import Manager, Process
from multiprocessing.managers import ListProxy


def merge_sort(data: list[int]) -> list[int]:
    """
    Perform merge sort on the data.
    """
    if len(data) <= 1:
        return data

    mid = len(data) // 2
    left = merge_sort(data[:mid])
    right = merge_sort(data[mid:])

    return merge(left, right)


def merge(left: list[int], right: list[int]) -> list[int]:
    """
    Merge two sorted lists.
    """
    merged = []
    left_index, right_index = 0, 0

    while left_index < len(left) and right_index < len(right):
        if left[left_index] < right[right_index]:
            merged.append(left[left_index])
            left_index += 1
        else:
            merged.append(right[right_index])
            right_index += 1

    merged.extend(left[left_index:])
    merged.extend(right[right_index:])
    return merged


def parallel_sort(data: list[int], result_list: ListProxy):
    """
    Each process sorts its portion of the data.
    """
    sorted_part = merge_sort(data)
    result_list.extend(sorted_part)


if __name__ == "__main__":
    t1 = time.time()
    # Number of processes
    num_processes = 16

    # Generate random data
    random_data = [random.randint(1, 1_000_000) for _ in range(750_000)]

    # Create a SyncManager
    with Manager() as manager:
        # Create a shared list for the sorted data
        sorted_data = manager.list()

        # Create processes that will perform parallel sort
        processes = []
        for i in range(num_processes):
            # not the most efficient approach as the whole random_data list is passed
            start = i * (len(random_data) // num_processes)
            end = (i + 1) * (len(random_data) // num_processes) if i < num_processes - 1 else len(random_data)
            process = Process(target=parallel_sort, args=(random_data[start:end], sorted_data))
            processes.append(process)
            process.start()

        # Wait for all processes to finish
        for process in processes:
            process.join()

        # Merge the sorted results from each process
        final_sorted_data = merge_sort(sorted_data)
    t2 = time.time()
    print(f'Computation time is {t2 - t1:2f} seconds')

    # Print the final sorted data
    with open('result.txt', 'w') as f:
        f.writelines(map(str, final_sorted_data))
