import org.jcsp.lang.Alternative;
import org.jcsp.lang.AltingChannelInputInt;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Guard;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Receiver implements CSProcess {
    private List<Integer> values;
    private AltingChannelInputInt[] channels;

    Receiver(AltingChannelInputInt[] channels) {
        this.channels = channels;
    }

    @Override
    public void run() {
        Guard[] guards = Arrays.copyOf(channels, channels.length);
        final Alternative alternative = new Alternative(guards);
        values = IntStream.range(0, 2).map(i -> {
            int index = alternative.fairSelect();
            return channels[index].read();
        }).boxed().collect(Collectors.toList());
    }

    List<Integer> getValues() {
        return values;
    }
}
