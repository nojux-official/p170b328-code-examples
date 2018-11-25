import java.util.stream.IntStream;

public class Main {

    private static IntStream getVector() {
        return IntStream.range(1, 21);
    }

    public static void main(String[] args) {
        IntStream vector = getVector();
        int sum = vector
                .filter(x -> x % 2 == 0) // filter only even
                .map(x -> x * x) // map to squares
                .reduce(0, (acc, x) -> acc + x); // reduce to sum
        System.out.println(sum);
    }
}
