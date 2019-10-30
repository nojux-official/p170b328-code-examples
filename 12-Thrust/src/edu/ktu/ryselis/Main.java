package edu.ktu.ryselis;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class Main {

    private static IntStream getStream(int startValue) {
        return IntStream.range(startValue, startValue + 20);
    }

    public static void main(String[] args) {
        IntStream firstStream = getStream(1);
        IntStream secondStream = getStream(21);
        int sum = vector
                .filter(x -> x % 2 == 0) // filter only even
                .map(x -> x * x) // map to squares
                .reduce(0, (acc, x) -> acc + x); // reduce to sum
        System.out.println(sum);
    }
}

