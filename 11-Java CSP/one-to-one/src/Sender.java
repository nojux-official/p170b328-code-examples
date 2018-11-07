import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelOutputInt;

public class Sender implements CSProcess {
    private ChannelOutputInt channel;
    private int value;

    Sender(ChannelOutputInt channel) {
        this.channel = channel;
        value = 9999;
    }

    @Override
    public void run() {
        channel.write(value);
    }
}
