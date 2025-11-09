package org.main;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class ConvolutieWorker implements Runnable {

    private final float[] f, c;
    private final int N, M, K;
    private final int start_row, end_row;
    private final CyclicBarrier barieraSincronizare;

    public ConvolutieWorker(float[] f, float[] c, int N, int M, int K,
                            int tid, int P, CyclicBarrier bariera) {
        this.f = f;
        this.c = c;
        this.N = N;
        this.M = M;
        this.K = K;
        this.barieraSincronizare = bariera;

        // Impartirea pe linii
        int chunk = N / P;
        int rem = N % P;
        if (tid < rem) {
            this.start_row = tid * (chunk + 1);
            this.end_row = this.start_row + (chunk + 1);
        } else {
            this.start_row = tid * chunk + rem;
            this.end_row = this.start_row + chunk;
        }
    }

    private int clamp(int val, int min, int max) {
        return Math.max(min, Math.min(max, val));
    }

    @Override
    public void run() {
        float[] sus_buffer = new float[M];
        float[] jos_buffer = null;
        float[] temp_line = new float[M];
        int nrBorder = (K - 1) / 2; // = 1

        if (start_row > 0) {
            System.arraycopy(f, (start_row - 1) * M, sus_buffer, 0, M);
        } else {
            System.arraycopy(f, 0, sus_buffer, 0, M);
        }

        if (end_row < N && end_row > start_row) {
             jos_buffer = new float[M];
             System.arraycopy(f, end_row * M, jos_buffer, 0, M);
        }

        try {
            // Asteapta ca toate thread-urile sa termine de copiat frontierele
            barieraSincronizare.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
            return;
        }

        float[] current_prev_line = sus_buffer;

        for (int i = start_row; i < end_row; i++) {
            float[] r_sus = current_prev_line; // Linia i-1 (din bufferul local)
            int r_sus_offset = 0;

            float[] r_mid = f;
            int r_mid_offset = i * M;

            float[] r_jos;
            int r_jos_offset;

            if (i + 1 == end_row && jos_buffer != null) {
                r_jos = jos_buffer;
                r_jos_offset = 0;
            } else if (i + 1 >= N) {
                r_jos = r_mid;
                r_jos_offset = r_mid_offset;
            } else {
                r_jos = f;
                r_jos_offset = (i + 1) * M;
            }

            for (int j = 0; j < M; j++) {
                float suma = 0.0f;
                for (int li = -nrBorder; li <= nrBorder; li++) {
                    float[] sursa_linie;
                    int sursa_offset;

                    if (li == -1) { sursa_linie = r_sus; sursa_offset = r_sus_offset; }
                    else if (li == 0) { sursa_linie = r_mid; sursa_offset = r_mid_offset; }
                    else { sursa_linie = r_jos; sursa_offset = r_jos_offset; }

                    for (int lj = -nrBorder; lj <= nrBorder; lj++) {
                        int c_idx = clamp(j + lj, 0, M - 1);
                        float val_pixel = sursa_linie[sursa_offset + c_idx];
                        int k_r_idx = li + nrBorder;
                        int k_c_idx = lj + nrBorder;
                        suma += val_pixel * c[k_r_idx * K + k_c_idx];
                    }
                }
                temp_line[j] = suma;
            }

            if (i + 1 < end_row) {
                 System.arraycopy(f, r_mid_offset, current_prev_line, 0, M);
            }
            System.arraycopy(temp_line, 0, f, i * M, M);
        }
    }
}