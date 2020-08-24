package ec.edu.epn.pdc;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

public class ScheduledFuturo {
    public static void main (String argvs[]) throws InterruptedException {
        ScheduledExecutorService executor = Executors.newScheduledThreadPool(1);
        Runnable task = () -> {
            try {
                TimeUnit.MILLISECONDS.sleep(1337);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Scheduling: " + System.nanoTime());
        };
        //ScheduledFuture<?> future = executor.schedule(task, 3, TimeUnit.SECONDS);
        int initialDelay = 0; int period = 1;
        //ScheduledFuture<?> future = executor.scheduleAtFixedRate(task, initialDelay, period, TimeUnit.SECONDS);
        //TimeUnit.MILLISECONDS.sleep(1337);
        //long remainingDelay = future.getDelay(TimeUnit.MILLISECONDS);
        //System.out.printf("Remaining Delay: %sms\n", remainingDelay);
        Runnable task1 = () -> {
            try {
                TimeUnit.SECONDS.sleep(2);
                System.out.println("Scheduling: " + System.nanoTime());
            }
            catch (InterruptedException e) {
                System.err.println("task interrupted");
            }
        };
        executor.scheduleWithFixedDelay(task1, 0, 1, TimeUnit.SECONDS);
    }
}

