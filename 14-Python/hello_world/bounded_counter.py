from threading import Lock, Condition, Thread


class SimpleBoundedCounter:
    MIN = 0
    MAX = 50

    def __init__(self):
        self.count = self.MIN
        self._lock = Lock()
        self._condition = Condition(self._lock)

    def increase(self):
        with self._lock:
            self._condition.wait_for(lambda: self.count < self.MAX)
            self.count += 1
            self._condition.notify_all()

    def decrease(self):
        with self._lock:
            self._condition.wait_for(lambda: self.count > self.MIN)
            self.count -= 1
            self._condition.notify_all()


def increase(counter):
    for i in range(50):
        counter.increase()


def decrease(counter):
    for i in range(50):
        counter.decrease()


if __name__ == '__main__':
    simple_counter = SimpleBoundedCounter()
    threads = [Thread(target=increase, args=(simple_counter,))
               for i in range(10)]
    threads += [Thread(target=decrease, args=(simple_counter,))
                for i in range(9)]
    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join()
    print(simple_counter.count)
