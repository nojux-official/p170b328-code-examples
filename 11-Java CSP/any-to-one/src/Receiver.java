import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInputInt;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Receiver implements CSProcess {
    private List<Integer> receivedValues;
    private ChannelInputInt channel;

    Receiver(ChannelInputInt channel) {
        this.channel = channel;
        receivedValues = new ArrayList<>();
    }

    @Override
    public void run() {
        receivedValues = IntStream.range(0, 2).map(i -> channel.read()).boxed().collect(Collectors.toList());
    }

    List<Integer> getReceivedValues() {
        return receivedValues;
    }
}
