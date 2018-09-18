package edu.ktu.ryselis;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class Main {

    public static void main(String[] args) {
        SimpleBoundedCounter counter = new SimpleBoundedCounter();
        Stream<Runnable> increasers = IntStream.range(0, 10).mapToObj(i -> new Increaser(counter));
        Stream<Runnable> decreasers = IntStream.range(0, 9).mapToObj(i -> new Decreaser(counter));
        Stream<Runnable> runnables = Stream.concat(increasers, decreasers);
        List<Thread> threads = runnables.map(Thread::new).collect(Collectors.toList());
        threads.forEach(Thread::start);
        threads.forEach(thread -> {
            try {
                thread.join();
            } catch (InterruptedException e) {
                System.out.println("Thread was interrupted");
            }
        });
        System.out.println(counter.getCount());
    }
}
