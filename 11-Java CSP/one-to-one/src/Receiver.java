import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInputInt;

public class Receiver implements CSProcess {
    private ChannelInputInt channel;
    private int value;

    Receiver(ChannelInputInt channel) {
        this.channel = channel;
    }

    @Override
    public void run() {
        value = channel.read();
    }

    int getValue() {
        return value;
    }
}
