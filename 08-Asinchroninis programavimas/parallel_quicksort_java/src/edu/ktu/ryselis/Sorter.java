package edu.ktu.ryselis;

import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.stream.Collectors;
import java.util.stream.Stream;

class Sorter {
    private List<Integer> listToSort;

    Sorter(List<Integer> listToSort){
        this.listToSort = listToSort;
    }

    List<Integer> getSorted() {
        if (listToSort.isEmpty()) {
            return listToSort;
        }
        int pivot = listToSort.get(0);
        List<Integer> lowerPart = listToSort.stream().filter(item -> item < pivot).collect(Collectors.toList());
        CompletableFuture<List<Integer>> newLower = CompletableFuture.supplyAsync(() -> new Sorter(lowerPart).getSorted());
        List<Integer> higherPart = listToSort.stream().filter(item -> item > pivot).collect(Collectors.toList());
        List<Integer> newHigher = new Sorter(higherPart).getSorted();
        try {
            Stream<Integer> firstPart = Stream.concat(newLower.get().stream(), Stream.of(pivot));
            return Stream.concat(firstPart, newHigher.stream()).collect(Collectors.toList());
        } catch (InterruptedException | ExecutionException e) {
            System.err.println(e.getMessage());
            return null;
        }
    }
}
