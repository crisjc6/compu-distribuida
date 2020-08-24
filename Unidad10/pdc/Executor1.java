package ec.edu.epn.pdc;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Executor1 {

    public static void main (String argvs[]) {
        ExecutorService executor = Executors.newSingleThreadExecutor();
        Future f = executor.submit(() -> {
            String threadName = Thread.currentThread().getName();
            System.out.println("Hello " + threadName);
        });

        executor.shutdownNow();
    }
}
