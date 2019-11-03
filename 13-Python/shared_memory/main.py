"""
A program that demonstrates how to create shared memory between processes
"""
from multiprocessing import Array
from multiprocessing.pool import Pool
from random import randint

POWER = 3
MAX_ITEM = 100
MAX_NUMBER = 1290

# generate a list of random numbers between 0 and MAX_NUMBER
items = [randint(0, MAX_NUMBER) for _ in range(MAX_ITEM)]
# create an array to hold shared memory. First parameter is array type (i means integer), second parameter - what values the memory should contain.
# shared_array may now be accessed from all processes and all changes will be visible to all processes.
shared_array = Array('i', items)


def calculate_powers(index):
    """
    Performs a power operation on an element in shared array at given index
    :param index: an index in the array to perform operation on
    """
    shared_array[index] = shared_array[index] ** POWER


with Pool() as pool:
    # for each item in shared_array (for each index from 0 to MAX_ITEM), call calculate_powers in separate processes in the pool
    pool.map(calculate_powers, range(MAX_ITEM))
# changes made by process pool should be visible in the main process - print them to verify
for item in shared_array:
    print(item)
