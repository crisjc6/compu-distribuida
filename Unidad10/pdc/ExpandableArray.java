package ec.edu.epn.pdc;

import java.util.NoSuchElementException;
import static java.lang.Thread.activeCount;

public class ExpandableArray {
    private Object[] data;
    private int size = 0;
    public ExpandableArray(int cap) { data = new Object[cap]; }
    public synchronized int size() {
        return size;
    }
    public synchronized Object get(int i) throws NoSuchElementException {
        if (i<0 || i >= size)
            throw new NoSuchElementException();
        return data[i];
    }
    public synchronized void add(Object x) {
        if (size == data.length) {
            Object[] od = data;
            data = new Object[3 * (size + 1)/2];
            System.arraycopy(od, 0, data, 0, od.length);
        }
        data[size++] = x;
    }
    public synchronized void removeLast() throws NoSuchElementException {
        if (size == 0)
            throw new NoSuchElementException();
        data[--size] = null;
    }
    public static void main (String args[]) {
        System.out.printf("Hay %d hilos activos\n", activeCount());
    }
}
