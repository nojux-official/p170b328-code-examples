import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelOutputInt;

public class Sender implements CSProcess {
    private ChannelOutputInt channel;
    private int value;

    Sender(ChannelOutputInt channel, int value) {
        this.channel = channel;
        this.value = value;
    }

    @Override
    public void run() {
        channel.write(value);
    }
}
