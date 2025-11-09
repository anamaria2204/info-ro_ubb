#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <iomanip> 
#include <thread>
#include <string>
#include <cstring> 
#include <iostream>
#include <vector> 
#include <cmath> 

using namespace std;

int N = 10;
int M = 10000;
int K = 5;

float* f;
float* c;
float* v;
float* temp_v;

void generare_fisier_input_binar() {
    ofstream outi("input.bin", ios::binary);
    if (!outi.is_open()) {
        cerr << "Eroare la deschiderea fisierului binar 'input.bin'" << endl;
        return;
    }

    srand(time(NULL));
    float val_pixel;
    for (int i = 0; i < N * M; i++) {
        val_pixel = (float)(rand() % 256);
        outi.write(reinterpret_cast<const char*>(&val_pixel), sizeof(float));
    }

    float val_kernel;
    for (int i = 0; i < K * K; i++) {
        val_kernel = (rand() % 1000) / 1000.0f;
        outi.write(reinterpret_cast<const char*>(&val_kernel), sizeof(float));
    }
    outi.close();
}

void citire_matrice_binar(ifstream& in_file, float* mat, int rows, int cols) {
    in_file.read(reinterpret_cast<char*>(mat), (long long)rows * cols * sizeof(float));
}

void scriere_matrice_binar(ofstream& out_file, float* mat, int rows, int cols) {
    out_file.write(reinterpret_cast<const char*>(mat), (long long)rows * cols * sizeof(float));
}

