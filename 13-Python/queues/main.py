import hashlib
import multiprocessing
import random
import string


# the program will generate random string and their hashes will be computed in parallel


def process_elements(queue: multiprocessing.Queue, lock: multiprocessing.Lock):
    """
    This is a worker process function. Accepts elements from queue and processes them until a None is received
    :param queue: a queue to receive items from
    :param lock: locks print statements to avoid messy output
    """
    while True:
        item = queue.get()
        if item is None:
            break
        process_item(item, lock)


def process_item(item: str, lock: multiprocessing.Lock):
    """
    Accepts an item, computes its SHA512 hash and prints it together with the value
    :param item: a string to process
    :param lock: a lock for print statements
    """
    hashed_value = hashlib.sha512(item.encode()).hexdigest()
    with lock:
        print(f'SHA 512 hash of {item} is {hashed_value}')


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


if __name__ == '__main__':
    main()
