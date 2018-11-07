import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInputInt;

public class Collector implements CSProcess {
    private ChannelInputInt fromLeft;

    Collector(ChannelInputInt fromLeft) {
        this.fromLeft = fromLeft;
    }

    @Override
    public void run() {
        int number = 1;
        while (number > 0) {
            number = fromLeft.read();
        }
    }
}
