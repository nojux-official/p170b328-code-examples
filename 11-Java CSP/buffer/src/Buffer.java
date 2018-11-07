import org.jcsp.lang.*;

public class Buffer implements CSProcess {
    private static final int maxItems = 10;
    private int[] items;
    private int currentItems;
    private AltingChannelInputInt takeChannel;
    private AltingChannelInputInt putChannel;
    private AltingChannelOutputInt takeResponseChannel;

    public Buffer(AltingChannelInputInt takeChannel, AltingChannelInputInt putChannel,
                  AltingChannelOutputInt takeResponseChannel) {
        this.takeChannel = takeChannel;
        this.putChannel = putChannel;
        this.takeResponseChannel = takeResponseChannel;
        items = new int[maxItems];
        currentItems = 0;
    }

    @Override
    public void run(){
        Guard[] guards = {putChannel, takeChannel};
        Alternative alternative = new Alternative(guards);
        boolean finish = false;
        while (true) {
            boolean[] preconditions = {currentItems < maxItems, currentItems > 0};
            switch (alternative.select(preconditions)) {
                case 0:
                    int item = putChannel.read();
                    insertItem(item);
                    break;
                case 1:
                    takeChannel.read();
                    takeResponseChannel.write(removeItem());
                    break;
            }
        }
    }

    private void insertItem(int item) {
        items[currentItems] = item;
        currentItems++;
    }

    private int removeItem(){
        int item = items[0];
        System.arraycopy(items, 1, items, 0, currentItems - 1);
        currentItems--;
        return item;
    }
}
