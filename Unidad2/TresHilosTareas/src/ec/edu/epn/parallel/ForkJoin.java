package ec.edu.epn.parallel;
import java.util.Random;
import java.util.concurrent.RecursiveAction;
import java.util.concurrent.ForkJoinPool;

import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public final class ForkJoin {
    // Default constructor.
    private ForkJoin() {
    }
    static int count;

    public static int secTresFil(int[] X) {
        long startTime = System.nanoTime();
        int c = 0;
        for (int i = 0; i < X.length; i++) {
            if (X[i] == 3) c++;
        }
        long timeInNanos = System.nanoTime() - startTime;
        printResults("secTresFil", timeInNanos, c);
        return c;
    }

    public static int secTresCol(int[] X) {
        long startTime = System.nanoTime();
        int c = 0;
        for (int i = 0; i < X.length; i++) {
            if (X[i] == 3) c++;
        }
        long timeInNanos = System.nanoTime() - startTime;
        printResults("secTresCol", timeInNanos, c);
        return c;
    }

    public static int parTresTareas(int[] X) {
        long startTime = System.nanoTime();
        SumArray t = new SumArray(X, 0, X.length);
        ForkJoinPool.commonPool().invoke(t);
        int c = t.ans;
        long timeInNanos = System.nanoTime() - startTime;
        printResults("parTresTareas", timeInNanos, c);
        return c;
    }

    public static int parTresPriv(int[] X, int tasks) {
        long startTime = System.nanoTime();
        //int tasks = Runtime.getRuntime().availableProcessors();
        Thread[] threads = new Thread[tasks];
        final int chunkSize = (X.length + tasks - 1) / tasks;
        int[] c = new int[tasks];
        int count = 0;

        for (int ii = 0; ii < tasks; ii++) {
            final int i = ii;

            threads[ii] = new Thread(() -> {
                c[i] = 0;
                final int left = (i * chunkSize);
                int right = (left + chunkSize);
                if (right > X.length) right = X.length;

                for (int j = left; j < right; j++) {
                    if (X[j] == 3) c[i]++;
                }
            });
            threads[ii].start();
        }

        for (int ii = 0; ii < tasks; ii++) {
            try {
                threads[ii].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        for (int j=0; j<tasks; j++) count += c[j];
        long timeInNanos = System.nanoTime() - startTime;
        printResults("parTresPriv", timeInNanos, count);
        return count;
    }

    public static int parTresLocks(int[] X, int tasks) {
        long startTime = System.nanoTime();
        //int tasks = Runtime.getRuntime().availableProcessors();
        Thread[] threads = new Thread[tasks];
        final ReentrantLock lock = new ReentrantLock();
        final int chunkSize = (X.length + tasks - 1) / tasks;
        count = 0;

        for (int ii = 0; ii < tasks; ii++) {
            final int i = ii;
            threads[ii] = new Thread(() -> {
                final int left = (i * chunkSize);
                int right = (left + chunkSize);
                if (right > X.length) right = X.length;

                for (int j = left; j < right; j++) {
                    lock.lock();
                    if (X[j] == 3) count = count + 1;
                    lock.unlock();
                }
            });
            threads[ii].start();
        }
        for (int ii = 0; ii < tasks; ii++) {
            try {
                threads[ii].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        long timeInNanos = System.nanoTime() - startTime;
        printResults("parTresLocks", timeInNanos, count);
        return count;
    }

    public static void main(final String[] argv) {
        final String ERROR_MSG = "Mensaje de error";
        final int DEFAULT_N = 200000000;
        int n;
        if (argv.length != 0) {
            try {
                n = Integer.parseInt(argv[0]);
                if (n<=0) {
                    System.out.println (ERROR_MSG);
                    n = DEFAULT_N;
                }
            } catch (Throwable e) {
                System.out.println(ERROR_MSG);
                n = DEFAULT_N;
            }
        } else {
            n = DEFAULT_N;
        }
        int[] X = new int[n];
        Random r = new Random(123);

        for (int i = 0; i < n; i++) {
            X[i] = r.nextInt(10);
        }
        // Set number of workers used by ForkJoinPool.commonPool()
        System.setProperty ("java.util.concurrent.ForkJoinPool.common.parallelism", "6");

        for  (int numRun=0; numRun<5; numRun++) {
            System.out.printf ("Run %d\n", numRun);
            secTresFil(X);
            parTresTareas(X);
            parTresLocks(X, 2);
            parTresPriv(X, 2);
            parTresPriv(X, 4);
            parTresPriv(X, 8);
        }
    }

    private static void printResults(String name, long timeInNanos, double sum) {
        System.out.printf("  %s completo en %8.3f milisecs, sum = %8.5f \n",
                name, timeInNanos/1e6, sum);
    }

    private static class SumArray extends RecursiveAction {
        static int SEQUENTIAL_THRESHOLD = 5;
        int lo;
        int hi;
        int[] arr;
        int ans = 0;

        SumArray(int[] a, int l, int h) {
            lo = l;
            hi = h;
            arr = a;
        }

        protected void compute() {
            if (hi-lo <= SEQUENTIAL_THRESHOLD) {
                for (int i = lo; i < hi; i++)
                    if (arr[i] == 3)  ans += 1;
            } else {
                SumArray left = new SumArray(arr, lo, (hi+lo)/2);
                SumArray right = new SumArray(arr, (hi+lo)/2, hi);
                left.fork();
                right.compute();
                left.join();
                ans = left.ans + right.ans;
            }
        }
    }
}