bool verifica_fisiere(const string& filename1, const string& filename2) {
    ifstream in1(filename1, ios::binary);
    ifstream in2(filename2, ios::binary);

    if (!in1.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide fisierul de verificare: " << filename1 << endl;
        return false;
    }
    if (!in2.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide fisierul de verificare: " << filename2 << endl;
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
                cerr << "Eroare: Fisierele au dimensiuni diferite (prea scurte)." << endl;
                cerr << "Oprire la (" << i << ", " << j << ")." << endl;
                in1.close();
                in2.close();
                return false;
            }

            if (val1 != val2) {
                cerr << "--- VERIFICARE ESUATA! ---" << endl;
                cerr << "Prima diferenta gasita la:" << endl;
                cerr << "  Linia: " << i << ", Coloana: " << j << endl;
                cerr << "  " << filename1 << " are valoarea: " << fixed << setprecision(8) << val1 << endl;
                cerr << "  " << filename2 << " are valoarea: " << fixed << setprecision(8) << val2 << endl;
                in1.close();
                in2.close();
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

    cout << "--- VERIFICARE REUSITA! ---" << endl;
    cout << "Fisierele '" << filename1 << "' si '" << filename2 << "' sunt absolut identice (bit-cu-bit)." << endl;
    return true;
}

void convolutie_secv(float* mat, float* conv) {
    int nr_border = (K - 1) / 2;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            float suma = 0.0f;
            for (int li = -nr_border; li <= nr_border; li++) {
                for (int lj = -nr_border; lj <= nr_border; lj++) {
                    int r_idx = i + li;
                    int c_idx = j + lj;

                    r_idx = std::clamp(r_idx, 0, N - 1);
                    c_idx = std::clamp(c_idx, 0, M - 1);

                    float val_pixel = mat[r_idx * M + c_idx];
                    int k_r_idx = li + nr_border;
                    int k_c_idx = lj + nr_border;

                    suma += val_pixel * conv[k_r_idx * K + k_c_idx];
                }
            }
            temp_v[i * M + j] = suma;
        }
    }
    memcpy(mat, temp_v, (long long)N * M * sizeof(float));
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
                    int r_idx = i + li;
                    int c_idx = j + lj;

                    r_idx = std::clamp(r_idx, 0, N - 1);
                    c_idx = std::clamp(c_idx, 0, M - 1);

                    float val_pixel = f[r_idx * M + c_idx];
                    int k_r_idx = li + nr_border;
                    int k_c_idx = lj + nr_border;

                    suma += val_pixel * c[k_r_idx * K + k_c_idx];
                }
            }
            v[i * M + j] = suma;
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
                    int r_idx = i + li;
                    int c_idx = j + lj;

                    r_idx = std::clamp(r_idx, 0, N - 1);
                    c_idx = std::clamp(c_idx, 0, M - 1);

                    float val_pixel = f[r_idx * M + c_idx];
                    int k_r_idx = li + nr_border;
                    int k_c_idx = lj + nr_border;

                    suma += val_pixel * c[k_r_idx * K + k_c_idx];
                }
            }
            v[i * M + j] = suma;
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
    else if (mod == "verifica_coloane") {
        verifica_fisiere("output_secvential.bin", "output_paralel_coloane.bin");
        return 0;
    }

    try {
        f = new float[(long long)N * M];
        c = new float[(long long)K * K];
        v = new float[(long long)N * M];
        temp_v = new float[(long long)N * M];
    }
    catch (const std::bad_alloc& e) {
        cerr << "Eroare la alocarea memoriei: " << e.what() << endl;
        return 1;
    }

    ifstream in("input.bin", ios::binary);
    if (!in.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide 'input.bin'. Ruleaza modul 'gen' intai." << endl;
        delete[] f; delete[] c; delete[] v; delete[] temp_v;
        return 1;
    }

    citire_matrice_binar(in, f, N, M);
    citire_matrice_binar(in, c, K, K);
    in.close();

    if (mod == "secv") {
        auto start_secv = std::chrono::high_resolution_clock::now();
        convolutie_secv(f, c);
        auto end_secv = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, milli> delta_secv = end_secv - start_secv;

        cout << fixed << setprecision(6) << delta_secv.count() << endl;

        ofstream out_secv("output_secvential.bin", ios::binary);
        scriere_matrice_binar(out_secv, f, N, M);
        out_secv.close();
    }
    else if (mod == "par_linii") {
        if (argc < 3) {
            cerr << "Eroare: Specificati numarul de thread-uri P" << endl;
            return 1;
        }
        int P = atoi(argv[2]);
        std::thread* threads = new std::thread[P];

        auto start_par = std::chrono::high_resolution_clock::now();

        for (int t = 0; t < P; t++) {
            threads[t] = thread(convolutie_worker_orizontala, t, P);
        }
        for (int t = 0; t < P; t++) {
            if (threads[t].joinable()) {
                threads[t].join();
            }
        }

        memcpy(f, v, (long long)N * M * sizeof(float));
        auto end_par = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, milli> delta_par = end_par - start_par;

        cout << fixed << setprecision(6) << delta_par.count() << endl;
        delete[] threads;

        ofstream out_par("output_paralel_linii.bin", ios::binary);
        scriere_matrice_binar(out_par, f, N, M);
        out_par.close();
    }
    else if (mod == "par_coloane") {
        if (argc < 3) {
            cerr << "Eroare: Specificati numarul de thread-uri P" << endl;
            return 1;
        }
        int P = atoi(argv[2]);
        std::thread* threads = new std::thread[P];

        auto start_par = std::chrono::high_resolution_clock::now();
        for (int t = 0; t < P; t++) {
            threads[t] = thread(convolutie_worker_verticala, t, P);
        }
        for (int t = 0; t < P; t++) {
            if (threads[t].joinable()) {
                threads[t].join();
            }
        }

        memcpy(f, v, (long long)N * M * sizeof(float));
        auto end_par = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, milli> delta_par = end_par - start_par;

        cout << fixed << setprecision(6) << delta_par.count() << endl;
        delete[] threads;

        ofstream out_par("output_paralel_coloane.bin", ios::binary);
        scriere_matrice_binar(out_par, f, N, M);
        out_par.close();
    }
    else {
        cerr << "Mod necunoscut: " << mod << endl;
        delete[] f; delete[] c; delete[] v; delete[] temp_v;
        return 1;
    }

    delete[] f;
    delete[] c;
    delete[] v;
    delete[] temp_v;

    return 0;
}