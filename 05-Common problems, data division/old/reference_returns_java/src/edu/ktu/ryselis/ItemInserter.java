package edu.ktu.ryselis;

import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class ItemInserter implements Runnable {
    private volatile SortedThreadSafeList<Integer> list;

    ItemInserter(SortedThreadSafeList<Integer> list) {
        this.list = list;
    }

    /**
     * Generates an array of number from 0 to 10000, shuffles it and adds all numbers to the list
     */
    @Override
    public void run() {
        List<Integer> items = IntStream.range(0, 10000).boxed().collect(Collectors.toList());
        Collections.shuffle(items);
        items.forEach(i -> list.add(i));
    }
}
