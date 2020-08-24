package ec.edu.epn.pdc;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Random;

public class MatrixMult extends Thread {
    static int A[][]; static int B[][]; static int C[][];
    static int n=3; int row;
    MatrixMult (int i) {
        row = i;
        this.start();
    }
    public void run() {
        int i,j;
        try {
            sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        for(i=0; i<n; i++) {
            C[row][i] = 0;
            for (j=0; j<n; j++)
                C[row][i] += A[row][j]*B[j][i];
        }

    }

    public static void ReadMatrix (int in[][]) {
        final Random rand = new Random(613);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                try {
                in[i][j] = rand.nextInt(1000);
                } catch (Exception e) {}
    }
    public static void PrintMatrix (int out[][]) {
        System.out.println ("MATRIZ: ");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                System.out.printf("%d ", out[i][j]);
            System.out.printf("\n");
        }
    }
    public static void main (String args[]) {
        int i, j;
        A = new int[n][n]; B = new int[n][n]; C = new int[n][n];
        ReadMatrix(A);
        ReadMatrix(B);
        MatrixMult mat[] = new MatrixMult[n];
        for (i=0; i<n; i++)
            mat[i] = new MatrixMult(i);
        PrintMatrix(C);
        try {
            for (i=0; i<n; i++)
                mat[i].join();
        } catch (Exception e) {}
        PrintMatrix(C);
    }
}
