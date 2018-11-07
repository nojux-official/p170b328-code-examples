import org.jcsp.lang.*;

public class NumberGenerator implements CSProcess {
    private ChannelOutputInt toNext;
    private AltingChannelInputInt finishChannel;
    private Alternative alternative;
    private boolean finish;

    public NumberGenerator(ChannelOutputInt toNext, AltingChannelInputInt finishChannel) {
        this.toNext = toNext;
        this.finishChannel = finishChannel;
        Skip skip = new Skip();
        Guard[] guards = new Guard[]{finishChannel, skip};
        alternative = new Alternative(guards);
        finish = false;
    }

    @Override
    public void run() {
        int number = 2;
        while (!finish) {
            switch (alternative.priSelect()) {
                case 0:
                    toNext.write(finishChannel.read());
                    finish = true;
                    break;
                case 1:
                    toNext.write(number);
                    number++;
                    break;
            }
        }
    }
}
