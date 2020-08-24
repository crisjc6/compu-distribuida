package ec.edu.epn.pdc;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.IntStream;

import static ec.edu.epn.pdc.ConcurrentUtils.stop;

public class ReentranteLock {
    ReentrantLock lock = new ReentrantLock();
    public static int count = 0;
    void increment() {
        lock.lock();
        try {
            count++;
        } finally {
            lock.unlock();
        }
    }
    public static void main (String argvs[]) {
        ReentranteLock rl = new ReentranteLock();
        ExecutorService executor = Executors.newFixedThreadPool(2);
        IntStream.range(0, 10000)
                .forEach(i -> executor.submit(rl::increment));
        stop(executor);
        System.out.println(count);
    }
}
