package ec.edu.epn.pdc;

public class Hilos1 extends Thread {
    public void run() {  // override metodo run() de clase Thread
        System.out.println("Hola from new thread");
        try {
            sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    public static void main (String args[]) throws InterruptedException {
        Thread th_array[];
        th_array = new Thread[4];
        Hilos1 nh = new Hilos1();
        Hilos1 nh2 = new Hilos1();
        nh.start();
        nh2.start();
        System.out.printf("Hay %d hilos activos\n", activeCount());
        int n = enumerate (th_array);
        for (int i=0; i<n; i++)
            System.out.printf("Hilo %d: %s\n", i, th_array[i]);
        nh.join();
        nh2.join();
    }
}