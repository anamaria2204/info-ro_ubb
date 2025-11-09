package main.org;

public class ConvolutieSecvential {
    public static void convolutieSecv(float[] f, float[] c, float[] temp_v, int N, int M, int K) {

        int nrBorder = (K - 1) / 2;

        for (int i = 0; i < N; i++) {
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
                temp_v[i * M + j] = suma;
            }
        }
        System.arraycopy(temp_v, 0, f, 0, N * M);
    }
    private static int clamp(int val, int min, int max) {
        return Math.max(min, Math.min(max, val));
    }
}
