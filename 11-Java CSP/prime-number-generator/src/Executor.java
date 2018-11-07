import org.jcsp.lang.*;

import java.util.Arrays;
import java.util.stream.IntStream;

public class Executor implements CSProcess {
    private One2OneChannelInt[] toRight;
    private One2OneChannelInt[] down;
    private Parallel parallel;

    Executor() {
        int primeNumberCount = 100;
        toRight = IntStream.range(0, primeNumberCount + 1)
                .mapToObj(i -> Channel.one2oneInt())
                .toArray(One2OneChannelInt[]::new);
        down = IntStream.range(0, primeNumberCount)
                .mapToObj(i -> Channel.one2oneInt())
                .toArray(One2OneChannelInt[]::new);
        AltingChannelInputInt[] downIn = Arrays.stream(down)
                .map(One2OneChannelInt::in)
                .toArray(AltingChannelInputInt[]::new);
        One2OneChannelInt finishChannel = Channel.one2oneInt();
        NumberGenerator generator = new NumberGenerator(toRight[0].out(), finishChannel.in());
        Collector collector = new Collector(toRight[primeNumberCount].in());
        Printer printer = new Printer(downIn, finishChannel.out());
        Filter[] filters = IntStream.range(0, primeNumberCount)
                .mapToObj(i ->
                        new Filter(toRight[i].in(), toRight[i+1].out(), down[i].out())
                )
                .toArray(Filter[]::new);
        parallel = new Parallel(new CSProcess[] {
                generator, collector, printer, new Parallel(filters)
        });

    }

    @Override
    public void run() {
        parallel.run();
    }
}
