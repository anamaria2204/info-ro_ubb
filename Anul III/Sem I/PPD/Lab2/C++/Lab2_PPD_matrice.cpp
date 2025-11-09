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
#include <barrier>

using namespace std;

int N = 10;
int M = 10;
int K = 3;

float* f;
float* c;

void generare_fisier_input_binar() {
    ofstream outi("input.bin", ios::binary);
    if (!outi.is_open()) { cerr << "Eroare deschidere input.bin\n"; return; }
    srand(time(NULL));
    float val;
    for (long long i = 0; i < (long long)N * M; ++i) {
        val = (float)(rand() % 256);
        outi.write(reinterpret_cast<const char*>(&val), sizeof(float));
    }
    for (int i = 0; i < K * K; ++i) {
        val = (rand() % 1000) / 1000.0f;
        outi.write(reinterpret_cast<const char*>(&val), sizeof(float));
    }
    outi.close();
}

void citesteMatriceDinBinar(ifstream& in_file, float* mat, int rows, int cols) {
    in_file.read(reinterpret_cast<char*>(mat), (long long)rows * cols * sizeof(float));
}

void scrieMatriceInBinar(ofstream& out_file, float* mat, int rows, int cols) {
    out_file.write(reinterpret_cast<const char*>(mat), (long long)rows * cols * sizeof(float));
}

bool verificaIdentitateFisiereBinare(const string& filename1, const string& filename2) {
    ifstream in1(filename1, ios::binary); ifstream in2(filename2, ios::binary);
    if (!in1.is_open() || !in2.is_open()) { cerr << "Eroare deschidere fisiere verificare.\n"; return false; }
    cout << "Se verifica fisierele '" << filename1 << "' si '" << filename2 << "' (comparatie bit-cu-bit)..." << endl;
    float v1, v2;
    for (long long i = 0; i < (long long)N * M; ++i) {
        in1.read(reinterpret_cast<char*>(&v1), sizeof(float)); in2.read(reinterpret_cast<char*>(&v2), sizeof(float));
        if (!in1 || !in2) { cerr << "Eroare: Dimensiuni diferite (prea scurte).\n"; return false; }
        if (v1 != v2) { cerr << "--- VERIFICARE ESUATA! --- Diferenta la elementul " << i << endl; return false; }
    }
    in1.peek(); in2.peek();
    if (!in1.eof() || !in2.eof()) { cerr << "Eroare: Dimensiuni diferite (prea lungi).\n"; return false; }
    cout << "--- VERIFICARE REUSITA! --- Fisierele sunt absolut identice." << endl;
    return true;
}

inline float calculeazaPixel(int j, float* r_sus, float* r_mid, float* r_jos, float* conv) {
    float suma = 0.0f;
    int nr_border = (K - 1) / 2;
    for (int li = -nr_border; li <= nr_border; li++) {
        float* sursa_linie = (li == -1) ? r_sus : ((li == 0) ? r_mid : r_jos);
        for (int lj = -nr_border; lj <= nr_border; lj++) {
            int c_idx = std::clamp(j + lj, 0, M - 1);
            float val_pixel = sursa_linie[c_idx];
            int k_r_idx = li + nr_border;
            int k_c_idx = lj + nr_border;
            suma += val_pixel * conv[k_r_idx * K + k_c_idx];
        }
    }
    return suma;
}

void aplicaConvolutieSecventialInPlaceLinii(float* mat, float* conv) {
    float* prev_line = new float[M];
    float* temp_line = new float[M];
    memcpy(prev_line, &mat[0], M * sizeof(float));

    for (int i = 0; i < N; i++) {
        float* r_sus = (i == 0) ? prev_line : prev_line;
        float* r_mid = (i == 0) ? prev_line : &mat[i * M];
        float* r_jos = (i + 1 >= N) ? r_mid : &mat[(i + 1) * M];

        for (int j = 0; j < M; j++) {
            temp_line[j] = calculeazaPixel(j, r_sus, r_mid, r_jos, conv);
        }

        if (i < N - 1) {
            memcpy(prev_line, r_mid, M * sizeof(float));
        }

        memcpy(&mat[i * M], temp_line, M * sizeof(float));
    }

    delete[] prev_line;
    delete[] temp_line;
}

