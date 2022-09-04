package edu.ktu.ryselis;

import java.util.List;
import java.util.stream.Collectors;

public class Main {

    public static void main(String[] args) {
        // create names for threads
        var names = List.of("First", "Second");
        // create a thread object for each name. .map() calls DemoRunnable constructor with each name
        // on the list, second .map() calls Thread constructor with each runnable
        var runnables = names.stream()
                .map(DemoRunnable::new)
                .map(Thread::new)
                .collect(Collectors.toList());
        // launch all threads
        runnables.forEach(Thread::start);
        // wait for all threads to finish
        runnables.forEach(thread -> {
            try {
                thread.join();
            } catch (InterruptedException e) {
                System.out.println("Thread was interrupted");
            }
        });
        System.out.println("Program finished execution");
    }
}
