package org.main;

public class Transition {
    private State fromState;
    private State toState;
    private Alphabet withSymbol;

    public Transition(State fromState, State toState, Alphabet withSymbol) {
        this.fromState = fromState;
        this.toState = toState;
        this.withSymbol = withSymbol;
    }

    public State getFromState() {
        return fromState;
    }

    public State getToState() {
        return toState;
    }

    public Alphabet getWithSymbol() {
        return withSymbol;
    }

    @Override
    public String toString() {
        // Formatul cerut de tine: "q0q1 +"
        return fromState.getName() + toState.getName() + " " + withSymbol.getSymbol();
    }
}
