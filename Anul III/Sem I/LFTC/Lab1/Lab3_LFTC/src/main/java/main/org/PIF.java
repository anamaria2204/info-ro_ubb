package main.org;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class PIF {
    private final List<PIFEntry> entries = new ArrayList<>();

    public void add(String token, int code, int position) {
        entries.add(new PIFEntry(token, code, position));
    }

    public void writeToFile(String filename) throws IOException {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(filename))) {
            bw.write("--- Forma Internă a Programului ---\n");
            for (PIFEntry entry : entries) {
                bw.write(entry.toString() + "\n");
            }
        }
    }
}
