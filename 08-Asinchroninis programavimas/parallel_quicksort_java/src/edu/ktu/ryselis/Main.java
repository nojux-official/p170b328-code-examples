package edu.ktu.ryselis;

import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Main {

    public static void main(String[] args) {
        Random rand = new Random();
        rand.setSeed(System.currentTimeMillis());
        List<Integer> numbers = IntStream.range(0, 30).mapToObj(i -> rand.nextInt(1000)).collect(Collectors.toList());
        Sorter sorter = new Sorter(numbers);
        List<Integer> sorted = sorter.getSorted();
        sorted.forEach(System.out::println);
    }
}
