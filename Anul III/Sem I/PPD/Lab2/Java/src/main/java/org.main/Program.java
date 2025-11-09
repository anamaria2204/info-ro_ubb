package org.main;

import java.io.*;
import java.util.Locale;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Program {

    static final int N = 10000;
    static final int M = 10000;
    static final int K = 3;

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Eroare: Specificati modul ('gen', 'secv', 'paralel P', 'verifica')");
            return;
        }

        String mod = args[0];

        if (mod.equals("gen")) {
            FisierUtil.generareFisierInputBinar(N, M, K);
            return;
        }
        if (mod.equals("verifica")) {
            FisierUtil.verificaFisiere("output_secvential.bin", "output_paralel.bin", N, M);
            return;
        }

        float[] f, c;
        try {
            long totalElements = (long) N * M;
            if (totalElements > Integer.MAX_VALUE) {
                 System.err.println("Eroare: Matricea este prea mare pentru indexarea ca array Java.");
                 return;
            }
            f = new float[(int)totalElements];
            c = new float[K * K];
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

        float[] f_backup = new float[(int)(N*M)];
        System.arraycopy(f, 0, f_backup, 0, f.length);

        long startTime = System.nanoTime();

        if (mod.equals("secv")) {
            ConvolutieSecvential.aplicaConvolutieSecventialInPlaceLinii(f, c, N, M, K);

            long endTime = System.nanoTime();
            System.out.printf(Locale.US, "%.6f%n", (endTime - startTime) / 1e6);
            FisierUtil.scriereMatriceBinar("output_secvential.bin", f);

        } else if (mod.equals("paralel")) {
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

                System.arraycopy(f_backup, 0, f, 0, f.length);

                String outputFilename = "output_paralel.bin";

                // Cream o bariera de sincronizare pentru P thread-uri
                final CyclicBarrier bariera = new CyclicBarrier(P);

                ExecutorService executor = Executors.newFixedThreadPool(P);
                for (int t = 0; t < P; t++) {
                    // Trimitem bariera la fiecare worker
                    Runnable worker = new ConvolutieWorker(f, c, N, M, K, t, P, bariera);
                    executor.submit(worker);
                }
                executor.shutdown();

                if (!executor.awaitTermination(1, TimeUnit.HOURS)) {
                    System.err.println("Eroare: Thread-urile nu au terminat intr-o ora!");
                    executor.shutdownNow();
                }

                long endTime = System.nanoTime();
                System.out.printf(Locale.US, "%.6f%n", (endTime - startTime) / 1e6);
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