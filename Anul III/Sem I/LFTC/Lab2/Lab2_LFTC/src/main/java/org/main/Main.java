package org.main;

import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

public class Main {

    static FiniteAutomata finiteAutomata = new FiniteAutomata();
    static Scanner scanner = new Scanner(System.in);

    public static void printMenu() {
        System.out.println("\n--- Meniu Automat Finit ---");
        System.out.println("1. Citeste automatul din fisier (format EBNF).");
        System.out.println("2. Citeste automatul de la tastatura.");
        System.out.println("3. Afiseaza definitia EBNF a formatului de fisier.");
        System.out.println("4. Verifica daca o secventa este acceptata.");
        System.out.println("5. Afiseaza cel mai lung prefix acceptat dintr-o secventa.");
        System.out.println("6. Afiseaza multimea starilor (Q).");
        System.out.println("7. Afiseaza alfabetul (Sigma).");
        System.out.println("8. Afiseaza multimea starilor finale (F).");
        System.out.println("9. Afiseaza multimea tranzitiilor (Delta).");
        System.out.println("10. Afiseaza starea initiala (q0).");
        System.out.println("11. Afiseaza automatul complet.");
        System.out.println("12. Iesire.");
        System.out.print("Alege optiunea: ");
    }

    public static void readAutomataFromConsole() {
        try {
            FiniteAutomata newAF = new FiniteAutomata();

            System.out.println("Introdu starile (separate prin virgula, ex: q0,q1,q2):");
            String statesLine = scanner.nextLine();
            List<State> states = Arrays.stream(statesLine.split(","))
                    .map(String::trim).map(State::new).collect(Collectors.toList());
            newAF.setAllStates(states);

            System.out.println("Introdu alfabetul (separat prin virgula, ex: a,b,0):");
            String alphabetLine = scanner.nextLine();
            List<Alphabet> alphabet = Arrays.stream(alphabetLine.split(","))
                    .map(String::trim).map(Alphabet::new).collect(Collectors.toList());
            newAF.setAlphabet(alphabet);

            System.out.println("Introdu starea initiala (ex: q0):");
            String initialName = scanner.nextLine().trim();
            newAF.setInitialState(new State(initialName));

            System.out.println("Introdu starile finale (separate prin virgula, ex: q2):");
            String finalStatesLine = scanner.nextLine();
            List<State> finalStates = Arrays.stream(finalStatesLine.split(","))
                    .map(String::trim).map(State::new).collect(Collectors.toList());
            newAF.setFinalStates(finalStates);

            List<Transition> transitions = new ArrayList<>();
            System.out.println("Introdu tranzitiile (format 'q0q1 a'). Scrie 'gata' cand termini:");
            while (true) {
                String line = scanner.nextLine().trim();
                if (line.equalsIgnoreCase("gata")) {
                    break;
                }

                java.util.regex.Pattern p = java.util.regex.Pattern.compile("(q[0-9]+)(q[0-9]+)\\s+(.+)");
                java.util.regex.Matcher m = p.matcher(line);

                if (m.find()) {
                    State from = new State(m.group(1));
                    State to = new State(m.group(2));
                    Alphabet symbol = new Alphabet(m.group(3));
                    transitions.add(new Transition(from, to, symbol));
                    System.out.println("Tranzitie adaugata: " + from.getName() + " -> " + to.getName() + " cu " + symbol.getSymbol());
                } else {
                    System.out.println("Format invalid. Incearca din nou (ex: q0q1 a) sau scrie 'gata'.");
                }
            }
            newAF.setTransitions(transitions);

            finiteAutomata = newAF;
            System.out.println("Automatul a fost citit de la tastatura!");

        } catch (Exception e) {
            System.err.println("Eroare la citirea de la tastatura: " + e.getMessage());
        }
    }

    public static void doAction(String option) {
        switch (option) {
            case "1": {
                System.out.print("Introdu numele fisierului: ");
                String fileName = scanner.nextLine();
                try {
                    String path = "src/main/resources/" + fileName;
                    finiteAutomata = FileManager.readFA(path);
                    System.out.println("Automatul a fost citit cu succes!");
                    System.out.println(finiteAutomata);
                } catch (Exception e) {
                    System.err.println("Eroare la citirea fisierului: " + e.getMessage());
                }
                break;
            }
            case "2": {
                readAutomataFromConsole();
                break;
            }
            case "3": {
                System.out.println(finiteAutomata.getBNF());
                break;
            }
            case "4": {
                System.out.print("Introdu secventa de verificat: ");
                String sequence = scanner.nextLine();
                if (finiteAutomata.getAllStates().isEmpty()) {
                    System.out.println("Eroare: Nu este incarcat niciun automat.");
                    break;
                }
                if (finiteAutomata.acceptsSequence(sequence)) {
                    System.out.println("Rezultat: Secventa este ACCEPTATA.");
                } else {
                    System.out.println("Rezultat: Secventa este RESPINSA.");
                }
                break;
            }
            case "5": {
                System.out.print("Introdu secventa pentru prefix: ");
                String sequence = scanner.nextLine();
                if (finiteAutomata.getAllStates().isEmpty()) {
                    System.out.println("Eroare: Nu este incarcat niciun automat.");
                    break;
                }
                String longestPrefix = finiteAutomata.longestPrefixAccepted(sequence);

                PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out, StandardCharsets.UTF_8), true);
                if (longestPrefix.isEmpty() && !finiteAutomata.getFinalStates().contains(finiteAutomata.getInitialState())) {
                    out.println("Rezultat: Nu exista un prefix acceptat.");
                } else {
                    out.println("Rezultat: Cel mai lung prefix acceptat este: \"" + longestPrefix + "\"");
                }
                break;
            }
            case "6": {
                System.out.println("Multimea starilor (Q): ");
                for (State state : finiteAutomata.getAllStates()) {
                    System.out.println(state);
                }
                break;
            }
            case "7": {
                System.out.println("Alfabetul (Sigma): ");
                for (Alphabet alphabet : finiteAutomata.getAlphabet()) {
                    System.out.println(alphabet);
                }
                break;
            }
            case "8": {
                System.out.println("Multimea starilor finale (F): ");
                for (State state : finiteAutomata.getFinalStates()) {
                    System.out.println(state);
                }
                break;
            }
            case "9": {
                System.out.println("Multimea tranzitiilor (Delta): ");
                for (Transition transition : finiteAutomata.getTransitions()) {
                    System.out.println(transition);
                }
                break;
            }
            case "10": {
                System.out.println("Starea initiala (q0): ");
                System.out.println(finiteAutomata.getInitialState());
                break;
            }
            case "11": {
                System.out.println(finiteAutomata);
                break;
            }
            case "12": {
                System.out.println("La revedere!");
                break;
            }
            default: {
                System.out.println("Optiune invalida! Te rog incearca din nou.");
                break;
            }
        }
    }

    public static void main(String[] args) {
        String option = "";
        while (true) {
            printMenu();
            option = scanner.nextLine().trim();

            if (option.equals("12")) {
                doAction(option);
                break;
            }

            doAction(option);
        }
        scanner.close();
    }
}