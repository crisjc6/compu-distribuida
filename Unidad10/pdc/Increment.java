package ec.edu.epn.pdc;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.IntStream;

import static ec.edu.epn.pdc.ConcurrentUtils.stop;

public class Increment {
    public static void main(String argvs[]){
        final int[] count = {0};
        Runnable incrementar = () -> count[0] = count[0] + 1;
        ExecutorService executor = Executors.newFixedThreadPool(1);
        IntStream.range(0, 10000)
                .forEach(i -> executor.submit(incrementar));
        stop(executor);
        System.out.println(count[0]);
    }
}
