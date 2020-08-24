package ec.edu.epn.pdc;

import java.util.Arrays;
import java.util.List;
import java.util.concurrent.*;

public class InvokeAny {
    static Callable<String> callable(String res, long sleepSeconds) {
        return () -> {
            TimeUnit.SECONDS.sleep(sleepSeconds);
            return res;
        };
    }
    public static void main (String argvs[]) throws ExecutionException, InterruptedException {
        ExecutorService executor = Executors.newWorkStealingPool();
        List<Callable<String>> callables = Arrays.asList(
            callable("task1", 2),
            callable("task2", 1),
            callable("task3", 3));
        String result = executor.invokeAny(callables);
        System.out.println(result);
    }
}
