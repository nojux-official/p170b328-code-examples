import org.jcsp.lang.Any2OneChannelInt;
import org.jcsp.lang.Channel;
import org.jcsp.lang.Parallel;

import java.util.stream.IntStream;

class OrnamentalGarden {
    private Parallel parallel;
    private Any2OneChannelInt gate;
    private Controller controller;
    private Gate[] gates;

    OrnamentalGarden() {
        parallel = new Parallel();
        gate = Channel.any2oneInt();
        gates = IntStream.range(0, 5).mapToObj(i -> new Gate(gate.out())).toArray(Gate[]::new);
        controller = new Controller(gate.in(), gates.length);
    }

    void execute() {
        parallel.addProcess(controller);
        parallel.addProcess(gates);
        parallel.run();
    }

    int getVisitors() {
        return controller.getTotalAmount();
    }
}
