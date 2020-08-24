package ec.edu.epn.pdc;

import java.util.concurrent.*;

public class FutureTO {
    public static void main (String argvs[]) throws InterruptedException, ExecutionException, TimeoutException {
        ExecutorService executor = Executors.newFixedThreadPool(1);

        Future<Integer> future = executor.submit(() -> {
            try {
                TimeUnit.SECONDS.sleep(1);
                return 123;
            }
            catch (InterruptedException e) {
                throw new IllegalStateException("task interrupted", e);
            }
        });
        System.out.printf("future: %d\n", future.get(1, TimeUnit.SECONDS));
        executor.shutdownNow();
    }
}
