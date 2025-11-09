package org.main;
import java.io.*;
import java.util.Locale;
import java.util.Random;

public class FisierUtil {

    public static void generareFisierInputBinar(int N, int M, int K) {
        System.out.println("Se genereaza 'input.bin'...");
        try (DataOutputStream dos = new DataOutputStream(
                new BufferedOutputStream(
                        new FileOutputStream("input.bin")))) {

            Random rand = new Random();
            long totalElements = (long) N * M;

            for (long i = 0; i < totalElements; i++) {
                dos.writeFloat((float) (rand.nextInt(256)));
            }

            for (int i = 0; i < K * K; i++) {
                dos.writeFloat(rand.nextFloat());
            }

            System.out.println("Fisierul 'input.bin' a fost generat.");

        } catch (IOException e) {
            System.err.println("Eroare la generarea fisierului de input: " + e.getMessage());
            e.printStackTrace();
        }
    }

    public static void citireMatriceBinar(DataInputStream dis, float[] mat) throws IOException {
        for (int i = 0; i < mat.length; i++) {
            mat[i] = dis.readFloat();
        }
    }

    public static void scriereMatriceBinar(String filename, float[] mat) {
        try (DataOutputStream dos = new DataOutputStream(
                new BufferedOutputStream(
                        new FileOutputStream(filename)))) {

            for (int i = 0; i < mat.length; i++) {
                dos.writeFloat(mat[i]);
            }

        } catch (IOException e) {
            System.err.println("Eroare la scrierea fisierului '" + filename + "': " + e.getMessage());
            e.printStackTrace();
        }
    }

    public static boolean verificaFisiere(String f1, String f2, int N, int M) {
        System.out.println("Se verifica fisierele '" + f1 + "' si '" + f2 + "' pentru identitate...");
        long totalElements = (long) N * M;

        try (DataInputStream dis1 = new DataInputStream(
                new BufferedInputStream(
                        new FileInputStream(f1)));
             DataInputStream dis2 = new DataInputStream(
                     new BufferedInputStream(
                             new FileInputStream(f2)))) {

            for (long i = 0; i < totalElements; i++) {
                float val1 = dis1.readFloat();
                float val2 = dis2.readFloat();

                if (val1 != val2) {
                    long linia = i / M;
                    long coloana = i % M;
                    System.err.println("--- VERIFICARE ESUATA! ---");
                    System.err.println("Prima diferenta gasita la: Linia " + linia + ", Coloana " + coloana);
                    System.err.printf(Locale.US, "  %s: %.8f | %s: %.8f%n", f1, val1, f2, val2);
                    return false;
                }
            }

            if (dis1.read() != -1 || dis2.read() != -1) {
                System.err.println("Eroare: Fisierele au dimensiuni diferite (unul este mai lung).");
                return false;
            }

        } catch (FileNotFoundException e) {
            System.err.println("Eroare: Unul dintre fisierele de output nu a fost gasit. Ruleaza 'secv' si 'par_' intai.");
            return false;
        } catch (EOFException e) {
            System.err.println("Eroare: Fisierele au dimensiuni diferite (unul este mai scurt). Verificarea a eșuat.");
            return false;
        } catch (IOException e) {
            System.err.println("Eroare I/O in timpul verificarii: " + e.getMessage());
            e.printStackTrace();
            return false;
        }

        System.out.println("--- VERIFICARE REUSITA! --- Fisierele sunt absolut identice.");
        return true;
    }
}