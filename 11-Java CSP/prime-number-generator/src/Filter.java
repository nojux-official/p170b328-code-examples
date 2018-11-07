import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInputInt;
import org.jcsp.lang.ChannelOutputInt;

public class Filter implements CSProcess {
    private ChannelInputInt fromPrevious;
    private ChannelOutputInt toNext;
    private ChannelOutputInt toPrinter;

    Filter(ChannelInputInt fromPrevious, ChannelOutputInt toNext, ChannelOutputInt toPrinter) {
        this.fromPrevious = fromPrevious;
        this.toNext = toNext;
        this.toPrinter = toPrinter;
    }

    @Override
    public void run() {
        int m = 1;
        int n = fromPrevious.read();
        if (n > 0) {
            toPrinter.write(n);
            while (m > 0) {
                m = fromPrevious.read();
                if ((m == 0) || ((m % n != 0))) {
                    toNext.write(m);
                }
            }
        } else {
            toNext.write(0);
        }
    }
}
