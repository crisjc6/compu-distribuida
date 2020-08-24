package ec.edu.epn.pdc;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.IntStream;

import static ec.edu.epn.pdc.ConcurrentUtils.stop;

public class UpdateAndGet {
    public static void main (String argvs[]) {
        AtomicInteger atomicInt = new AtomicInteger(0);
        ExecutorService executor = Executors.newFixedThreadPool(2);

        IntStream.range(0, 1000)
                .forEach(i -> {
                    Runnable task = () ->
                            atomicInt.updateAndGet(n -> n - 2);
                    executor.submit(task);
                });
        stop(executor);
        System.out.println(atomicInt.get());
    }
}
