package edu.ktu.ryselis;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Main {

    public static void main(String[] args) {
        Data d = new Data();
        int threadCount = 10;
        Locker locker = new Locker(threadCount);
        List<Thread> threads = IntStream.range(0, threadCount)
                .mapToObj(i -> new DemoThread(d, i, locker))
                .collect(Collectors.toList());
        threads.forEach(Thread::start);
        threads.forEach(thread -> {
            try {
                thread.join();
            } catch (InterruptedException e) {
                System.out.println("A thread was interrupted");
            }
        });
        System.out.println(d.getCounter());
    }
}
