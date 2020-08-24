package ec.edu.epn.pdc;

import static ec.edu.epn.pdc.ConcurrentUtils.sleep;

public class Task1 {
    public static void main (String args[]) throws InterruptedException {
        Runnable task = () -> {
            sleep(1);
            String threadName = Thread.currentThread().getName();
            System.out.println("Hello " + threadName);
        };
        task.run();
        Thread thread = new Thread(task);
        thread.start();
        //thread.join();
        System.out.println("Done!");
        //System.exit(1);
    }
}
