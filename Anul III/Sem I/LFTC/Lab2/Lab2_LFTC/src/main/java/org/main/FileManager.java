package org.main;
import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

public class FileManager {

    /**
     * CERINȚA 1: Citește un AF dintr-un fișier, conform EBNF-ului specificat.
     */
    public static FiniteAutomata readFA(String filePath) throws Exception {
        FiniteAutomata fa = new FiniteAutomata();

        String content = new BufferedReader(new FileReader(filePath)).lines()
                .collect(Collectors.joining());

        // Regex pentru a extrage cuvântul cheie și conținutul dintre paranteze
        Pattern declarationPattern = Pattern.compile("(\\w+)\\((.*?)\\)");

        // Împărțim fișierul la ";" pentru a obține fiecare declarație
        String[] declarations = content.split(";");

        for (String decl : declarations) {
            if (decl.trim().isEmpty()) continue;

            Matcher matcher = declarationPattern.matcher(decl.trim());
            if (!matcher.find()) {
                throw new Exception("Declarație invalidă: " + decl);
            }

            String keyword = matcher.group(1).trim();
            String value = matcher.group(2).trim();

            switch (keyword) {
                case "stari":
                    parseStates(fa, value);
                    break;
                case "alfabet":
                    parseAlphabet(fa, value);
                    break;
                case "initiala":
                    parseInitialState(fa, value);
                    break;
                case "finale":
                    parseFinalStates(fa, value);
                    break;
                case "tranzitii":
                    parseTransitions(fa, value);
                    break;
                default:
                    throw new Exception("Cuvânt cheie necunoscut: " + keyword);
            }
        }
        return fa;
    }

    // --- Metode ajutătoare pentru parsare ---

    private static void parseStates(FiniteAutomata fa, String value) {
        List<State> states = Arrays.stream(value.split(","))
                .map(String::trim)
                .map(State::new)
                .collect(Collectors.toList());
        fa.setAllStates(states);
    }

    private static void parseAlphabet(FiniteAutomata fa, String value) {
        List<Alphabet> alphabet = Arrays.stream(value.split(","))
                .map(String::trim)
                .map(Alphabet::new)
                .collect(Collectors.toList());
        fa.setAlphabet(alphabet);
    }

    private static void parseInitialState(FiniteAutomata fa, String value) throws Exception {
        State initialState = findStateByName(fa.getAllStates(), value.trim());
        fa.setInitialState(initialState);
    }

    private static void parseFinalStates(FiniteAutomata fa, String value) {
        List<State> finalStates = Arrays.stream(value.split(","))
                .map(String::trim)
                .map(name -> {
                    try {
                        return findStateByName(fa.getAllStates(), name);
                    } catch (Exception e) {
                        return null; // Sau gestionează eroarea
                    }
                })
                .filter(Objects::nonNull)
                .collect(Collectors.toList());
        fa.setFinalStates(finalStates);
    }

    private static void parseTransitions(FiniteAutomata fa, String value) throws Exception {
        Pattern transitionPattern = Pattern.compile("(q[0-9]+)(q[0-9]+)\\s+(.+)");

        String[] transitionsStr = value.split(",");
        List<Transition> transitions = new ArrayList<>();

        for (String tStr : transitionsStr) {
            Matcher matcher = transitionPattern.matcher(tStr.trim());
            if (!matcher.find()) {
                throw new Exception("Format tranziție invalid: " + tStr);
            }

            String fromStateName = matcher.group(1).trim();
            String toStateName = matcher.group(2).trim();
            String symbolName = matcher.group(3).trim();

            // Găsim obiectele corespunzătoare
            State from = findStateByName(fa.getAllStates(), fromStateName);
            State to = findStateByName(fa.getAllStates(), toStateName);
            Alphabet symbol = findSymbolByName(fa.getAlphabet(), symbolName);

            transitions.add(new Transition(from, to, symbol));
        }
        fa.setTransitions(transitions);
    }

    // --- Utilitare pentru parsare ---

    private static State findStateByName(List<State> states, String name) throws Exception {
        return states.stream()
                .filter(s -> s.getName().equals(name))
                .findFirst()
                .orElseThrow(() -> new Exception("Starea '" + name + "' nu a fost definită în 'stari'."));
    }

    private static Alphabet findSymbolByName(List<Alphabet> alphabet, String name) throws Exception {
        return alphabet.stream()
                .filter(a -> a.getSymbol().equals(name))
                .findFirst()
                .orElseThrow(() -> new Exception("Simbolul '" + name + "' nu a fost definit în 'alfabet'."));
    }
}
