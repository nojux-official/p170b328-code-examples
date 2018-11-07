import org.jcsp.lang.*;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class Executor {
    private List<One2OneChannelInt> channels;
    private Receiver receiver;
    private Sender[] senders;
    private Parallel parallel;

    Executor() {
        channels = IntStream.range(0, 2).mapToObj(i -> Channel.one2oneInt()).collect(Collectors.toList());
        List<Integer> values = IntStream.range(1, 3).map(i -> i * 11).boxed().collect(Collectors.toList());
        senders = IntStream.range(0, channels.size()).mapToObj(i -> new Sender(channels.get(i).out(), values.get(i)))
                .toArray(Sender[]::new);
        AltingChannelInputInt[] channelOutputs = channels.stream().map(One2OneChannelInt::in)
                .toArray(AltingChannelInputInt[]::new);
        receiver = new Receiver(channelOutputs);
        parallel = new Parallel();
    }

    void execute() {
        parallel.addProcess(receiver);
        parallel.addProcess(senders);
        parallel.run();
    }

    List<Integer> getValues() {
        return receiver.getValues();
    }
}
