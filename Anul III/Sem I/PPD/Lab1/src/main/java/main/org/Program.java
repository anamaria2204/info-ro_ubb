package main.org;

import java.io.*;
import java.util.Locale;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Program {

    static final int N = 10000;
    static final int M = 10000;
    static final int K = 5;

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Eroare: Specificati modul ('gen', 'secv', 'par_linii P', 'par_coloane P', 'verifica_linii', 'verifica_coloane')");
            return;
        }

        String mod = args[0];

        if (mod.equals("gen")) {
            FisierUtil.generareFisierInputBinar(N, M, K);
            return;
        }
        if (mod.equals("verifica_linii")) {
            FisierUtil.verificaFisiere("output_secvential.bin", "output_paralel_linii.bin", N, M);
            return;
        }
        if (mod.equals("verifica_coloane")) {
            FisierUtil.verificaFisiere("output_secvential.bin", "output_paralel_coloane.bin", N, M);
            return;
        }

        float[] f, c, v, temp_v;
        try {
            long totalElements = (long) N * M;
            if (totalElements > Integer.MAX_VALUE) {
                 System.err.println("Eroare: Matricea este prea mare pentru indexarea ca array Java.");
                 return;
            }
            f = new float[(int)totalElements];
            c = new float[K * K];
            v = new float[(int)totalElements];
            temp_v = new float[(int)totalElements];
        } catch (OutOfMemoryError e) {
            System.err.println("Eroare memorie. Rulati cu mai multa memorie (ex: java -Xmx4g " + Program.class.getName() + " " + mod + ")");
            return;
        }

        try (DataInputStream dis = new DataInputStream(new BufferedInputStream(new FileInputStream("input.bin")))) {
            FisierUtil.citireMatriceBinar(dis, f);
            FisierUtil.citireMatriceBinar(dis, c);
        } catch (IOException e) {
            System.err.println("Eroare la citirea 'input.bin'. Ruleaza 'gen' intai.");
            return;
        }

        long startTime = System.nanoTime();

        if (mod.equals("secv")) {
            ConvolutieSecvential.convolutieSecv(f, c, temp_v, N, M, K);

            long endTime = System.nanoTime();
            System.out.printf(Locale.US, "%.6f%n", (endTime - startTime) / 1_000_000.0);
            FisierUtil.scriereMatriceBinar("output_secvential.bin", f);

        } else if (mod.equals("par_linii") || mod.equals("par_coloane")) {

            if (args.length < 2) {
                System.err.println("Eroare: Specificati numarul de thread-uri P");
                return;
            }

            try {
                int P = Integer.parseInt(args[1]);
                if (P <= 0) {
                     System.err.println("Eroare: P trebuie sa fie un numar pozitiv.");
                     return;
                }

                boolean esteOrizontal = mod.equals("par_linii");
                String outputFilename = esteOrizontal ? "output_paralel_linii.bin" : "output_paralel_coloane.bin";

                ExecutorService executor = Executors.newFixedThreadPool(P);
                for (int t = 0; t < P; t++) {
                    Runnable worker = new ConvolutieWorker(f, c, v, N, M, K, t, P, esteOrizontal);
                    executor.submit(worker);
                }
                executor.shutdown();

                if (!executor.awaitTermination(1, TimeUnit.HOURS)) {
                    System.err.println("Eroare: Thread-urile nu au terminat intr-o ora!");
                    executor.shutdownNow();
                }

                System.arraycopy(v, 0, f, 0, N * M);
                long endTime = System.nanoTime();
                System.out.printf(Locale.US, "%.6f%n", (endTime - startTime) / 1_000_000.0);
                FisierUtil.scriereMatriceBinar(outputFilename, f);

            } catch (NumberFormatException e) {
                System.err.println("Eroare: P ('" + args[1] + "') trebuie sa fie un numar intreg.");
            } catch (InterruptedException e) {
                System.err.println("Eroare: Asteptarea thread-urilor a fost intrerupta.");
                Thread.currentThread().interrupt();
            }

        } else {
            System.err.println("Mod necunoscut: " + mod);
        }
    }
}