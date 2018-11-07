import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInputInt;
import org.jcsp.lang.ChannelOutputInt;

import java.util.Arrays;

public class Printer implements CSProcess {
    private ChannelInputInt[] fromTop;
    private ChannelOutputInt finishChannel;

    Printer(ChannelInputInt[] fromTop, ChannelOutputInt finishChannel) {
        this.fromTop = fromTop;
        this.finishChannel = finishChannel;
    }

    @Override
    public void run() {
        Arrays.stream(fromTop).forEach(channel -> {
            int primaryNumber = channel.read();
            System.out.println(primaryNumber);
        });
        finishChannel.write(0);
    }
}
