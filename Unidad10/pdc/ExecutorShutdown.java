package ec.edu.epn.pdc;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

import static ec.edu.epn.pdc.ConcurrentUtils.sleep;

public class ExecutorShutdown {
    public static void main (String argvs[]){
        ExecutorService executor = Executors.newSingleThreadExecutor();
        executor.submit(() -> {
            String threadName = Thread.currentThread().getName();
            System.out.println("Hello " + threadName);
        });
        try {
            System.out.println("attempt to shutdown executor");
            executor.shutdown();
            if (!executor.awaitTermination(5, TimeUnit.SECONDS))
                System.out.printf("Pool no finalizo\n");
        }
        catch (InterruptedException e) {
            System.err.println("tasks interrupted");
        }
        finally {
            if (!executor.isTerminated()) {
                System.err.println("cancel non-finished tasks");
            }
            executor.shutdownNow();
            System.out.println("shutdown finished");
        }
    }
}
