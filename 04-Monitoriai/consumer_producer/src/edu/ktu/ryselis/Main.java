package edu.ktu.ryselis;

import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        LimitedBuffer buffer = new LimitedBuffer(5);
        Thread producerThread = new Thread(new Producer(10, buffer));
        Consumer consumer = new Consumer(10, buffer);
        Thread consumerThread = new Thread(consumer);
        producerThread.start();
        consumerThread.start();
        try {
            producerThread.join();
            consumerThread.join();
        } catch (InterruptedException e) {
            System.out.println("One of the threads was interrupted");
        }
        Arrays.stream(consumer.getConsumedItems()).forEach(System.out::println);
    }
}
