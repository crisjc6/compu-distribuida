package ec.edu.epn.pdc;

public class Hilos2 implements Runnable {
     public void run() {
         System.out.println("Hola from new thread Runnable");
     }
    public static void main (String args[]) {
        Hilos2 nh = new Hilos2();
        Thread th = new Thread(nh);
        th.start();
    }
}
