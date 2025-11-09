#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <vector>
#include <thread>
#include <string>
#include <cstring>

using namespace std;

const int N = 10;
const int M = 10000;
const int K = 5;

float f[N][M];
float c[K][K];
float v[N][M];
float temp_v[N][M];

void generare_fisier_input_binar() {
    ofstream outi("input.bin", ios::binary);
    if (!outi.is_open()) {
        cerr << "Eroare la deschiderea fisierului 'input.bin'" << endl;
        return;
    }

    srand(time(NULL));
    float val_pixel;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            val_pixel = (float)(rand() % 256);
            outi.write(reinterpret_cast<const char*>(&val_pixel), sizeof(float));
        }
    }

    float val_kernel;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            val_kernel = (rand() % 1000) / 1000.0f;
            outi.write(reinterpret_cast<const char*>(&val_kernel), sizeof(float));
        }
    }
    outi.close();
}

template <size_t n, size_t m>
void citire_matrice_static_binar(ifstream& in_file, float(&mat)[n][m]) {
    in_file.read(reinterpret_cast<char*>(mat), (long long)n * m * sizeof(float));
}

template <size_t n, size_t m>
void scriere_matrice_static_binar(ofstream& out_file, float(&mat)[n][m]) {
    out_file.write(reinterpret_cast<const char*>(mat), (long long)n * m * sizeof(float));
}

bool verifica_fisiere(const string& filename1, const string& filename2) {
    ifstream in1(filename1, ios::binary);
    ifstream in2(filename2, ios::binary);
    if (!in1.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide: " << filename1 << endl;
        return false;
    }
    if (!in2.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide: " << filename2 << endl;
        in1.close();
        return false;
    }

    cout << "Se verifica fisierele '" << filename1 << "' si '" << filename2 << "' (comparatie bit-cu-bit)..." << endl;
    float val1, val2;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            in1.read(reinterpret_cast<char*>(&val1), sizeof(float));
            in2.read(reinterpret_cast<char*>(&val2), sizeof(float));

            if (!in1 || !in2) {
                cerr << "Eroare: Fisierele au dimensiuni diferite. Oprire la (" << i << ", " << j << ")." << endl;
                return false;
            }

            if (val1 != val2) {
                cerr << "--- VERIFICARE ESUATA! ---" << endl;
                cerr << "Prima diferenta gasita la: Linia " << i << ", Coloana " << j << endl;
                cerr << "  " << filename1 << ": " << fixed << setprecision(8) << val1 << " | " << filename2 << ": " << fixed << setprecision(8) << val2 << endl;
                return false;
            }
        }
    }

    in1.peek();
    in2.peek();
    if (!in1.eof() || !in2.eof()) {
        cerr << "Eroare: Fisierele au dimensiuni diferite (unul este mai lung)." << endl;
        in1.close();
        in2.close();
        return false;
    }

    in1.close();
    in2.close();
    cout << "--- VERIFICARE REUSITA! --- Fisierele sunt absolut identice (bit-cu-bit)." << endl;
    return true;
}

template <int n, int m, int k>
void convolutie_secv(float(&mat)[n][m], float(&conv)[k][k]) {
    int nr_border = (k - 1) / 2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            float suma = 0.0f;
            for (int li = -nr_border; li <= nr_border; li++) {
                for (int lj = -nr_border; lj <= nr_border; lj++) {
                    int r_idx = std::clamp(i + li, 0, n - 1);
                    int c_idx = std::clamp(j + lj, 0, m - 1);
                    int k_r_idx = li + nr_border;
                    int k_c_idx = lj + nr_border;
                    suma += mat[r_idx][c_idx] * conv[k_r_idx][k_c_idx];
                }
            }
            temp_v[i][j] = suma;
        }
    }
    memcpy(mat, temp_v, sizeof(float) * n * m);
}

void convolutie_worker_orizontala(int tid, int P) {
    int nr_border = (K - 1) / 2;
    int chunk_size = N / P;
    int remainder = N % P;
    int start_row = tid * chunk_size + min(tid, remainder);
    int end_row = (tid + 1) * chunk_size + min(tid + 1, remainder);

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < M; j++) {
            float suma = 0.0f;
            for (int li = -nr_border; li <= nr_border; li++) {
                for (int lj = -nr_border; lj <= nr_border; lj++) {
                    int r_idx = std::clamp(i + li, 0, N - 1);
                    int c_idx = std::clamp(j + lj, 0, M - 1);
                    int k_r_idx = li + nr_border;
                    int k_c_idx = lj + nr_border;
                    suma += f[r_idx][c_idx] * c[k_r_idx][k_c_idx];
                }
            }
            v[i][j] = suma;
        }
    }
}

