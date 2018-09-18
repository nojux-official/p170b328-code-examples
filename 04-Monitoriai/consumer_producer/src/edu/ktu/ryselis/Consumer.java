package edu.ktu.ryselis;

import java.util.stream.IntStream;

public class Consumer implements Runnable {
    private int itemsToConsume;
    private LimitedBuffer buffer;
    private int[] consumedItems;

    Consumer(int itemsToConsume, LimitedBuffer buffer) {
        this.itemsToConsume = itemsToConsume;
        this.buffer = buffer;
    }

    @Override
    public void run() {
        consumedItems = IntStream.range(0, itemsToConsume).map(i -> buffer.remove()).toArray();
    }

    int[] getConsumedItems() {
        return consumedItems;
    }
}
