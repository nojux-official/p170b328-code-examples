package edu.ktu.ryselis;

import java.util.LinkedList;
import java.util.List;

class SortedThreadSafeList<T extends Comparable<T>> {
    private List<T> storage;

    SortedThreadSafeList() {
        storage = new LinkedList<>();
    }

    /**
     * Adds an item to the storage so that it remains sorted in a thread-safe way
     * @param item - an item to add
     */
    synchronized void add(T item) {
        int index = (int) storage.stream().filter(i -> i.compareTo(item) < 0).count();
        storage.add(index, item);
    }

    /**
     * Returns the internal storage object
     */
    synchronized List<T> getStorage() {
        return storage;
    }
}
