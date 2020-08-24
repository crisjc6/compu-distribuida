package ec.edu.epn.pdc;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

public class MapaConcurrente {
    public static void main (String argvs[]) {
        ConcurrentMap<String, String> map = new ConcurrentHashMap<>();
        map.put("foo", "bar");
        map.put("han", "solo");
        map.put("r2", "d2");
        map.put("c3", "p0");

        map.forEach((key, value) -> System.out.printf("%s = %s\n", key, value));
        String value = map.putIfAbsent("c3", "p1");
        System.out.println(value);
        String value1 = map.getOrDefault("hi", "there");
        System.out.println(value1);

        map.replaceAll((key, value2) -> "r2".equals(key) ? "d3" : value2);
        System.out.println(map.get("r2"));

        map.compute("foo", (key, value3) -> value3 + value3); //computeIfAbsent(); computeIfPresent()
        System.out.println(map.get("foo"));

        map.merge("foo", "boo", (oldVal, newVal) -> newVal + " was " + oldVal);
        System.out.println(map.get("foo"));   // boo was foo
    }
}
