package ec.edu.epn.pdc;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.LongAccumulator;
import java.util.function.LongBinaryOperator;
import java.util.stream.IntStream;

import static ec.edu.epn.pdc.ConcurrentUtils.stop;

public class LongAcumulador {
    public static void main (String argvs[]) {
        LongBinaryOperator op = (x, y) -> 2 * x + y;
        LongAccumulator accumulator = new LongAccumulator(op, 1L);
        ExecutorService executor = Executors.newFixedThreadPool(1);
        IntStream.range(0, 5) .forEach(i -> executor.submit(() -> accumulator.accumulate(i)));
        stop(executor);
        System.out.println(accumulator.getThenReset());
    }
}
