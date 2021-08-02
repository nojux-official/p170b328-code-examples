package edu.ktu.ryselis;

import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class Main {

    public static void main(String[] args) {
        var counter = new SimpleBoundedCounter();  // create counter
        // create 10 runnables that will increase value of the counter
        var increasers = IntStream.range(0, 10).mapToObj(i -> new Increaser(counter));
        // create 9 runnables that will decrease value of the counter
        var decreasers = IntStream.range(0, 9).mapToObj(i -> new Decreaser(counter));
        // merge all runnables into a single stream
        var runnables = Stream.concat(increasers, decreasers);
        // create a thread for each runnable
        var threads = runnables.map(Thread::new).collect(Collectors.toList());
        // start all threads
        threads.forEach(Thread::start);
        // wait for all threads to finish
        threads.forEach(thread -> {
            try {
                thread.join();
            } catch (InterruptedException e) {
                System.out.println("Thread was interrupted");
            }
        });
        // check what value we got in our counter
        System.out.println(counter.getCount());
    }
}
