import org.jcsp.lang.Channel;
import org.jcsp.lang.One2OneChannelInt;
import org.jcsp.lang.Parallel;

class Executor {
    private Receiver receiver;
    private Sender sender;
    private Parallel parallel;
    Executor() {
        One2OneChannelInt channel = Channel.one2oneInt();
        receiver = new Receiver(channel.in());
        sender = new Sender(channel.out());
        parallel = new Parallel();
    }

    void execute() {
        parallel.addProcess(receiver);
        parallel.addProcess(sender);
        parallel.run();
    }

    int getValue() {
        return receiver.getValue();
    }
}
