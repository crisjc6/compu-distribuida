package ec.edu.epn.pdc;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ForkJoinPool;

public class MapaHashConcurrente {
    public static void main (String argvs[]) {
        System.out.println(ForkJoinPool.getCommonPoolParallelism());
        ConcurrentHashMap<String, String> map = new ConcurrentHashMap<>();
        map.put("foo", "bar");
        map.put("han", "solo");
        map.put("r2", "d2");
        map.put("c3", "p0");

        System.out.printf("Prueba de forEach\n");
        map.forEach(1, (key, value) ->
                System.out.printf("K: %s; V: %s; Th: %s\n", key, value, Thread.currentThread().getName()));

        System.out.printf("Prueba de search\n");
        String result = map.searchValues(1, value -> {
            System.out.println(Thread.currentThread().getName());
            if (value.length() > 3) {
                return value;
            }
            return null;
        });
        System.out.println("Result (search): " + result);

        System.out.printf("Prueba de reduce\n");
        String result1 = map.reduce(1,
                (key, value) -> {
                    System.out.println("Transform: " + Thread.currentThread().getName());
                    return key + "=" + value;
                },
                (s1, s2) -> {
                    System.out.println("Reduce: " + Thread.currentThread().getName());
                    return s1 + ", " + s2;
                });
        System.out.println("Result (reduce): " + result1);
    }
}

