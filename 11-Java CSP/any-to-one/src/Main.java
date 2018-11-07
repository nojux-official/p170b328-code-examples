public class Main {

    public static void main(String[] args) {
        Executor executor = new Executor();
        executor.execute();
        executor.getValues().forEach(System.out::println);
    }
}
