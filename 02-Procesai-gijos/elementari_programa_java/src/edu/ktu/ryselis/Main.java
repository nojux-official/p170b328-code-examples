package edu.ktu.ryselis;

import java.util.List;
import java.util.stream.Collectors;

public class Main {

    public static void main(String[] args) {
        // create names for threads
        List<String> names = List.of("First", "Second");
        // create a thread object for each name. .map() calls DemoThread constructor with each name
        // on the list
        List<DemoThread> threads = names.stream().map(DemoThread::new).collect(Collectors.toList());
        // launch all threads
        threads.forEach(Thread::start);
        // wait for all threads to finish
        threads.forEach(t -> {
            try{
                t.join();
            } catch (InterruptedException e) {
                System.out.println("Thread was interrupted");
            }
        });
        System.out.println("Program finished execution");
    }
}
