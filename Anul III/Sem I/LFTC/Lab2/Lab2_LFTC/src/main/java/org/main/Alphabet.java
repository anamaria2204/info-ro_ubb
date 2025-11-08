package org.main;

import java.util.Objects;
public class Alphabet {
    private String symbol;

    public Alphabet(String symbol) {
        this.symbol = symbol;
    }

    public String getSymbol() {
        return symbol;
    }

    @Override
    public String toString() {
        return symbol;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Alphabet alphabet = (Alphabet) o;
        return Objects.equals(symbol, alphabet.symbol);
    }

    @Override
    public int hashCode() {
        return Objects.hash(symbol);
    }
}
