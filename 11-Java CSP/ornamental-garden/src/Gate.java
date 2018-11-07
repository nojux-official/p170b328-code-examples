import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelOutputInt;

import java.util.stream.IntStream;

public class Gate implements CSProcess {
    private ChannelOutputInt channel;
    private final int people = 1;

    Gate(ChannelOutputInt channel) {
        this.channel = channel;
    }

    @Override
    public void run() {
        int cycles = 10;
        IntStream.range(0, cycles).forEach(i -> channel.write(people));
        channel.write(-1);
    }
}
