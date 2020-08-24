package ec.edu.epn.pdc;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.DoubleAdder;
import java.util.stream.IntStream;

import static ec.edu.epn.pdc.ConcurrentUtils.stop;

public class LongAdder {
    public static void main (String argvs[]) {
        ExecutorService executor = Executors.newFixedThreadPool(2);
        java.util.concurrent.atomic.LongAdder adder = new java.util.concurrent.atomic.LongAdder();
        IntStream.range(0, 1000)
                .forEach(i -> executor.submit(adder::increment));
        stop(executor);
        System.out.println(adder.sumThenReset());
    }
}