void workerParalelCalculeazaLiniiSincronizat(int tid, int P, float* mat, float* conv, std::barrier<>& barieraSincronizare) {
    int chunk_size = N / P;
    int remainder = N % P;
    int start_row;
    int end_row;

    if (tid < remainder) {
        start_row = tid * (chunk_size + 1);
        end_row = start_row + (chunk_size + 1);
    }
    else {
        start_row = tid * chunk_size + remainder;
        end_row = start_row + chunk_size;
    }

    float* sus_buffer = new float[M];
    float* jos_buffer = nullptr;
    float* temp_line = new float[M];

    if (start_row > 0) {
        memcpy(sus_buffer, &mat[(start_row - 1) * M], M * sizeof(float));
    }
    else {
        memcpy(sus_buffer, &mat[0], M * sizeof(float));
    }

    if (end_row < N && end_row > start_row) {
        jos_buffer = new float[M];
        memcpy(jos_buffer, &mat[end_row * M], M * sizeof(float));
    }

    barieraSincronizare.arrive_and_wait();

    float* current_prev_line = sus_buffer;

    for (int i = start_row; i < end_row; i++) {
        float* r_sus = current_prev_line;
        float* r_mid = &mat[i * M];
        float* r_jos;

        if (i + 1 == end_row && jos_buffer != nullptr) {
            r_jos = jos_buffer;
        }
        else if (i + 1 >= N) {
            r_jos = r_mid;
        }
        else {
            r_jos = &mat[(i + 1) * M];
        }

        for (int j = 0; j < M; j++) {
            temp_line[j] = calculeazaPixel(j, r_sus, r_mid, r_jos, conv);
        }

        if (i + 1 < end_row) {
            memcpy(current_prev_line, r_mid, M * sizeof(float));
        }

        memcpy(&mat[i * M], temp_line, M * sizeof(float));
    }

    delete[] sus_buffer;
    if (jos_buffer != nullptr) delete[] jos_buffer;
    delete[] temp_line;
}

void aplicaConvolutieParalelInPlaceLiniiSincronizat(float* mat, float* conv, int P) {
    std::thread* threads = new std::thread[P];
    std::barrier<> barieraSincronizare(P);

    for (int t = 0; t < P; t++) {
        threads[t] = thread(workerParalelCalculeazaLiniiSincronizat, t, P, mat, conv, std::ref(barieraSincronizare));
    }

    for (int t = 0; t < P; t++) {
        if (threads[t].joinable()) threads[t].join();
    }

    delete[] threads;
}


int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "Eroare: Specificati modul ('gen', 'secv', 'paralel P', 'verifica')" << endl;
        return 1;
    }

    K = 3;
    N = 10000; M = 10000;

    string mod = argv[1];

    if (mod == "gen") {
        generare_fisier_input_binar();
        cout << "Fisierul 'input.bin' a fost generat pt K=3." << endl;
        return 0;
    }

    if (mod == "verifica") {
        verificaIdentitateFisiereBinare("output_secvential.bin", "output_paralel.bin");
        return 0;
    }

    try {
        f = new float[(long long)N * M];
        c = new float[(long long)K * K];
    }
    catch (const std::bad_alloc& e) { cerr << "Eroare alocare memorie\n"; return 1; }

    ifstream in("input.bin", ios::binary);
    if (!in.is_open()) { cerr << "Eroare deschidere input.bin. Ruleaza 'gen' intai.\n"; return 1; }
    citesteMatriceDinBinar(in, f, N, M);
    citesteMatriceDinBinar(in, c, K, K);
    in.close();

    float* f_backup = new float[(long long)N * M];
    memcpy(f_backup, f, (long long)N * M * sizeof(float));


    if (mod == "secv") {
        auto start_secv = std::chrono::high_resolution_clock::now();
        aplicaConvolutieSecventialInPlaceLinii(f, c);
        auto end_secv = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, milli> delta_secv = end_secv - start_secv;
        cout << fixed << setprecision(6) << delta_secv.count() << endl;
        ofstream out_secv("output_secvential.bin", ios::binary);
        scrieMatriceInBinar(out_secv, f, N, M);
        out_secv.close();
    }
    else if (mod == "paralel") {
        if (argc < 3) { cerr << "Specificati P\n"; return 1; }
        int P = atoi(argv[2]);
        if (P <= 0) { cerr << "P trebuie > 0\n"; return 1; }

        memcpy(f, f_backup, (long long)N * M * sizeof(float));

        auto start_par = std::chrono::high_resolution_clock::now();
        aplicaConvolutieParalelInPlaceLiniiSincronizat(f, c, P);
        auto end_par = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, milli> delta_par = end_par - start_par;
        cout << fixed << setprecision(6) << delta_par.count() << endl;
        ofstream out_par("output_paralel.bin", ios::binary);
        scrieMatriceInBinar(out_par, f, N, M);
        out_par.close();
    }
    else {
        cerr << "Mod necunoscut: " << mod << endl;
        delete[] f; delete[] c; delete[] f_backup;
        return 1;
    }

    delete[] f;
    delete[] c;
    delete[] f_backup;

    return 0;
}