import hashlib
import multiprocessing
import random
import string
import time


# the program will generate random string and their hashes will be computed in parallel


def process_elements(queue: multiprocessing.Queue, lock: multiprocessing.Lock):
    """
    This is a worker process function. Accepts elements from queue and processes them until a None is received
    :param queue: a queue to receive items from
    :param lock: locks print statements to avoid messy output
    """
    hashed_values = []
    while True:
        items = queue.get()
        if items is None:
            break
        hashed_values += [(item, process_item(item)) for item in items]
    output = '\n'.join(f'SHA 512 hash of {item} is {hashed_value}' for item, hashed_value in hashed_values)
    with lock:
        print(output)


def process_item(item: str):
    """
    Accepts an item, computes its SHA512 hash and prints it together with the value
    :param item: a string to process
    """
    return hashlib.sha512(item.encode()).hexdigest()


def get_random_string() -> str:
    """
    Generates a random (not crypto-secure random) string of length 64
    :return: generated string
    """
    allowed_chars = string.ascii_letters
    return ''.join(random.choice(allowed_chars) for _ in range(64))


def generate_items_to_queue(queue: multiprocessing.Queue):
    """
    Generates random strings and writes them to the queue
    :param queue: a queue to write to
    """
    for _ in range(40000):
        random_string = get_random_string()
        queue.put(random_string)


def main():
    t0 = time.time()
    queue = multiprocessing.Queue()
    cpu_count = multiprocessing.cpu_count()  # we will spawn as many processes as the core count
    lock = multiprocessing.Lock()
    # create process objects and tell them to call process_elements function with args queue and lock
    processing_processes = [multiprocessing.Process(target=process_elements,
                                                    args=(queue, lock))
                            for _ in range(cpu_count)]
    # start the processes
    for process in processing_processes:
        process.start()
    # write stuff to queue
    generate_items_to_queue(queue)
    # write a None value for each process to finish it
    for _ in range(cpu_count):
        queue.put(None)
    # wait for the processes to finish
    for process in processing_processes:
        process.join()
    t1 = time.time()
    print(f"Elapsed {t1 - t0:.2f} seconds")


if __name__ == '__main__':
    main()
