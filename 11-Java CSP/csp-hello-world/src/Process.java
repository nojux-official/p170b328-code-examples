import org.jcsp.lang.CSProcess;

class Process implements CSProcess {
    private String name;

    Process(String name) {
        this.name = name;
    }

    @Override
    public void run() {
        System.out.println(name);
    }
}
