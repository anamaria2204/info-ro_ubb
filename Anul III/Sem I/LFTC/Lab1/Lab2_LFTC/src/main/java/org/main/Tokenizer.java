package org.main;

import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Tokenizer {

    private static final Map<String, String> COMPOSITE_ATOMS_REGEX = new LinkedHashMap<>();
    static {
        COMPOSITE_ATOMS_REGEX.put("int main", "int\\s+main\\s*");
    }

    private static final Set<String> keywords = new HashSet<>(Arrays.asList(
            "int", "float", "char", "struct",
            "if", "else", "while",
            "cin", "cout",
            "return"
    ));

    private static final List<String> operators = new ArrayList<>(Arrays.asList(
            ">>", "<<", ">=", "<=", "==", "!=", "+", "-", "*", "/", "%", "=", ">", "<"
    ));

    private static final Set<Character> symbols = new HashSet<>(Arrays.asList(
            '{', '}', '(', ')', ';', ','
    ));

    public static void main(String[] args) {

        List<String> atoms = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader("input.txt"))) {
            String line;
            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) continue;

                line = line.replace("–", "-").replace("—", "-");

                for (Map.Entry<String, String> entry : COMPOSITE_ATOMS_REGEX.entrySet()) {
                    String atom = entry.getKey();
                    String regex = entry.getValue();
                    Pattern pattern = Pattern.compile(regex);
                    Matcher matcher = pattern.matcher(line);
                    while (matcher.find()) {
                        atoms.add(atom);
                        line = matcher.replaceFirst("");
                        matcher = pattern.matcher(line);
                    }
                }

                int i = 0;
                while (i < line.length()) {
                    char c = line.charAt(i);

                    if (Character.isWhitespace(c)) {
                        i++;
                        continue;
                    }

                    if (symbols.contains(c)) {
                        atoms.add(String.valueOf(c));
                        i++;
                        continue;
                    }

                    boolean matchedOp = false;
                    for (String op : operators) {
                        if (line.startsWith(op, i)) {
                            atoms.add(op);
                            i += op.length();
                            matchedOp = true;
                            break;
                        }
                    }
                    if (matchedOp) continue;

                    if (Character.isDigit(c)) {
                        StringBuilder sb = new StringBuilder();
                        while (i < line.length() && Character.isDigit(line.charAt(i))) {
                            sb.append(line.charAt(i));
                            i++;
                        }
                        atoms.add(sb.toString());
                        continue;
                    }

                    if (Character.isLetter(c)) {
                        StringBuilder sb = new StringBuilder();
                        while (i < line.length() && Character.isLetter(line.charAt(i))) {
                            sb.append(line.charAt(i));
                            i++;
                        }
                        String token = sb.toString();
                        if (keywords.contains(token)) {
                            atoms.add(token);
                        } else {
                            atoms.add(token);
                        }
                        continue;
                    }

                    i++;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        try (BufferedWriter bw = new BufferedWriter(new FileWriter("output.txt"))) {
            for (String atom : atoms) {
                bw.write(atom + "\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
