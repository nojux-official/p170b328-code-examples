import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInputInt;

public class Controller implements CSProcess {
    private ChannelInputInt gate;
    private int n;
    private int totalAmount;

    Controller(ChannelInputInt gate, int n) {
        this.gate = gate;
        this.n = n;
    }

    @Override
    public void run() {
        int closed = 0;
        totalAmount = 0;
        while (closed < n) {
            int visitors = gate.read();
            if (visitors < 0) {
                closed++;
            } else {
                totalAmount += visitors;
            }
        }
    }

    int getTotalAmount() {
        return totalAmount;
    }
}
