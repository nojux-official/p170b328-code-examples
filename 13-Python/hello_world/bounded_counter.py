"""
A program that demonstrates the basics on lock and condition variable usage in Python
"""


from threading import Lock, Condition, Thread


class SimpleBoundedCounter:
    """
    A class that encapsulates an int and provides synchronized methods to modify it
    """
    MIN = 0  # count value cannot go lower that MIN
    MAX = 50  # count value cannot go higher that MAX

    def __init__(self):
        """
        Initializes count, lock and condition variable
        """
        self.count = self.MIN  # initialize count to MIN
        self._lock = Lock()
        self._condition = Condition(self._lock)

    def increase(self):
        """
        A synchronized method that increases value of counter when it's lower than MAX
        """
        with self._lock:
            self._condition.wait_for(lambda: self.count < self.MAX)
            self.count += 1
            self._condition.notify_all()

    def decrease(self):
        """
        A synchronized method that decreases value of counter when it's higher than MIN
        """
        with self._lock:
            self._condition.wait_for(lambda: self.count > self.MIN)
            self.count -= 1
            self._condition.notify_all()


def increase(counter):
    """
    Increases counter value 50 times
    :param counter: a counter for increasing
    """
    for i in range(50):
        counter.increase()


def decrease(counter):
    """
    Decreases counter value 50 times
    :param counter: a counter for decreasing
    """
    for i in range(50):
        counter.decrease()


if __name__ == '__main__':
    simple_counter = SimpleBoundedCounter()  # create a counter object
    threads = [Thread(target=increase, args=(simple_counter,))  # create 10 threads that call increase
               for i in range(10)]
    threads += [Thread(target=decrease, args=(simple_counter,))  # create 10 threads that call decrease
                for i in range(9)]
    for thread in threads:
        thread.start()  # start all threads
    for thread in threads:
        thread.join()  # wait for all threads to finish
    print(simple_counter.count)  # check value of counter
