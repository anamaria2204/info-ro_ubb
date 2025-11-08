package main.org;

class PIFEntry {
    String token;
    int code;
    int position;

    public PIFEntry(String token, int code, int position) {
        this.token = token;
        this.code = code;
        this.position = position;
    }

    @Override
    public String toString() {
        return String.format("%-15s | Cod: %-4d | Poziție TS: %d", "\"" + token + "\"", code, position);
    }
}