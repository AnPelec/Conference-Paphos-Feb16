#include <bits/stdc++.h>

#define MAXN 100   /// complexity of algorithm is O(N^3) where N
                  ///   is the number of equations and variables

using namespace std;

/// Source : Competitive Programming 3 by Steven & Felix Halim

/**
    N : number of equations
    answer : column vector where solution is stored
    matrix : matrix where coefficients and values are stored
**/

int N;
double answer[MAXN];
double matrix[MAXN][MAXN+1];

void Read() {
    cin >> N;

    for (int i=0; i<N; i++) {
        for (int j=0; j<=N; j++) {
            cin >> matrix[i][j];
        }
    }
}

double dAbs(double x) {
    if (x < 0.0) return -1.0*x;
    return x;
}

void GaussianEliminationAlgorithm() {
    int next;
    double temp;

    for (int i=0; i<N-1; i++) {  /// forward elimination phase

        /// find row with largest coefficient
        next = i;
        for (int j=i+1; j<N; j++) {
            if (dAbs(matrix[j][i]) > dAbs(matrix[next][i])) {
                next = j;
            }
        }

        /// swap the two rows to minimize precision errors
        for (int j=i; j<=N; j++) {
            swap(matrix[i][j], matrix[next][j]);
        }

        for (int j=i+1; j<N; j++) {
            for (int k=N; k>=i; k--) {
                matrix[j][k] -= matrix[i][k] * matrix[j][i] / matrix[i][i];
            }
        }
    }

    /// back substitution phase
    for (int i=N-1; i>=0; i--) {
        temp = 0.0;
        for (int j=i+1; j<N; j++) {
            temp += matrix[i][j] * answer[j];
        }
        answer[i] = (matrix[i][N] - temp) / matrix[i][i];
    }
}

int main()
{
    Read();

    GaussianEliminationAlgorithm();

    for (int i=0; i<N; i++) {
        cout << "Value of variable: " << answer[i] << "\n";
    }

    return 0;
}
