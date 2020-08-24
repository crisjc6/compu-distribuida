package ec.edu.epn.pdc;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.IntStream;

import static ec.edu.epn.pdc.ConcurrentUtils.sleep;
import static ec.edu.epn.pdc.ConcurrentUtils.stop;

public class IncrementSync {
    private static int count = 0;

    void increment() {
        count = count + 1;
    }
    synchronized void incrementSync() {
        count = count + 1;
    }
    void incrementSyncBk() {
        synchronized (this) {
            count = count + 1;
        }
    }
    public static void main(String argvs[]) {
        IncrementSync inc = new IncrementSync();
        ExecutorService executor = Executors.newFixedThreadPool(2);

        IntStream.range(0, 10000)
                .forEach(i -> executor.submit(inc::increment));
        sleep (2);
        System.out.println(count);
        count = 0;
        IntStream.range(0, 10000)
                .forEach(i -> executor.submit(inc::incrementSync));
        sleep (2);
        System.out.println(count);
        count = 0;
        IntStream.range(0, 10000)
                .forEach(i -> executor.submit(inc::incrementSyncBk));
        stop(executor);
        System.out.println(count);
    }
}