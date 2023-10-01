package edu.ktu.ryselis;

import java.util.List;
import java.util.stream.IntStream;

public class Main {

    /**
     * A program that demonstrates the issue with returning data from monitor to a non-synchronized context
     */
    public static void main(String[] args) {
        SortedThreadSafeList<Integer> threadSafeList = new SortedThreadSafeList<>();  // monitor object, has list inside
        ItemInserter inserter = new ItemInserter(threadSafeList);  // thread object
        Thread thread = new Thread(inserter);
        thread.start();  // launch thread
        List<Integer> storage = threadSafeList.getStorage();  // get internal list from monitor
        // modify the list without synchronization - code does the same as monitor's add(), but without locks
        IntStream.range(1001, 1500).forEach(item -> {
            int index = (int) storage.stream().filter(i -> i.compareTo(item) < 0).count();
            // ConcurrentModificationException might be thrown here, because inserter is also modifying the list at the
            // same time
            storage.add(index, item);
        });
        try {
            thread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        storage.forEach(System.out::println);
    }
}
