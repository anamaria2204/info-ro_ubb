package org.main;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

public class FiniteAutomata {

    private List<State> allStates;
    private List<Alphabet> alphabet;
    private State initialState;
    private List<State> finalStates;
    private List<Transition> transitions;

    public FiniteAutomata() {
        this.allStates = new ArrayList<>();
        this.alphabet = new ArrayList<>();
        this.finalStates = new ArrayList<>();
        this.transitions = new ArrayList<>();
    }

    public List<State> getAllStates() { return allStates; }
    public void setAllStates(List<State> allStates) { this.allStates = allStates; }
    public List<Alphabet> getAlphabet() { return alphabet; }
    public void setAlphabet(List<Alphabet> alphabet) { this.alphabet = alphabet; }
    public State getInitialState() { return initialState; }
    public void setInitialState(State initialState) { this.initialState = initialState; }
    public List<State> getFinalStates() { return finalStates; }
    public void setFinalStates(List<State> finalStates) { this.finalStates = finalStates; }
    public List<Transition> getTransitions() { return transitions; }
    public void setTransitions(List<Transition> transitions) { this.transitions = transitions; }

    private Optional<Transition> findTransition(State currentState, Alphabet symbol) {
        return transitions.stream()
                .filter(t -> t.getFromState().equals(currentState) && t.getWithSymbol().equals(symbol))
                .findFirst();
    }

    public boolean isDFA() {
        for (State state : allStates) {
            for (Alphabet symbol : alphabet) {
                long count = transitions.stream()
                        .filter(t -> t.getFromState().equals(state) && t.getWithSymbol().equals(symbol))
                        .count();
                // Dacă există mai mult de o tranziție pentru (stare, simbol), e AFN
                if (count > 1) {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * CERINȚA 3: Verifică dacă o secvență este acceptată de automat (doar pt. AFD).
     */
    public boolean acceptsSequence(String sequence) {
        if (!isDFA()) {
            System.out.println("Verificarea este implementată doar pentru AFD-uri.");
            return false;
        }

        State currentState = initialState;
        if (currentState == null) return false;

        for (char symbolChar : sequence.toCharArray()) {
            Alphabet symbol = new Alphabet(String.valueOf(symbolChar));

            Optional<Transition> transition = findTransition(currentState, symbol);

            if (transition.isEmpty()) {
                // Nu există tranziție, secvența este blocată (respinsă)
                return false;
            }

            currentState = transition.get().getToState();
        }

        // La final, verificăm dacă starea curentă este finală
        return finalStates.contains(currentState);
    }

    public String longestPrefixAccepted(String sequence) {
        if (!isDFA()) {
            System.out.println("Verificarea este implementată doar pentru AFD-uri.");
            return "";
        }

        State currentState = initialState;
        String longestPrefix = "";
        String currentPrefix = "";

        if (currentState == null) return "";

        if (finalStates.contains(currentState)) {
            longestPrefix = "";
        }

        for (char symbolChar : sequence.toCharArray()) {
            Alphabet symbol = new Alphabet(String.valueOf(symbolChar));

            Optional<Transition> transition = findTransition(currentState, symbol);

            if (transition.isEmpty()) {
                break;
            }

            currentState = transition.get().getToState();
            currentPrefix += symbolChar;

            if (finalStates.contains(currentState)) {
                longestPrefix = currentPrefix;
            }
        }

        return longestPrefix;
    }

    @Override
    public String toString() {
        return "Automat Finit:\n" +
                "  Stări: " + allStates.stream().map(State::getName).collect(Collectors.joining(", ")) + "\n" +
                "  Alfabet: " + alphabet.stream().map(Alphabet::getSymbol).collect(Collectors.joining(", ")) + "\n" +
                "  Stare Inițială: " + (initialState != null ? initialState.getName() : "N/A") + "\n" +
                "  Stări Finale: " + finalStates.stream().map(State::getName).collect(Collectors.joining(", ")) + "\n" +
                "  Tranziții:\n    " + transitions.stream().map(Transition::toString).collect(Collectors.joining("\n    ")) + "\n";
    }

    public String getBNF() {
        return "automat_finit ::= lista_declarari\n" +
               "lista_declarari ::= declaratie | declaratie, \";\", lista_declarari\n" +
               "declaratie ::= \"stari\", \"(\", lista_stari, \")\" | ... (restul EBNF-ului)";
    }
}
