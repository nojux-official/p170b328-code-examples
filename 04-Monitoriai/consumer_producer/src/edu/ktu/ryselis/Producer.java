package edu.ktu.ryselis;

import java.util.stream.IntStream;

public class Producer implements Runnable {
    private int itemsToProduce;
    private LimitedBuffer buffer;

    Producer(int itemsToProduce, LimitedBuffer buffer){
        this.itemsToProduce = itemsToProduce;
        this.buffer = buffer;
    }

    @Override
    public void run() {
        int startItem = 10;
        IntStream.range(0, itemsToProduce).forEach(i -> {
            int itemToInsert = startItem + i;
            buffer.insert(itemToInsert);
        });
    }
}
