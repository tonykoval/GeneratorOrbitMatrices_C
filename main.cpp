#include<iostream>
#include<vector>

#include "libraryZ3.hpp"

using namespace std;

int n = 15;
int k = 6;
int l = 1;
int m = 3;
int p = 3;
int f = 3;
int o = (n - f) / p;

int isoConst = 5;

vector<vector<int>> linEqFixSolution;
vector<vector<int>> linEqOrbitSolution0;
vector<vector<int>> linEqOrbitSolution2;

// from Behbahani thesis
void solveLinearEquations() {
    {
        // Create and solve linear equations for fixed rows using z3 library
        // x0 + x1 = f
        // y0 + y1 = o
        // x1 + p*y1 = k
        vector<vector<int>> linearSystem {{1, 1, 0, 0}, {0, 0, 1, 1}, {0, 1, 0, p}};
        vector<int> vect {f, o, k};
        vector<vector<int>> tmpSolutions = solveLinearEquations(linearSystem, vect, 0, max(f, o));

        // filter: matrix must have 0 on diagonalise -> x0 >= 1
        for (int i=0; i<tmpSolutions.size(); i++) {
            if (tmpSolutions[i][0] != 0) linEqFixSolution.push_back(tmpSolutions[i]);
        }
    }

    {
        // Create and solve linear equations for fixed rows
        // x0 + x1 = f
        // y0 + y1 + y2 + y3 = o
        // x1 + y1 + 2 y2 + 3 y3 = k
        // p x1 + y1 + 4 y2 + 9 y3 = s_rr / p, where s_rr = (k - m) n_r[p] + m n_r^2[p] + (l-m)c_rr n_r[p] and c_rr is 0 1 2
        // there is lemma in theory c_rr could be only even, that 0 or 2 that implies 2 possible linear systems
        // s = (k-m)*p + m*p*p + (l-m)*c_rr*p
        vector<vector<int>> linearSystem = {{1, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1}, {0, 1, 0, 1, 2, 3}, {0, 3, 0, 1, 4, 9}};
        int s = (k - m) * p + m * p * p + (l - m) * 0 * p;
        vector<int> vect {f, o, k, s / 3};
        vector<vector<int>> tmpSolutions = solveLinearEquations(linearSystem, vect, 0, max(f, o));

        // filter: if c_rr = 0 then y0 >0
        for (int i=0; i<tmpSolutions.size(); i++) {
            if (tmpSolutions[i][2] != 0) linEqOrbitSolution0.push_back(tmpSolutions[i]);
        }
    }

    {
        vector<vector<int>> linearSystem = {{1, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1}, {0, 1, 0, 1, 2, 3}, {0, 3, 0, 1, 4, 9}};
        int s = (k - m) * p + m * p * p + (l - m) * 2 * p;
        vector<int> vect {f, o, k, s / 3};
        linEqOrbitSolution2 = solveLinearEquations(linearSystem, vect, 0, max(f, o));
    }
}

int main() {
    cout << "Program start " << n << " " << k << " " << l << " " << m << " " << p << " " << f << endl;
    cout << "Number of fixed points and orbits: " << f << " " << o << endl;
    cout << "Size of orbit matrix: " << (f + o) << "x" << (f + o) << endl;

    solveLinearEquations();

    cout << "Number of solutions on fixed rows: " << linEqFixSolution.size() << endl;
    cout << "Number of solutions on orbit rows: " << linEqOrbitSolution0.size() << " " << linEqOrbitSolution2.size() << endl;

    return 0;
}