package ec.edu.epn.pdc;

import java.util.concurrent.TimeUnit;

public class TaskSleep {
    public static void main (String[] argvs) throws InterruptedException {
        Runnable runnable = () -> {
            try {
                String name = Thread.currentThread().getName();
                System.out.println("Foo " + name + " durmiento 1 segundo...");
                TimeUnit.SECONDS.sleep(1);
                System.out.println("Bar " + name);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        };
        Thread thread = new Thread(runnable);
        thread.start();
        thread.join();
    }
}
