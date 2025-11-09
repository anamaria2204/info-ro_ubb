package main.org;

public class ConvolutieWorker implements Runnable {

    private final float[] f, c, v;
    private final int N, M, K;
    private final int start, end;
    private final boolean esteOrizontal;

    public ConvolutieWorker(float[] f, float[] c, float[] v, int N, int M, int K,
                            int tid, int P, boolean esteOrizontal) {
        this.f = f;
        this.c = c;
        this.v = v;
        this.N = N;
        this.M = M;
        this.K = K;
        this.esteOrizontal = esteOrizontal;

        if (esteOrizontal) {
            int chunk = N / P;
            int rem = N % P;
            this.start = tid * chunk + Math.min(tid, rem);
            this.end = (tid + 1) * chunk + Math.min(tid + 1, rem);
        } else {
            int chunk = M / P;
            int rem = M % P;
            this.start = tid * chunk + Math.min(tid, rem);
            this.end = (tid + 1) * chunk + Math.min(tid + 1, rem);
        }
    }

    private int clamp(int val, int min, int max) {
        return Math.max(min, Math.min(max, val));
    }

    @Override
    public void run() {

        int nrBorder = (K - 1) / 2;

        if (esteOrizontal) {
            for (int i = start; i < end; i++) {
                for (int j = 0; j < M; j++) {

                    float suma = 0.0f;
                    for (int li = -nrBorder; li <= nrBorder; li++) {
                        for (int lj = -nrBorder; lj <= nrBorder; lj++) {

                            int r_idx = clamp(i + li, 0, N - 1);
                            int c_idx = clamp(j + lj, 0, M - 1);

                            int k_r_idx = li + nrBorder;
                            int k_c_idx = lj + nrBorder;

                            suma += f[r_idx * M + c_idx] * c[k_r_idx * K + k_c_idx];
                        }
                    }
                    v[i * M + j] = suma;
                }
            }
        } else {
            for (int i = 0; i < N; i++) {
                for (int j = start; j < end; j++) {

                    float suma = 0.0f;
                    for (int li = -nrBorder; li <= nrBorder; li++) {
                        for (int lj = -nrBorder; lj <= nrBorder; lj++) {

                            int r_idx = clamp(i + li, 0, N - 1);
                            int c_idx = clamp(j + lj, 0, M - 1);

                            int k_r_idx = li + nrBorder;
                            int k_c_idx = lj + nrBorder;

                            suma += f[r_idx * M + c_idx] * c[k_r_idx * K + k_c_idx];
                        }
                    }
                    v[i * M + j] = suma;
                }
            }
        }
    }
}