void convolutie_worker_verticala(int tid, int P) {
    int nr_border = (K - 1) / 2;
    int chunk_size = M / P;
    int remainder = M % P;
    int start_col = tid * chunk_size + min(tid, remainder);
    int end_col = (tid + 1) * chunk_size + min(tid + 1, remainder);

    for (int i = 0; i < N; i++) {
        for (int j = start_col; j < end_col; j++) {
            float suma = 0.0f;
            for (int li = -nr_border; li <= nr_border; li++) {
                for (int lj = -nr_border; lj <= nr_border; lj++) {
                    int r_idx = std::clamp(i + li, 0, N - 1);
                    int c_idx = std::clamp(j + lj, 0, M - 1);
                    int k_r_idx = li + nr_border;
                    int k_c_idx = lj + nr_border;
                    suma += f[r_idx][c_idx] * c[k_r_idx][k_c_idx];
                }
            }
            v[i][j] = suma;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "Eroare: Specificati modul ('gen', 'secv', 'par_linii P', 'par_coloane P', 'verifica_linii', 'verifica_coloane')" << endl;
        return 1;
    }

    string mod = argv[1];

    if (mod == "gen") {
        generare_fisier_input_binar();
        cout << "Fisierul 'input.bin' a fost generat." << endl;
        return 0;
    }

    if (mod == "verifica_linii") {
        verifica_fisiere("output_secvential.bin", "output_paralel_linii.bin");
        return 0;
    }
    if (mod == "verifica_coloane") {
        verifica_fisiere("output_secvential.bin", "output_paralel_coloane.bin");
        return 0;
    }

    ifstream in("input.bin", ios::binary);
    if (!in.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide 'input.bin'. Ruleaza 'gen' intai." << endl;
        return 1;
    }

    citire_matrice_static_binar(in, f);
    citire_matrice_static_binar(in, c);
    in.close();

    if (mod == "secv") {
        auto start_secv = std::chrono::high_resolution_clock::now();
        convolutie_secv(f, c);
        auto end_secv = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, milli> delta_secv = end_secv - start_secv;

        cout << fixed << setprecision(6) << delta_secv.count() << endl;

        ofstream out_secv("output_secvential.bin", ios::binary);
        scriere_matrice_static_binar(out_secv, f);
        out_secv.close();
    }
    else if (mod == "par_linii") {
        if (argc < 3) {
            cerr << "Eroare: Specificati numarul de thread-uri P" << endl;
            return 1;
        }
        int P = atoi(argv[2]);

        vector<thread> threads;
        auto start_par = std::chrono::high_resolution_clock::now();
        for (int t = 0; t < P; t++) {
            threads.push_back(thread(convolutie_worker_orizontala, t, P));
        }
        for (auto& th : threads) {
            th.join();
        }

        memcpy(f, v, sizeof(float) * N * M);

        auto end_par = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, milli> delta_par = end_par - start_par;

        cout << fixed << setprecision(6) << delta_par.count() << endl;

        ofstream out_par("output_paralel_linii.bin", ios::binary);
        scriere_matrice_static_binar(out_par, f);
        out_par.close();
    }
    else if (mod == "par_coloane") {
        if (argc < 3) {
            cerr << "Eroare: Specificati numarul de thread-uri P" << endl;
            return 1;
        }
        int P = atoi(argv[2]);

        vector<thread> threads;
        auto start_par = std::chrono::high_resolution_clock::now();
        for (int t = 0; t < P; t++) {
            threads.push_back(thread(convolutie_worker_verticala, t, P));
        }
        for (auto& th : threads) {
            th.join();
        }

        memcpy(f, v, sizeof(float) * N * M);

        auto end_par = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, milli> delta_par = end_par - start_par;

        cout << fixed << setprecision(6) << delta_par.count() << endl;

        ofstream out_par("output_paralel_coloane.bin", ios::binary);
        scriere_matrice_static_binar(out_par, f);
        out_par.close();
    }
    else {
        cerr << "Mod necunoscut: " << mod << endl;
        return 1;
    }

    return 0;
}