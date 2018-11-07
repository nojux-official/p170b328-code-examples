import org.jcsp.lang.Any2OneChannelInt;
import org.jcsp.lang.Channel;
import org.jcsp.lang.Parallel;

import java.util.List;
import java.util.stream.IntStream;

class Executor {
    private Any2OneChannelInt channel;
    private Receiver receiver;
    private Sender[] senders;
    private Parallel parallel;

    Executor() {
        channel = Channel.any2oneInt();
        receiver = new Receiver(channel.in());
        senders = IntStream.range(0, 2).mapToObj(i -> new Sender(i, channel.out())).toArray(Sender[]::new);
        parallel = new Parallel();
    }

    void execute() {
        parallel.addProcess(receiver);
        parallel.addProcess(senders);
        parallel.run();
    }

    List<Integer> getValues() {
        return receiver.getReceivedValues();
    }
}
