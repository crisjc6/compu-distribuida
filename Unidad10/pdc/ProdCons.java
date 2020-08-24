package ec.edu.epn.pdc;

public class ProdCons {
    private final Object[] array;
    private int putptr = 0;
    private int takeptr = 0;
    private int numel = 0;
    public ProdCons (int capacity) throws IllegalArgumentException {
        if (capacity <= 0)
            throw new IllegalArgumentException();
        array = new Object[capacity];
    }
    public synchronized  int size () { return numel;}
    public int capacity() {return array.length;}
    public synchronized void put (Object obj) throws InterruptedException {
        while (numel == array.length)
            wait();
        array[putptr] = obj;
        putptr = (putptr + 1) % array.length;
        if (numel++ == 0)
            notifyAll();
    }
    public synchronized Object take() throws InterruptedException {
        while (numel == 0)
            wait();
        Object x = array[takeptr];
        takeptr = (takeptr + 1) % array.length;
        if (numel-- == array.length)
            notifyAll();
        return x;
    }
}
