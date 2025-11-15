#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

const int CYLINDERS = 5000;
const int REQUESTS = 1000;

//------------------ ALGORITHMS -----------------------

int run_fcfs(const vector<int>& req, int head, vector<int>& path) {
    int movement = 0;
    int current = head;

    path.push_back(current);
    for (int r : req) {
        movement += abs(current - r);
        current = r;
        path.push_back(current);
    }
    return movement;
}

int run_scan(vector<int> req, int head, vector<int>& path) {
    int movement = 0;
    int current = head;

    vector<int> left, right;

    for (int r : req) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }

    sort(left.begin(), left.end(), greater<int>());
    sort(right.begin(), right.end());

    path.push_back(current);

    // Ir hacia la derecha
    for (int r : right) {
        movement += abs(current - r);
        current = r;
        path.push_back(current);
    }

    // Llegar al final del disco
    if (current != CYLINDERS - 1) {
        movement += abs(current - (CYLINDERS - 1));
        current = CYLINDERS - 1;
        path.push_back(current);
    }

    // Volver hacia la izquierda
    for (int r : left) {
        movement += abs(current - r);
        current = r;
        path.push_back(current);
    }

    return movement;
}

int run_cscan(vector<int> req, int head, vector<int>& path) {
    int movement = 0;
    int current = head;

    vector<int> left, right;

    for (int r : req) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    path.push_back(current);

    // Atender derecha
    for (int r : right) {
        movement += abs(current - r);
        current = r;
        path.push_back(current);
    }

    // Ir al extremo derecho
    if (current != CYLINDERS - 1) {
        movement += abs(current - (CYLINDERS - 1));
        current = CYLINDERS - 1;
        path.push_back(current);
    }

    // Salto circular desde el final hacia 0
    movement += (CYLINDERS - 1);
    current = 0;
    path.push_back(current);

    // Atender izquierda
    for (int r : left) {
        movement += abs(current - r);
        current = r;
        path.push_back(current);
    }

    return movement;
}

//------------------ WRITE GNUPLOT DATA -----------------------

void write_path_file(const string& filename, const vector<int>& path) {
    ofstream out(filename);
    for (int i = 0; i < path.size(); i++)
        out << i << " " << path[i] << "\n";
}

void write_bars_file(const string& filename, int a, int b, int c) {
    ofstream out(filename);
    out << "FCFS " << a << "\n";
    out << "SCAN " << b << "\n";
    out << "C-SCAN " << c << "\n";
}

void generate_graphs() {
    system("start gnuplot -p plot_paths.gp");
    system("start gnuplot -p plot_bars.gp");
}

//------------------ MAIN -----------------------

int main() {
    srand(time(NULL));

    int head;

    cout << "Ingrese la posición inicial del cabezal (0 - " << CYLINDERS - 1 << "): ";
    cin >> head;

    // Validación simple
    if (head < 0 || head >= CYLINDERS) {
        cout << "Valor inválido. Debe estar entre 0 y " << CYLINDERS - 1 << ".\n";
        return 1;
    }

    vector<int> requests(REQUESTS);

    for (int i = 0; i < REQUESTS; i++)
        requests[i] = rand() % CYLINDERS;

    vector<int> p1, p2, p3;
    int m1 = run_fcfs(requests, head, p1);
    int m2 = run_scan(requests, head, p2);
    int m3 = run_cscan(requests, head, p3);

    write_path_file("fcfs.dat", p1);
    write_path_file("scan.dat", p2);
    write_path_file("cscan.dat", p3);

    write_bars_file("performance.dat", m1, m2, m3);

    generate_graphs();

    cout << "\nGraficos generados exitosamente.\n";
    cout << "=== DISK SCHEDULING SIMULATOR ===\n";
    cout << "Initial head position: " << head << "\n";
    cout << "Generated requests: " << REQUESTS << "\n\n";

    cout << "---- RESULTS ----\n";
    cout << "FCFS    total movement: " << m1 << " cylinders\n";
    cout << "SCAN    total movement: " << m2 << " cylinders\n";
    cout << "C-SCAN  total movement: " << m3 << " cylinders\n";

    return 0;
}
