import org.jcsp.lang.Parallel;

class ProcessContainer {
    private Process[] processes;
    private Process process0;
    private Parallel parallel;

    ProcessContainer(Parallel parallel, Process process0, Process[] processes) {
        this.parallel = parallel;
        this.process0 = process0;
        this.processes = processes;
    }

    void execute() {
        parallel.addProcess(process0);
        parallel.addProcess(processes);
        parallel.run();
    }
}
