package org.main;

public class ConvolutieSecvential {

    public static void aplicaConvolutieSecventialInPlaceLinii(float[] f, float[] c, int N, int M, int K) {

        float[] prev_line = new float[M];
        float[] temp_line = new float[M];

        System.arraycopy(f, 0, prev_line, 0, M);

        int nrBorder = (K - 1) / 2; // k=3 -> nrBorder=1

        for (int i = 0; i < N; i++) {
            float[] r_sus = (i == 0) ? prev_line : prev_line;
            float[] r_mid = (i == 0) ? prev_line : f; // Daca i > 0, r_mid e f[i*M]
            int r_mid_offset = (i == 0) ? 0 : i * M;
            float[] r_jos = (i + 1 >= N) ? r_mid : f; // Daca i+1 e N, r_jos e r_mid. Altfel e f[(i+1)*M]
            int r_jos_offset = (i + 1 >= N) ? r_mid_offset : (i + 1) * M;

            for (int j = 0; j < M; j++) {
                float suma = 0.0f;
                for (int li = -nrBorder; li <= nrBorder; li++) {
                    float[] sursa_linie;
                    int sursa_offset;

                    if (li == -1) { sursa_linie = r_sus; sursa_offset = 0; }
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

            if (i < N - 1) {
                System.arraycopy(r_mid, r_mid_offset, prev_line, 0, M);
            }

            System.arraycopy(temp_line, 0, f, i * M, M);
        }
    }

    private static int clamp(int val, int min, int max) {
        return Math.max(min, Math.min(max, val));
    }
}