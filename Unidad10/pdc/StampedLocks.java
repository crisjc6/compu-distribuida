package ec.edu.epn.pdc;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.StampedLock;

import static ec.edu.epn.pdc.ConcurrentUtils.sleep;
import static ec.edu.epn.pdc.ConcurrentUtils.stop;

public class StampedLocks {
    public static void main (String argvs[]) {
        ExecutorService executor = Executors.newFixedThreadPool(2);
        Map<String, String> map = new HashMap<>();
        StampedLock lock = new StampedLock();

        executor.submit(() -> {
            long stamp = lock.writeLock();
            try {
                sleep(1);
                map.put("foo", "bar");
            } finally {
                lock.unlockWrite(stamp);
            }
        });

        Runnable readTask = () -> {
            long stamp = lock.readLock();
            try {
                System.out.println(map.get("foo"));
                //sleep(1);
            } finally {
                lock.unlockRead(stamp);
            }
        };
        executor.submit(readTask);
        executor.submit(readTask);

        stop(executor);
    }
}
