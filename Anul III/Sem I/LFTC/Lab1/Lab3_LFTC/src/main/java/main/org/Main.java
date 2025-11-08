package main.org;

import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        LexicalAnalyzer analyzer = new LexicalAnalyzer();
        try {
            analyzer.analyze("input.txt");
        } catch (IOException e) {
            System.err.println("Eroare critică: Nu s-a putut citi fișierul sursă. " + e.getMessage());
        }
    }
}