package main.org;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

public class LexicalAnalyzer {
    private static class Token {
        String type;
        String value;

        public Token(String type, String value) {
            this.type = type;
            this.value = value;
        }
    }

    private final Map<String, Integer> tokenCodes = new LinkedHashMap<>();
    private final SymbolTable symbolTable = new SymbolTable();
    private final PIF pif = new PIF();
    private final List<String> operators;
    private int nextCode = 2;

    public LexicalAnalyzer() {
        tokenCodes.put("identifier", 0);
        tokenCodes.put("constant", 1);
        tokenCodes.put("int main", nextCode++);

        List<String> keywords = Arrays.asList("int", "if", "else", "while", "cin", "cout", "return");
        operators = Arrays.asList(">>", "<<", ">=", "<=", "==", "!=", "+", "-", "*", "/", "%", "=", ">", "<");
        List<String> separators = Arrays.asList(";", ",", "{", "}", "(", ")");

        keywords.forEach(kw -> tokenCodes.put(kw, nextCode++));
        operators.forEach(op -> tokenCodes.put(op, nextCode++));
        separators.forEach(sep -> tokenCodes.put(sep, nextCode++));

        operators.sort((a, b) -> Integer.compare(b.length(), a.length()));
    }

    public void analyze(String sourceFile) throws IOException {
        List<String> errors = new ArrayList<>();
        List<Token> allTokens = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(sourceFile))) {
            String line;
            int lineNumber = 1;
            while ((line = br.readLine()) != null) {
                line = line.replace("–", "-").replace("—", "-");
                int i = 0;
                while (i < line.length()) {
                    if (Character.isWhitespace(line.charAt(i))) {
                        i++;
                        continue;
                    }

                    if (line.startsWith("int main", i)) {
                        allTokens.add(new Token("int main", "int main"));
                        i += 8;
                        continue;
                    }

                    boolean operatorFound = false;
                    for (String op : operators) {
                        if (line.startsWith(op, i)) {
                            allTokens.add(new Token(op, op));
                            i += op.length();
                            operatorFound = true;
                            break;
                        }
                    }
                    if (operatorFound) continue;

                    String oneChar = String.valueOf(line.charAt(i));
                    if (tokenCodes.containsKey(oneChar) && !isIdentifier(oneChar) && !isConstant(oneChar)) {
                        allTokens.add(new Token(oneChar, oneChar));
                        i++;
                        continue;
                    }

                    if (Character.isLetter(line.charAt(i))) {
                        StringBuilder sb = new StringBuilder();
                        while (i < line.length() && Character.isLetterOrDigit(line.charAt(i))) {
                            sb.append(line.charAt(i));
                            i++;
                        }
                        String word = sb.toString();
                        if (tokenCodes.containsKey(word)) {
                            allTokens.add(new Token(word, word));
                        } else {
                            allTokens.add(new Token("identifier", word));
                            symbolTable.insert(word);
                        }
                        continue;
                    }

                    if (Character.isDigit(line.charAt(i))) {
                         StringBuilder sb = new StringBuilder();
                        while (i < line.length() && Character.isDigit(line.charAt(i))) {
                            sb.append(line.charAt(i));
                            i++;
                        }
                        String number = sb.toString();
                        allTokens.add(new Token("constant", number));
                        symbolTable.insert(number);
                        continue;
                    }

                    errors.add("Eroare lexicală la linia " + lineNumber + ": caracter necunoscut -> " + line.charAt(i));
                    i++;
                }
                lineNumber++;
            }
        }

        if (errors.isEmpty()) {
            for (Token token : allTokens) {
                int code = tokenCodes.get(token.type);
                int tsPosition = -1;
                if (token.type.equals("identifier") || token.type.equals("constant")) {
                    tsPosition = symbolTable.getPosition(token.value);
                }
                pif.add(token.value, code, tsPosition);
            }

            symbolTable.writeToFile("ts.txt");
            pif.writeToFile("fip.txt");
            System.out.println("Analiza lexicală a fost finalizată cu succes!");
        } else {
            System.out.println("S-au găsit erori lexicale:");
            errors.forEach(System.out::println);
        }
    }

    private boolean isIdentifier(String token) {
        return Pattern.matches("^[a-zA-Z_][a-zA-Z0-9_]*$", token);
    }

    private boolean isConstant(String token) {
        return Pattern.matches("^(0|[1-9][0-9]*)$", token);
    }
}