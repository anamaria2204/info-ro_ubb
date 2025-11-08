package main.org;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class SymbolTable {

    private static class Node {
        String value;
        Node left;
        Node right;

        Node(String value){
            this.value = value;
            this.left = null;
            this.right = null;
        }
    }

    private Node root;
    private Map<String, Integer> positionMap;

    public SymbolTable() {
        this.root = null;
        this.positionMap = new HashMap<>();
    }

    public void insert(String value) {
        root = insertRec(root, value);
    }

    private Node insertRec(Node current, String value) {
        if (current == null) {
            return new Node(value);
        }

        int comparison = value.compareTo(current.value);
        if (comparison < 0) {
            current.left = insertRec(current.left, value);
        } else if (comparison > 0) {
            current.right = insertRec(current.right, value);
        }
        return current;
    }

    public int getPosition(String value) {
        if (positionMap.isEmpty()) {
            buildPositionMap();
        }
        return positionMap.getOrDefault(value, -1);
    }

    private void buildPositionMap() {
        List<String> sortedSymbols = getSortedSymbols();
        for (int i = 0; i < sortedSymbols.size(); i++) {
            positionMap.put(sortedSymbols.get(i), i);
        }
    }

    private List<String> getSortedSymbols() {
        List<String> list = new ArrayList<>();
        inOrderTraversal(root, list);
        return list;
    }

    private void inOrderTraversal(Node node, List<String> list) {
        if (node != null) {
            inOrderTraversal(node.left, list);
            list.add(node.value);
            inOrderTraversal(node.right, list);
        }
    }

    public void writeToFile(String filename) throws IOException {
        if (positionMap.isEmpty()) {
            buildPositionMap();
        }

        List<String> sortedSymbols = getSortedSymbols();
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(filename))) {
            bw.write("Tabela de Simboluri \n");
            for (int i = 0; i < sortedSymbols.size(); i++) {
                bw.write(String.format("%-4d -> %s\n", i, sortedSymbols.get(i)));
            }
        }
    }
}
