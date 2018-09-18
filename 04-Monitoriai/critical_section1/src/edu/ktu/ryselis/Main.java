package edu.ktu.ryselis;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Main {

    public static void main(String[] args) {
        Data d = new Data();
        List<Thread> threads = IntStream.range(0, 10)
                .mapToObj(i -> new DemoThread(d))
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
