import org.jcsp.lang.Parallel;

import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        String[] names = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
        Process[] processes = Arrays.stream(names).map(Process::new).toArray(Process[]::new);
        Process process0 = new Process("zero");
        Parallel parallel = new Parallel();
        ProcessContainer processContainer = new ProcessContainer(parallel, process0, processes);
        processContainer.execute();
    }
}
