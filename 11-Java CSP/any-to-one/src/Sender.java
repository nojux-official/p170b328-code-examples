import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelOutputInt;

public class Sender implements CSProcess {
    private int value;
    private ChannelOutputInt channel;

    Sender(int value, ChannelOutputInt channel) {
        this.value = value;
        this.channel = channel;
    }

    @Override
    public void run() {
        channel.write(value);
    }
}
