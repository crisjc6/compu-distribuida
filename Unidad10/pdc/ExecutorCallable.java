package ec.edu.epn.pdc;

import java.util.concurrent.*;

import static ec.edu.epn.pdc.ConcurrentUtils.sleep;

public class ExecutorCallable {
    public static void main (String argvs[]) throws ExecutionException, InterruptedException {
        Callable<Integer> task = () -> {
            try {
                System.out.printf("Trying to sleep...\n");
                TimeUnit.SECONDS.sleep(1);
                return 123;
            }
            catch (InterruptedException e) {
                throw new IllegalStateException("task interrupted", e);
            }
        };
        ExecutorService executor = Executors.newFixedThreadPool(1);
        Future<Integer> future = executor.submit(task);
        System.out.println("future done? " + future.isDone());
        Integer result = future.get();
        System.out.println("future done? " + future.isDone());
        System.out.print("result: " + result);
        //executor.shutdownNow();
    }
}
